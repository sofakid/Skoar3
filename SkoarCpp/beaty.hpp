#pragma once
#include "skoarcery.hpp"
#include "lex_fwd.hpp"
#include "skoarpion_fwd.hpp"
#include "skoarpuscle.hpp"

class SkoarpuscleDuration : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleDuration" << " :: " << minutes << ":" << seconds; }

    SkoarInt minutes;
    SkoarFloat seconds;

    SkoarpuscleDuration(SkoarToke *);
    SkoarpuscleDuration(SkoarInt, SkoarFloat);
    void on_enter(SkoarMinstrelPtr) override;
};

class SkoarpuscleExactBeat : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleExactBeat" << " :: " ; }
    SkoarpuscleExactBeat(SkoarToke *);
    void on_enter(SkoarMinstrelPtr) override;
    void after(SkoarMinstrelPtr);
};

class SkoarpuscleExactRest : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleExactRest" << " :: " ; }
    SkoarpuscleExactRest(SkoarToke *);
    void on_enter(SkoarMinstrelPtr) override;
    void after(SkoarMinstrelPtr);
};


class SkoarpuscleBeat : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleBeat" << " :: " << val; }
    static SkoarFloat beat_short(SkoarString, SkoarInt);
    static SkoarFloat beat_long(SkoarString, SkoarInt);

    SkoarFloat val;

    SkoarString s;
    bool is_staccato;
    bool has_tie;
    bool is_grace;
    bool is_exact;

    SkoarpuscleBeat(SkoarToke *);
    void on_enter_sometimes(SkoarMinstrelPtr);
};

class SkoarpuscleRest : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleRest" << " :: " << val; }

    SkoarFloat val;

    SkoarString s;
    bool is_staccato;
    bool has_tie;
    bool is_grace;
    bool is_exact;

    SkoarpuscleRest(SkoarToke *);
    void on_enter_sometimes(SkoarMinstrelPtr);
};
