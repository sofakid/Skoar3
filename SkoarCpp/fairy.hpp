#pragma once
#include "skoarcery.hpp"
#include "skoarpuscle.hpp"
#include "spells.hpp"


class SkoarFairy {
public:
	SkoarString name;
	SkoarMinstrel *minstrel;
	SkoarpusclePtr impression;
	SkoarpusclePtr noat;

	ArcaneMagic magic;
	list<ListOfSkoarpusclesPtr> listy_stack;
	list<ArcaneMagic> magic_stack;

	SkoarFairy(SkoarString nom, SkoarMinstrel *m);
	SkoarpusclePtr impress(SkoarpusclePtr x);

	void charge_arcane_magic(ArcaneMagic spell);
	SkoarpusclePtr cast_arcane_magic();

	ListOfSkoarpusclesPtr get_top_listy();
	void next_listy();

	void push();
	SkoarpusclePtr pop();

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