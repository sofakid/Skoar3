#include "skoarpuscle.hpp"

#include "lex.hpp"
#include "minstrel.hpp"
#include "fairy.hpp"
#include "skoar.hpp"
#include "koar.hpp"
#include "noad.hpp"
#include "skoarpion.hpp"
#include "skoarpion_skoarpuscle.hpp"
#include "make_skoarpuscle.hpp"
#include "operators.hpp"
#include "skoarpuscle_structors.h"
#include <regex>


// --- SkoarpuscleUnknown ---------------------------------------------------------
SkoarpuscleUnknown::SkoarpuscleUnknown () {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().allocSkoarpuscle (L"Unknown");
#endif
}

SkoarpuscleUnknown::~SkoarpuscleUnknown () {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().deallocSkoarpuscle (L"Unknown");
#endif
}

// --- SkoarpuscleCat ---------------------------------------------------------
SkoarpuscleCat::SkoarpuscleCat () : Skoarpuscle (ESkoarpuscle::Cat) {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().allocSkoarpuscle (L"Cat");
#endif

    impressionable = true;
}

SkoarpuscleCat::~SkoarpuscleCat () {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().deallocSkoarpuscle (L"Cat");
#endif
}

SkoarpuscleCat::SkoarpuscleCat (nullptr_t) : SkoarpuscleCat () {
}


// --- SkoarpuscleTrue ---------------------------------------------------------
SkoarpuscleTrue::SkoarpuscleTrue () : Skoarpuscle (ESkoarpuscle::True) {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().allocSkoarpuscle (L"True");
#endif
    impressionable = true;
}

SkoarpuscleTrue::~SkoarpuscleTrue () {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().deallocSkoarpuscle (L"True");
#endif
}

SkoarpuscleTrue::SkoarpuscleTrue (bool /*x*/) : SkoarpuscleTrue () {
    // assert x == true
}

// --- SkoarpuscleFalse ---------------------------------------------------------
SkoarpuscleFalse::SkoarpuscleFalse () :
    Skoarpuscle (ESkoarpuscle::False) {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().allocSkoarpuscle (L"False");
#endif
    impressionable = true;
}

SkoarpuscleFalse::~SkoarpuscleFalse () {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().deallocSkoarpuscle (L"False");
#endif
}
SkoarpuscleFalse::SkoarpuscleFalse (bool /*x*/) : SkoarpuscleFalse () {
    // assert x == false
}

// --- SkoarpuscleInt ---------------------------------------------------------
SkoarpuscleInt::SkoarpuscleInt (SkoarInt v) :
    Skoarpuscle (ESkoarpuscle::Int),
    val (v) {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().allocSkoarpuscle (L"Int");
#endif
    noatworthy = true;
    impressionable = true;
    county = true;
}

SkoarInt SkoarpuscleInt::asCount () {
    return val;
}

SkoarpuscleInt::~SkoarpuscleInt () {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().deallocSkoarpuscle (L"Int");
#endif
}

// --- SkoarpuscleFloat ---------------------------------------------------------
SkoarpuscleFloat::SkoarpuscleFloat (SkoarFloat v) :
    Skoarpuscle (ESkoarpuscle::Float),
    val (v) {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().allocSkoarpuscle (L"Float");
#endif
    noatworthy = true;
    impressionable = true;
}

SkoarpuscleFloat::~SkoarpuscleFloat () {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().deallocSkoarpuscle (L"Float");
#endif
}

// --- SkoarpuscleFreq ---------------------------------------------------------
SkoarpuscleFreq::SkoarpuscleFreq (SkoarFloat v) :
    Skoarpuscle (ESkoarpuscle::Freq),
    val (v)
{
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().allocSkoarpuscle (L"Freq");
#endif
    noatworthy = true;
    impressionable = true;
}

SkoarpuscleFreq::~SkoarpuscleFreq () {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().deallocSkoarpuscle (L"Freq");
#endif
}

SkoarpuscleFreq::SkoarpuscleFreq (SkoarString lexeme) :
    SkoarpuscleFreq (stod (lexeme.substr (0, lexeme.length () - 2))) {
}

SkoarpuscleFreq::SkoarpuscleFreq (SkoarInt v) :
    SkoarpuscleFreq (static_cast<SkoarFloat>(v)) {
}

