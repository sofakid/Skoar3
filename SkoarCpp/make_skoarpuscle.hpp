#pragma once
// include this after skoarpuscles
#include "skoarpion.hpp"

// --- make_skoarpuscle -----------------------------------------------------

inline SkoarpusclePtr make_skoarpuscle(nullptr_t x) {
    return make_shared<SkoarpuscleCat>();
}

inline SkoarpusclePtr make_skoarpuscle(SkoarpusclePtr x) {
    return x;
}

inline SkoarpusclePtr make_skoarpuscle(SkoarpionPtr x) {
    return make_shared<SkoarpuscleSkoarpion>(x);
}

inline SkoarpusclePtr make_skoarpuscle(SkoarInt x) {
    return make_shared<SkoarpuscleInt>(x);
}

inline SkoarpusclePtr make_skoarpuscle(int x) {
    return make_skoarpuscle(static_cast<SkoarInt>(x));
}

inline SkoarpusclePtr make_skoarpuscle(SkoarFloat x) {
    return make_shared<SkoarpuscleFloat>(x);
}

inline SkoarpusclePtr make_skoarpuscle(SkoarString x) {
    return make_shared<SkoarpuscleString>(x);
}

inline SkoarpusclePtr make_skoarpuscle(bool x) {
    if (x)
        return make_shared<SkoarpuscleTrue>();
    return make_shared<SkoarpuscleFalse>();
}

// --- skoarpuscle_ptr -----------------------------------------------------

// cast and get raw pointer 
template <class T> 
inline T* skoarpuscle_ptr(SkoarpusclePtr p) {
    return dynamic_cast<T*>(&*p);
}

// --- is_skoarpuscle -----------------------------------------------------

// nullptr check and type check 
template <class T>
inline bool is_skoarpuscle(SkoarpusclePtr p) {
    if (p == nullptr)
        return false;

    return (typeid(*p) == typeid(T));
}

// move this to lex.hpp after it works

template <ESkoarToke::Kind T>
inline bool is_toke(SkoarToke *p) {
    if (p == nullptr)
        return false;

    return (p->kind == T);
}

/*
template <typename S, typename R>
R* flatten_skoarpuscle(SkoarpusclePtr p) {
    if (is_skoarpuscle<S>(p)) {
        return &(skoarpuscle_ptr<S>(p)->val);
    }
    return nullptr;
}
*/
