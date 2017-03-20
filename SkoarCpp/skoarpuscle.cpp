#include "skoarpuscle.hpp"

#include "lex.hpp"
#include "minstrel.hpp"
#include "fairy.hpp"
#include "skoar.hpp"
#include "koar.hpp"
#include "noad.hpp"
#include "skoarpion.hpp"


// Skoarpuscles are the closest thing we have to "types".
//
// They represent value types, as well as most things that
// can be spoken of as things, like a statement, boolean expression, etc.
//


// --- Skoarpuscle ---------------------------------------------------------
Skoarpuscle::Skoarpuscle() : val(nullptr) {
}

// --- SkoarpuscleUnknown ---------------------------------------------------------
SkoarpuscleUnknown::SkoarpuscleUnknown() {
}

// --- SkoarpuscleCat ---------------------------------------------------------
SkoarpuscleCat::SkoarpuscleCat() {
    
}

// --- SkoarpuscleTrue ---------------------------------------------------------
SkoarpuscleTrue::SkoarpuscleTrue() {
    val = true;
}

// --- SkoarpuscleFalse ---------------------------------------------------------
SkoarpuscleFalse::SkoarpuscleFalse() {
    val = false;
}

/*asString{ "=^.^=" }
skoar_msg{}
flatten{ return nil }
*/	

// --- SkoarpuscleInt ---------------------------------------------------------
SkoarpuscleInt::SkoarpuscleInt(SkoarInt v) {
	val = v;

	on_enter = [v](SkoarMinstrel *m) {
		m->fairy->impress(make_shared<SkoarpuscleInt>(v));
	};
}

bool SkoarpuscleInt::isNoatworthy() { return true; }

void *SkoarpuscleInt::asNoat() {
	return nullptr;//return new SkoarNoat_Degree(val.asInteger);
}


// --- SkoarpuscleFloat ---------------------------------------------------------
SkoarpuscleFloat::SkoarpuscleFloat(SkoarFloat v) {
	val = v;
	on_enter = [v](SkoarMinstrel *m) {
		m->fairy->impress(make_shared<SkoarpuscleFloat>(v));
	};
}

bool SkoarpuscleFloat::isNoatworthy() { 
	return true; 
}

void *SkoarpuscleFloat::asNoat() {
	return nullptr;//return new SkoarNoat_Degree(val.asInteger);
}

//double SkoarpuscleFloat::flatten(SkoarMinstrel *m) {
//	return val.Float;
//}

//void SkoarpuscleFloat::



// --- SkoarpuscleFreq ---------------------------------------------------------
SkoarpuscleFreq::SkoarpuscleFreq(SkoarString lexeme) {
	val = lexeme; // todo chop off Hz
	
	on_enter = [lexeme](SkoarMinstrel *m) {
		m->fairy->impress(make_shared<SkoarpuscleFreq>(lexeme));
	};
}

bool SkoarpuscleFreq::isNoatworthy() { 
	return false; 
} // todo

void *SkoarpuscleFreq::asNoat() {
	return nullptr;
	//return new SkoarNoat_Freq(val.asFloat);
}



// --- SkoarpuscleNoat ---------------------------------------------------------
SkoarpuscleNoat::SkoarpuscleNoat(SkoarString&) {
}
	
bool SkoarpuscleNoat::isNoatworthy() {
	return true;
}

void *SkoarpuscleNoat::asNoat() {
	return nullptr;
}

// --- SkoarpuscleChoard ---------------------------------------------------------
SkoarpuscleChoard::SkoarpuscleChoard(SkoarString&) {
}

bool SkoarpuscleChoard::isNoatworthy() {
	return true;
}

void *SkoarpuscleChoard::asNoat() {
	return nullptr;
}
			



// --- SkoarpuscleString ---------------------------------------------------------
SkoarpuscleString::SkoarpuscleString(SkoarString s) {
	val = s;
	on_enter = [s](SkoarMinstrel *m) {
		m->fairy->impress(make_shared<SkoarpuscleString>(s));
	};
}


// --- SkoarpuscleSymbolName ---------------------------------------------------------
SkoarpuscleSymbolName::SkoarpuscleSymbolName(SkoarString s) {
	val = s;
	on_enter = [s](SkoarMinstrel *m) {
		m->fairy->impress(make_shared<SkoarpuscleSymbolName>(s));
	};
}

