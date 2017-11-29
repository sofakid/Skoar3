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

#include "skoarpuscle_types.hpp"

#include "koar.hpp"

class Skoarpuscle {
public:

    const ESkoarpuscle::Kind kind;

    Skoarpuscle() :
        impressionable(true),
        noatworthy(false),
        county(false),
        kind(ESkoarpuscle::Kind::Other) {
    }

    Skoarpuscle(ESkoarpuscle::Kind kind) :
        impressionable(true),
        noatworthy(false),
        county(false),
        kind(kind) {
    }

    virtual ~Skoarpuscle() {
    }

    virtual void clear () {};

    virtual void on_enter(SkoarMinstrelPtr) {};

    virtual bool isNoatworthy() { return noatworthy; }
    bool isCounty() { return county; }

    virtual SkoarInt asCount() {
        throw SkoarpuscleException(L"asCount() called on noncounty skoarpuscle.");
    }

    virtual void* asNoat() {
        throw SkoarpuscleException(L"asNoat() called on incompatible skoarpuscle.");
    }

    virtual SkoarpusclePtr skoar_msg(SkoarpuscleMsg* /*msg*/, SkoarMinstrelPtr /*minstrel*/) {
        throw SkoarpuscleException(L"skoar_msg() called on incompatible skoarpuscle.");
    }

    //virtual Poco::DynamicAny flatten(SkoarMinstrelPtr m) {
    //    return val;
    //}

    virtual void asString(wostream &out) {
        out << L"Skoarpuscle";
    }

    SkoarString asString() {
        wostringstream out;
        asString(out);
        return out.str();
    }

    virtual void typeAsString(wostream &out) {
        asString(out);
    }

    SkoarString typeAsString() {
        wostringstream out;
        typeAsString(out);
        return out.str();
    }

    virtual void valAsString(wostream &) {
    }

    SkoarString valAsString() {
        wostringstream out;
        valAsString(out);
        return out.str();
    }


    virtual bool canBeDivisor() {
        return false;
    }

    friend std::wostream & operator<<(wostream &out, Skoarpuscle &x) {
        x.asString(out);
        return out;
    }

    bool isImpressionable() {
        return impressionable;
    }

    virtual SkoarpusclePtr duplicate () { return nullptr; };

protected:
    bool impressionable;
    bool noatworthy;
    bool county;
};

class SkoarpuscleUnknown : public Skoarpuscle {
public:
    SkoarpuscleUnknown();
    ~SkoarpuscleUnknown() override;

    void asString(wostream &out) override;
    void typeAsString(wostream &out) override;
    void valAsString(wostream &out) override;
};

// Cats show up in unexpected places.
class SkoarpuscleCat : public Skoarpuscle {
public:
    SkoarpuscleCat();
    SkoarpuscleCat(nullptr_t);
    ~SkoarpuscleCat() override;
    void asString(wostream &out) override;
    void typeAsString(wostream &out) override;
    void valAsString(wostream &out) override;

    void on_enter(SkoarMinstrelPtr) override;
    SkoarpusclePtr duplicate () override;

};

class SkoarpuscleTrue : public Skoarpuscle {
public:

    SkoarpuscleTrue();
    SkoarpuscleTrue(bool);
    ~SkoarpuscleTrue() override;

    void asString(wostream &out) override;
    void typeAsString(wostream &out) override;
    void valAsString(wostream &out) override;

    void on_enter(SkoarMinstrelPtr) override;
    SkoarpusclePtr duplicate () override;

};

class SkoarpuscleFalse : public Skoarpuscle {
public:

    SkoarpuscleFalse();
    SkoarpuscleFalse(bool);
    ~SkoarpuscleFalse() override;

    void asString(wostream &out) override;
    void typeAsString(wostream &out) override;
    void valAsString(wostream &out) override;

    void on_enter(SkoarMinstrelPtr) override;
    SkoarpusclePtr duplicate () override;

};

class SkoarpuscleFreq : public Skoarpuscle {
public:
    const SkoarFloat val;
    SkoarpuscleFreq(SkoarString);
    SkoarpuscleFreq(SkoarFloat);
    SkoarpuscleFreq(SkoarInt);
    ~SkoarpuscleFreq() override;

