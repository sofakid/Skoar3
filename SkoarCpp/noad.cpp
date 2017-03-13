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

SkoarNoad::SkoarNoad(wstring &nameArg, SkoarNoadPtr parentArg, const ESkoarNoad::Kind kindArg, const SkoarStyles::EStyle styleArg) :
    parent(parentArg),
    name(nameArg),
    skoarce(nullptr),
    kind(kindArg),
    style(styleArg)
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


SkoarNoad::~SkoarNoad() {
    --SkoarMemories.Noads;

    parent = nullptr;
    skoarce = nullptr;
    toke = nullptr;
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

void SkoarNoad::scry(SpellOfScrying f) {

	this->depth_visit([f](SkoarNoad* noad){
		


	});

}

// -----------------
// climbing the Tree
// -----------------

// depth-first, find the leaves, run handler, working towards trunk
//
// if it's crashing during the decorating stage, here's a good place to
// start debugging
void SkoarNoad::depth_visit(SpellOfNoads f) {
	//var s = " " ++ if (toke.notNil) {toke.lexeme} {""};
	//debug(">>> depth_visit: " ++ name ++ s);

	if (!children.empty())
		for (auto y: children)
			y->depth_visit(f);

	//debug("--- depth_visit: " ++ name ++ s);

	// note: leaves first
	f(this);

	//debug("<<< depth_visit: " ++ name ++ s);

}

void SkoarNoad::inorder(SpellOfNoads f) {

	f(this);

	if (!children.empty())
		for (auto y : children)
			y->inorder(f);
	
	//debug("<<< inorder: " ++ name);
}

void SkoarNoad::inorderBeforeAfter(SpellOfNoads f, SpellOfNoads g) {

    f(this);

    if (!children.empty())
        for (auto y : children)
            y->inorderBeforeAfter(f, g);

    g(this);


    //debug("<<< inorder: " ++ name);
}

// - debug here if it's crashing while performing the skoar
// - modifies &here
void SkoarNoad::inorder_from_here(list<int> &here, SpellOfNoads f) {
	//debug("inorder_from_here: j:" ++ j ++ " " ++ name);

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

// expect skoarpuscle
Skoarpuscle *SkoarNoad::next_skoarpuscle() {
	
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

SkoarToke *SkoarNoad::next_toke() {
	if (toke != nullptr)
		return toke.get();

	if (children.empty())
		return nullptr;

	return children.front()->next_toke();
}

// -------------------
// performing the tree
// -------------------
void SkoarNoad::enter_noad(SkoarMinstrel* minstrel) {
	if (on_enter) {
		on_enter(minstrel);
	}
}

/*
// ------------------
// searching the tree
// ------------------

// desires - array of names of noads as symbol, or SkoarToke implementation classes
// writer - a function that will do something with the matches
match{
| desires, writer |

desires.do {
| item |

if (item == name) {
writer.(this);
};
};
}

collect{
| desires |

var results = List.new;

this.depth_visit({
| x |
x.match(desires, {
| y |
results.add(y);
});
});

^results.asArray;
}

collect_skoarpuscles{
| j = 0 |

var results = List.new;
while {j < children.size} {

children[j].inorder({
| x |
if (x.skoarpuscle.notNil) {
//debug("found skoarpuscle: " ++ x.skoarpuscle.asString);
results.add(x.skoarpuscle);
};
});

j = j + 1;
};
^results.asArray;

}
*/



