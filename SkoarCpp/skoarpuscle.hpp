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

    bool impressionable;
    
	Skoarpuscle();
    ~Skoarpuscle() {
    }

    virtual void on_enter(SkoarMinstrelPtr) {
    };

	virtual bool isNoatworthy() {
		return false;
	}
	virtual void *Skoarpuscle::asNoat() {
		return nullptr;
	}

	virtual SkoarpusclePtr skoar_msg(SkoarpuscleMsg *msg, SkoarMinstrelPtr minstrel) {
		return nullptr;
	}
	
    virtual SkoarInt Skoarpuscle::flatten(SkoarMinstrelPtr m) { return 0; }
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
    void on_enter(SkoarMinstrelPtr) override;
};

class SkoarpuscleTrue : public Skoarpuscle {
public:
	SkoarpuscleTrue();
    void on_enter(SkoarMinstrelPtr) override;

};

class SkoarpuscleFalse : public Skoarpuscle {
public:
	SkoarpuscleFalse();
    void on_enter(SkoarMinstrelPtr) override;
};

class SkoarpuscleFreq : public Skoarpuscle {
public:
    SkoarpuscleFreq(SkoarString);
	bool isNoatworthy() override;
	void *asNoat() override;
    void on_enter(SkoarMinstrelPtr) override;
};

class SkoarpuscleInt : public Skoarpuscle {
public:
	SkoarpuscleInt(SkoarInt v);
	bool isNoatworthy() override; 
	void *asNoat() override;
    void on_enter(SkoarMinstrelPtr) override;
};

class SkoarpuscleFloat : public Skoarpuscle {
public:
    SkoarpuscleFloat(SkoarFloat);
	bool isNoatworthy() override;
	void *asNoat() override;
    void on_enter(SkoarMinstrelPtr) override;
};

class SkoarpuscleNoat : public Skoarpuscle {
public:
    SkoarpuscleNoat(SkoarString&);
	bool isNoatworthy() override;
	void *asNoat() override;
    void on_enter(SkoarMinstrelPtr) override;
};

class SkoarpuscleChoard : public Skoarpuscle {
public:
    SkoarpuscleChoard(SkoarString&);
	bool isNoatworthy() override;
	void *asNoat() override;
    void on_enter(SkoarMinstrelPtr) override;
};

class SkoarpuscleString : public Skoarpuscle {
public:
    SkoarpuscleString(SkoarString);
    void on_enter(SkoarMinstrelPtr) override;
};

class SkoarpuscleSymbol : public Skoarpuscle {
public:
    SkoarpuscleSymbol(SkoarString);
	SkoarpusclePtr skoar_msg(SkoarpuscleMsg *msg, SkoarMinstrelPtr minstrel) override;
    void on_enter(SkoarMinstrelPtr) override;
};

class SkoarpuscleSymbolName : public Skoarpuscle {
public:
    SkoarpuscleSymbolName(SkoarString);
    void on_enter(SkoarMinstrelPtr) override;
};

class SkoarpuscleSymbolColon : public Skoarpuscle {
public:
    SkoarpuscleSymbolColon(SkoarString);
    void on_enter(SkoarMinstrelPtr) override;
};

class SkoarpuscleTimes : public Skoarpuscle {
public:
    SkoarpuscleTimes();
    void on_enter(SkoarMinstrelPtr) override;
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
	function<bool(Poco::DynamicAny, Poco::DynamicAny)> f;

	SkoarpuscleBooleanOp(SkoarNoadPtr, SkoarToke *);
	bool compare(SkoarpusclePtr a, SkoarpusclePtr b, SkoarMinstrelPtr m);
    void on_enter(SkoarMinstrelPtr) override;
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
	function<void(SkoarMinstrelPtr m, SkoarpusclePtr , SkoarpusclePtr )> f;

    SkoarpuscleMathOp(SkoarToke *);
	void calculate(SkoarMinstrelPtr m, SkoarpusclePtr a, SkoarpusclePtr b);
};

class SkoarpuscleList : public Skoarpuscle {
public:
	SkoarpuscleList();

	SkoarpuscleList(ListOfSkoarpusclesPtr listy);
	
	bool isNoatworthy() override;
	void *asNoat() override;
	SkoarpusclePtr skoar_msg(SkoarpuscleMsg *msg, SkoarMinstrelPtr minstrel) override;
    void on_enter(SkoarMinstrelPtr) override;

};

class SkoarpuscleListSep : public Skoarpuscle {
public:
	SkoarpuscleListSep();
    void on_enter(SkoarMinstrelPtr) override;
};

class SkoarpuscleListEnd : public Skoarpuscle {
public:
	SkoarpuscleListEnd();
    void on_enter(SkoarMinstrelPtr) override;
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
	SkoarpuscleDeref(SkoarString, shared_ptr<SkoarpuscleArgs>);

	SkoarpusclePtr lookup(SkoarMinstrelPtr);
};

class SkoarpuscleConditional : public Skoarpuscle {
public:
	ListOfSkoarpusclesPtr ifs;

	SkoarpuscleConditional();
	SkoarpuscleConditional(Skoar*, SkoarNoadPtr);

	
};

class SkoarpuscleBoolean : public Skoarpuscle {
public:
	SkoarpuscleBoolean();
	SkoarpuscleBoolean(SkoarNoadPtr);

    void on_enter(SkoarMinstrelPtr) override;

	bool evaluate(SkoarMinstrelPtr, SkoarpusclePtr, SkoarpusclePtr);
private:
    SkoarpusclePtr op;

};

class SkoarpuscleLoop : public Skoarpuscle {
public:

	SkoarpuscleConditional *condition;
	SkoarpusclePtr body;
	ListOfSkoarpusclesPtr each;

	SkoarpuscleLoop();
	SkoarpuscleLoop(Skoar*, SkoarNoadPtr);

	SkoarpusclePtr lookup(SkoarMinstrel* minstrel);

	SkoarpusclePtr foreach(ListOfSkoarpusclesPtr listy);
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
	//void *get_msg_arr(SkoarMinstrelPtr m);
};


class SkoarpuscleExprEnd : public Skoarpuscle {
public:
	SkoarpuscleExprEnd();
    void on_enter(SkoarMinstrelPtr) override;
};

class SkoarpuscleHashLevel : public Skoarpuscle {
public:
    SkoarpuscleHashLevel(SkoarString);
    void on_enter(SkoarMinstrelPtr) override;
};

class SkoarpusclePair : public Skoarpuscle {
public:
    SkoarpusclePair(SkoarString, Skoarpuscle*);
};

class SkoarpuscleExpr : public Skoarpuscle {
public:
    SkoarpuscleExpr(SkoarNoadPtr);
};

