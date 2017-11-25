#include "testing_util.hpp"

string SkoarString_to_s (SkoarString ws) {
    return string (ws.begin (), ws.end ());
}

bool check_skoarpuscle_int (SkoarpusclePtr p, SkoarInt v) {
    return check_skoarpuscle_val<SkoarpuscleInt, SkoarInt> (p, v);
}

bool check_skoarpuscle_float (SkoarpusclePtr p, SkoarFloat v) {

    auto x (is_skoarpuscle<SkoarpuscleFloat> (p));
    if (x == false)
        return false;

    auto ptr = skoarpuscle_ptr<SkoarpuscleFloat> (p);

    if (typeid(ptr->val) != typeid(SkoarFloat))
        return false;

    // don't compare float values with equality, check if it's close.
    auto epsilon ((v == 0.0 ? 1 : v) * 0.0001);
    if ((ptr->val < (v + epsilon)) && (ptr->val > (v - epsilon)))
        return true;

    return false;
}


bool check_skoarpuscle_freq (SkoarpusclePtr p, SkoarFloat v) {

    auto x (is_skoarpuscle<SkoarpuscleFreq> (p));
    if (x == false)
        return false;

    auto ptr (skoarpuscle_ptr<SkoarpuscleFreq> (p));

    if (typeid(ptr->val) != typeid(SkoarFloat))
        return false;

    // don't compare float values with equality, check if it's close.
    auto epsilon ((v == 0.0 ? 1 : v) * 0.0001);
    if ((ptr->val < (v + epsilon)) && (ptr->val > (v - epsilon)))
        return true;

    return false;
}

bool check_skoarpuscle_num (SkoarpusclePtr p, SkoarInt v) {
    if (is_skoarpuscle<SkoarpuscleInt> (p))
    {

        if (check_skoarpuscle_int (p, v))
            return true;

        if (check_skoarpuscle_float (p, static_cast<SkoarFloat>(v)))
            return true;
    }

    if (is_skoarpuscle<SkoarpuscleFloat> (p))
        if (check_skoarpuscle_float (p, static_cast<SkoarFloat>(v)))
            return true;

    return false;
}

bool check_skoarpuscle_num (SkoarpusclePtr p, SkoarFloat v) {
    return check_skoarpuscle_float (p, v);
}



bool check_skoarpuscle_string (SkoarpusclePtr p, SkoarString v) {
    return check_skoarpuscle_val<SkoarpuscleString, SkoarString> (p, v);
}

bool check_skoarpuscle_symbol (SkoarpusclePtr p, SkoarString v) {
    return check_skoarpuscle_val<SkoarpuscleSymbol, SkoarString> (p, v);
}


VectorOfSkoarEventsPtr skoar_get_events (Skoar* skoar) {
    auto events (make_shared<VectorOfSkoarEvents> ());
    try
    {
        skoar->play ([&](SkoarEventPtr e) {
            events->push_back (e->duplicate());
        });
    }
    catch (SkoarError &e)
    {
        FAIL (SkoarString_to_s (e.wwhat ()));
    }
    return events;
}

VectorOfSkoarEventsPtr skoar_get_events_inf (Skoar* skoar, size_t num) {
    auto events (make_shared<VectorOfSkoarEvents> ());
    try
    {
        size_t i (0);
        skoar->play ([&](SkoarEventPtr e) {
            events->push_back (e);

            if (++i >= num)
                skoar->cthulhu (L"skoar_get_events_inf");

        });
    }
    catch (SkoarError &e)
    {
        if (wstring (e.wwhat ()) != wstring (L"skoar_get_events_inf"))
            FAIL (SkoarString_to_s (e.wwhat ()));
    }
    return events;
}


VectorOfSkoarEventsPtr skoar_get_events_for_voice (Skoar* skoar, SkoarString voice) {
    auto events (make_shared<VectorOfSkoarEvents> ());
    try
    {
        skoar->play_voice (voice, [&](SkoarEventPtr e) {
            events->push_back (e);
        });
    }
    catch (SkoarError &e)
    {
        FAIL (SkoarString_to_s (e.wwhat ()));
    }
    return events;
}


