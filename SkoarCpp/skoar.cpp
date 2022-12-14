#include "skoar.hpp"
#include "exception.hpp"
#include "decorating.hpp"
#include "noad.hpp"
#include "toker.hpp"
#include "koar.hpp"
#include "rdpp.hpp"
#include "operators.hpp"
#include "skoarpion.hpp"
#include "spells.hpp"
#include "logging.hpp"
#include "styles.hpp"
#include "toke_inspector.hpp"
#include "minstrel.hpp"
#include <ctime>
#include "memories.hpp"

// =====
// Skoar
// =====
void Skoar::init () {
    static bool isInitialized (false);
    if (isInitialized == false)
    {
        SkoarToker::init ();
        SkoarParser::init ();
        SkoarTokeInspector::init ();
        Skoarmantics::init ();
        SkoarOps::init ();

        isInitialized = true;
    }

    // reset the counters
    SkoarpuscleLoop::id (true);
    SkoarpuscleConditional::id (true);
}

Skoar::Skoar (SkoarString src, ISkoarLog *log) :
    skoarce (src + L"\n"), // i don't like this + L"\n" business.
    log (log),
    parsedOk (false),
    decoratedOk (false),
    tree(nullptr),
    running(0)
{
    Skoar::init ();

#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().allocSkoar ();
#endif

    SkoarToker toker (skoarce);
    SkoarParser parser (&toker);

    all_voice = std::make_shared<SkoarKoar> (this, SkoarString (L"all"));
    voices[L"all"] = all_voice;

    log->d (">>> parsing skoar...");
    clock_t start_time (clock ());
    try
    {
        tree = parser.skoar (nullptr);
    }
    catch (SkoarTokerException &e)
    {
        // someday we can.. underline the error or something.
        log->e ("parse fail", e.wwhat ());

        // delete the unfinished tree
        auto x (e.noad);
        while (x->parent != nullptr)
        {
            auto parent (x->parent);
            x->clear ();
            x = parent;
        }
        // delete the broken tree
        x->clear ();
        x = nullptr;
        e.noad = nullptr;

        return;
    }
    catch (SkoarParseException &e)
    {
        // someday we can like, underline the error or something.
        log->e ("parse fail", e.wwhat ());

        // delete the unfinished tree
        auto x (e.noad);
        while (x->parent != nullptr)
        {
            auto parent (x->parent);
            x->clear ();
            x = parent;
        }
        // delete the broken tree
        x->clear ();
        x = nullptr;
        e.noad = nullptr;

        return;
    }
    parser.sortDesirables ();

    try
    {
        toker.eof ();
    }
    catch (SkoarError &e)
    {
        // someday we can like, underline the error or something.
        log->e ("parse fail", e.wwhat ());

        // delete the broken tree
        tree->clear ();
        tree = nullptr;
        return;
    }
    parsedOk = true;
    clock_t parse_time (clock () - start_time);

    if (log->getLevel () == ISkoarLog::debug)
    {
        log->d ("---< Undecorated Skoar Tree >---");
        tree->log_tree (log);
    }

    decorate_offs_size_style ();

    //log->i("<<< tree created, now decorating...");
    try
    {
        decorate ();
    }
    catch (SkoarDecoratingException &e)
    {
        log->e ("failed decorating", e.wwhat ());
        tree->clear ();
        return;
    }

    decoratedOk = true;

    if (log->getLevel () == ISkoarLog::debug)
    {
        clock_t decorate_time (clock () - start_time - parse_time);

        float f_parse_time (static_cast<float> (parse_time) / CLOCKS_PER_SEC);
        float f_decorate_time (static_cast<float> (decorate_time) / CLOCKS_PER_SEC);
        log->d ("---< Decorated Skoar Tree >---");
        tree->log_tree (log);

        draw_skoarpions ();
        log->d ("+++ Skoar Parsed +++",
            "seconds parsing", f_parse_time,
            "seconds decorating", f_decorate_time,
            "seconds total: ", f_parse_time + f_decorate_time);
    }
}

Skoar::~Skoar () {
    clear ();

#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().deallocSkoar ();
#endif
}

