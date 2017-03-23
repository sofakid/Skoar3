#pragma once
#include "skoarpuscle.hpp"

class SkoarpuscleMeditation : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleMeditation" << " :: " ; }
    SkoarpuscleMeditation(Skoar *skoar, SkoarNoadPtr noad);
};

class SkoarpuscleMeditationMsg : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleMeditationMsg" << " :: " ; }
    SkoarpuscleMeditationMsg(Skoar *skoar, SkoarNoadPtr noad);
};
