#pragma once
#include "skoarcery.hpp"

#include "lex_fwd.hpp"
#include "noad_fwd.hpp"
#include "skoarpion_fwd.hpp"
#include "minstrel_fwd.hpp"
#include "event_fwd.hpp"

#include "skoarpuscle_fwd.hpp"
#include "skoar_fwd.hpp"

#include "spells.hpp"

#define SKOARPUSCLE(x) Skoarpuscle::wrap<decltype(x)>(x)

union SkoarpuscleValue {
	SkoarInt Int;
	SkoarFloat Float;
	bool Boolean;

	string *String;
	Skoarpion *Skoarpion;
	Skoarpuscle *Skoarpuscle;
	list<class Skoarpuscle *> *List;
	void *Void;

	SkoarNoad *Subtree;

	SkoarpuscleValue();
	SkoarpuscleValue(int x);
	SkoarpuscleValue(long x);
	SkoarpuscleValue(long long x);
	SkoarpuscleValue(float x);
	SkoarpuscleValue(double x);
	SkoarpuscleValue(bool x);
	SkoarpuscleValue(void *x);

};

class Skoarpuscle {
public:
	SkoarpuscleValue val;

	Skoarpuscle();

	SpellOfMinstrels on_enter;

	/*template <typename T>
	static Skoarpuscle *wrap(T x) {

		SkoarpuscleValue v = x;

		if (is_pointer<T>::value) {
			if ((void*)x == nullptr)
				return new SkoarpuscleCrap();
		}
		if (typeid(x) == typeid(Skoarpuscle*))
			return x;

		if (typeid(x) == typeid(Skoarpion*))
			return new SkoarpuscleSkoarpion(x);

		if (typeid(x) == typeid(string*))
			return new SkoarpuscleString(x);

		if (typeid(x) == typeid(list<Skoarpuscle*>*))
			return new SkoarpuscleList(x);
	
		if (typeid(x) == typeid(int))
			return new SkoarpuscleInt(x);

		if (typeid(x) == typeid(float))
			return new SkoarpuscleFloat(x);

		if (typeid(x) == typeid(double))
			return new SkoarpuscleFloat(x);

		if (typeid(x) == typeid(bool)) {
			if (x)
				return new SkoarpuscleTrue();
			return new SkoarpuscleFalse();
		}

		return new SkoarpuscleUnknown(new string(typeid(x).name()));
	} */

	virtual bool isNoatworthy() {
		return false;
	}
	virtual void *Skoarpuscle::asNoat() {
		return nullptr;
	}

	virtual Skoarpuscle *skoar_msg(SkoarpuscleMsg *msg, SkoarMinstrel *minstrel) {
		return nullptr;
	}
	
	virtual SkoarInt Skoarpuscle::flatten(SkoarMinstrel *m) {
		return val.Int;
	}
	
	virtual string Skoarpuscle::asString() {
		return string("Skoarpuscle");
	}


};

class SkoarpuscleUnknown : public Skoarpuscle {
public:
	SkoarpuscleUnknown();
};

class SkoarpuscleCrap : public Skoarpuscle{
public:
	SkoarpuscleCrap();
};

class SkoarpuscleTrue : public Skoarpuscle {
public:
	SkoarpuscleTrue();
};

class SkoarpuscleFalse : public Skoarpuscle {
public:
	SkoarpuscleFalse();
};

class SkoarpuscleFreq : public Skoarpuscle {
public:
    SkoarpuscleFreq(string *);
	bool isNoatworthy() override;
	void *asNoat() override;
};

class SkoarpuscleInt : public Skoarpuscle {
public:
	SkoarpuscleInt(SkoarInt v);
	bool isNoatworthy() override; 
	void *asNoat() override;
};

class SkoarpuscleFloat : public Skoarpuscle {
public:
    SkoarpuscleFloat(double);
	bool isNoatworthy() override;
	void *asNoat() override;
};

class SkoarpuscleNoat : public Skoarpuscle {
public:
    SkoarpuscleNoat(string *);
	bool isNoatworthy() override;
	void *asNoat() override;
};

class SkoarpuscleChoard : public Skoarpuscle {
public:
    SkoarpuscleChoard(string *);
	bool isNoatworthy() override;
	void *asNoat() override;
};

class SkoarpuscleString : public Skoarpuscle {
public:
    SkoarpuscleString(string *);
};

class SkoarpuscleSymbol : public Skoarpuscle {
public:
    SkoarpuscleSymbol(string *);
	Skoarpuscle *skoar_msg(SkoarpuscleMsg *msg, SkoarMinstrel *minstrel) override;

};

class SkoarpuscleSymbolName : public Skoarpuscle {
public:
    SkoarpuscleSymbolName(string *);
};

class SkoarpuscleRest : public Skoarpuscle {
public:
	SkoarpuscleRest(SkoarToke *);
};

class SkoarpuscleBeat : public Skoarpuscle {
public:
	SkoarpuscleBeat(SkoarToke *);
};

class SkoarpuscleBars : public Skoarpuscle {
	SkoarNoad *noad;
	bool pre_repeat;
	bool post_repeat;
public:
	SkoarpuscleBars(SkoarToke *);
};

class SkoarpuscleVolta : public Skoarpuscle {
public:
	SkoarNoad *noad;
	SkoarpuscleVolta(SkoarNoad *, SkoarToke *);
};

class SkoarpuscleMeter : public Skoarpuscle {
public:
	SkoarpuscleMeter(SkoarToke *);
};

