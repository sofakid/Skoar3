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

	wstring *String;
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
	
	virtual wstring Skoarpuscle::asString() {
		return wstring(L"Skoarpuscle");
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
    SkoarpuscleFreq(wstring *);
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
    SkoarpuscleNoat(wstring *);
	bool isNoatworthy() override;
	void *asNoat() override;
};

class SkoarpuscleChoard : public Skoarpuscle {
public:
    SkoarpuscleChoard(wstring *);
	bool isNoatworthy() override;
	void *asNoat() override;
};

class SkoarpuscleString : public Skoarpuscle {
public:
    SkoarpuscleString(wstring *);
};

class SkoarpuscleSymbol : public Skoarpuscle {
public:
    SkoarpuscleSymbol(wstring *);
	Skoarpuscle *skoar_msg(SkoarpuscleMsg *msg, SkoarMinstrel *minstrel) override;

};

class SkoarpuscleSymbolName : public Skoarpuscle {
public:
    SkoarpuscleSymbolName(wstring *);
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
    SkoarpuscleMsgName(wstring *);
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
	list<wstring*> *msg_arr;

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
	list<wstring*> msg_arr;
	SkoarpuscleArgs * args;

	SkoarpuscleDeref();
	SkoarpuscleDeref(wstring *msg_name, SkoarpuscleArgs *);

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
	wstring *nav_cmd;
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
	SkoarpuscleLoopMsg(wstring *);
};

class SkoarpuscleMsg : public Skoarpuscle {
public:
	SkoarpuscleArgs *args;
	SkoarpuscleMsg();
	SkoarpuscleMsg(wstring *v, SkoarpuscleArgs *a);
	//void *get_msg_arr(SkoarMinstrel *m);
};


class SkoarpuscleExprEnd : public Skoarpuscle {
public:
	SkoarpuscleExprEnd();
};
