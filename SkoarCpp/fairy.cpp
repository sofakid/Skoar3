#include "fairy.hpp"

#include "exception.hpp"
#include "skoarpuscle.hpp"
#include "minstrel.hpp"
#include "make_skoarpuscle.hpp"

SkoarFairy::SkoarFairy(SkoarString nom, SkoarMinstrelPtr m) :
    name(nom),
    minstrel(m),
    magic(HarmlessMagic),
    times_seen(nullptr)
{
#if SKOAR_DEBUG_MEMORY
    SkoarMemories.allocFairy(name);
#endif
    push_times_seen();
}

SkoarFairy::~SkoarFairy() {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories.deallocFairy(name);
#endif
    fly_away();
}

void SkoarFairy::fly_away() {
    i = 0;
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

    //minstrel->koar->push_state();
}

SkoarpusclePtr SkoarFairy::pop() {
    if (magic_stack.empty()) {
        throw SkoarError(L"Magic Stack Underflow");
    }

    magic = magic_stack.back();
    magic_stack.pop_back();

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
    times_seen = make_shared<map<Skoarpuscle*, SkoarInt>>();
}

void SkoarFairy::pop_times_seen() {
    times_seen = times_seen_stack.back();
    times_seen_stack.pop_back();
}

SkoarInt SkoarFairy::how_many_times_have_you_seen(Skoarpuscle* x) {
    auto times = (*times_seen)[x];

    ++times;
    (*times_seen)[x] = times;
    return times;
}

void SkoarFairy::forget_that_you_have_seen(Skoarpuscle*) {

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
    
    if (is_skoarpuscle<SkoarpuscleDeref>(x)) {
        impression = skoarpuscle_ptr<SkoarpuscleDeref>(x)->lookup(minstrel);
    };
    
    impression = x;

    if (impression->isNoatworthy() == true) {
        noat = impression;
    };

    return impression;
}

void SkoarFairy::compile_ugen() {
    //lute.compile_ugen();
}


SkoarpusclePtr SkoarFairy::exact_duration() {
    return exact;
}

void SkoarFairy::charge_arcane_magic(ArcaneMagic spell) {
    ArcaneMagic f = magic;

    magic = [=]() {
        //                "ARCANE-alpha".postln;
        f();
        //            "ARCANE-omega".postln;
        SkoarpusclePtr x = spell();
        if (x != nullptr) {
            impress(x);
        }
        return nullptr;
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