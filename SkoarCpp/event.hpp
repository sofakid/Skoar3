#pragma once
#include "skoarcery.hpp"
#include "skoarpuscle_fwd.hpp"

class SkoarDic {
public:
	map<string, Skoarpuscle*> table;

	//Skoarpuscle *not_found;

	SkoarDic();

	Skoarpuscle* &SkoarDic::operator[](string *key);
	Skoarpuscle* &SkoarDic::operator[](string key);
};

class SkoarEvent : SkoarDic {
public:

	void from(SkoarDic *);

};