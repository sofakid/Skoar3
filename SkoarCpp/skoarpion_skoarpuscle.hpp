#pragma once
#include "skoarpuscle.hpp"

class SkoarpuscleSkoarpion;
class SkoarpuscleSkoarpionSig;
class SkoarpuscleArgExpr;
class SkoarpuscleArgList;


class SkoarpuscleSkoarpion : public Skoarpuscle {
public:
    list<SkoarString> msg_arr;

    SkoarpuscleSkoarpion(Skoarpion *);
    SkoarpuscleSkoarpion(Skoarpion *, SkoarNoadPtr);

    Skoarpuscle *skoar_msg(SkoarpuscleMsg *msg, SkoarMinstrel *minstrel) override;

    void on_enter_method(SkoarMinstrel *m);
};

class SkoarpuscleProjection : public Skoarpuscle {
public:
    SkoarpuscleProjection(SkoarProjection *);
};