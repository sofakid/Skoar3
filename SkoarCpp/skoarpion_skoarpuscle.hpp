#pragma once
#include "skoarpuscle.hpp"
#include "event.hpp"

class SkoarpuscleSkoarpion : public Skoarpuscle {
public:
    const SkoarpionPtr val;
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
    SkoarString name;
    SkoarpusclePtr arg_list; // is a SkoarpuscleArgList
    SkoarpuscleSkoarpionSig(SkoarNoadPtr);
};

class SkoarpuscleArgExpr : public Skoarpuscle {
public:
    SkoarString name;
    SkoarpusclePtr expr; // is a SkoarpuscleExpr
    SkoarpuscleArgExpr(SkoarNoadPtr);
};

class SkoarpuscleArgList : public Skoarpuscle {
public:
    SkoarDic args_dict;
    list<SkoarString> args_names;

    SkoarpuscleArgList(SkoarNoadPtr);

    void on_enter(SkoarMinstrelPtr) override;

};

class SkoarpuscleProjection : public Skoarpuscle {
public:
    SkoarpuscleProjection(SkoarpionProjectionPtr);
};

class SkoarpuscleProjections : public Skoarpuscle {
public:
    SkoarpuscleProjections(ListOfSkoarpionProjectionsPtr);
};
