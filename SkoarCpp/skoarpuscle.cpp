#include "skoarpuscle.hpp"

#include "lex.hpp"
#include "minstrel.hpp"
#include "fairy.hpp"
#include "skoar.hpp"
#include "koar.hpp"
#include "noad.hpp"
#include "skoarpion.hpp"
#include "skoarpion_skoarpuscle.hpp"



// Skoarpuscles are the closest thing we have to "types".
//
// They represent value types, as well as most things that
// can be spoken of as things, like a statement, boolean expression, etc.
//

// --- SkoarpuscleUnknown ---------------------------------------------------------
SkoarpuscleUnknown::SkoarpuscleUnknown() {}

// --- SkoarpuscleCat ---------------------------------------------------------
SkoarpuscleCat::SkoarpuscleCat() {}

void SkoarpuscleCat::on_enter(SkoarMinstrelPtr m) { m->fairy->impress(make_shared<SkoarpuscleCat>()); }

// --- SkoarpuscleTrue ---------------------------------------------------------
SkoarpuscleTrue::SkoarpuscleTrue() {
    val = true;
    impressionable = true;
}

void SkoarpuscleTrue::on_enter(SkoarMinstrelPtr m) { m->fairy->impress(make_shared<SkoarpuscleTrue>()); }

// --- SkoarpuscleFalse ---------------------------------------------------------
SkoarpuscleFalse::SkoarpuscleFalse() {
    val = false;
    impressionable = true;
}


void SkoarpuscleFalse::on_enter(SkoarMinstrelPtr m) { m->fairy->impress(make_shared<SkoarpuscleFalse>()); }

// --- SkoarpuscleInt ---------------------------------------------------------
SkoarpuscleInt::SkoarpuscleInt(SkoarInt v) {
    val = v;
    noatworthy = true;
    impressionable = true;
}

void SkoarpuscleInt::on_enter(SkoarMinstrelPtr m) { m->fairy->impress(make_shared<SkoarpuscleInt>(val.extract<SkoarInt>())); }

void *SkoarpuscleInt::asNoat() { return nullptr; }


// --- SkoarpuscleFloat ---------------------------------------------------------
SkoarpuscleFloat::SkoarpuscleFloat(SkoarFloat v) { 
    val = v; 
    noatworthy = true;
    impressionable = true;
}

void SkoarpuscleFloat::on_enter(SkoarMinstrelPtr m) { m->fairy->impress(make_shared<SkoarpuscleFloat>(val.extract<SkoarFloat>())); }
void *SkoarpuscleFloat::asNoat() { return nullptr; }

// --- SkoarpuscleFreq ---------------------------------------------------------
SkoarpuscleFreq::SkoarpuscleFreq(SkoarString lexeme) { 
    val = stod(lexeme.substr(0,lexeme.length() - 3));
    noatworthy = true;
    impressionable = true;
} 

void SkoarpuscleFreq::on_enter(SkoarMinstrelPtr m) { m->fairy->impress(make_shared<SkoarpuscleFreq>(val.extract<SkoarString>())); }

void *SkoarpuscleFreq::asNoat() { return nullptr;
	//return new SkoarNoat_Freq(val.asFloat);
}

// --- SkoarpuscleNoat ---------------------------------------------------------
SkoarpuscleNoat::SkoarpuscleNoat(SkoarString&) {
    noatworthy = true;
    impressionable = true;
}
	
void *SkoarpuscleNoat::asNoat() { return nullptr; }

// --- SkoarpuscleChoard ---------------------------------------------------------
SkoarpuscleChoard::SkoarpuscleChoard(SkoarString&) {
    noatworthy = true;
    impressionable = true;
}

void *SkoarpuscleChoard::asNoat() { return nullptr; }
		
// --- SkoarpuscleString ---------------------------------------------------------
SkoarpuscleString::SkoarpuscleString(SkoarString s) {
    val = s;
    impressionable = true;
}

void SkoarpuscleString::on_enter(SkoarMinstrelPtr m) { m->fairy->impress(make_shared<SkoarpuscleString>(val.extract<SkoarString>())); }
SkoarpusclePtr SkoarpuscleString::skoar_msg(SkoarpuscleMsg *msg, SkoarMinstrelPtr minstrel) {
    auto sel = msg->val.extract<SkoarString>();

    //if (sel == L"sample") {
    //    return make_shared<SkoarpuscleSample>(val.extract<SkoarString>());
    //}
    return make_shared<SkoarpuscleCat>();
}

