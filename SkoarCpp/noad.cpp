#pragma once
#include "skoarcery.hpp"

#include "lex.hpp"
#include "event.hpp"
#include "skoarpuscle.hpp"
#include "toker.hpp"
#include "noad.hpp"
#include "styles.hpp"
#include "koar.hpp"

#include "memories.hpp"

/*
// --- SkoarNoadAddress ---------------------------------------------------------
SkoarNoadAddress::SkoarNoadAddress(size_t n) {
    data.reserve(n);
}

SkoarNoadAddress::SkoarNoadAddress(const SkoarNoadAddress &other) {
    data = other.data;
}

SkoarInt& SkoarNoadAddress::operator[] (size_t i) {
    return data[i];
}
*/

// ==========================
// The Parse Tree - SkoarNoad
// ==========================

SkoarNoad::SkoarNoad(const wchar_t *nameArg, SkoarNoadPtr parentArg, const ESkoarNoad::Kind kindArg, const SkoarStyles::EStyle styleArg) :
    parent(parentArg),
    name(nameArg),
    skoarce(nullptr),
    kind(kindArg),
    style(styleArg),
    voice(nullptr),
    skoarpuscle(nullptr)
{
#if SKOAR_DEBUG_MEMORY
    SkoarMemories.allocNoad(name);
#endif
}

SkoarNoadPtr SkoarNoad::New(const wchar_t *nameArg, SkoarNoadPtr parentArg, SkoarTokePtr toke)
{
    SkoarNoadPtr x = make_shared<SkoarNoad>(nameArg, parentArg, ESkoarNoad::toke, toke->style);
    x->skoarce = &toke->lexeme;
    x->size = toke->size;
    x->toke = move(toke);

    return x;
}

SkoarNoadPtr SkoarNoad::NewArtificial(const wchar_t *nameArg, SkoarNoadPtr parentArg)
{
    return SkoarNoad::New<ESkoarNoad::artificial>(nameArg, parentArg);
}

SkoarNoadPtr SkoarNoad::NewArtificial(const wchar_t *nameArg)
{
    return SkoarNoad::New<ESkoarNoad::artificial>(nameArg, nullptr);
}

SkoarNoadPtr SkoarNoad::NewAlias(const wchar_t *nameArg)
{
    return SkoarNoad::New<ESkoarNoad::alias>(nameArg, nullptr);
}


SkoarNoad::~SkoarNoad() {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories.deallocNoad(name);
#endif
    clear();
}

void SkoarNoad::clear() {
    if (kind == ESkoarNoad::alias) {
        // this one just erases the children references
        children.clear();
    } 
    else {
        // this one erases the entire subtree
        clear_children();
    }
    clear_values();
}

void SkoarNoad::clear_children() {
    // visit the noads depth-first, clear children and unset all shared_ptrs. 
    // should then trigger destruction.
    depth_visit([](SkoarNoad *noad) {
        noad->children.clear();
        noad->clear_values();
    });
    children.clear();
}
void SkoarNoad::clear_values() {
    parent = nullptr;
    skoap = nullptr;
    skoarce = nullptr;
    toke = nullptr;
    voice = nullptr;
    skoarpuscle = nullptr;
    size = 0;
    offs = 0;
}

SkoarString *SkoarNoad::asString() {
    if (skoarce == nullptr)
        return new SkoarString(name + L": nullptr");

	return new SkoarString(name + L": " + *skoarce);
}

// -------------------
// decorating the tree
// -------------------
void SkoarNoad::decorate_zero(SkoarKoarPtr v, SkoarNoadPtr s, SkoarNoadAddress &/*parent_address*/, SkoarInt i) {

	if (voice == nullptr) {
		voice = v;

	}
	else {
		// the voice has changed, this is what the children get
		v = voice;
	}

    // decorate_zero starts with an empty address
	address.clear();
	skoap = s;

	i = 0;
	for (auto y : children) {
		y->decorate(v, s, address, i);
		++i;
	}

}

