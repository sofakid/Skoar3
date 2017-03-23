#pragma once
#include "skoarcery.hpp"

#include "lex_fwd.hpp"
#include "noad_fwd.hpp"
#include "skoar_fwd.hpp"
#include "fairy_fwd.hpp"
#include "spells.hpp"

class Skoarmantics {
public:
    
    static void init();
    static Skoarmantics* instance();

	const map<ESkoarNoad::Kind, SpellOfNoadyDecoration> table;

	Skoarmantics();

    void decorate(Skoar* skoar, SkoarNoadPtr noad);

};
