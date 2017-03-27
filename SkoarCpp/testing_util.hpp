#pragma once
#include "catch.hpp"
#include "skoarcery.hpp"
#include "skoar_public.hpp"
#include "all_skoarpuscles.hpp"
#include "memories.hpp"

bool check_skoarpuscle_int(SkoarpusclePtr p, SkoarInt v) {
    return check_skoarpuscle_val<SkoarpuscleInt, SkoarInt>(p, v);
}

bool check_skoarpuscle_float(SkoarpusclePtr p, SkoarFloat v) {

    auto x = is_skoarpuscle<SkoarpuscleFloat>(p);
    if (x == false)
        return false;

    auto ptr = skoarpuscle_ptr<SkoarpuscleFloat>(p);

    if (typeid(ptr->val) != typeid(SkoarFloat))
        return false;

    // don't compare float values with equality, check if it's close.
    auto epsilon = v * 0.0001;
    if ((ptr->val < (v + epsilon)) && (ptr->val > (v - epsilon)))
        return true;

    return false;
}

bool check_skoarpuscle_num(SkoarpusclePtr p, SkoarInt v) {
    if (is_skoarpuscle<SkoarpuscleInt>(p)) {

        if (check_skoarpuscle_int(p, v))
            return true;

        if (check_skoarpuscle_float(p, static_cast<SkoarFloat>(v)))
            return true;
    }

    if (is_skoarpuscle<SkoarpuscleFloat>(p)) {

        if (check_skoarpuscle_float(p, static_cast<SkoarFloat>(v)))
            return true;
    }

    return false;
}

bool check_skoarpuscle_num(SkoarpusclePtr p, SkoarFloat v) {
    return check_skoarpuscle_float(p, v);
}



bool check_skoarpuscle_string(SkoarpusclePtr p, SkoarString v) {
    return check_skoarpuscle_val<SkoarpuscleString, SkoarString>(p, v);
}

bool check_skoarpuscle_symbol(SkoarpusclePtr p, SkoarString v) {
    return check_skoarpuscle_val<SkoarpuscleSymbol, SkoarString>(p, v);
}

