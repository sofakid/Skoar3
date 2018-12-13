#pragma once
#include "skoarcery.hpp"
#include "skoarpuscle_fwd.hpp"
#include "spells.hpp"

class SkoarDic {
public:
    std::map<SkoarString, SkoarpusclePtr> table;

    //Skoarpuscle *not_found;

    SkoarDic();
    virtual ~SkoarDic();

    void put(SkoarString k, SkoarpusclePtr v);
    SkoarpusclePtr at(const SkoarString &k);

    void clear();
    size_t size();

};

class SkoarEvent : public SkoarDic {
public:
    SkoarEvent();
    ~SkoarEvent() override;

    void from(SkoarDicPtr);

    std::shared_ptr<SkoarEvent> duplicate ();
};

class SkoarEventStream {

    SkoarEventStream();
    ~SkoarEventStream();

    SkoarEventPtr next();

};