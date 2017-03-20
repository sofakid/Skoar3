#include "fairy.hpp"

#include "exception.hpp"
#include "skoarpuscle.hpp"

SkoarFairy::SkoarFairy(SkoarString nom, SkoarMinstrel *m) :
    name(nom),
    minstrel(m),
    magic(HarmlessMagic)
{
}

SkoarpusclePtr SkoarFairy::impress(SkoarpusclePtr x) {
	//("$:" ++name++ ".impression: " ++x.asString).postln;
    auto p = x.get();

	if (typeid(p) == typeid(SkoarpuscleDeref*)) {
		impression = static_cast<SkoarpuscleDeref*>(p)->lookup(minstrel);
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
		SkoarpusclePtr x = spell();
		if (x != nullptr) {
			impress(x);
		}
		return nullptr;
	};
}

SkoarpusclePtr SkoarFairy::cast_arcane_magic() {
	magic();
	magic = HarmlessMagic;
	
	return impression;
}

// magic stacks and list collecting
ListOfSkoarpusclesPtr SkoarFairy::get_top_listy() {
	if (listy_stack.empty())
		return nullptr;

	return listy_stack.back();
}

void SkoarFairy::next_listy() {
	auto listy = get_top_listy();

	if (listy != nullptr) {
		(*listy).push_back(impression);
	}
}

void SkoarFairy::push() {
	magic_stack.push_back(magic);
	magic = HarmlessMagic;

	listy_stack.push_back(make_shared<ListOfSkoarpuscles>());
	//"$.push;".postln;
}

SkoarpusclePtr SkoarFairy::pop() {
	if (magic_stack.empty()) {
		throw SkoarError(L"Magic Stack Underflow");
	}

	magic = magic_stack.back();
	magic_stack.pop_back();

	auto listy = listy_stack.back();
	listy_stack.pop_back();

	impress(make_shared<SkoarpuscleList>(listy));

	//"popped listy: ".post; impression.postln;

	return impression;
}

SkoarpuscleFairy::SkoarpuscleFairy() {

}