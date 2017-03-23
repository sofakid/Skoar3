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
#include "exception.hpp"

class Skoarpuscle {
public:
    
    Skoarpuscle() :
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

	virtual void* asNoat() {
        throw SkoarpuscleException(L"asNoat() called on incompatible skoarpuscle.");
	}

	virtual SkoarpusclePtr skoar_msg(SkoarpuscleMsg* msg, SkoarMinstrelPtr minstrel) {
        throw SkoarpuscleException(L"skoar_msg() called on incompatible skoarpuscle.");
	}
	
    //virtual Poco::DynamicAny flatten(SkoarMinstrelPtr m) {
    //    return val;
    //}
   
	virtual void asString(wostream &out) {
		out << L"Skoarpuscle";
	}

    virtual bool canBeDivisor() {
        return false;
    }

    friend std::wostream & operator<<(wostream &out, Skoarpuscle &x) {
        x.asString(out);
        return out;
    }
    
protected:
    bool noatworthy;
    bool county;
    bool impressionable;
};

class SkoarpuscleUnknown : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleUnknown"; }
    SkoarpuscleUnknown();
};

// Cats show up in unexpected places.
class SkoarpuscleCat : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleCat" << " :: =^.^=" ; }
	SkoarpuscleCat();
    SkoarpuscleCat(nullptr_t);

    void on_enter(SkoarMinstrelPtr) override;
};

class SkoarpuscleTrue : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleTrue" << " :: true" ; }

	SkoarpuscleTrue();
    SkoarpuscleTrue(bool);

    void on_enter(SkoarMinstrelPtr) override;
};

class SkoarpuscleFalse : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleFalse" << " :: false" ; }

	SkoarpuscleFalse();
    SkoarpuscleFalse(bool);
    void on_enter(SkoarMinstrelPtr) override;
};

class SkoarpuscleFreq : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleFreq" << " :: " << val; }

    const SkoarFloat val;
    SkoarpuscleFreq(SkoarString);
    SkoarpuscleFreq(SkoarFloat);
    SkoarpuscleFreq(SkoarInt);

	void *asNoat() override;
    void on_enter(SkoarMinstrelPtr) override;
};

class SkoarpuscleInt : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleInt" << " :: " << val; }

    const SkoarInt val;
	SkoarpuscleInt(SkoarInt v);
	void *asNoat() override;
    void on_enter(SkoarMinstrelPtr) override;
};

class SkoarpuscleFloat : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleFloat" << " :: " << val; }

    const SkoarFloat val;
    SkoarpuscleFloat(SkoarFloat);
	void *asNoat() override;
    void on_enter(SkoarMinstrelPtr) override;
};

class SkoarpuscleNoat : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleNoat" << " :: " << val; }
    const SkoarInt val;

    SkoarpuscleNoat(SkoarString&);
	void *asNoat() override;
    void on_enter(SkoarMinstrelPtr) override;
};

class SkoarpuscleChoard : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleChoard" << " :: " << val; }
    const SkoarInt val;

    SkoarpuscleChoard(SkoarString&);
	void *asNoat() override;
    void on_enter(SkoarMinstrelPtr) override;
};

class SkoarpuscleString : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleString" << " :: " << val; }
    const SkoarString val;

    SkoarpuscleString(SkoarString);
    void on_enter(SkoarMinstrelPtr) override;
    SkoarpusclePtr skoar_msg(SkoarpuscleMsg *msg, SkoarMinstrelPtr minstrel) override;
};

class SkoarpuscleSymbol : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleSymbol" << " :: " << val; }
    const SkoarString val;

    SkoarpuscleSymbol(SkoarString);
    void on_enter(SkoarMinstrelPtr) override;
    SkoarpusclePtr skoar_msg(SkoarpuscleMsg *msg, SkoarMinstrelPtr minstrel) override;
};

class SkoarpuscleSymbolName : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleSymbolName" << " :: " << val; }
    const SkoarString val;

    SkoarpuscleSymbolName(SkoarString);
};

class SkoarpuscleSymbolColon : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleSymbolColon" << " :: " << val; }
    const SkoarString val;

    SkoarpuscleSymbolColon(SkoarString);
};

