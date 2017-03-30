#pragma once
#include "skoarcery.hpp"
#include <sstream>
#include "spells.hpp"



typedef map<SkoarString, SkoarInt> MemoriesMap;

class SkoarMem {
public:
    SkoarMem();

    SkoarInt Tokes;
    SkoarInt Noads;
    SkoarInt Skoars;
    SkoarInt Skoarpuscles;
    SkoarInt Skoarpions;
    SkoarInt Projections;
    SkoarInt Koars;
    SkoarInt Fairies;
    SkoarInt Minstrels;
    SkoarInt SkoarDics;
    SkoarInt Events;

    MemoriesMap TokesMap;
    MemoriesMap NoadsMap;
    MemoriesMap SkoarpusclesMap;
    MemoriesMap SkoarpionsMap;
    MemoriesMap ProjectionsMap;
    MemoriesMap KoarsMap;
    MemoriesMap FairiesMap;
    MemoriesMap MinstrelsMap;
    MemoriesMap SkoarDicsMap;
    MemoriesMap EventsMap;


    // --------------------------------------------------------------------------
    // for testing use only!
    void reset() {
        Tokes = 0;
        Noads = 0;
        Skoars = 0;
        Skoarpuscles = 0;
        Skoarpions = 0;
        Projections = 0;
        Koars = 0;
        Fairies = 0;
        Minstrels = 0;
        SkoarDics = 0;
        Events = 0;

        TokesMap.clear();
        NoadsMap.clear();
        SkoarpusclesMap.clear();
        SkoarpionsMap.clear();
        ProjectionsMap.clear();
        KoarsMap.clear();
        FairiesMap.clear();
        MinstrelsMap.clear();
        SkoarDicsMap.clear();
        EventsMap.clear();
    }
    
    // --------------------------------------------------------------------------
    void alloc(SkoarString &name, MemoriesMap &Map) {
        Map[name] += 1;
    }

    void dealloc(SkoarString &name, MemoriesMap &Map) {
        Map[name] -= 1;
    }

    // --------------------------------------------------------------------------
    void allocSkoar() { Skoars += 1; }
    void deallocSkoar() { Skoars -= 1; }

    void allocToke(SkoarString name) { alloc(name, TokesMap); Tokes += 1; }
    void deallocToke(SkoarString name) { dealloc(name, TokesMap); Tokes -= 1; }

    void allocNoad(SkoarString name) { alloc(name, NoadsMap); Noads += 1; }
    void deallocNoad(SkoarString name) { dealloc(name, NoadsMap); Noads -= 1; }

    void allocSkoarpuscle(SkoarString name) { alloc(name, SkoarpusclesMap); Skoarpuscles += 1; }
    void deallocSkoarpuscle(SkoarString name) { dealloc(name, SkoarpusclesMap); Skoarpuscles -= 1; }
    
    void allocSkoarpion(SkoarString name) { alloc(name, SkoarpionsMap); Skoarpions += 1; }
    void deallocSkoarpion(SkoarString name) { dealloc(name, SkoarpionsMap); Skoarpions -= 1; }

    void allocProjection(SkoarString name) { alloc(name, ProjectionsMap); Projections += 1; }
    void deallocProjection(SkoarString name) { dealloc(name, ProjectionsMap); Projections -= 1; }

    void allocKoar(SkoarString name) { alloc(name, KoarsMap); Koars += 1; }
    void deallocKoar(SkoarString name) { dealloc(name, KoarsMap); Koars -= 1; }

    void allocFairy(SkoarString name) { alloc(name, FairiesMap); Fairies += 1; }
    void deallocFairy(SkoarString name) { dealloc(name, FairiesMap); Fairies -= 1; }

    void allocMinstrel(SkoarString name) { alloc(name, MinstrelsMap); Minstrels += 1; }
    void deallocMinstrel(SkoarString name) { dealloc(name, MinstrelsMap); Minstrels -= 1; }

    void allocSkoarDic(SkoarString name) { alloc(name, SkoarDicsMap); SkoarDics += 1; }
    void deallocSkoarDic(SkoarString name) { dealloc(name, SkoarDicsMap); SkoarDics -= 1; }

    void allocEvent(SkoarString name) { alloc(name, EventsMap); Events += 1; }
    void deallocEvent(SkoarString name) { dealloc(name, EventsMap); Events -= 1; }

    friend std::wostream& operator << (std::wostream& out, const SkoarMem& obj);
    friend std::ostream& operator << (std::ostream& out, const SkoarMem& obj);

};


namespace SkoarMemories {
    SkoarMem& o();
}
