#include "beaty.hpp"
#include "skoarpuscle.hpp"
#include "lex.hpp"
#include "minstrel.hpp"
#include "fairy.hpp"
#include <regex>


// --- SkoarpuscleDuration ------------------------------------------------
SkoarpuscleDuration::SkoarpuscleDuration(SkoarToke *toke) {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories.allocSkoarpuscle(L"Duration");
#endif
    //val = toke->lexeme.length();
    auto s = toke->lexeme;
    auto n = s.length();
    auto i = s.find_first_of(L':', 0);

    minutes = stoi(s.substr(0, i));
    seconds = stod(s.substr(i, n - i));
}

SkoarpuscleDuration::SkoarpuscleDuration(SkoarInt min, SkoarFloat sec) :
    minutes(min),
    seconds(sec) 
{
#if SKOAR_DEBUG_MEMORY
    SkoarMemories.allocSkoarpuscle(L"Duration");
#endif
}

SkoarpuscleDuration::~SkoarpuscleDuration() {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories.deallocSkoarpuscle(L"Duration");
#endif
}

void SkoarpuscleDuration::on_enter(SkoarMinstrelPtr m) {
    m->fairy->impress(make_shared<SkoarpuscleDuration>(minutes, seconds));
}


// --- SkoarpuscleExactBeat -----------------------------------------------
SkoarpuscleExactBeat::SkoarpuscleExactBeat(SkoarToke *toke) {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories.allocSkoarpuscle(L"ExactBeat");
#endif
    impressionable = false;
}

SkoarpuscleExactBeat::~SkoarpuscleExactBeat() {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories.deallocSkoarpuscle(L"ExactBeat");
#endif
}

void SkoarpuscleExactBeat::on_enter(SkoarMinstrelPtr m) {
    m->fairy->push_noating();
    m->fairy->push();
}

void SkoarpuscleExactBeat::after(SkoarMinstrelPtr m) {
    //auto dur = m->fairy->impression->flatten(m);

    m->fairy->pop();
    m->fairy->pop_noating();

    auto noat = m->fairy->noat->asNoat();

    //noat->execute(m);

    // create an event with everything we've collected up until now
    //auto e = m->koar->event(m);

    //e[L"dur"] = dur * e[L"tempo"];
    //m->fairy->consider(e);
}


// --- SkoarpuscleExactRest -----------------------------------------------
SkoarpuscleExactRest::SkoarpuscleExactRest(SkoarToke *toke) {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories.allocSkoarpuscle(L"ExactRest");
#endif
    impressionable = false;
}

SkoarpuscleExactRest::~SkoarpuscleExactRest() {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories.deallocSkoarpuscle(L"ExactRest");
#endif
}

void SkoarpuscleExactRest::on_enter(SkoarMinstrelPtr m) {
    m->fairy->push_noating();
    m->fairy->push();
}

void SkoarpuscleExactRest::after(SkoarMinstrelPtr m) {
    //auto dur = m->fairy->impression->flatten(m);

    m->fairy->pop();
    m->fairy->pop_noating();

    auto noat = m->fairy->noat->asNoat();

    //noat->execute(m);

    // create an event with everything we've collected up until now
    auto e = m->koar->event(m);

    //e[L"dur"] = dur * e[L"tempo"];
    //e[L"isRest"] = true;
    //m->fairy->consider(e);
}


// --- SkoarpuscleBeat -----------------------------------------------------
SkoarFloat SkoarpuscleBeat::beat_short(SkoarString s, SkoarInt n) {
    auto is_dotted = s.back() == L'.';
    
    if (is_dotted) {
        n = n - 1;
    }

    SkoarFloat x = pow(2.0, -1.0 * (SkoarFloat) n);

    if (is_dotted) {
        x = x * 1.5;
    }
    
    return x;
}

SkoarFloat SkoarpuscleBeat::beat_long(SkoarString s, SkoarInt n) {
    auto is_dotted = s.back() == L'.';

    if (is_dotted) {
        n = n - 1;
    }

    SkoarFloat x = pow(2.0, (SkoarFloat) n - 1.0);

    if (is_dotted) {
        x = x * 1.5;
    }

    return x;
}

SkoarpuscleBeat::SkoarpuscleBeat(SkoarToke *toke) {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories.allocSkoarpuscle(L"Beat");
#endif
    impressionable = false;
    
    s = toke->lexeme;
    auto n = s.length();

    if (s.front() == L'.') {
        is_staccato = true;
        --n;
    }
    else {
        is_staccato = false;
    }
    
    auto tie_pos = s.find(SkoarString(L"__"), 0);

    if (tie_pos != wstring::npos) {
        has_tie = true;
        is_grace = false;
        n = n - 2;
    }
    else {
        auto grace_pos = s.find(SkoarString(L"_"), 0);
        if (grace_pos != wstring::npos) {
            has_tie = true;
            is_grace = false;
            n = n - 2;
        }
        else {
            has_tie = false;
            is_grace = false;
        }
    }

    if (toke->kind == ESkoarToke::Eighths) {
        val = SkoarpuscleBeat::beat_short(s, n);
    } else {
        val = SkoarpuscleBeat::beat_long(s, n);
    }
}

SkoarpuscleBeat::~SkoarpuscleBeat() {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories.deallocSkoarpuscle(L"Beat");
#endif
}


void SkoarpuscleBeat::on_enter_sometimes(SkoarMinstrelPtr m) {
    SkoarFloat dur = val;

    //auto noat = m->fairy->noat->asNoat();

    //noat->execute(m);

    // create an event with everything we've collected up until now
    auto e = m->koar->event(m);

    e->put(L"dur", make_skoarpuscle(dur));
    m->fairy->consider(e);
}

// --- SkoarpuscleRest -----------------------------------------------------
SkoarpuscleRest::SkoarpuscleRest(SkoarToke *toke) {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories.allocSkoarpuscle(L"Rest");
#endif
    impressionable = false;

    s = toke->lexeme;
    auto n = s.length();

    if (toke->kind == ESkoarToke::Quavers) {
        // size -1 for the / (we just count the o's)
        val = SkoarpuscleBeat::beat_short(s, n - 1);
    } else {
        val = SkoarpuscleBeat::beat_long(s, n);
    }
}

SkoarpuscleRest::~SkoarpuscleRest() {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories.deallocSkoarpuscle(L"Rest");
#endif
}


void SkoarpuscleRest::on_enter_sometimes(SkoarMinstrelPtr m) {
    SkoarFloat dur = val;

    //auto noat = m->fairy->noat->asNoat();

    //noat->execute(m);

    // create an event with everything we've collected up until now
    auto e = m->koar->event(m);

    e->put(L"dur", make_skoarpuscle(dur));
    e->put(L"isRest", make_skoarpuscle(true));

    m->fairy->consider(e);
}