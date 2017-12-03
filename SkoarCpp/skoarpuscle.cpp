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


// Skoarpuscles are the closest thing we have to "types".
//
// They represent value types, as well as most things that
// can be spoken of as things, like a statement, boolean expression, etc.
//

// --- SkoarpuscleCat ---------------------------------------------------------
void SkoarpuscleCat::on_enter (SkoarMinstrelPtr m) {
    m->fairy->impress (nullptr);
}

SkoarpusclePtr SkoarpuscleCat::duplicate ()
{
    return make_skoarpuscle(nullptr);
}

// --- SkoarpuscleTrue ---------------------------------------------------------
void SkoarpuscleTrue::on_enter (SkoarMinstrelPtr m) {
    m->fairy->impress (true);
}

SkoarpusclePtr SkoarpuscleTrue::duplicate ()
{
    return make_skoarpuscle (true);
}

// --- SkoarpuscleFalse ---------------------------------------------------------

void SkoarpuscleFalse::on_enter (SkoarMinstrelPtr m) {
    m->fairy->impress (false);
}

SkoarpusclePtr SkoarpuscleFalse::duplicate ()
{
    return make_skoarpuscle (false);
}

// --- SkoarpuscleInt ---------------------------------------------------------
void SkoarpuscleInt::on_enter (SkoarMinstrelPtr m) {
    m->fairy->impress (val);
}

SkoarpusclePtr SkoarpuscleInt::duplicate ()
{
    return make_shared<SkoarpuscleInt> (val);
}

void *SkoarpuscleInt::asNoat () { return nullptr; }

// --- SkoarpuscleFloat ---------------------------------------------------------
void SkoarpuscleFloat::on_enter (SkoarMinstrelPtr m) {
    m->fairy->impress (val);
}
SkoarpusclePtr SkoarpuscleFloat::duplicate ()
{
    return make_shared<SkoarpuscleFloat> (val);
}
void *SkoarpuscleFloat::asNoat () {
    return nullptr;
}

// --- SkoarpuscleFreq ---------------------------------------------------------
void SkoarpuscleFreq::on_enter (SkoarMinstrelPtr m) {
    m->fairy->impress (duplicate());
}

SkoarpusclePtr SkoarpuscleFreq::duplicate ()
{
    return make_shared<SkoarpuscleFreq> (val);
}

void *SkoarpuscleFreq::asNoat () {
    return nullptr;
    //return new SkoarNoat_Freq(val.asFloat);
}


// --- SkoarpuscleString ---------------------------------------------------------
void SkoarpuscleString::on_enter (SkoarMinstrelPtr m) {
    m->fairy->impress (val);
}

SkoarpusclePtr SkoarpuscleString::duplicate ()
{
    return make_shared<SkoarpuscleString> (val);
}

// --- SkoarpuscleSymbol ---------------------------------------------------------
void SkoarpuscleSymbol::on_enter (SkoarMinstrelPtr m) {
    m->fairy->impress (make_shared<SkoarpuscleSymbol> (val));
}

SkoarpusclePtr SkoarpuscleSymbol::duplicate ()
{
    return  make_shared<SkoarpuscleSymbol> (val);
}

// --- SkoarpuscleSymbolColon ---------------------------------------------------------


SkoarpusclePtr SkoarpuscleSymbolColon::duplicate ()
{
    return make_shared<SkoarpuscleSymbolColon> (val);
}


SkoarpusclePtr SkoarpuscleSymbolName::duplicate ()
{
    return make_shared<SkoarpuscleSymbolName> (val);
}

// --- SkoarpuscleDeref ---------------------------------------------------------
SkoarpusclePtr SkoarpuscleDeref::lookup (SkoarMinstrelPtr minstrel) {
    return minstrel->koar->at (val);
}

//Poco::DynamicAny SkoarpuscleDeref::flatten(SkoarMinstrelPtr m) {
//    return lookup(m)->flatten(m);
//}

void SkoarpuscleDeref::on_enter (SkoarMinstrelPtr m) {
    //if (args != nullptr)
    //    skoarpuscle_ptr<SkoarpuscleArgs> (args)->on_enter (m);
}