// --- SkoarpuscleSymbol ---------------------------------------------------------
SkoarpuscleSymbol::SkoarpuscleSymbol(SkoarString s) {
	val = s;
	on_enter = [s](SkoarMinstrel *m) {
		m->fairy->impress(make_shared<SkoarpuscleSymbol>(s));
	};
}


Skoarpuscle *SkoarpuscleSymbol::skoar_msg(SkoarpuscleMsg *msg, SkoarMinstrel *minstrel) {
	//auto o = msg.get_msg_arr(minstrel);
	//auto ret = val.performMsg(o);

	//return new Skoarpuscle.wrap(ret);
	return nullptr;
}

// --- SkoarpuscleSymbolColon ---------------------------------------------------------
SkoarpuscleSymbolColon::SkoarpuscleSymbolColon(SkoarString lex) {

    // lexeme was matched by: [a-zA-Z0-9_][a-zA-Z0-9_]*[ \t]*:(?![:|}])
    
    //var regex = "[a-zA-Z0-9_][a-zA-Z0-9_]*";
    //val = lex.findRegexpAt(regex, 0)[0].asSymbol;

    //("SSC :: init :: lex:" ++ lex ++ " val:" ++ val.asString).postln; 

    //impressionable = true;

}

// --- SkoarpuscleDeref ---------------------------------------------------------
SkoarpuscleDeref::SkoarpuscleDeref(SkoarString v, shared_ptr<SkoarpuscleArgs> a) {
	val = v;
	args = a;
	
	on_enter = [this](SkoarMinstrel *m) {
		auto x = this->lookup(m);

		//"deref:on_enter: SYMBOL LOOKEDUP : ".post; val.post; " ".post; x.postln;
		/*x = Skoarpuscle::wrap(x);

		if (x.isKindOf(SkoarpuscleSkoarpion)) {
		    m->koar.do_skoarpion(x.val, m, msg_arr, m->fairy->impression);
		} {
		    m->fairy->impress(x);
		};*/
	};
}

SkoarpusclePtr SkoarpuscleDeref::lookup(SkoarMinstrel* minstrel) {
	//return m->koar[val];
	return nullptr;
}
/*
SkoarpuscleDeref::flatten(m) {
	return this.lookup(m);
}

SkoarpusclePtr SkoarpuscleDeref::skoar_msg(SkoarpuscleMsg *msg, SkoarMinstrel *minstrel) {

	auto ret = val;
	auto x = this->lookup(minstrel);

	//"deref:skoar_msg: SYMBOL LOOKEDUP : ".post; val.post; " ".post; x.postln;
	//msg_arr = msg->get_msg_arr(minstrel);

	if (typeid(x) == typeid(SkoarpuscleSkoarpion*)) {
		return this;
	};

	// we don't recognise that name, did they mean a SuperCollider class?
	if (x == nullptr) {
		//x = val.asClass;
	};

	if (x != nullptr) {
		if (typeid(x) == typeid(SkoarpuscleString*)) {
			//x = x.val;
		};
		//ret = x.performMsg(msg_arr);
	};

	return nullptr;
	//return Skoarpuscle.wrap(ret);
}
*/

// --- SkoarpuscleMathOp ---------------------------------------------------------
SkoarpuscleMathOp::SkoarpuscleMathOp(SkoarToke *toke) {
	val = &toke->lexeme;

	/*f = switch (val)
	{
		"+"
	}  {{
			| minstrel, a, b |
				Skoar.ops.add(minstrel, a, b);
		}}

		{"x"}  {{
				| minstrel, a, b |
					Skoar.ops.multiply(minstrel, a, b);
			}}

		{"-"}  {{
				| minstrel, a, b |
					// todo minstrel.skoar.ops.sub(minstrel, a, b);
			}};	 */
}

void SkoarpuscleMathOp::calculate(SkoarMinstrel *m, Skoarpuscle* left, Skoarpuscle *right) {

	// the result is impressed by the operation
	f(m, left, right);
}

// --- SkoarpuscleBooleanOp ---------------------------------------------------------
SkoarpuscleBooleanOp::SkoarpuscleBooleanOp(SkoarNoadPtr noad, SkoarToke *toke) {
	val = &toke->lexeme;

	// ==|!=|<=|>=|in|nin|and|or|xor
	/*f = switch (val)
	{
		"=="
	}  {{
			| a, b |
				a == b
		}}
		{"!="}  {{
				| a, b |
					a != b
			}}
		{"<="}  {{
				| a, b |
					a <= b
			}}
		{"<"}  {{
				| a, b |
					a < b
			}}
		{">="}  {{
				| a, b |
					a >= b
			}}
		{">"}  {{
				| a, b |
					a < b
			}}
		{"and"} {{
				| a, b |
					a and : b
			}}
		{"or"}  {{
				| a, b |
					a or : b
			}}
		{"xor"} {{
				| a, b |
					a xor : b
			}};
			*/

}

