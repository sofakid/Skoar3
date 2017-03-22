#include "all_skoarpuscles.hpp"

// --- make_skoarpuscle -----------------------------------------------------
template <typename T>
SkoarpusclePtr make_skoarpuscle(T x) {
    return make_shared<SkoarpuscleUnknown>();
}
template<>
SkoarpusclePtr make_skoarpuscle(nullptr_t x) {
    return make_shared<SkoarpuscleCat>();
}
template<>
SkoarpusclePtr make_skoarpuscle(bool x) {
    if (x)
        return make_shared<SkoarpuscleTrue>();
    return make_shared<SkoarpuscleFalse>();
}
template<>
SkoarpusclePtr make_skoarpuscle(SkoarpusclePtr x) {
    return x;
}
template<>
SkoarpusclePtr make_skoarpuscle(SkoarpionPtr x) {
    return make_shared<SkoarpuscleSkoarpion>(x);
}
template<>
SkoarpusclePtr make_skoarpuscle(SkoarInt x) {
    return make_shared<SkoarpuscleInt>(x);
}
template<>
SkoarpusclePtr make_skoarpuscle(SkoarFloat x) {
    return make_shared<SkoarpuscleFloat>(x);
}
template<>
SkoarpusclePtr make_skoarpuscle(SkoarString x) {
    return make_shared<SkoarpuscleString>(x);
}

// --- skoarpuscle_ptr -----------------------------------------------------
template <class T>
T* skoarpuscle_ptr(SkoarpusclePtr p) {
    return dynamic_cast<T*>(&*p);
}
