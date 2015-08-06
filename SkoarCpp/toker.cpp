#include "toker.hpp"
#include "lex.hpp"
#include "exception.hpp"

// =========
// The Toker
// =========

SkoarToker::SkoarToker(wstring &skoarce) {
	this->i_am_here = 0;
	this->i_saw = nullptr;
	this->skoarce = &skoarce;
	this->dispensary = new SkoarDispensary();
}

SkoarToke *SkoarToker::see(ESkoarToke::Kind want) {

	if (i_saw != nullptr) {
		if (i_saw->kind == want) {
			return i_saw;
		}
		return nullptr;
	} 
	
	i_saw = dispensary->match_toke(want, skoarce, i_am_here);
	return i_saw;
	
}

SkoarToke *SkoarToker::sees(std::list<ESkoarToke::Kind> *wants) {

	i_am_here = i_am_here + Toke_Whitespace::burn(skoarce, i_am_here);

	for (auto want : *wants) {
		auto x = this->see(want);

		if (x != nullptr) {
			return x;
		}
	}

	return nullptr;
}

SkoarToke * SkoarToker::burn(ESkoarToke::Kind want) {

	auto toke = i_saw;

	if (toke == nullptr) {
		toke = this->see(want);
	}

	if (toke != nullptr && toke->kind == want) {
		i_saw = nullptr;
		i_am_here = i_am_here + toke->burn();
		i_am_here = i_am_here + Toke_Whitespace::burn(skoarce, i_am_here);
		return toke;
	};

	//msg = "Tried to burn " + want->name + ", but saw " + toke->asString;

	puts("Toker Fail.");
	this->dump();

	throw new SkoarError(*(new wstring(L"toker fail")));
}

void SkoarToker::eof() {
	Toke_Eof::burn(skoarce, i_am_here);
}

void SkoarToker::dump() {
		/*("\nToker Dump" ++
		"\nhere   : " ++i_am_here.asString++
		"\nsaw    : " ++i_saw.asString++
		"\nskoarce: " ++skoarce.copyRange(0, i_am_here)
		++ "_$_" ++skoarce.copyRange(i_am_here, skoarce.size)).postln;
	  */
}