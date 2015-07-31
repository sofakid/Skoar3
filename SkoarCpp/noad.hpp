#pragma once
#include "skoarcery.hpp"

class Skoarpuscle;
class SkoarToke;
class SkoarMinstrel;
class SkoarDict;

// ==========================
// The Parse Tree - SkoarNoad
// ==========================
class SkoarNoad {
public:

	list<int>  address;         // a list code to find the noad quickly
	SkoarNoad *parent;          // the parent noad
	list<SkoarNoad*> children;  // a list of child noads

	string name;            // name of the nonterminal (a \symbol)
	Skoarpuscle *skoarpuscle;     // skoarpuscle types go here, just one.
	SkoarToke *toke;

	function<void(SkoarMinstrel *minstrel)> on_enter;
	
	string *voice;           // what voice to use
	void *skoap;           // what skoap are we in

	SkoarNoad(string &nameArg, SkoarNoad *parentArg);

	string asString();

	// -------------------
	// decorating the tree
	// -------------------
	void decorate_zero(string *v, void *s, list<int> &parent_address, int i);

	void decorate(string *v, void *s, list<int> &parent_address, int i);

	// ----------------
	// growing the tree
	// ----------------
	void add_noad(SkoarNoad *noad);

	void add_toke(string name, SkoarToke *t);

	// ----------------
	// showing the tree
	// ----------------
	string draw_tree(int tab = 1);

	
	// -----------------
	// climbing the Tree
	// -----------------

	// depth-first, find the leaves, run handler, working towards trunk
	//
	// if it's crashing during the decorating stage, here's a good place to
	// start debugging
	void depth_visit(function<void(SkoarNoad *noad)> f);
	
	void inorder(function<void(SkoarNoad *noad)> f);

	// debug here if it's crashing while performing the skoar
	void inorder_from_here(list<int> here, function<void(SkoarNoad *noad)> f); 
	
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



