#include "skoarcery.hpp"
#include "koar.hpp"

#include "skoar.hpp"
#include "event.hpp"
#include "minstrel.hpp"
#include "skoarpion.hpp"
#include "all_skoarpuscles.hpp"
#include "fairy.hpp" 

#include "noad.hpp"

SkoarKoar::SkoarKoar(Skoar *skoar, const SkoarString &name) :
    skoar(skoar),
    name(name),
    skoarboard(make_shared<SkoarDic>())
{
    (*skoarboard)[L"voice"] = make_skoarpuscle(name);
	stack.push_back(skoarboard);
}

SkoarKoar::~SkoarKoar() {
    
    skoarboard = nullptr;
    stack.clear();
    state_stack.clear();
    skoar = nullptr;
}

// ---------------------
// State and scope stuff
// ---------------------
void SkoarKoar::put(SkoarString k, SkoarpusclePtr v) {
	(*(stack.back()))[k] = v;
}

SkoarpusclePtr SkoarKoar::at(SkoarString &k) {
	SkoarpusclePtr out = nullptr;

	for (auto rev_it = stack.rbegin(); rev_it != stack.rend(); rev_it++) {
		out = (**rev_it)[k];
		if (out != nullptr) {
			return out;
		}
	}

	return out;
}

void SkoarKoar::state_put(SkoarString &k, SkoarpusclePtr v) {
	(*(state_stack.back()))[k] = v;
}

SkoarpusclePtr SkoarKoar::state_at(SkoarString &k) {
	SkoarpusclePtr out = nullptr;

	for (auto rev_it = stack.rbegin(); rev_it != stack.rend(); rev_it++) {
		out = (**rev_it)[k];
		if (out != nullptr) {
			return out;
		}
	}

	return out;
}

SkoarEventPtr SkoarKoar::event(SkoarMinstrelPtr minstrel) {
	auto e = make_shared<SkoarEvent>();
	
	// going from global to local, overwriting existing entries with the more local one. 
	for (auto skrb : stack) {
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
    SkoarpusclePtr args_spec,
    SkoarpusclePtr args_prov)
{
	size_t i = 0, n = 0;
	auto vars = *(stack.back());

    SkoarpuscleArgList *args_list;
    if (is_skoarpuscle<SkoarpuscleArgList>(args_spec)) {
        args_list = skoarpuscle_ptr<SkoarpuscleArgList>(args_spec);
    }
    else
        return;

    ListOfSkoarpusclesPtr args_provided;
    if (is_skoarpuscle<SkoarpuscleList>(args_prov)) {
        args_provided = skoarpuscle_ptr<SkoarpuscleList>(args_prov)->val;
    }
    else {
        args_provided = make_shared<ListOfSkoarpuscles>();
        auto n = args_list->args_names.size();
        for (int i = 0; i < n; ++i) {
            args_provided->push_back(make_skoarpuscle(nullptr));
        }
    }

    minstrel->fairy->push_noating();
    auto provided_iter = args_provided->cbegin();
    for (auto arg_name : args_list->args_names) {
        auto x = (*(provided_iter++));

        if (is_skoarpuscle<SkoarpuscleCat>(x)) {
            // not found, use default
            auto y = args_list->args_dict[arg_name];

            // if (is_skoarpuscle<SkoarpuscleExpr>(y)) {
            //    flatten(y)
            // }

            vars[arg_name] = y;
        }
        else if (is_skoarpuscle<SkoarpusclePair>(x)) {
            auto pair = skoarpuscle_ptr<SkoarpusclePair>(x);
            vars[pair->val.first] = pair->val.second;
        }
        else {
            vars[arg_name] = x;
        }
    }

    minstrel->fairy->pop_noating();
}

void SkoarKoar::push_state() {
	
	auto state = make_shared<SkoarDic>();
	auto projections = make_shared<ListOfSkoarpionProjections>();

	state_stack.push_back(state);

	(*state)[L"colons_burned"] = make_shared<SkoarpuscleList>();
	(*state)[L"al_fine"]       = make_skoarpuscle(false);
	(*state)[L"projections"]   = make_shared<SkoarpuscleProjections>(projections);

	stack.push_back(make_shared<SkoarDic>());
	
}

void SkoarKoar::pop_state() {
	stack.pop_back();
	state_stack.pop_back();
}

void SkoarKoar::do_skoarpion(
	SkoarpionPtr skoarpion,
	SkoarMinstrelPtr minstrel,
	list<SkoarString> &msg_arr,
	SkoarpusclePtr args_provided) {
	
	SkoarNoadPtr subtree;
	SkoarpionProjectionPtr projection = nullptr;
	map<SkoarString, SkoarpionProjectionPtr> projections;
	SkoarString msg_name;
	bool inlined;

	// default behaviour (when unmessaged)
	if (msg_arr.empty()) {
		msg_arr.push_back(L"block");
	}

	msg_name = msg_arr.front();

	inlined = (msg_name == L"inline");
	if (inlined == false) {
		push_state();
        minstrel->fairy->push_times_seen();
	}

	// load arg values into their names
	set_args(minstrel, skoarpion->arg_list, args_provided);

	//projections = state_at(wstring(L"projections"));
	if (skoarpion->name.size() > 0) {
		projection = projections[skoarpion->name];

		// start a new one if we haven't seen it
		if (projection == nullptr) {
			projection = Skoarpion::projection(skoarpion, name);
			projections[skoarpion->name] = projection;
		}
	} 
	else {
		projection = Skoarpion::projection(skoarpion, name);
	}

	subtree = projection->proj;

	this->nav_loop(subtree, projection, minstrel, inlined);

	if (inlined == false) {
		pop_state();
        minstrel->fairy->pop_times_seen();
	}
}

void SkoarKoar::nav_loop(
	SkoarNoadPtr dst,
	SkoarpionProjectionPtr projection,
	SkoarMinstrelPtr minstrel,
	bool inlined) {

	auto running = true;
	auto subtree = dst;

	while (running) {
		try {
			// map dst to an address relative to the projection
			auto here = projection->map_dst(dst);

			subtree->inorder_from_here(
				here,
				[&](SkoarNoad* x) {
				    x->enter_noad(minstrel);
			    }
            );

			throw SkoarNav(SkoarNav::DONE);
		}
		catch (SkoarNav &nav_result) {
			switch (nav_result.code) {

			case SkoarNav::DONE:
				running = false;
				break;

			case SkoarNav::CODA:
				break;

			case SkoarNav::DA_CAPO:
				bubble_up_nav(nav_result, inlined);
				break;

			case SkoarNav::SEGNO:
				/*dst = state_at(L"segno_seen");

				if ((dst !? (_->skoap)) != subtree->skoap) {
					bubble_up_nav(nav_result, inlined);
				};*/
				break;

			case SkoarNav::COLON:
				//dst = state_at(L"colon_seen");

				//if ((dst !? (_->skoap)) != subtree->skoap) {
				//   bubble_up_nav(nav_result, inlined);
				//};
				break;

			case SkoarNav::FINE:
				bubble_up_nav(nav_result, inlined);
				break;
			};

		}
	}
}

void SkoarKoar::bubble_up_nav(SkoarNav &nav, bool inlined) {
	
	// the nav throw will abort do_skoarpion,
	// we have to clean up here.
	if (inlined == false) {
		pop_state();
	}

	throw nav;
	
}

SkoarNav::SkoarNav(ECode code) {
	this->code = code;
}