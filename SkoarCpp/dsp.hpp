#pragma once

#include "skoarpuscle.hpp"

class SkoarpuscleUgen : public Skoarpuscle {
public:
    SkoarpuscleUgen(SkoarToke *);
};

class SkoarpuscleUGenWithArgs : public Skoarpuscle {
public:
    SkoarpuscleUGenWithArgs(SkoarToke *);
};

class SkoarpuscleUGenArgs : public Skoarpuscle {
public:
    SkoarpuscleUGenArgs(SkoarToke *);
};
