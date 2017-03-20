#pragma once

#include "skoarpuscle.hpp"

class SkoarpuscleUGen : public Skoarpuscle {
public:
    enum class Type {
        audio,
        control,
        demand
    };

    SkoarpuscleUGen(SkoarString, Type);
};

class SkoarpuscleUGenWithArgs : public Skoarpuscle {
public:
    SkoarpuscleUGenWithArgs(SkoarString, SkoarpuscleUGen::Type);
};

class SkoarpuscleUGenArgs : public Skoarpuscle {
public:
    SkoarpuscleUGenArgs(SkoarToke *);
};
