#pragma once
#include "skoarcery.hpp"
#include "skoar_fwd.hpp"
#include "noad_fwd.hpp"		
#include "skoarpuscle_fwd.hpp"

#include "skoarpion_fwd.hpp"

#include "spells.hpp"

class Skoarpion {
public:

	static SkoarpionPtr new_from_skoar(Skoar *skoar);
    static SkoarpionPtr new_from_skoar_noad(Skoar *skoar, SkoarNoadPtr noad);

	Skoarpion(Skoar *skoar, SkoarNoadPtr node);

    SkoarString name;
	shared_ptr<SkoarpuscleArgSpec> args_spec;

	SkoarProjectionPtr projection(SkoarString name);

};

class SkoarProjection {
public:

	SkoarNoadPtr performMsg(list<SkoarString> &msg_arr);

	list<int> *map_dst(SkoarNoadPtr dst);
};
