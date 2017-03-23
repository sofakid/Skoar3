#pragma once
#include "skoarcery.hpp"
#include "fairy.hpp"
#include "skoar.hpp"
#include "koar.hpp"
#include "event.hpp"
#include "skoarpion.hpp"

class SkoarMinstrel {
public:

    Skoar* skoar;

	SkoarFairyPtr fairy;

    SkoarKoarPtr koar;
    SkoarKoarPtr all_voice;

    //SkoarControls controls;

    SkoarEventStreamPtr event_stream; //kek save me.

    // don't use this, use SkoarMinstrel::New.
    SkoarMinstrel(SkoarString, SkoarKoarPtr, Skoar*);

    ~SkoarMinstrel();

    // create and initialize minstrel, return a shared_ptr
    static SkoarMinstrelPtr New(SkoarString name, SkoarKoarPtr koar, Skoar* skoar);
    static void EventStream(SkoarMinstrelPtr m);
    
    SkoarEventPtr nextEvent();
    SkoarEventStreamPtr pfunk();

    void reset_colons();

};


// ----------------------------------
// Skoarchestra - A band of minstrels
// ----------------------------------
class Skoarchestra {
public:

    ListOfMinstrels minstrels;
    //SkoarTroll troll;
    
    Skoarchestra(Skoar*);

    SkoarEventStreamPtr eventStream();
    SkoarEventStreamPtr pfunk();

};