#include "skoarpion.hpp"

#include "skoar.hpp"
#include "noad.hpp"
#include "skoarpuscle.hpp"
#include "skoar.hpp"

// --- Skoarpion ------------------------------------------------
SkoarpionPtr Skoarpion::new_from_skoar(Skoar* skoar) {
	return nullptr;
}

SkoarpionPtr Skoarpion::new_from_skoar_noad(Skoar* skoar, SkoarNoadPtr noad) {
    return make_shared<Skoarpion>(skoar, noad);
}

SkoarpionPtr Skoarpion::NewFromSubtree(Skoar* skoar, SkoarNoadPtr noad) {
    return make_shared<Skoarpion>(skoar, noad);
}


Skoarpion::Skoarpion(Skoar *skoar, SkoarNoadPtr node) {
}



// --- SkoarProjection ------------------------------------------------
SkoarProjectionPtr Skoarpion::projection(SkoarString name) {
	return nullptr;
}

SkoarNoadPtr SkoarProjection::performMsg(list<SkoarString> &msg_arr) {
	return nullptr;
}

list<int> *SkoarProjection::map_dst(SkoarNoadPtr dst) {
	return nullptr;
}
