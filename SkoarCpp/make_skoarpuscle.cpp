#include "all_skoarpuscles.hpp"

// --- make_skoarpuscle -----------------------------------------------------

SkoarpusclePtr make_skoarpuscle(nullptr_t x) {
    return make_shared<SkoarpuscleCat>();
}

SkoarpusclePtr make_skoarpuscle(bool x) {
    if (x)
        return make_shared<SkoarpuscleTrue>();
    return make_shared<SkoarpuscleFalse>();
}

SkoarpusclePtr make_skoarpuscle(SkoarpusclePtr x) {
    return x;
}

SkoarpusclePtr make_skoarpuscle(SkoarpionPtr x) {
    return make_shared<SkoarpuscleSkoarpion>(x);
}

SkoarpusclePtr make_skoarpuscle(SkoarInt x) {
    return make_shared<SkoarpuscleInt>(x);
}

SkoarpusclePtr make_skoarpuscle(SkoarFloat x) {
    return make_shared<SkoarpuscleFloat>(x);
}

SkoarpusclePtr make_skoarpuscle(SkoarString x) {
    return make_shared<SkoarpuscleString>(x);
}

// --- skoarpuscle_ptr -----------------------------------------------------
//template <class T>
//T* skoarpuscle_ptr(SkoarpusclePtr p) {
//    return dynamic_cast<T*>(&*p);
//}
