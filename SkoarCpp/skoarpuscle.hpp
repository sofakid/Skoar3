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
#include "memories.hpp"

class Skoarpuscle {
public:
    
    Skoarpuscle() :
        impressionable(true),
        noatworthy(false),
        county(false) {
    }
 
    virtual ~Skoarpuscle() {
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
    ~SkoarpuscleUnknown() override;

};

// Cats show up in unexpected places.
class SkoarpuscleCat : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleCat" << " :: =^.^=" ; }
	SkoarpuscleCat();
    SkoarpuscleCat(nullptr_t);
    ~SkoarpuscleCat() override;

    void on_enter(SkoarMinstrelPtr) override;
};

class SkoarpuscleTrue : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleTrue" << " :: true" ; }

	SkoarpuscleTrue();
    SkoarpuscleTrue(bool);
    ~SkoarpuscleTrue() override;

    void on_enter(SkoarMinstrelPtr) override;
};

class SkoarpuscleFalse : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleFalse" << " :: false" ; }

	SkoarpuscleFalse();
    SkoarpuscleFalse(bool);
    ~SkoarpuscleFalse() override;

    void on_enter(SkoarMinstrelPtr) override;
};

class SkoarpuscleFreq : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleFreq" << " :: " << val; }

    const SkoarFloat val;
    SkoarpuscleFreq(SkoarString);
    SkoarpuscleFreq(SkoarFloat);
    SkoarpuscleFreq(SkoarInt);
    ~SkoarpuscleFreq() override;

	void *asNoat() override;
    void on_enter(SkoarMinstrelPtr) override;
};

class SkoarpuscleInt : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleInt" << " :: " << val; }

    const SkoarInt val;
	SkoarpuscleInt(SkoarInt v);
    ~SkoarpuscleInt() override;

	void *asNoat() override;
    void on_enter(SkoarMinstrelPtr) override;
};

class SkoarpuscleFloat : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleFloat" << " :: " << val; }

    const SkoarFloat val;
    SkoarpuscleFloat(SkoarFloat);
    ~SkoarpuscleFloat() override;

	void *asNoat() override;
    void on_enter(SkoarMinstrelPtr) override;
};

class SkoarpuscleNoat : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleNoat" << " :: " << val; }
    const SkoarInt val;

    SkoarpuscleNoat(SkoarString&);
    ~SkoarpuscleNoat() override;

	void *asNoat() override;
    void on_enter(SkoarMinstrelPtr) override;
};

class SkoarpuscleChoard : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleChoard" << " :: " << val; }
    const SkoarInt val;

    SkoarpuscleChoard(SkoarString&);
    ~SkoarpuscleChoard() override;

	void *asNoat() override;
    void on_enter(SkoarMinstrelPtr) override;
};

class SkoarpuscleString : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleString" << " :: " << val; }
    const SkoarString val;

    SkoarpuscleString(SkoarString);
    ~SkoarpuscleString() override;

    void on_enter(SkoarMinstrelPtr) override;
    SkoarpusclePtr skoar_msg(SkoarpuscleMsg *msg, SkoarMinstrelPtr minstrel) override;
};

class SkoarpuscleSymbol : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleSymbol" << " :: " << val; }
    const SkoarString val;

    SkoarpuscleSymbol(SkoarString);
    ~SkoarpuscleSymbol() override;

    void on_enter(SkoarMinstrelPtr) override;
    SkoarpusclePtr skoar_msg(SkoarpuscleMsg *msg, SkoarMinstrelPtr minstrel) override;
};

class SkoarpuscleSymbolName : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleSymbolName" << " :: " << val; }
    const SkoarString val;

    SkoarpuscleSymbolName(SkoarString);
    ~SkoarpuscleSymbolName() override;

};

class SkoarpuscleSymbolColon : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleSymbolColon" << " :: " << val; }
    const SkoarString val;

    SkoarpuscleSymbolColon(SkoarString);
    ~SkoarpuscleSymbolColon() override;

};

class SkoarpuscleTimes : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleTimes" << " :: " ; }
    
    SkoarpuscleTimes();
    ~SkoarpuscleTimes() override;

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
    ~SkoarpuscleBars() override;

    void on_enter(SkoarMinstrelPtr m) override;
};

class SkoarpuscleCarrots : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleCarrots" << " :: " << val; }
    const SkoarInt val;

	SkoarpuscleCarrots(SkoarToke *);
    ~SkoarpuscleCarrots() override;

};

class SkoarpuscleTuplet : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleTuplet" << " :: " << val; }
    const SkoarInt val;
	SkoarpuscleTuplet(SkoarToke *);
    ~SkoarpuscleTuplet() override;

};

class SkoarpuscleDynamic : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleDynamic" << " :: " << val; }
    const SkoarInt val;

	SkoarpuscleDynamic(SkoarToke *);
    ~SkoarpuscleDynamic() override;


	SkoarFloat amp();
};

class SkoarpuscleOctaveShift : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleOctaveShift" << " :: " << val; }
    const SkoarInt val;
	SkoarpuscleOctaveShift(SkoarToke *);
    ~SkoarpuscleOctaveShift() override;

    void on_enter(SkoarMinstrelPtr) override;
};

class SkoarpuscleBooleanOp : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleBooleanOp" << " :: " ; }
    //function<bool(Poco::DynamicAny, Poco::DynamicAny)> f;

	SkoarpuscleBooleanOp(SkoarNoadPtr, SkoarToke *);
    ~SkoarpuscleBooleanOp() override;

	bool compare(SkoarpusclePtr a, SkoarpusclePtr b, SkoarMinstrelPtr m);
    void on_enter(SkoarMinstrelPtr) override;
};

