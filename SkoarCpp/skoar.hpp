#pragma once
#include "skoarcery.hpp"

#include "noad_fwd.hpp"
#include "toker_fwd.hpp"
#include "koar_fwd.hpp"
#include "rdpp_fwd.hpp"
#include "operators_fwd.hpp"
#include "skoarpion_fwd.hpp"

class Skoar {
public:
	// todo: make this static
	SkoarOps *ops;      // operations tables object

	string skoarce;      // the skoarce code
	SkoarNoad *tree;         // root of tree
	SkoarToker *toker;        // toker
	map<string, SkoarKoar*>  voices;       // all the voices
	SkoarKoar *all_voice;    // the all voice
	list<Skoarpion *> skoarpions;   // all the skoarpions

	Skoar(string &skoarce);

	void decorate();
	SkoarKoar *get_voice(string *k);
	void cthulhu(SkoarNoad *noad);
	void play();
	void pskoar();
	void pvoice(string *voice_name);
	void draw_skoarpions();
};


