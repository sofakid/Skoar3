#pragma once
#include "skoarcery.hpp"
#include "lex.hpp"
#include "spells.hpp"

class SkoarToker {
public:
	wstring *skoarce;
	size_t i_am_here;
	SkoarToke* i_saw;

	SkoarToker(wstring &skoarce);
	
	SkoarToke* see(ESkoarToke::Kind want);
	SkoarToke* sees(list<ESkoarToke::Kind> *wants);

	SkoarTokePtr burn(ESkoarToke::Kind want);

	void eof();
	void dump();
};
