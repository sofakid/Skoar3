#include "skoarcery.hpp"
#include "koar.hpp"
#include "skoar.hpp"
#include "event.hpp"
#include "minstrel.hpp"
#include "skoarpion.hpp"
#include "all_skoarpuscles.hpp"
#include "fairy.hpp" 
#include "noad.hpp"

SkoarKoar::SkoarKoar (Skoar *skoar, const SkoarString &name) :
    skoar (skoar),
    name (name),
    skoarboard (make_shared<SkoarDic> ())
{
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().allocKoar (name);
#endif
    skoarboard->put (L"voice", make_skoarpuscle (name));
    stack.push_back (skoarboard);
}

SkoarKoar::~SkoarKoar () {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().deallocKoar (name);
#endif
    clear ();
}

void SkoarKoar::clear () {
    if (skoarboard != nullptr)
    {
        skoarboard->clear ();
        skoarboard = nullptr;
    }
    stack.clear ();
    state_stack.clear ();
    skoar = nullptr;
}

// ---------------------
// State and scope stuff
// ---------------------
void SkoarKoar::put (SkoarString k, SkoarpusclePtr v) {
    stack.back ()->put (k, v);
}

SkoarpusclePtr SkoarKoar::at (const SkoarString &k) {

    SkoarpusclePtr out (nullptr);

    for (auto rev_it = stack.rbegin (); rev_it != stack.rend (); rev_it++)
    {
        out = (*rev_it)->at (k);
        if (out != nullptr)
            return out;
    }

    return out;
}


void SkoarKoar::state_put (const wchar_t* k, SkoarpusclePtr v) {
    SkoarString s (k);
    state_put (s, v);
}

void SkoarKoar::state_put (SkoarString &k, SkoarpusclePtr v) {
    state_stack.back ()->put (k, v);
}

SkoarpusclePtr SkoarKoar::state_at (const wchar_t* k) {
    SkoarString s (k);
    return state_at (s);
}

SkoarpusclePtr SkoarKoar::state_at (SkoarString &k) {
    SkoarpusclePtr out = nullptr;

    for (auto rev_it = state_stack.rbegin (); rev_it != state_stack.rend (); rev_it++)
    {
        out = (*rev_it)->at (k);
        if (out != nullptr)
            return out;
    }

    return out;
}

SkoarEventPtr SkoarKoar::event (SkoarMinstrelPtr minstrel) {
    auto e = make_shared<SkoarEvent> ();

    // going from global to local, overwriting existing entries with the more local one. 
    for (auto skrb : stack)
    {
        // native function constructs the event quickly
        e->from (skrb);

        /*// but we need to change stuff
        e.keysValuesChange{
            | key, value |

            case {value.isKindOf(SkoarpuscleSkoarpion)} {
                // we don't need to pass skoarpions to SC
                nil

            } {value.isKindOf(Skoarpuscle)} {
                    // we want values, not skoarpuscles
                    value.flatten(minstrel)

                } {
                    // perfect
                    value
                }
        };*/
    }

    return e;
}

// new plan:
// make list of provided named args (1)
// make list of provided unnamed args (2)
// make list of arg spec with named provided args removed (3)
// line up (2) and (3) for positional args. 

#include <iostream>
ListOfSkoarpusclesPtr make_list_of_provided_named_args (SkoarpuscleList* p) {
    auto provided_named_args = make_shared<ListOfSkoarpuscles> ();
    auto provided_unnamed_args = make_shared<ListOfSkoarpuscles> ();

    auto &listy = p->val;

    for (auto& li : *listy)
    {
        if (is_skoarpuscle<SkoarpusclePair> (li))
        {
            provided_named_args->push_back (li);
        }
        else
        {
            provided_unnamed_args->push_back (li);
        }

    }

    return provided_named_args;
}

ListOfSkoarpionsPtr make_list_of_provided_unnamed_args () {
    return nullptr;
}

ListOfSkoarpionsPtr make_args_spec_for_remaining_positional_args () {
    return nullptr;
}


