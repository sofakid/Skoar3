#pragma once
#include "skoarpuscle.hpp"

class SkoarpuscleKey : public Skoarpuscle {
public:
    SkoarpusclePtr scale;
    SkoarpusclePtr scale_name;
    SkoarpusclePtr root;

    SkoarpuscleKey (SkoarpusclePtr);
    ~SkoarpuscleKey () override;

    void apply (SkoarEventPtr);
    void asString (wostream&) override;

};


class SkoarpuscleNoat : public Skoarpuscle
{
public:
    SkoarString lexeme;
    bool low;
    int val;
    int sharps;

    SkoarpusclePtr scale;

    SkoarpuscleNoat (SkoarString&);
    SkoarpuscleNoat (SkoarString&, bool, int, int);
    ~SkoarpuscleNoat () override;
    void asString (wostream&) override;
    void typeAsString (wostream&) override;
    void valAsString (wostream&) override;

    //void *asNoat () override;
    void on_enter (SkoarMinstrelPtr) override;
    SkoarpusclePtr duplicate () override;
    void execute (SkoarMinstrelPtr m);
};

class SkoarpuscleChoard : public Skoarpuscle
{
public:
    SkoarString lexeme;
    SkoarString letter;
    int sharps;
    ListOfSkoarpusclesPtr val;

    SkoarpusclePtr scale;

    SkoarpuscleChoard (SkoarString&);
    SkoarpuscleChoard (SkoarString&, SkoarString&, int, ListOfSkoarpusclesPtr);
    ~SkoarpuscleChoard () override;
    void asString (wostream&) override;
    void typeAsString (wostream&) override;
    void valAsString (wostream&) override;

    //void *asNoat () override;
    void on_enter (SkoarMinstrelPtr) override;
    SkoarpusclePtr duplicate () override;
    void execute (SkoarMinstrelPtr m);
};
