#pragma once
#include "skoarcery.hpp"

#include "skoarpuscle_fwd.hpp"
#include "lex.hpp"
#include "minstrel_fwd.hpp"
#include "event_fwd.hpp"
#include "spells.hpp"
#include "styles.hpp"

// ==========================
// The Parse Tree - SkoarNoad
// ==========================
class SkoarNoad {
public:

	list<int>  address;         // a list code to find the noad quickly
    SkoarNoadPtr parent;          // the parent noad

	list<SkoarNoadPtr> children;  // a list of child noads

	const wstring name;               // name of the nonterminal
	const ESkoarNoad::Kind kind;
    const SkoarStyles::EStyle style;

	Skoarpuscle *skoarpuscle;   // skoarpuscle types go here, just one.

	SkoarTokePtr toke;
	wstring *skoarce; 

	size_t offs;
	size_t size;

	SpellOfMinstrels on_enter;
	
	wstring *voice;           // what voice to use
	void *skoap;              // what skoap are we in

	//SkoarNoad(wstring &nameArg, const ESkoarNoad::Kind kindArg, SkoarNoadPtr parentArg);
    
    //SkoarNoad() :
    //    parent(nullptr),
    //    name(L""),
    //    skoarce(nullptr),
    //    kind(ESkoarNoad::unknown),
    //    style(SkoarStyles::EStyle::nostyle);

    SkoarNoad(wstring &nameArg, SkoarNoadPtr parentArg, const ESkoarNoad::Kind kindArg, const SkoarStyles::EStyle styleArg);
    ~SkoarNoad();

    // can't figure out how to do this as a constructor..
    template<const ESkoarNoad::Kind kindArg>
    static SkoarNoadPtr New(wstring &nameArg, SkoarNoadPtr parentArg)
    {
        return std::make_shared<SkoarNoad>(nameArg, parentArg, kindArg, SkoarStyles::style<kindArg>());
    }

    static SkoarNoadPtr New(wstring &nameArg, SkoarNoadPtr parentArg, SkoarTokePtr toke);

	wstring *asString();

	// -------------------
	// decorating the tree
	// -------------------
	void decorate_zero(wstring *v, void *s, list<int> &parent_address, int i);
	void decorate(wstring *v, void *s, list<int> &parent_address, int i);

	// ----------------
	// growing the tree
	// ----------------
	void add_noad(SkoarNoadPtr noad);
	void add_toke(wstring name, SkoarToke *t);

	// ----------------
	// showing the tree
	// ----------------
	void log_tree(ISkoarLog *log, int tab = 1);
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
    void inorderBeforeAfter(SpellOfNoads f, SpellOfNoads g);

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

    friend std::wostream & operator<<(wostream &out, SkoarNoad &noad) {
        out << L"SkoarNoad: offs: " << noad.offs 
            << L", size: " << noad.size 
            << L", " << noad.name;
        return out;
    }
};




