#include "dsp.hpp"

// --- SkoarpuscleUGen ---------------------------------------------
SkoarpuscleUGen::SkoarpuscleUGen() {

}

SkoarpuscleUGen::SkoarpuscleUGen(SkoarString, Type) {

}

SkoarString SkoarpuscleUGen::defaultMsg() {
    return SkoarString(L"audio");
}

// --- SkoarpuscleMeditationMsg ------------------------------------------
SkoarpuscleUGenWithArgs::SkoarpuscleUGenWithArgs(SkoarString, SkoarpuscleUGen::Type) {

}

// --- SkoarpuscleMeditationMsg ------------------------------------------
SkoarpuscleUGenArgs::SkoarpuscleUGenArgs(SkoarToke *) {

}

