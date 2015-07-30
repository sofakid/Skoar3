#pragma once
#include "skoar.hpp"
#include "lex.hpp"

class SkoarToker {
public:
	string skoarce;
	size_t i_am_here;
	SkoarToke *i_saw;

	SkoarToker(string code);

	SkoarToke *see(SkoarToke *want);
	SkoarToke *sees(list<SkoarToke *> *wants);

	SkoarToke *burn(SkoarToke *want);

	void eof();
	void dump();
};