void SkoarpuscleDeref::on_exit (SkoarMinstrelPtr m) {
    //if (args != nullptr)
    //    skoarpuscle_ptr<SkoarpuscleArgs> (args)->on_deref_exit (m);
    do_deref (m);
}

void SkoarpuscleDeref::do_deref (SkoarMinstrelPtr m) {
    auto& fairy (*m->fairy);

    auto x (lookup (m));

    if (x == nullptr)
    {
        fairy.impress (nullptr);
        return;
    }

    if (is_skoarpuscle<SkoarpusclePair> (x))
        x = skoarpuscle_ptr<SkoarpusclePair> (x)->val.second;

    if (is_skoarpuscle<SkoarpuscleSkoarpion> (x))
    {
        if (args == nullptr)
            fairy.impress (nullptr);

        skoarpuscle_ptr<SkoarpuscleSkoarpion> (x)->run (m);
    }

    else if (is_skoarpuscle<SkoarpuscleExpr> (x))
    {
        auto result (skoarpuscle_ptr<SkoarpuscleExpr> (x)->result);

        fairy.push_noating ();
        if (result != nullptr)
        {
            if (is_skoarpuscle<SkoarpusclePair> (result))
                result = skoarpuscle_ptr<SkoarpusclePair> (result)->val.second;
            fairy.impress (result);
        }
        else
            skoarpuscle_ptr<SkoarpuscleExpr> (x)->flatten (m);
        fairy.pop_noating ();

    }
    else if (is_skoarpuscle<SkoarpuscleList> (x))
    {
        if (args == nullptr)
        {
            fairy.impress (x);
        }
        else
        {
            // args when derefencing a list means send "at"
            SkoarpusclePtr result (nullptr);
            auto listy (skoarpuscle_ptr<SkoarpuscleList> (x));
            auto arg_list = fairy.impression;
            if (is_skoarpuscle<SkoarpuscleList> (arg_list))
            {
                const SkoarString sel (L"at");
                result = listy->skoar_msg (sel, arg_list, m);
            }
            fairy.impress (result);
        }
    }
    // todo: uncomment when books exist
    /*
    else if (is_skoarpuscle<SkoarpuscleBook>(x)) {
        auto book = skoarpuscle_ptr<SkoarpuscleBook>(x);
        auto args = fairy.impression;

        if (is_skoarpuscle<SkoarpuscleList>(args)) {
            auto listy = dynamic_cast<SkoarpuscleList>(*args);
            auto entry = listy.val.extract<ListOfSkoarpuscles>.front();

            if (is_skoarpuscle<SkoarpusclePair>(entry)) {
                entry = entry->flatten(m).extract<SkoarpusclePtr>();
            }

            if (is_skoarpuscle<SkoarpuscleSymbol>(entry)) {
                auto v = book->lookup(entry->val.extract<SkoarString>());
                fairy.impress(v);
            }
        }
    }*/
    else
        fairy.impress (x);
}


SkoarpusclePtr SkoarpuscleDeref::skoar_msg (SkoarString sel, SkoarpusclePtr /*args*/, SkoarMinstrelPtr m) {
    auto ret (val);
    auto x (lookup (m));

    // we don't recognise that name.
    if (x == nullptr)
        return make_shared<SkoarpuscleCat> ();

    if (is_skoarpuscle<SkoarpuscleSkoarpion> (x))
        return make_shared<SkoarpuscleSkoarpion> (x, args);

    return x;
}


// --- SkoarpuscleMathOp ---------------------------------------------------------
void SkoarpuscleMathOp::on_enter (SkoarMinstrelPtr m)
{
    auto& fairy (*m->fairy);
    auto left (fairy.cast_arcane_magic ());

    fairy.charge_arcane_magic (
        [=]() {
            auto& f (*m->fairy);
            SkoarpusclePtr right (f.impression);
            calculate (m, left, right);
            return f.impression;
        }
    );
}

void SkoarpuscleMathOp::calculate (SkoarMinstrelPtr m, SkoarpusclePtr left, SkoarpusclePtr right) {
    // the result is impressed by the operation
    f (m, left, right);
}


