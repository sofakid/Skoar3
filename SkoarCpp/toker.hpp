#pragma once
#include "skoarcery.hpp"
#include "lex_fwd.hpp"

class SkoarToker {
public:
	wstring *skoarce;
	size_t i_am_here;
	SkoarToke *i_saw;

	SkoarToker(wstring &skoarce);

	SkoarToke *see(SkoarToke *want);
	SkoarToke *sees(list<SkoarToke *> *wants);

	SkoarToke *burn(SkoarToke *want);

	void eof();
	void dump();
};
