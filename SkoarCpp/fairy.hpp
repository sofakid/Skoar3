#pragma once
#include "skoarcery.hpp"
#include "all_skoarpuscles.hpp"
#include "spells.hpp"


class SkoarFairy {
public:
	SkoarString name;
	SkoarMinstrelPtr minstrel;
    SkoarpusclePtr noat;
    SkoarpusclePtr impression;
    SkoarpusclePtr boolean_impression;
    SkoarpusclePtr l_value;
    
	SkoarFairy(SkoarString, SkoarMinstrelPtr);
    ~SkoarFairy();
    void fly_away();

    ListOfSkoarpusclesPtr get_top_listy();
    void set_top_listy(ListOfSkoarpusclesPtr);
	void next_listy();

    void push();
    SkoarpusclePtr pop();

    void push_impression();
    void pop_impression();

    void push_noating(bool = false);
    void pop_noating();

    void push_i();
    void pop_i();
    void incr_i();

    void push_times_seen();
    void pop_times_seen();

    SkoarInt how_many_times_have_you_seen(Skoarpuscle*);
    void forget_that_you_have_seen(Skoarpuscle*);
    
    void push_compare();
    void pop_compare();

    void compare_impress(SkoarMinstrelPtr);

    void push_boolean();
    void pop_boolean();

    SkoarpusclePtr impress_i();

    template <typename T>
    SkoarpusclePtr impress(T x) {
        return impress<SkoarpusclePtr>(make_skoarpuscle(x));
    }

    template<>
    SkoarpusclePtr impress(SkoarpusclePtr);

    void compile_ugen();

    SkoarpusclePtr exact_duration();

    void charge_arcane_magic(ArcaneMagic spell);
    SkoarpusclePtr cast_arcane_magic();

    void consider(SkoarEvent&);
    void consider_amp(SkoarEvent&, SkoarMinstrelPtr);


private:
    ArcaneMagic magic;
    
    list<ListOfSkoarpusclesPtr> listy_stack;
    list<ArcaneMagic> magic_stack;
    list<SkoarInt> i_stack;
    
    ListOfSkoarpuscles compare_stack;

    ListOfSkoarpuscles impression_stack;
    
    ListOfSkoarpuscles boolean_stack;
    

    list<shared_ptr<map<Skoarpuscle*, SkoarInt>>> times_seen_stack;
    shared_ptr<map<Skoarpuscle*, SkoarInt>> times_seen;

    SkoarpusclePtr exact;

    bool noating;
    list<bool> noating_stack;

    bool noatworthy;
    list<bool> noatworthy_stack;

    SkoarInt i;
    SkoarInt j;

    //SkoarLute lute;

};

class SkoarpuscleFairy : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleFairy" << " :: $" ; }
    SkoarpuscleFairy();

};
