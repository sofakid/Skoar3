#pragma once
#include "skoarcery.hpp"
#include "lex.hpp"
#include "spells.hpp"

class SkoarToker {
public:
    static void init();

    std::wstring *skoarce;
    size_t i_am_here;
    SkoarToke* i_saw;

    SkoarToker(std::wstring &skoarce);
    
    SkoarToke* see(ESkoarToke::Kind want);
    SkoarToke* sees(ListOfSkoarTokeKinds *wants);

    SkoarTokePtr burn(ESkoarToke::Kind want, SkoarNoadPtr noad);

    void eof();
    void dump();
};
