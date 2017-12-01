#include "beaty.hpp"
#include "skoarpuscle.hpp"
#include "lex.hpp"
#include "minstrel.hpp"
#include "fairy.hpp"
#include <regex>
#include "make_skoarpuscle.hpp"
#include "pitchy.hpp"

void flatten_list_r (ListOfSkoarpuscles* listy, SkoarpusclePtr p) {
    
    if (is_skoarpuscle<SkoarpuscleInt> (p))
    {
        listy->push_back (p);
    }

    if (is_skoarpuscle<SkoarpuscleNoat> (p))
    {
        auto x = skoarpuscle_ptr<SkoarpuscleNoat> (p);
        listy->push_back (make_skoarpuscle (x->val));
    }

    else if (is_skoarpuscle<SkoarpuscleChoard> (p))
    {
        auto x = skoarpuscle_ptr<SkoarpuscleChoard> (p)->val;
        for (auto& y : *x)
            flatten_list_r (listy, y);
    }

    else if (is_skoarpuscle<SkoarpuscleList> (p))
    {
        auto x = skoarpuscle_ptr<SkoarpuscleList> (p)->val;
        for (auto& y : *x)
            flatten_list_r (listy, y);
    }

}

SkoarpusclePtr flatten_list (SkoarpusclePtr p) {
    auto listy = make_shared<ListOfSkoarpuscles> ();
    flatten_list_r (listy.get (), p);
    return make_skoarpuscle (listy);
}

void execute_noat (SkoarpusclePtr s, SkoarMinstrelPtr m) {
    auto& koar (*m->koar);
    if (is_skoarpuscle<SkoarpuscleFloat> (s))
    {
        koar.put (L"freq", s);
        koar.put (L"note", nullptr);
        koar.put (L"choard", nullptr);
    }

    else if (is_skoarpuscle<SkoarpuscleInt> (s))
    {
        koar.put (L"freq", nullptr);
        koar.put (L"note", s);
        koar.put (L"choard", nullptr);
    }

    else if (is_skoarpuscle<SkoarpuscleNoat> (s))
    {
        auto p = skoarpuscle_ptr<SkoarpuscleNoat> (s);
        koar.put (L"freq", nullptr);
        koar.put (L"note", make_skoarpuscle (p->val));
        koar.put (L"choard", nullptr);
    }

    else if (is_skoarpuscle<SkoarpuscleChoard> (s))
    {
        koar.put (L"freq", nullptr);
        koar.put (L"note", nullptr);
        koar.put (L"choard", flatten_list (s));
    }

    else if (is_skoarpuscle<SkoarpuscleList> (s))
    {
        koar.put (L"freq", nullptr);
        koar.put (L"note", nullptr);
        koar.put (L"choard", flatten_list (s));
    }
}

// --- SkoarpuscleDuration ------------------------------------------------
SkoarpuscleDuration::SkoarpuscleDuration(SkoarToke *toke) {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o().allocSkoarpuscle(L"Duration");
#endif
    //val = toke->lexeme.length();
    try
    {
        auto s = toke->lexeme;
        auto n = s.length();
        auto i = s.find_first_of(L':', 0);

        minutes = stoi(s.substr(0, i));
        seconds = stod(s.substr(i, n - i));
    }
    catch (const std::invalid_argument& /*ia*/)
    {
        //throw SkoarDecoratingException (L"stod/i - invalid arg");
        minutes = 0;
        seconds = 0;
    }
    catch (const std::out_of_range& /*oor*/)
    {
        minutes = 0;
        seconds = 0;
        //throw SkoarDecoratingException (L"stod/i - out of range");
    }
}

SkoarpuscleDuration::SkoarpuscleDuration(SkoarInt min, SkoarFloat sec) :
    minutes(min),
    seconds(sec) 
{
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o().allocSkoarpuscle(L"Duration");
#endif
}

SkoarpuscleDuration::~SkoarpuscleDuration() {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o().deallocSkoarpuscle(L"Duration");
#endif
}

void SkoarpuscleDuration::on_enter(SkoarMinstrelPtr m) {
    m->fairy->impress(make_shared<SkoarpuscleDuration>(minutes, seconds));
}


// --- SkoarpuscleExactBeat -----------------------------------------------
SkoarpuscleExactBeat::SkoarpuscleExactBeat(SkoarToke* /*toke*/) {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o().allocSkoarpuscle(L"ExactBeat");
#endif
    impressionable = false;
}

SkoarpuscleExactBeat::~SkoarpuscleExactBeat() {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o().deallocSkoarpuscle(L"ExactBeat");
#endif
}

void SkoarpuscleExactBeat::on_enter(SkoarMinstrelPtr m) {
    auto& fairy (*m->fairy);
    fairy.push_noating();
    fairy.push();
}

