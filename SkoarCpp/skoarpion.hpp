#pragma once
#include "skoarcery.hpp"
#include "skoar_fwd.hpp"
#include "noad_fwd.hpp"		
#include "skoarpuscle_fwd.hpp"

#include "skoarpion_fwd.hpp"

#include "spells.hpp"

class Skoarpion {
public:

	static Skoarpion *new_from_skoar(Skoar *skoar);

	Skoarpion(Skoar *skoar, SkoarNoadPtr node);

    SkoarString name;
	SkoarpuscleArgSpec *args_spec;

	SkoarProjection *projection(SkoarString name);

};

class SkoarProjection {
public:

	SkoarNoad *performMsg(list<SkoarString> &msg_arr);

	list<int> *map_dst(SkoarNoad *dst);
};
