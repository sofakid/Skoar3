#pragma once
#include "skoarcery.hpp"
#include "skoarpuscle_fwd.hpp"
#include "spells.hpp"

class SkoarDic {
public:
	map<SkoarString, SkoarpusclePtr> table;

	//Skoarpuscle *not_found;

	SkoarDic();
    ~SkoarDic();

	SkoarpusclePtr SkoarDic::operator[](SkoarString *key);
    SkoarpusclePtr SkoarDic::operator[](SkoarString &key);
    SkoarpusclePtr SkoarDic::operator[](const SkoarString &key);
    SkoarpusclePtr SkoarDic::operator[](const wchar_t *key);
};

class SkoarEvent : SkoarDic {
public:

	void from(SkoarDicPtr);
};