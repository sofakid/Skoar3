#pragma once
#include "skoar_public.hpp"

#include "noad_fwd.hpp"
#include "toker_fwd.hpp"
#include "koar_fwd.hpp"
#include "rdpp_fwd.hpp"
#include "operators_fwd.hpp"
#include "skoarpion_fwd.hpp"

#include "logging.hpp"

class Skoar {
public:

	ISkoarLog *log;

	// todo: make this static
	SkoarOps *ops;      // operations tables object

	std::wstring skoarce;      // the skoarce code
	SkoarNoad *tree;         // root of tree
	SkoarToker *toker;        // toker
	std::map<std::wstring, SkoarKoar*>  voices;       // all the voices
	SkoarKoar *all_voice;    // the all voice
	std::list<Skoarpion *> skoarpions;   // all the skoarpions

	Skoar(std::wstring &skoarce, ISkoarLog *log);

	void decorate();
	SkoarKoar *get_voice(std::wstring *k);
	void cthulhu(SkoarNoad *noad);
	void play();
	void pskoar();
	void pvoice(std::wstring *voice_name);
	void draw_skoarpions();
};

