#pragma once
#include "skoarcery.hpp"

#include "noad_fwd.hpp"
#include "event_fwd.hpp"
#include "skoarpuscle_fwd.hpp"
#include "skoarpion_fwd.hpp"
#include "minstrel_fwd.hpp"
#include "spells.hpp"

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
	SkoarDicPtr		   skoarboard;   //
	ListOfSkoarDicsPtr stack;        // stack of vars visible to the skoar code
    ListOfSkoarDicsPtr state_stack;  // stack of vars invisible to the skoar code
	SkoarString        name;         // name of voice

    SkoarString garbage;

	SkoarKoar(SkoarString &nom);
	// ---------------------
	// State and scope stuff
	// ---------------------
	void put(SkoarString k, SkoarpusclePtr v);
	SkoarpusclePtr at(SkoarString &k);

	void state_put(SkoarString &k, SkoarpusclePtr v);
	
	SkoarpusclePtr state_at(SkoarString &k);
	
	SkoarEvent *event(SkoarMinstrelPtr minstrel);
	void set_args(SkoarMinstrelPtr minstrel, 
		shared_ptr<SkoarpuscleArgSpec> args_spec, ListOfSkoarpusclesPtr args);

	void push_state();
	void pop_state();
	void do_skoarpion(
		SkoarpionPtr skoarpion, 
		SkoarMinstrelPtr minstrel, 
		list<SkoarString> &msg_arr, 
		ListOfSkoarpusclesPtr args);

	void nav_loop(
		SkoarNoadPtr dst, 
		SkoarProjection *projection, 
		SkoarMinstrelPtr minstrel,
		bool inlined);

	void bubble_up_nav(SkoarNav *nav, bool inlined);
};

