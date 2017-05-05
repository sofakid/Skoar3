#pragma once
#include "skoar_public.hpp"

#include "noad_fwd.hpp"
#include "toker_fwd.hpp"
#include "koar_fwd.hpp"
#include "rdpp_fwd.hpp"
#include "operators_fwd.hpp"
#include "skoarpion_fwd.hpp"
#include "minstrel_fwd.hpp"

#include "logging.hpp"
#include "spells.hpp"
#include "toker.hpp"

class Skoar
{
public:

    // init everything.
    static void init ();

    ISkoarLog* log;

    // todo: make this static
    SkoarOps* ops;                         // operations tables object

    SkoarString skoarce;                   // the skoarce code
    SkoarNoadPtr tree;                     // root of tree
    map<SkoarString, SkoarKoarPtr> voices; // all the voices
    SkoarKoarPtr all_voice;                // the all voice
    ListOfSkoarpions skoarpions;           // all the skoarpions

    SkoarInt running;

    list<size_t> markers_colon;
    list<size_t> markers_coda;
    map<SkoarString, size_t> markers_coda_named;

    bool parsedOk;
    bool decoratedOk;

    Skoar (SkoarString skoarce, ISkoarLog* log);
    ~Skoar ();

    void decorate ();
    void decorate_offs_size_style ();
    void registerMarker (SkoarpuscleBars* bars);
    void registerMarker (SkoarpuscleCoda* coda);
    SkoarKoarPtr get_voice (const SkoarString& k);
    void cthulhu (SkoarNoadPtr noad);
    void cthulhu (SkoarString s);
    void draw_skoarpions ();

    ListOfSkoarpionProjectionsPtr get_all_projections ();
    ListOfSkoarpionProjectionsPtr get_projections (SkoarString koar_name);
    ListOfSkoarStrings get_all_voices ();

    void play (const SpellOfHappening& spell);

    void play_voice (SkoarString voice, const SpellOfHappening& spell);
    void play_voice_skoarpion (SkoarString voice, SkoarpionPtr skoarpion, const SpellOfHappening& spell);

    void debug_voice (SkoarString voice, const SpellOfHappening& spell, const MinstrelDebugConfig& config);

    void one_more_running ();
    void one_less_running ();

};

class SkoarLite
{
public:
    SkoarLite (SkoarString skoarce, ISkoarLog* log);
    ~SkoarLite ();

    ISkoarLog* log;

    SkoarString skoarce;      // the skoarce code
    SkoarNoadPtr tree;         // root of tree

    bool parsedOk;
    void decorate_offs_size_style ();

};