// --- SkoarpuscleNoat ---------------------------------------------------------
SkoarpuscleNoat::SkoarpuscleNoat (SkoarString&) :
    Skoarpuscle (ESkoarpuscle::Noat),
    val (0) {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().allocSkoarpuscle (L"Noat");
#endif
    noatworthy = true;
    impressionable = true;
}

SkoarpuscleNoat::~SkoarpuscleNoat () {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().deallocSkoarpuscle (L"Noat");
#endif
}

// --- SkoarpuscleChoard ---------------------------------------------------------
SkoarpuscleChoard::SkoarpuscleChoard (SkoarString&) :
    Skoarpuscle (ESkoarpuscle::Choard),
    val (0) {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().allocSkoarpuscle (L"Choard");
#endif
    noatworthy = true;
    impressionable = true;
}

SkoarpuscleChoard::~SkoarpuscleChoard () {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().deallocSkoarpuscle (L"Choard");
#endif
}

// --- SkoarpuscleString ---------------------------------------------------------
SkoarpuscleString::SkoarpuscleString (SkoarString s) :
    Skoarpuscle (ESkoarpuscle::String),
    val (s) {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().allocSkoarpuscle (L"String");
#endif
    impressionable = true;
}

SkoarpuscleString::~SkoarpuscleString () {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().deallocSkoarpuscle (L"String");
#endif
}


// --- SkoarpuscleSymbol ---------------------------------------------------------
SkoarpuscleSymbol::SkoarpuscleSymbol (SkoarString s) : val (s) {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().allocSkoarpuscle (L"Symbol");
#endif
    impressionable = true;
}

SkoarpuscleSymbol::~SkoarpuscleSymbol () {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().deallocSkoarpuscle (L"Symbol");
#endif
}

// --- SkoarpuscleSymbolColon ---------------------------------------------------------

inline SkoarString clean_symbol_colon (SkoarString &lex) {
    // lexeme was matched by: [a-zA-Z0-9_][a-zA-Z0-9_]*[ \t]*:(?![:|}])
    // ... so we'll remove anything that's not [a-zA-Z0-9_]
    std::wregex expr (L"([^a-zA-Z0-9_]+)");
    return std::regex_replace (lex, expr, L"");
}

SkoarpuscleSymbolColon::SkoarpuscleSymbolColon (SkoarString lex) :
    Skoarpuscle (ESkoarpuscle::SymbolColon),
    val (clean_symbol_colon (lex)) {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().allocSkoarpuscle (L"SymbolColon");
#endif
    impressionable = true;
}


SkoarpuscleSymbolColon::~SkoarpuscleSymbolColon () {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().deallocSkoarpuscle (L"SymbolColon");
#endif
}


// --- SkoarpuscleSymbolName ---------------------------------------------------------

SkoarpuscleSymbolName::SkoarpuscleSymbolName (SkoarString lex) :
    Skoarpuscle (ESkoarpuscle::SymbolName),
    val (clean_symbol_colon (lex)) {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().allocSkoarpuscle (L"SymbolName");
#endif
    impressionable = true;
}

SkoarpuscleSymbolName::~SkoarpuscleSymbolName () {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().deallocSkoarpuscle (L"SymbolName");
#endif
}

// --- SkoarpuscleDeref ---------------------------------------------------------
SkoarpuscleDeref::SkoarpuscleDeref (SkoarString v, SkoarpusclePtr a) : val (v) {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().allocSkoarpuscle (L"Deref");
#endif
    args = a; // is actually shared_ptr<SkoarpuscleArgs>
}


SkoarpuscleDeref::~SkoarpuscleDeref () {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().deallocSkoarpuscle (L"Deref");
#endif
}

// --- SkoarpuscleMathOp ---------------------------------------------------------
SkoarpuscleMathOp::SkoarpuscleMathOp (SkoarToke *toke) : val (toke->lexeme) {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().allocSkoarpuscle (L"MathOp");
#endif
    auto s = toke->lexeme;

    if (s == L"+")
    {
        f = [](SkoarMinstrelPtr m, SkoarpusclePtr a, SkoarpusclePtr b) {
            SkoarOps::getInstance ()->add (m, a, b);
        };
    }
    else if (s == L"*")
    {
        f = [](SkoarMinstrelPtr m, SkoarpusclePtr a, SkoarpusclePtr b) {
            // SkoarOps::getInstance()->multiply(m, a, b);
        };
    }
    else if (s == L"/")
    {
        f = [](SkoarMinstrelPtr m, SkoarpusclePtr a, SkoarpusclePtr b) {
            // SkoarOps::getInstance()->divide(m, a, b);
        };
    }
    else if (s == L"-")
    {
        f = [](SkoarMinstrelPtr m, SkoarpusclePtr a, SkoarpusclePtr b) {
            // SkoarOps::getInstance()->sub(m, a, b);
        };
    }
}


