#pragma once
#include "skoarcery.hpp"

#include "noad_fwd.hpp"
#include "event_fwd.hpp"
#include "skoarpuscle_fwd.hpp"
#include "skoarpion_fwd.hpp"
#include "minstrel_fwd.hpp"

class SkoarNav {
public:
	enum ECode {
		DONE = 0,
		CODA,
		DA_CAPO,
		SEGNO,
		COLON,
		FINE
	} code;

	SkoarNav(ECode code);
};

class SkoarKoar {
public:
	SkoarDic		*skoarboard;   //
	list<SkoarDic*> *stack;        // stack of vars visible to the skoar code
	list<SkoarDic*> *state_stack;  // stack of vars invisible to the skoar code
	string          *name;         // name of voice as Symbol

	string *garbage;

	SkoarKoar(string *nom);
	// ---------------------
	// State and scope stuff
	// ---------------------
	void put(string *k, Skoarpuscle *v);
	Skoarpuscle *at(string*k);

	void state_put(string *k, Skoarpuscle *v);
	
	Skoarpuscle *state_at(string *k);
	inline Skoarpuscle *state_at(string k) {
		return state_at(&k);
	}
	SkoarEvent *event(SkoarMinstrel *minstrel);
	void set_args(SkoarMinstrel *minstrel, 
		SkoarpuscleArgsSpec *args_spec, list<Skoarpuscle *> *args);

	void push_state();
	void pop_state();
	void do_skoarpion(
		Skoarpion *skoarpion, 
		SkoarMinstrel *minstrel, 
		list<string*> &msg_arr, 
		list<Skoarpuscle *> *args);

	void nav_loop(
		SkoarNoad *dst, 
		SkoarProjection *projection, 
		SkoarMinstrel *minstrel,
		bool inlined);

	void bubble_up_nav(SkoarNav *nav, bool inlined);
};

