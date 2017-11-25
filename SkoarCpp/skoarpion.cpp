#include "skoarpion.hpp"
#include "skoar.hpp"
#include "noad.hpp"
#include "skoarpuscle.hpp"
#include "skoar.hpp"
#include "all_skoarpuscles.hpp"
#include "koar.hpp"

// --- Skoarpion ------------------------------------------------
SkoarpionPtr Skoarpion::NewFromSkoar (Skoar* skoar) {
    auto skoarpion (make_shared<Skoarpion> (L"from skoar"));
    skoarpion->init_from_skoar (skoar);
    skoar->skoarpions.push_back (skoarpion);
    return skoarpion;
}

SkoarpionPtr Skoarpion::NewFromSkoarNoad (Skoar* skoar, SkoarNoadPtr noad) {
    auto skoarpion (make_shared<Skoarpion> (L"from noad"));
    skoarpion->init_from_noad (skoar, noad);
    skoar->skoarpions.push_back (skoarpion);
    return skoarpion;
}

SkoarpionPtr Skoarpion::NewFromSubtree (Skoar* skoar, SkoarNoadPtr subtree) {
    auto skoarpion (make_shared<Skoarpion> (L"from subtree"));
    skoarpion->init_from_subtree (skoar, subtree);
    skoar->skoarpions.push_back (skoarpion);
    return skoarpion;
}

Skoarpion::Skoarpion (const SkoarString from) :
    skoar (nullptr),
    body (nullptr),
    arg_list (nullptr),
    n (0),
    name (L"uninitialized"),
    made_from (from)
{
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().allocSkoarpion (made_from);
#endif
}

Skoarpion::Skoarpion (const Skoarpion *other) :
    skoar (other->skoar),
    body (other->body),
    n (other->n),
    name (other->name),
    arg_list (other->arg_list),
    made_from (other->made_from)
{
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().allocSkoarpion (made_from);
#endif
}

Skoarpion::~Skoarpion () {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().deallocSkoarpion (made_from);
#endif
    clear ();
}

void Skoarpion::clear () {
    if (arg_list != nullptr)
        arg_list->clear ();
    arg_list = nullptr;

    if (body != nullptr)
    {
        body->clear ();
        body = nullptr;
    }
    n = 0;
    
    skoar = nullptr;
}

void Skoarpion::init_from_skoar (Skoar* skr) {
    name = L"skoar";
    skoar = skr;

    body = SkoarNoad::NewArtificial (L"section");
    body->voice = skr->all_voice;

    for (auto line : skoar->tree->children)
    {
        auto v (line->next_skoarpuscle ());

        if (line->children.size () > 0)
            body->add_noad (line);
    }

    body->decorate_voices (skoar->all_voice);
    body->decorate_address_zero (body);

    n = body->size;
}


void Skoarpion::init_from_subtree (Skoar* skr, SkoarNoadPtr subtree) {
    name = L"=^.^=";
    skoar = skr;
    body = subtree;
    body->decorate_voices (skoar->all_voice);
    body->decorate_address_zero (body);
    n = subtree->size;
}


/*
== I ::  novoice :              skoarpion
== I ::  novoice :                opt_args           - 0
== I ::  novoice :                  Toke_SkoarpionArgs -- 0
== I ::  novoice :                  args_entries       -- 1
== I ::  novoice :                    Toke_SymbolName      --- 0
== I ::  novoice :                    Toke_ListSep         --- 1
== I ::  novoice :                    args_entries         --- 2
== I ::  novoice :                      Toke_SymbolColon        ---- 0
== I ::  novoice :                      expr                    ---- 1
== I ::  novoice :                        msgable
== I ::  novoice :                          nouny
== I ::  novoice :                            Toke_Int
== I ::  novoice :                        expr_prime
== I ::  novoice :                      Toke_ListSep            ---- 2
== I ::  novoice :                      args_entries            ---- 3
== I ::  novoice :                        Toke_SymbolName

== I ::  novoice :                Toke_SkoarpionStart - 1

== I ::  novoice :                skrp_suffix         - 2
== I ::  novoice :                  opt_voiced_phrases
== I ::  novoice :                    beat
== I ::  novoice :                      regular_beat
== I ::  novoice :                        Toke_Quarters

== I ::  novoice :                  Toke_SkoarpionEnd

*/

