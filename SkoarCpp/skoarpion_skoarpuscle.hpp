#pragma once
#include "skoarpuscle.hpp"
#include "event.hpp"

class SkoarpuscleSkoarpion : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleSkoarpion" << " :: " ; }
    const SkoarpionPtr val;
    SkoarpusclePtr args;

    SkoarpuscleSkoarpion(const SkoarpuscleSkoarpion*);
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
    void asString(wostream &out) override { out << "SkoarpuscleSkoarpionSig" << " :: " ; }
    SkoarString name;
    SkoarpusclePtr arg_list; // is a SkoarpuscleArgList
    SkoarpuscleSkoarpionSig(SkoarNoadPtr);
};

class SkoarpuscleArgExpr : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleArgExpr" << " :: " ; }
    SkoarString name;
    SkoarpusclePtr expr; // is a SkoarpuscleExpr
    SkoarpuscleArgExpr(SkoarNoadPtr);
};

class SkoarpuscleArgList : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleArgList" << " :: " ; }
    SkoarDic args_dict;
    list<SkoarString> args_names;

    SkoarpuscleArgList(SkoarNoadPtr);

    void on_enter(SkoarMinstrelPtr) override;

};

class SkoarpuscleProjection : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleProjection" << " :: " ; }
    SkoarpuscleProjection(SkoarpionProjectionPtr);
};

class SkoarpuscleProjections : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleProjections" << " :: " ; }
    SkoarpuscleProjections(ListOfSkoarpionProjectionsPtr);
};
