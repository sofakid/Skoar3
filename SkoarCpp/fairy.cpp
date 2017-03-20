#include "fairy.hpp"

#include "exception.hpp"
#include "skoarpuscle.hpp"

SkoarFairy::SkoarFairy(SkoarString nom, SkoarMinstrelPtr m) :
    name(nom),
    minstrel(m),
    magic(HarmlessMagic)
{
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

void SkoarFairy::push() {
    magic_stack.push_back(magic);
    magic = HarmlessMagic;

    listy_stack.push_back(make_shared<ListOfSkoarpuscles>());
    //"$.push;".postln;
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




void SkoarFairy::push_impression() {

}

void SkoarFairy::pop_impression() {

}


void SkoarFairy::push_noating() {

}

void SkoarFairy::pop_noating() {

}


void SkoarFairy::push_i() {

}

void SkoarFairy::pop_i() {

}

void SkoarFairy::incr_i() {

}


void SkoarFairy::push_times_seen() {

}

void SkoarFairy::pop_times_seen() {

}


void SkoarFairy::how_many_times_have_you_seen(SkoarpusclePtr) {

}

void SkoarFairy::forget_that_you_have_seen(SkoarpusclePtr) {

}


void SkoarFairy::push_compare() {

}

void SkoarFairy::pop_compare() {

}


void SkoarFairy::compare_impress(SkoarMinstrelPtr) {

}


void SkoarFairy::push_boolean() {

}

void SkoarFairy::pop_boolean() {

}

SkoarpusclePtr SkoarFairy::impress_i() {
    return nullptr;
}

SkoarpusclePtr SkoarFairy::impress(SkoarpusclePtr x) {
    //("$:" ++name++ ".impression: " ++x.asString).postln;
    auto p = x.get();

    if (typeid(p) == typeid(SkoarpuscleDeref*)) {
        impression = static_cast<SkoarpuscleDeref*>(p)->lookup(minstrel);
    };

    if (impression->isNoatworthy() == true) {
        noat = impression;
    };

    return impression;
}

void SkoarFairy::compile_ugen() {

}


SkoarpusclePtr SkoarFairy::exact_duration() {
    return nullptr;
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

void SkoarFairy::consider(SkoarEvent&) {

}

void SkoarFairy::consider_amp(SkoarEvent&) {

}




// ----------------------------------------------------------------------
// --- SkoarpuscleFairy -------------------------------------------------
SkoarpuscleFairy::SkoarpuscleFairy() {

}