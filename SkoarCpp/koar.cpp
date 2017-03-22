#include "skoarcery.hpp"
#include "koar.hpp"

#include "skoar.hpp"
#include "event.hpp"
#include "minstrel.hpp"
#include "skoarpion.hpp"
#include "all_skoarpuscles.hpp"

#include "noad.hpp"

SkoarKoar::SkoarKoar(SkoarString &nom) {
	name = nom;
	stack = make_unique<ListOfSkoarDics>();
	skoarboard = make_shared<SkoarDic>();
	stack->push_back(skoarboard);
}

// ---------------------
// State and scope stuff
// ---------------------
void SkoarKoar::put(SkoarString k, SkoarpusclePtr v) {
	(*stack->back())[k] = v;
}

SkoarpusclePtr SkoarKoar::at(SkoarString &k) {
	SkoarpusclePtr out = nullptr;

	for (auto skrb = stack->rbegin(); skrb != stack->rend(); skrb++) {
		out = (**skrb)[k];
		if (out != nullptr) {
			return out;
		}
	}

	return out;
}

void SkoarKoar::state_put(SkoarString &k, SkoarpusclePtr v) {
	(*state_stack->back())[k] = v;
}

SkoarpusclePtr SkoarKoar::state_at(SkoarString &k) {
	SkoarpusclePtr out = nullptr;

	for (auto skrb = stack->rbegin(); skrb != stack->rend(); skrb++) {
		out = (**skrb)[k];
		if (out != nullptr) {
			return out;
		}
	}

	return out;
}

// constructs the event that will be played by SC
SkoarEvent *SkoarKoar::event(SkoarMinstrelPtr minstrel) {
	auto e = new SkoarEvent();
	
	// going from global to local, overwriting existing entries with the more local one. 
	for (auto skrb : *stack) {
		// native function constructs the event quickly
		e->from(skrb);

		/*// but we need to change stuff
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
		};*/
	}

	return e; 
}

void SkoarKoar::set_args(
	SkoarMinstrelPtr minstrel, 
    shared_ptr<SkoarpuscleList> args_spec,
	ListOfSkoarpusclesPtr args) 
{
	size_t i = 0, n = 0;
	auto vars = *stack->back();

	if (args == nullptr)
		n = 0;
	else
		n = args->size();

		// foreach arg name defined, set the value from args
		auto arg_it = args->begin();

        auto args_spec_val = args_spec->val;
		for (auto k_skoarpuscle : *args_spec_val) {
            auto k = skoarpuscle_ptr<SkoarpuscleSymbolName>(k_skoarpuscle)->val;
            
			//("k: " ++ k).postln;
			if (i++ < n) {
				vars[k] = *(arg_it++);
			} else {
				// this defaults to passing 0 when not enough args are sent.
				vars[k] = make_shared<SkoarpuscleInt>(0);
			}
		}
}


void SkoarKoar::push_state() {
	
	auto state = make_shared<SkoarDic>();
	auto projections = make_shared<ListOfSkoarProjections>();

	state_stack->push_back(state);

	//(*state)[&wstring(L"colons_burned")] = new SkoarpuscleList(new list<SkoarNoad *>());
	//(*state)[&wstring(L"al_fine")] = new SkoarpuscleFalse();
	//(*state)[&wstring(L"projections")] = new SkoarpuscleProjections(projections);

	stack->push_back(make_shared<SkoarDic>());
	
}

void SkoarKoar::pop_state() {
	stack->pop_back();
	state_stack->pop_back();
}

void SkoarKoar::do_skoarpion(
	SkoarpionPtr skoarpion,
	SkoarMinstrelPtr minstrel,
	list<SkoarString> &msg_arr,
	ListOfSkoarpusclesPtr args) {
	
	SkoarNoadPtr subtree;
	SkoarProjectionPtr projection = nullptr;
	map<SkoarString, shared_ptr<SkoarpuscleProjection>> projections;
	SkoarString msg_name;
	bool inlined;

	// default behaviour (when unmessaged)
	if (msg_arr.empty()) {
		//msg_arr.emplace_back(wstring(L"block"));
	}

	msg_name = msg_arr.front();

	inlined = (msg_name == SkoarString(L"inline"));
	if (inlined == false) {
		this->push_state();
	}

	// load arg values into their names
	set_args(minstrel, skoarpion->args_spec, args);

	//projections = state_at(wstring(L"projections"));
	if (skoarpion->name.size() > 0) {
		//projection = projections[*skoarpion->name];

		// start a new one if we haven't seen it
		if (projection == nullptr) {
			projection = skoarpion->projection(name);
			//projections[*skoarpion->name] = projection;
		}
	} 
	else {
		//projection = skoarpion->projection;
	}

	subtree = projection->performMsg(msg_arr);

	this->nav_loop(subtree, projection, minstrel, inlined);

	if (inlined == false) {
		this->pop_state();
	}
}

void SkoarKoar::nav_loop(
	SkoarNoadPtr dst,
	SkoarProjectionPtr projection,
	SkoarMinstrelPtr minstrel,
	bool inlined) {

	auto running = true;
	auto subtree = dst;

	while (running) {
		try {
			// map dst to an address relative to the projection
			auto here = projection->map_dst(dst);

			subtree->inorder_from_here(
				*here,
				[&](SkoarNoad* x) {
				x->enter_noad(minstrel);
			});

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
				/*dst = this->state_at(L"segno_seen");

				if ((dst !? (_->skoap)) != subtree->skoap) {
					this->bubble_up_nav(nav_result, inlined);
				};*/
				break;

			case SkoarNav::COLON:
				//dst = this->state_at(L"colon_seen");

				//if ((dst !? (_->skoap)) != subtree->skoap) {
				this->bubble_up_nav(nav_result, inlined);
				//};
				break;

			case SkoarNav::FINE:
				this->bubble_up_nav(nav_result, inlined);
				break;
			};

			delete nav_result;
		}
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