#include "decorating.hpp"

#include "lex.hpp"
#include "noad.hpp"
#include "skoarpuscle.hpp"
#include "skoarpion.hpp"
#include "fairy.hpp"
#include "event.hpp"
#include "skoar.hpp"
#include "minstrel.hpp"
#include "beaty.hpp"
#include "skoarpion_skoarpuscle.hpp"
#include "dsp.hpp"
#include "lute.hpp"
#include "meditation.hpp"

// ==============
// toke_inspector
// ==============
//
// Here we pick the values out of the tokens
// and set its attributes appropriately
SkoarTokeInspector::SkoarTokeInspector() {

}

void SkoarTokeInspector::decorate(SkoarToke *, SkoarNoadPtr)	{
	;
};

void SkoarTokeInspector::decorate(Toke_Fairy *toke, SkoarNoadPtr noad)	{
	noad->skoarpuscle = new SkoarpuscleFairy();
    noad->toke = nullptr;
};

void SkoarTokeInspector::decorate(Toke_Cat *toke, SkoarNoadPtr noad) {
    noad->skoarpuscle = new SkoarpuscleCat();
    noad->toke = nullptr;
};

void SkoarTokeInspector::decorate(Toke_True *toke, SkoarNoadPtr noad) {
    noad->skoarpuscle = new SkoarpuscleTrue();
    noad->toke = nullptr;
}

void SkoarTokeInspector::decorate(Toke_False *toke, SkoarNoadPtr noad) {
    noad->skoarpuscle = new SkoarpuscleFalse();
    noad->toke = nullptr;
}


// -----------------------------------------------------------------
void SkoarTokeInspector::decorate(Toke_Freq *toke, SkoarNoadPtr noad) {
	noad->skoarpuscle = new SkoarpuscleFreq(toke->lexeme);
    noad->toke = nullptr;
}

void SkoarTokeInspector::decorate(Toke_Int *toke, SkoarNoadPtr noad) {
	noad->skoarpuscle = new SkoarpuscleInt(stoi(toke->lexeme));
    noad->toke = nullptr;
}

void SkoarTokeInspector::decorate(Toke_Float *toke, SkoarNoadPtr noad) {
	noad->skoarpuscle = new SkoarpuscleFloat(stod(toke->lexeme));
    noad->toke = nullptr;
}


// -----------------------------------------------------------------
void SkoarTokeInspector::decorate(Toke_NamedNoat *toke, SkoarNoadPtr noad) {
	noad->skoarpuscle = new SkoarpuscleNoat(toke->lexeme);
    noad->toke = nullptr;
}

void SkoarTokeInspector::decorate(Toke_Choard *toke, SkoarNoadPtr noad) {
	noad->skoarpuscle = new SkoarpuscleChoard(toke->lexeme);
    noad->toke = nullptr;
}


// -----------------------------------------------------------------
void SkoarTokeInspector::decorate(Toke_String *toke, SkoarNoadPtr noad) {
	noad->skoarpuscle = new SkoarpuscleString(toke->lexeme);
    noad->toke = nullptr;
}

void SkoarTokeInspector::decorate(Toke_Symbol *toke, SkoarNoadPtr noad) {
	noad->skoarpuscle = new SkoarpuscleSymbol(toke->lexeme.substr(1));
    noad->toke = nullptr;
}

void SkoarTokeInspector::decorate(Toke_SymbolName *toke, SkoarNoadPtr noad) {
	noad->skoarpuscle = new SkoarpuscleSymbolName(toke->lexeme);
    noad->toke = nullptr;
}

void SkoarTokeInspector::decorate(Toke_SymbolColon *toke, SkoarNoadPtr noad) {
    noad->skoarpuscle = new SkoarpuscleSymbolColon(toke->lexeme);
    noad->toke = nullptr;
}


// -----------------------------------------------------------------
// rests
// } }} }}}
void SkoarTokeInspector::decorate(Toke_Crotchets *toke, SkoarNoadPtr noad) {
	noad->skoarpuscle = new SkoarpuscleRest(toke);
    noad->toke = nullptr;
}

// o/ oo/ ooo/
void SkoarTokeInspector::decorate(Toke_Quavers *toke, SkoarNoadPtr noad) {
	noad->skoarpuscle = new SkoarpuscleRest(toke);
    noad->toke = nullptr;
}

