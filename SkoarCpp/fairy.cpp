#include "fairy.hpp"

#include "exception.hpp"
#include "skoarpuscle.hpp"
#include "minstrel.hpp"
#include "make_skoarpuscle.hpp"

SkoarFairy::SkoarFairy (SkoarString nom, SkoarMinstrelPtr m) :
    name (nom),
    minstrel (m),
    magic (HarmlessMagic),
    times_seen (make_shared<FairyTimesMap> ()),
    fly_to_dest (0),
    al_fine (false),
    l_value (make_skoarpuscle (nullptr)),
    noat (make_skoarpuscle (nullptr)),
    impression (make_skoarpuscle (nullptr)),
    boolean_impression (make_skoarpuscle(nullptr))

{
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o().allocFairy(name);
#endif
    //push_times_seen();
}

SkoarFairy::~SkoarFairy() {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o().deallocFairy(name);
#endif
    fly_away();
}

void SkoarFairy::fly_away() {
    i = 0;
    fly_to_dest = 0;
    impression = nullptr;
    listy_stack.empty();
    impression_stack.clear();
    noatworthy_stack.clear();
    magic_stack.clear();
    noating_stack.clear();
    i_stack.clear();
    times_seen_stack.clear();
    times_seen = nullptr;
    boolean_stack.clear();
    minstrel = nullptr;
}

// magic stacks and list collecting
ListOfSkoarpusclesPtr SkoarFairy::get_top_listy() {
    if (listy_stack.empty())
        return nullptr;

    return listy_stack.back();
}

void SkoarFairy::set_top_listy(ListOfSkoarpusclesPtr x) {
    listy_stack.push_back(x);
}

void SkoarFairy::next_listy() {
    auto listy = get_top_listy();

    if (listy != nullptr) {
        (*listy).push_back(impression);
    }
}


void SkoarFairy::push_impression() {
    impression_stack.push_back(impression);
    noatworthy_stack.push_back(noatworthy);
}

void SkoarFairy::pop_impression() {
    noatworthy = noatworthy_stack.back();
    noatworthy_stack.pop_back();
    if (noatworthy == true) {
        auto x = impression_stack.back();
        impression_stack.pop_back();
        impress(x);
    }
}


void SkoarFairy::push() {
    magic_stack.push_back(magic);
    magic = HarmlessMagic;

    listy_stack.push_back(make_shared<ListOfSkoarpuscles>());
    //"$.push;".postln;

    minstrel->koar->push_state();
}

SkoarpusclePtr SkoarFairy::pop() {
    if (magic_stack.empty())
        throw SkoarError(L"Magic Stack Underflow");

    magic = magic_stack.back();
    magic_stack.pop_back();

    minstrel->koar->pop_state();

    if (listy_stack.empty ())
        throw SkoarError (L"Listy Stack Underflow");

    auto listy = listy_stack.back();
    listy_stack.pop_back();

    impress(make_shared<SkoarpuscleList>(listy));

    //"popped listy: ".post; impression.postln;

    return impression;
}

void SkoarFairy::push_noating(bool n) {
    name = (n ? L"." : L"!") + name;
    noating_stack.push_back(noating);
    noating = n;
}

void SkoarFairy::pop_noating() {
    name = name.substr(1);
    noating = noating_stack.back();
    noating_stack.pop_back();
}

void SkoarFairy::push_i() {
    i_stack.push_back(i);
}

void SkoarFairy::pop_i() {
    i = i_stack.back();
    i_stack.pop_back();
}

void SkoarFairy::incr_i() {
    ++i;
}

void SkoarFairy::push_times_seen() {
    times_seen_stack.push_back(times_seen);
    times_seen = make_shared<FairyTimesMap>();
}

void SkoarFairy::pop_times_seen() {
    times_seen = times_seen_stack.back();
    times_seen_stack.pop_back();
}

/*
typedef map<SkoarNoadAddress, SkoarInt> FairyTimesAddressSeen;
typedef map<ESkoarpuscle::Kind, FairyTimesAddressSeen> FairyTimesMap;
typedef shared_ptr<FairyTimesMap> FairyTimesMapPtr;
typedef list<FairyTimesMapPtr> ListOfFairyTimesMaps;
*/
SkoarInt SkoarFairy::how_many_times_have_you_seen(ESkoarpuscle::Kind kind, size_t offs) {

    auto &addressMap = (*times_seen)[kind];
    auto times = addressMap[offs];

    ++times;
    addressMap[offs] = times;
    return times;
}

void SkoarFairy::forget_that_you_have_seen(ESkoarpuscle::Kind kind) {
    for (auto times_map : times_seen_stack) {
        if (times_map != nullptr)
        {
            (*times_map)[kind].clear ();
        }
        else
        {
            throw SkoarError (L"WTF times_map is nullptr");
        }

    }
}


void SkoarFairy::forget_that_you_have_seen(size_t offs) {
    for (auto times_map : times_seen_stack) {
        for (auto kv : *times_map) {
            auto addressMap = kv.second;
            addressMap.erase(offs);
        }
    }
}

