#include "skoarpion.hpp"

#include "skoar.hpp"
#include "noad.hpp"
#include "skoarpuscle.hpp"
#include "skoar.hpp"

// --- Skoarpion ------------------------------------------------
Skoarpion* Skoarpion::new_from_skoar(Skoar *skoar) {
	return nullptr;
}

Skoarpion::Skoarpion(Skoar *skoar, SkoarNoadPtr node) {
}


// --- SkoarProjection ------------------------------------------------
SkoarProjection *Skoarpion::projection(SkoarString name) {
	return nullptr;
}

SkoarNoadPtr SkoarProjection::performMsg(list<SkoarString> &msg_arr) {
	return nullptr;
}

list<int> *SkoarProjection::map_dst(SkoarNoadPtr dst) {
	return nullptr;
}
