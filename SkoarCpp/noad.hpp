#pragma once
#include "skoarcery.hpp"

#include "skoarpuscle_fwd.hpp"
#include "lex_fwd.hpp"
#include "minstrel_fwd.hpp"
#include "event_fwd.hpp"
#include "spells.hpp"

// ==========================
// The Parse Tree - SkoarNoad
// ==========================
class SkoarNoad {
public:

	list<int>  address;         // a list code to find the noad quickly
	SkoarNoad *parent;          // the parent noad
	list<SkoarNoad*> children;  // a list of child noads

	wstring name;                // name of the nonterminal
	Skoarpuscle *skoarpuscle;   // skoarpuscle types go here, just one.
	SkoarToke *toke;
	wstring skoarce; 
	size_t skoarce_offs;
	size_t skoarce_len;


	SpellOfMinstrels on_enter;
	
	wstring *voice;           // what voice to use
	void *skoap;             // what skoap are we in

	SkoarNoad(wstring &nameArg, SkoarNoad *parentArg);

	wstring *asString();

	// -------------------
	// decorating the tree
	// -------------------
	void decorate_zero(wstring *v, void *s, list<int> &parent_address, int i);
	void decorate(wstring *v, void *s, list<int> &parent_address, int i);

	// ----------------
	// growing the tree
	// ----------------
	void add_noad(SkoarNoad *noad);
	void add_toke(wstring name, SkoarToke *t);

	// ----------------
	// showing the tree
	// ----------------
	wstring draw_tree(int tab = 1);
	void scry(SpellOfScrying f);
	
	// -----------------
	// climbing the Tree
	// -----------------
	// depth-first, find the leaves, run handler, working towards trunk
	//
	// if it's crashing during the decorating stage, here's a good place to
	// start debugging
	void depth_visit(SpellOfNoads f);
	
	void inorder(SpellOfNoads f);

	// debug here if it's crashing while performing the skoar
	void inorder_from_here(list<int> &here, SpellOfNoads f);
	
	// expect skoarpuscle
	Skoarpuscle *next_skoarpuscle();
	SkoarToke *next_toke();

	// -------------------
	// performing the tree
	// -------------------
	void enter_noad(SkoarMinstrel* minstrel);

	// ------------------
	// searching the tree
	// ------------------

	// desires - array of names of noads as symbol, or SkoarToke implementation classes
	// writer - a function that will do something with the matches
	/*match{
	| desires, writer |


	collect{
	| desires |

		

	collect_skoarpuscles{
	| j = 0 |

	*/
};



