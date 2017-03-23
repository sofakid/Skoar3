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
}

SkoarpuscleSkoarpion::SkoarpuscleSkoarpion(SkoarpionPtr s) :
    val(s),
    args(nullptr)
{
}

SkoarpuscleSkoarpion::SkoarpuscleSkoarpion(SkoarpionPtr s, SkoarNoadPtr) :
    val(s),
    args(nullptr)
{
}

SkoarpuscleSkoarpion::SkoarpuscleSkoarpion(SkoarpusclePtr s, SkoarpusclePtr args) :
    val(skoarpuscle_ptr<SkoarpuscleSkoarpion>(s)->val),
    args(args)
{
}
void SkoarpuscleSkoarpion::on_enter(SkoarMinstrelPtr m) {
    on_enter_method(m);
}

void SkoarpuscleSkoarpion::run(SkoarMinstrelPtr m) {
    
}


SkoarpusclePtr SkoarpuscleSkoarpion::skoar_msg(SkoarpuscleMsg *msg, SkoarMinstrelPtr minstrel) {
    //args = msg->get_msg_arr(minstrel);
    return nullptr;
}

void SkoarpuscleSkoarpion::on_enter_method(SkoarMinstrelPtr m) {
    
    auto name = val->name;
    if (name.size() > 0) {
        m->koar->put(name, make_shared<SkoarpuscleSkoarpion>(this));
    }

    m->koar->do_skoarpion(val, m, SkoarKoar::EExecStyle::NORMAL, args);
}

// --- SkoarpuscleSkoarpionSig ----------------------------------------------
SkoarpuscleSkoarpionSig::SkoarpuscleSkoarpionSig(SkoarNoadPtr noad) {
    auto kidderator = noad->children.cbegin();
    auto x = (*kidderator)->skoarpuscle;

    if (is_skoarpuscle<SkoarpuscleSymbolName>(x)) {
        name = skoarpuscle_ptr<SkoarpuscleSymbolName>(x)->val;
        x = (*(++kidderator))->skoarpuscle;
    }

    if (is_skoarpuscle<SkoarpuscleArgList>(x)) {
        arg_list = x;
    }
}


// --- SkoarpuscleArgExpr ----------------------------------------------
/* arg_expr tree looks like:

    arg_expr
       Toke_SymbolName
or 
    arg_expr
       Toke_SymbolColon
       expr
*/
SkoarpuscleArgExpr::SkoarpuscleArgExpr(SkoarNoadPtr noad) {
    auto x = noad->next_skoarpuscle();

    if (is_skoarpuscle<SkoarpuscleSymbolName>(x)) {
        name = skoarpuscle_ptr<SkoarpuscleSymbolName>(x)->val;
    } 
    else if (is_skoarpuscle<SkoarpuscleSymbolColon>(x)) {
        name = skoarpuscle_ptr<SkoarpuscleSymbolColon>(x)->val;
    }
    
    if (noad->children.size() > 1) {
        auto kidderator = noad->children.begin();
        expr = make_shared<SkoarpuscleExpr>(*(++kidderator));
    }
    else
        expr = nullptr;
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
    
    auto skoarpuscles = noad->collect_skoarpuscles();
    for (auto x : *skoarpuscles) {
        if (is_skoarpuscle<SkoarpuscleArgExpr>(x)) {
            auto p = skoarpuscle_ptr<SkoarpuscleArgExpr>(x);
            args_dict[p->name] = p->expr;
            args_names.push_back(p->name);
        }
    }
}

void SkoarpuscleArgList::on_enter(SkoarMinstrelPtr m) {
    m->fairy->push_noating();
    m->fairy->push();
}


// --- SkoarpuscleProjection ----------------------------------------------
SkoarpuscleProjection::SkoarpuscleProjection(SkoarpionProjectionPtr) {

}

// --- SkoarpuscleProjections ----------------------------------------------
SkoarpuscleProjections::SkoarpuscleProjections(ListOfSkoarpionProjectionsPtr) {

}