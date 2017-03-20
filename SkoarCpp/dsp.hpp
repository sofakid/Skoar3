#pragma once

#include "skoarpuscle.hpp"

class SkoarpuscleUGen : public Skoarpuscle {
public:
    SkoarpuscleUGen(SkoarToke *);
};

class SkoarpuscleUGenWithArgs : public Skoarpuscle {
public:
    SkoarpuscleUGenWithArgs(SkoarToke *);
};

class SkoarpuscleUGenArgs : public Skoarpuscle {
public:
    SkoarpuscleUGenArgs(SkoarToke *);
};
