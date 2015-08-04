#pragma once
#include "skoarcery.hpp"
#include "skoarpuscle.hpp"
#include "spells.hpp"


class SkoarFairy {
public:
	wstring * name;
	SkoarMinstrel *minstrel;
	Skoarpuscle *impression;
	Skoarpuscle *noat;

	ArcaneMagic magic;
	list<list<Skoarpuscle *> *> listy_stack;
	list<ArcaneMagic> magic_stack;

	SkoarFairy(wstring *nom, SkoarMinstrel *m);
	Skoarpuscle *impress(Skoarpuscle *x);

	void charge_arcane_magic(ArcaneMagic spell);
	Skoarpuscle *cast_arcane_magic();

	list<Skoarpuscle *> *get_top_listy();
	void next_listy();

	void push();
	Skoarpuscle *pop();

};

class SkoarpuscleFairy : public Skoarpuscle {
public:
	SkoarpuscleFairy();

};
/*
SkoarpuscleFairy : Skoarpuscle {

var msg_arr;

*new { ^super.new.init; }

init {
msg_arr = #[];
}

flatten {
| m |
var x = m.fairy.impression;

if (x.isKindOf(Skoarpuscle)) {
x = x.flatten(m);
};

^x;
}

on_enter {
| m, nav |
var x = m.fairy.impression;

L"performing fairy impression: ".post; x.dump;

if (x.isKindOf(Skoarpuscle)) {
x.perform(m, nav);
};

}


skoar_msg {
| msg, minstrel |
msg_arr = msg.get_msg_arr(minstrel);

L"Fairy got msg: ".post; msg_arr.dump;

^this;
}

//isNoatworthy { ^true; }

//asNoat {
// need a reference to the fairy
//}
}
*/