#pragma once
// include this after skoarpuscles


// --- make_skoarpuscle -----------------------------------------------------
template <typename T>
SkoarpusclePtr make_skoarpuscle(T x);

template<>
SkoarpusclePtr make_skoarpuscle(nullptr_t x);

template<>
SkoarpusclePtr make_skoarpuscle(bool x);

template<>
SkoarpusclePtr make_skoarpuscle(SkoarpusclePtr x);

template<>
SkoarpusclePtr make_skoarpuscle(SkoarpionPtr x);

template<>
SkoarpusclePtr make_skoarpuscle(SkoarInt x);

template<>
SkoarpusclePtr make_skoarpuscle(SkoarFloat x);

template<>
SkoarpusclePtr make_skoarpuscle(SkoarString x);

// --- skoarpuscle_ptr -----------------------------------------------------

// cast and get raw pointer 
template <class T> 
T* skoarpuscle_ptr(SkoarpusclePtr p);
