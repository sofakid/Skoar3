#pragma once
#include "skoarcery.hpp"
#include "skoarpuscle_fwd.hpp"
#include "spells.hpp"

class SkoarDic {
public:
	map<wstring, SkoarpusclePtr> table;

	//Skoarpuscle *not_found;

	SkoarDic();

	SkoarpusclePtr &SkoarDic::operator[](wstring *key);
	SkoarpusclePtr &SkoarDic::operator[](wstring key);
};

class SkoarEvent : SkoarDic {
public:

	void from(SkoarDic *);

};