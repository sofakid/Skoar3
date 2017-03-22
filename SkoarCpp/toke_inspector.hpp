#pragma once
#include "skoarcery.hpp"

#include "lex_fwd.hpp"
#include "spells.hpp"

class SkoarTokeInspector {

public:
    const map<ESkoarToke::Kind, SpellOfTokeyDecoration> table;

    SkoarTokeInspector();

    void decorate(SkoarToke* toke, SkoarNoadPtr noad);

};