bool SkoarpuscleBooleanOp::compare(Skoarpuscle *a, Skoarpuscle *b, SkoarMinstrel *m) {
	/*auto x;
	auto y;

	a.on_enter(m);
	x = m->fairy->impression;

	b.on_enter(m);
	y = m->fairy->impression;

	if (x.isKindOf(Skoarpuscle)) {
		debug(x);
		x = x.flatten(m);
	};

	if (y.isKindOf(Skoarpuscle)) {
		debug(y);
		y = y.flatten(m);
	};
		*/
	//debug("{? " ++x.asString++ " " ++val++ " " ++y.asString++ " ?}");

	//x !? y !? {return f.(x, y)};

	return false;
}


// --- SkoarpuscleBoolean ---------------------------------------------------------
SkoarpuscleBoolean::SkoarpuscleBoolean(SkoarNoadPtr noad) {
	// a and b are exprs
	/*a = noad.children[0];
	op = noad.children[1].next_skoarpuscle;
	b = noad.children[2];

	noad.children = [];	  */
}

bool SkoarpuscleBoolean::evaluate(SkoarMinstrel *m) {
	return false;
	//return op->compare(a, b, m);
}



// --- SkoarpuscleConditional ---------------------------------------------------------
SkoarpuscleConditional::SkoarpuscleConditional() {
}


SkoarpuscleConditional::SkoarpuscleConditional(Skoar *skoar, SkoarNoadPtr noad) {

    ifs = make_shared<ListOfSkoarpuscles>();
	/*
	for (auto x : noad->collect("cond_if")) {
		auto condition = x->children.front()->next_skoarpuscle();
		Skoarpion *if_body;
		Skoarpion *else_body;

		if_body = Skoarpion::new_from_subtree(skoar, x.children[2]);

		else_body = x.children[4];
		if (else_body != nullptr) {
			else_body = Skoarpion::new_from_subtree(skoar, else_body);
		};

		ifs.emplace_back([condition, if_body, else_body]);
	};
	*/
	on_enter = [this](SkoarMinstrel *m) {

		/*for (auto x : *this->ifs) {
			auto c = x[0];
			auto i = x[1];
			auto e = x[2];

			m->koar->do_skoarpion(
				(c->evaluate(m) ? i : e),
				m, ["inline"], nullptr
				);
		}*/
	};
}


// --- SkoarpuscleTimes ---------------------------------------------------------
SkoarpuscleTimes::SkoarpuscleTimes() {

}

// --- SkoarpuscleLoop ---------------------------------------------------------
SkoarpuscleLoop::SkoarpuscleLoop(Skoar *skoar, SkoarNoadPtr noad) {

    val = make_shared<std::list<Skoarpuscle>>();
	/*for (auto x : noad->collect("loop_condition")) {
		if (x->children.size != 0) {
			condition = x.children[1].next_skoarpuscle();
		}
	}

	for (auto x : noad.collect("loop_body")) {
		body = Skoarpion::new_from_subtree(skoar, x);
	}	*/


	each = nullptr;

	on_enter = [this](SkoarMinstrel *m) {
		/*
		auto i = 0;

		m->koar["i"] = 0;

		bool looping = true;
		while (looping) {

			SpellOfSkoarpucles f =

				[this, m, &looping](Skoarpuscle *element) {

				// this is how we foreach
				if (element->on_enter) {
					element->on_enter(m);
				}
				//"eh?".postln;
				//m->koar->do_skoarpion(body, m, ["inline"], m->fairy->impression);


				//m->koar["i"] = ++i;

				if (this->condition != nullptr) {
					if (this->condition->evaluate(m) == false) {
						looping = false;
					}
				}

			};

			if (this->each == nullptr) {
				f(nullptr);
			} else {
				//debug("each: " ++each.asString);
				for (auto element : *each) {
					//debug("each:el: " ++element.asString);
					f(element);
				}
			}

			if (this->condition == nullptr) {
				this->looping = false;
			}
		}	*/
	};

}

