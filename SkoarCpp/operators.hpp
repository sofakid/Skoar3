#pragma once
#include "skoarcery.hpp"
#include "spells.hpp"
#include "all_skoarpuscles.hpp"
#include "minstrel.hpp"
#include "koar.hpp"

typedef std::function<SkoarpusclePtr(SkoarpusclePtr, SkoarpusclePtr, SkoarMinstrelPtr)> SpellOfMath;
typedef std::function<SkoarFloat(SkoarpusclePtr, SkoarpusclePtr, SkoarMinstrelPtr)> SpellOfCmp;

typedef std::map<ESkoarpuscle::Kind, SpellOfMath> YTable;
typedef std::map<ESkoarpuscle::Kind, YTable> XTable;

typedef std::map<ESkoarpuscle::Kind, SpellOfCmp> YCmpTable;
typedef std::map<ESkoarpuscle::Kind, YCmpTable> XCmpTable;

class SkoarOps {
public:

    static void init();
    static SkoarOps* getInstance();

    SpellOfMath lookup (XTable &xtable, SkoarpusclePtr, SkoarpusclePtr);
    SpellOfCmp lookup (XCmpTable &xtable, SkoarpusclePtr, SkoarpusclePtr);

    SkoarpusclePtr assign (SkoarMinstrelPtr, SkoarpusclePtr, SkoarpusclePtr);

    SkoarpusclePtr add (SkoarMinstrelPtr, SkoarpusclePtr, SkoarpusclePtr);
    SkoarpusclePtr sub (SkoarMinstrelPtr, SkoarpusclePtr, SkoarpusclePtr);

    SkoarpusclePtr mul (SkoarMinstrelPtr, SkoarpusclePtr, SkoarpusclePtr);
    SkoarpusclePtr div (SkoarMinstrelPtr, SkoarpusclePtr, SkoarpusclePtr);
    SkoarpusclePtr mod (SkoarMinstrelPtr, SkoarpusclePtr, SkoarpusclePtr);

    SkoarpusclePtr neq (SkoarMinstrelPtr, SkoarpusclePtr, SkoarpusclePtr);
    SkoarpusclePtr eq (SkoarMinstrelPtr, SkoarpusclePtr, SkoarpusclePtr);

    SkoarpusclePtr gt (SkoarMinstrelPtr, SkoarpusclePtr, SkoarpusclePtr);
    SkoarpusclePtr gte (SkoarMinstrelPtr, SkoarpusclePtr, SkoarpusclePtr);

    SkoarpusclePtr lt (SkoarMinstrelPtr, SkoarpusclePtr, SkoarpusclePtr);
    SkoarpusclePtr lte (SkoarMinstrelPtr, SkoarpusclePtr, SkoarpusclePtr);

    SkoarpusclePtr and_ (SkoarMinstrelPtr, SkoarpusclePtr, SkoarpusclePtr);
    SkoarpusclePtr or_ (SkoarMinstrelPtr, SkoarpusclePtr, SkoarpusclePtr);

};
