#include "decorating.hpp"

#include "lex.hpp"
#include "noad.hpp"
#include "skoarpuscle.hpp"
#include "skoarpion.hpp"
#include "fairy.hpp"
#include "skoar.hpp"
#include "minstrel.hpp"
#include "beaty.hpp"
#include "skoarpion_skoarpuscle.hpp"
#include "dsp.hpp"
#include "lute.hpp"
#include "meditation.hpp"

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

#define SpellOfSkoarmantics [](Skoar *skoar, SkoarNoadPtr noad)

Skoarmantics::Skoarmantics() : table({

    // ported yes
    {ESkoarNoad::skoar, SpellOfSkoarmantics {
        noad->skoarpuscle = make_shared<SkoarpuscleSkoarpion>(Skoarpion::new_from_skoar(skoar));
        noad->children.clear();
    }},

    // ported yes
    {ESkoarNoad::skoarpion, SpellOfSkoarmantics {
        noad->skoarpuscle = make_shared<SkoarpuscleSkoarpion>(Skoarpion::new_from_skoar_noad(skoar, noad));
        noad->children.clear();
    }},

    // ported yes
    {ESkoarNoad::meditation, SpellOfSkoarmantics {
        noad->skoarpuscle = make_shared<SkoarpuscleMeditation>(skoar, noad);
        noad->children.clear();
    }},

    // ported yes
    {ESkoarNoad::conditional, SpellOfSkoarmantics {
        noad->skoarpuscle = make_shared<SkoarpuscleConditional>(skoar, noad);
    }},

    // ported yes
    {ESkoarNoad::boolean_expr, SpellOfSkoarmantics { 
        
        // we insert a node at the end of the boolean expression
        // so we can restore the impression
        auto end_noad = SkoarNoad::NewArtificial(L"boolean_expr_end", noad);

        noad->on_enter = [](SkoarMinstrelPtr m) {
            //("boolean_expr :: push_boolean").postln;
            m->fairy->push_boolean();
        };

        end_noad->on_enter = [](SkoarMinstrelPtr m) {
            //("boolean_expr :: pop_boolean").postln;
            m->fairy->pop_boolean();
        };

        noad->add_noad(end_noad);
        
    }},

    // ported yes
    {ESkoarNoad::boolean, SpellOfSkoarmantics {
        
        // we insert a node at the end of the expression
        // so we can evaluate the result
        auto end_noad = SkoarNoad::NewArtificial(L"boolean_end", noad);
        auto x = make_shared<SkoarpuscleBoolean>(noad);

        noad->skoarpuscle = x;

        end_noad->on_enter = [&](SkoarMinstrelPtr m) {
            auto l_value = m->fairy->l_value;
            auto imp = m->fairy->impression;

            if (x->evaluate(m, l_value, imp))
                m->fairy->impress(make_shared<SkoarpuscleTrue>());
            else 
                m->fairy->impress(make_shared<SkoarpuscleFalse>());

            m->fairy->pop_compare();
        };

        noad->add_noad(end_noad);
        
    }},

    // ported yes
    {ESkoarNoad::regular_beat, SpellOfSkoarmantics {
        auto xp = noad->next_skoarpuscle();

        noad->skoarpuscle = xp;
        
        if (noad->parent->name == L"assignment") {
            noad->on_enter = [&](SkoarMinstrelPtr m) {
                dynamic_cast<SkoarpuscleBeat&>(*xp).on_enter_sometimes(m);
            };
        }
    }},

    // ported yes
    {ESkoarNoad::exact_beat, SpellOfSkoarmantics {
        auto skoarpuscle = noad->next_skoarpuscle();
        auto end_noad = SkoarNoad::NewArtificial(L"exact_beat_end", noad);
        end_noad->on_enter = [=](SkoarMinstrelPtr m) {
            dynamic_cast<SkoarpuscleExactBeat&>(*skoarpuscle).after(m);
        };

        noad->add_noad(end_noad);
    }},

    // ported yes
    {ESkoarNoad::exact_rest, SpellOfSkoarmantics {
        auto skoarpuscle = noad->next_skoarpuscle();
        auto end_noad = SkoarNoad::NewArtificial(L"exact_rest_end", noad);
        end_noad->on_enter = [=](SkoarMinstrelPtr m) {
            dynamic_cast<SkoarpuscleExactRest&>(*skoarpuscle).after(m);
        };

        noad->add_noad(end_noad);
    }},

    // ported yes
    {ESkoarNoad::loop, SpellOfSkoarmantics {
        noad->skoarpuscle = make_shared<SkoarpuscleLoop>(skoar, noad);
        noad->children.clear();
    }},

    // ported yes
    {ESkoarNoad::musical_keyword_misc, SpellOfSkoarmantics {
        noad->skoarpuscle = noad->next_skoarpuscle();
        noad->children.clear();
    }},

    // ported yes
    {ESkoarNoad::cthulhu, SpellOfSkoarmantics {
        noad->on_enter = [&](SkoarMinstrelPtr m) {
            skoar->cthulhu(noad);
        };
    }},

    // ported yes
    {ESkoarNoad::dal_goto, SpellOfSkoarmantics {
        noad->skoarpuscle = make_shared<SkoarpuscleGoto>(noad);
    }},

    // ported yes
    {ESkoarNoad::marker, SpellOfSkoarmantics {
        auto x = noad->next_skoarpuscle();
        noad->skoarpuscle = x;

        if (typeid(*x) == typeid(SkoarpuscleBars)) {
            //y.noad = noad;
            auto y = dynamic_cast<SkoarpuscleBars&>(*x);
            y.noad = noad;
            noad->children.clear();
        }

    }},

    // deref*         : Deref MsgNameWithArgs listy_suffix
    //                | Deref MsgName
    {ESkoarNoad::deref, SpellOfSkoarmantics {
        // this still needs to be compared
        shared_ptr<SkoarpuscleDeref> x;
        shared_ptr<SkoarpuscleArgs> args = nullptr;
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
            args = make_shared<SkoarpuscleArgs>();
        }

        x = make_shared<SkoarpuscleDeref>(msg_name, args);
        noad->skoarpuscle = x;

        // !f<x,y>
        if (args != nullptr) {

            auto end_noad = SkoarNoad::NewArtificial(L"deref_end", noad);
            end_noad->on_enter = [&](SkoarMinstrelPtr m) {
                m->fairy->cast_arcane_magic();
                x->on_enter(m);
            };

            noad->add_noad(end_noad);
            noad->on_enter = [&](SkoarMinstrelPtr m) {
                args->on_enter(m);
            };

            // !f
        } {
            noad->on_enter = [&](SkoarMinstrelPtr m) {
                x->on_enter(m);
            };
        };

    }},

    // ported yes
    {ESkoarNoad::listy, SpellOfSkoarmantics {
        noad->skoarpuscle = make_shared<SkoarpuscleList>();
    }},

    // ported yes
    {ESkoarNoad::arg_listy, SpellOfSkoarmantics {
        noad->skoarpuscle = make_shared<SkoarpuscleArgList>(noad);
    }},

    // ported yes
    {ESkoarNoad::arg_expr, SpellOfSkoarmantics {
        noad->skoarpuscle = make_shared<SkoarpuscleArgExpr>();
        noad->children.clear();
    }},

    // ported yes
    {ESkoarNoad::skrp_sig, SpellOfSkoarmantics {
        noad->skoarpuscle = make_shared<SkoarpuscleSkoarpionSig>(noad);
    }},

    {ESkoarNoad::msg, SpellOfSkoarmantics {
        // todo: compare
        SkoarpusclePtr msg = noad->next_skoarpuscle();

        if (msg != nullptr) {
            if (typeid(msg) == typeid(SkoarpuscleList*)) {
                // i'm not sure what i want this to mean

            }
            else if (typeid(msg) == typeid(SkoarpuscleLoop*)) {
                SkoarString val = msg->val;
                noad->skoarpuscle = make_shared<SkoarpuscleLoopMsg>(val);
            }
            else if (typeid(msg) == typeid(SkoarpuscleMsgName*)) {
                shared_ptr<SkoarpuscleArgs> args = make_shared<SkoarpuscleArgs>();
                SkoarString val = msg->val;
                noad->skoarpuscle = make_shared<SkoarpuscleMsg>(val, args);
            }
        }

        noad->children.clear();
    }},

    {ESkoarNoad::ugen_simple, SpellOfSkoarmantics {
        /*
        var ugen = noad.next_skoarpuscle;
        var args = nil;
        var end_noad = SkoarNoad(\ugen_s_end, noad);
        var msg = SkoarpuscleMsg(ugen.defaultMsg, nil);

        msg.dest = ugen;

        end_noad.skoarpuscle = msg;
        noad.add_noad(end_noad);
        */
    }},

    {ESkoarNoad::ugen_with_args, SpellOfSkoarmantics {
        /*
        var ugen = noad.next_skoarpuscle;
        var args = SkoarpuscleArgs.new;
        var end_noad = SkoarNoad(\ugen_wa_end, noad);
        var msg = SkoarpuscleMsg(ugen.defaultMsg, args);

        msg.dest = ugen;

        end_noad.skoarpuscle = msg;
        noad.add_noad(end_noad);
        */
    }},

    {ESkoarNoad::lute, SpellOfSkoarmantics {
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
    }},

    {ESkoarNoad::expr, SpellOfSkoarmantics {
        /*
        // we insert a node at the end of the expression
        // so we can impress the result
        var end_noad = SkoarNoad(\expr_end, noad);
		var child = noad.children[0].skoarpuscle;
		var needs_compile = false;

		noad.collect_skoarpuscles.do {
			| x |
			if (x.isKindOf(SkoarpuscleUGen)) {
				needs_compile = true;
			};
		};
				
		if (child.isKindOf(SkoarpuscleSymbolColon)) {
			var settable = child;
			noad.on_enter = {
				| m, nav |
				//("SYM_COL :: pushing noating").postln;
				m.fairy.push_noating;
			};
			end_noad.on_enter = {
				| m, nav |
				var x;
				var p;

				//Skoar.ops.assign(m, x, settable);
				x = m.fairy.cast_arcane_magic;
						
				p = SkoarpusclePair(settable, x);
				//"SSC".postln;
                m.fairy.impress(p);
				if (needs_compile == true) {
					m.fairy.compile_ugen;
				};
				//("SYM_COL :: popping noating").postln;
				m.fairy.pop_noating;

			};
		} {
			end_noad.on_enter = {
				| m, nav |
				//"EXPR ARCANE".postln;
				m.fairy.cast_arcane_magic;
				if (needs_compile == true) {
					m.fairy.compile_ugen;
				};
			};
		};
                
        noad.add_noad(end_noad);
    },
        */

    }},

    {ESkoarNoad::msgable, SpellOfSkoarmantics {
        // todo: compare
        auto noads = new list<SkoarNoadPtr>;

        // strip out the msg operators
        for (auto x : noad->children) {
            if (typeid(x->toke) != typeid(Toke_MsgOp*)) {
                noads->push_back(x);
            }
        }

        noad->children = *noads;
        noads = &noad->children;

        // evaluate a chain of messages, returning the result
        noad->on_enter = [&](SkoarMinstrelPtr m) {
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
    }},

    {ESkoarNoad::assignment, SpellOfSkoarmantics {
        // todo: compare
            auto child = noad->children.begin();
            wstring *op = &(*child)->toke->lexeme;

            ++child;

            auto settable = (*child)->next_skoarpuscle();

            if (*op == L"=>") {
                noad->on_enter = [=](SkoarMinstrelPtr m) {
                    auto x = m->fairy->cast_arcane_magic();
                    //skoar->ops->assign(m, x, settable);
                };
            }
            else if (*op == L"+>") {
                noad->on_enter = [=](SkoarMinstrelPtr m) {
                    auto x = m->fairy->impression;
                    // todo Skoar.ops.increment(m, x, settable);
                };
            }
            else if (*op == L"->") {
                noad->on_enter = [=](SkoarMinstrelPtr m) {
                    auto x = m->fairy->impression;
                    // todo Skoar.ops.decrement(m, x, settable);
                };
            }
        }},

        // ported yes
        {ESkoarNoad::math, SpellOfSkoarmantics {
            auto op = noad->children.front()->skoarpuscle;

            noad->on_enter = [=](SkoarMinstrelPtr m) {
                auto left = m->fairy->cast_arcane_magic();

                m->fairy->charge_arcane_magic(
                    [=]() {
                        SkoarpusclePtr right = m->fairy->impression;
                        // todo: make op
                        //op->calculate(m, left, right);
                        return m->fairy->impression;
                    }
                );

            };

        }}

}) {
}

void Skoarmantics::decorate(Skoar* skoar, SkoarNoadPtr noad) {
    // it is a pair<key, value>
    auto it = table.find(noad->kind);
    if (it != table.end())
        (it->second)(skoar, noad);
}


