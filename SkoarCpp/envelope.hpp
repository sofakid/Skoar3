#pragma once

#include "skoarpuscle.hpp"

class SkoarpuscleEnvelope : public Skoarpuscle {
public:
    void asString(wostream &out) override { out << "SkoarpuscleEnvelope" << " :: " ; }
    SkoarpuscleEnvelope();

};