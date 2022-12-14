#pragma once
#include "skoarcery.hpp"

#include "skoarpuscle_fwd.hpp"
#include "lex.hpp"
#include "minstrel_fwd.hpp"
#include "event_fwd.hpp"
#include "spells.hpp"
#include "styles.hpp"


class SkoarNoadAddress : public std::vector<SkoarInt> {
public:

    SkoarString code() {
        std::wostringstream kode;
        for (auto x : *this) {
            kode << L"." << x;
        }
        return kode.str();
    }
};


// ==========================
// The Parse Tree - SkoarNoad
// ==========================
class SkoarNoad {
public:

    SkoarNoadAddress address;     // a list code to find the noad quickly
    SkoarNoadPtr parent;          // the parent noad

    std::vector<SkoarNoadPtr> children;  // a list of child noads

    const SkoarString name;       // name of the nonterminal
    const ESkoarNoad::Kind kind;
    SkoarStyles::EStyle style;

    SkoarpusclePtr skoarpuscle;   // skoarpuscle types go here, just one.

    SkoarTokePtr toke;

    size_t offs;
    size_t size;

    bool breakpoint;

    SpellOfMinstrels on_enter;
    
    SkoarKoarPtr voice;       // what voice to use
    SkoarNoadPtr skoap;       // what skoap are we in

    //SkoarNoad(SkoarString &nameArg, const ESkoarNoad::Kind kindArg, SkoarNoadPtr parentArg);
    
    //SkoarNoad() :
    //    parent(nullptr),
    //    name(L""),
    //    skoarce(nullptr),
    //    kind(ESkoarNoad::unknown),
    //    style(SkoarStyles::EStyle::nostyle);

    SkoarNoad(const wchar_t *nameArg, SkoarNoadPtr parentArg, const ESkoarNoad::Kind kindArg, SkoarStyles::EStyle styleArg);
    ~SkoarNoad();

    // can't figure out how to do this as a constructor..
    template<const ESkoarNoad::Kind kindArg>
    static SkoarNoadPtr New(const wchar_t *nameArg, SkoarNoadPtr parentArg)
    {
        return std::make_shared<SkoarNoad>(nameArg, parentArg, kindArg, SkoarStyles::Noad::style<kindArg>());
    }

    static SkoarNoadPtr New(const wchar_t *nameArg, SkoarNoadPtr parentArg, SkoarTokePtr toke);
    static SkoarNoadPtr NewArtificial(const wchar_t *nameArg, SkoarNoadPtr parentArg);
    static SkoarNoadPtr NewArtificial(const wchar_t *nameArg);
    static SkoarNoadPtr NewAlias(const wchar_t *nameArg);

    void clear();
    void clear_children();
    void clear_values();

    SkoarString asString();

    void decorate_voices (SkoarKoarPtr default_voice);

    // -------------------
    // decorating the tree
    // -------------------
    void decorate_address_zero (SkoarNoadPtr s);
    void decorate_address (SkoarNoadPtr s, SkoarNoadAddress &parent_address, SkoarInt i);

    // ----------------
    // growing the tree
    // ----------------
    void add_noad(SkoarNoadPtr noad);
    
    // ----------------
    // showing the tree
    // ----------------
    void log_tree(ISkoarLog *log, int tab = 1);
    void draw_tree(std::wostringstream &out, int tab = 1);
    
    // -----------------
    // climbing the Tree
    // -----------------

    // static versions for use with shared_ptrs
    static void depth_visit(SkoarNoadPtr p, SpellOfNoadPtrs f);
    static void inorder(SkoarNoadPtr p, SpellOfNoadPtrs f);
    static void inorderBeforeAfter(SkoarNoadPtr p, SpellOfNoadPtrs f, SpellOfNoadPtrs g);


    void depth_visit(SpellOfNoads f);
    void inorder(SpellOfNoads f);
    void inorderBeforeAfter(SpellOfNoads f, SpellOfNoads g);

    // debug here if it's crashing while performing the skoar
    void inorder_from_here(SkoarNoadAddress &here, SpellOfNoads f);
    
    // expect skoarpuscle
    SkoarpusclePtr next_skoarpuscle();
    SkoarToke* next_toke();

    SkoarNoadPtr getNoadAtOffs (size_t at_offs);

    // -------------------
    // performing the tree
    // -------------------
    void evaluate(SkoarMinstrelPtr minstrel);

    // ------------------
    // searching the tree
    // ------------------

    static ListOfSkoarNoadPtrs collect(SkoarNoadPtr, std::vector<ESkoarNoad::Kind>&);
    static ListOfSkoarNoadPtrs collect(SkoarNoadPtr, std::vector<ESkoarToke::Kind>&);
    static void match(SkoarNoadPtr, std::vector<ESkoarNoad::Kind>&, SpellOfNoadPtrs);
    static void match(SkoarNoadPtr, std::vector<ESkoarToke::Kind>&, SpellOfNoadPtrs);

    ListOfSkoarpuscles collect_skoarpuscles(int = 0);

    friend std::wostream & operator<<(std::wostream &out, SkoarNoad &noad) {
        out << L"SkoarNoad: offs: " << noad.offs 
            << L", size: " << noad.size 
            << L", " << noad.name;
        return out;
    }
};

class SkoarNoadite
{
public:
    const SkoarString name;       // name of the nonterminal
    const ESkoarNoad::Kind kind;
    const SkoarStyles::EStyle style;

    SkoarpusclePtr skoarpuscle;   // skoarpuscle types go here, just one.

    size_t offs;
    size_t size;

    bool breakpoint;

    SpellOfMinstrels on_enter;

    SkoarKoarPtr voice;       // what voice to use

    SkoarNoadite (SkoarNoadPtr);
    ~SkoarNoadite ();

    void enter_noad (SkoarMinstrelPtr minstrel);

};




