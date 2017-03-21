#pragma once
// include this after skoarpuscles

template <typename T>
static SkoarpusclePtr make_skoarpuscle(T x) {
    auto u = make_shared<SkoarpuscleUnknown>();
    u->val = x;
    return u;
}
template<>
static SkoarpusclePtr make_skoarpuscle(nullptr_t x) {
    return make_shared<SkoarpuscleCat>();
}
template<>
static SkoarpusclePtr make_skoarpuscle(bool x) {
    if (x)
        return make_shared<SkoarpuscleTrue>();
    return make_shared<SkoarpuscleFalse>();
}
template<>
static SkoarpusclePtr make_skoarpuscle(SkoarpusclePtr x) {
    return x;
}
template<>
static SkoarpusclePtr make_skoarpuscle(SkoarpionPtr x) {
    return make_shared<SkoarpuscleSkoarpion>(x);
}
template<>
static SkoarpusclePtr make_skoarpuscle(SkoarInt x) {
    return make_shared<SkoarpuscleInt>(x);
}
template<>
static SkoarpusclePtr make_skoarpuscle(SkoarFloat x) {
    return make_shared<SkoarpuscleFloat>(x);
}
template<>
static SkoarpusclePtr make_skoarpuscle(SkoarString x) {
    return make_shared<SkoarpuscleString>(x);
}