    void asString(wostream &out) override;
    void typeAsString(wostream &out) override;
    void valAsString(wostream &out) override;

    void *asNoat() override;
    void on_enter(SkoarMinstrelPtr) override;
    SkoarpusclePtr duplicate () override;

};

class SkoarpuscleInt : public Skoarpuscle {
public:

    const SkoarInt val;
    SkoarpuscleInt(SkoarInt v);
    ~SkoarpuscleInt() override;

    void asString(wostream &out) override;
    void typeAsString(wostream &out) override;
    void valAsString(wostream &out) override;

    void *asNoat() override;
    SkoarInt asCount() override;

    void on_enter(SkoarMinstrelPtr) override;
    SkoarpusclePtr duplicate () override;

};

class SkoarpuscleFloat : public Skoarpuscle {
public:

    const SkoarFloat val;
    SkoarpuscleFloat(SkoarFloat);
    ~SkoarpuscleFloat() override;
    void asString(wostream &out) override;
    void typeAsString(wostream &out) override;
    void valAsString(wostream &out) override;

    void *asNoat() override;
    void on_enter(SkoarMinstrelPtr) override;
    SkoarpusclePtr duplicate () override;

};


class SkoarpuscleString : public Skoarpuscle {
public:
    const SkoarString val;

    SkoarpuscleString(SkoarString);
    ~SkoarpuscleString() override;
    void asString(wostream &out) override;
    void typeAsString(wostream &out) override;
    void valAsString(wostream &out) override;

    void on_enter(SkoarMinstrelPtr) override;
    SkoarpusclePtr skoar_msg(SkoarpuscleMsg *msg, SkoarMinstrelPtr minstrel) override;
    SkoarpusclePtr duplicate () override;
};

class SkoarpuscleSymbol : public Skoarpuscle {
public:
    const SkoarString val;

    SkoarpuscleSymbol(SkoarString);
    ~SkoarpuscleSymbol() override;
    void asString(wostream &out) override;
    void typeAsString(wostream &out) override;
    void valAsString(wostream &out) override;

    void on_enter(SkoarMinstrelPtr) override;
    SkoarpusclePtr skoar_msg(SkoarpuscleMsg *msg, SkoarMinstrelPtr minstrel) override;
    SkoarpusclePtr duplicate () override;
};

class SkoarpuscleSymbolColon : public Skoarpuscle {
public:
    const SkoarString val;

    SkoarpuscleSymbolColon(SkoarString);
    ~SkoarpuscleSymbolColon() override;
    void asString(wostream &out) override;
    void typeAsString(wostream &out) override;
    void valAsString(wostream &out) override;
    SkoarpusclePtr duplicate () override;
};


class SkoarpuscleSymbolName : public Skoarpuscle
{
public:
    const SkoarString val;

    SkoarpuscleSymbolName (SkoarString);
    ~SkoarpuscleSymbolName () override;
    void asString (wostream &out) override;
    void typeAsString (wostream &out) override;
    void valAsString (wostream &out) override;
    SkoarpusclePtr duplicate () override;

};

class SkoarpuscleTimes : public Skoarpuscle {
public:
    const size_t& offs;

    SkoarpuscleTimes(SkoarNoadPtr);
    ~SkoarpuscleTimes() override;
    void asString(wostream &out) override;
    void typeAsString(wostream &out) override;

    void on_enter(SkoarMinstrelPtr) override;

};

class SkoarpuscleBars : public Skoarpuscle {

public:
    const bool pre_repeat;
    const bool post_repeat;
    const size_t offs;

    const SkoarNoadAddress& address;
    const SkoarString val;
    SkoarNoadPtr noad;
    SkoarpuscleBars(SkoarToke*, SkoarNoadPtr);
    ~SkoarpuscleBars() override;
    void asString(wostream &out) override;
    void typeAsString(wostream &out) override;
    void valAsString(wostream &out) override;

    void on_enter(SkoarMinstrelPtr m) override;

};

