#pragma once
#include "skoarpuscle.hpp"
#include "event.hpp"

class SkoarpuscleSkoarpion : public Skoarpuscle
{
public:
    SkoarpionPtr val;
    SkoarpusclePtr args;
    ListOfSkoarStrings capture_names;
    ListOfSkoarpuscles captures;
    ListOfSkoarStrings expoart_names;

    SkoarpuscleSkoarpion (const SkoarpuscleSkoarpion*);
    SkoarpuscleSkoarpion (SkoarpionPtr);
    SkoarpuscleSkoarpion (SkoarpionPtr, SkoarNoadPtr);

    SkoarpuscleSkoarpion (SkoarpusclePtr, SkoarpusclePtr);
    ~SkoarpuscleSkoarpion () override;

    void clear () override;

    void run (SkoarMinstrelPtr m);
    void on_enter (SkoarMinstrelPtr) override;
    void asString (wostream &out) override;

    void bind_captures (SkoarMinstrelPtr m);

};

class SkoarpuscleArgExpr : public Skoarpuscle
{
public:
    SkoarString name;

    std::vector<SkoarNoadite> expr;

    SkoarpuscleArgExpr (SkoarNoadPtr);
    ~SkoarpuscleArgExpr () override;
    void clear () override;

    void asString (wostream &out) override;

    SkoarpusclePtr flatten (SkoarMinstrelPtr);

};

class SkoarpuscleArgList : public Skoarpuscle
{
public:
    map<SkoarString, SkoarpusclePtr> args_dict;
    ListOfSkoarStrings args_names;
    SkoarNoadPtr noad;

    SkoarpuscleArgList (SkoarNoadPtr);
    ~SkoarpuscleArgList () override;
    void clear () override;

    void on_enter (SkoarMinstrelPtr) override;
    void asString (wostream &out) override;
};

// for koar->state, we don't pass these around
class SkoarpuscleProjections : public Skoarpuscle
{
public:
    map<SkoarString, SkoarpionProjectionPtr> map;

    SkoarpuscleProjections (ListOfSkoarpionProjectionsPtr);
    ~SkoarpuscleProjections () override;
    void clear () override;

    void asString (wostream &out) override;
};

class SkoarpuscleCapture : public Skoarpuscle
{
public:
    SkoarpuscleCapture (const SkoarString&);
    ~SkoarpuscleCapture ();

    const SkoarString name;
    SkoarpusclePtr val;

    static void Capture (SkoarpusclePtr&, SkoarMinstrelPtr);
    void asString (wostream &out) override;
};