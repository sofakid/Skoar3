#include "noad.hpp"
#include "skoarpion.hpp"
#include "skoarpion_skoarpuscle.hpp"
#include "all_skoarpuscles.hpp"
#include "minstrel.hpp"
#include "fairy.hpp"


// --- SkoarpuscleSkoarpion ------------------------------------------------
SkoarpuscleSkoarpion::SkoarpuscleSkoarpion(const SkoarpuscleSkoarpion *that) :
    val(that->val),
    args(that->args)
{
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o().allocSkoarpuscle(L"Skoarpion");
#endif
}

SkoarpuscleSkoarpion::SkoarpuscleSkoarpion(SkoarpionPtr s) :
    val(s),
    args(nullptr)
{
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o().allocSkoarpuscle(L"Skoarpion");
#endif
}

SkoarpuscleSkoarpion::SkoarpuscleSkoarpion(SkoarpionPtr s, SkoarNoadPtr) :
    val(s),
    args(nullptr)
{
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o().allocSkoarpuscle(L"Skoarpion");
#endif
}

SkoarpuscleSkoarpion::SkoarpuscleSkoarpion(SkoarpusclePtr s, SkoarpusclePtr args) :
    val(skoarpuscle_ptr<SkoarpuscleSkoarpion>(s)->val),
    args(args)
{
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o().allocSkoarpuscle(L"Skoarpion");
#endif
}

SkoarpuscleSkoarpion::~SkoarpuscleSkoarpion(){
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o().deallocSkoarpuscle(L"Skoarpion");
#endif
    
    if (args != nullptr)
        args->clear ();

    args = nullptr;
    val = nullptr;
}

void SkoarpuscleSkoarpion::clear ()
{
    if (val != nullptr)
        val->clear ();

    if (args != nullptr)
        args->clear ();
}


void SkoarpuscleSkoarpion::on_enter(SkoarMinstrelPtr m) {
    auto skrpskrp (make_shared<SkoarpuscleSkoarpion>(this));
    m->fairy->impress (skrpskrp);
}

void SkoarpuscleSkoarpion::run(SkoarMinstrelPtr m) {
    auto impression = m->fairy->impression;
    //("SKRP_Skoarpion :: msg_arr :: " ++ msg_arr ++ " :: impression :: " ++  impression).postln;													
    m->koar->do_skoarpion(val, m, SkoarKoar::EExecStyle::NORMAL, impression);
}


SkoarpusclePtr SkoarpuscleSkoarpion::skoar_msg(SkoarpuscleMsg* /*msg*/, SkoarMinstrelPtr minstrel) {
    //args = msg->get_msg_arr(minstrel);
    return nullptr;
}

void SkoarpuscleSkoarpion::asString(wostream &out) { 
    out << "Skoarpion" << " :: " << val->name;
}

// --- SkoarpuscleArgExpr ----------------------------------------------
/* args_entries tree looks like:

    args_entries
       Toke_SymbolName
or 
    args_entries
       Toke_SymbolColon
       expr
*/
SkoarpuscleArgExpr::SkoarpuscleArgExpr(SkoarNoadPtr noad) {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o().allocSkoarpuscle(L"ArgExpr");
#endif
    auto x = noad->next_skoarpuscle();

    if (is_skoarpuscle<SkoarpuscleSymbolColon>(x)) {
        name = skoarpuscle_ptr<SkoarpuscleSymbolColon>(x)->val;
    }
    
    if (is_skoarpuscle<SkoarpuscleSymbolName> (x))
    {
        name = skoarpuscle_ptr<SkoarpuscleSymbolName> (x)->val;
    }

    if (noad->children.size() > 1) {
        auto kidderator = noad->children.begin();
        expr = make_shared<SkoarpuscleExpr>(*(++kidderator));
    }
    else
        expr = nullptr;
}

SkoarpuscleArgExpr::~SkoarpuscleArgExpr() {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o().deallocSkoarpuscle(L"ArgExpr");
#endif
    clear ();
}

void SkoarpuscleArgExpr::clear ()
{
    if (expr != nullptr)
    {
        expr->clear ();
        expr = nullptr;
    }
}

void SkoarpuscleArgExpr::asString(wostream &out) {
    out << "ArgExpr" << " :: " << name;
    if (is_skoarpuscle<SkoarpuscleExpr>(expr)) {
        out << " :: ";
        skoarpuscle_ptr<SkoarpuscleExpr>(expr)->asString(out);
    }
}

// --- SkoarpuscleArgList ----------------------------------------------
/*
    arg_listy
       Toke_ListS
       arg_expr
       Toke_ListSep
       arg_expr
*/
SkoarpuscleArgList::SkoarpuscleArgList(SkoarNoadPtr noad) {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o().allocSkoarpuscle(L"ArgList");
#endif
    
    auto skoarpuscles (noad->collect_skoarpuscles());
    for (auto x : *skoarpuscles) {
        if (is_skoarpuscle<SkoarpuscleArgExpr>(x)) {
            auto p = skoarpuscle_ptr<SkoarpuscleArgExpr>(x);
            args_dict.put(p->name, p->expr);
            args_names.push_back(p->name);
        }
    }
}

SkoarpuscleArgList::~SkoarpuscleArgList() {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o().deallocSkoarpuscle(L"ArgList");
#endif
    clear();
}

void SkoarpuscleArgList::clear ()
{
    args_dict.clear ();
    args_names.clear ();
}

void SkoarpuscleArgList::on_enter(SkoarMinstrelPtr m) {
    m->fairy->push_noating();
    m->fairy->push();
}

void SkoarpuscleArgList::asString(wostream &out) {
    out << "ArgList";
    for (auto x : args_names)
        out << " :: " << x ;
}



// --- SkoarpuscleProjections ----------------------------------------------
SkoarpuscleProjections::SkoarpuscleProjections (ListOfSkoarpionProjectionsPtr lospp) {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().allocSkoarpuscle (L"Projections");
#endif
    if (lospp != nullptr && lospp->size() > 0)
        for (auto x : *lospp)
            if (x != nullptr)
                // todo: there will be dups, what's up?
                map[x->name] = x;
}

SkoarpuscleProjections::~SkoarpuscleProjections () {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().deallocSkoarpuscle (L"Projections");
#endif
    clear ();
}

void SkoarpuscleProjections::clear ()
{
    map.clear ();
}

void SkoarpuscleProjections::asString (wostream &out) {
    out << "Projections";
}