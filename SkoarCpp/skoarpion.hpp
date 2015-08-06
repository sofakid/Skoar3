#pragma once
#include "skoarcery.hpp"
#include "skoar_fwd.hpp"
#include "noad_fwd.hpp"		
#include "skoarpuscle_fwd.hpp"

#include "skoarpion_fwd.hpp"

class Skoarpion {
public:

	static Skoarpion *new_from_skoar(Skoar *skoar);

	Skoarpion(Skoar *skoar, SkoarNoad *node);

	wstring *name;
	SkoarpuscleArgsSpec *args_spec;

	SkoarProjection *projection(wstring *name);

};

class SkoarProjection {
public:

	SkoarNoad *performMsg(list<wstring*> &msg_arr);

	list<int> *map_dst(SkoarNoad *dst);
};