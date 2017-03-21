#pragma once

#include "skoarpuscle.hpp"

class SkoarpuscleUGen : public Skoarpuscle {
public:
    enum class Type {
        audio,
        control,
        demand
    };

    SkoarpuscleUGen();
    SkoarpuscleUGen(SkoarString, Type);

    SkoarString defaultMsg();
};

class SkoarpuscleUGenWithArgs : public SkoarpuscleUGen {
public:
    SkoarpuscleUGenWithArgs(SkoarString, SkoarpuscleUGen::Type);
};

class SkoarpuscleUGenArgs : public Skoarpuscle {
public:
    SkoarpuscleUGenArgs(SkoarToke *);
};