void SkoarKoar::set_args (
    SkoarMinstrelPtr minstrel,
    SkoarpusclePtr args_spec,
    SkoarpusclePtr args_prov)
{
    auto vars (stack.back ());

    if (is_skoarpuscle<SkoarpuscleArgList> (args_spec) == false)
        return;

    SkoarpuscleArgList *args_list = skoarpuscle_ptr<SkoarpuscleArgList> (args_spec);

    ListOfSkoarpusclesPtr args_provided;
    /*if (is_skoarpuscle<SkoarpuscleArgs> (args_prov))
        args_provided = skoarpuscle_ptr<SkoarpuscleArgs> (args_prov)->val;
    else*/ 
        
    if (is_skoarpuscle<SkoarpuscleList> (args_prov))
    {
        args_provided = skoarpuscle_ptr<SkoarpuscleList> (args_prov)->val;
        //make_list_of_provided_named_args (skoarpuscle_ptr<SkoarpuscleList> (args_prov));
    }
    
    /*else if (is_skoarpuscle<SkoarpusclePair> (args_prov))
    {
        // this isn't right.
        args_provided = make_shared<ListOfSkoarpuscles> ();
        args_provided->push_back (skoarpuscle_ptr<SkoarpusclePair> (args_prov)->val.second);
    }*/
    else
    {
        args_provided = make_shared<ListOfSkoarpuscles> ();
        //if (args_prov != nullptr)
        //    args_provided->push_back (args_prov);

        //const auto n (args_list->args_names.size ());
        //for (int i = 0; i < n; ++i)
        //    args_provided->push_back (make_skoarpuscle (nullptr));
    }
    
   

    minstrel->fairy->push_noating ();
    // make list of provided named args (1)
    // make list of provided unnamed args (2)
    ListOfSkoarpuscles provided_named_args;
    ListOfSkoarpuscles provided_unnamed_args;

    for (auto& x : *args_provided)
        if (is_skoarpuscle<SkoarpusclePair> (x))
            provided_named_args.push_back (x);
        else
            provided_unnamed_args.push_back (x);

    std::list<SkoarString> list_args_spec_minus_names_provided;
    // make list of arg spec with named provided args removed (3)
    for (auto& arg_name : args_list->args_names)
    {
        bool include_this = true;

        for (auto& x : provided_named_args)
            if (arg_name == skoarpuscle_ptr<SkoarpusclePair> (x)->val.first)
            {
                include_this = false;
                break;
            }

        if (include_this)
            list_args_spec_minus_names_provided.push_back (arg_name);
    }

    // set defaults
    //
    // - todo 
    auto src (args_list->args_dict);
    for (auto pair : src)
    {
        auto arg_name (pair.first);
        auto &sp = pair.second;
        
        SkoarpusclePtr y;
        if (is_skoarpuscle<SkoarpuscleArgExpr>(sp))
            y = skoarpuscle_ptr<SkoarpuscleArgExpr>(sp)->flatten (minstrel);
        else
            y = make_skoarpuscle (nullptr);

        vars->put (arg_name, y);
    }

    // set named args
    for (auto& named_arg : provided_named_args)
    {
        auto p (skoarpuscle_ptr<SkoarpusclePair> (named_arg));
        //p->assign (minstrel);
        vars->put (p->val.first, p->val.second);
    }

    // set positionals
    auto positional_iter (provided_unnamed_args.cbegin ());
    for (auto& arg_name : list_args_spec_minus_names_provided)
    {
        SkoarpusclePtr x;
        if (positional_iter == provided_unnamed_args.cend ())
            break;

        x = *(positional_iter++);
        vars->put (arg_name, x);
    }


    // old way:
    /*auto provided_iter (args_provided->cbegin ());
    for (auto arg_name : args_list->args_names)
    {
        SkoarpusclePtr x;
        if (provided_iter != args_provided->cend ())
            x = *(provided_iter++);
        else
            x = make_skoarpuscle (nullptr);

        if (is_skoarpuscle<SkoarpuscleCat> (x))
        {
            // not found, use default
            auto y (args_list->args_dict.at (arg_name));

            if (is_skoarpuscle<SkoarpuscleExpr> (y))
                y = skoarpuscle_ptr<SkoarpuscleExpr> (y)->flatten (minstrel);

            vars->put (arg_name, y);
        }
        else if (is_skoarpuscle<SkoarpusclePair> (x))
        {
            auto p (skoarpuscle_ptr<SkoarpusclePair> (x));
            vars->put (p->val.first, p->val.second);
        }
        else
            vars->put (arg_name, x);
    }*/

    minstrel->fairy->pop_noating ();
}

