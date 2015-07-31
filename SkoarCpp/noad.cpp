#pragma once
#include "skoarcery.hpp"

#include "lex.hpp"
#include "event.hpp"
#include "skoarpuscle.hpp"
#include "toker.hpp"
#include "noad.hpp"

// ==========================
// The Parse Tree - SkoarNoad
// ==========================
SkoarNoad::SkoarNoad(string &nameArg, SkoarNoad *parentArg) {
	parent = parentArg;
	name = nameArg;
}

string SkoarNoad::asString() {
	return name;
}

// -------------------
// decorating the tree
// -------------------
void SkoarNoad::decorate_zero(string *v, void *s, list<int> &parent_address, int i) {

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
	for (SkoarNoad *y : children) {
		y->decorate(v, s, address, i);
		++i;
	}

}

void SkoarNoad::decorate(string *v, void *s, list<int> &parent_address, int i) {

	if (voice == nullptr) {
		voice = v;
	}
	else {
		// the voice has changed, this is what the children get
		v = voice;
	}

	address.emplace_back(i);
	address.splice(address.end(), parent_address);
	skoap = s;

	i = 0;
	for (SkoarNoad *y : children) {
		y->decorate(v, s, address, i);
		i = i + 1;
	}

}

// ----------------
// growing the tree
// ----------------
void SkoarNoad::add_noad(SkoarNoad *noad) {
	children.emplace_back(noad);
}

void SkoarNoad::add_toke(string name, SkoarToke *t) {
	auto x = new SkoarNoad(string(typeid(t).name()), this);
	x->toke = t;
	children.emplace_back(x);
}

// ----------------
// showing the tree
// ----------------
string SkoarNoad::draw_tree(int tab)	{
	int n = 16;
	string s = "";
	//string sa = skoap->asString() + ":";
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

// depth-first, find the leaves, run handler, working towards trunk
//
// if it's crashing during the decorating stage, here's a good place to
// start debugging
void SkoarNoad::depth_visit(function<void(SkoarNoad *noad)> f) {
	//var s = " " ++ if (toke.notNil) {toke.lexeme} {""};
	//debug(">>> depth_visit: " ++ name ++ s);

	for (auto y: children) {
		y->depth_visit(f);
	}

	//debug("--- depth_visit: " ++ name ++ s);

	// note: leaves first
	f(this);

	//debug("<<< depth_visit: " ++ name ++ s);

}

void SkoarNoad::inorder(function<void(SkoarNoad *noad)> f) {

	f(this);

	for (auto y : children) {
		y->inorder(f);
	};

	//debug("<<< inorder: " ++ name);
}

// debug here if it's crashing while performing the skoar
void SkoarNoad::inorder_from_here(list<int> here, function<void(SkoarNoad *noad)> f) {
	

	//debug("inorder_from_here: j:" ++ j ++ " " ++ name);

	if (here.empty()) {
		inorder(f);
	} 
	else {
		int i = 0;
		int j = here.back();
		here.pop_back();
		
		for (auto child = children.begin(); child != children.end(); ++i, ++child) {
			if (i < j) 
				continue;

			if (i == j)
				(*child)->inorder_from_here(here, f);
			else 
				(*child)->inorder(f);

		}
		
	}
}

// expect skoarpuscle
Skoarpuscle *SkoarNoad::next_skoarpuscle() {
	
	if (skoarpuscle != nullptr) 
		return skoarpuscle;

	if (children.empty())
		return nullptr;

	return children.front()->next_skoarpuscle();

}

SkoarToke *SkoarNoad::next_toke() {
	if (toke != nullptr)
		return toke;

	if (children.empty())
		return nullptr;

	return children.front()->next_toke();
}

// -------------------
// performing the tree
// -------------------
void SkoarNoad::enter_noad(SkoarMinstrel* minstrel) {
	if (on_enter != nullptr) {
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