void SkoarpuscleExactBeat::after(SkoarMinstrelPtr m) {
    //auto dur = m->fairy->impression->flatten(m);
    auto& fairy (*m->fairy);
    fairy.pop();
    fairy.pop_noating();

    execute_noat (fairy.noat, m);
    //auto noat = fairy.noat->asNoat();

    //noat->execute(m);

    // create an event with everything we've collected up until now
    //auto e = m->koar->event(m);

    //e[L"dur"] = dur * e[L"tempo"];
    //fairy.consider(e);
}


// --- SkoarpuscleExactRest -----------------------------------------------
SkoarpuscleExactRest::SkoarpuscleExactRest(SkoarToke* /*toke*/) {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o().allocSkoarpuscle(L"ExactRest");
#endif
    impressionable = false;
}

SkoarpuscleExactRest::~SkoarpuscleExactRest() {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o().deallocSkoarpuscle(L"ExactRest");
#endif
}

void SkoarpuscleExactRest::on_enter(SkoarMinstrelPtr m) {
    auto& fairy (*m->fairy);
    fairy.push_noating();
    fairy.push();
}

void SkoarpuscleExactRest::after(SkoarMinstrelPtr m) {
    //auto dur = m->fairy->impression->flatten(m);

    auto& fairy (*m->fairy);
    fairy.pop();
    fairy.pop_noating();

    //auto noat = m->fairy->noat->asNoat();
    //noat->execute(m);

    execute_noat (fairy.noat, m);

    // create an event with everything we've collected up until now
    auto e = m->koar->event(m);

    //e[L"dur"] = dur * e[L"tempo"];
    //e[L"isRest"] = true;
    //m->fairy->consider(e);
}


// --- SkoarpuscleBeat -----------------------------------------------------
SkoarFloat SkoarpuscleBeat::beat_short(SkoarString s, SkoarInt n) {
    auto is_dotted = s.back() == L'.';
    
    if (is_dotted)
        --n;

    SkoarFloat x (pow(2.0, -1.0 * (SkoarFloat) n));

    if (is_dotted)
        x *= 1.5;
    
    return x;
}

SkoarFloat SkoarpuscleBeat::beat_long(SkoarString s, SkoarInt n) {
    auto is_dotted = s.back() == L'.';

    if (is_dotted)
        --n;

    SkoarFloat x (pow(2.0, (SkoarFloat) n - 1.0));

    if (is_dotted)
        x *= 1.5;
    

    return x;
}

SkoarpuscleBeat::SkoarpuscleBeat(SkoarToke *toke) {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o().allocSkoarpuscle(L"Beat");
#endif
    impressionable = false;
    
    s = toke->lexeme;
    auto n (s.length());

    if (s.front() == L'.') {
        is_staccato = true;
        --n;
    }
    else 
        is_staccato = false;
    
    auto tie_pos (s.find(SkoarString(L"__"), 0));

    if (tie_pos != wstring::npos) {
        has_tie = true;
        is_grace = false;
        n -= 2;
    }
    else {
        auto grace_pos = s.find(SkoarString(L"_"), 0);
        if (grace_pos != wstring::npos) {
            has_tie = true;
            is_grace = false;
            n -= 2;
        }
        else {
            has_tie = false;
            is_grace = false;
        }
    }

    if (toke->kind == ESkoarToke::Eighths) 
        val = SkoarpuscleBeat::beat_short(s, n);
    else
        val = SkoarpuscleBeat::beat_long(s, n);
}

SkoarpuscleBeat::~SkoarpuscleBeat() {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o().deallocSkoarpuscle(L"Beat");
#endif
}


void SkoarpuscleBeat::on_enter_sometimes(SkoarMinstrelPtr m) {
    SkoarFloat dur = val;

    //auto noat = m->fairy->noat->asNoat();
    //noat->execute(m);

    auto& fairy (*m->fairy);
    execute_noat (fairy.noat, m);

    // create an event with everything we've collected up until now
    auto e (m->koar->event(m));

    e->put(L"dur", make_skoarpuscle(dur));
    fairy.consider(e);
}

// --- SkoarpuscleRest -----------------------------------------------------
SkoarpuscleRest::SkoarpuscleRest(SkoarToke *toke) {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o().allocSkoarpuscle(L"Rest");
#endif
    impressionable = false;

    s = toke->lexeme;
    auto n (s.length());

    // size -1 for the / (we just count the o's)
    if (toke->kind == ESkoarToke::Quavers)
        val = SkoarpuscleBeat::beat_short(s, n - 1);
    else 
        val = SkoarpuscleBeat::beat_long(s, n);
}

SkoarpuscleRest::~SkoarpuscleRest() {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o().deallocSkoarpuscle(L"Rest");
#endif
}


void SkoarpuscleRest::on_enter_sometimes(SkoarMinstrelPtr m) {
    SkoarFloat dur = val;

    auto& fairy (*m->fairy);
    //auto noat = m->fairy->noat->asNoat();

    //noat->execute(m);
    execute_noat (fairy.noat, m);

    // create an event with everything we've collected up until now
    auto e (m->koar->event(m));

    e->put(L"dur", make_skoarpuscle(dur));
    e->put(L"isRest", make_skoarpuscle(true));

    fairy.consider(e);
}