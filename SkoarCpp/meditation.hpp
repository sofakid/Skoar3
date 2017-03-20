#pragma once
#include "skoarpuscle.hpp"

class SkoarpuscleMeditation : public Skoarpuscle {
public:
    SkoarpuscleMeditation(Skoar *skoar, SkoarNoadPtr noad);
};

class SkoarpuscleMeditationMsg : public Skoarpuscle {
public:
    SkoarpuscleMeditationMsg(Skoar *skoar, SkoarNoadPtr noad);
};
