#pragma once
#include "skoarcery.hpp"
#include "lex_fwd.hpp"
#include "skoarpion_fwd.hpp"
#include "skoarpuscle.hpp"


class SkoarpuscleRest : public Skoarpuscle {
public:
    SkoarpuscleRest(SkoarToke *);
};

class SkoarpuscleBeat : public Skoarpuscle {
public:
    SkoarpuscleBeat(SkoarToke *);
};


class SkoarpuscleDuration : public Skoarpuscle {
public:
    SkoarpuscleDuration(SkoarToke *);
};

class SkoarpuscleExactBeat : public Skoarpuscle {
public:
    SkoarpuscleExactBeat(SkoarToke *);
};

class SkoarpuscleExactRest : public Skoarpuscle {
public:
    SkoarpuscleExactRest(SkoarToke *);
};