class SkoarpuscleTimes : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleTimes" << " :: " ; }
    void on_enter(SkoarMinstrelPtr) override;
};

class SkoarpuscleBars : public Skoarpuscle {
	bool pre_repeat;
	bool post_repeat;
public:
    void asString(wostream &out) override { out << "SkoarpuscleBars" << " :: " ; }
    const SkoarString val;
    SkoarNoadPtr noad;
	SkoarpuscleBars(SkoarToke *);
    void on_enter(SkoarMinstrelPtr m) override;
};

class SkoarpuscleCarrots : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleCarrots" << " :: " << val; }
    const SkoarInt val;

	SkoarpuscleCarrots(SkoarToke *);
};

class SkoarpuscleTuplet : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleTuplet" << " :: " << val; }
    const SkoarInt val;
	SkoarpuscleTuplet(SkoarToke *);
};

class SkoarpuscleDynamic : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleDynamic" << " :: " << val; }
    const SkoarInt val;

	SkoarpuscleDynamic(SkoarToke *);

	SkoarFloat amp();
};

class SkoarpuscleOctaveShift : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleOctaveShift" << " :: " << val; }
    const SkoarInt val;
	SkoarpuscleOctaveShift(SkoarToke *);
    void on_enter(SkoarMinstrelPtr) override;
};

class SkoarpuscleBooleanOp : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleBooleanOp" << " :: " ; }
    //function<bool(Poco::DynamicAny, Poco::DynamicAny)> f;

	SkoarpuscleBooleanOp(SkoarNoadPtr, SkoarToke *);
	bool compare(SkoarpusclePtr a, SkoarpusclePtr b, SkoarMinstrelPtr m);
    void on_enter(SkoarMinstrelPtr) override;
};

class SkoarpuscleVoice : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleVoice" << " :: " << val; }
    const SkoarString val;

	SkoarpuscleVoice(SkoarToke *);
};

class SkoarpuscleSegno : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleSegno" << " :: " ; }
    SkoarNoadPtr noad;

	SkoarpuscleSegno(SkoarNoadPtr, SkoarToke *);
};

class SkoarpuscleFine : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleFine" << " :: " ; }
    SkoarpuscleFine();
};

class SkoarpuscleMsgName : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleMsgName" << " :: " << val; }
    const SkoarString val;
    SkoarpuscleMsgName(SkoarString);
};

class SkoarpuscleMsgNameWithArgs : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleMsgNameWithArgs" << " :: " << val; }
    const SkoarString val;
    SkoarpuscleMsgNameWithArgs(SkoarString);
    void on_enter(SkoarMinstrelPtr) override;
};

class SkoarpuscleMathOp : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleMathOp" << " :: " << val; }
    const SkoarString val;

	function<void(SkoarMinstrelPtr m, SkoarpusclePtr , SkoarpusclePtr )> f;

    SkoarpuscleMathOp(SkoarToke *);
	void calculate(SkoarMinstrelPtr m, SkoarpusclePtr a, SkoarpusclePtr b);
};

class SkoarpuscleList : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleList" << " :: " ; }
    const ListOfSkoarpusclesPtr val;

    bool noaty;
	SkoarpuscleList();

	SkoarpuscleList(ListOfSkoarpusclesPtr listy);
	
    bool isNoatworthy() override;
	void *asNoat() override;
	SkoarpusclePtr skoar_msg(SkoarpuscleMsg *msg, SkoarMinstrelPtr minstrel) override;
    void on_enter(SkoarMinstrelPtr) override;

    shared_ptr<SkoarpuscleList> mul(SkoarMinstrelPtr, SkoarpusclePtr);
    shared_ptr<SkoarpuscleList> div(SkoarMinstrelPtr, SkoarpusclePtr);
    shared_ptr<SkoarpuscleList> divBy(SkoarMinstrelPtr, SkoarpusclePtr);
    SkoarInt size();
    //Poco::DynamicAny flatten(SkoarMinstrelPtr m) override;


};

class SkoarpuscleListSep : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleListSep" << " :: " ; }
    void on_enter(SkoarMinstrelPtr) override;
};