void SkoarKoar::push_state () {

    auto state (make_shared<SkoarDic> ());
    auto projections (make_shared<ListOfSkoarpionProjections> ());

    state_stack.push_back (state);

    state->put (L"colons_burned", make_shared<SkoarpuscleList> ());
    state->put (L"al_fine", make_skoarpuscle (false));
    state->put (L"projections", make_shared<SkoarpuscleProjections> (projections));

    stack.push_back (make_shared<SkoarDic> ());

}

void SkoarKoar::pop_state () {
    stack.pop_back ();
    state_stack.pop_back ();
}

void SkoarKoar::do_skoarpion (
    SkoarpionPtr skoarpion,
    SkoarMinstrelPtr minstrel,
    const EExecStyle exec_style,
    SkoarpusclePtr args_provided) {

    SkoarNoadPtr subtree;
    SkoarpionProjectionPtr projection = Skoarpion::projection (skoarpion, name);

    SkoarString msg_name;

    if (exec_style != EExecStyle::INLINE)
    {
        push_state ();
        minstrel->fairy->push_times_seen ();
    }

    // load arg values into their names
    set_args (minstrel, skoarpion->arg_list, args_provided);

    SpellOfDecency cleanup = [&]() {
        if (exec_style != EExecStyle::INLINE)
        {
            pop_state ();
            minstrel->fairy->pop_times_seen ();
        }

        minstrel->after_entering_skoarpion (minstrel, skoarpion);
    };

    minstrel->before_entering_skoarpion (minstrel, skoarpion);
    nav_loop (projection, minstrel, cleanup);


}

void SkoarKoar::nav_loop (
    SkoarpionProjectionPtr projection,
    SkoarMinstrelPtr minstrel,
    SpellOfDecency cleanup) {

    //auto subtree = dst;

    try
    {
        for (auto& x : projection->noadites)
            x.enter_noad (minstrel);
        // map dst to an address relative to the projection

        //auto here = projection->map_dst (dst);

        //subtree->inorder_from_here (
        //    here,
        //    [&](SkoarNoad* x) {
        //    x->enter_noad (minstrel);
        //}
        //);
        //throw SkoarNav (SkoarNav::DONE);
    }
    catch (SkoarNav &nav_result)
    {
        switch (nav_result.code)
        {

        case SkoarNav::DONE:
            bubble_up_nav (nav_result, cleanup);
            break;

        case SkoarNav::CODA:
        {
            // try to land fairy
            //auto dst_offs = minstrel->fairy->fly_to_dest;
            //dst = subtree->getNoadAtOffs (dst_offs);
            //if (dst == nullptr || dst->skoap != subtree->skoap)
                bubble_up_nav (nav_result, cleanup);

            break;
        }
        case SkoarNav::COLON:
            //dst = state_at(L"colon_seen");

            //if ((dst !? (_->skoap)) != subtree->skoap) {
            //   bubble_up_nav(nav_result, cleanup);
            //};
            break;

        }
    }
    cleanup ();
}

void SkoarKoar::bubble_up_nav (SkoarNav &nav, SpellOfDecency cleanup) {

    // the nav throw will abort do_skoarpion,
    // we have to clean up here.
    cleanup ();

    throw nav;

}

SkoarNav::SkoarNav (ECode c) {
    code = c;
}