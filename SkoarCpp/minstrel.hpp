#pragma once
#include "skoarcery.hpp"
#include "fairy.hpp"
#include "skoar.hpp"
#include "koar.hpp"
#include "event.hpp"
#include "skoarpion.hpp"

struct MinstrelDebugConfig {

    MinstrelDebugConfig(
        const SpellOfDebuggingNoads& before_entering_noad_spell,
        const SpellOfDebuggingNoads& after_entering_noad_spell,
        const SpellOfDebuggingSkoarpuscles& before_entering_skoarpuscle_spell,
        const SpellOfDebuggingSkoarpuscles& after_entering_skoarpuscle_spell,
        const SpellOfDebuggingSkoarpions& before_entering_skoarpion_spell,
        const SpellOfDebuggingSkoarpions& after_entering_skoarpion_spell
        );

    const SpellOfDebuggingNoads& before_entering_noad;
    const SpellOfDebuggingNoads& after_entering_noad;
    const SpellOfDebuggingSkoarpuscles& before_entering_skoarpuscle;
    const SpellOfDebuggingSkoarpuscles& after_entering_skoarpuscle;
    const SpellOfDebuggingSkoarpions& before_entering_skoarpion;
    const SpellOfDebuggingSkoarpions& after_entering_skoarpion;

};

class SkoarMinstrel {
public:

    const SkoarString name;
    Skoar* const skoar;

	SkoarFairyPtr fairy;

    SkoarKoarPtr koar;
    SkoarKoarPtr all_voice;

    const SpellOfHappening& happenSpell;
    SpellOfSimplicity f;

    bool isDebugging;

    //SkoarControls controls;

    // don't use this, use SkoarMinstrel::New.
    SkoarMinstrel(SkoarString, SkoarKoarPtr, Skoar* const, const SpellOfHappening& happenSpell);

    virtual ~SkoarMinstrel();

    // create and initialize minstrel, return a shared_ptr
    static SkoarMinstrelPtr New(SkoarString name, SkoarKoarPtr koar, Skoar* const skoar, const SpellOfHappening& happenSpell);
    static SkoarMinstrelPtr NewDebugging(SkoarString name, SkoarKoarPtr koar, Skoar* const skoar, const SpellOfHappening& happenSpell, const MinstrelDebugConfig& config);

    static void EventStream(SkoarMinstrelPtr m);
    
    void reset_colons();

    void start();

    void happen(SkoarEventPtr);

    virtual void before_entering_noad(SkoarMinstrelPtr m, SkoarNoad* noad);
    virtual void after_entering_noad(SkoarMinstrelPtr m, SkoarNoad* noad);
    virtual void before_entering_skoarpuscle(SkoarMinstrelPtr m, SkoarpusclePtr skoarpuscle);
    virtual void after_entering_skoarpuscle(SkoarMinstrelPtr m, SkoarpusclePtr skoarpuscle);
    virtual void before_entering_skoarpion(SkoarMinstrelPtr m, SkoarpionPtr skoarpion);
    virtual void after_entering_skoarpion(SkoarMinstrelPtr m, SkoarpionPtr skoarpion);

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

    const SpellOfDebuggingNoads& before_entering_noad_spell;
    const SpellOfDebuggingNoads& after_entering_noad_spell;
    const SpellOfDebuggingSkoarpuscles& before_entering_skoarpuscle_spell;
    const SpellOfDebuggingSkoarpuscles& after_entering_skoarpuscle_spell;
    const SpellOfDebuggingSkoarpions& before_entering_skoarpion_spell;
    const SpellOfDebuggingSkoarpions& after_entering_skoarpion_spell;

    void before_entering_noad(SkoarMinstrelPtr m, SkoarNoad* noad) override;
    void after_entering_noad(SkoarMinstrelPtr m, SkoarNoad* noad) override;
    void before_entering_skoarpuscle(SkoarMinstrelPtr m, SkoarpusclePtr skoarpuscle) override;
    void after_entering_skoarpuscle(SkoarMinstrelPtr m, SkoarpusclePtr skoarpuscle) override;
    void before_entering_skoarpion(SkoarMinstrelPtr m, SkoarpionPtr skoarpion) override;
    void after_entering_skoarpion(SkoarMinstrelPtr m, SkoarpionPtr skoarpion) override;

};