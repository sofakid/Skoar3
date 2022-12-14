#pragma once
#include "skoarcery.hpp"

#include "noad_fwd.hpp"
#include "event_fwd.hpp"
#include "skoarpuscle_fwd.hpp"
#include "skoarpion_fwd.hpp"
#include "minstrel_fwd.hpp"
#include "spells.hpp"

class SkoarNav {
public:
    enum ECode {
        DONE = 0,
        CODA,
        COLON
    } code;

    SkoarNav(ECode code);
};



class SkoarKoar {
public:

    enum EExecStyle {
        INLINE,
        NORMAL,
        MEDITATION
    };

    Skoar              *skoar;
    SkoarDicPtr		   skoarboard;   //
    ListOfSkoarDics    stack;        // stack of vars visible to the skoar code
    ListOfSkoarDics    state_stack;  // stack of vars invisible to the skoar code
    SkoarString        name;         // name of voice

    SkoarKoar(Skoar *skoar, const SkoarString &nom);
    ~SkoarKoar();

    void clear();
    
    // ---------------------
    // State and scope stuff
    // ---------------------
    SkoarDicPtr find_stack_level_for_var (SkoarString k);
    void put (SkoarString k, SkoarpusclePtr v);
    SkoarpusclePtr at (const SkoarString &k);

    void state_put (SkoarString &k, SkoarpusclePtr v);
    void state_put (const wchar_t* k, SkoarpusclePtr v);
    
    SkoarpusclePtr state_at (const wchar_t* k);
    SkoarpusclePtr state_at (SkoarString &k);
    
    SkoarEventPtr event(SkoarMinstrelPtr minstrel);
    void set_args(SkoarMinstrelPtr minstrel, 
        SkoarpusclePtr args_spec, SkoarpusclePtr args);

    void push_state();
    void pop_state();
    void do_skoarpion(
        SkoarpionPtr skoarpion, 
        SkoarMinstrelPtr minstrel, 
        const EExecStyle,
        SkoarpusclePtr args_provided);

    void do_skoarpion (
        SkoarpionPtr skoarpion,
        SkoarMinstrelPtr minstrel,
        const EExecStyle,
        SkoarpusclePtr args_provided,
        ListOfSkoarpuscles*,
        ListOfSkoarStrings*
        );

    void nav_loop(
        SkoarpionProjectionPtr projection, 
        SkoarMinstrelPtr minstrel,
        SpellOfDecency cleanup);

    void bubble_up_nav(SkoarNav &nav, SpellOfDecency cleanup);
};

