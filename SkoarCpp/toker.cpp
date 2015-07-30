#include "toker.hpp"

// =========
// The Toker
// =========

SkoarToker::SkoarToker(std::string code) {
	this->skoarce = code;
	this->i_am_here = 0;
	this->i_saw = nullptr;
}

SkoarToke *SkoarToker::see(SkoarToke *want) {

	if (i_saw != nullptr) {
		if (typeid(*i_saw) == typeid(*want)) {
			return i_saw;
		}
	} else {
		i_saw = want->match_toke(skoarce, i_am_here);
		return i_saw;
	}

	return nullptr;
}

SkoarToke *SkoarToker::sees(std::list<SkoarToke *> *wants) {

	i_am_here = i_am_here + Toke_Whitespace::burn(skoarce, i_am_here);

	for (SkoarToke *want : *wants) {
		auto x = this->see(want);

		if (x != nullptr) {
			return x;
		}
	}

	return nullptr;
}

SkoarToke * SkoarToker::burn(SkoarToke *want) {

	auto toke = i_saw;
	std::string msg = nullptr;

	if (toke == nullptr) {
		toke = this->see(want);
	}

	if (typeid(toke) == typeid(want)) {
		i_saw = nullptr;
		i_am_here = i_am_here + toke->burn();
		i_am_here = i_am_here + Toke_Whitespace::burn(skoarce, i_am_here);
		return toke;
	};

	//msg = "Tried to burn " + want->name + ", but saw " + toke->asString;

	puts("Toker Fail.");
	puts(msg.c_str());
	this->dump();

	throw new SkoarError(msg);
}

void SkoarToker::eof() {
	Toke_EOF::burn(skoarce, i_am_here);
}

void SkoarToker::dump() {
		/*("\nToker Dump" ++
		"\nhere   : " ++i_am_here.asString++
		"\nsaw    : " ++i_saw.asString++
		"\nskoarce: " ++skoarce.copyRange(0, i_am_here)
		++ "_$_" ++skoarce.copyRange(i_am_here, skoarce.size)).postln;
	  */
}