#pragma once
#include "skoarcery.hpp"
#include "all_skoarpuscles.hpp"
#include "spells.hpp"

typedef map<size_t, SkoarInt> FairyTimesOffsMap;
typedef map<ESkoarpuscle::Kind, FairyTimesOffsMap> FairyTimesMap;
typedef shared_ptr<FairyTimesMap> FairyTimesMapPtr;
typedef vector<FairyTimesMapPtr> ListOfFairyTimesMaps;


class SkoarFairy
{
public:
    SkoarString name;
    SkoarMinstrelPtr minstrel;
    SkoarpusclePtr noat;
    SkoarpusclePtr impression;

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

    void push_magic ();
    void pop_magic ();

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
    
    SkoarpusclePtr impress_i ();

    template <typename T>
    SkoarpusclePtr impress (T x) {
        return impressSkoarpusclePtr (make_skoarpuscle (x));
    }

    SkoarpusclePtr impressSkoarpusclePtr (SkoarpusclePtr);

    void compile_ugen ();

    SkoarpusclePtr exact_duration ();

    void charge_arcane_magic (ArcaneMagic spell);
    SkoarpusclePtr cast_arcane_magic ();

    void consider (SkoarEventPtr);
    void consider_amp (SkoarEventPtr, SkoarMinstrelPtr);


private:
    AncientArcaneMagic magic;

    vector<ListOfSkoarpusclesPtr> listy_stack;
    vector<AncientArcaneMagic> magic_stack;
    vector<SkoarInt> i_stack;

    ListOfSkoarpuscles compare_stack;

    ListOfSkoarpuscles impression_stack;

    ListOfSkoarpuscles boolean_stack;

    ListOfFairyTimesMaps times_seen_stack;
    FairyTimesMapPtr times_seen;

    SkoarpusclePtr exact;

    bool noating;
    vector<bool> noating_stack;

    bool noatworthy;
    vector<bool> noatworthy_stack;

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