// --- SkoarpuscleBooleanOp ---------------------------------------------------------
bool SkoarpuscleBooleanOp::compare (SkoarpusclePtr a, SkoarpusclePtr b, SkoarMinstrelPtr m) {

    // the result is also impressed by the operation
    SkoarpusclePtr result (f (m, a, b));

    if (is_skoarpuscle<SkoarpuscleTrue> (result))
        return true;

    return false;
}

void SkoarpuscleBooleanOp::on_enter (SkoarMinstrelPtr m) {
    auto& fairy (*m->fairy);

    auto left (fairy.cast_arcane_magic ());

    fairy.charge_arcane_magic (
        [=]() {
            auto& f (*m->fairy);
            SkoarpusclePtr right (f.impression);
            compare (left, right, m);
            return f.impression;
        }
    );
}


// --- SkoarpuscleBoolean ---------------------------------------------------------
void SkoarpuscleBoolean::on_enter (SkoarMinstrelPtr m) {
    //m->fairy->push_compare ();
}

bool SkoarpuscleBoolean::evaluate (SkoarMinstrelPtr m, SkoarpusclePtr a, SkoarpusclePtr b) {
    return skoarpuscle_ptr<SkoarpuscleBooleanOp> (op)->compare (a, b, m);
}

// --- SkoarpuscleConditional ---------------------------------------------------------
void SkoarpuscleConditional::on_enter (SkoarMinstrelPtr m) {
    auto& fairy (*m->fairy);
    auto& koar (*m->koar);

    for (auto x : ifs)
    {
        auto condition (get<0> (x));
        auto if_body   (get<1> (x));
        auto else_body (get<2> (x));


        fairy.push_noating ();
        koar.do_skoarpion (condition, m, SkoarKoar::EExecStyle::INLINE, nullptr);
        fairy.pop_noating ();

        auto& impression (fairy.impression);

        bool bad_impression (is_skoarpuscle<SkoarpuscleFalse> (impression) ||
                             is_skoarpuscle<SkoarpuscleCat> (impression));

        if (!bad_impression)
            koar.do_skoarpion (if_body, m, SkoarKoar::EExecStyle::INLINE, nullptr);
        else if (else_body != nullptr)
            koar.do_skoarpion (else_body, m, SkoarKoar::EExecStyle::INLINE, nullptr);
    }
}

// --- SkoarpuscleTimes ---------------------------------------------------------
void SkoarpuscleTimes::on_enter (SkoarMinstrelPtr m) {
    auto& fairy (*m->fairy);
    auto desired_times (fairy.impression);

    if (desired_times->isCounty ())
    {
        auto times_seen (fairy.how_many_times_have_you_seen (ESkoarpuscle::Times, offs));
        auto times (desired_times->asCount ());

        fairy.impress (make_skoarpuscle (times_seen < times));
    }
    else
    {
        if (is_skoarpuscle<SkoarpuscleTrue> (desired_times) ||
            is_skoarpuscle<SkoarpuscleFalse> (desired_times) ||
            is_skoarpuscle<SkoarpuscleCat> (desired_times))
            fairy.impress (desired_times);
        else
            // todo: handle durations
            fairy.impress (make_skoarpuscle (false));

    }
}


// --- SkoarpuscleLoop ---------------------------------------------------------
// when we send a loop as a message, the receiver
// goes into _each_, then we go into on_enter (see decorating.cpp)
void SkoarpuscleLoop::foreach (SkoarpusclePtr listy) {
    each = listy;
}

