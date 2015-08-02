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

Skoarpuscle::Skoarpuscle() {
}


SkoarpuscleUnknown::SkoarpuscleUnknown() {
}

SkoarpuscleCrap::SkoarpuscleCrap() {
}

/*asString{ "crap" }
// these aren't doing nothing, they are returning this crap
skoar_msg{}
flatten{ return nil }
*/	

SkoarpuscleInt::SkoarpuscleInt(SkoarInt v) {
	val.Int = v;

	on_enter = [this](SkoarMinstrel *m) {
		m->fairy->impress(this);
	};
}

bool SkoarpuscleInt::isNoatworthy() { return true; }

void *SkoarpuscleInt::asNoat() {
	return nullptr;//return new SkoarNoat_Degree(val.asInteger);
}




SkoarpuscleFloat::SkoarpuscleFloat(SkoarFloat v) {
	val.Float = v;
	on_enter = [this](SkoarMinstrel *m) {
		m->fairy->impress(this);
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



SkoarpuscleFreq::SkoarpuscleFreq(string *lexeme) {
	val.String = lexeme; // todo chop off Hz
	
	on_enter = [this](SkoarMinstrel *m) {
		m->fairy->impress(this);
	};
}

bool SkoarpuscleFreq::isNoatworthy() { 
	return false; 
} // todo

void *SkoarpuscleFreq::asNoat() {
	return nullptr;
	//return new SkoarNoat_Freq(val.asFloat);
}



SkoarpuscleString::SkoarpuscleString(string *s) {
	val.String = s;
	on_enter = [this](SkoarMinstrel *m) {
		m->fairy->impress(this);
	};
}


SkoarpuscleSymbolName::SkoarpuscleSymbolName(string *s) {
	val.String = s;
	on_enter = [this](SkoarMinstrel *m) {
		m->fairy->impress(this);
	};
}

SkoarpuscleSymbol::SkoarpuscleSymbol(string *s) {
	val.String = s;
	on_enter = [this](SkoarMinstrel *m) {
		m->fairy->impress(this);
	};
}


Skoarpuscle *SkoarpuscleSymbol::skoar_msg(SkoarpuscleMsg *msg, SkoarMinstrel *minstrel) {
	//auto o = msg.get_msg_arr(minstrel);
	//auto ret = val.performMsg(o);

	//return new Skoarpuscle.wrap(ret);
	return nullptr;
}



SkoarpuscleDeref::SkoarpuscleDeref(string *v, SkoarpuscleArgs *a) {
	val = v;
	args = a;
	
	on_enter = [this](SkoarMinstrel *m) {
		/*auto x = this->lookup(m);

		//"deref:on_enter: SYMBOL LOOKEDUP : ".post; val.post; " ".post; x.postln;
		x = Skoarpuscle.wrap(x);

		if (x.isKindOf(SkoarpuscleSkoarpion)) {
		m->koar.do_skoarpion(x.val, m, msg_arr, m->fairy->impression);
		} {
		m->fairy->impress(x);
		};*/
	};
}

Skoarpuscle *SkoarpuscleDeref::lookup(SkoarMinstrel* minstrel){
	//return m->koar[val];
	return nullptr;
}
/*
SkoarpuscleDeref::flatten(m) {
	return this.lookup(m);
}

Skoarpuscle *SkoarpuscleDeref::skoar_msg(SkoarpuscleMsg *msg, SkoarMinstrel *minstrel) {

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

SkoarpuscleMathOp::SkoarpuscleMathOp(SkoarToke *toke) {
	val.String = toke->lexeme;

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

SkoarpuscleBooleanOp::SkoarpuscleBooleanOp(SkoarToke *toke) {
	val.String = toke->lexeme;

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


SkoarpuscleBoolean::SkoarpuscleBoolean(SkoarNoad *noad) {
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



SkoarpuscleConditional::SkoarpuscleConditional() {
}


SkoarpuscleConditional::SkoarpuscleConditional(Skoar *skoar, SkoarNoad *noad) {

	ifs = new list<Skoarpuscle*>();
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

SkoarpuscleSkoarpion::SkoarpuscleSkoarpion(Skoarpion *) {
	on_enter = [this](SkoarMinstrel *m) {
		this->on_enter_method(m);
	};
}

SkoarpuscleSkoarpion::SkoarpuscleSkoarpion(Skoarpion *, SkoarNoad *) {
	on_enter = [this](SkoarMinstrel *m) {
		this->on_enter_method(m);
	};
}


Skoarpuscle *SkoarpuscleSkoarpion::skoar_msg(SkoarpuscleMsg *msg, SkoarMinstrel *minstrel) {
	//msg_arr = msg->get_msg_arr(minstrel);
	return this;
}

void SkoarpuscleSkoarpion::on_enter_method(SkoarMinstrel *m) {
	if (val.Skoarpion->name != nullptr) {
		//m->koar[val.Skoarpion->name] = this;
	}

	if (msg_arr != nullptr) {
		//m->koar.do_skoarpion(val, m, msg_arr, nullptr);
	}
}


SkoarpuscleLoop::SkoarpuscleLoop(Skoar *skoar, SkoarNoad *noad) {

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
	each = val.List;
	return this;
}


SkoarpuscleLoopMsg::SkoarpuscleLoopMsg() {
}

SkoarpuscleExprEnd::SkoarpuscleExprEnd() {
	on_enter = [](SkoarMinstrel *m) {
		m->fairy->cast_arcane_magic();
	};
}

SkoarpuscleListSep::SkoarpuscleListSep() {
	on_enter = [](SkoarMinstrel *m) {
		m->fairy->next_listy();
	};
}

SkoarpuscleListEnd::SkoarpuscleListEnd() {
	on_enter = [](SkoarMinstrel *m) {
		m->fairy->next_listy();
		m->fairy->pop();
	};
}
SkoarpuscleList::SkoarpuscleList() {
}

SkoarpuscleList::SkoarpuscleList(list<Skoarpuscle *> *x) {
	val.List = x;
	on_enter = [](SkoarMinstrel *m) {
		m->fairy->push();
	};
}

bool SkoarpuscleList::isNoatworthy() {
	for (auto x : *val.List )
		if (!x->isNoatworthy())
			return false;

	return true;
}

void *SkoarpuscleList::asNoat() {

	auto n = val.List->size();
	auto noats = new void*[n];
	auto i = -1;

	for (auto x : *val.List) {
		noats[++i] = x->asNoat();
	}

	return nullptr;
	//return new SkoarNoat_DegreeList(noats);
}

Skoarpuscle *SkoarpuscleList::skoar_msg(SkoarpuscleMsg *msg, SkoarMinstrel *minstrel) {
	//auto o = msg->get_msg_arr(minstrel);
	auto name = msg->val.String;
	Skoarpuscle *ret = nullptr;

	if (*name == "next") {
		//ret = val.performMsg(o);
	}
	else if (*name == "last") {
		//ret = val.performMsg(o);
	} 
	else {
		//ret = val.performMsg(o);
	}

	return nullptr;
	//return new Skoarpuscle.wrap(ret);
}




SkoarpuscleArgs::SkoarpuscleArgs(){
}

		// {! f<a,b,c> !! '[\a,\b,\c] is the ArgsSpec' !}
SkoarpuscleArgsSpec::SkoarpuscleArgsSpec() {
}

SkoarpuscleArgsSpec::SkoarpuscleArgsSpec(SkoarNoad *noad) {
	val.List = new list<Skoarpuscle*>;
	
	/*for (auto x : *(noad->collect_skoarpuscles())) {
		if (typeid(x) == typeid(SkoarpuscleSymbolName*)) {
			val.List->emplace_back(x);
		}
	} */
}

SkoarpuscleMsg::SkoarpuscleMsg() {
	args = nullptr;
}
	
SkoarpuscleMsg::SkoarpuscleMsg(string *v, SkoarpuscleArgs *a) {
	val.String = v;
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

SkoarpuscleMsgName::SkoarpuscleMsgName(string *s) {
	val.String = s;
}


// -----------------------------
// musical keywords skoarpuscles
// -----------------------------

SkoarpuscleBars::SkoarpuscleBars(SkoarToke *toke) {

	val.String = toke->lexeme;
	auto n = val.String->length() - 1;
	bool pre_repeat = (*val.String)[0] == ':';
	bool post_repeat = (*val.String)[n] == ':';

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

SkoarpuscleFine::SkoarpuscleFine() {
	on_enter = [](SkoarMinstrel *m) {
		/*if (m->koar->state_at("al_fine")->val.Bool == true) {
			//debug("fine");
			throw new SkoarNav(SkoarNav::FINE);
		}	 */
	};
}


SkoarpuscleSegno::SkoarpuscleSegno(SkoarNoad *nod, SkoarToke *toke) {
	auto s = toke->lexeme;
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


SkoarpuscleGoto::SkoarpuscleGoto(SkoarNoad *noad) {

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


SkoarpuscleVolta::SkoarpuscleVolta(SkoarNoad *nod, SkoarToke *toke) {
	//val = toke.lexeme.strip("[.]").asInteger;
	noad = nod;
}


SkoarpuscleMeter::SkoarpuscleMeter(SkoarToke *toke) {
	//auto a = toke.lexeme.split;
	//val = [a[0].asInteger, a[1].asInteger];
}

SkoarpuscleCarrots::SkoarpuscleCarrots(SkoarToke *toke) {
	val.Int = toke->lexeme->length();
}

SkoarpuscleTuplet::SkoarpuscleTuplet(SkoarToke *toke) {
	val.Int = toke->lexeme->length();
}
			



SkoarpuscleDynamic::SkoarpuscleDynamic(SkoarToke *toke) {
	auto s = toke->lexeme;

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
	return val.Float / 8.0;
}

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

SkoarpuscleVoice::SkoarpuscleVoice(SkoarToke *toke) {
	auto s = toke->lexeme;
	auto n = s->length() - 1;
	//val = s[1..n].asSymbol;
}


SkoarpuscleRep::SkoarpuscleRep(SkoarToke *toke) {
	val.Int = toke->lexeme->length();
}

