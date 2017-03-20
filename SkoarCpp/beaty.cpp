#include "beaty.hpp"
#include "skoarpuscle.hpp"
#include "lex.hpp"
#include "minstrel.hpp"
#include "fairy.hpp"
#include <regex>


// --- SkoarpuscleDuration ------------------------------------------------
SkoarpuscleDuration::SkoarpuscleDuration(SkoarToke *toke) {
    //val = toke->lexeme.length();
    auto s = toke->lexeme;
    auto n = s.length();
    auto i = s.find_first_of(L':', 0);

    minutes = stoi(s.substr(0, i));
    seconds = stod(s.substr(i, n - i));
}

SkoarpuscleDuration::SkoarpuscleDuration(SkoarInt min, SkoarFloat sec) :
    minutes(min),
    seconds(sec) {}

void SkoarpuscleDuration::on_enter(SkoarMinstrelPtr m) {
    m->fairy->impress(make_shared<SkoarpuscleDuration>(minutes, seconds));
}


// --- SkoarpuscleExactBeat -----------------------------------------------
SkoarpuscleExactBeat::SkoarpuscleExactBeat(SkoarToke *toke) {
    impressionable = false;
}

void SkoarpuscleExactBeat::on_enter(SkoarMinstrelPtr m) {
    m->fairy->push_noating();
    m->fairy->push();
}

void SkoarpuscleExactBeat::after(SkoarMinstrelPtr m) {
    auto dur = 0; //auto dur = m->fairy->impression->flatten_forgetfully(m);

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
    impressionable = false;
}

void SkoarpuscleExactRest::on_enter(SkoarMinstrelPtr m) {
    m->fairy->push_noating();
    m->fairy->push();
}

void SkoarpuscleExactRest::after(SkoarMinstrelPtr m) {
    auto dur = 0; //auto dur = m->fairy->impression->flatten_forgetfully(m);

    m->fairy->pop();
    m->fairy->pop_noating();

    auto noat = m->fairy->noat->asNoat();

    //noat->execute(m);

    // create an event with everything we've collected up until now
    //auto e = m->koar->event(m);

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
    } {
        val = SkoarpuscleBeat::beat_long(s, n);
    }
}


void SkoarpuscleBeat::on_enter_sometimes(SkoarMinstrelPtr m) {
    SkoarFloat dur = val;

    auto noat = m->fairy->noat->asNoat();

    //noat->execute(m);

    // create an event with everything we've collected up until now
    //auto e = m->koar->event(m);

    //e[L"dur"] = dur;
    //m->fairy->consider(e);
}

// --- SkoarpuscleRest -----------------------------------------------------
SkoarpuscleRest::SkoarpuscleRest(SkoarToke *toke) {
    impressionable = false;

    s = toke->lexeme;
    auto n = s.length();

    if (toke->kind == ESkoarToke::Quavers) {
        // size -1 for the / (we just count the o's)
        val = SkoarpuscleBeat::beat_short(s, n - 1);
    } {
        val = SkoarpuscleBeat::beat_long(s, n);
    }
}

void SkoarpuscleRest::on_enter_sometimes(SkoarMinstrelPtr m) {
    SkoarFloat dur = val;

    auto noat = m->fairy->noat->asNoat();

    //noat->execute(m);

    // create an event with everything we've collected up until now
    //auto e = m->koar->event(m);

    //e[L"dur"] = dur;
    //e[L"isRest"] = true;

    //m->fairy->consider(e);
}