void SkoarpuscleLoop::on_enter (SkoarMinstrelPtr m) {

    auto& fairy (*m->fairy);
    auto& koar (*m->koar);

    fairy.push_i ();
    fairy.push_noating (true);
    fairy.push_times_seen ();

    bool looping (true);

    auto f ([&](SkoarpusclePtr element) {
        if (element != nullptr)
            fairy.impress (element);

        koar.do_skoarpion (body, m, SkoarKoar::EExecStyle::INLINE, fairy.impression);
        fairy.incr_i ();

        if (condition != nullptr)
        {
            fairy.push_noating ();
            koar.do_skoarpion (condition, m, SkoarKoar::EExecStyle::INLINE, fairy.impression);
            fairy.pop_noating ();

            auto x (fairy.impression);
            if (is_skoarpuscle<SkoarpuscleFalse> (x) ||
                is_skoarpuscle<SkoarpuscleCat> (x))
                looping = false;
        }

    });

    for (; looping;)
    {
        if (each == nullptr)
            f (nullptr);
        else
            if (is_skoarpuscle<SkoarpuscleList> (each))
            {
                auto each_p (skoarpuscle_ptr<SkoarpuscleList> (each));
                // each->val is a ListOfSkoarpusclesPtr
                for (auto x : *(each_p->val))
                    f (x);
            }

        if (condition == nullptr)
            looping = false;
    }

    fairy.pop_times_seen ();
    fairy.pop_noating ();
    fairy.pop_i ();
}


// --- SkoarpuscleLoopMsg ---------------------------------------------------------


// --- SkoarpuscleExprEnd ---------------------------------------------------------
void SkoarpuscleExprEnd::on_enter (SkoarMinstrelPtr m) {
    m->fairy->cast_arcane_magic ();
}

// --- SkoarpuscleListSep ---------------------------------------------------------
void SkoarpuscleListSep::on_enter (SkoarMinstrelPtr m) {
    m->fairy->next_listy ();
}

// --- SkoarpuscleListEnd ---------------------------------------------------------
void SkoarpuscleListEnd::on_enter (SkoarMinstrelPtr m) {
    auto& fairy (*m->fairy);
    fairy.next_listy ();
    fairy.pop ();
    fairy.pop_noating ();
}

// --- SkoarpuscleList ---------------------------------------------------------
void SkoarpuscleList::on_enter (SkoarMinstrelPtr m) {
    auto& fairy (*m->fairy);

    fairy.push_noating (noaty);
    fairy.push ();
}

SkoarpusclePtr SkoarpuscleList::duplicate ()
{
    auto listy (make_shared<SkoarpuscleList> ());
    auto& newval (listy->val);

    for (auto& x : *val)
        newval->push_back (x->duplicate ());

    return listy;
}

bool SkoarpuscleList::isNoatworthy () {
    for (auto x : *val)
        if (!x->isNoatworthy ())
            return false;

    return true;
}

shared_ptr<SkoarpuscleList> SkoarpuscleList::mul (SkoarMinstrelPtr m, SkoarpusclePtr y) {
    auto out (make_shared<ListOfSkoarpuscles> ());

    for (auto x : *val)
    {
        //out->push_back(Skoar.ops.multiply_unimpressively(m, x, y));
    }

    return make_shared<SkoarpuscleList> (out);
}

shared_ptr<SkoarpuscleList> SkoarpuscleList::div (SkoarMinstrelPtr, SkoarpusclePtr) {
    auto out (make_shared<ListOfSkoarpuscles> ());

    for (auto x : *val)
    {
        //out->push_back(Skoar.ops.divide_unimpressively(m, y, x));
    }

    return make_shared<SkoarpuscleList> (out);
}

shared_ptr<SkoarpuscleList> SkoarpuscleList::divBy (SkoarMinstrelPtr, SkoarpusclePtr) {
    auto out (make_shared<ListOfSkoarpuscles> ());

    for (auto x : *val)
    {
        //out->push_back(Skoar.ops.divide_unimpressively(m, x, y));
    }

    return make_shared<SkoarpuscleList> (out);
}

SkoarInt SkoarpuscleList::size () {
    return val->size ();
}


void *SkoarpuscleList::asNoat () {
    return nullptr;
}



// --- SkoarpuscleArgs ---------------------------------------------------------
void SkoarpuscleArgs::on_enter (SkoarMinstrelPtr m) {
    auto& fairy (*m->fairy);

    fairy.push_noating ();
    fairy.push ();
}

void SkoarpuscleArgs::on_deref_exit (SkoarMinstrelPtr m) {
    auto& fairy (*m->fairy);

    fairy.pop ();
    fairy.pop_noating ();
}

