#pragma once
#include "skoarcery.hpp"

#include "lex_fwd.hpp"
#include "spells.hpp"

class SkoarTokeInspector {
public:
    static void init();
    static SkoarTokeInspector* instance();
    SkoarTokeInspector ();
    
    const map<ESkoarToke::Kind, SpellOfTokeyDecoration> table;

    void decorate (Skoar* skoar, SkoarNoadPtr noad, SkoarToke* toke);
};
