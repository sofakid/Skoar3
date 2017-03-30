#pragma once
#include "catch.hpp"
#include "skoarcery.hpp"
#include "skoar_public.hpp"
#include "all_skoarpuscles.hpp"
#include "memories.hpp"

string SkoarString_to_s(SkoarString ws);

bool check_skoarpuscle_int(SkoarpusclePtr p, SkoarInt v);
bool check_skoarpuscle_float(SkoarpusclePtr p, SkoarFloat v);
bool check_skoarpuscle_freq(SkoarpusclePtr p, SkoarFloat v);
bool check_skoarpuscle_num(SkoarpusclePtr p, SkoarInt v);
bool check_skoarpuscle_num(SkoarpusclePtr p, SkoarFloat v);

bool check_skoarpuscle_string(SkoarpusclePtr p, SkoarString v);
bool check_skoarpuscle_symbol(SkoarpusclePtr p, SkoarString v);

typedef shared_ptr<vector<SkoarEventPtr>> EventsPtr;


VectorOfSkoarEventsPtr skoar_get_events(Skoar* skoar);

// --- make_event ------------------------------------------------

template<typename Type, typename... Args>
void make_event_r(SkoarEventPtr e, SkoarString key, Type value, const Args&... args)
{
    e->put(key, make_skoarpuscle(value));
    make_event_r(e, args...);
}

void make_event_r(SkoarEventPtr);

template<typename... Args>
SkoarEventPtr make_event(const Args&... args) {
    SkoarEventPtr e = make_shared<SkoarEvent>();
    make_event_r(e, args...);
    return e;
}


// --- make_events_vec ------------------------------------------------
class MakeEventSep {};

template<typename Type, typename... Args>
void make_events_vec_r(VectorOfSkoarEventsPtr vec, SkoarEventPtr e, const SkoarString& key, const Type& value, const Args&... args)
{
    e->put(key, make_skoarpuscle(value));
    make_events_vec_r(vec, e, args...);
}

template<typename... Args>
void make_events_vec_r(VectorOfSkoarEventsPtr vec, SkoarEventPtr e, const MakeEventSep&, const Args&... args)
{
    vec->push_back(e);
    SkoarEventPtr e_new = make_shared<SkoarEvent>();
    make_events_vec_r(vec, e_new, args...);
}

void make_events_vec_r(VectorOfSkoarEventsPtr, SkoarEventPtr);

template<typename... Args>
VectorOfSkoarEventsPtr make_events_vec(const Args&... args) {
    VectorOfSkoarEventsPtr vec = make_shared<VectorOfSkoarEvents>();
    SkoarEventPtr e = make_shared<SkoarEvent>();
    make_events_vec_r(vec, e, args...);
    return vec;
}

// --- make_listy ---------------------------------------------------------------------

template<typename Type, typename... Args>
void make_listy_r(ListOfSkoarpusclesPtr listy, const Type& value, const Args&... args)
{
    listy->push_back(make_skoarpuscle(value));
    make_listy_r(listy, args...);
}

void make_listy_r(ListOfSkoarpusclesPtr);

template<typename... Args>
ListOfSkoarpusclesPtr make_listy(const Args&... args) {
    auto listy = make_shared<ListOfSkoarpuscles>();
    make_listy_r(listy, args...);
    return listy;
}


// --- comparing event vectors --------------------------------------------------------

void compare_skoarpuscles_equal(SkoarpusclePtr desire, SkoarpusclePtr reality);
void require_desire_in_event(SkoarString k, SkoarpusclePtr v, SkoarEventPtr ev);
void require_subset_of_event(SkoarEventPtr desire, SkoarEventPtr ev);
void compare_desires_to_events(VectorOfSkoarEventsPtr desires, VectorOfSkoarEventsPtr events);

void compare_lists(ListOfSkoarpusclesPtr desires, ListOfSkoarpusclesPtr realities);


// --- run skoars and expect events ---------------------------------------------------

void run_and_expect(SkoarString skoarce, VectorOfSkoarEventsPtr desires); 
void run_and_expect_d(SkoarString skoarce, VectorOfSkoarEventsPtr desires); // verbose one