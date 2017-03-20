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

#include "Poco/DynamicAny.h"

#define SKOARPUSCLE(x) Skoarpuscle::wrap<decltype(x)>(x)

class Skoarpuscle {
public:

    Poco::DynamicAny val;
    
	Skoarpuscle();
    ~Skoarpuscle() {
    }

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
	
    virtual SkoarInt Skoarpuscle::flatten(SkoarMinstrel *m) { return 0; }
    /*{
        std::any* v = &val;
        SkoarInt* vp = std::any_cast<SkoarInt>(v);
        return (vp == nullptr) ? static_cast<SkoarInt>(0) : *vp;
	}*/
	
	virtual SkoarString Skoarpuscle::asString() {
		return SkoarString(L"Skoarpuscle");
	}


};

class SkoarpuscleUnknown : public Skoarpuscle {
public:
	SkoarpuscleUnknown();
};

class SkoarpuscleCat : public Skoarpuscle {
public:
	SkoarpuscleCat();
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
    SkoarpuscleFreq(SkoarString);
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
    SkoarpuscleNoat(SkoarString&);
	bool isNoatworthy() override;
	void *asNoat() override;
};

class SkoarpuscleChoard : public Skoarpuscle {
public:
    SkoarpuscleChoard(SkoarString&);
	bool isNoatworthy() override;
	void *asNoat() override;
};

class SkoarpuscleString : public Skoarpuscle {
public:
    SkoarpuscleString(SkoarString);

};

class SkoarpuscleSymbol : public Skoarpuscle {
public:
    SkoarpuscleSymbol(SkoarString);
	Skoarpuscle *skoar_msg(SkoarpuscleMsg *msg, SkoarMinstrel *minstrel) override;

};

class SkoarpuscleSymbolName : public Skoarpuscle {
public:
    SkoarpuscleSymbolName(SkoarString);

};

class SkoarpuscleSymbolColon : public Skoarpuscle {
public:
    SkoarpuscleSymbolColon(SkoarString);

};

class SkoarpuscleTimes : public Skoarpuscle {
public:
    SkoarpuscleTimes();

};

class SkoarpuscleBars : public Skoarpuscle {
	SkoarNoadPtr noad;
	bool pre_repeat;
	bool post_repeat;
public:
	SkoarpuscleBars(SkoarToke *);
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

	SkoarpuscleBooleanOp(SkoarNoadPtr, SkoarToke *);
	bool compare(Skoarpuscle *a, Skoarpuscle *b, SkoarMinstrel *m);
};

class SkoarpuscleVoice : public Skoarpuscle {
public:
	SkoarpuscleVoice(SkoarToke *);
};

class SkoarpuscleSegno : public Skoarpuscle {
public:
	SkoarNoadPtr noad;

	SkoarpuscleSegno(SkoarNoadPtr, SkoarToke *);
};

class SkoarpuscleFine : public Skoarpuscle {
public:
    SkoarpuscleFine();
};

class SkoarpuscleMsgName : public Skoarpuscle {
public:
    SkoarpuscleMsgName(SkoarString);

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

	SkoarpuscleList(ListOfSkoarpusclesPtr listy);
	
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

class SkoarpuscleArgSpec : public SkoarpuscleList {
public:
	SkoarpuscleArgSpec();
	SkoarpuscleArgSpec(SkoarNoadPtr);
};


class SkoarpuscleDeref : public Skoarpuscle {
public:
	list<SkoarString> msg_arr;
	shared_ptr<SkoarpuscleArgs> args;

	SkoarpuscleDeref();
	SkoarpuscleDeref(SkoarString msg_name, shared_ptr<SkoarpuscleArgs>);

	SkoarpusclePtr lookup(SkoarMinstrel* minstrel);
};

class SkoarpuscleConditional : public Skoarpuscle {
public:
	ListOfSkoarpusclesPtr ifs;

	SkoarpuscleConditional();
	SkoarpuscleConditional(Skoar *, SkoarNoadPtr);

	
};

class SkoarpuscleBoolean : public Skoarpuscle {
public:
	SkoarpuscleBoolean();
	SkoarpuscleBoolean(SkoarNoadPtr);

	bool evaluate(SkoarMinstrel *m);
	

};

class SkoarpuscleLoop : public Skoarpuscle {
public:

	SkoarpuscleConditional *condition;
	Skoarpuscle *body;
	list<Skoarpuscle*> *each;

	SkoarpuscleLoop();
	SkoarpuscleLoop(Skoar *, SkoarNoadPtr);

	Skoarpuscle *lookup(SkoarMinstrel* minstrel);

	SkoarpuscleLoop *foreach(SkoarpuscleList *listy);
};

class SkoarpuscleGoto : public Skoarpuscle {
public:
	SkoarString nav_cmd;
	bool al_fine;

	SkoarpuscleGoto(SkoarNoadPtr);
};

class SkoarpuscleArgs : public Skoarpuscle {
public:
	SkoarpuscleArgs();
};

class SkoarpuscleLoopMsg : public Skoarpuscle {
public:
	SkoarpuscleLoopMsg();
	SkoarpuscleLoopMsg(SkoarString);
};

class SkoarpuscleMsg : public Skoarpuscle {
public:
    shared_ptr<SkoarpuscleArgs> args;

	SkoarpuscleMsg();
	SkoarpuscleMsg(SkoarString v, shared_ptr<SkoarpuscleArgs> a);
	//void *get_msg_arr(SkoarMinstrel *m);
};


class SkoarpuscleExprEnd : public Skoarpuscle {
public:
	SkoarpuscleExprEnd();
};

class SkoarpuscleHashLevel : public Skoarpuscle {
public:
    SkoarpuscleHashLevel(SkoarString);
};

class SkoarpusclePair : public Skoarpuscle {
public:
    SkoarpusclePair(SkoarString, Skoarpuscle*);
};

class SkoarpuscleExpr : public Skoarpuscle {
public:
    SkoarpuscleExpr(SkoarNoadPtr);
};

