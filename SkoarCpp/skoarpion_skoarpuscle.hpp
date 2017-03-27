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
    ~SkoarpuscleSkoarpion() override;


    SkoarpusclePtr skoar_msg(SkoarpuscleMsg *msg, SkoarMinstrelPtr minstrel) override;

    void run(SkoarMinstrelPtr m);
    void on_enter(SkoarMinstrelPtr) override;
};

class SkoarpuscleSkoarpionSig : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleSkoarpionSig" << " :: " ; }
    SkoarString name;
    SkoarpusclePtr arg_list; // is a SkoarpuscleArgList
    SkoarpuscleSkoarpionSig(SkoarNoadPtr);
    ~SkoarpuscleSkoarpionSig() override;

};

class SkoarpuscleArgExpr : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleArgExpr" << " :: " ; }
    SkoarString name;
    SkoarpusclePtr expr; // is a SkoarpuscleExpr
    SkoarpuscleArgExpr(SkoarNoadPtr);
    ~SkoarpuscleArgExpr() override;

};

class SkoarpuscleArgList : public Skoarpuscle {
public:
    void asString(wostream &out) override { 
        out << "SkoarpuscleArgList" << " :: ";
        for (auto x : args_names) 
            out << x << " :: ";
    }
    SkoarDic args_dict;
    list<SkoarString> args_names;

    SkoarpuscleArgList(SkoarNoadPtr);
    ~SkoarpuscleArgList() override;

    void on_enter(SkoarMinstrelPtr) override;

};
