#pragma once
#include "skoarcery.hpp"
#include "skoarpuscle_fwd.hpp"

class SkoarDic {
public:
	map<wstring, Skoarpuscle*> table;

	//Skoarpuscle *not_found;

	SkoarDic();

	Skoarpuscle* &SkoarDic::operator[](wstring *key);
	Skoarpuscle* &SkoarDic::operator[](wstring key);
};

class SkoarEvent : SkoarDic {
public:

	void from(SkoarDic *);

};