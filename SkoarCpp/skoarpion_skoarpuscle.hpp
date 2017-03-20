#pragma once
#include "skoarpuscle.hpp"


class SkoarpuscleSkoarpion : public Skoarpuscle {
public:
    list<SkoarString> msg_arr;

    SkoarpuscleSkoarpion(Skoarpion *);
    SkoarpuscleSkoarpion(Skoarpion *, SkoarNoadPtr);

    Skoarpuscle *skoar_msg(SkoarpuscleMsg *msg, SkoarMinstrel *minstrel) override;

    void on_enter_method(SkoarMinstrel *m);
};

class SkoarpuscleSkoarpionSig : public Skoarpuscle {
public:
    SkoarpuscleSkoarpionSig(SkoarNoadPtr);
};

class SkoarpuscleArgExpr : public Skoarpuscle {
public:
    SkoarpuscleArgExpr();
};

class SkoarpuscleArgList : public Skoarpuscle {
public:
    SkoarpuscleArgList(SkoarNoadPtr);
};

class SkoarpuscleProjection : public Skoarpuscle {
public:
    SkoarpuscleProjection(SkoarProjection *);
};
