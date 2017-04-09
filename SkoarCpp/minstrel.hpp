#pragma once
#include "skoarcery.hpp"
#include "fairy.hpp"
#include "skoar.hpp"
#include "koar.hpp"
#include "event.hpp"
#include "skoarpion.hpp"

struct MinstrelDebugConfig {

    MinstrelDebugConfig(
        const SpellOfMinstrels& before_entering_noad_spell,
        const SpellOfMinstrels& after_entering_noad_spell,
        const SpellOfMinstrels& before_entering_skoarpuscle_spell,
        const SpellOfMinstrels& after_entering_skoarpuscle_spell,
        const SpellOfMinstrels& before_entering_skoarpion_spell,
        const SpellOfMinstrels& after_entering_skoarpion_spell
        );

    const SpellOfMinstrels& before_entering_noad;
    const SpellOfMinstrels& after_entering_noad;
    const SpellOfMinstrels& before_entering_skoarpuscle;
    const SpellOfMinstrels& after_entering_skoarpuscle;
    const SpellOfMinstrels& before_entering_skoarpion;
    const SpellOfMinstrels& after_entering_skoarpion;

};

class SkoarMinstrel {
public:

    const SkoarString name;
    Skoar* skoar;

	SkoarFairyPtr fairy;

    SkoarKoarPtr koar;
    SkoarKoarPtr all_voice;

    const SpellOfHappening& happenSpell;
    SpellOfSimplicity f;

    bool isDebugging;

    //SkoarControls controls;

    // don't use this, use SkoarMinstrel::New.
    SkoarMinstrel(SkoarString, SkoarKoarPtr, Skoar*, const SpellOfHappening& happenSpell);

    virtual ~SkoarMinstrel();

    // create and initialize minstrel, return a shared_ptr
    static SkoarMinstrelPtr New(SkoarString name, SkoarKoarPtr koar, Skoar* skoar, const SpellOfHappening& happenSpell);
    static SkoarMinstrelPtr NewDebugging(SkoarString name, SkoarKoarPtr koar, Skoar* skoar, const SpellOfHappening& happenSpell, const MinstrelDebugConfig& config);

    static void EventStream(SkoarMinstrelPtr m);
    
    void reset_colons();

    void start();

    void happen(SkoarEventPtr);

    virtual void before_entering_noad(SkoarMinstrelPtr);
    virtual void after_entering_noad(SkoarMinstrelPtr);
    virtual void before_entering_skoarpuscle(SkoarMinstrelPtr);
    virtual void after_entering_skoarpuscle(SkoarMinstrelPtr);
    virtual void before_entering_skoarpion(SkoarMinstrelPtr);
    virtual void after_entering_skoarpion(SkoarMinstrelPtr);

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

class DebuggingMinstrel : public SkoarMinstrel {
public:
    DebuggingMinstrel(SkoarString, SkoarKoarPtr, Skoar*, const SpellOfHappening& happenSpell, const MinstrelDebugConfig& config);
    ~DebuggingMinstrel() override;

    const SpellOfMinstrels& before_entering_noad_spell;
    const SpellOfMinstrels& after_entering_noad_spell;
    const SpellOfMinstrels& before_entering_skoarpuscle_spell;
    const SpellOfMinstrels& after_entering_skoarpuscle_spell;
    const SpellOfMinstrels& before_entering_skoarpion_spell;
    const SpellOfMinstrels& after_entering_skoarpion_spell;

    void before_entering_noad(SkoarMinstrelPtr) override;
    void after_entering_noad(SkoarMinstrelPtr) override;
    void before_entering_skoarpuscle(SkoarMinstrelPtr) override;
    void after_entering_skoarpuscle(SkoarMinstrelPtr) override;
    void before_entering_skoarpion(SkoarMinstrelPtr) override;
    void after_entering_skoarpion(SkoarMinstrelPtr) override;

};