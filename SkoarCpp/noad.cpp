#pragma once
#include "skoarcery.hpp"

#include "lex.hpp"
#include "event.hpp"
#include "skoarpuscle.hpp"
#include "toker.hpp"
#include "noad.hpp"
#include "styles.hpp"

#include "memories.hpp"

// ==========================
// The Parse Tree - SkoarNoad
// ==========================

SkoarNoad::SkoarNoad(SkoarString &nameArg, SkoarNoadPtr parentArg, const ESkoarNoad::Kind kindArg, const SkoarStyles::EStyle styleArg) :
    parent(parentArg),
    name(nameArg),
    skoarce(nullptr),
    kind(kindArg),
    style(styleArg),
    voice(nullptr),
    skoarpuscle(nullptr)
{
    ++SkoarMemories.Noads;
}

SkoarNoadPtr SkoarNoad::New(wstring &nameArg, SkoarNoadPtr parentArg, SkoarTokePtr toke)
{
    SkoarNoadPtr x = std::make_shared<SkoarNoad>(nameArg, parentArg, ESkoarNoad::toke, toke->style);
    x->skoarce = &toke->lexeme;
    x->size = toke->size;
    x->toke = std::move(toke);

    return x;
}

SkoarNoadPtr SkoarNoad::NewArtificial(SkoarString &nameArg, SkoarNoadPtr parentArg)
{
    return SkoarNoad::New<ESkoarNoad::artificial>(nameArg, parentArg);
}


SkoarNoadPtr SkoarNoad::NewArtificial(const wchar_t *nameArg, SkoarNoadPtr parentArg)
{
    return SkoarNoad::New<ESkoarNoad::artificial>(SkoarString(nameArg), parentArg);
}


SkoarNoad::~SkoarNoad() {
    --SkoarMemories.Noads;

    parent = nullptr;
    skoarce = nullptr;
    toke = nullptr;
    voice = nullptr;
    skoarpuscle = nullptr;
    size = 0;
    offs = 0;
    children.clear();
}

void SkoarNoad::clear() {
    // visit the noads depth-first, clear children and unset all shared_ptrs. 
    // should then trigger destruction.
    depth_visit([](SkoarNoad *noad) {
        noad->children.clear();
        noad->parent = nullptr;
    });
}

wstring *SkoarNoad::asString() {
    if (skoarce == nullptr)
        return new wstring(name + L": nullptr");

	return new wstring(name + L": " + *skoarce);
}

// -------------------
// decorating the tree
// -------------------
void SkoarNoad::decorate_zero(wstring *v, void *s, list<int> &parent_address, int i) {

	if (voice == nullptr) {
		voice = v;

	}
	else {
		// the voice has changed, this is what the children get
		v = voice;
	}

	address.clear();
	skoap = s;

	i = 0;
	for (auto y : children) {
		y->decorate(v, s, address, i);
		++i;
	}

}

void SkoarNoad::decorate(wstring *v, void *s, list<int> &parent_address, int i) {

	if (voice == nullptr) {
		voice = v;
	}
	else {
		// the voice has changed, this is what the children get
		v = voice;
	}

	address.push_back(i);
	address.splice(address.end(), parent_address);
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
	int n = 16;

	wstring s = wstring(tab * 2, L' ');

	//delete tabs;

	if (voice != nullptr) {
		s += *voice + L":";
	}
	else {
		s += L" novoice :";
	}

	if (skoarpuscle != nullptr) {
		s += skoarpuscle->asString() + L" - ";
	}
	s += name;// +L" __{ " + skoarce + L" }__";

	//s += L"\n";
	
	log->d(s);

	for (auto x : children) {
		x->log_tree(log, tab + 1);
	}

}

wstring SkoarNoad::draw_tree(int tab)	{
	int n = 16;
	
	wstring s = wstring(tab * 2, L' ');
	
	//delete tabs;

	if (voice != nullptr) {
		s += *voice + L":";
	}
	else {
		s += L" novoice :";
	}

	if (skoarpuscle != nullptr) {
		s += skoarpuscle->asString() + L" - ";
	}
	s += name;// +L" __{ " + skoarce + L" }__";

	s += L"\n";

	for (auto x : children) {
		s += x->draw_tree(tab + 1);
	}

	return s;

	//wstring sa = skoap->asString() + ":";
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
	return s;
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
void SkoarNoad::inorder_from_here(list<int> &here, SpellOfNoads f) {

	if (here.empty())
		inorder(f);
	
	else {
		int i = 0;
		int j = here.back();
		here.pop_back();
		
		if (!children.empty())
			for (auto child: children) {
				if (i < j)
					++i;
					continue;

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

    auto child = children.cbegin();
    for (int i = 0; i < j; ++i)
        ++child;

    while (j++ < children.size()) {
        (*child)->inorder([=](SkoarNoad *noad) {
            if (noad->skoarpuscle != nullptr)
                results->push_back(noad->skoarpuscle);
        });
    }
    return results;
}