void Skoar::clear () {
    if (decoratedOk)
    {
        for (auto& skoarpion : skoarpions)
            skoarpion->clear ();

        skoarpions.clear ();

        for (auto& v_pair : voices)
        {
            auto voice (v_pair.second);
            if (voice != nullptr)
                voice->clear ();
        }

        voices.clear ();
        all_voice = nullptr;

        if (tree != nullptr)
            tree->clear ();
    }
    else if (parsedOk)
    {
        for (auto& skoarpion : skoarpions)
            skoarpion->clear ();

        skoarpions.clear ();

        for (auto& v_pair : voices)
        {
            auto voice (v_pair.second);
            if (voice != nullptr)
                voice->clear ();
        }

        voices.clear ();
        all_voice = nullptr;

        if (tree != nullptr)
            tree->clear ();
    }

    tree = nullptr;
}

void Skoar::decorate_offs_size_style () {
    SkoarStyles::EStyle current_style (SkoarStyles::EStyle::nostyle);
    std::vector<SkoarStyles::EStyle> style_stack { current_style };
    size_t pos (0);

    auto before ([&](SkoarNoadPtr noad) {
        style_stack.push_back (current_style);

        if (noad->style == SkoarStyles::EStyle::nostyle)
            noad->style = current_style;
        else
            current_style = noad->style;

        auto toke = noad->toke.get ();
        if (toke != nullptr)
        {
            pos = toke->offs + toke->size;
            noad->offs = toke->offs;
        }
        else
            noad->offs = pos;
    });

    auto after ([&](SkoarNoadPtr noad) {
        current_style = style_stack.back ();
        style_stack.pop_back ();
        noad->size = pos - noad->offs;
    });

    SkoarNoad::inorderBeforeAfter (tree, before, after);
}

void Skoar::decorate () {
    auto f ([&](SkoarNoadPtr noad) {
        auto t (noad->toke.get ());
        if (t != nullptr)
            SkoarTokeInspector::instance ()->decorate (this, noad, t);
        else
            Skoarmantics::instance ()->decorate (this, noad);

        auto x (noad->skoarpuscle);
        if (x != nullptr)
        {
            if (is_skoarpuscle<SkoarpuscleBars> (x))
                registerMarker (skoarpuscle_ptr<SkoarpuscleBars> (x));

            else if (is_skoarpuscle<SkoarpuscleCoda> (x))
                registerMarker (skoarpuscle_ptr<SkoarpuscleCoda> (x));

        }
    });

    SkoarNoad::depth_visit (tree, f);
}


// -------
// markers
// -------
void Skoar::registerMarker (SkoarpuscleBars* bar) {
    if (bar->post_repeat)
        markers_colon.push_back (bar->offs);
}

void Skoar::registerMarker (SkoarpuscleCoda* coda) {
    markers_coda.push_back (coda->offs);
    if (coda->label != L"")
        markers_coda_named[coda->label] = coda->offs;
}

// ----
// misc
// ----

// creates a new one if needed
SkoarKoarPtr Skoar::get_voice (const SkoarString &k) {
    SkoarKoarPtr voice (voices[k]);
    if (voice != nullptr)
        return voice;

    voice = std::make_shared<SkoarKoar> (this, k);
    voices[k] = voice;

    return voice;
}

void Skoar::cthulhu (SkoarNoadPtr noad) {
    // TODO more
    //"^^(;,;)^^".postln;
    //dump();
    throw SkoarRuntimeException (L"^^(;,;)^^");

}


void Skoar::cthulhu (SkoarString s) {
    throw SkoarRuntimeException (s);
}

void Skoar::draw_skoarpions () {

    if (log->getLevel () != ISkoarLog::debug)
        return;

    std::wostringstream stream;

    for (auto x : skoarpions)
    {
        stream << "\n";
        x->draw_tree (stream);

        stream << "\nProjections:\n";
        for (auto pairs : voices)
        {
            auto koar_name (pairs.first);
            auto projection (Skoarpion::projection (x, koar_name));

            projection->draw (stream);
            stream << "\n";
        }
    }

    log->i ("draw_skoarpions\n", stream.str ());
}

ListOfSkoarpionProjectionsPtr Skoar::get_all_projections () {
    auto listy (std::make_shared<ListOfSkoarpionProjections> ());

    for (auto x : skoarpions)
        for (auto pairs : voices)
        {
            auto koar_name (pairs.first);
            auto projection (Skoarpion::projection (x, koar_name));
            listy->push_back (projection);
        }

    return listy;
}

ListOfSkoarpionProjectionsPtr Skoar::get_projections (SkoarString koar_name) {
    auto listy (std::make_shared<ListOfSkoarpionProjections> ());

    for (auto x : skoarpions)
    {
        auto projection (Skoarpion::projection (x, koar_name));
        listy->push_back (projection);
    }

    return listy;
}

