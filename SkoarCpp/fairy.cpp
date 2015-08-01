#include "fairy.hpp"

#include "exception.hpp"
#include "skoarpuscle.hpp"

SkoarFairy::SkoarFairy(string *nom, SkoarMinstrel *m) {
	name = nom;
	minstrel = m;
	magic = HarmlessMagic;
}

Skoarpuscle *SkoarFairy::impress(Skoarpuscle *x) {
	//("$:" ++name++ ".impression: " ++x.asString).postln;

	if (typeid(x) == typeid(SkoarpuscleDeref*)) {
		impression = static_cast<SkoarpuscleDeref*>(x)->lookup(minstrel);
	};

	if (impression->isNoatworthy() == true) {
		noat = impression;
	};

	return impression;
}

void SkoarFairy::charge_arcane_magic(ArcaneMagic spell) {
	ArcaneMagic f = magic;

	magic = [=]() {
		//                "ARCANE-alpha".postln;
		f();
		//            "ARCANE-omega".postln;
		Skoarpuscle *x = spell();
		if (x != nullptr) {
			impress(x);
		}
		return nullptr;
	};
}

Skoarpuscle *SkoarFairy::cast_arcane_magic() {
	magic();
	magic = HarmlessMagic;
	
	return impression;
}

// magic stacks and list collecting
list<Skoarpuscle*> *SkoarFairy::get_top_listy() {
	if (listy_stack.empty())
		return nullptr;

	return listy_stack.back();
}

void SkoarFairy::next_listy() {
	auto listy = get_top_listy();

	if (listy != nullptr) {
		(*listy).emplace_back(impression);
	}
}

void SkoarFairy::push() {
	magic_stack.emplace_back(magic);
	magic = HarmlessMagic;

	listy_stack.emplace_back(new list<Skoarpuscle*>);
	//"$.push;".postln;
}

Skoarpuscle *SkoarFairy::pop() {
	if (magic_stack.empty()) {
		throw SkoarError("Magic Stack Underflow");
	}

	magic = magic_stack.back();
	magic_stack.pop_back();

	auto listy = listy_stack.back();
	listy_stack.pop_back();

	impress(new SkoarpuscleList(listy));

	//"popped listy: ".post; impression.postln;

	return impression;
}

