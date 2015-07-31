#pragma once
#include "skoarcery.hpp"

#include "lex_fwd.hpp"
#include "noad_fwd.hpp"
#include "skoarpion_fwd.hpp"
#include "minstrel_fwd.hpp"
#include "event_fwd.hpp"

class Skoarpuscle {
public:

	function<void(SkoarMinstrel *m)> on_enter;

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