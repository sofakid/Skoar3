#pragma once
#include "skoarcery.hpp"
#include "skoarpuscle_fwd.hpp"
#include "spells.hpp"

class SkoarDic {
public:
	map<SkoarString, SkoarpusclePtr> table;

	//Skoarpuscle *not_found;

	SkoarDic();

	SkoarpusclePtr &SkoarDic::operator[](SkoarString *key);
	SkoarpusclePtr &SkoarDic::operator[](SkoarString &key);
};

class SkoarEvent : SkoarDic {
public:

	void from(SkoarDicPtr);

};