void Skoarpion::init_from_noad (Skoar* skr, SkoarNoadPtr noad) {

    skoar = skr;

    auto kidderatoar (noad->children.cbegin ());

    // With args:
    // kid 0 - opt_args
    // kid 1 - SkoarpionStart
    // kid 2 - suffix

    // without args:
    // kid 0 - SkoarpionStart
    // kid 1 - suffix
    auto first (*kidderatoar);

    if (first->kind == ESkoarNoad::opt_args)
    {
        arg_list = first->skoarpuscle;
        ++kidderatoar;
    }

    auto suffix (*(++kidderatoar));
    
    auto line (SkoarNoad::NewArtificial (L"line"));
    body = SkoarNoad::NewArtificial (L"section");
    

    for (auto x : suffix->children)
    {
        auto process_line ([&]() {
            if (line->children.size () > 0)
                body->add_noad (line);
        });

        auto toke (x->toke.get ());
        if (is_toke<ESkoarToke::Newline> (toke))
        {
            process_line ();
            line = SkoarNoad::NewArtificial (L"line");
        }
        else if (is_toke<ESkoarToke::SkoarpionEnd> (toke))
        {
            process_line ();
        }
        else
            line->add_noad (x);
    }
    suffix->children.clear ();

    body->decorate_address_zero (body);

    n = body->size;
    body->decorate_voices (skoar->all_voice);

}

// this is static, need a shared_ptr to the skoarpion.
SkoarpionProjectionPtr Skoarpion::projection (SkoarpionPtr skoarpion, SkoarString koar_name) {
    return make_shared<SkoarpionProjection> (skoarpion, koar_name);
}

ListOfSkoarpionProjectionsPtr Skoarpion::get_projections (
    SkoarpionPtr skoarpion, 
    const ListOfSkoarStrings& voices
) {
    auto listy (make_shared<ListOfSkoarpionProjections> ());

    for (auto x : voices)
    {
        auto projection (Skoarpion::projection (skoarpion, x));
        listy->push_back (projection);
    }

    return listy;
}

void Skoarpion::draw_tree (wostringstream &out) {
    out << "--< Skoarpion " << name << " >---\n";

    if (is_skoarpuscle<SkoarpuscleArgList> (arg_list))
    {
        out << "arg_list: ";
        arg_list->asString (out);
        out << "\n";

        auto listy (skoarpuscle_ptr<SkoarpuscleArgList> (arg_list)->args_names);

        for (auto x : listy)
            out << x << " ";

        out << "\n";
    }

    if (body != nullptr)
        body->draw_tree (out);
}

// --- SkoarpionProjection ------------------------------------------------
SkoarpionProjection::SkoarpionProjection (SkoarpionPtr skoarpion, SkoarString koar_name) :
    name (skoarpion->name + SkoarString (L":") + koar_name),
    voice_name (koar_name)
{
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().allocProjection (name);
#endif

    if (skoarpion->body == nullptr)
        return;

    SkoarNoad::inorder (skoarpion->body, [&](SkoarNoadPtr x) {
        const SkoarString& s (x->voice->name);
        const SkoarString all (L"all");

        if ((x->on_enter != nullptr || x->skoarpuscle != nullptr) && 
            (s == koar_name || s == all))
            noadites.emplace_back (x);
    });

}

SkoarpionProjection::~SkoarpionProjection ()
{
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().deallocProjection (name);
#endif
}


void SkoarpionProjection::draw (wostringstream &out) {
    out << "--< Projection " << name << " >---\n";

    for (auto& x : noadites)
    {
        out << L"   " << x.voice->name << L": " << x.name << L"\n";
    }
    
}