// unrests
void SkoarTokeInspector::decorate(Toke_Quarters *toke, SkoarNoadPtr noad) {
	noad->skoarpuscle = new SkoarpuscleBeat(toke);
    noad->toke = nullptr;
}

void SkoarTokeInspector::decorate(Toke_Eighths *toke, SkoarNoadPtr noad) {
	noad->skoarpuscle = new SkoarpuscleBeat(toke);
    noad->toke = nullptr;
}

void SkoarTokeInspector::decorate(Toke_ExactBeat *toke, SkoarNoadPtr noad) {
    noad->skoarpuscle = new SkoarpuscleExactBeat(toke);
    noad->toke = nullptr;
}

void SkoarTokeInspector::decorate(Toke_ExactRest *toke, SkoarNoadPtr noad) {
    noad->skoarpuscle = new SkoarpuscleExactRest(toke);
    noad->toke = nullptr;
}

void SkoarTokeInspector::decorate(Toke_Duration *toke, SkoarNoadPtr noad) {
    noad->skoarpuscle = new SkoarpuscleDuration(toke);
    noad->toke = nullptr;
}


// -----------------------------------------------------------------
void SkoarTokeInspector::decorate(Toke_Bars *toke, SkoarNoadPtr noad) {
	noad->skoarpuscle = new SkoarpuscleBars(toke);
    noad->toke = nullptr;
}

void SkoarTokeInspector::decorate(Toke_Carrot *toke, SkoarNoadPtr noad) {
	noad->skoarpuscle = new SkoarpuscleCarrots(toke);
    noad->toke = nullptr;
}

void SkoarTokeInspector::decorate(Toke_Tuplet *toke, SkoarNoadPtr noad) {
	noad->skoarpuscle = new SkoarpuscleTuplet(toke);
    noad->toke = nullptr;
}

void SkoarTokeInspector::decorate(Toke_DynPiano *toke, SkoarNoadPtr noad) {
	noad->skoarpuscle = new SkoarpuscleDynamic(toke);
    noad->toke = nullptr;
}

void SkoarTokeInspector::decorate(Toke_DynForte *toke, SkoarNoadPtr noad) {
	noad->skoarpuscle = new SkoarpuscleDynamic(toke);
    noad->toke = nullptr;
}

void SkoarTokeInspector::decorate(Toke_OctaveShift *toke, SkoarNoadPtr noad) {
	noad->skoarpuscle = new SkoarpuscleOctaveShift(toke);
    noad->toke = nullptr;
}

void SkoarTokeInspector::decorate(Toke_OttavaA *toke, SkoarNoadPtr noad) {
	noad->skoarpuscle = new SkoarpuscleOctaveShift(toke);
    noad->toke = nullptr;
}

void SkoarTokeInspector::decorate(Toke_OttavaB *toke, SkoarNoadPtr noad) {
	noad->skoarpuscle = new SkoarpuscleOctaveShift(toke);
    noad->toke = nullptr;
}

void SkoarTokeInspector::decorate(Toke_QuindicesimaA *toke, SkoarNoadPtr noad) {
	noad->skoarpuscle = new SkoarpuscleOctaveShift(toke);
    noad->toke = nullptr;
}

void SkoarTokeInspector::decorate(Toke_QuindicesimaB *toke, SkoarNoadPtr noad) {
	noad->skoarpuscle = new SkoarpuscleOctaveShift(toke);
    noad->toke = nullptr;
}

void SkoarTokeInspector::decorate(Toke_Segno *toke, SkoarNoadPtr noad) {
    noad->skoarpuscle = new SkoarpuscleSegno(noad, toke);
    noad->toke = nullptr;
}

void SkoarTokeInspector::decorate(Toke_Fine *toke, SkoarNoadPtr noad) {
    noad->skoarpuscle = new SkoarpuscleFine();
    noad->toke = nullptr;
}


// -----------------------------------------------------------------
void SkoarTokeInspector::decorate(Toke_BooleanOp *toke, SkoarNoadPtr noad) {
	noad->skoarpuscle = new SkoarpuscleBooleanOp(noad, toke);
    noad->toke = nullptr;
}

void SkoarTokeInspector::decorate(Toke_Voice *toke, SkoarNoadPtr noad) {
	noad->skoarpuscle = new SkoarpuscleVoice(toke);
    noad->toke = nullptr;
}

void SkoarTokeInspector::decorate(Toke_MsgName *toke, SkoarNoadPtr noad) {
	noad->skoarpuscle = new SkoarpuscleMsgName(toke->lexeme);
    noad->toke = nullptr;
}

