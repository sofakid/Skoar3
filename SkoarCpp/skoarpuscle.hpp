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

#include "exception.hpp"

#define SKOARPUSCLE(x) Skoarpuscle::wrap<decltype(x)>(x)

class Skoarpuscle {
public:
    Poco::DynamicAny val;
    
    Skoarpuscle() :
        val(nullptr),
        impressionable(true),
        noatworthy(false),
        county(false) {
    }
 
    ~Skoarpuscle() {
    }

    virtual void on_enter(SkoarMinstrelPtr) {};

	virtual bool isNoatworthy() { return noatworthy; }
    bool isCounty() { return county; }

    virtual bool asCount() {
        throw SkoarpuscleException(L"asCount() called on noncounty skoarpuscle.");
    }

	virtual void *Skoarpuscle::asNoat() {
        throw SkoarpuscleException(L"asNoat() called on incompatible skoarpuscle.");
	}

	virtual SkoarpusclePtr skoar_msg(SkoarpuscleMsg* msg, SkoarMinstrelPtr minstrel) {
        throw SkoarpuscleException(L"skoar_msg() called on incompatible skoarpuscle.");
	}
	
    virtual Poco::DynamicAny Skoarpuscle::flatten(SkoarMinstrelPtr m) {
        return val;
    }
   
	virtual SkoarString Skoarpuscle::asString() {
		return SkoarString(L"Skoarpuscle");
	}

    virtual bool canBeDivisor() {
        return false;
    }

protected:
    bool noatworthy;
    bool county;
    bool impressionable;
};

class SkoarpuscleUnknown : public Skoarpuscle {
public:
	SkoarpuscleUnknown();
};

// Cats show up in unexpected places.
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
	void *asNoat() override;
    void on_enter(SkoarMinstrelPtr) override;
};

class SkoarpuscleInt : public Skoarpuscle {
public:
	SkoarpuscleInt(SkoarInt v);
	void *asNoat() override;
    void on_enter(SkoarMinstrelPtr) override;
};

class SkoarpuscleFloat : public Skoarpuscle {
public:
    SkoarpuscleFloat(SkoarFloat);
	void *asNoat() override;
    void on_enter(SkoarMinstrelPtr) override;
};

class SkoarpuscleNoat : public Skoarpuscle {
public:
    SkoarpuscleNoat(SkoarString&);
	void *asNoat() override;
    void on_enter(SkoarMinstrelPtr) override;
};

class SkoarpuscleChoard : public Skoarpuscle {
public:
    SkoarpuscleChoard(SkoarString&);
	void *asNoat() override;
    void on_enter(SkoarMinstrelPtr) override;
};

class SkoarpuscleString : public Skoarpuscle {
public:
    SkoarpuscleString(SkoarString);
    void on_enter(SkoarMinstrelPtr) override;
    SkoarpusclePtr skoar_msg(SkoarpuscleMsg *msg, SkoarMinstrelPtr minstrel) override;
};

class SkoarpuscleSymbol : public Skoarpuscle {
public:
    SkoarpuscleSymbol(SkoarString);
    void on_enter(SkoarMinstrelPtr) override;
    SkoarpusclePtr skoar_msg(SkoarpuscleMsg *msg, SkoarMinstrelPtr minstrel) override;
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
    void on_enter(SkoarMinstrelPtr) override;
};

class SkoarpuscleBars : public Skoarpuscle {
	bool pre_repeat;
	bool post_repeat;
public:
    SkoarNoadPtr noad;
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

class SkoarpuscleMsgNameWithArgs : public Skoarpuscle {
public:
    SkoarpuscleMsgNameWithArgs(SkoarString);
};

class SkoarpuscleMathOp : public Skoarpuscle {
public:
	function<void(SkoarMinstrelPtr m, SkoarpusclePtr , SkoarpusclePtr )> f;

    SkoarpuscleMathOp(SkoarToke *);
	void calculate(SkoarMinstrelPtr m, SkoarpusclePtr a, SkoarpusclePtr b);
};

class SkoarpuscleList : public Skoarpuscle {
public:
    bool noaty;
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
    SkoarpusclePtr args; // is actually shared_ptr<SkoarpuscleArgs> args;

	SkoarpuscleDeref(SkoarString, SkoarpusclePtr);

	SkoarpusclePtr lookup(SkoarMinstrelPtr);
    
    Poco::DynamicAny flatten(SkoarMinstrelPtr m) override;

    void on_enter(SkoarMinstrelPtr) override;
    void on_exit(SkoarMinstrelPtr);
    void do_deref(SkoarMinstrelPtr);
    SkoarpusclePtr skoar_msg(SkoarpuscleMsg *msg, SkoarMinstrelPtr minstrel) override;


};

class SkoarpuscleConditional : public Skoarpuscle {
public:
    list<tuple<SkoarpionPtr, SkoarpionPtr, SkoarpionPtr>> ifs;

	SkoarpuscleConditional(Skoar*, SkoarNoadPtr);
    void on_enter(SkoarMinstrelPtr) override;

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

	SkoarpusclePtr foreach(SkoarpusclePtr listy);
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
    void on_enter(SkoarMinstrelPtr) override;
    void on_deref_exit(SkoarMinstrelPtr);
};

class SkoarpuscleLoopMsg : public Skoarpuscle {
public:
	SkoarpuscleLoopMsg();
	SkoarpuscleLoopMsg(SkoarpusclePtr);
};

class SkoarpuscleMsg : public Skoarpuscle {
public:
    shared_ptr<SkoarpuscleArgs> args;
    SkoarpusclePtr dest;

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
    SkoarpusclePair(SkoarpusclePtr, SkoarpusclePtr);
};

class SkoarpuscleExpr : public Skoarpuscle {
public:
    SkoarpusclePtr result;
    SkoarpuscleExpr(SkoarNoadPtr);
};

