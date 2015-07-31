#pragma once
#include "skoarcery.hpp"
#include "skoar_fwd.hpp"
#include "noad_fwd.hpp"

class Skoarpion {
public:

	static Skoarpion *new_from_skoar(Skoar *skoar);

	Skoarpion(Skoar *skoar, SkoarNoad *node);

	string *name;
};

class SkoarProjection {
public:


};