// --- SkoarpuscleSymbolName ---------------------------------------------------------
SkoarpuscleSymbolName::SkoarpuscleSymbolName(SkoarString s) {
    val = s;
}

// --- SkoarpuscleSymbol ---------------------------------------------------------
SkoarpuscleSymbol::SkoarpuscleSymbol(SkoarString s) { 
    val = s; 
    impressionable = true;
}

void SkoarpuscleSymbol::on_enter(SkoarMinstrelPtr m) { m->fairy->impress(make_shared<SkoarpuscleSymbol>(val.extract<SkoarString>())); }

SkoarpusclePtr SkoarpuscleSymbol::skoar_msg(SkoarpuscleMsg *msg, SkoarMinstrelPtr minstrel) {
    
    /* this was how we called underlying SC class methods.. 
       don't know what I want to do with this anymore. */

    return make_shared<SkoarpuscleCat>();
}

// --- SkoarpuscleSymbolColon ---------------------------------------------------------
SkoarpuscleSymbolColon::SkoarpuscleSymbolColon(SkoarString lex) {
    impressionable = true;
    // lexeme was matched by: [a-zA-Z0-9_][a-zA-Z0-9_]*[ \t]*:(?![:|}])
    // ... so we'll remove anything that's not [a-zA-Z0-9_]
    std::wregex expr(L"([^a-zA-Z0-9_]+)"); 
    val = std::regex_replace(lex, expr, L"");
}

// --- SkoarpuscleDeref ---------------------------------------------------------
SkoarpuscleDeref::SkoarpuscleDeref(SkoarString v, SkoarpusclePtr a) {
	val = v;
	args = a; // is actually shared_ptr<SkoarpuscleArgs>
}

SkoarpusclePtr SkoarpuscleDeref::lookup(SkoarMinstrelPtr minstrel) {
	//return minstrel->koar[val.extract<SkoarString>];
    return make_shared<SkoarpuscleCat>();
}

Poco::DynamicAny SkoarpuscleDeref::flatten(SkoarMinstrelPtr m) {
    return lookup(m)->flatten(m);
}

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
        m->fairy->impress(make_shared<SkoarpuscleCat>());
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
SkoarpuscleMathOp::SkoarpuscleMathOp(SkoarToke *toke) {
	auto s = toke->lexeme;
    val = s;
    
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
	val = &toke->lexeme;

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

}

bool SkoarpuscleBooleanOp::compare(SkoarpusclePtr a, SkoarpusclePtr b, SkoarMinstrelPtr m) {
	
    // todo: when using ops table, don't do these two lines
    auto x = a->flatten(m).extract<SkoarInt>();
    auto y = b->flatten(m).extract<SkoarInt>();

    return f(x, y);
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

        bool imp = impression->val;

        if (imp) {
            //m->koar->do_skoarpion(if_body, m, ["inline"], nullptr);
        }
        else if (else_body != nullptr) {
            //m->koar->do_skoarpion(else_body, m, ["inline"], nullptr);
        }
	}
}


// ----------------------------------------------
// ----------------------------------------------
// ----------------------------------------------
// porting here
// ----------------------------------------------
// ----------------------------------------------
// ----------------------------------------------



// --- SkoarpuscleTimes ---------------------------------------------------------
SkoarpuscleTimes::SkoarpuscleTimes() {}

// --- SkoarpuscleLoop ---------------------------------------------------------
SkoarpuscleLoop::SkoarpuscleLoop(Skoar *skoar, SkoarNoadPtr noad) {

    val = make_shared<ListOfSkoarpuscles>();
	/*for (auto x : noad->collect("loop_condition")) {
		if (x->children.size != 0) {
			condition = x.children[1].next_skoarpuscle();
		}
	}

	for (auto x : noad.collect("loop_body")) {
		body = Skoarpion::new_from_subtree(skoar, x);
	}	*/


	each = nullptr;

    // todo

}

// when we send a loop as a message, the receiver
// goes into _each_ and _this_ becomes the new receiver.
SkoarpusclePtr SkoarpuscleLoop::foreach(SkoarpusclePtr listy) {
	//each = val.List;
	//return this;
    return nullptr;
}


