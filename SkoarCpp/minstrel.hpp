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
        const SpellOfDebuggingSkoarpions& after_entering_skoarpion_spell,
        const SpellOfDebuggingExiting& exiting_spell
    );

    const SpellOfDebuggingNoads& before_entering_noad;
    const SpellOfDebuggingNoads& after_entering_noad;
    const SpellOfDebuggingSkoarpuscles& before_entering_skoarpuscle;
    const SpellOfDebuggingSkoarpuscles& after_entering_skoarpuscle;
    const SpellOfDebuggingSkoarpions& before_entering_skoarpion;
    const SpellOfDebuggingSkoarpions& after_entering_skoarpion;
    const SpellOfDebuggingExiting& exiting;
};

class ISkoarMinstrelMusicker
{
public:
    virtual ~ISkoarMinstrelMusicker () = default;

    virtual void config (SkoarEventPtr event) = 0;
    virtual void noteOn () = 0;
    virtual void noteOff () = 0;
    virtual void sleep (int ms) = 0;
    virtual SkoarFloat getTime () = 0;
};

class SkoarMinstrel {
    SkoarFloat t0;
    SkoarFloat tAccumulated;

public:
    const SkoarString name;
    Skoar* const skoar;

    SkoarFairyPtr fairy;

    SkoarKoarPtr koar;
    SkoarKoarPtr all_voice;

    const SpellOfHappening& happenSpell;
    SpellOfSimplicity f;

    bool isDebugging;

    std::unique_ptr<ISkoarMinstrelMusicker> musicker;

    //SkoarControls controls;

    // don't use this, use SkoarMinstrel::New.
    SkoarMinstrel(SkoarString, SkoarKoarPtr, Skoar* const, const SpellOfHappening& happenSpell);

    virtual ~SkoarMinstrel();
    void clear ();

    // create and initialize minstrel, return a shared_ptr
    static SkoarMinstrelPtr New (SkoarString name, SkoarKoarPtr koar, Skoar* const skoar, const SpellOfHappening& happenSpell);
    static SkoarMinstrelPtr NewForSkoarpion (SkoarString name, SkoarKoarPtr koar, Skoar* const skoar, SkoarpionPtr skoarpion, const SpellOfHappening& happenSpell);
    static SkoarMinstrelPtr NewDebugging(SkoarString name, SkoarKoarPtr koar, Skoar* const skoar, const SpellOfHappening& happenSpell, const MinstrelDebugConfig& config);
    static SkoarMinstrelPtr NewDebuggingForSkoarpion (SkoarString name, SkoarKoarPtr koar, Skoar * const skoar, SkoarpionPtr skoarpion, const SpellOfHappening & spell, const MinstrelDebugConfig & config);

    static void ready_stream (SkoarMinstrelPtr m);
    static void ready_skoarpion (SkoarMinstrelPtr m, SkoarpionPtr skoarpion);

    void done ();

    void reset_colons();

    void start();

    void happen(SkoarEventPtr);

    virtual void before_entering_noad(SkoarMinstrelPtr m, SkoarNoadite* noadite);
    virtual void after_entering_noad(SkoarMinstrelPtr m, SkoarNoadite* noadite);
    virtual void before_entering_skoarpuscle(SkoarMinstrelPtr m, SkoarpusclePtr skoarpuscle);
    virtual void after_entering_skoarpuscle(SkoarMinstrelPtr m, SkoarpusclePtr skoarpuscle);
    virtual void before_entering_skoarpion(SkoarMinstrelPtr m, SkoarpionPtr skoarpion);
    virtual void after_entering_skoarpion (SkoarMinstrelPtr m, SkoarpionPtr skoarpion);
    virtual void exiting ();
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
    const SpellOfDebuggingExiting& exiting_spell;

    void before_entering_noad(SkoarMinstrelPtr m, SkoarNoadite* noadite) override;
    void after_entering_noad(SkoarMinstrelPtr m, SkoarNoadite* noadite) override;
    void before_entering_skoarpuscle(SkoarMinstrelPtr m, SkoarpusclePtr skoarpuscle) override;
    void after_entering_skoarpuscle(SkoarMinstrelPtr m, SkoarpusclePtr skoarpuscle) override;
    void before_entering_skoarpion(SkoarMinstrelPtr m, SkoarpionPtr skoarpion) override;
    void after_entering_skoarpion (SkoarMinstrelPtr m, SkoarpionPtr skoarpion) override;
    void exiting() override;
};

// ----------------------------------
// Skoarchestra - A band of minstrels
// ----------------------------------
class Skoarchestra
{
    const SpellOfHappening& happenSpell;
public:
    //SkoarTroll troll;
    ListOfMinstrels minstrels;
    Skoarchestra (Skoar* const, const SpellOfHappening&);
};