class SkoarpuscleCarrots : public Skoarpuscle {
public:
	SkoarpuscleCarrots(SkoarToke *);
};

class SkoarpuscleTuplet : public Skoarpuscle {
public:
	SkoarpuscleTuplet(SkoarToke *);
};

class SkoarpuscleDynamic : public Skoarpuscle {
public:
	SkoarpuscleDynamic(SkoarToke *);

	SkoarFloat amp();
};

class SkoarpuscleOctaveShift : public Skoarpuscle {
public:
	SkoarpuscleOctaveShift(SkoarToke *);
};

class SkoarpuscleBooleanOp : public Skoarpuscle {
public:
	function<bool(Skoarpuscle *, Skoarpuscle *)> f;

	SkoarpuscleBooleanOp(SkoarToke *);
	bool compare(Skoarpuscle *a, Skoarpuscle *b, SkoarMinstrel *m);
};

class SkoarpuscleVoice : public Skoarpuscle {
public:
	SkoarpuscleVoice(SkoarToke *);
};

class SkoarpuscleSegno : public Skoarpuscle {
public:
	SkoarNoad *noad;

	SkoarpuscleSegno(SkoarNoad *, SkoarToke *);
};

class SkoarpuscleRep : public Skoarpuscle {
public:
	SkoarpuscleRep(SkoarToke *);
};

class SkoarpuscleFine : public Skoarpuscle {
public:
    SkoarpuscleFine();
};

class SkoarpuscleMsgName : public Skoarpuscle {
public:
    SkoarpuscleMsgName(string *);
};

class SkoarpuscleMathOp : public Skoarpuscle {
public:
	function<void(SkoarMinstrel *m, Skoarpuscle *, Skoarpuscle *)> f;

    SkoarpuscleMathOp(SkoarToke *);
	void calculate(SkoarMinstrel *m, Skoarpuscle *a, Skoarpuscle *b);
};

class SkoarpuscleList : public Skoarpuscle {
public:
	SkoarpuscleList();

	SkoarpuscleList(list<Skoarpuscle*>* listy);
	
	bool isNoatworthy() override;
	void *asNoat() override;
	Skoarpuscle *skoar_msg(SkoarpuscleMsg *msg, SkoarMinstrel *minstrel) override;

};

class SkoarpuscleListSep : public Skoarpuscle {
public:
	SkoarpuscleListSep();
};

class SkoarpuscleListEnd : public Skoarpuscle {
public:
	SkoarpuscleListEnd();
};

class SkoarpuscleArgsSpec : public SkoarpuscleList {
public:
	SkoarpuscleArgsSpec();
	SkoarpuscleArgsSpec(SkoarNoad *);
};

class SkoarpuscleSkoarpion : public Skoarpuscle {
public:
	list<string*> *msg_arr;

	SkoarpuscleSkoarpion(Skoarpion *);
	SkoarpuscleSkoarpion(Skoarpion *, SkoarNoad *);

	Skoarpuscle *skoar_msg(SkoarpuscleMsg *msg, SkoarMinstrel *minstrel) override;

	void on_enter_method(SkoarMinstrel *m);
};

class SkoarpuscleProjection : public Skoarpuscle {
public:
	SkoarpuscleProjection(SkoarProjection *);
};

class SkoarpuscleDeref : public Skoarpuscle {
public:
	list<string*> msg_arr;
	SkoarpuscleArgs * args;

	SkoarpuscleDeref();
	SkoarpuscleDeref(string *msg_name, SkoarpuscleArgs *);

	Skoarpuscle *lookup(SkoarMinstrel* minstrel);
};

class SkoarpuscleConditional : public Skoarpuscle {
public:
	list<Skoarpuscle *> *ifs;

	SkoarpuscleConditional();
	SkoarpuscleConditional(Skoar *, SkoarNoad *);

	
};

class SkoarpuscleBoolean : public Skoarpuscle {
public:
	SkoarpuscleBoolean();
	SkoarpuscleBoolean(SkoarNoad *);

	bool evaluate(SkoarMinstrel *m);
	

};

class SkoarpuscleLoop : public Skoarpuscle {
public:

	SkoarpuscleConditional *condition;
	Skoarpuscle *body;
	list<Skoarpuscle*> *each;

	SkoarpuscleLoop();
	SkoarpuscleLoop(Skoar *, SkoarNoad *);

	Skoarpuscle *lookup(SkoarMinstrel* minstrel);

	SkoarpuscleLoop *foreach(SkoarpuscleList *listy);
};

class SkoarpuscleGoto : public Skoarpuscle {
public:
	string *nav_cmd;
	bool al_fine;

	SkoarpuscleGoto(SkoarNoad *);
};

class SkoarpuscleArgs : public Skoarpuscle {
public:
	SkoarpuscleArgs();
};

class SkoarpuscleLoopMsg : public Skoarpuscle {
public:
	SkoarpuscleLoopMsg();
	SkoarpuscleLoopMsg(string *);
};

class SkoarpuscleMsg : public Skoarpuscle {
public:
	SkoarpuscleArgs *args;
	SkoarpuscleMsg();
	SkoarpuscleMsg(string *v, SkoarpuscleArgs *a);
	//void *get_msg_arr(SkoarMinstrel *m);
};


class SkoarpuscleExprEnd : public Skoarpuscle {
public:
	SkoarpuscleExprEnd();
};
