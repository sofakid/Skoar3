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

// --- SkoarpuscleTrue ---------------------------------------------------------
void SkoarpuscleTrue::on_enter (SkoarMinstrelPtr m) {
    m->fairy->impress (true);
}

// --- SkoarpuscleFalse ---------------------------------------------------------

void SkoarpuscleFalse::on_enter (SkoarMinstrelPtr m) {
    m->fairy->impress (false);
}

// --- SkoarpuscleInt ---------------------------------------------------------
void SkoarpuscleInt::on_enter (SkoarMinstrelPtr m) {
    m->fairy->impress (val);
}

void *SkoarpuscleInt::asNoat () { return nullptr; }

// --- SkoarpuscleFloat ---------------------------------------------------------
void SkoarpuscleFloat::on_enter (SkoarMinstrelPtr m) {
    m->fairy->impress (val);
}
void *SkoarpuscleFloat::asNoat () {
    return nullptr;
}

// --- SkoarpuscleFreq ---------------------------------------------------------
void SkoarpuscleFreq::on_enter (SkoarMinstrelPtr m) {
    m->fairy->impress (make_shared<SkoarpuscleFreq> (val));
}

void *SkoarpuscleFreq::asNoat () {
    return nullptr;
    //return new SkoarNoat_Freq(val.asFloat);
}

// --- SkoarpuscleNoat ---------------------------------------------------------
void *SkoarpuscleNoat::asNoat () { return nullptr; }

void SkoarpuscleNoat::on_enter (SkoarMinstrelPtr) {

}

// --- SkoarpuscleChoard ---------------------------------------------------------
void* SkoarpuscleChoard::asNoat () { return nullptr; }

void SkoarpuscleChoard::on_enter (SkoarMinstrelPtr) {

}

// --- SkoarpuscleString ---------------------------------------------------------
void SkoarpuscleString::on_enter (SkoarMinstrelPtr m) {
    m->fairy->impress (val);
}

SkoarpusclePtr SkoarpuscleString::skoar_msg (SkoarpuscleMsg *msg, SkoarMinstrelPtr minstrel) {
    auto sel (msg->val);

    //if (sel == L"sample") {
    //    return make_shared<SkoarpuscleSample>(val);
    //}
    return make_shared<SkoarpuscleCat> ();
}

// --- SkoarpuscleSymbolName ---------------------------------------------------------

// --- SkoarpuscleSymbol ---------------------------------------------------------
void SkoarpuscleSymbol::on_enter (SkoarMinstrelPtr m) {
    m->fairy->impress (make_shared<SkoarpuscleSymbol> (val));
}

SkoarpusclePtr SkoarpuscleSymbol::skoar_msg (SkoarpuscleMsg* /*msg*/, SkoarMinstrelPtr minstrel) {

    /* this was how we called underlying SC class methods..
       don't know what I want to do with this anymore. */

    return make_shared<SkoarpuscleCat> ();
}

// --- SkoarpuscleSymbolColon ---------------------------------------------------------

// --- SkoarpuscleDeref ---------------------------------------------------------
SkoarpusclePtr SkoarpuscleDeref::lookup (SkoarMinstrelPtr minstrel) {
    return minstrel->koar->at (val);
}

//Poco::DynamicAny SkoarpuscleDeref::flatten(SkoarMinstrelPtr m) {
//    return lookup(m)->flatten(m);
//}

void SkoarpuscleDeref::on_enter (SkoarMinstrelPtr m) {
    if (args != nullptr)
        skoarpuscle_ptr<SkoarpuscleArgs> (args)->on_enter (m);
}

void SkoarpuscleDeref::on_exit (SkoarMinstrelPtr m) {
    if (args != nullptr)
        skoarpuscle_ptr<SkoarpuscleArgs> (args)->on_deref_exit (m);
    do_deref (m);
}

