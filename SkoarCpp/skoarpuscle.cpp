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



// Skoarpuscles are the closest thing we have to "types".
//
// They represent value types, as well as most things that
// can be spoken of as things, like a statement, boolean expression, etc.
//

// --- SkoarpuscleUnknown ---------------------------------------------------------
SkoarpuscleUnknown::SkoarpuscleUnknown() {}

// --- SkoarpuscleCat ---------------------------------------------------------
SkoarpuscleCat::SkoarpuscleCat() {}

void SkoarpuscleCat::on_enter(SkoarMinstrelPtr m) { 
    m->fairy->impress(nullptr); 
}

// --- SkoarpuscleTrue ---------------------------------------------------------
SkoarpuscleTrue::SkoarpuscleTrue() {
    impressionable = true;
}

void SkoarpuscleTrue::on_enter(SkoarMinstrelPtr m) {
    m->fairy->impress(true);
}

// --- SkoarpuscleFalse ---------------------------------------------------------
SkoarpuscleFalse::SkoarpuscleFalse() {
    impressionable = true;
}


void SkoarpuscleFalse::on_enter(SkoarMinstrelPtr m) { 
    m->fairy->impress(false);
}

// --- SkoarpuscleInt ---------------------------------------------------------
SkoarpuscleInt::SkoarpuscleInt(SkoarInt v) : val(v) {
    noatworthy = true;
    impressionable = true;
}

void SkoarpuscleInt::on_enter(SkoarMinstrelPtr m) {
    m->fairy->impress(val);
}

void *SkoarpuscleInt::asNoat() { return nullptr; }


// --- SkoarpuscleFloat ---------------------------------------------------------
SkoarpuscleFloat::SkoarpuscleFloat(SkoarFloat v) : val(v) {
    noatworthy = true;
    impressionable = true;
}

void SkoarpuscleFloat::on_enter(SkoarMinstrelPtr m) { 
    m->fairy->impress(val);
}
void *SkoarpuscleFloat::asNoat() { 
    return nullptr;
}

// --- SkoarpuscleFreq ---------------------------------------------------------

SkoarpuscleFreq::SkoarpuscleFreq(SkoarFloat v) : 
    val(v) 
{
    noatworthy = true;
    impressionable = true;
}

SkoarpuscleFreq::SkoarpuscleFreq(SkoarString lexeme) :
    SkoarpuscleFreq(stod(lexeme.substr(0, lexeme.length() - 3))) {
}

SkoarpuscleFreq::SkoarpuscleFreq(SkoarInt v) : 
    SkoarpuscleFreq(static_cast<SkoarFloat>(v)) {
}

void SkoarpuscleFreq::on_enter(SkoarMinstrelPtr m) {
    m->fairy->impress(make_shared<SkoarpuscleFreq>(val));
}

void *SkoarpuscleFreq::asNoat() { 
    return nullptr;
	//return new SkoarNoat_Freq(val.asFloat);
}

// --- SkoarpuscleNoat ---------------------------------------------------------
SkoarpuscleNoat::SkoarpuscleNoat(SkoarString&) : val(0) {
    noatworthy = true;
    impressionable = true;
}
	
void *SkoarpuscleNoat::asNoat() { return nullptr; }

void SkoarpuscleNoat::on_enter(SkoarMinstrelPtr) {

}

// --- SkoarpuscleChoard ---------------------------------------------------------
SkoarpuscleChoard::SkoarpuscleChoard(SkoarString&) : val(0) {
    noatworthy = true;
    impressionable = true;
}

void* SkoarpuscleChoard::asNoat() { return nullptr; }

void SkoarpuscleChoard::on_enter(SkoarMinstrelPtr) {

}

// --- SkoarpuscleString ---------------------------------------------------------
SkoarpuscleString::SkoarpuscleString(SkoarString s) : val(s) {
    impressionable = true;
}

void SkoarpuscleString::on_enter(SkoarMinstrelPtr m) {
    m->fairy->impress(val); 
}