// --- SkoarpuscleLoopMsg ---------------------------------------------------------
SkoarpuscleLoopMsg::SkoarpuscleLoopMsg() {}
SkoarpuscleLoopMsg::SkoarpuscleLoopMsg(SkoarpusclePtr msg) {
	val = msg;
}


// --- SkoarpuscleExprEnd ---------------------------------------------------------
SkoarpuscleExprEnd::SkoarpuscleExprEnd() {}

void SkoarpuscleExprEnd::on_enter(SkoarMinstrelPtr m) {
    m->fairy->cast_arcane_magic();
}

// --- SkoarpuscleListSep ---------------------------------------------------------
SkoarpuscleListSep::SkoarpuscleListSep() {}

void SkoarpuscleListSep::on_enter(SkoarMinstrelPtr m) {
    m->fairy->next_listy();
}

// --- SkoarpuscleListEnd ---------------------------------------------------------
SkoarpuscleListEnd::SkoarpuscleListEnd() {}

void SkoarpuscleListEnd::on_enter(SkoarMinstrelPtr m) {
    m->fairy->next_listy();
    m->fairy->pop();
}

// --- SkoarpuscleList ---------------------------------------------------------
SkoarpuscleList::SkoarpuscleList() { 
    val = make_shared<ListOfSkoarpuscles>();
    noaty = true;
    impressionable = true;
}
SkoarpuscleList::SkoarpuscleList(ListOfSkoarpusclesPtr x) { 
    val = x; 
    noaty = true;
}

void SkoarpuscleList::on_enter(SkoarMinstrelPtr m) {
    m->fairy->push_noating(noaty);
    m->fairy->push();
}

bool SkoarpuscleList::isNoatworthy() {
    auto list = val.extract<ListOfSkoarpusclesPtr>();
	for (auto x : *list )
		if (!x->isNoatworthy())
			return false;

	return true;
}

void *SkoarpuscleList::asNoat() {

    auto listy = val.extract<ListOfSkoarpusclesPtr>();
    auto n = listy->size();
	auto noats = new void*[n];
	auto i = -1;

	for (auto x : *listy) {
		noats[++i] = x->asNoat();
	}

	return nullptr;
	//return new SkoarNoat_DegreeList(noats);
}

SkoarpusclePtr SkoarpuscleList::skoar_msg(SkoarpuscleMsg *msg, SkoarMinstrelPtr minstrel) {
	//auto o = msg->get_msg_arr(minstrel);
    SkoarString name = msg->val;
	Skoarpuscle *ret = nullptr;

	if (name == L"next") {
		//ret = val.performMsg(o);
	}
	else if (name == L"last") {
		//ret = val.performMsg(o);
	} 
	else {
		//ret = val.performMsg(o);
	}

	return nullptr;
	//return new Skoarpuscle.wrap(ret);
}




// --- SkoarpuscleArgs ---------------------------------------------------------
SkoarpuscleArgs::SkoarpuscleArgs() {}

// --- SkoarpuscleArgSpec ---------------------------------------------------------
// {! f<a,b,c> !! '[\a,\b,\c] is the ArgsSpec' !}
SkoarpuscleArgSpec::SkoarpuscleArgSpec() {
    val = make_shared<ListOfSkoarpuscles>();
}

SkoarpuscleArgSpec::SkoarpuscleArgSpec(SkoarNoadPtr noad) {
	val = make_shared<ListOfSkoarpuscles>();
	
	/*for (auto x : *(noad->collect_skoarpuscles())) {
		if (typeid(x) == typeid(SkoarpuscleSymbolName*)) {
			val.List->emplace_back(x);
		}
	} */
}

// --- SkoarpuscleMsg ---------------------------------------------------------
SkoarpuscleMsg::SkoarpuscleMsg() { args = nullptr; }
	
SkoarpuscleMsg::SkoarpuscleMsg(SkoarString v, shared_ptr<SkoarpuscleArgs> a) {
	val = v;
	args = a;
}

/*SkoarpuscleMsg::get_msg_arr(SkoarMinstrelPtr m) {
	auto x = Array.newClear(args.size + 1);
	auto i = 0;

	x[0] = val;
	args.flatten(m).do( y ) {
			i = i + 1;
		x[i] = y;
	};
	return x;
}  */