class SkoarpuscleListEnd : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleListEnd" << " :: " ; }
    SkoarpuscleListEnd();
    void on_enter(SkoarMinstrelPtr) override;
};

class SkoarpuscleDeref : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleDeref" << " :: " << val; }
    const SkoarString val;

	list<SkoarString> msg_arr;
    SkoarpusclePtr args; // is actually shared_ptr<SkoarpuscleArgs> args;

	SkoarpuscleDeref(SkoarString, SkoarpusclePtr);

	SkoarpusclePtr lookup(SkoarMinstrelPtr);
    
    //Poco::DynamicAny flatten(SkoarMinstrelPtr m) override;

    void on_enter(SkoarMinstrelPtr) override;
    void on_exit(SkoarMinstrelPtr);
    void do_deref(SkoarMinstrelPtr);
    SkoarpusclePtr skoar_msg(SkoarpuscleMsg *msg, SkoarMinstrelPtr minstrel) override;


};

class SkoarpuscleConditional : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleConditional" << " :: " ; }
    list<tuple<SkoarpionPtr, SkoarpionPtr, SkoarpionPtr>> ifs;

	SkoarpuscleConditional(Skoar*, SkoarNoadPtr);
    void on_enter(SkoarMinstrelPtr) override;

};

class SkoarpuscleBoolean : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleBoolean" << " :: " ; }
    SkoarpuscleBoolean(SkoarNoadPtr);

    void on_enter(SkoarMinstrelPtr) override;

	bool evaluate(SkoarMinstrelPtr, SkoarpusclePtr, SkoarpusclePtr);
private:
    SkoarpusclePtr op;

};

class SkoarpuscleLoop : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleLoop" << " :: " ; }

	SkoarpionPtr condition;
    SkoarpionPtr body;
	SkoarpusclePtr each;

	SkoarpuscleLoop(Skoar*, SkoarNoadPtr);

	void foreach(SkoarpusclePtr listy);
    void on_enter(SkoarMinstrelPtr) override;
};

class SkoarpuscleLoopMsg : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleLoopMsg" << " :: " ; }
    const SkoarpusclePtr val;

    SkoarpuscleLoopMsg(SkoarpusclePtr);
};

class SkoarpuscleGoto : public Skoarpuscle {
public:
	void asString(wostream &out) override { out << "SkoarpuscleGoto" << " :: "; }
    SkoarString nav_cmd;
	bool al_fine;

	SkoarpuscleGoto(SkoarNoadPtr);
};

class SkoarpuscleArgs : public SkoarpuscleList {
public:
    void asString(wostream &out) override { out << "SkoarpuscleArgs" << " :: " ; }
    SkoarpusclePtr pairs;

    void on_enter(SkoarMinstrelPtr) override;
    void on_deref_exit(SkoarMinstrelPtr);
};


class SkoarpuscleMsg : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleMsg" << " :: " << val; }
    const SkoarString val;

    shared_ptr<SkoarpuscleArgs> args;
    SkoarpusclePtr dest;

	SkoarpuscleMsg(SkoarString v, shared_ptr<SkoarpuscleArgs> a);
    void on_enter(SkoarMinstrelPtr) override;
    SkoarpusclePtr skoar_msg(SkoarpuscleMsg *msg, SkoarMinstrelPtr minstrel) override;

	list<SkoarString> get_msg_arr(SkoarMinstrelPtr);
    list<SkoarString> get_args_from_prototype(SkoarMinstrelPtr);
    
};

class SkoarpuscleExprEnd : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleExprEnd" << " :: " ; }
    void on_enter(SkoarMinstrelPtr) override;
};

class SkoarpuscleHashLevel : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleHashLevel" << " :: " << val; }
    const SkoarFloat val;

    SkoarpuscleHashLevel(SkoarString);
};

class SkoarpusclePair : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpusclePair" << " :: " << val.first; }
    const pair<SkoarString, SkoarpusclePtr> val;

    SkoarpusclePair(SkoarString, SkoarpusclePtr);
    void assign(SkoarMinstrelPtr);
};

class SkoarpuscleExpr : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleExpr" << " :: " ; }
    SkoarpusclePtr result;
    SkoarpuscleExpr(SkoarNoadPtr);
};