SkoarpusclePtr SkoarpuscleString::skoar_msg(SkoarpuscleMsg *msg, SkoarMinstrelPtr minstrel) {
    auto sel = msg->val;

    //if (sel == L"sample") {
    //    return make_shared<SkoarpuscleSample>(val);
    //}
    return make_shared<SkoarpuscleCat>();
}

// --- SkoarpuscleSymbolName ---------------------------------------------------------
SkoarpuscleSymbolName::SkoarpuscleSymbolName(SkoarString s) : val(s) {
}

// --- SkoarpuscleSymbol ---------------------------------------------------------
SkoarpuscleSymbol::SkoarpuscleSymbol(SkoarString s) : val(s) { 
    impressionable = true;
}

void SkoarpuscleSymbol::on_enter(SkoarMinstrelPtr m) { 
    m->fairy->impress(make_shared<SkoarpuscleSymbol>(val)); 
}

SkoarpusclePtr SkoarpuscleSymbol::skoar_msg(SkoarpuscleMsg *msg, SkoarMinstrelPtr minstrel) {
    
    /* this was how we called underlying SC class methods.. 
       don't know what I want to do with this anymore. */

    return make_shared<SkoarpuscleCat>();
}

inline SkoarString clean_symbol_colon(SkoarString &lex) {
    // lexeme was matched by: [a-zA-Z0-9_][a-zA-Z0-9_]*[ \t]*:(?![:|}])
    // ... so we'll remove anything that's not [a-zA-Z0-9_]
    std::wregex expr(L"([^a-zA-Z0-9_]+)");
    return std::regex_replace(lex, expr, L"");
}

// --- SkoarpuscleSymbolColon ---------------------------------------------------------
SkoarpuscleSymbolColon::SkoarpuscleSymbolColon(SkoarString lex) : val(clean_symbol_colon(lex)) {
    impressionable = true;
}

// --- SkoarpuscleDeref ---------------------------------------------------------
SkoarpuscleDeref::SkoarpuscleDeref(SkoarString v, SkoarpusclePtr a) : val(v) {
	args = a; // is actually shared_ptr<SkoarpuscleArgs>
}

SkoarpusclePtr SkoarpuscleDeref::lookup(SkoarMinstrelPtr minstrel) {
	//return minstrel->koar[val];
    return make_shared<SkoarpuscleCat>();
}

//Poco::DynamicAny SkoarpuscleDeref::flatten(SkoarMinstrelPtr m) {
//    return lookup(m)->flatten(m);
//}

void SkoarpuscleDeref::on_enter(SkoarMinstrelPtr m) {
    if (args != nullptr) {
        auto o = dynamic_cast<SkoarpuscleArgs&>(*args);
        o.on_enter(m);
    }
}

void SkoarpuscleDeref::on_exit(SkoarMinstrelPtr m) {
    if (args != nullptr) {
        auto o = dynamic_cast<SkoarpuscleArgs&>(*args);
        o.on_deref_exit(m);
    }
    do_deref(m);
}

void SkoarpuscleDeref::do_deref(SkoarMinstrelPtr m) {
    auto x = lookup(m);

    if (x == nullptr) {
        m->fairy->impress(nullptr);
        return;
    }

    if (typeid(*x) == typeid(SkoarpuscleSkoarpion&)) {
        auto skrpn = dynamic_cast<SkoarpuscleSkoarpion&>(*x);
        skrpn.run(m);
    } 
    
    else if (typeid(*x) == typeid(SkoarpuscleExpr&)) {
        auto expr = dynamic_cast<SkoarpuscleExpr&>(*x);
        auto result = expr.result;

        m->fairy->push_noating();
        if (result != nullptr) {
            m->fairy->impress(result);
        }
        // not sure about this.. it seems to go nowhere..
        //else {
        //    expr.flatten(m);
        //}
        m->fairy->pop_noating();

    }
    // todo: uncomment when books exist
    /*
    else if (typeid(*x) == typeid(SkoarpuscleBook&)) {
        auto book = dynamic_cast<SkoarpuscleBook&>(*x);
        auto args = m->fairy->impression;

        if (typeid(*args) == typeid(SkoarpuscleList&)) {
            auto listy = dynamic_cast<SkoarpuscleList&>(*args);
            auto entry = listy.val.extract<ListOfSkoarpuscles>.front();

            if (typeid(*entry) == typeid(SkoarpusclePair)) {
                entry = entry->flatten(m).extract<SkoarpusclePtr>();
            }

            if (typeid(*entry) == typeid(SkoarpuscleSymbol)) {
                auto v = book.lookup(entry->val.extract<SkoarString>());
                m->fairy->impress(v);
            }
        }
    }*/
    else {
        m->fairy->impress(x);
    }
}


