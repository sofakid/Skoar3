#include "skoarpion.hpp"

#include "skoar.hpp"
#include "noad.hpp"
#include "skoarpuscle.hpp"
#include "skoar.hpp"
#include "all_skoarpuscles.hpp"

// --- Skoarpion ------------------------------------------------
SkoarpionPtr Skoarpion::NewFromSkoar(Skoar* skoar) {
    
    auto skoarpion = make_shared<Skoarpion>();
    skoarpion->init_from_skoar(skoar);
    skoar->skoarpions.push_back(skoarpion);
	return skoarpion;
}

SkoarpionPtr Skoarpion::NewFromSkoarNoad(Skoar* skoar, SkoarNoadPtr noad) {
    auto skoarpion = make_shared<Skoarpion>();
    skoarpion->init_from_noad(skoar, noad);
    skoar->skoarpions.push_back(skoarpion);
    return skoarpion;
}

SkoarpionPtr Skoarpion::NewFromSubtree(Skoar* skoar, SkoarNoadPtr subtree) {
    auto skoarpion = make_shared<Skoarpion>();
    skoarpion->init_from_subtree(skoar, subtree);
    skoar->skoarpions.push_back(skoarpion);
    return skoarpion;
}

Skoarpion::Skoarpion() :
    skoar(nullptr),
    body(nullptr),
    n(0),
    name(L"uninitialized")
{
}

void Skoarpion::init_from_skoar(Skoar* skoar) {
    name = L"skoar";
    this->skoar = skoar;
    
    body = SkoarNoad::NewArtificial(L"section");

    for (auto line : skoar->tree->children) {
        auto i = 0;
        auto v = line->next_skoarpuscle();

        if (is_skoarpuscle<SkoarpuscleVoice>(v)) {
            line->voice = skoar->get_voice(skoarpuscle_ptr<SkoarpuscleVoice>(v)->val);
        }

        if (line->children.size() > 0) {
            body->add_noad(line);
        }
    }

    list<SkoarInt> address;
    body->decorate_zero(skoar->all_voice, body, address, 0);
    n = body->size;
}


void Skoarpion::init_from_subtree(Skoar* skoar, SkoarNoadPtr subtree) {
    name = nullptr;
    this->skoar = skoar;

    body = subtree;

    for (auto line : subtree->children) {
        auto v = line->next_skoarpuscle();

        if (is_skoarpuscle<SkoarpuscleVoice>(v)) {
            line->voice = skoar->get_voice(skoarpuscle_ptr<SkoarpuscleVoice>(v)->val);
        }
    }

    list<SkoarInt> address;
    body->decorate_zero(skoar->all_voice, body, address, 0);
    n = subtree->size;
}

void Skoarpion::init_from_noad(Skoar* skoar, SkoarNoadPtr noad) {
    
    this->skoar = skoar;

    auto kidderatoar = noad->children.cbegin();

    // kid 0 - start
    // kid 1 - sig or suffix
    // kid 2 - suffix if no sig

    auto kid_1 = (*(++kidderatoar));
    auto kid_1_s = kid_1->skoarpuscle;

    SkoarNoadPtr suffix = nullptr;
    if (is_skoarpuscle<SkoarpuscleSkoarpionSig>(kid_1_s)) {
        auto p = skoarpuscle_ptr<SkoarpuscleSkoarpionSig>(kid_1_s);
        name = p->name;
        arg_list = p->arg_list;
        suffix = (*(++kidderatoar));
    } 
    else {
        suffix = kid_1;
    }

    auto line = SkoarNoad::NewArtificial(L"line");
    auto section = SkoarNoad::NewArtificial(L"section");
    list<SkoarNoadPtr> sections;

    for (auto x : suffix->children) {
        auto process_line = [&]() {
            auto v = line->next_skoarpuscle();

            if (is_skoarpuscle<SkoarpuscleVoice>(v)) {
                line->voice = skoar->get_voice(skoarpuscle_ptr<SkoarpuscleVoice>(v)->val);
            }

            if (line->children.size() > 0) {
                section->add_noad(line);
            }
        };

        auto toke = x->toke.get();
        if (is_toke<ESkoarToke::SkoarpionSep>(toke)) {
            process_line();
            sections.push_back(section);
            
            section = SkoarNoad::NewArtificial(L"section");
            line = SkoarNoad::NewArtificial(L"line");
        }
        else if (is_toke<ESkoarToke::Newline>(toke)) {
            process_line();
            line = SkoarNoad::NewArtificial(L"line");
        }
        else if (is_toke<ESkoarToke::SkoarpionEnd>(toke)) {
            process_line();
            sections.push_back(section);
        }
        else {
            line->add_noad(x);
        }
    }

    for (auto sec : sections) {
        auto i = 0;
        list<SkoarInt> parent_address;
        sec->decorate_zero(skoar->all_voice, sec, parent_address, i);
    }

    list<SkoarInt> address;
    body = sections.front(); // really? in skoar.sc it's sections[0].. wha?
    n = body->size;
}



// --- SkoarpionProjection ------------------------------------------------
SkoarpionProjectionPtr Skoarpion::projection(SkoarpionPtr skoarpion, SkoarString koar_name) {
	return make_shared<SkoarpionProjection>(skoarpion, koar_name);
}