SkoarpuscleMathOp::~SkoarpuscleMathOp () {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().deallocSkoarpuscle (L"MathOp");
#endif
}

// --- SkoarpuscleBooleanOp ---------------------------------------------------------
SkoarpuscleBooleanOp::SkoarpuscleBooleanOp (SkoarNoadPtr /*noad*/, SkoarToke* /*toke*/) {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().allocSkoarpuscle (L"BooleanOp");
#endif
    /*
    // todo: use the ops table.
    //#define InsaneMagic [=](Poco::DynamicAny a, Poco::DynamicAny b)
    #define InsaneMagic [=](int a, int b)

    if (val == SkoarString(L"=="))
    f = InsaneMagic { return a == b; };

    else if (val == SkoarString(L"!="))
    f = InsaneMagic { return a != b; };

    else if (val == SkoarString(L"!="))
    f = InsaneMagic { return a == b; };

    else if (val == SkoarString(L"<="))
    f = InsaneMagic { return a <= b; };

    else if (val == SkoarString(L">="))
    f = InsaneMagic { return a >= b; };

    else if (val == SkoarString(L">"))
    f = InsaneMagic { return a > b; };

    else if (val == SkoarString(L"<"))
    f = InsaneMagic { return a < b; };

    else if (val == SkoarString(L"and"))
    f = InsaneMagic { return a && b; };

    else if (val == SkoarString(L"or"))
    f = InsaneMagic { return a || b; };

    else if (val == SkoarString(L"xor"))
    f = InsaneMagic{ return !a != !b; };

    #undef InsaneMagic
    */
}

SkoarpuscleBooleanOp::~SkoarpuscleBooleanOp () {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().deallocSkoarpuscle (L"BooleanOp");
#endif
}

// --- SkoarpuscleBoolean ---------------------------------------------------------
SkoarpuscleBoolean::SkoarpuscleBoolean (SkoarNoadPtr noad) {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().allocSkoarpuscle (L"Boolean");
#endif
    op = noad->children.front ()->next_skoarpuscle ();
}


SkoarpuscleBoolean::~SkoarpuscleBoolean () {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().deallocSkoarpuscle (L"Boolean");
#endif
}

// --- SkoarpuscleConditional ---------------------------------------------------------
SkoarpuscleConditional::SkoarpuscleConditional (Skoar *skoar, SkoarNoadPtr noad) {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().allocSkoarpuscle (L"Conditional");
#endif

    list<ESkoarNoad::Kind> desires = { ESkoarNoad::cond_if };

    for (auto x : SkoarNoad::collect (noad, desires))
    {
        SkoarpionPtr condition;
        SkoarpionPtr if_body;
        SkoarpionPtr else_body;

        auto boolean_expr (SkoarNoad::NewArtificial (L"cond_cond"));

        auto child (x->children.cbegin ());
        auto condition_skoarpuscle ((*child)->next_skoarpuscle ());

        boolean_expr->add_noad (*child);

        condition = Skoarpion::NewFromSubtree (skoar, boolean_expr);

        ++child;                   // children[1]
        auto if_noad (*(++child)); // children[2]

        if_body = Skoarpion::NewFromSubtree (skoar, if_noad);

        if (x->children.size () > 4)
        {
            ++child;                     // children[3]
            auto else_noad (*(++child)); // children[4]
            else_body = Skoarpion::NewFromSubtree (skoar, else_noad);
        }
        else
            else_body = nullptr;

        ifs.push_back (make_tuple (condition, if_body, else_body));

        x->children.clear ();
    }

    noad->children.clear ();
}

SkoarpuscleConditional::~SkoarpuscleConditional () {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().deallocSkoarpuscle (L"Conditional");
#endif
    for (auto x : ifs)
    {
        SkoarpionPtr z;
        z = get<0> (x);
        if (z != nullptr)
            z->clear ();

        z = get<1> (x);
        if (z != nullptr)
            z->clear ();

        z = get<2> (x);
        if (z != nullptr)
            z->clear ();

    }
    ifs.clear ();
}

