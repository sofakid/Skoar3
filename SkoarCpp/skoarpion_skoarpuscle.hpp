#pragma once
#include "skoarpuscle.hpp"


class SkoarpuscleSkoarpion : public Skoarpuscle {
public:
    SkoarpusclePtr msg_arr;

    SkoarpuscleSkoarpion(SkoarpionPtr);
    SkoarpuscleSkoarpion(SkoarpionPtr, SkoarNoadPtr);

    SkoarpuscleSkoarpion(SkoarpusclePtr, SkoarpusclePtr);


    SkoarpusclePtr skoar_msg(SkoarpuscleMsg *msg, SkoarMinstrelPtr minstrel) override;

    void run(SkoarMinstrelPtr m);
    void on_enter_method(SkoarMinstrelPtr m);
    void on_enter(SkoarMinstrelPtr) override;
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
