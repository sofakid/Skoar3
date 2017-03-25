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

    void put(SkoarString k, SkoarpusclePtr v);
    SkoarpusclePtr at(const SkoarString &k);

};

class SkoarEvent : public SkoarDic {
public:
	void from(SkoarDicPtr);
};

class SkoarEventStream {

    SkoarEventStream();
    ~SkoarEventStream();

    SkoarEventPtr next();

};