void SkoarTokeInspector::decorate(Toke_MsgNameWithArgs *toke, SkoarNoadPtr noad) {
	auto s = toke->lexeme;
	auto n = s.length() - 2;
	noad->skoarpuscle = new SkoarpuscleMsgName(s.substr(0,n));
    noad->toke = nullptr;
}

void SkoarTokeInspector::decorate(Toke_MathOp *toke, SkoarNoadPtr noad) {
	noad->skoarpuscle = new SkoarpuscleMathOp(toke);
    noad->toke = nullptr;
}

void SkoarTokeInspector::decorate(Toke_ListSep *toke, SkoarNoadPtr noad) {
	auto x = new SkoarpuscleListSep();
	noad->skoarpuscle = x;
    noad->toke = nullptr;
}

void SkoarTokeInspector::decorate(Toke_ListE *toke, SkoarNoadPtr noad) {
	auto x = new SkoarpuscleListEnd();
	noad->skoarpuscle = x;
    noad->toke = nullptr;
}


// -----------------------------------------------------------------
void SkoarTokeInspector::decorate(Toke_Times *toke, SkoarNoadPtr noad) {
    noad->skoarpuscle = new SkoarpuscleTimes();
    noad->toke = nullptr;
}

void SkoarTokeInspector::decorate(Toke_HashLevel *toke, SkoarNoadPtr noad) {
    noad->skoarpuscle = new SkoarpuscleHashLevel(toke->lexeme);
    noad->toke = nullptr;
}



// -----------------------------------------------------------------
void SkoarTokeInspector::decorate(Toke_AUGen *toke, SkoarNoadPtr noad) {
    noad->skoarpuscle = new SkoarpuscleUGen(toke->lexeme.substr(1), SkoarpuscleUGen::Type::audio);
    noad->toke = nullptr;
}

void SkoarTokeInspector::decorate(Toke_KUGen *toke, SkoarNoadPtr noad) {
    noad->skoarpuscle = new SkoarpuscleUGen(toke->lexeme.substr(1), SkoarpuscleUGen::Type::control);
    noad->toke = nullptr;
}

void SkoarTokeInspector::decorate(Toke_DUGen *toke, SkoarNoadPtr noad) {
    noad->skoarpuscle = new SkoarpuscleUGen(toke->lexeme.substr(1), SkoarpuscleUGen::Type::demand);
    noad->toke = nullptr;
}

void SkoarTokeInspector::decorate(Toke_AUGenWithArgs *toke, SkoarNoadPtr noad) {
    auto s = toke->lexeme;
    noad->skoarpuscle = new SkoarpuscleUGenWithArgs(s.substr(1, s.size() - 2), SkoarpuscleUGen::Type::audio);
    noad->toke = nullptr;
}

void SkoarTokeInspector::decorate(Toke_KUGenWithArgs *toke, SkoarNoadPtr noad) {
    auto s = toke->lexeme;
    noad->skoarpuscle = new SkoarpuscleUGenWithArgs(s.substr(1, s.size() - 2), SkoarpuscleUGen::Type::control);
    noad->toke = nullptr;
}

void SkoarTokeInspector::decorate(Toke_DUGenWithArgs *toke, SkoarNoadPtr noad) {
    auto s = toke->lexeme;
    noad->skoarpuscle = new SkoarpuscleUGenWithArgs(s.substr(1, s.size() - 2), SkoarpuscleUGen::Type::demand);
    noad->toke = nullptr;
}


// -----------------------------------------------------------------
void SkoarTokeInspector::decorate(Toke_Lute *toke, SkoarNoadPtr noad) {
    noad->skoarpuscle = new SkoarpuscleLute(toke);
    noad->toke = nullptr;
}

void SkoarTokeInspector::decorate(Toke_LuteWithArgs *toke, SkoarNoadPtr noad) {
    noad->skoarpuscle = new SkoarpuscleLute(toke);
    noad->toke = nullptr;
}

// ============
// Skoarmantics
// ============

/*

This code is applied during the decoration stage of compiling the skoar tree.

For stuff to happen during performance of the tree, we set handlers here.

We also shrink the tree, drop some punctuation noads.

We went depth first and run the code on the way back,
so children are processed first.

*/


