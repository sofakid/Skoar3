#pragma once

#include "skoarpuscle.hpp"
#include "dsp.hpp"

class SkoarpuscleLute : public Skoarpuscle {
public:
    void asString(std::wostream &out) override { out << "SkoarpuscleLute" << " :: " ; }
    bool has_messages;
    SkoarpuscleLute(SkoarToke *);

};

class SkoarpuscleLuteWithArgs : public Skoarpuscle {
public:
    void asString(std::wostream &out) override { out << "SkoarpuscleLuteWithArgs" << " :: " ; }
    bool has_messages;
    SkoarpuscleLuteWithArgs(SkoarToke *);

};