void SkoarFairy::on_bar (SkoarpuscleBars *skoarpuscle) {
    // :|
    if (skoarpuscle->pre_repeat)
        if (how_many_times_have_you_seen (ESkoarpuscle::Bars, skoarpuscle->offs) < 2)
            fly_to_colon ();

    // |:
    // if (skoarpuscle->post_repeat)
}

void SkoarFairy::fly_to_colon () {
    throw SkoarNav (SkoarNav::COLON);
}

void SkoarFairy::fly_to_coda (SkoarString label) {
    if (label == SkoarString (L""))
    {
        fly_to_dest = minstrel->skoar->markers_coda.front();
    }
    else
    {
        fly_to_dest = minstrel->skoar->markers_coda_named[label];
    }

    throw SkoarNav (SkoarNav::CODA);
}

void SkoarFairy::push_compare() {
    compare_stack.push_back(l_value);
    l_value = nullptr;
}

void SkoarFairy::pop_compare() {
    l_value = compare_stack.back();
    compare_stack.pop_back();
}

void SkoarFairy::compare_impress(SkoarMinstrelPtr m) {
    l_value = impression;

    // wha???? original comment: we want the impression now.
    if (is_skoarpuscle<SkoarpuscleFairy>(l_value)) {
        l_value = m->fairy->impression;
    }
}

void SkoarFairy::push_boolean() {
    boolean_stack.push_back(impression);
    push_noating();
}

void SkoarFairy::pop_boolean() {
    boolean_impression = impression;
    auto x = boolean_stack.back();
    boolean_stack.pop_back();
    impress(x);
    pop_noating();
}

SkoarpusclePtr SkoarFairy::impress_i() {
    return impress(i);
}

template<>
SkoarpusclePtr SkoarFairy::impress(SkoarpusclePtr x) {
    //("$:" ++name++ ".impression: " ++x.asString).postln;
    
    if (x == nullptr) {
        x = make_skoarpuscle(nullptr);
    }

    if (is_skoarpuscle<SkoarpuscleFairy>(x)) {
        return impression;
    };


    if (is_skoarpuscle<SkoarpusclePair>(x)) {
        auto p = skoarpuscle_ptr<SkoarpusclePair> (x);
        p->assign (minstrel);
    };

    if (is_skoarpuscle<SkoarpuscleDeref>(x)) {
        x = skoarpuscle_ptr<SkoarpuscleDeref>(x)->lookup(minstrel);
    };
    

    if (x->isImpressionable() == false) {
        return x;
    }
    
    impression = x;

    if (noating) {
        if (impression->isNoatworthy() == true) {
            noat = impression;
            noatworthy = true;
        }
        else {
            noatworthy = false;
        }
    }
    else {
        noatworthy = false;
    }
    minstrel->koar->put(L"impression", impression);

    if (is_skoarpuscle<SkoarpuscleUGen>(x)) {
        //lute.impress(impression);
    }
    else if (is_skoarpuscle<SkoarpuscleInt>(x) || is_skoarpuscle<SkoarpuscleFloat>(x)) {
        minstrel->koar->put(L"num_impression", impression);
        //num_impression = impression;
        minstrel->koar->put(L"exact_dur", impression);
    }
    else if (is_skoarpuscle<SkoarpuscleSymbol>(x)) {
        minstrel->koar->put(L"sym_impression", impression);
        //sym_impression = impression;
    }
    else if (is_skoarpuscle<SkoarpuscleDynamic>(x)) {
        minstrel->koar->put(L"dyn_impression", impression);
        //dyn_impression = impression;
    }
    else if (is_skoarpuscle<SkoarpuscleDuration>(x)) {
        minstrel->koar->put(L"exact_dur", impression);
    }

    return impression;
}

void SkoarFairy::compile_ugen() {
    //lute.compile_ugen();
}


SkoarpusclePtr SkoarFairy::exact_duration() {
    return exact;
}

void SkoarFairy::charge_arcane_magic(ArcaneMagic spell) {
    AncientArcaneMagic f (magic);

    magic = [=]() {
        f ();
        SkoarpusclePtr x (spell ());
        if (x != nullptr) 
            impress (x);
    };
}

SkoarpusclePtr SkoarFairy::cast_arcane_magic() {
    magic();
    magic = HarmlessMagic;

    return impression;
}

void SkoarFairy::consider(SkoarEventPtr e) {
    
    auto xs = e->at(L"tempo");
    /*auto x = 
    if (x <= 0) {
        x = 1;
    };
    e[\dur_by_tempo] = e[\dur] / x;
        
    //(name++".consider :: " ++ e).postln;
    e.yield;
    */
    minstrel->happen(e);
}

void SkoarFairy::consider_amp(SkoarEventPtr, SkoarMinstrelPtr) {
    /*
    if (worries.isNil) {
        if (noating == true) {
            var a = skrpe.amp;
            var offs = a - m.koar[\amp];
            m.controls.amp_bus.set(a);
            m.koar[\amp] = a;
        };
    } {
        dyn_impression = skrpe;
    };
    */
}




// ----------------------------------------------------------------------
// --- SkoarpuscleFairy -------------------------------------------------
SkoarpuscleFairy::SkoarpuscleFairy() {

}