#pragma once
#include "catch.hpp"
#include "skoarcery.hpp"
#include "skoar_public.hpp"
#include "all_skoarpuscles.hpp"
#include "memories.hpp"

std::string SkoarString_to_s(SkoarString ws);

bool check_skoarpuscle_int(SkoarpusclePtr p, SkoarInt v);
bool check_skoarpuscle_float(SkoarpusclePtr p, SkoarFloat v);
bool check_skoarpuscle_freq(SkoarpusclePtr p, SkoarFloat v);
bool check_skoarpuscle_num(SkoarpusclePtr p, SkoarInt v);
bool check_skoarpuscle_num(SkoarpusclePtr p, SkoarFloat v);

bool check_skoarpuscle_string(SkoarpusclePtr p, SkoarString v);
bool check_skoarpuscle_symbol(SkoarpusclePtr p, SkoarString v);

typedef std::shared_ptr<std::vector<SkoarEventPtr>> EventsPtr;


VectorOfSkoarEventsPtr skoar_get_events (Skoar* skoar);
VectorOfSkoarEventsPtr skoar_get_events_inf (Skoar * skoar, size_t num);
VectorOfSkoarEventsPtr skoar_get_events_for_voice (Skoar* skoar, SkoarString voice);
VectorOfSkoarEventsPtr skoar_get_events_for_voice_skoarpion (Skoar* skoar, SkoarString voice, SkoarpionPtr skoarpion);
VectorOfSkoarEventsPtr skoar_get_events_for_voice_skoarpion_chance_of_cthulhu (Skoar* skoar, SkoarString voice, SkoarpionPtr skoarpion);


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
    SkoarEventPtr e = std::make_shared<SkoarEvent>();
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
    SkoarEventPtr e_new = std::make_shared<SkoarEvent>();
    make_events_vec_r(vec, e_new, args...);
}

void make_events_vec_r(VectorOfSkoarEventsPtr, SkoarEventPtr);

template<typename... Args>
VectorOfSkoarEventsPtr make_events_vec(const Args&... args) {
    VectorOfSkoarEventsPtr vec = std::make_shared<VectorOfSkoarEvents>();
    SkoarEventPtr e = std::make_shared<SkoarEvent>();
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
    auto listy = std::make_shared<ListOfSkoarpuscles>();
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

// run skoar and expect exact sequence of events
void run_and_expect(SkoarString skoarce, VectorOfSkoarEventsPtr desires); 

// expect an infinite stream of events, just read for the first expected ones, then kill minstrel.
void run_and_expect_inf (SkoarString skoarce, VectorOfSkoarEventsPtr desires);
void run_and_expect_d(SkoarString skoarce, VectorOfSkoarEventsPtr desires); // verbose one

void print_skoarce (SkoarString skoarce);

void compile_skoar_test (SkoarString skoarce);
void run_skoar_test (SkoarString skoarce);
void run_skoar_multi_test (SkoarString skoarce, std::string filename);

#if SKOAR_DEBUG_MEMORY

void reset_memories ();
void require_no_memory_consumed ();
void require_fresh_memory_tables ();

#endif