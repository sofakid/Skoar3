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

	ISkoarLog *log;

	// todo: make this static
	SkoarOps *ops;                               // operations tables object

	SkoarString skoarce;                        // the skoarce code
	SkoarNoadPtr tree;                           // root of tree
	SkoarToker toker;                            // toker
	map<std::wstring, SkoarKoar*>  voices;  // all the voices
	SkoarKoar *all_voice;                        // the all voice
	list<Skoarpion *> skoarpions;           // all the skoarpions

	Skoar(SkoarString &skoarce, ISkoarLog *log);
    ~Skoar();

	void decorate();
	SkoarKoar *get_voice(SkoarString &k);
	void cthulhu(SkoarNoadPtr noad);
	void play();
	void pskoar();
	void pvoice(std::wstring *voice_name);
	void draw_skoarpions();
};

class SkoarLite {
public:
    SkoarLite(std::wstring &skoarce, ISkoarLog *log);
    ~SkoarLite();

    ISkoarLog *log;

    std::wstring skoarce;      // the skoarce code
    SkoarNoadPtr tree;         // root of tree
    SkoarToker toker;          // toker

    bool parsedOk;
};