SkoarpusclePtr SkoarpuscleDeref::skoar_msg(SkoarpuscleMsg *msg, SkoarMinstrelPtr minstrel) {

	auto ret = val;
	auto x = lookup(minstrel);

    // we don't recognise that name.
    if (x == nullptr) {
        return make_shared<SkoarpuscleCat>();
    }

	if (typeid(*x) == typeid(SkoarpuscleSkoarpion)) {
		return make_shared<SkoarpuscleSkoarpion>(x, args);
	};

	return x;    
}


// --- SkoarpuscleMathOp ---------------------------------------------------------
SkoarpuscleMathOp::SkoarpuscleMathOp(SkoarToke *toke) : val(toke->lexeme) {
	auto s = toke->lexeme;
    
    if (s == L"+") {
        f = [](SkoarMinstrelPtr m, SkoarpusclePtr a, SkoarpusclePtr b) {
            // Skoar::ops.add(m, a, b);
        };
    } 
    else if (s == L"*") {
        f = [](SkoarMinstrelPtr m, SkoarpusclePtr a, SkoarpusclePtr b) {
            // Skoar::ops.multiply(m, a, b);
        };
    }
    else if(s == L"/") {
        f = [](SkoarMinstrelPtr m, SkoarpusclePtr a, SkoarpusclePtr b) {
            // Skoar::ops.divide(m, a, b);
        };
    }
    else if (s == L"-") {
        f = [](SkoarMinstrelPtr m, SkoarpusclePtr a, SkoarpusclePtr b) {
            // Skoar::ops.sub(m, a, b);
        };
    }
}

void SkoarpuscleMathOp::calculate(SkoarMinstrelPtr m, SkoarpusclePtr left, SkoarpusclePtr right) {
	// the result is impressed by the operation
	f(m, left, right);
}