void SkoarpuscleDeref::do_deref (SkoarMinstrelPtr m) {
    auto x (lookup (m));

    if (x == nullptr)
    {
        m->fairy->impress (nullptr);
        return;
    }

    if (is_skoarpuscle<SkoarpusclePair> (x))
        x = skoarpuscle_ptr<SkoarpusclePair> (x)->val.second;

    if (is_skoarpuscle<SkoarpuscleSkoarpion> (x))
        skoarpuscle_ptr<SkoarpuscleSkoarpion> (x)->run (m);

    else if (is_skoarpuscle<SkoarpuscleExpr> (x))
    {
        auto result = skoarpuscle_ptr<SkoarpuscleExpr> (x)->result;

        m->fairy->push_noating ();
        if (result != nullptr)
        {
            if (is_skoarpuscle<SkoarpusclePair> (result))
                result = skoarpuscle_ptr<SkoarpusclePair> (result)->val.second;
            m->fairy->impress (result);
        }
        else
            skoarpuscle_ptr<SkoarpuscleExpr> (x)->flatten (m);
        m->fairy->pop_noating ();

    }
    // todo: uncomment when books exist
    /*
    else if (is_skoarpuscle<SkoarpuscleBook>(x)) {
        auto book = skoarpuscle_ptr<SkoarpuscleBook>(x);
        auto args = m->fairy->impression;

        if (is_skoarpuscle<SkoarpuscleList>(args)) {
            auto listy = dynamic_cast<SkoarpuscleList>(*args);
            auto entry = listy.val.extract<ListOfSkoarpuscles>.front();

            if (is_skoarpuscle<SkoarpusclePair>(entry)) {
                entry = entry->flatten(m).extract<SkoarpusclePtr>();
            }

            if (is_skoarpuscle<SkoarpuscleSymbol>(entry)) {
                auto v = book->lookup(entry->val.extract<SkoarString>());
                m->fairy->impress(v);
            }
        }
    }*/
    else
        m->fairy->impress (x);
}


SkoarpusclePtr SkoarpuscleDeref::skoar_msg (SkoarpuscleMsg* /*msg*/, SkoarMinstrelPtr minstrel) {
    auto ret (val);
    auto x (lookup (minstrel));

    // we don't recognise that name.
    if (x == nullptr)
        return make_shared<SkoarpuscleCat> ();

    if (is_skoarpuscle<SkoarpuscleSkoarpion> (x))
        return make_shared<SkoarpuscleSkoarpion> (x, args);

    return x;
}


// --- SkoarpuscleMathOp ---------------------------------------------------------
void SkoarpuscleMathOp::calculate (SkoarMinstrelPtr m, SkoarpusclePtr left, SkoarpusclePtr right) {
    // the result is impressed by the operation
    f (m, left, right);
}


// --- SkoarpuscleBooleanOp ---------------------------------------------------------
bool SkoarpuscleBooleanOp::compare (SkoarpusclePtr a, SkoarpusclePtr b, SkoarMinstrelPtr m) {

    // todo: when using ops table, don't do these two lines
    /*auto x = a->flatten(m).extract<SkoarInt>();
    auto y = b->flatten(m).extract<SkoarInt>();

    return f(x, y);*/
    return false;
}

void SkoarpuscleBooleanOp::on_enter (SkoarMinstrelPtr m) {
    m->fairy->cast_arcane_magic ();
    m->fairy->compare_impress (m);
}


// --- SkoarpuscleBoolean ---------------------------------------------------------
void SkoarpuscleBoolean::on_enter (SkoarMinstrelPtr m) {
    m->fairy->push_compare ();
}

bool SkoarpuscleBoolean::evaluate (SkoarMinstrelPtr m, SkoarpusclePtr a, SkoarpusclePtr b) {
    return skoarpuscle_ptr<SkoarpuscleBooleanOp> (op)->compare (a, b, m);
}

// --- SkoarpuscleConditional ---------------------------------------------------------
void SkoarpuscleConditional::on_enter (SkoarMinstrelPtr m) {
    for (auto x : ifs)
    {
        auto condition (get<0> (x));
        auto if_body   (get<1> (x));
        auto else_body (get<2> (x));

        m->fairy->push_noating ();
        m->koar->do_skoarpion (condition, m, SkoarKoar::EExecStyle::INLINE, nullptr);
        m->fairy->pop_noating ();

        auto impression (m->fairy->boolean_impression);

        bool bad_impression (is_skoarpuscle<SkoarpuscleFalse> (impression) ||
                             is_skoarpuscle<SkoarpuscleCat> (impression));

        if (!bad_impression)
            m->koar->do_skoarpion (if_body, m, SkoarKoar::EExecStyle::INLINE, nullptr);
        else if (else_body != nullptr)
            m->koar->do_skoarpion (else_body, m, SkoarKoar::EExecStyle::INLINE, nullptr);
    }
}

