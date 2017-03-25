#pragma once
#include "skoarcery.hpp"
#include "fairy.hpp"
#include "skoar.hpp"
#include "koar.hpp"
#include "event.hpp"
#include "skoarpion.hpp"

class SkoarMinstrel {
public:

    const SkoarString name;
    Skoar* skoar;

	SkoarFairyPtr fairy;

    SkoarKoarPtr koar;
    SkoarKoarPtr all_voice;

    const SpellOfHappening& happenSpell;
    SpellOfSimplicity f;

    //SkoarControls controls;

    SkoarEventStreamPtr event_stream; //kek save me.

    // don't use this, use SkoarMinstrel::New.
    SkoarMinstrel(SkoarString, SkoarKoarPtr, Skoar*, const SpellOfHappening& happenSpell);

    ~SkoarMinstrel();

    // create and initialize minstrel, return a shared_ptr
    static SkoarMinstrelPtr New(SkoarString name, SkoarKoarPtr koar, Skoar* skoar, const SpellOfHappening& happenSpell);
    static void EventStream(SkoarMinstrelPtr m);
    
    void reset_colons();

    void start();

    void happen(SkoarEventPtr);


};


// ----------------------------------
// Skoarchestra - A band of minstrels
// ----------------------------------
class Skoarchestra {
public:

    ListOfMinstrels minstrels;
    //SkoarTroll troll;
    const SpellOfHappening& happenSpell;

    Skoarchestra(Skoar*, const SpellOfHappening&);

};