// --- SkoarpuscleTimes ---------------------------------------------------------
SkoarpuscleTimes::SkoarpuscleTimes (SkoarNoadPtr noad) :
    offs (noad->offs)
{
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().allocSkoarpuscle (L"Times");
#endif
}

SkoarpuscleTimes::~SkoarpuscleTimes () {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().deallocSkoarpuscle (L"Times");
#endif
}

// --- SkoarpuscleLoop ---------------------------------------------------------
SkoarpuscleLoop::SkoarpuscleLoop (Skoar *skoar, SkoarNoadPtr noad) {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().allocSkoarpuscle (L"Loop");
#endif
    list<ESkoarNoad::Kind> desires_cond = { ESkoarNoad::loop_condition };
    for (auto x : SkoarNoad::collect (noad, desires_cond))
        if (x->children.size () > 0)
            condition = Skoarpion::NewFromSubtree (skoar, x);

    list<ESkoarNoad::Kind> desires_body = { ESkoarNoad::loop_body };
    for (auto x : SkoarNoad::collect (noad, desires_body))
        body = Skoarpion::NewFromSubtree (skoar, x);

    each = nullptr;
}

SkoarpuscleLoop::~SkoarpuscleLoop () {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().deallocSkoarpuscle (L"Loop");
#endif
}

// --- SkoarpuscleLoopMsg ---------------------------------------------------------
SkoarpuscleLoopMsg::SkoarpuscleLoopMsg (SkoarpusclePtr msg) : val (msg) {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().allocSkoarpuscle (L"LoopMsg");
#endif
}

SkoarpuscleLoopMsg::~SkoarpuscleLoopMsg () {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().deallocSkoarpuscle (L"LoopMsg");
#endif
}

// --- SkoarpuscleExprEnd ---------------------------------------------------------
SkoarpuscleExprEnd::SkoarpuscleExprEnd () {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().allocSkoarpuscle (L"ExprEnd");
#endif
}

SkoarpuscleExprEnd::~SkoarpuscleExprEnd () {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().deallocSkoarpuscle (L"ExprEnd");
#endif
}

// --- SkoarpuscleListSep ---------------------------------------------------------
SkoarpuscleListSep::SkoarpuscleListSep () {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().allocSkoarpuscle (L"ListSep");
#endif
}

SkoarpuscleListSep::~SkoarpuscleListSep () {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().deallocSkoarpuscle (L"ListSep");
#endif
}

// --- SkoarpuscleListEnd ---------------------------------------------------------
SkoarpuscleListEnd::SkoarpuscleListEnd () {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().allocSkoarpuscle (L"ListEnd");
#endif
}

SkoarpuscleListEnd::~SkoarpuscleListEnd () {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().deallocSkoarpuscle (L"ListEnd");
#endif
}

// --- SkoarpuscleList ---------------------------------------------------------
SkoarpuscleList::SkoarpuscleList () :
    SkoarpuscleList (make_shared<ListOfSkoarpuscles> ())
{}

SkoarpuscleList::SkoarpuscleList (ListOfSkoarpusclesPtr x) :
    Skoarpuscle (ESkoarpuscle::List),
    val (x)
{
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().allocSkoarpuscle (L"List");
#endif

    noaty = true;
    impressionable = true;
}

SkoarpuscleList::~SkoarpuscleList () {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().deallocSkoarpuscle (L"List");
#endif
    clear ();

}

void SkoarpuscleList::clear ()
{
    if (val != nullptr)
    {
        for (auto x : *val)
            if (x != nullptr)
                x->clear ();
        val->clear ();
    }
}

// --- SkoarpuscleArgs ---------------------------------------------------------
SkoarpuscleArgs::SkoarpuscleArgs () {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().allocSkoarpuscle (L"Args");
#endif
}

SkoarpuscleArgs::~SkoarpuscleArgs () {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().deallocSkoarpuscle (L"Args");
#endif
}

// --- SkoarpuscleMsg ---------------------------------------------------------
SkoarpuscleMsg::SkoarpuscleMsg (SkoarString v, shared_ptr<SkoarpuscleArgs> a) :
    val (v),
    args (a),
    dest (nullptr) {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().allocSkoarpuscle (L"Msg");
#endif

}

