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

    enum EExecStyle {
        INLINE,
        NORMAL
    };

    Skoar              *skoar;
	SkoarDicPtr		   skoarboard;   //
	ListOfSkoarDics    stack;        // stack of vars visible to the skoar code
    ListOfSkoarDics    state_stack;  // stack of vars invisible to the skoar code
	SkoarString        name;         // name of voice

	SkoarKoar(Skoar *skoar, const SkoarString &nom);
    ~SkoarKoar();
	
    // ---------------------
	// State and scope stuff
	// ---------------------
	void put(SkoarString k, SkoarpusclePtr v);
	SkoarpusclePtr at(const SkoarString &k);

	void state_put(SkoarString &k, SkoarpusclePtr v);
	
	SkoarpusclePtr state_at(SkoarString &k);
	
	SkoarEventPtr event(SkoarMinstrelPtr minstrel);
	void set_args(SkoarMinstrelPtr minstrel, 
		SkoarpusclePtr args_spec, SkoarpusclePtr args);

	void push_state();
	void pop_state();
	void do_skoarpion(
		SkoarpionPtr skoarpion, 
		SkoarMinstrelPtr minstrel, 
        const EExecStyle,
		SkoarpusclePtr args_provided);

	void nav_loop(
		SkoarNoadPtr dst, 
		SkoarpionProjectionPtr projection, 
		SkoarMinstrelPtr minstrel,
		bool inlined);

	void bubble_up_nav(SkoarNav &nav, bool inlined);
};

