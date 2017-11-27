#pragma once
#include "skoarcery.hpp"
#include "spells.hpp"
#include "all_skoarpuscles.hpp"
#include "minstrel.hpp"
#include "koar.hpp"

typedef function<SkoarpusclePtr(SkoarpusclePtr, SkoarpusclePtr, SkoarMinstrelPtr)> SpellOfMath;

typedef map<ESkoarpuscle::Kind, SpellOfMath> YTable;
typedef map<ESkoarpuscle::Kind, YTable> XTable;

class SkoarOps {
public:

    static void init();
    static SkoarOps* getInstance();

    SpellOfMath lookup (XTable &xtable, SkoarpusclePtr, SkoarpusclePtr);
    SkoarpusclePtr assign (SkoarMinstrelPtr, SkoarpusclePtr, SkoarpusclePtr);

    SkoarpusclePtr add (SkoarMinstrelPtr, SkoarpusclePtr, SkoarpusclePtr);
    SkoarpusclePtr sub (SkoarMinstrelPtr, SkoarpusclePtr, SkoarpusclePtr);

    SkoarpusclePtr mul (SkoarMinstrelPtr, SkoarpusclePtr, SkoarpusclePtr);
    SkoarpusclePtr div (SkoarMinstrelPtr, SkoarpusclePtr, SkoarpusclePtr);

};
