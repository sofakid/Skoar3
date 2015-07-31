#include "skoarcery.hpp"
#include "koar.hpp"

#include "skoar.hpp"
#include "event.hpp"
#include "minstrel.hpp"
#include "skoarpion.hpp"
#include "skoarpuscle.hpp"
#include "noad.hpp"


SkoarKoar::SkoarKoar(string *nom) {
	name = nom;
	stack->emplace_back(skoarboard);
}

// ---------------------
// State and scope stuff
// ---------------------
void SkoarKoar::put(string *k, Skoarpuscle *v) {
	top_args()[*k] = v;
}

Skoarpuscle *SkoarKoar::at(string *k) {
	Skoarpuscle *out = nullptr;

	for (auto skrb = stack->rbegin();skrb != stack->rend();skrb++) {
		out = (**skrb)[*k];
		if (out != nullptr) {
			return out;
		}
	}

	return out;
}

void SkoarKoar::state_put(string *k, Skoarpuscle *v) {
	(*state_stack->back())[*k] = v;
}

Skoarpuscle *SkoarKoar::state_at(string *k) {
	Skoarpuscle *out = nullptr;

	for (auto skrb = stack->rbegin(); skrb != stack->rend(); skrb++) {
		out = (**skrb)[*k];
		if (out != nullptr) {
			return out;
		}
	}

	return out;
}

// constructs the event that will be played by SC
SkoarEvent *SkoarKoar::event(SkoarMinstrel *minstrel) {
	auto e = new SkoarEvent();
	/*
	for (auto skrb : stack) {
		// native function constructs the event quickly
		e = skrb.transformEvent(e);

		// but we need to change stuff
		e.keysValuesChange{
			| key, value |

			case {value.isKindOf(SkoarpuscleSkoarpion)} {
				// we don't need to pass skoarpions to SC
				nil

			} {value.isKindOf(Skoarpuscle)} {
					// we want values, not skoarpuscles
					value.flatten(minstrel)

				} {
					// perfect
					value
				}
		};
	}

	return e; */
}

void SkoarKoar::set_args(SkoarMinstrel *minstrel, void *args_spec, void *args) {
	/*auto i = 0;
	auto vars = stack[stack.size - 1];

	if (args_spec.isKindOf(SkoarpuscleArgsSpec)) {
		var passed_args, n;

		passed_args = if (args.isNil) { [] } { args };
		n = passed_args.size;

		// foreach arg name defined, set the value from args
		args_spec.val.do {
			| k |
				//("k: " ++ k).postln;
				vars[k] = if (i < n) {
				args[i]
			} {
				// this defaults to passing 0 when not enough args are sent.
				SkoarpuscleInt(0)
			};
			i = i + 1;
		};
	};*/
}

void *SkoarKoar::top_args() {
	return stack[stack->size - 1];
}

void SkoarKoar::push_state() {
	/*
	var state = IdentityDictionary.new;
	var projections = IdentityDictionary.new;

	state_stack = state_stack.add(state);

	state[\colons_burned] = Dictionary.new;
	state[\al_fine] = false;
	state[\projections] = projections;

	stack = stack.add(IdentityDictionary.new);
	*/
}

void SkoarKoar::pop_state() {
	stack->pop_back();
	state_stack->pop_back();
}

void SkoarKoar::do_skoarpion(
	Skoarpion *skoarpion,
	SkoarMinstrel *minstrel,
	list<string> *msg_arr,
	void *args) {
	
	SkoarNoad *subtree;
	SkoarProjection *projection;
	list<SkoarProjection*> projections;
	string msg_name;
	bool inlined;

	// default behaviour (when unmessaged)
	if (msg_arr == nullptr) {
		msg_arr = new list<string>({"block"});
	};

	msg_name = msg_arr->front();

	inlined = (msg_name == "inline");
	if (inlined == false) {
		this->push_state();
	}

	// load arg values into their names
	set_args(minstrel, skoarpion->args_spec, args);

	projections = state_at("projections");
	if (skoarpion->name != nullptr) {
		projection = projections[skoarpion->name];

		// start a new one if we haven't seen it
		if (projection == nullptr) {
			projection = skoarpion->projection(name);
			projections[skoarpion->name] = projection;
		};
	} {
		projection = skoarpion->projection;
	};

	subtree = projection->performMsg(msg_arr);

	this->nav_loop(subtree, projection, minstrel, inlined);

	if (inlined == false) {
		this->pop_state();
	}
}

void SkoarKoar::nav_loop(
	SkoarNoad *dst,
	SkoarProjection *projection,
	SkoarMinstrel *minstrel,
	bool inlined) {

	auto running = true;
	auto subtree = dst;

	while (running) {
		try {

			// map dst to an address relative to the projection
			auto here = projection->map_dst(dst);

			subtree->inorder_from_here(
				here,
				[&](SkoarNoad *x) {
					x->enter_noad(minstrel); 
				});

			// our metaphorical throws look like this,
			// you'll also find them in the navigational
			// skoarpuscles' on_enters. (segno, bars, etc..)
			throw new SkoarNav(SkoarNav::DONE);
		}
		catch (SkoarNav *nav_result) {
			switch (nav_result->code) {
			
			case SkoarNav::DONE:
				running = false;
				break;

			case SkoarNav::CODA:
				break;

			case SkoarNav::DA_CAPO:
				this->bubble_up_nav(nav_result, inlined);
				break;

			case SkoarNav::SEGNO:
				dst = this->state_at(\segno_seen);

				if ((dst !? (_->skoap)) != subtree->skoap) {
					this->bubble_up_nav(nav_result, inlined);
				};
				break;

			case SkoarNav::COLON:
				dst = this->state_at(\colon_seen);

				if ((dst !? (_->skoap)) != subtree->skoap) {
					this->bubble_up_nav(nav_result, inlined);
				};
				break;

			case SkoarNav::FINE:
				this->bubble_up_nav(nav_result, inlined);
				break;
			};

			delete nav_result;
		}
		
}

void SkoarKoar::bubble_up_nav(SkoarNav *nav, bool inlined) {
	
	// the nav throw will abort do_skoarpion,
	// we have to clean up here.
	if (inlined == false) {
		this->pop_state();
	}

	throw nav;
	
}

SkoarNav::SkoarNav(ECode code) {
	this->code = code;
}