// --- SkoarpuscleBooleanOp ---------------------------------------------------------
SkoarpuscleBooleanOp::SkoarpuscleBooleanOp(SkoarNoadPtr noad, SkoarToke *toke) {
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

bool SkoarpuscleBooleanOp::compare(SkoarpusclePtr a, SkoarpusclePtr b, SkoarMinstrelPtr m) {
	
    // todo: when using ops table, don't do these two lines
    /*auto x = a->flatten(m).extract<SkoarInt>();
    auto y = b->flatten(m).extract<SkoarInt>();

    return f(x, y);*/
    return false;
}

void SkoarpuscleBooleanOp::on_enter(SkoarMinstrelPtr m) {
    m->fairy->cast_arcane_magic();
    m->fairy->compare_impress(m);
}


// --- SkoarpuscleBoolean ---------------------------------------------------------
SkoarpuscleBoolean::SkoarpuscleBoolean(SkoarNoadPtr noad) {
	op = noad->children.front()->next_skoarpuscle();
}

void SkoarpuscleBoolean::on_enter(SkoarMinstrelPtr m) {
    m->fairy->push_compare();
}

bool SkoarpuscleBoolean::evaluate(SkoarMinstrelPtr m, SkoarpusclePtr a, SkoarpusclePtr b) {
    auto o = dynamic_cast<SkoarpuscleBooleanOp&>(*op);
    return o.compare(a, b, m);
}

// --- SkoarpuscleConditional ---------------------------------------------------------
SkoarpuscleConditional::SkoarpuscleConditional(Skoar *skoar, SkoarNoadPtr noad) {

    list<ESkoarNoad::Kind> desires = { ESkoarNoad::cond_if };

    for (auto x : SkoarNoad::collect(noad, desires)) {
        SkoarpionPtr condition;
        SkoarpionPtr if_body;
        SkoarpionPtr else_body;

        auto boolean_expr = SkoarNoad::NewArtificial(L"cond_cond", nullptr);

        auto child = x->children.cbegin();
        auto condition_skoarpuscle = (*child)->next_skoarpuscle();

        boolean_expr->add_noad(*child);

        condition = Skoarpion::NewFromSubtree(skoar, boolean_expr);

        ++child;                   // children[1]
        auto if_noad = *(++child); // children[2]

        if_body = Skoarpion::NewFromSubtree(skoar, if_noad);

        if (x->children.size() >= 4) {
            ++child;                     // children[3]
            auto else_noad = *(++child); // children[4]
            else_body = Skoarpion::NewFromSubtree(skoar, else_noad);
        }
        else {
            else_body = nullptr;
        }

        ifs.push_back(make_tuple(condition, if_body, else_body));

    }
}
	
void SkoarpuscleConditional::on_enter(SkoarMinstrelPtr m) {
	for (auto x : ifs) {
		auto condition = get<0>(x);
		auto if_body   = get<1>(x);
		auto else_body = get<2>(x);

        m->fairy->push_noating();
        //m->koar->do_skoarpion(condition, m, nav, L"inline", nullptr);
        m->fairy->pop_noating();

        auto impression = m->fairy->boolean_impression;

        bool bad_impression = (typeid(*impression) == typeid(SkoarpuscleFalse)) ||
                              (typeid(*impression) == typeid(SkoarpuscleCat));

        if (!bad_impression) {
            //m->koar->do_skoarpion(if_body, m, ["inline"], nullptr);
        }
        else if (else_body != nullptr) {
            //m->koar->do_skoarpion(else_body, m, ["inline"], nullptr);
        }
	}
}

// --- SkoarpuscleTimes ---------------------------------------------------------
void SkoarpuscleTimes::on_enter(SkoarMinstrelPtr m) {
    auto desired_times = m->fairy->cast_arcane_magic();

    if (desired_times->isCounty()) {
        auto times_seen = m->fairy->how_many_times_have_you_seen(this);
        auto times = desired_times->asCount();
        auto x = times_seen % times;
        m->fairy->impress(x != 0);
    }
}


// --- SkoarpuscleLoop ---------------------------------------------------------
SkoarpuscleLoop::SkoarpuscleLoop(Skoar *skoar, SkoarNoadPtr noad) {
    {
        list<ESkoarNoad::Kind> desires = { ESkoarNoad::loop_condition };
        for (auto x : SkoarNoad::collect(noad, desires)) {
            if (x->children.size() > 0) {
                condition = Skoarpion::NewFromSubtree(skoar, x);
            }
        }
    }
    {
        list<ESkoarNoad::Kind> desires = { ESkoarNoad::loop_body };
        for (auto x : SkoarNoad::collect(noad, desires)) {
            body = Skoarpion::NewFromSubtree(skoar, x);
        }
    }

	each = nullptr;
}

// when we send a loop as a message, the receiver
// goes into _each_, then we go into on_enter (see decorating.cpp)
void SkoarpuscleLoop::foreach(SkoarpusclePtr listy) {
    each = listy;
}

void SkoarpuscleLoop::on_enter(SkoarMinstrelPtr m) {

    m->fairy->push_i();
    m->fairy->push_noating(true);

    bool looping = true;
    
    auto f = [&](SkoarpusclePtr element) {
        if (element != nullptr)
            m->fairy->impress(element);

        //m->koar->do_skoarpion(body, m, L"inline", m->fairy->impression);
        m->fairy->incr_i();
        
        if (condition != nullptr) {
            m->fairy->push_noating();
            //m->koar->do_skoarpion(condition, m, L"inline", m->fairy->impression);
            m->fairy->pop_noating();

            auto x = m->fairy->boolean_impression;
            if (typeid(*x) == typeid(SkoarpuscleFalse*) ||
                typeid(*x) == typeid(SkoarpuscleCat*))
                looping = false;
        }

    };

    for (;looping;) {
        if (each == nullptr)
            f(nullptr);
        else
            if (typeid(*each) == typeid(SkoarpuscleList)) {
                auto oEach = dynamic_cast<SkoarpuscleList&>(*each);
                // each->val is a ListOfSkoarpusclesPtr
                for (auto x : *(oEach.val))
                    f(x);
            }
            
        if (condition == nullptr)
            looping = false;
    }
 
}


// --- SkoarpuscleLoopMsg ---------------------------------------------------------
SkoarpuscleLoopMsg::SkoarpuscleLoopMsg(SkoarpusclePtr msg) : val(msg) {
}

// --- SkoarpuscleExprEnd ---------------------------------------------------------
void SkoarpuscleExprEnd::on_enter(SkoarMinstrelPtr m) {
    m->fairy->cast_arcane_magic();
}

// --- SkoarpuscleListSep ---------------------------------------------------------
void SkoarpuscleListSep::on_enter(SkoarMinstrelPtr m) {
    m->fairy->next_listy();
}

// --- SkoarpuscleListEnd ---------------------------------------------------------
SkoarpuscleListEnd::SkoarpuscleListEnd() {}

void SkoarpuscleListEnd::on_enter(SkoarMinstrelPtr m) {
    m->fairy->next_listy();
    m->fairy->pop();
    m->fairy->pop_noating();

}


// --- SkoarpuscleList ---------------------------------------------------------
SkoarpuscleList::SkoarpuscleList() : 
    val(make_shared<ListOfSkoarpuscles>())
{
    noaty = true;
    impressionable = true;
}
SkoarpuscleList::SkoarpuscleList(ListOfSkoarpusclesPtr x) :
    val(x)
{ 
    noaty = true;
    impressionable = true;
}

void SkoarpuscleList::on_enter(SkoarMinstrelPtr m) {
    m->fairy->push_noating(noaty);
    m->fairy->push();
}

bool SkoarpuscleList::isNoatworthy() {
	for (auto x : *val )
		if (!x->isNoatworthy())
			return false;

	return true;
}

shared_ptr<SkoarpuscleList> SkoarpuscleList::mul(SkoarMinstrelPtr m, SkoarpusclePtr y) {
    auto out = make_shared<ListOfSkoarpuscles>();

    for (auto x : *val) {
        //out->push_back(Skoar.ops.multiply_unimpressively(m, x, y));
    }

    return make_shared<SkoarpuscleList>(out);
}

shared_ptr<SkoarpuscleList> SkoarpuscleList::div(SkoarMinstrelPtr, SkoarpusclePtr) {
    auto out = make_shared<ListOfSkoarpuscles>();

    for (auto x : *val) {
        //out->push_back(Skoar.ops.divide_unimpressively(m, y, x));
    }

    return make_shared<SkoarpuscleList>(out);
}

shared_ptr<SkoarpuscleList> SkoarpuscleList::divBy(SkoarMinstrelPtr, SkoarpusclePtr) {
    auto out = make_shared<ListOfSkoarpuscles>();

    for (auto x : *val) {
        //out->push_back(Skoar.ops.divide_unimpressively(m, x, y));
    }

    return make_shared<SkoarpuscleList>(out);
}

SkoarInt SkoarpuscleList::size() {
    return val->size();
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


void *SkoarpuscleList::asNoat() {
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

SkoarpusclePtr SkoarpuscleList::skoar_msg(SkoarpuscleMsg *msg, SkoarMinstrelPtr minstrel) {
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
void SkoarpuscleArgs::on_enter(SkoarMinstrelPtr m) {
    m->fairy->push_noating();
    m->fairy->push();
}

void SkoarpuscleArgs::on_deref_exit(SkoarMinstrelPtr m) {
    m->fairy->pop();
    m->fairy->pop_noating();
}


// --- SkoarpuscleMsg ---------------------------------------------------------
SkoarpuscleMsg::SkoarpuscleMsg(SkoarString v, shared_ptr<SkoarpuscleArgs> a) :
    val(v),
    args(a),
    dest(nullptr) {
}

void SkoarpuscleMsg::on_enter(SkoarMinstrelPtr m) {
    // i don't want to go down this road.
    /* if (args != nullptr) {
        auto x = m->fairy->impression;
        if (typeid(*x) == typeid(SkoarpuscleList)) {
            auto new_args = dynamic_cast<SkoarpuscleList&>(*x);
            // original code:
            // args = m.fairy.impression;
        }
    }*/

    if (dest == nullptr) {
        throw SkoarRuntimeException(L"msg: dest is nullptr");
    }

    SkoarpusclePtr result = nullptr;
    if (typeid(*dest) == typeid(SkoarpuscleList)) {
        // why not this? : result = skoarpuscle_ptr<SkoarpuscleList>(dest)->skoar_msg(this, m);
        result = m->fairy->impression;
        result = skoarpuscle_ptr<SkoarpuscleList>(result)->skoar_msg(this, m);
    } 
    else if (typeid(*dest) == typeid(SkoarpuscleSkoarpion)) {
        result = skoarpuscle_ptr<SkoarpuscleSkoarpion>(dest)->skoar_msg(this, m);
    }
    else if (typeid(*dest) == typeid(SkoarpuscleString)) {
        result = skoarpuscle_ptr<SkoarpuscleString>(dest)->skoar_msg(this, m);
    }
    else if (typeid(*dest) == typeid(SkoarpuscleSymbol)) {
        result = skoarpuscle_ptr<SkoarpuscleSymbol>(dest)->skoar_msg(this, m);
    }
    else if (typeid(*dest) == typeid(SkoarpuscleDeref)) {
        result = skoarpuscle_ptr<SkoarpuscleDeref>(dest)->skoar_msg(this, m);
    }
    else if (typeid(*dest) == typeid(SkoarpuscleMsg)) {
        result = skoarpuscle_ptr<SkoarpuscleMsg>(dest)->skoar_msg(this, m);
    }
    else if (typeid(*dest) == typeid(SkoarpuscleList)) {
        result = skoarpuscle_ptr<SkoarpuscleList>(dest)->skoar_msg(this, m);
    }
    else if (typeid(*dest) == typeid(SkoarpuscleList)) {
        result = skoarpuscle_ptr<SkoarpuscleList>(dest)->skoar_msg(this, m);
    }

    m->fairy->impress(result);

}

SkoarpusclePtr SkoarpuscleMsg::skoar_msg(SkoarpuscleMsg *msg, SkoarMinstrelPtr m) {
    SkoarpusclePtr result = m->fairy->impression;
    if (typeid(*result) == typeid(SkoarpuscleList)) {
        result = skoarpuscle_ptr<SkoarpuscleList>(result)->skoar_msg(this, m);
    }
    else if (typeid(*result) == typeid(SkoarpuscleSkoarpion)) {
        result = skoarpuscle_ptr<SkoarpuscleSkoarpion>(result)->skoar_msg(this, m);
    }
    else if (typeid(*result) == typeid(SkoarpuscleString)) {
        result = skoarpuscle_ptr<SkoarpuscleString>(result)->skoar_msg(this, m);
    }
    else if (typeid(*result) == typeid(SkoarpuscleSymbol)) {
        result = skoarpuscle_ptr<SkoarpuscleSymbol>(result)->skoar_msg(this, m);
    }
    else if (typeid(*result) == typeid(SkoarpuscleDeref)) {
        result = skoarpuscle_ptr<SkoarpuscleDeref>(result)->skoar_msg(this, m);
    }
    else if (typeid(*result) == typeid(SkoarpuscleMsg)) {
        result = skoarpuscle_ptr<SkoarpuscleMsg>(result)->skoar_msg(this, m);
    }
    else if (typeid(*result) == typeid(SkoarpuscleList)) {
        result = skoarpuscle_ptr<SkoarpuscleList>(result)->skoar_msg(this, m);
    }
    else if (typeid(*result) == typeid(SkoarpuscleList)) {
        result = skoarpuscle_ptr<SkoarpuscleList>(result)->skoar_msg(this, m);
    }

    return m->fairy->impress(result);
}

list<SkoarString> SkoarpuscleMsg::get_msg_arr(SkoarMinstrelPtr m) {
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

list<SkoarString> SkoarpuscleMsg::get_args_from_prototype(SkoarMinstrelPtr m) {
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
SkoarpuscleMsgName::SkoarpuscleMsgName(SkoarString s) : val(s) {}

// --- SkoarpuscleMsgNameWithArgs ---------------------------------------------------------
SkoarpuscleMsgNameWithArgs::SkoarpuscleMsgNameWithArgs(SkoarString s) : val(s) {}

void SkoarpuscleMsgNameWithArgs::on_enter(SkoarMinstrelPtr m) {
    m->fairy->push_noating();
    m->fairy->push();
}

// -----------------------------
// musical keywords skoarpuscles
// -----------------------------

// --- SkoarpuscleBars ---------------------------------------------------------
SkoarpuscleBars::SkoarpuscleBars(SkoarToke *toke) :
    val(toke->lexeme)
{
    auto n = val.length() - 1;
    pre_repeat = val.at(0) == L':';
    post_repeat = val.at(n) == L':';
}

// todo: this is badness.
void SkoarpuscleBars::on_enter(SkoarMinstrelPtr m) {
	// :|
	if (pre_repeat == true) {
		/*auto burned = m->koar->state_at("colons_burned");

        if (m->fairy->how_many_times_have_you_seen(this) < 2) {
            nav.(\nav_colon);
        }

		if (burned.falseAt(noad)) {
			burned[noad] = true;
			throw SkoarNav(SkoarNav::COLON);
		}
		*/
	}

	// |:
	if (post_repeat == true) {
		//m->koar->state_put("colon_seen", noad);
	}
//};
}

// --- SkoarpuscleFine ---------------------------------------------------------
SkoarpuscleFine::SkoarpuscleFine() {
	//on_enter = [](SkoarMinstrelPtr m) {
		/*if (m->koar->state_at("al_fine")->val == true) {
			//debug("fine");
			throw new SkoarNav(SkoarNav::FINE);
		}	 */
	//};
}


// --- SkoarpuscleSegno ---------------------------------------------------------
SkoarpuscleSegno::SkoarpuscleSegno(SkoarNoadPtr nod, SkoarToke *toke) {
	auto s = &toke->lexeme;
	auto n = s->length();

	noad = nod;

	// ,segno`label`
	/*if (n > 8) {
		s[6..n - 2].asSymbol;
		} {
		\segno
		};
		val = s[1..n].asSymbol;	 */

	//on_enter = [](SkoarMinstrelPtr m) {
		//m->koar->state_put("segno_seen", noad);
	//};
}


// --- SkoarpuscleGoto ---------------------------------------------------------
SkoarpuscleGoto::SkoarpuscleGoto(SkoarNoadPtr noad) {

/*	auto toke = noad->children[0]->next_toke();
	auto al_x = noad->children[1];

	nav_cmd = case {toke.isKindOf(Toke_DaCapo)} {\nav_da_capo}
			{toke.isKindOf(Toke_DalSegno)} {\nav_segno};

			al_fine = false;
			if (al_x.notNil) {
				if (al_x.next_toke.isKindOf(Toke_AlFine)) {
					al_fine = true;
				};
			};

	on_enter = [this](SkoarMinstrelPtr m) {
		if (this->al_fine == true) {
			m->koar->state_put("al_fine", true);
		};

		m->reset_colons();
		//"goto:".post; nav_cmd.postln;
		//nav.(nav_cmd);
	};
*/
}


// --- SkoarpuscleCarrots ---------------------------------------------------------
SkoarpuscleCarrots::SkoarpuscleCarrots(SkoarToke *toke) :
    val(toke->lexeme.length())
{
}

// --- SkoarpuscleTuplet ---------------------------------------------------------
SkoarpuscleTuplet::SkoarpuscleTuplet(SkoarToke *toke) :
    val(toke->lexeme.length())
{
}

// --- SkoarpuscleDynamic ---------------------------------------------------------

inline SkoarInt decode_skoar_dynamic(SkoarString &s) {
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
    return 0;
}

SkoarpuscleDynamic::SkoarpuscleDynamic(SkoarToke *toke) :
    val(decode_skoar_dynamic(toke->lexeme))
{
}

SkoarFloat SkoarpuscleDynamic::amp() { return val / 8.0; }

// --- SkoarpuscleOctaveShift ---------------------------------------------------------
inline const SkoarInt decode_skoar_octave_shift(SkoarToke *toke) {
    auto f = [&]() {
        auto s = toke->lexeme;
        auto n = s.length() - 1;

        if (s.at(0) == L'o') {
            n = n * -1;
        }
        return n;
    };

    switch (toke->kind) {
    case ESkoarToke::OctaveShift:
        return f();
    case ESkoarToke::OttavaA:
        return 1;
    case ESkoarToke::OttavaB:
        return -1;
    case ESkoarToke::QuindicesimaA:
        return 2;
    case ESkoarToke::QuindicesimaB:
        return -2;
    };
    return 0;
}

SkoarpuscleOctaveShift::SkoarpuscleOctaveShift(SkoarToke *toke) :
    val(decode_skoar_octave_shift(toke))
{
}

void SkoarpuscleOctaveShift::on_enter(SkoarMinstrelPtr m) {
    /* todo: porting done, uncomment when koar exists
    auto octave = m->koar[L"octave"];
    SkoarInt x = 5;
    if (octave != nullptr)
        x = skoarpuscle_ptr<SkoarpuscleInt>(octave)->val;

    m->koar[L"octave"] = make_skoarpuscle(x + val);
    */
}
// --- SkoarpuscleVoice ---------------------------------------------------------
SkoarpuscleVoice::SkoarpuscleVoice(SkoarToke *toke) :
    val(toke->lexeme.substr(1))
{
}

// --- SkoarpuscleHashLevel ---------------------------------------------------------
inline SkoarFloat decode_skoar_hashlevel(SkoarString &lex) {
    SkoarFloat n = -2.0;
    SkoarFloat i = 0;
    for (auto c : lex) {
        n += 1.0;
        if (c == L'#')
            i += 1.0;
    }

    if (n <= 0.0)
        return 0.0;
    return i / n;
}

SkoarpuscleHashLevel::SkoarpuscleHashLevel(SkoarString lex) :
    val(decode_skoar_hashlevel(lex))
{
    impressionable = true;
    noatworthy = false;
}

// --- SkoarpusclePair ---------------------------------------------------------
SkoarpusclePair::SkoarpusclePair(SkoarpusclePtr k, SkoarpusclePtr v) :
    val(make_pair(k,v))
{}

void SkoarpusclePair::assign(SkoarMinstrelPtr m) {
    m->fairy->push_noating();

    /*x = if (val.isKindOf(SkoarpuscleExpr)) {
        val.flatten(m)
    } {
        val
    };*/
    //Skoar.ops.assign(m, val.second(), val.first());

    m->fairy->pop_noating();
}

// --- SkoarpuscleExpr ---------------------------------------------------------
SkoarpuscleExpr::SkoarpuscleExpr(SkoarNoadPtr noad) {
    // val = noad;
    result = nullptr;
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