SkoarpuscleMsg::~SkoarpuscleMsg () {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().deallocSkoarpuscle (L"Msg");
    clear ();
#endif
}

void SkoarpuscleMsg::clear ()
{
    if (args != nullptr)
        args->clear ();

    if (dest != nullptr)
        dest->clear ();
}

// --- SkoarpuscleMsgName ---------------------------------------------------------
SkoarpuscleMsgName::SkoarpuscleMsgName (SkoarString s) : val (s) {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().allocSkoarpuscle (L"MsgName");
#endif
}

SkoarpuscleMsgName::~SkoarpuscleMsgName () {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().deallocSkoarpuscle (L"MsgName");
#endif
}

// --- SkoarpuscleMsgNameWithArgs ---------------------------------------------------------
SkoarpuscleMsgNameWithArgs::SkoarpuscleMsgNameWithArgs (SkoarString s) : val (s) {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().allocSkoarpuscle (L"MsgNameWithArgs");
#endif
}

SkoarpuscleMsgNameWithArgs::~SkoarpuscleMsgNameWithArgs () {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().deallocSkoarpuscle (L"MsgNameWithArgs");
#endif
}

// -----------------------------
// musical keywords skoarpuscles
// -----------------------------

// --- SkoarpuscleBars ---------------------------------------------------------
SkoarpuscleBars::SkoarpuscleBars (SkoarToke* toke, SkoarNoadPtr noad) :
    val (toke->lexeme),
    address (noad->address),
    pre_repeat (toke->lexeme.at (0) == L':'),
    post_repeat (toke->lexeme.at (toke->lexeme.length () - 1) == L':'),
    offs (toke->offs)
{
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().allocSkoarpuscle (L"Bars");
#endif
}

SkoarpuscleBars::~SkoarpuscleBars () {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().deallocSkoarpuscle (L"Bars");
#endif
}

// --- SkoarpuscleCoda ---------------------------------------------------------
SkoarpuscleCoda::SkoarpuscleCoda (SkoarNoadPtr /*noad*/, SkoarToke* toke) {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().allocSkoarpuscle (L"Coda");
#endif

    offs = toke->offs;

    wregex re (L":\\s*(.+)");
    wsmatch matches;

    label = regex_search (toke->lexeme, matches, re) ? matches.str (1) : SkoarString (L"");

}

SkoarpuscleCoda::~SkoarpuscleCoda () {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().deallocSkoarpuscle (L"Coda");
#endif
}
// --- SkoarpuscleGoto ---------------------------------------------------------
SkoarpuscleGoto::SkoarpuscleGoto (SkoarNoadPtr noad) {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().allocSkoarpuscle (L"Goto");
#endif

    auto it (noad->children.cbegin ());
    auto toke ((*it)->next_toke ());

    if (toke != nullptr)
    {
        nav_cmd = SkoarNav::CODA;

        wregex re (L":\\s*(.+)");
        wsmatch matches;

        label = regex_search (toke->lexeme, matches, re) ? matches.str (1) : SkoarString (L"");
    }
}

SkoarpuscleGoto::~SkoarpuscleGoto () {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().deallocSkoarpuscle (L"Goto");
#endif
}

// --- SkoarpuscleCarrots ---------------------------------------------------------
SkoarpuscleCarrots::SkoarpuscleCarrots (SkoarToke *toke) :
    val (toke->lexeme.length ())
{
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().allocSkoarpuscle (L"Carrots");
#endif

}

SkoarpuscleCarrots::~SkoarpuscleCarrots () {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().deallocSkoarpuscle (L"Carrots");
#endif
}

// --- SkoarpuscleTuplet ---------------------------------------------------------
SkoarpuscleTuplet::SkoarpuscleTuplet (SkoarToke *toke) :
    val (toke->lexeme.length ())
{
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().allocSkoarpuscle (L"Tuplet");
#endif

}

SkoarpuscleTuplet::~SkoarpuscleTuplet () {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().deallocSkoarpuscle (L"Tuplet");
#endif
}

// --- SkoarpuscleDynamic ---------------------------------------------------------