ListOfSkoarStrings Skoar::get_all_voices () {
    ListOfSkoarStrings out;
    for (auto kv : voices)
        out.push_back (kv.first);
    return out;
}


void Skoar::play (const SpellOfHappening& spell) {
    Skoarchestra x (this, spell);
    for (auto m : x.minstrels)
        m->start ();
}

void Skoar::play_voice (SkoarString voice, const SpellOfHappening& spell) {
    Skoarchestra x (this, spell);
    for (auto m : x.minstrels)
        if (m->koar->name == voice)
            m->start ();
}

void Skoar::play_voice_skoarpion (SkoarString voice, SkoarpionPtr skoarpion, const SpellOfHappening& spell) {
    auto koar (get_voice (voice));
    auto m (SkoarMinstrel::NewForSkoarpion (L"testing", koar, this, skoarpion, spell));
    m->start ();
    //m->clear ();
}

void Skoar::debug_voice (SkoarString voice, const SpellOfHappening& spell, const MinstrelDebugConfig &config) {
    auto v (voices[voice]);
    auto m (SkoarMinstrel::NewDebugging (voice, v, this, spell, config));
    one_more_running ();
    m->start ();
    one_less_running ();
}

void Skoar::one_more_running () {
    // todo: lock a mutex
    ++running;
    // todo: unlock the mutex
}

void Skoar::one_less_running () {
    // todo: lock a mutex
    --running;
    // todo: unlock the mutex

    if (running == 0)
    {
        //clear ();
    }
}

// --------------------------------------------------------------------------------
// for highlighting

SkoarLite::SkoarLite (SkoarString s, ISkoarLog *log) :
    skoarce (s + L"\n"), // i don't like this + L"\n" business.
    log (log),
    parsedOk (false)
{
    Skoar::init ();
    SkoarToker toker (skoarce);
    SkoarParser parser (&toker);

    try
    {
        tree = parser.skoar (nullptr);
        parser.sortDesirables ();

    }
    catch (SkoarTokerException &e)
    {
        // someday we can underline the error or something.
        log->d ("toker fail", e.wwhat ());

        // delete the unfinished tree
        auto x (e.noad);
        while (x->parent != nullptr)
        {
            auto parent (x->parent);
            x->clear ();
            x = parent;
        }
        x->clear ();
        x = nullptr;
        e.noad = nullptr;
        return;
    }
    catch (SkoarParseException &e)
    {
        // someday we can underline the error or something.
        log->d ("parse fail", e.wwhat ());

        // delete the unfinished tree
        auto x (e.noad);
        while (x->parent != nullptr)
        {
            auto parent (x->parent);
            x->clear ();
            x = parent;
        }
        // delete the broken tree
        x->clear ();
        x = nullptr;
        e.noad = nullptr;
        return;
    }

    try
    {
        toker.eof ();
        parsedOk = true;
    }
    catch (SkoarError &e)
    {
        // someday we can underline the error or something.
        log->d ("parse fail", e.wwhat ());

        // delete the broken tree
        tree->clear ();
        tree = nullptr;
    }

    if (parsedOk)
        decorate_offs_size_style ();

    //log->e("False style", SkoarStyles::style<ESkoarToke::False>());
}

void SkoarLite::decorate_offs_size_style() 
{
    SkoarStyles::EStyle current_style (SkoarStyles::EStyle::nostyle);
    std::vector<SkoarStyles::EStyle> style_stack { current_style };
    size_t pos (0);

    auto before ([&](SkoarNoadPtr noad) {
        style_stack.push_back (current_style);

        if (noad->style == SkoarStyles::EStyle::nostyle)
            noad->style = current_style;
        else
            current_style = noad->style;

        auto toke (noad->toke.get ());

        if (toke != nullptr)
        {
            pos = toke->offs + toke->size;
            noad->offs = toke->offs;
        }
        else
            noad->offs = pos;

    });

    auto after ([&](SkoarNoadPtr noad) {
        current_style = style_stack.back ();
        style_stack.pop_back ();
        noad->size = pos - noad->offs;
    });

    SkoarNoad::inorderBeforeAfter (tree, before, after);
}


SkoarLite::~SkoarLite () {
    if (parsedOk)
        tree->clear ();
    tree = nullptr;
}