// --- SkoarpuscleMsgName ---------------------------------------------------------
SkoarpuscleMsgName::SkoarpuscleMsgName(SkoarString s) { val = s; }

// --- SkoarpuscleMsgNameWithArgs ---------------------------------------------------------
SkoarpuscleMsgNameWithArgs::SkoarpuscleMsgNameWithArgs(SkoarString s) { val = s; }

// -----------------------------
// musical keywords skoarpuscles
// -----------------------------

// --- SkoarpuscleBars ---------------------------------------------------------
SkoarpuscleBars::SkoarpuscleBars(SkoarToke *toke) {

    auto lex = &toke->lexeme;
	val = lex;
	auto n = lex->length() - 1;
	bool pre_repeat = lex->at(0) == L':';
	bool post_repeat = lex->at(n) == L':';

	//on_enter = [pre_repeat, post_repeat](SkoarMinstrelPtr m) {

		// :|
		if (pre_repeat == true) {
			/*auto burned = m->koar->state_at("colons_burned");

			if (burned.falseAt(noad)) {
				burned[noad] = true;
				throw new SkoarNav(SkoarNav::COLON);
			};
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
		/*if (m->koar->state_at("al_fine")->val.Bool == true) {
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
SkoarpuscleCarrots::SkoarpuscleCarrots(SkoarToke *toke) { val = toke->lexeme.length(); }

// --- SkoarpuscleTuplet ---------------------------------------------------------
SkoarpuscleTuplet::SkoarpuscleTuplet(SkoarToke *toke) { val = toke->lexeme.length(); }
			



// --- SkoarpuscleDynamic ---------------------------------------------------------
SkoarpuscleDynamic::SkoarpuscleDynamic(SkoarToke *toke) {
	auto s = &toke->lexeme;

	/*val = switch (*s)
	{
		"ppp"
	}     {1}
	{"pppiano"} {1}
	{"pp"}      {2}
	{"ppiano"}  {2}
	{"p"}       {3}
	{"piano"}   {3}
	{"mp"}      {4}
	{"mpiano"}  {4}
	{"mf"}      {5}
	{"mforte"}  {5}
	{"forte"}   {6}
	{"ff"}      {7}
	{"fforte"}  {7}
	{"fff"}     {8}
	{"ffforte"} {8};
		*/
	//on_enter = [this](SkoarMinstrelPtr m) {
		//m->koar["amp"] = this->amp();
	//};
}

SkoarFloat SkoarpuscleDynamic::amp() { return val.extract<SkoarFloat>() / 8.0; }

// --- SkoarpuscleOctaveShift ---------------------------------------------------------
SkoarpuscleOctaveShift::SkoarpuscleOctaveShift(SkoarToke *toke) {
	/*auto f = {
		auto s = toke.lexeme;
		auto n = s.size - 1;

		if (s.beginsWith("o")) {
			n = n * -1;
		};
		n
	};

	val = case {toke.isKindOf(Toke_OctaveShift)} {f.()}
		{toke.isKindOf(Toke_OttavaA)}       { 1}
		{toke.isKindOf(Toke_OttavaB)}       {-1}
		{toke.isKindOf(Toke_QuindicesimaA)} { 2}
		{toke.isKindOf(Toke_QuindicesimaB)} {-2};  */

	//on_enter = [](SkoarMinstrelPtr m) {
		//auto octave = m->koar[\octave] ? ? 5;
		//m->koar[\octave] = octave + val;
	//};
}

// --- SkoarpuscleVoice ---------------------------------------------------------
SkoarpuscleVoice::SkoarpuscleVoice(SkoarToke *toke) {
	auto s = &toke->lexeme;
	auto n = s->length() - 1;
	//val = s[1..n];
}

// --- SkoarpuscleHashLevel ---------------------------------------------------------
SkoarpuscleHashLevel::SkoarpuscleHashLevel(SkoarString lex) {}


// --- SkoarpusclePair ---------------------------------------------------------
SkoarpusclePair::SkoarpusclePair(SkoarpusclePtr k, SkoarpusclePtr v) {}



// --- SkoarpuscleExpr ---------------------------------------------------------
SkoarpuscleExpr::SkoarpuscleExpr(SkoarNoadPtr noad) {
    result = nullptr;
}