VectorOfSkoarEventsPtr skoar_get_events_for_voice_skoarpion (Skoar* skoar, SkoarString voice, SkoarpionPtr skoarpion) {
    auto events (make_shared<VectorOfSkoarEvents> ());
    try
    {
        skoar->play_voice_skoarpion (voice, skoarpion, [&](SkoarEventPtr e) {
            events->push_back (e->duplicate());
        });
    }
    catch (SkoarError &e)
    {
        FAIL (SkoarString_to_s (e.wwhat ()));
    }
    return events;
}


VectorOfSkoarEventsPtr skoar_get_events_for_voice_skoarpion_chance_of_cthulhu (Skoar* skoar, SkoarString voice, SkoarpionPtr skoarpion) {
    auto events (make_shared<VectorOfSkoarEvents> ());
    try
    {
        skoar->play_voice_skoarpion (voice, skoarpion, [&](SkoarEventPtr e) {
            events->push_back (e->duplicate ());
        });
    }
    catch (SkoarRuntimeException &e)
    {
        SkoarEvent ev;

        ev.put (L"Cthulhu", make_skoarpuscle (true));
        ev.put (L"CthulhuString", make_skoarpuscle(e.sWhat));
        ev.put (L"CthulhuArgument", e.skoarpuscle);

        events->push_back (ev.duplicate ());
    }
    catch (SkoarError &e)
    {
        FAIL (SkoarString_to_s (e.wwhat ()));
    }
    return events;
}



void make_event_r (SkoarEventPtr)
{
    // done
}


void make_events_vec_r (VectorOfSkoarEventsPtr, SkoarEventPtr) {
    // done
}

void make_listy_r (ListOfSkoarpusclesPtr) {
    // done
}

// --- comparing event vectors --------------------------------------------------------

void compare_skoarpuscles_equal (SkoarpusclePtr desire, SkoarpusclePtr reality) {
    REQUIRE (desire->kind == reality->kind);

    if (is_skoarpuscle<SkoarpuscleInt> (desire))
    {
        auto desire_val (skoarpuscle_ptr<SkoarpuscleInt> (desire)->val);
        REQUIRE (check_skoarpuscle_int (reality, desire_val));
    }

    if (is_skoarpuscle<SkoarpuscleFloat> (desire))
    {
        auto desire_val (skoarpuscle_ptr<SkoarpuscleFloat> (desire)->val);
        REQUIRE (check_skoarpuscle_float (reality, desire_val));
    }

    if (is_skoarpuscle<SkoarpuscleFreq> (desire))
    {
        auto desire_val (skoarpuscle_ptr<SkoarpuscleFreq> (desire)->val);
        REQUIRE (check_skoarpuscle_freq (reality, desire_val));
    }

    if (is_skoarpuscle<SkoarpuscleString> (desire))
    {
        auto desire_val (skoarpuscle_ptr<SkoarpuscleString> (desire)->val);
        REQUIRE (check_skoarpuscle_string (reality, desire_val));
    }

    if (is_skoarpuscle<SkoarpuscleSymbol> (desire))
    {
        auto desire_val (skoarpuscle_ptr<SkoarpuscleSymbol> (desire)->val);
        REQUIRE (check_skoarpuscle_symbol (reality, desire_val));
    }

    if (is_skoarpuscle<SkoarpuscleList> (desire))
    {
        auto desire_val (skoarpuscle_ptr<SkoarpuscleList> (desire)->val);
        auto reality_val (skoarpuscle_ptr<SkoarpuscleList> (reality)->val);
        INFO ("comparing lists");
        compare_lists (desire_val, reality_val);
    }

    // todo: more kinds
}

void require_desire_in_event (SkoarString k, SkoarpusclePtr v, SkoarEventPtr ev) {
    auto event_entry (ev->at (k));


    REQUIRE (event_entry != nullptr);

    wostringstream stream;
    stream << "reality :: " << *event_entry;
    INFO (SkoarString_to_s (stream.str ()));


    compare_skoarpuscles_equal (v, event_entry);

}

