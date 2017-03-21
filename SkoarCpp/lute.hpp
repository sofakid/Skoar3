#pragma once

#include "skoarpuscle.hpp"
#include "dsp.hpp"

class SkoarpuscleLute : public Skoarpuscle {
public:
    bool has_messages;
    SkoarpuscleLute(SkoarToke *);

};

class SkoarpuscleLuteWithArgs : public Skoarpuscle {
public:
    bool has_messages;
    SkoarpuscleLuteWithArgs(SkoarToke *);

};