// --- SkoarpuscleTimes ---------------------------------------------------------
void SkoarpuscleTimes::on_enter (SkoarMinstrelPtr m) {

    auto desired_times (m->fairy->cast_arcane_magic ());

    if (desired_times->isCounty ())
    {
        auto times_seen (m->fairy->how_many_times_have_you_seen (ESkoarpuscle::Times, offs));
        auto times (desired_times->asCount ());

        m->fairy->impress (make_skoarpuscle (times_seen < times));
    }
    else
    {
        if (is_skoarpuscle<SkoarpuscleTrue> (desired_times) ||
            is_skoarpuscle<SkoarpuscleFalse> (desired_times) ||
            is_skoarpuscle<SkoarpuscleCat> (desired_times))
            m->fairy->impress (desired_times);
        else
            // todo: handle durations
            m->fairy->impress (make_skoarpuscle (false));

    }
}


// --- SkoarpuscleLoop ---------------------------------------------------------
// when we send a loop as a message, the receiver
// goes into _each_, then we go into on_enter (see decorating.cpp)
void SkoarpuscleLoop::foreach (SkoarpusclePtr listy) {
    each = listy;
}

void SkoarpuscleLoop::on_enter (SkoarMinstrelPtr m) {

    m->fairy->push_i ();
    m->fairy->push_noating (true);
    m->fairy->push_times_seen ();

    bool looping (true);

    auto f ([&](SkoarpusclePtr element) {
        if (element != nullptr)
            m->fairy->impress (element);

        m->koar->do_skoarpion (body, m, SkoarKoar::EExecStyle::INLINE, m->fairy->impression);
        m->fairy->incr_i ();

        if (condition != nullptr)
        {
            m->fairy->push_noating ();
            m->koar->do_skoarpion (condition, m, SkoarKoar::EExecStyle::INLINE, m->fairy->impression);
            m->fairy->pop_noating ();

            auto x = m->fairy->boolean_impression;
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

    m->fairy->pop_times_seen ();
    m->fairy->pop_noating ();
    m->fairy->pop_i ();
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
    m->fairy->next_listy ();
    m->fairy->pop ();
    m->fairy->pop_noating ();

}


// --- SkoarpuscleList ---------------------------------------------------------
void SkoarpuscleList::on_enter (SkoarMinstrelPtr m) {
    m->fairy->push_noating (noaty);
    m->fairy->push ();
}

bool SkoarpuscleList::isNoatworthy () {
    for (auto x : *val)
        if (!x->isNoatworthy ())
            return false;

    return true;
}

shared_ptr<SkoarpuscleList> SkoarpuscleList::mul (SkoarMinstrelPtr m, SkoarpusclePtr y) {
    auto out = make_shared<ListOfSkoarpuscles> ();

    for (auto x : *val)
    {
        //out->push_back(Skoar.ops.multiply_unimpressively(m, x, y));
    }

    return make_shared<SkoarpuscleList> (out);
}

shared_ptr<SkoarpuscleList> SkoarpuscleList::div (SkoarMinstrelPtr, SkoarpusclePtr) {
    auto out = make_shared<ListOfSkoarpuscles> ();

    for (auto x : *val)
    {
        //out->push_back(Skoar.ops.divide_unimpressively(m, y, x));
    }

    return make_shared<SkoarpuscleList> (out);
}

shared_ptr<SkoarpuscleList> SkoarpuscleList::divBy (SkoarMinstrelPtr, SkoarpusclePtr) {
    auto out = make_shared<ListOfSkoarpuscles> ();

    for (auto x : *val)
    {
        //out->push_back(Skoar.ops.divide_unimpressively(m, x, y));
    }

    return make_shared<SkoarpuscleList> (out);
}

SkoarInt SkoarpuscleList::size () {
    return val->size ();
}

//Poco::DynamicAny SkoarpuscleList::flatten(SkoarMinstrelPtr m) {
//    auto listy = val.extract<ListOfSkoarpuscles>();

//    list<Poco::DynamicAny> arr;

 //   for (auto x: listy) {
 //       auto y = x->flatten(m);

        /*
        ??? i don't know what to do here

        if (y.type == typeid(shared_ptr<SkoarpusclePair>)) {
            auto z = y.extract<shared_ptr<SkoarpusclePair>>()->flatten(m);
            arr.push_back(z);
        }
        else

        */
        //          arr.push_back(y);
          //}

       //   Poco::DynamicAny out = arr;
       //   return out;
      //}


void *SkoarpuscleList::asNoat () {
    // ready to port as commented
    /*
    var n = val.size;
    var noats = Array.newClear(n);
    var i = -1;
    var theseAreNoats = true;
    var theseAreFreq = false;

    val.do {
        | x |
        i = i + 1;

        if (x.isKindOf(SkoarpuscleFreq)) {
            theseAreNoats = false;
            theseAreFreq = true;
        };

        if (x.isKindOf(SkoarpuscleInt)) {
            theseAreNoats = false;
        };

        if (x.isKindOf(SkoarpuscleFloat)) {
            theseAreNoats = false;
        };
        noats[i] = x.asNoat;
    };

    if (theseAreNoats == true) {
        ^SkoarNoat_NoteList(noats);
    };

    if (theseAreFreq == true) {
        ^SkoarNoat_FreqList(noats);
    };

    ^SkoarNoat_DegreeList(noats);
    */
    return nullptr;
}

SkoarpusclePtr SkoarpuscleList::skoar_msg (SkoarpuscleMsg* /*msg*/, SkoarMinstrelPtr minstrel) {
    // ready to port as commented
    /*
    var o = msg.get_msg_arr(minstrel);
    var name = msg.val;
    var ret;

    // todo teach the fairy to next and last
    case {name == \next} {
        ret = val.performMsg(o);
    } {name == \last} {
        ret = val.performMsg(o);
    } {name == \choose} {
        ret = val.choose();
    } {
        ret = val.performMsg(o);
    };

    ^Skoarpuscle.wrap(ret);
    */
    return nullptr;
}



// --- SkoarpuscleArgs ---------------------------------------------------------
void SkoarpuscleArgs::on_enter (SkoarMinstrelPtr m) {
    m->fairy->push_noating ();
    m->fairy->push ();
}

void SkoarpuscleArgs::on_deref_exit (SkoarMinstrelPtr m) {
    m->fairy->pop ();
    m->fairy->pop_noating ();
}


// --- SkoarpuscleMsg ---------------------------------------------------------
void SkoarpuscleMsg::on_enter (SkoarMinstrelPtr m) {
    // i don't want to go down this road.
    /* if (args != nullptr) {
        auto x = m->fairy->impression;
        if (is_skoarpuscle<SkoarpuscleList>(x)) {
            auto new_args = skoarpuscle_ptr<SkoarpuscleList>(x);
            // original code:
            // args = m.fairy.impression;
        }
    }*/

    if (dest == nullptr)
        throw SkoarRuntimeException (L"msg: dest is nullptr");

    SkoarpusclePtr result = nullptr;
    if (is_skoarpuscle<SkoarpuscleList> (dest))
    {
        // why not this? : result = skoarpuscle_ptr<SkoarpuscleList>(dest)->skoar_msg(this, m);
        result = m->fairy->impression;
        result = skoarpuscle_ptr<SkoarpuscleList> (result)->skoar_msg (this, m);
    }
    else if (is_skoarpuscle<SkoarpuscleSkoarpion> (dest))
        result = skoarpuscle_ptr<SkoarpuscleSkoarpion> (dest)->skoar_msg (this, m);
    
    else if (is_skoarpuscle<SkoarpuscleString> (dest))
        result = skoarpuscle_ptr<SkoarpuscleString> (dest)->skoar_msg (this, m);
    
    else if (is_skoarpuscle<SkoarpuscleSymbol> (dest))
        result = skoarpuscle_ptr<SkoarpuscleSymbol> (dest)->skoar_msg (this, m);
    
    else if (is_skoarpuscle<SkoarpuscleDeref> (dest))
        result = skoarpuscle_ptr<SkoarpuscleDeref> (dest)->skoar_msg (this, m);
    
    else if (is_skoarpuscle<SkoarpuscleMsg> (dest))
        result = skoarpuscle_ptr<SkoarpuscleMsg> (dest)->skoar_msg (this, m);
    
    else if (is_skoarpuscle<SkoarpuscleList> (dest))
        result = skoarpuscle_ptr<SkoarpuscleList> (dest)->skoar_msg (this, m);
    
    else if (is_skoarpuscle<SkoarpuscleList> (dest))
        result = skoarpuscle_ptr<SkoarpuscleList> (dest)->skoar_msg (this, m);

    m->fairy->impress (result);

}

SkoarpusclePtr SkoarpuscleMsg::skoar_msg (SkoarpuscleMsg* /*msg*/, SkoarMinstrelPtr m) {
    SkoarpusclePtr result = m->fairy->impression;
    if (is_skoarpuscle<SkoarpuscleList> (result))
        result = skoarpuscle_ptr<SkoarpuscleList> (result)->skoar_msg (this, m);
    
    else if (is_skoarpuscle<SkoarpuscleSkoarpion> (result))
        result = skoarpuscle_ptr<SkoarpuscleSkoarpion> (result)->skoar_msg (this, m);
    
    else if (is_skoarpuscle<SkoarpuscleString> (result))
        result = skoarpuscle_ptr<SkoarpuscleString> (result)->skoar_msg (this, m);
    
    else if (is_skoarpuscle<SkoarpuscleSymbol> (result))
        result = skoarpuscle_ptr<SkoarpuscleSymbol> (result)->skoar_msg (this, m);
    
    else if (is_skoarpuscle<SkoarpuscleDeref> (result))
        result = skoarpuscle_ptr<SkoarpuscleDeref> (result)->skoar_msg (this, m);
    
    else if (is_skoarpuscle<SkoarpuscleMsg> (result))
        result = skoarpuscle_ptr<SkoarpuscleMsg> (result)->skoar_msg (this, m);
    
    else if (is_skoarpuscle<SkoarpuscleList> (result))
        result = skoarpuscle_ptr<SkoarpuscleList> (result)->skoar_msg (this, m);
    
    else if (is_skoarpuscle<SkoarpuscleList> (result))
        result = skoarpuscle_ptr<SkoarpuscleList> (result)->skoar_msg (this, m);

    return m->fairy->impress (result);
}

list<SkoarString> SkoarpuscleMsg::get_msg_arr (SkoarMinstrelPtr m) {
    list<SkoarString> out;
    /*
    var x, z;
    var i;

    if (args.isNil) {
        ^[val];
    };

    //("MSG::"++val++"::get_msg_arr::args:"++ args).postln;
    //("Args exist, x will be " ++ (args.size + 1).asString).postln;
    x = Array.newClear(args.size + 1);
    i = 0;

    //"args: ".post; args.postln;
    //("SKRP_Msg.get_msg_arr :: pushing noating").postln;
    m.fairy.push_noating;

    x[0] = val;
    args.val.do {
        | y |
        //"y: ".post; y.postln;
        i = i + 1;
        case {y.isKindOf(SkoarpusclePair)} {
            x[i] = [y.key.val, y.val.flatten(m)];
        } {y.isKindOf(Skoarpuscle)} {
            x[i] = y.flatten(m);
        } {
            x[i] = y;
        };
    };
    //("SKRP_Msg.get_msg_arr :: popping noating").postln;
    m.fairy.pop_noating;

    //("MSG::get_msg_arr::  x :"++ x).postln;
    ^x;
    */
    return out;
}

list<SkoarString> SkoarpuscleMsg::get_args_from_prototype (SkoarMinstrelPtr m) {
    list<SkoarString> out;
    /*
    var e = ();
    var j = 0;
    var ret = [];
    var w;
    var p = pref ++ " g_a_f_proto :: ";

    //(p ++ "arg_prot :: " ++ arg_prot).postln;

    if (args.notNil) {
        args.val.do {
            | x |
            if (x.isKindOf(SkoarpusclePair)) {
                e[x.key.val] = x.val.flatten(m);
                //(p ++ "e[" ++ x.key.val ++ "] = e[x.key.val] =" ++ e[x.key.val] ++ ";").postln;
            } {
                e[j] = x.flatten(m);
                //(p ++ "e[" ++ j ++ "] = e[j] =" ++ e[j] ++ ";").postln;

            };
            j = j + 1;
        };
    };

    arg_spec.do {
        | x, i |
        var v = e[x];
        var y;

        if (v.notNil) {
            arg_prot[i] = v;
            //(p ++ "arg_prot[" ++ i ++ "] = v = " ++ v ++ ";").postln;
        } {
            y = e[i];
            //(p ++ "arg_prot[" ++ i ++ "] = e[i] =" ++ e[i] ++ ";").postln;

            if (y.notNil) {
                arg_prot[i] = y;
            };
        };
    };

    //(p ++ "arg_prot :: "++ arg_prot).postln;

    ^arg_prot;
    */
    return out;
}

// --- SkoarpuscleMsgName ---------------------------------------------------------

// --- SkoarpuscleMsgNameWithArgs ---------------------------------------------------------
void SkoarpuscleMsgNameWithArgs::on_enter (SkoarMinstrelPtr m) {
    m->fairy->push_noating ();
    m->fairy->push ();
}

// -----------------------------
// musical keywords skoarpuscles
// -----------------------------

// --- SkoarpuscleBars ---------------------------------------------------------
void SkoarpuscleBars::on_enter (SkoarMinstrelPtr m) {

    m->fairy->on_bar (this);

    // :|
    if (pre_repeat)
        if (m->fairy->how_many_times_have_you_seen (ESkoarpuscle::Bars, offs) < 2)
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
    auto octave (m->koar->at (L"octave"));
    SkoarInt x (5);

    if (octave != nullptr)
        x = skoarpuscle_ptr<SkoarpuscleInt> (octave)->val;

    x += val;
    if (x < 0)
        x = 0;

    m->koar->put (L"octave", make_skoarpuscle (x));
}
// --- SkoarpuscleVoice ---------------------------------------------------------

// --- SkoarpuscleHashLevel ---------------------------------------------------------

// --- SkoarpusclePair ---------------------------------------------------------
SkoarpusclePtr SkoarpusclePair::assign (SkoarMinstrelPtr m) {
    m->fairy->push_noating ();

    /*x = if (val.isKindOf(SkoarpuscleExpr)) {
        val.flatten(m)
    } {
        val
    };*/

    SkoarpusclePtr x (val.second);
    if (is_skoarpuscle<SkoarpuscleExpr> (x))
        x = skoarpuscle_ptr<SkoarpuscleExpr> (x)->flatten (m);

    auto out (SkoarOps::getInstance ()->assign (m, x, make_shared<SkoarpuscleSymbolColon> (val.first)));

    m->fairy->pop_noating ();

    return out;
}

// --- SkoarpuscleExpr ---------------------------------------------------------


SkoarpusclePtr SkoarpuscleExpr::flatten (SkoarMinstrelPtr m) {

    m->fairy->push ();
    if (val != nullptr)
        val->evaluate (m);
    else
        m->fairy->impress (nullptr);

    result = m->fairy->impression;

    if (is_skoarpuscle<SkoarpusclePair> (result))
        result = skoarpuscle_ptr<SkoarpusclePair> (result)->val.second;

    m->fairy->pop ();
    return result;
}

/*flatten {
        | m |
        //("SkoarpuscleExpr :: flatten").postln;
        m.fairy.push;

        if (val.notNil) {
            val.evaluate(m);
        } {
            m.fairy.impress(SkoarpuscleCat.new);
        };

        result = m.fairy.impression;
        result = result.flatten(m);

        m.fairy.pop;

        //("SkoarpuscleExpr :: result :: " ++ result).postln;

        ^result;
    }*/

