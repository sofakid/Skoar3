#pragma once
#include "skoarcery.hpp"
#include "all_skoarpuscles.hpp"
#include "spells.hpp"

typedef map<size_t, SkoarInt> FairyTimesOffsMap;
typedef map<ESkoarpuscle::Kind, FairyTimesOffsMap> FairyTimesMap;
typedef shared_ptr<FairyTimesMap> FairyTimesMapPtr;
typedef list<FairyTimesMapPtr> ListOfFairyTimesMaps;


class SkoarFairy
{
public:
    SkoarString name;
    SkoarMinstrelPtr minstrel;
    SkoarpusclePtr noat;
    SkoarpusclePtr impression;
    SkoarpusclePtr boolean_impression;
    SkoarpusclePtr l_value;

    size_t fly_to_dest;
    bool al_fine;

    SkoarFairy (SkoarString, SkoarMinstrelPtr);
    ~SkoarFairy ();
    void fly_away ();

    ListOfSkoarpusclesPtr get_top_listy ();
    void set_top_listy (ListOfSkoarpusclesPtr);
    void next_listy ();

    void push ();
    SkoarpusclePtr pop ();

    void push_impression ();
    void pop_impression ();

    void push_noating (bool = false);
    void pop_noating ();

    void push_i ();
    void pop_i ();
    void incr_i ();

    void push_times_seen ();
    void pop_times_seen ();

    SkoarInt how_many_times_have_you_seen (ESkoarpuscle::Kind kind, size_t offs);
    void forget_that_you_have_seen (ESkoarpuscle::Kind);
    void forget_that_you_have_seen (size_t offs);

    void on_bar (SkoarpuscleBars * skoarpuscle);


    void fly_to_colon ();
    void fly_to_coda (SkoarString label);
    
    void push_compare ();
    void pop_compare ();

    void compare_impress (SkoarMinstrelPtr);

    void push_boolean ();
    void pop_boolean ();

    SkoarpusclePtr impress_i ();

    template <typename T>
    SkoarpusclePtr impress (T x) {
        return impress<SkoarpusclePtr> (make_skoarpuscle (x));
    }

    template<>
    SkoarpusclePtr impress (SkoarpusclePtr);

    void compile_ugen ();

    SkoarpusclePtr exact_duration ();

    void charge_arcane_magic (ArcaneMagic spell);
    SkoarpusclePtr cast_arcane_magic ();

    void consider (SkoarEventPtr);
    void consider_amp (SkoarEventPtr, SkoarMinstrelPtr);


private:
    AncientArcaneMagic magic;

    list<ListOfSkoarpusclesPtr> listy_stack;
    list<AncientArcaneMagic> magic_stack;
    list<SkoarInt> i_stack;

    ListOfSkoarpuscles compare_stack;

    ListOfSkoarpuscles impression_stack;

    ListOfSkoarpuscles boolean_stack;

    ListOfFairyTimesMaps times_seen_stack;
    FairyTimesMapPtr times_seen;

    SkoarpusclePtr exact;

    bool noating;
    list<bool> noating_stack;

    bool noatworthy;
    list<bool> noatworthy_stack;

    SkoarInt i;
    SkoarInt j;

    //SkoarLute lute;

};

class SkoarpuscleFairy : public Skoarpuscle
{
public:
    void asString (wostream &out) override { out << "SkoarpuscleFairy" << " :: $"; }
    SkoarpuscleFairy ();

};