Skoarmantics::Skoarmantics() {

	table[ESkoarNoad::skoar] = [](Skoar *skoar, SkoarNoadPtr noad) {
		noad->skoarpuscle = new SkoarpuscleSkoarpion(Skoarpion::new_from_skoar(skoar));
		noad->children.clear();
	};

	table[ESkoarNoad::skoarpion] = [](Skoar *skoar, SkoarNoadPtr noad) {
		auto x = new SkoarpuscleSkoarpion(new Skoarpion(skoar, noad));
		noad->skoarpuscle = x;
		noad->children.clear();
	};

    table[ESkoarNoad::meditation] = [](Skoar *skoar, SkoarNoadPtr noad) {
        auto x = new SkoarpuscleMeditation(skoar, noad);
        noad->skoarpuscle = x;
        noad->children.clear();
    };

	table[ESkoarNoad::conditional] = [](Skoar *skoar, SkoarNoadPtr noad) {
		noad->skoarpuscle = new SkoarpuscleConditional(skoar, noad);
		noad->children.empty();
	};

    table[ESkoarNoad::boolean_expr] = [](Skoar *skoar, SkoarNoadPtr noad) {
        /*
        // we insert a node at the end of the boolean expression
        // so we can restore the impression
        var end_noad = SkoarNoad(\boolean_expr_end, noad);
				
		noad.on_enter = {
			| m, nav |
			//("boolean_expr :: push_boolean").postln;
			m.fairy.push_boolean;
		};

		end_noad.on_enter = {
            | m, nav |
			//("boolean_expr :: pop_boolean").postln;
			m.fairy.pop_boolean;
        };

        noad.add_noad(end_noad);
        */
    };

    table[ESkoarNoad::boolean] = [](Skoar *skoar, SkoarNoadPtr noad) {
		noad->skoarpuscle = new SkoarpuscleBoolean(noad);
		/*
        // we insert a node at the end of the expression
        // so we can evaluate the result
        var end_noad = SkoarNoad(\boolean_end, noad);
		var x = SkoarpuscleBoolean(noad);
		noad.skoarpuscle = x;
				
		end_noad.on_enter = {
            | m, nav |
			var l_value = m.fairy.l_value;
            var y;
			var imp = m.fairy.impression;
					
			//("derp " ++ l_value.asString ++ " imp: " ++ imp.asString).postln;
			y = x.evaluate(m, nav, l_value, imp);

			m.fairy.impress(y);
			m.fairy.pop_compare;
        };

        noad.add_noad(end_noad);
        */
	};

    table[ESkoarNoad::regular_beat] = [](Skoar *skoar, SkoarNoadPtr noad) {
		auto xp = noad->next_skoarpuscle();

		if (xp != nullptr) {
			noad->skoarpuscle = xp;
			auto x = *xp;

			noad->on_enter = [&](SkoarMinstrel *m) {
				x.on_enter(m);
			};
		}
		noad->children.empty();
        /*
        var x = noad.next_skoarpuscle;
        noad.skoarpuscle = x;

        if (noad.parent.name != \assignment) {
            noad.on_enter = {
                | m, nav |
				//("REGULAR BEAT :: " ++ x).postln;
                x.on_enter_sometimes(m, nav);
            };
        };
        */
	};

    table[ESkoarNoad::exact_beat] = [](Skoar *skoar, SkoarNoadPtr noad) {
        /*
        var skoarpuscle = noad.next_skoarpuscle;
		var end_noad = SkoarNoad(\exact_beat_end, noad);
		end_noad.on_enter = {
			| m, nav |
			skoarpuscle.after(m, nav);
		};

		noad.add_noad(end_noad);
        */
    };

    table[ESkoarNoad::exact_rest] = [](Skoar *skoar, SkoarNoadPtr noad) {
        /*
        var skoarpuscle = noad.next_skoarpuscle;
		var end_noad = SkoarNoad(\exact_rest_end, noad);
		end_noad.on_enter = {
			| m, nav |
			skoarpuscle.after(m, nav);
		};

		noad.add_noad(end_noad);
				
        */
    };

    table[ESkoarNoad::loop] = [](Skoar *skoar, SkoarNoadPtr noad) {
		noad->skoarpuscle = new SkoarpuscleLoop(skoar, noad);
		noad->children.clear();
	};

    table[ESkoarNoad::musical_keyword_misc] = [](Skoar *skoar, SkoarNoadPtr noad) {
		auto skoarpuscle = noad->next_skoarpuscle();
        noad->children.clear();
	};

    table[ESkoarNoad::cthulhu] = [](Skoar *skoar, SkoarNoadPtr noad) {
		noad->on_enter = [&](SkoarMinstrel *m) {
			skoar->cthulhu(noad);
		};
	};

    table[ESkoarNoad::dal_goto] = [](Skoar *skoar, SkoarNoadPtr noad) {
		noad->skoarpuscle = new SkoarpuscleGoto(noad);
	};

    table[ESkoarNoad::marker] = [](Skoar *skoar, SkoarNoadPtr noad) {
		/*
        var x = noad.next_skoarpuscle;
		noad.skoarpuscle = x;

        if (x.isKindOf(SkoarpuscleBars)) {
            x.noad = noad;
            noad.children = [];
        };
        */
        auto x = noad->next_skoarpuscle();

		if (x != nullptr) {
			auto y = *x;
			noad->on_enter = [&](SkoarMinstrel *m) {
				y.on_enter(m);
			};

			if (typeid(y) == typeid(SkoarpuscleBars)) {
				//y.noad = noad;
				noad->children.empty();
			}
		}
	};

	// deref*         : Deref MsgNameWithArgs listy_suffix
	//                | Deref MsgName
    table[ESkoarNoad::deref] = [](Skoar *skoar, SkoarNoadPtr noad) {
		SkoarpuscleDeref *x;
		SkoarpuscleArgs *args = nullptr;
		SkoarString msg_name(L"");

		if (noad->children.empty() != true) {
			auto child = noad->children.begin();
			child++;
			auto y = (*child)->skoarpuscle;

			if (typeid(y) == typeid(SkoarpuscleMsgName*)) {
                SkoarString val = y->val;
                msg_name = val;
			}
			else if (y == nullptr) {
				skoar->log->e("WTF Skoarpuscle is nullptr.");

			}
			else {
				skoar->log->e("WTF Skoarpuscle: ", y);
			}
		}
		
		if (msg_name.size() == 0) {
			msg_name = SkoarString(L"nomsgname");
		}
		
		if (noad->children.size() > 2) {
			args = new SkoarpuscleArgs();
		}

		x = new SkoarpuscleDeref(msg_name, args);
		noad->skoarpuscle = x;

		// !f<x,y>
		if (args != nullptr) {

			auto end_noad = SkoarNoad::New<ESkoarNoad::artificial>(wstring(L"deref_end"), noad);
			end_noad->on_enter = [&](SkoarMinstrel *m) {
				m->fairy->cast_arcane_magic();
				x->on_enter(m);
			};

			noad->add_noad(end_noad);
			noad->on_enter = [&](SkoarMinstrel *m) {
				args->on_enter(m);
			};
            
			// !f
		} {
			noad->on_enter = [&](SkoarMinstrel *m) {
				x->on_enter(m);
			};
		};

	};

    table[ESkoarNoad::listy] = [](Skoar *skoar, SkoarNoadPtr noad) {
        noad->skoarpuscle = new SkoarpuscleList();
	};

    table[ESkoarNoad::arg_listy] = [](Skoar *skoar, SkoarNoadPtr noad) {
        noad->skoarpuscle = new SkoarpuscleArgList(noad);
    };

    table[ESkoarNoad::arg_expr] = [](Skoar *skoar, SkoarNoadPtr noad) {
        noad->skoarpuscle = new SkoarpuscleArgExpr();
        noad->children.clear();
    };

    table[ESkoarNoad::skrp_sig] = [](Skoar *skoar, SkoarNoadPtr noad) {
        noad->skoarpuscle = new SkoarpuscleSkoarpionSig();
    };

    table[ESkoarNoad::msg] = [](Skoar *skoar, SkoarNoadPtr noad) {
		Skoarpuscle *msg = noad->next_skoarpuscle();

		if (msg != nullptr) {
			if (typeid(msg) == typeid(SkoarpuscleList*)) {
				// i'm not sure what i want this to mean

			}
			else if (typeid(msg) == typeid(SkoarpuscleLoop*)) {
                SkoarString val = msg->val;
                noad->skoarpuscle = new SkoarpuscleLoopMsg(val);
			}
			else if (typeid(msg) == typeid(SkoarpuscleMsgName*)) {
				SkoarpuscleArgs *args = new SkoarpuscleArgs();
                SkoarString val = msg->val;
                noad->skoarpuscle = new SkoarpuscleMsg(val, args);
			}
		}

		noad->children.clear();
	};

    table[ESkoarNoad::ugen_simple] = [](Skoar *skoar, SkoarNoadPtr noad) {
        /*
        var ugen = noad.next_skoarpuscle;
        var args = nil;
		var end_noad = SkoarNoad(\ugen_s_end, noad);
		var msg = SkoarpuscleMsg(ugen.defaultMsg, nil);
				
		msg.dest = ugen;
				
		end_noad.skoarpuscle = msg;
		noad.add_noad(end_noad);
		*/
    };

    table[ESkoarNoad::ugen_with_args] = [](Skoar *skoar, SkoarNoadPtr noad) {
        /*
        var ugen = noad.next_skoarpuscle;
        var args = SkoarpuscleArgs.new;
        var end_noad = SkoarNoad(\ugen_wa_end, noad);
        var msg = SkoarpuscleMsg(ugen.defaultMsg, args);

        msg.dest = ugen;

        end_noad.skoarpuscle = msg;
        noad.add_noad(end_noad);
        */
    };

    table[ESkoarNoad::lute] = [](Skoar *skoar, SkoarNoadPtr noad) {
        /*
        var lute = noad.next_skoarpuscle;

		if (lute.has_messages == true) {
			var args = SkoarpuscleArgs.new;
			var end_noad = SkoarNoad(\lute_string_end, noad);
			var msg = SkoarpuscleMsg(\string, args);

			msg.dest = lute;
					
			end_noad.skoarpuscle = msg;
			noad.add_noad(end_noad);
		};
        */
    };

    table[ESkoarNoad::expr] = [](Skoar *skoar, SkoarNoadPtr noad) {
		// we insert a node at the end of the expression
		// so we can impress the result
        
        auto end_noad = SkoarNoad::New<ESkoarNoad::artificial>(wstring(L"expr_end"), noad);
		end_noad->on_enter = [&](SkoarMinstrel *m) {
			m->fairy->cast_arcane_magic();
		};

		noad->add_noad(end_noad);
        
	};

    table[ESkoarNoad::msgable] = [](Skoar *skoar, SkoarNoadPtr noad) {
		auto noads = new list<SkoarNoadPtr>;

		// strip out the msg operators
		for (auto x: noad->children) {
			if (typeid(x->toke) != typeid(Toke_MsgOp*)) {
				noads->emplace_back(x);
			}
		}

		noad->children = *noads;
		noads = &noad->children;

		// evaluate a chain of messages, returning the result
		noad->on_enter = [&](SkoarMinstrel *m) {
			auto result = noads->front()->next_skoarpuscle();

			if (result != nullptr) {
				for (auto y : *noads) {
					auto x = y->skoarpuscle;
						
					if (typeid(x) == typeid(SkoarpuscleMsg*)) {
						//result = static_cast<SkoarpuscleMsg*>(result)->skoar_msg(x, m);

					}
					else if (typeid(x) == typeid(SkoarpuscleLoopMsg*)) {
						//result = static_cast<SkoarpuscleLoopMsg*>(x)->val->foreach(result);
					}
				}

				//"msgable: ".post; result.postln;
				m->fairy->impress(result);
			};

		};
	};

	table[ESkoarNoad::assignment] = [](Skoar *skoar, SkoarNoadPtr noad) {

		auto child = noad->children.begin();
		wstring *op = &(*child)->toke->lexeme;

		++child;

		auto settable = (*child)->next_skoarpuscle();

		if (*op == L"=>") {
			noad->on_enter = [=](SkoarMinstrel *m) {
				auto x = m->fairy->cast_arcane_magic();
				//skoar->ops->assign(m, x, settable);
			};
		}
		else if (*op == L"+>") {
			noad->on_enter = [=](SkoarMinstrel *m) {
				auto x = m->fairy->impression;
				// todo Skoar.ops.increment(m, x, settable);
			};
		}
		else if (*op == L"->") {
			noad->on_enter = [=](SkoarMinstrel *m) {
				auto x = m->fairy->impression;
				// todo Skoar.ops.decrement(m, x, settable);
			};
		}
	};
		
    table[ESkoarNoad::math] = [](Skoar *skoar, SkoarNoadPtr noad) {
		auto op = noad->children.front()->skoarpuscle;

		noad->on_enter = [=](SkoarMinstrel *m) {
			auto left = m->fairy->cast_arcane_magic();

			m->fairy->charge_arcane_magic(
				[=]() {
					Skoarpuscle *right = m->fairy->impression;
					//op->calculate(m, left, right);
					return m->fairy->impression;
				}
			);

		};

	};
		
}