inline SkoarInt decode_skoar_dynamic (SkoarString &s) {
    if (s == L"ppp")
        return 1;
    if (s == L"pppiano")
        return 1;
    if (s == L"pp")
        return 2;
    if (s == L"ppiano")
        return 2;
    if (s == L"p")
        return 3;
    if (s == L"piano")
        return 3;
    if (s == L"mp")
        return 4;
    if (s == L"mpiano")
        return 4;
    if (s == L"mf")
        return 5;
    if (s == L"mforte")
        return 5;
    if (s == L"forte")
        return 6;
    if (s == L"ff")
        return 7;
    if (s == L"fforte")
        return 7;
    return 8;
}

SkoarpuscleDynamic::SkoarpuscleDynamic (SkoarToke *toke) :
    val (decode_skoar_dynamic (toke->lexeme))
{
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().allocSkoarpuscle (L"Dynamic");
#endif
}

SkoarpuscleDynamic::~SkoarpuscleDynamic () {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().deallocSkoarpuscle (L"Dynamic");
#endif
}

// --- SkoarpuscleOctaveShift ---------------------------------------------------------
inline const SkoarInt decode_skoar_octave_shift (SkoarToke *toke) {

    if (toke->kind == ESkoarToke::OctaveShift)
    {
        auto s (toke->lexeme);
        auto n (s.length () - 1);

        if (s.at (0) == L'o')
            n *= -1;

        return n;
    }
    
    return 0;
}

SkoarpuscleOctaveShift::SkoarpuscleOctaveShift (SkoarToke *toke) :
    val (decode_skoar_octave_shift (toke))
{
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().allocSkoarpuscle (L"OctaveShift");
#endif
}

SkoarpuscleOctaveShift::~SkoarpuscleOctaveShift () {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().deallocSkoarpuscle (L"Unknown");
#endif
}

// --- SkoarpuscleVoice ---------------------------------------------------------
SkoarpuscleVoice::SkoarpuscleVoice (SkoarToke *toke) :
    val (toke->lexeme.substr (1))
{
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().allocSkoarpuscle (L"Voice");
#endif
}

SkoarpuscleVoice::~SkoarpuscleVoice () {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().deallocSkoarpuscle (L"Voice");
#endif
}

// --- SkoarpuscleHashLevel ---------------------------------------------------------
inline SkoarFloat decode_skoar_hashlevel (SkoarString &lex) {
    SkoarFloat n = -2.0;
    SkoarFloat i = 0;
    for (auto c : lex)
    {
        n += 1.0;
        if (c == L'#')
            i += 1.0;
    }

    if (n <= 0.0)
        return 0.0;

    return i / n;
}

SkoarpuscleHashLevel::SkoarpuscleHashLevel (SkoarString lex) :
    SkoarpuscleHashLevel (decode_skoar_hashlevel (lex))
{
}

SkoarpuscleHashLevel::SkoarpuscleHashLevel (const SkoarFloat x) :
    val (x)
{
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().allocSkoarpuscle (L"HashLevel");
#endif

    impressionable = true;
    noatworthy = false;
}

SkoarpuscleHashLevel::~SkoarpuscleHashLevel () {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().deallocSkoarpuscle (L"HashLevel");
#endif
}

// --- SkoarpusclePair ---------------------------------------------------------
SkoarpusclePair::SkoarpusclePair (SkoarString k, SkoarpusclePtr v) :
    val (make_pair (k, v == nullptr ? make_skoarpuscle (nullptr) : v))
{
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().allocSkoarpuscle (L"Pair");
#endif
    impressionable = true;
}

SkoarpusclePair::~SkoarpusclePair () {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().deallocSkoarpuscle (L"Pair");
#endif
}

void SkoarpusclePair::clear ()
{
    if (val.second != nullptr)
        val.second->clear ();
}

// --- SkoarpuscleExpr ---------------------------------------------------------
SkoarpuscleExpr::SkoarpuscleExpr (SkoarNoadPtr noad) {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().allocSkoarpuscle (L"Expr");
#endif

    val = noad;
    result = nullptr;
}

SkoarpuscleExpr::~SkoarpuscleExpr () {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().deallocSkoarpuscle (L"Expr");
#endif
    val = nullptr;
}

void SkoarpuscleExpr::clear ()
{

    if (result != nullptr)
        result->clear ();

    if (val != nullptr)
        val->clear ();

    result = nullptr;
    val = nullptr;

}