void SkoarNoad::decorate(SkoarKoarPtr v, SkoarNoadPtr s, SkoarNoadAddress &parent_address, SkoarInt i) {

	if (voice == nullptr) {
		voice = v;
	}
	else {
		// the voice has changed, this is what the children get
		v = voice;
	}

    // decorate starts with an existing address
    address = parent_address;
	address.emplace(address.begin(), i);
	skoap = s;

	i = 0;
	size = 0;
	for (auto y : children) {
		y->decorate(v, s, address, i);
		i = i + 1;
		//skoarce += y->skoarce;
        size += y->size;
	}

}

// ----------------
// growing the tree
// ----------------
void SkoarNoad::add_noad(SkoarNoadPtr noad) {
	children.push_back(noad);
}

// ----------------
// showing the tree
// ----------------
void SkoarNoad::log_tree(ISkoarLog *log, int tab)	{

    if (log->getLevel() != ISkoarLog::debug)
        return;

    wostringstream out;

	SkoarString s = SkoarString(tab * 2, L' ');

	//delete tabs;

	if (voice != nullptr) {
		out << voice->name + L":" << s;
	}
	else {
		out << L" novoice :" << s;
	}

    out << name;
	if (skoarpuscle != nullptr) {
        out << " :: ";
		skoarpuscle->asString(out);
	}

	log->i(out.str());

	for (auto x : children) {
		x->log_tree(log, tab + 1);
	}

}

void SkoarNoad::draw_tree(wostringstream &out, int tab)	{
 
	SkoarString s = SkoarString(tab * 2, L' ');
	
	//delete tabs;

	if (voice != nullptr) {
		out << voice->name << L":" << s;
	}
	else {
        out << L" novoice :" << s;
	}

    out << name;

	if (skoarpuscle != nullptr) {
        out << " - " << *skoarpuscle;
	}
    out << L"\n";

	for (auto x : children) {
		x->draw_tree(out, tab + 1);
	}

	//SkoarString sa = skoap->asString() + ":";
	//stirng *sv;

	/*address.reverseDo{
	| x |
	sa = sa ++ x.asString++ ";";
	};

	sv = if (voice.notNil) {
	voice.name.asString.padLeft(n)++ ":"
	} {
	":".padLeft(n + 1)
	};

	s = sa.padRight(n) ++sv++ " ".padLeft(tab) ++name;

	if (skoarpuscle.notNil) {
	s = s++ ": " ++skoarpuscle.val;
	};

	s = s++ "\n";
	children.do {
	| x |
	s = if (x.isKindOf(SkoarNoad)) {
	s ++ x.draw_tree(tab + 1)
	} {
	s++ " ".padLeft(tab + 1) ++x.class.asString++ "\n"
	};
	};
	*/
}


// -----------------
// climbing the Tree
// -----------------

// static versions for use with shared_ptrs
void SkoarNoad::depth_visit(SkoarNoadPtr p, SpellOfNoadPtrs f) {
    if (!p->children.empty())
        for (auto y : p->children)
            SkoarNoad::depth_visit(y, f);
    f(p);
}

void SkoarNoad::inorder(SkoarNoadPtr p, SpellOfNoadPtrs f) {
    f(p);
    if (!p->children.empty())
        for (auto y : p->children)
            SkoarNoad::inorder(y, f);
}

void SkoarNoad::inorderBeforeAfter(SkoarNoadPtr p, SpellOfNoadPtrs f, SpellOfNoadPtrs g) {
    f(p);
    if (!p->children.empty())
        for (auto y : p->children)
            SkoarNoad::inorderBeforeAfter(y, f, g);
    g(p);
}



// depth-first, find the leaves, run handler, working towards trunk
//
// if it's crashing during the decorating stage, here's a good place to
// start debugging
void SkoarNoad::depth_visit(SpellOfNoads f) {
    if (!children.empty())
		for (auto y: children)
			y->depth_visit(f);
    f(this);
}

