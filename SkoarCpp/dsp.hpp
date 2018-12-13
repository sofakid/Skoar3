#pragma once

#include "skoarpuscle.hpp"

class SkoarpuscleUGen : public Skoarpuscle {
public:
    void asString(std::wostream &out) override { out << "SkoarpuscleUGen" << " :: " ; }
    enum class Type {
        audio,
        control,
        demand
    };

    SkoarpuscleUGen();
    SkoarpuscleUGen(SkoarString, Type);

    SkoarString defaultMsg();

    SkoarpusclePtr add(SkoarpusclePtr);
    SkoarpusclePtr sub(SkoarpusclePtr);
    SkoarpusclePtr mul(SkoarpusclePtr);
    SkoarpusclePtr div(SkoarpusclePtr);
    SkoarpusclePtr divBy(SkoarpusclePtr);

};

class SkoarpuscleUGenWithArgs : public SkoarpuscleUGen {
public:
    void asString(std::wostream &out) override { out << "SkoarpuscleUGenWithArgs" << " :: " ; }
    SkoarpuscleUGenWithArgs(SkoarString, SkoarpuscleUGen::Type);
};

class SkoarpuscleUGenArgs : public Skoarpuscle {
public:
    void asString(std::wostream &out) override { out << "SkoarpuscleUGenArgs" << " :: " ; }
    SkoarpuscleUGenArgs(SkoarToke *);
};
