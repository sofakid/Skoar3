#pragma once
#include "skoarpuscle.hpp"
#include "event.hpp"

class SkoarpuscleSkoarpion : public Skoarpuscle {
public:
    SkoarpionPtr val;
    SkoarpusclePtr args;

    SkoarpuscleSkoarpion(const SkoarpuscleSkoarpion*);
    SkoarpuscleSkoarpion(SkoarpionPtr);
    SkoarpuscleSkoarpion(SkoarpionPtr, SkoarNoadPtr);

    SkoarpuscleSkoarpion(SkoarpusclePtr, SkoarpusclePtr);
    ~SkoarpuscleSkoarpion() override;


    SkoarpusclePtr skoar_msg(SkoarpuscleMsg *msg, SkoarMinstrelPtr minstrel) override;

    void run(SkoarMinstrelPtr m);
    void on_enter(SkoarMinstrelPtr) override;
    void asString(wostream &out) override;

};

class SkoarpuscleSkoarpionSig : public Skoarpuscle {
public:
    SkoarString name;
    SkoarpusclePtr arg_list; // is a SkoarpuscleArgList
    SkoarpuscleSkoarpionSig(SkoarNoadPtr);
    ~SkoarpuscleSkoarpionSig() override;
    void asString(wostream &out) override;
};

class SkoarpuscleArgExpr : public Skoarpuscle {
public:
    SkoarString name;
    SkoarpusclePtr expr; // is a SkoarpuscleExpr
    SkoarpuscleArgExpr(SkoarNoadPtr);
    ~SkoarpuscleArgExpr() override;
    void asString(wostream &out) override;

};

class SkoarpuscleArgList : public Skoarpuscle {
public:
    SkoarDic args_dict;
    list<SkoarString> args_names;

    SkoarpuscleArgList(SkoarNoadPtr);
    ~SkoarpuscleArgList() override;

    void on_enter(SkoarMinstrelPtr) override;
    void asString(wostream &out) override;
};