class SkoarpuscleCarrots : public Skoarpuscle {
public:
    const SkoarInt val;

    SkoarpuscleCarrots(SkoarToke *);
    ~SkoarpuscleCarrots() override;
    void asString(wostream &out) override;
    void typeAsString(wostream &out) override;
    void valAsString(wostream &out) override;

};

class SkoarpuscleTuplet : public Skoarpuscle {
public:
    const SkoarInt val;
    SkoarpuscleTuplet(SkoarToke *);
    ~SkoarpuscleTuplet() override;
    void asString(wostream &out) override;
    void typeAsString(wostream &out) override;
    void valAsString(wostream &out) override;

};

class SkoarpuscleDynamic : public Skoarpuscle {
public:
    const SkoarInt val;

    SkoarpuscleDynamic(SkoarToke *);
    ~SkoarpuscleDynamic() override;

    void asString(wostream &out) override;
    void typeAsString(wostream &out) override;
    void valAsString(wostream &out) override;

    SkoarFloat amp();
    void on_enter (SkoarMinstrelPtr m) override;
};

class SkoarpuscleOctaveShift : public Skoarpuscle {
public:
    const SkoarInt val;
    SkoarpuscleOctaveShift(SkoarToke *);
    ~SkoarpuscleOctaveShift() override;

    void asString(wostream &out) override;
    void typeAsString(wostream &out) override;
    void valAsString(wostream &out) override;

    void on_enter(SkoarMinstrelPtr) override;
};

class SkoarpuscleBooleanOp : public Skoarpuscle {
public:
    void asString(wostream &out) override;
    void typeAsString(wostream &out) override;
    void valAsString(wostream &out) override;
    function<SkoarpusclePtr(SkoarMinstrelPtr m, SkoarpusclePtr, SkoarpusclePtr)> f;

    SkoarpuscleBooleanOp(SkoarNoadPtr, SkoarToke *);
    ~SkoarpuscleBooleanOp() override;

    bool compare(SkoarpusclePtr a, SkoarpusclePtr b, SkoarMinstrelPtr m);
    void on_enter(SkoarMinstrelPtr) override;
};

class SkoarpuscleVoice : public Skoarpuscle {
public:
    const SkoarString val;

    SkoarpuscleVoice(SkoarToke *);
    ~SkoarpuscleVoice() override;

    void asString(wostream &out) override;
    void typeAsString(wostream &out) override;
    void valAsString(wostream &out) override;

};

class SkoarpuscleCoda : public Skoarpuscle
{
public:
    size_t offs;
    SkoarString label;

    SkoarpuscleCoda (SkoarNoadPtr, SkoarToke *);
    ~SkoarpuscleCoda () override;

    void asString (wostream &out) override;
    void typeAsString (wostream &out) override;
    void valAsString (wostream &out) override;

    void on_enter (SkoarMinstrelPtr m) override;

};

class SkoarpuscleMsgName : public Skoarpuscle {
public:
    const SkoarString val;
    SkoarpuscleMsgName(SkoarString);
    ~SkoarpuscleMsgName() override;

    void asString(wostream &out) override;
    void typeAsString(wostream &out) override;
    void valAsString(wostream &out) override;

};

class SkoarpuscleMsgNameWithArgs : public Skoarpuscle {
public:
    const SkoarString val;
    SkoarpuscleMsgNameWithArgs(SkoarString);
    ~SkoarpuscleMsgNameWithArgs() override;

    void asString(wostream &out) override;
    void typeAsString(wostream &out) override;
    void valAsString(wostream &out) override;

    void on_enter(SkoarMinstrelPtr) override;
};

class SkoarpuscleMathOp : public Skoarpuscle {
public:
    const SkoarString val;

    function<void(SkoarMinstrelPtr m, SkoarpusclePtr, SkoarpusclePtr)> f;

    SkoarpuscleMathOp(SkoarToke *);
    ~SkoarpuscleMathOp() override;

    void asString(wostream &out) override;
    void typeAsString(wostream &out) override;
    void valAsString(wostream &out) override;

    void calculate(SkoarMinstrelPtr m, SkoarpusclePtr a, SkoarpusclePtr b);
};

