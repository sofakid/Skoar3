#pragma once
#include "skoarcery.hpp"
#include "lex.hpp"

class SkoarToker {
public:
	SkoarDispensary *dispensary;
	wstring *skoarce;
	size_t i_am_here;
	SkoarToke *i_saw;

	SkoarToker(wstring &skoarce);
	
	SkoarToke *see(ESkoarToke::Kind want);
	SkoarToke *sees(list<ESkoarToke::Kind> *wants);

	SkoarToke *burn(ESkoarToke::Kind want);

	void eof();
	void dump();
};
