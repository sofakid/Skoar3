#pragma once
#include "skoarpuscle.hpp"


class SkoarpuscleSkoarpion : public Skoarpuscle {
public:
    list<SkoarString> msg_arr;

    SkoarpuscleSkoarpion(SkoarpionPtr);
    SkoarpuscleSkoarpion(SkoarpionPtr, SkoarNoadPtr);

    Skoarpuscle *skoar_msg(SkoarpuscleMsg *msg, SkoarMinstrelPtr minstrel) override;

    void on_enter_method(SkoarMinstrelPtr m);
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
    SkoarpuscleProjection(SkoarProjectionPtr);
};

class SkoarpuscleProjections : public Skoarpuscle {
public:
    SkoarpuscleProjections(ListOfSkoarProjectionsPtr);
};