class SkoarpuscleList : public Skoarpuscle {
public:
    const ListOfSkoarpusclesPtr val;

    bool noaty;
    SkoarpuscleList();
    SkoarpuscleList(ListOfSkoarpusclesPtr listy);
    ~SkoarpuscleList() ;
    void clear () override;

    void asString(wostream &out) override;
    void typeAsString(wostream &out) override;
    void valAsString(wostream &out) override;

    bool isNoatworthy() override;
    void *asNoat() override;
    SkoarpusclePtr skoar_msg(SkoarpuscleMsg *msg, SkoarMinstrelPtr minstrel) override;
    void on_enter(SkoarMinstrelPtr) override;
    SkoarpusclePtr duplicate () override;


    shared_ptr<SkoarpuscleList> mul(SkoarMinstrelPtr, SkoarpusclePtr);
    shared_ptr<SkoarpuscleList> div(SkoarMinstrelPtr, SkoarpusclePtr);
    shared_ptr<SkoarpuscleList> divBy(SkoarMinstrelPtr, SkoarpusclePtr);
    SkoarInt size();

};

class SkoarpuscleListSep : public Skoarpuscle {
public:

    SkoarpuscleListSep();
    ~SkoarpuscleListSep() override;

    void asString(wostream &out) override;
    void typeAsString(wostream &out) override;
    void valAsString(wostream &out) override;
    void on_enter(SkoarMinstrelPtr) override;
};

class SkoarpuscleListEnd : public Skoarpuscle {
public:
    SkoarpuscleListEnd();
    ~SkoarpuscleListEnd() override;

    void asString(wostream &out) override;
    void typeAsString(wostream &out) override;
    void valAsString(wostream &out) override;

    void on_enter(SkoarMinstrelPtr) override;
};

class SkoarpuscleDeref : public Skoarpuscle {
public:
    const SkoarString val;

    list<SkoarString> msg_arr;
    SkoarpusclePtr args; // is actually shared_ptr<SkoarpuscleArgs> args;

    SkoarpuscleDeref(SkoarString, SkoarpusclePtr);
    ~SkoarpuscleDeref() override;

    void asString(wostream &out) override;
    void typeAsString(wostream &out) override;
    void valAsString(wostream &out) override;

    SkoarpusclePtr lookup(SkoarMinstrelPtr);

    //Poco::DynamicAny flatten(SkoarMinstrelPtr m) override;

    void on_enter(SkoarMinstrelPtr) override;
    void on_exit(SkoarMinstrelPtr);
    void do_deref(SkoarMinstrelPtr);
    SkoarpusclePtr skoar_msg(SkoarpuscleMsg *msg, SkoarMinstrelPtr minstrel) override;


};

class SkoarpuscleConditional : public Skoarpuscle {
public:
    static const SkoarString id (bool reset = false);

    list<tuple<SkoarpionPtr, SkoarpionPtr, SkoarpionPtr>> ifs;

    SkoarpuscleConditional(Skoar*, SkoarNoadPtr);
    ~SkoarpuscleConditional() override;

    void asString(wostream &out) override;
    void typeAsString(wostream &out) override;
    void valAsString(wostream &out) override;

    void on_enter(SkoarMinstrelPtr) override;

};

class SkoarpuscleBoolean : public Skoarpuscle {
public:
    SkoarpuscleBoolean(SkoarNoadPtr);
    ~SkoarpuscleBoolean() override;

    void asString(wostream &out) override;
    void typeAsString(wostream &out) override;
    void valAsString(wostream &out) override;

    void on_enter(SkoarMinstrelPtr) override;

    bool evaluate(SkoarMinstrelPtr, SkoarpusclePtr, SkoarpusclePtr);
private:
    SkoarpusclePtr op;

};

class SkoarpuscleLoop : public Skoarpuscle {
public:

    static const SkoarString id (bool reset = false);

    SkoarpionPtr condition;
    SkoarpionPtr body;
    SkoarpusclePtr each;

    SkoarpuscleLoop(Skoar*, SkoarNoadPtr);
    ~SkoarpuscleLoop() override;

