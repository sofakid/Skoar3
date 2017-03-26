#include "dsp.hpp"

// --- SkoarpuscleUGen ---------------------------------------------
SkoarpuscleUGen::SkoarpuscleUGen() {

}

SkoarpuscleUGen::SkoarpuscleUGen(SkoarString, Type) {

}

SkoarString SkoarpuscleUGen::defaultMsg() {
    return SkoarString(L"audio");
}

SkoarpusclePtr SkoarpuscleUGen::add(SkoarpusclePtr) {
    return nullptr;
}

SkoarpusclePtr SkoarpuscleUGen::sub(SkoarpusclePtr) {
    return nullptr;
}

SkoarpusclePtr SkoarpuscleUGen::mul(SkoarpusclePtr) {
        return nullptr;
}

SkoarpusclePtr SkoarpuscleUGen::div(SkoarpusclePtr) {
    return nullptr;
}

SkoarpusclePtr SkoarpuscleUGen::divBy(SkoarpusclePtr) {
    return nullptr;
}

// --- SkoarpuscleMeditationMsg ------------------------------------------
SkoarpuscleUGenWithArgs::SkoarpuscleUGenWithArgs(SkoarString, SkoarpuscleUGen::Type) {

}

// --- SkoarpuscleMeditationMsg ------------------------------------------
SkoarpuscleUGenArgs::SkoarpuscleUGenArgs(SkoarToke *) {

}

