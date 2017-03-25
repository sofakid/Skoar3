#include "skoarpion.hpp"

#include "skoar.hpp"
#include "noad.hpp"
#include "skoarpuscle.hpp"
#include "skoar.hpp"
#include "all_skoarpuscles.hpp"
#include "koar.hpp"

// --- Skoarpion ------------------------------------------------
SkoarpionPtr Skoarpion::NewFromSkoar(Skoar* skoar) {
    
    auto skoarpion = make_shared<Skoarpion>(L"from skoar");
    skoarpion->init_from_skoar(skoar);
    skoar->skoarpions.push_back(skoarpion);
	return skoarpion;
}

SkoarpionPtr Skoarpion::NewFromSkoarNoad(Skoar* skoar, SkoarNoadPtr noad) {
    auto skoarpion = make_shared<Skoarpion>(L"from noad");
    skoarpion->init_from_noad(skoar, noad);
    skoar->skoarpions.push_back(skoarpion);
    return skoarpion;
}

SkoarpionPtr Skoarpion::NewFromSubtree(Skoar* skoar, SkoarNoadPtr subtree) {
    auto skoarpion = make_shared<Skoarpion>(L"from subtree");
    skoarpion->init_from_subtree(skoar, subtree);
    skoar->skoarpions.push_back(skoarpion);
    return skoarpion;
}

Skoarpion::Skoarpion(const SkoarString from) :
    skoar(nullptr),
    body(nullptr),
    n(0),
    name(L"uninitialized"),
    made_from(from)
{
#if SKOAR_DEBUG_MEMORY
    SkoarMemories.allocSkoarpion(made_from);
#endif
}

Skoarpion::Skoarpion(const Skoarpion *other) :
    skoar(other->skoar),
    body(other->body),
    n(other->n),
    name(other->name),
    arg_list(other->arg_list),
    made_from(other->made_from)
{
#if SKOAR_DEBUG_MEMORY
    SkoarMemories.allocSkoarpion(made_from);
#endif
}

Skoarpion::~Skoarpion() {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories.deallocSkoarpion(made_from);
#endif
    clear();
}

void Skoarpion::clear() {
    if (body != nullptr) {
        body->clear();
        body = nullptr;
    }
    n = 0;
    arg_list = nullptr;
    skoar = nullptr;
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

    SkoarNoadAddress address;
    body->decorate_zero(skoar->all_voice, body, address, 0);
    n = body->size;
}


void Skoarpion::init_from_subtree(Skoar* skoar, SkoarNoadPtr subtree) {
    name = L"=^.^=";
    this->skoar = skoar;

    body = subtree;

    for (auto line : subtree->children) {
        auto v = line->next_skoarpuscle();

        if (is_skoarpuscle<SkoarpuscleVoice>(v)) {
            line->voice = skoar->get_voice(skoarpuscle_ptr<SkoarpuscleVoice>(v)->val);
        }
    }

    SkoarNoadAddress address;
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
        SkoarNoadAddress parent_address;
        sec->decorate_zero(skoar->all_voice, sec, parent_address, i);
    }

    body = sections.front(); // really? in skoar.sc it's sections[0].. wha?
    n = body->size;
}

SkoarpionProjectionPtr Skoarpion::projection(SkoarpionPtr skoarpion, SkoarString koar_name) {
	return make_shared<SkoarpionProjection>(skoarpion, koar_name);
}

void Skoarpion::draw_tree(wostringstream &out) {
    out << "--< Skoarpion " << name << " >---\n";

    if (is_skoarpuscle<SkoarpuscleArgList>(arg_list)) {
        out << "arg_list: ";
        arg_list->asString(out);
        out << "\n";

        auto listy = skoarpuscle_ptr<SkoarpuscleArgList>(arg_list)->args_names;

        for (auto x : listy ) {
            out << x << " ";
        }

        out << "\n";
    }

    if (body != nullptr) {
        body->draw_tree(out);
    }

}

// --- SkoarpionProjection ------------------------------------------------
SkoarpionProjection::SkoarpionProjection(SkoarpionPtr skoarpion, SkoarString koar_name) :
    body(nullptr),
    proj(SkoarNoad::NewArtificial(L"projection"))
{
    auto kids = skoarpion->body->children;

    size_t n = kids.size();
    skip_to.reserve(n);
    
    size_t i = 0;
    for (; i < n; ++i)
        skip_to.push_back(0);
    i = 0;
    
    for (auto x : kids) {
        auto s = x->voice->name;
        if ((s == koar_name) || (s == L"all")) {
            auto addr = x->address;
            auto m = addr.size();

            if (m > 0) {
                skip_to[addr[m - 1]] = i;
            }
            ++i;

            // don't use add_noad, it corrupts noad.
            proj->children.push_back(x);
            proj->skoap = x->skoap;
        }
    }

    // need these?
    //arr = proj->children;
    //i = 0;
    //n = arr.size();
}


/*list<SkoarInt> get_skip_to();
SkoarString    get_name();
SkoarNoadPtr   block();
SkoarNoadPtr   in_line();
SkoarNoadPtr   meditation();
*/
SkoarNoadAddress SkoarpionProjection::map_dst(SkoarNoadPtr dst) {
    auto addr = dst->address;
    
    if (addr.empty())
        return addr;

    auto j = addr.back();
    addr.pop_back();
    addr.push_back(skip_to[j]);
    return addr;
}