class SkoarpuscleVoice : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleVoice" << " :: " << val; }
    const SkoarString val;

	SkoarpuscleVoice(SkoarToke *);
    ~SkoarpuscleVoice() override;

};

class SkoarpuscleSegno : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleSegno" << " :: " ; }
    SkoarNoadPtr noad;

	SkoarpuscleSegno(SkoarNoadPtr, SkoarToke *);
    ~SkoarpuscleSegno() override;

};

class SkoarpuscleFine : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleFine" << " :: " ; }
    SkoarpuscleFine();
    ~SkoarpuscleFine() override;

};

class SkoarpuscleMsgName : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleMsgName" << " :: " << val; }
    const SkoarString val;
    SkoarpuscleMsgName(SkoarString);
    ~SkoarpuscleMsgName() override;

};

class SkoarpuscleMsgNameWithArgs : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleMsgNameWithArgs" << " :: " << val; }
    const SkoarString val;
    SkoarpuscleMsgNameWithArgs(SkoarString);
    ~SkoarpuscleMsgNameWithArgs() override;

    void on_enter(SkoarMinstrelPtr) override;
};

class SkoarpuscleMathOp : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleMathOp" << " :: " << val; }
    const SkoarString val;

	function<void(SkoarMinstrelPtr m, SkoarpusclePtr , SkoarpusclePtr )> f;

    SkoarpuscleMathOp(SkoarToke *);
    ~SkoarpuscleMathOp() override;

	void calculate(SkoarMinstrelPtr m, SkoarpusclePtr a, SkoarpusclePtr b);
};

class SkoarpuscleList : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleList" << " :: " ; }
    const ListOfSkoarpusclesPtr val;

    bool noaty;
    SkoarpuscleList();
	SkoarpuscleList(ListOfSkoarpusclesPtr listy);
    ~SkoarpuscleList() override;

	
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

    SkoarpuscleListSep();
    ~SkoarpuscleListSep() override;

    void asString(wostream &out) override { out << "SkoarpuscleListSep" << " :: " ; }
    void on_enter(SkoarMinstrelPtr) override;
};

class SkoarpuscleListEnd : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleListEnd" << " :: " ; }
    SkoarpuscleListEnd();
    ~SkoarpuscleListEnd() override;

    void on_enter(SkoarMinstrelPtr) override;
};

class SkoarpuscleDeref : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleDeref" << " :: " << val; }
    const SkoarString val;

	list<SkoarString> msg_arr;
    SkoarpusclePtr args; // is actually shared_ptr<SkoarpuscleArgs> args;

	SkoarpuscleDeref(SkoarString, SkoarpusclePtr);
    ~SkoarpuscleDeref() override;


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
    ~SkoarpuscleConditional() override;

    void on_enter(SkoarMinstrelPtr) override;

};

class SkoarpuscleBoolean : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleBoolean" << " :: " ; }
    SkoarpuscleBoolean(SkoarNoadPtr);
    ~SkoarpuscleBoolean() override;

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
    ~SkoarpuscleLoop() override;


	void foreach(SkoarpusclePtr listy);
    void on_enter(SkoarMinstrelPtr) override;
};

class SkoarpuscleLoopMsg : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleLoopMsg" << " :: " ; }
    const SkoarpusclePtr val;

    SkoarpuscleLoopMsg(SkoarpusclePtr);
    ~SkoarpuscleLoopMsg() override;

};

class SkoarpuscleGoto : public Skoarpuscle {
public:
	void asString(wostream &out) override { out << "SkoarpuscleGoto" << " :: "; }
    SkoarString nav_cmd;
	bool al_fine;

	SkoarpuscleGoto(SkoarNoadPtr);
    ~SkoarpuscleGoto() override;

};

class SkoarpuscleArgs : public SkoarpuscleList {
public:
    void asString(wostream &out) override { out << "SkoarpuscleArgs" << " :: " ; }
    SkoarpusclePtr pairs;
    
    SkoarpuscleArgs();
    ~SkoarpuscleArgs() override;

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
    ~SkoarpuscleMsg() override;

    void on_enter(SkoarMinstrelPtr) override;
    SkoarpusclePtr skoar_msg(SkoarpuscleMsg *msg, SkoarMinstrelPtr minstrel) override;

	list<SkoarString> get_msg_arr(SkoarMinstrelPtr);
    list<SkoarString> get_args_from_prototype(SkoarMinstrelPtr);
    
};

class SkoarpuscleExprEnd : public Skoarpuscle {
public:
    
    SkoarpuscleExprEnd();
    ~SkoarpuscleExprEnd() override;

    void asString(wostream &out) override { out << "SkoarpuscleExprEnd" << " :: " ; }
    void on_enter(SkoarMinstrelPtr) override;
};

class SkoarpuscleHashLevel : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleHashLevel" << " :: " << val; }
    const SkoarFloat val;

    SkoarpuscleHashLevel(SkoarString);
    ~SkoarpuscleHashLevel() override;
    
};

class SkoarpusclePair : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpusclePair" << " :: " << val.first; }
    const pair<SkoarString, SkoarpusclePtr> val;

    SkoarpusclePair(SkoarString, SkoarpusclePtr);
    ~SkoarpusclePair() override;

    void assign(SkoarMinstrelPtr);
};

class SkoarpuscleExpr : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleExpr" << " :: " ; }
    SkoarpusclePtr result;
    SkoarpuscleExpr(SkoarNoadPtr);
    ~SkoarpuscleExpr() override;

};
