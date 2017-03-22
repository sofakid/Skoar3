#pragma once
// include this after skoarpuscles


// --- make_skoarpuscle -----------------------------------------------------

SkoarpusclePtr make_skoarpuscle(nullptr_t x);
SkoarpusclePtr make_skoarpuscle(bool x);
SkoarpusclePtr make_skoarpuscle(SkoarpusclePtr x);
SkoarpusclePtr make_skoarpuscle(SkoarpionPtr x);
SkoarpusclePtr make_skoarpuscle(SkoarInt x);
SkoarpusclePtr make_skoarpuscle(SkoarFloat x);
SkoarpusclePtr make_skoarpuscle(SkoarString x);

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