// when we send a loop as a message, the receiver
// goes into _each_ and _this_ becomes the new receiver.
SkoarpuscleLoop *SkoarpuscleLoop::foreach(SkoarpuscleList *listy) {
	//each = val.List;
	return this;
}


// --- SkoarpuscleLoopMsg ---------------------------------------------------------
SkoarpuscleLoopMsg::SkoarpuscleLoopMsg() {
}

SkoarpuscleLoopMsg::SkoarpuscleLoopMsg(SkoarString s) {
	val = s;
}


// --- SkoarpuscleExprEnd ---------------------------------------------------------
SkoarpuscleExprEnd::SkoarpuscleExprEnd() {
	on_enter = [](SkoarMinstrel *m) {
		m->fairy->cast_arcane_magic();
	};
}

// --- SkoarpuscleListSep ---------------------------------------------------------
SkoarpuscleListSep::SkoarpuscleListSep() {
	on_enter = [](SkoarMinstrel *m) {
		m->fairy->next_listy();
	};
}

// --- SkoarpuscleListEnd ---------------------------------------------------------
SkoarpuscleListEnd::SkoarpuscleListEnd() {
	on_enter = [](SkoarMinstrel *m) {
		m->fairy->next_listy();
		m->fairy->pop();
	};
}
// --- SkoarpuscleList ---------------------------------------------------------
SkoarpuscleList::SkoarpuscleList() {
    val = make_shared<ListOfSkoarpuscles>();
}

SkoarpuscleList::SkoarpuscleList(ListOfSkoarpusclesPtr x) {
	val = x;
	on_enter = [](SkoarMinstrel *m) {
		m->fairy->push();
	};
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

Skoarpuscle *SkoarpuscleList::skoar_msg(SkoarpuscleMsg *msg, SkoarMinstrel *minstrel) {
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
SkoarpuscleArgs::SkoarpuscleArgs() {
}

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
SkoarpuscleMsg::SkoarpuscleMsg() {
	args = nullptr;
}
	
SkoarpuscleMsg::SkoarpuscleMsg(SkoarString v, shared_ptr<SkoarpuscleArgs> a) {
	val = v;
	args = a;
}

/*SkoarpuscleMsg::get_msg_arr(SkoarMinstrel *m) {
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
SkoarpuscleMsgName::SkoarpuscleMsgName(SkoarString s) {
	val = s;
}


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

	on_enter = [pre_repeat, post_repeat](SkoarMinstrel *m) {

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
	};
}

// --- SkoarpuscleFine ---------------------------------------------------------
SkoarpuscleFine::SkoarpuscleFine() {
	on_enter = [](SkoarMinstrel *m) {
		/*if (m->koar->state_at("al_fine")->val.Bool == true) {
			//debug("fine");
			throw new SkoarNav(SkoarNav::FINE);
		}	 */
	};
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

	on_enter = [](SkoarMinstrel *m) {
		//m->koar->state_put("segno_seen", noad);
	};
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

	on_enter = [this](SkoarMinstrel *m) {
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
SkoarpuscleCarrots::SkoarpuscleCarrots(SkoarToke *toke) {
	val = toke->lexeme.length();
}

// --- SkoarpuscleTuplet ---------------------------------------------------------
SkoarpuscleTuplet::SkoarpuscleTuplet(SkoarToke *toke) {
	val = toke->lexeme.length();
}
			



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
	on_enter = [this](SkoarMinstrel *m) {
		//m->koar["amp"] = this->amp();
	};
}

SkoarFloat SkoarpuscleDynamic::amp() {
    SkoarFloat x = val;
	return x / 8.0;
}

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

	on_enter = [](SkoarMinstrel *m) {
		//auto octave = m->koar[\octave] ? ? 5;
		//m->koar[\octave] = octave + val;
	};
}

// --- SkoarpuscleVoice ---------------------------------------------------------
SkoarpuscleVoice::SkoarpuscleVoice(SkoarToke *toke) {
	auto s = &toke->lexeme;
	auto n = s->length() - 1;
	//val = s[1..n];
}

// --- SkoarpuscleHashLevel ---------------------------------------------------------
SkoarpuscleHashLevel::SkoarpuscleHashLevel(SkoarString lex) {

}


// --- SkoarpusclePair ---------------------------------------------------------
SkoarpusclePair::SkoarpusclePair(SkoarString k, Skoarpuscle* v) {

}



// --- SkoarpuscleExpr ---------------------------------------------------------
SkoarpuscleExpr::SkoarpuscleExpr(SkoarNoadPtr noad) {

}