void SkoarNoad::inorder(SpellOfNoads f) {
	f(this);
	if (!children.empty())
		for (auto y : children)
			y->inorder(f);
}

void SkoarNoad::inorderBeforeAfter(SpellOfNoads f, SpellOfNoads g) {
    f(this);
    if (!children.empty())
        for (auto y : children)
            y->inorderBeforeAfter(f, g);

    g(this);
}

// - debug here if it's crashing while performing the skoar
// - modifies &here
void SkoarNoad::inorder_from_here(SkoarNoadAddress &here, SpellOfNoads f) {

	if (here.empty())
		inorder(f);
	
	else {
		SkoarInt i = 0;
        SkoarInt j = here.back();
		here.pop_back();
		
		if (!children.empty())
			for (auto child: children) {
                if (i < j) {
                    ++i;
                    continue;
                }

				if (i == j)
					child->inorder_from_here(here, f);
				else 
					child->inorder(f);
			
				++i;
			}
		
	}
}

SkoarpusclePtr SkoarNoad::next_skoarpuscle() {
	
	if (skoarpuscle != nullptr) 
		return skoarpuscle;

	if (children.empty())
		return nullptr;

	for (auto child : children) {
		auto x = child->next_skoarpuscle();
		if (x != nullptr) {
			return x;
		}
	}

	return nullptr;

}

SkoarToke* SkoarNoad::next_toke() {
	if (toke != nullptr)
		return toke.get();

	if (children.empty())
		return nullptr;

	return children.front()->next_toke();
}

// -------------------
// performing the tree
// -------------------
void SkoarNoad::enter_noad(SkoarMinstrelPtr minstrel) {
	if (on_enter) {
		on_enter(minstrel);
	}

    if (skoarpuscle != nullptr) {
        skoarpuscle->on_enter(minstrel);
    }
}

void SkoarNoad::evaluate(SkoarMinstrelPtr minstrel) {
    inorder([=](SkoarNoad* x) {
        x->enter_noad(minstrel); 
    });
}

// ------------------
// searching the tree
// ------------------

list<SkoarNoadPtr> SkoarNoad::collect(SkoarNoadPtr p, list<ESkoarNoad::Kind>& desires) {
    list<SkoarNoadPtr> results;

    SkoarNoad::depth_visit(p, [&](SkoarNoadPtr x) {
        SkoarNoad::match(x, desires, [&](SkoarNoadPtr y) {
            results.push_back(y);
        });
    });

    return results;
}

list<SkoarNoadPtr> SkoarNoad::collect(SkoarNoadPtr p, list<ESkoarToke::Kind>& desires) {
    list<SkoarNoadPtr> results;
    
    SkoarNoad::depth_visit(p, [&](SkoarNoadPtr x) {
        SkoarNoad::match(x, desires, [&](SkoarNoadPtr y) {
            results.push_back(y);
        });
    });

    return results;
}

void SkoarNoad::match(SkoarNoadPtr p, list<ESkoarNoad::Kind>& desires, SpellOfNoadPtrs writer) {
    for (auto x : desires)
        if (p->kind == x)
            writer(p);
}

void SkoarNoad::match(SkoarNoadPtr p, list<ESkoarToke::Kind>& desires, SpellOfNoadPtrs writer) {
    for (auto x : desires)
        if (p->kind == x)
            writer(p);
}

ListOfSkoarpusclesPtr SkoarNoad::collect_skoarpuscles(int j) {
    ListOfSkoarpusclesPtr results = make_shared<ListOfSkoarpuscles>();

    if (j == 0) {
        if (skoarpuscle != nullptr)
            results->push_back(skoarpuscle);
    }

    auto child = children.cbegin();
    for (int i = 0; i < j; ++i)
        ++child;

    while (j++ < children.size()) {
        (*(child++))->inorder([=](SkoarNoad *noad) {
            if (noad->skoarpuscle != nullptr)
                results->push_back(noad->skoarpuscle);
        });
    }
    return results;
}