    void asString(wostream &out) override;
    void typeAsString(wostream &out) override;
    void valAsString(wostream &out) override;

    void foreach(SkoarpusclePtr listy);
    void on_enter(SkoarMinstrelPtr) override;
};

class SkoarpuscleLoopMsg : public Skoarpuscle {
public:
    const SkoarpusclePtr val;

    SkoarpuscleLoopMsg(SkoarpusclePtr);
    ~SkoarpuscleLoopMsg() override;

    void asString(wostream &out) override;
    void typeAsString(wostream &out) override;
    void valAsString(wostream &out) override;

};

class SkoarpuscleGoto : public Skoarpuscle {
public:
    SkoarNav::ECode nav_cmd;
    SkoarString label;

    SkoarpuscleGoto(SkoarNoadPtr);
    ~SkoarpuscleGoto() override;

    void asString(wostream &out) override;
    void typeAsString(wostream &out) override;
    void valAsString(wostream &out) override;

    void on_enter (SkoarMinstrelPtr m);

};

class SkoarpuscleArgs : public SkoarpuscleList {
public:
    //SkoarpusclePtr pairs;

    SkoarpuscleArgs();
    ~SkoarpuscleArgs() override;

    void asString(wostream &out) override;
    void typeAsString(wostream &out) override;
    void valAsString(wostream &out) override;

    void on_enter(SkoarMinstrelPtr) override;
    void on_deref_exit(SkoarMinstrelPtr);
};


class SkoarpuscleMsg : public Skoarpuscle {
public:
    const SkoarString val;

    shared_ptr<SkoarpuscleArgs> args;
    SkoarpusclePtr dest;

    SkoarpuscleMsg(SkoarString v, shared_ptr<SkoarpuscleArgs> a);
    ~SkoarpuscleMsg() override;
    void clear () override;

    void asString(wostream &out) override;
    void typeAsString(wostream &out) override;
    void valAsString(wostream &out) override;

    void on_enter(SkoarMinstrelPtr) override;
    SkoarpusclePtr skoar_msg(SkoarpuscleMsg *msg, SkoarMinstrelPtr minstrel) override;

    list<SkoarString> get_msg_arr(SkoarMinstrelPtr);
    list<SkoarString> get_args_from_prototype(SkoarMinstrelPtr);

};

class SkoarpuscleExprEnd : public Skoarpuscle {
public:

    SkoarpuscleExprEnd();
    ~SkoarpuscleExprEnd() override;

    void asString(wostream &out) override;
    void typeAsString(wostream &out) override;
    void valAsString(wostream &out) override;
    void on_enter (SkoarMinstrelPtr) override;
};

class SkoarpuscleHashLevel : public Skoarpuscle {
public:
    const SkoarFloat val;

    SkoarpuscleHashLevel(SkoarString);
    SkoarpuscleHashLevel (const SkoarFloat);

    ~SkoarpuscleHashLevel() override;

    void asString(wostream &out) override;
    void typeAsString(wostream &out) override;
    void valAsString(wostream &out) override;

    void on_enter(SkoarMinstrelPtr) override;
    SkoarpusclePtr duplicate () override;


};

class SkoarpusclePair : public Skoarpuscle {
public:
    const pair<SkoarString, SkoarpusclePtr> val;

    SkoarpusclePair(SkoarString, SkoarpusclePtr);
    ~SkoarpusclePair() override;

    void clear () override;

    void asString(wostream &out) override;
    void typeAsString(wostream &out) override;
    void valAsString(wostream &out) override;

    SkoarpusclePtr assign(SkoarMinstrelPtr);
};

class SkoarpuscleExpr : public Skoarpuscle {
public:
    SkoarNoadPtr val;
    SkoarpusclePtr result;
    SkoarpuscleExpr(SkoarNoadPtr);
    ~SkoarpuscleExpr() override;
    void clear () override;

    void asString(wostream &out) override;
    void typeAsString(wostream &out) override;
    void valAsString(wostream &out) override;

    SkoarpusclePtr flatten(SkoarMinstrelPtr m);

};
