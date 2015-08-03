#include "skoarpion.hpp"

#include "skoar.hpp"
#include "noad.hpp"
#include "skoarpuscle.hpp"
#include "skoar.hpp"


Skoarpion* Skoarpion::new_from_skoar(Skoar *skoar) {
	return nullptr;
}

Skoarpion::Skoarpion(Skoar *skoar, SkoarNoad *node) {
}

SkoarProjection *Skoarpion::projection(string *name) {
	return nullptr;
}


SkoarNoad *SkoarProjection::performMsg(list<string*> &msg_arr) {
	return nullptr;
}

list<int> *SkoarProjection::map_dst(SkoarNoad *dst) {
	return nullptr;
}
