#pragma once
#include "skoarcery.hpp"
#include "skoarpuscle.hpp"
#include "spells.hpp"


class SkoarFairy {
public:
	SkoarString name;
	SkoarMinstrelPtr minstrel;
    SkoarpusclePtr noat;
    SkoarpusclePtr impression;
    
	SkoarFairy(SkoarString, SkoarMinstrelPtr);

    ListOfSkoarpusclesPtr get_top_listy();
    void set_top_listy(ListOfSkoarpusclesPtr);
	void next_listy();

    void push();
    SkoarpusclePtr pop();

    void push_impression();
    void pop_impression();

    void push_noating();
    void pop_noating();

    void push_i();
    void pop_i();
    void incr_i();

    void push_times_seen();
    void pop_times_seen();

    void how_many_times_have_you_seen(SkoarpusclePtr);
    void forget_that_you_have_seen(SkoarpusclePtr);
    
    void push_compare();
    void pop_compare();

    void compare_impress(SkoarMinstrelPtr);

    void push_boolean();
    void pop_boolean();

    SkoarpusclePtr impress_i();
    SkoarpusclePtr impress(SkoarpusclePtr);

    void compile_ugen();

    SkoarpusclePtr exact_duration();

    void charge_arcane_magic(ArcaneMagic spell);
    SkoarpusclePtr cast_arcane_magic();

    void consider(SkoarEvent&);
    void consider_amp(SkoarEvent&);

private:
    ArcaneMagic magic;
    
    list<ListOfSkoarpusclesPtr> listy_stack;
    list<ArcaneMagic> magic_stack;
    list<SkoarInt> i_stack;
    ListOfSkoarpuscles compare_stack;
    
    ListOfSkoarpuscles boolean_stack;
    SkoarpusclePtr boolean_impression;

    list<map<SkoarNoadPtr, SkoarInt>> times_seen_stack;
    map<SkoarNoadPtr, SkoarInt> times_seen;

    bool noating;
    list<bool> noating_stack;

    SkoarInt i;
    SkoarInt j;

    bool noatworthy;

    //SkoarLute lute;

};

class SkoarpuscleFairy : public Skoarpuscle {
public:
	SkoarpuscleFairy();

};