// --- SkoarpuscleMsgName ---------------------------------------------------------

// --- SkoarpuscleMsgNameWithArgs ---------------------------------------------------------
void SkoarpuscleMsgNameWithArgs::on_enter (SkoarMinstrelPtr m) {
    auto& fairy (*m->fairy);

    fairy.push_noating ();
    fairy.push ();
}

// -----------------------------
// musical keywords skoarpuscles
// -----------------------------

// --- SkoarpuscleBars ---------------------------------------------------------
void SkoarpuscleBars::on_enter (SkoarMinstrelPtr m) {
    auto& fairy (*m->fairy);

    fairy.on_bar (this);

    // :|
    if (pre_repeat)
        if (fairy.how_many_times_have_you_seen (ESkoarpuscle::Bars, offs) < 2)
            throw SkoarNav (SkoarNav::COLON);

    // |:
    //if (post_repeat)
        //m->koar->state_put(L"colon_seen", make_skoarpuscle(static_cast<SkoarInt>(offs)));
}

// --- SkoarpuscleCoda ---------------------------------------------------------
void SkoarpuscleCoda::on_enter (SkoarMinstrelPtr m)
{
}

// --- SkoarpuscleGoto ---------------------------------------------------------
void SkoarpuscleGoto::on_enter (SkoarMinstrelPtr m)
{
    m->fairy->fly_to_coda (label);
}

// --- SkoarpuscleCarrots ---------------------------------------------------------

// --- SkoarpuscleTuplet ---------------------------------------------------------

// --- SkoarpuscleDynamic ---------------------------------------------------------

SkoarFloat SkoarpuscleDynamic::amp() { return val / 8.0; }

void SkoarpuscleDynamic::on_enter (SkoarMinstrelPtr m) {
    m->koar->put (L"amp", make_skoarpuscle (amp()));
}


// --- SkoarpuscleOctaveShift ---------------------------------------------------------
void SkoarpuscleOctaveShift::on_enter (SkoarMinstrelPtr m) {
    auto& koar (*m->koar);
    auto octave (koar.at (L"octave"));
    SkoarInt x (5);

    if (octave != nullptr)
        x = skoarpuscle_ptr<SkoarpuscleInt> (octave)->val;

    x += val;
    if (x < 0)
        x = 0;

    koar.put (L"octave", make_skoarpuscle (x));
}
// --- SkoarpuscleVoice ---------------------------------------------------------

// --- SkoarpuscleHashLevel ---------------------------------------------------------
void SkoarpuscleHashLevel::on_enter (SkoarMinstrelPtr m) {
    m->fairy->impress (duplicate());
}

SkoarpusclePtr SkoarpuscleHashLevel::duplicate ()
{
    return make_shared<SkoarpuscleHashLevel>(val);
}


// --- SkoarpusclePair ---------------------------------------------------------
SkoarpusclePtr SkoarpusclePair::assign (SkoarMinstrelPtr m) {
    auto& fairy (*m->fairy);
    fairy.push_noating ();

    /*x = if (val.isKindOf(SkoarpuscleExpr)) {
        val.flatten(m)
    } {
        val
    };*/

    SkoarpusclePtr x (val.second);
    if (is_skoarpuscle<SkoarpuscleExpr> (x))
        x = skoarpuscle_ptr<SkoarpuscleExpr> (x)->flatten (m);

    auto out (SkoarOps::getInstance ()->assign (m, x, make_shared<SkoarpuscleSymbolColon> (val.first)));

    fairy.pop_noating ();

    return out;
}

// --- SkoarpuscleExpr ---------------------------------------------------------
SkoarpusclePtr SkoarpuscleExpr::flatten (SkoarMinstrelPtr m) {
    auto& fairy (*m->fairy);

    fairy.push ();
    if (val != nullptr)
        val->evaluate (m);
    else
        fairy.impress (nullptr);

    result = fairy.impression;

    if (is_skoarpuscle<SkoarpusclePair> (result))
        result = skoarpuscle_ptr<SkoarpusclePair> (result)->val.second;

    fairy.pop ();
    return result;
}
