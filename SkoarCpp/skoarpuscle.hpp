#pragma once
#include "skoarcery.hpp"

#include "lex_fwd.hpp"
#include "noad_fwd.hpp"
#include "skoarpion_fwd.hpp"
#include "minstrel_fwd.hpp"
#include "event_fwd.hpp"

#include "skoarpuscle_fwd.hpp"

#define SKOARPUSCLE(x) Skoarpuscle::wrap<decltype(x)>(x)

union SkoarpuscleValue {
	long long Int;
	double Float;
	bool Boolean;

	string *String;
	Skoarpion *Skoarpion;
	Skoarpuscle *Skoarpuscle;
	list<class Skoarpuscle *> *List;
	void *Void;

	SkoarNoad *Subtree;

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

	function<void(SkoarMinstrel *m)> on_enter;

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

	bool isNoatworthy() {
		return false;
	}
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
};

class SkoarpuscleInt : public Skoarpuscle {
public:
    SkoarpuscleInt(int);
};

class SkoarpuscleFloat : public Skoarpuscle {
public:
    SkoarpuscleFloat(double);
};

class SkoarpuscleNoat : public Skoarpuscle {
public:
    SkoarpuscleNoat(string *);
};

class SkoarpuscleChoard : public Skoarpuscle {
public:
    SkoarpuscleChoard(string *);
};

class SkoarpuscleString : public Skoarpuscle {
public:
    SkoarpuscleString(string *);
};

class SkoarpuscleSymbol : public Skoarpuscle {
public:
    SkoarpuscleSymbol(string *);
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
public:
	SkoarpuscleBars(SkoarToke *);
};

class SkoarpuscleVolta : public Skoarpuscle {
public:
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
};

class SkoarpuscleOctaveShift : public Skoarpuscle {
public:
	SkoarpuscleOctaveShift(SkoarToke *);
};

class SkoarpuscleBooleanOp : public Skoarpuscle {
public:
	SkoarpuscleBooleanOp(SkoarToke *);
};

class SkoarpuscleVoice : public Skoarpuscle {
public:
	SkoarpuscleVoice(SkoarToke *);
};

class SkoarpuscleSegno : public Skoarpuscle {
public:
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
    SkoarpuscleMathOp(SkoarToke *);
};

class SkoarpuscleList : public Skoarpuscle {
public:
	SkoarpuscleList();

	SkoarpuscleList(list<Skoarpuscle*>* listy);
	list<Skoarpuscle *> *list() {
		return val.List;
	}
};

class SkoarpuscleArgsSpec : public SkoarpuscleList {
public:
	SkoarpuscleArgsSpec();
	SkoarpuscleArgsSpec(SkoarNoad *);
};

class SkoarpuscleListSep : public Skoarpuscle {
public:
	SkoarpuscleListSep();

	void on_enter(SkoarMinstrel *m);
};

class SkoarpuscleListEnd : public Skoarpuscle {
public:
	SkoarpuscleListEnd();
	void on_enter(SkoarMinstrel *m);
};


class SkoarpuscleSkoarpion : public Skoarpuscle {
public:
	SkoarpuscleSkoarpion(Skoarpion *);
	SkoarpuscleSkoarpion(Skoarpion *, SkoarNoad *);

	void on_enter(SkoarMinstrel *m);
};

class SkoarpuscleProjection : public Skoarpuscle {
public:
	SkoarpuscleProjection(SkoarProjection *);
};

class SkoarpuscleDeref : public Skoarpuscle {
public:
	SkoarpuscleDeref();
	SkoarpuscleDeref(string *msg_name, Skoarpuscle *);

	Skoarpuscle *lookup(SkoarMinstrel* minstrel);
};

class SkoarpuscleConditional : public Skoarpuscle {
public:
	SkoarpuscleConditional();
	SkoarpuscleConditional(SkoarNoad *);
};

class SkoarpuscleBoolean : public Skoarpuscle {
public:
	SkoarpuscleBoolean();
	SkoarpuscleBoolean(SkoarNoad *);

};

class SkoarpuscleLoop : public Skoarpuscle {
public:
	SkoarpuscleLoop();
	SkoarpuscleLoop(SkoarNoad *);

	Skoarpuscle *lookup(SkoarMinstrel* minstrel);
};

class SkoarpuscleGoto : public Skoarpuscle {
public:
	SkoarpuscleGoto();
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
	SkoarpuscleMsg();
	SkoarpuscleMsg(string*, SkoarpuscleArgs *);
};

