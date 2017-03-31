#pragma once
#include "skoar_public.hpp"

#include "noad_fwd.hpp"
#include "toker_fwd.hpp"
#include "koar_fwd.hpp"
#include "rdpp_fwd.hpp"
#include "operators_fwd.hpp"
#include "skoarpion_fwd.hpp"

#include "logging.hpp"
#include "spells.hpp"
#include "toker.hpp"

class Skoar {
public:

    // init everything.
    static void init();

	ISkoarLog *log;

	// todo: make this static
	SkoarOps *ops;                         // operations tables object

	SkoarString skoarce;                   // the skoarce code
	SkoarNoadPtr tree;                     // root of tree
	SkoarToker toker;                      // toker
	map<SkoarString, SkoarKoarPtr> voices; // all the voices
	SkoarKoarPtr all_voice;                // the all voice
	ListOfSkoarpions skoarpions;           // all the skoarpions

    SkoarInt running;

    bool parsedOk;
    bool decoratedOk;

	Skoar(SkoarString skoarce, ISkoarLog *log);
    ~Skoar();

	void decorate();
	SkoarKoarPtr get_voice(const SkoarString &k);
	void cthulhu(SkoarNoadPtr noad);
	void draw_skoarpions();


    void play(const SpellOfHappening& spell);

    void play_voice(SkoarString voice, const SpellOfHappening& spell);

    void one_less_running();
};

class SkoarLite {
public:
    SkoarLite(SkoarString skoarce, ISkoarLog *log);
    ~SkoarLite();

    ISkoarLog *log;

    SkoarString skoarce;      // the skoarce code
    SkoarNoadPtr tree;         // root of tree
    SkoarToker toker;          // toker

    bool parsedOk;
};

