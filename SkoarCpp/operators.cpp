#include "operators.hpp"

static SkoarOps* instance;

void SkoarOps::init() {
    static bool initialized = false;
    if (initialized == false) {
        instance = new SkoarOps();
    }
}

SkoarOps* SkoarOps::getInstance() {
    return instance;
}

SpellOfMath SkoarOps::lookup(XTable &xtable, SkoarpusclePtr x, SkoarpusclePtr y) {
    static const SpellOfMath cat([](SkoarpusclePtr, SkoarpusclePtr, SkoarMinstrelPtr) {
        return make_skoarpuscle(nullptr);
    });

    try {
        auto ytable = xtable.at(x->kind);

        try {
            return ytable.at(y->kind);
        }
        catch (const std::out_of_range&) {
            return ytable.at(ESkoarpuscle::Any);
        }
    }
    catch (const std::out_of_range&) {
    }
    return cat;
}

SkoarpusclePtr SkoarOps::assign(SkoarMinstrelPtr m, SkoarpusclePtr x, SkoarpusclePtr y) {
    SpellOfMath f = lookup(assignment, y, x);
    return m->fairy->impress(f(y, x, m));
}

SkoarpusclePtr SkoarOps::add(SkoarMinstrelPtr m, SkoarpusclePtr x, SkoarpusclePtr y) {
    const SpellOfMath &f = lookup(addition, x, y);
    return m->fairy->impress(f(x, y, m));
}

SkoarpusclePtr SkoarOps::sub(SkoarMinstrelPtr m, SkoarpusclePtr x, SkoarpusclePtr y) {
    const SpellOfMath &f = lookup(addition, x, y);
    return m->fairy->impress(f(x, y, m));
}

SkoarpusclePtr SkoarOps::mul(SkoarMinstrelPtr m, SkoarpusclePtr x, SkoarpusclePtr y) {
    const SpellOfMath &f = lookup(addition, x, y);
    return m->fairy->impress(f(x, y, m));
}

SkoarpusclePtr SkoarOps::div(SkoarMinstrelPtr m, SkoarpusclePtr x, SkoarpusclePtr y) {
    const SpellOfMath &f = lookup(addition, x, y);
    return m->fairy->impress(f(x, y, m));
}