void require_subset_of_event (SkoarEventPtr desire, SkoarEventPtr ev) {
    for (auto kv : desire->table)
    {
        SkoarString k (kv.first);
        SkoarpusclePtr v (kv.second);

        wostringstream stream;
        stream << "desire :: " << k << " : " << *v;
        INFO (SkoarString_to_s (stream.str ()));

        require_desire_in_event (k, v, ev);
    }
}

void compare_desires_to_events (VectorOfSkoarEventsPtr desires, VectorOfSkoarEventsPtr events) {

    REQUIRE (desires->size () == events->size ());

    auto n (desires->size ());

    for (int i = 0; i < n; ++i)
    {
        INFO ("beat " << i + 1);
        require_subset_of_event (desires->at (i), events->at (i));
    }

}

void compare_lists (ListOfSkoarpusclesPtr desires, ListOfSkoarpusclesPtr realities) {
    REQUIRE (desires->size () == realities->size ());

    auto n (desires->size ());

    auto des_it (desires->cbegin ());
    auto real_it (realities->cbegin ());

    for (int i = 0; i < n; ++i)
    {
        auto des_x (*(des_it++));
        auto real_x (*(real_it++));

        wostringstream stream;
        stream << " :: desire: " << *des_x << " :: reality " << *real_x;
        INFO ("list i: " << i << SkoarString_to_s (stream.str ()));

        compare_skoarpuscles_equal (des_x, real_x);
    }
}


void run_and_expect (SkoarString skoarce, VectorOfSkoarEventsPtr desires) {

    SkoarNullLogger SkoarLog;

    INFO ("SkoarBegin :: \"" << SkoarString_to_s (skoarce) << "\" :: SkoarEnd");
    Skoar skoar (skoarce, &SkoarLog);

    REQUIRE (skoar.parsedOk);
    auto events (skoar_get_events (&skoar));
    compare_desires_to_events (desires, events);
}


void run_and_expect_inf (SkoarString skoarce, VectorOfSkoarEventsPtr desires) {

    SkoarNullLogger SkoarLog;

    INFO ("SkoarBegin :: \"" << SkoarString_to_s (skoarce) << "\" :: SkoarEnd");

    Skoar skoar (skoarce, &SkoarLog);

    REQUIRE (skoar.parsedOk);
    auto events (skoar_get_events_inf (&skoar, desires->size ()));
    compare_desires_to_events (desires, events);
}

void run_and_expect_d (SkoarString skoarce, VectorOfSkoarEventsPtr desires) {

    SkoarConsoleLogger SkoarLog;
    SkoarLog.setLevel (ISkoarLog::debug);

    INFO ("SkoarBegin :: \"" << SkoarString_to_s (skoarce) << "\" :: SkoarEnd");

    Skoar skoar (skoarce, &SkoarLog);

    REQUIRE (skoar.parsedOk);
    auto events (skoar_get_events (&skoar));
    compare_desires_to_events (desires, events);
}

void print_skoarce (SkoarString skoarce) {

}

void run_skoar_test (SkoarString skoarce)
{
    SkoarNullLogger SkoarLog;

    INFO ("SkoarBegin :: \"" << SkoarString_to_s (skoarce) << "\" :: SkoarEnd");
    Skoar skoar (skoarce, &SkoarLog);

    REQUIRE (skoar.parsedOk);

    SkoarpionPtr run (nullptr), expect (nullptr);
    for (auto x : skoar.skoarpions)
        if (x->name == SkoarString (L"run"))
            run = x;

        else if (x->name == SkoarString (L"expect"))
            expect = x;

    REQUIRE (run != nullptr);
    REQUIRE (expect != nullptr);

    map<SkoarString, VectorOfSkoarEventsPtr> expectations;
    map<SkoarString, VectorOfSkoarEventsPtr> runs;

    auto voices (skoar.get_all_voices ());

    for (auto voice : voices)
    {
        if (voices.size () > 1 && voice == SkoarString (L"all"))
            continue;

        string prefix ("Voice: ");
        string s (prefix + SkoarString_to_s (voice));
        INFO (s);

        auto desires (skoar_get_events_for_voice_skoarpion_chance_of_cthulhu (&skoar, voice, expect));
        auto reality (skoar_get_events_for_voice_skoarpion_chance_of_cthulhu (&skoar, voice, run));

        compare_desires_to_events (desires, reality);
    }

}
