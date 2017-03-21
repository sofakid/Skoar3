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

    {ESkoarNoad::skoar, SpellOfSkoarmantics {
        noad->skoarpuscle = make_shared<SkoarpuscleSkoarpion>(Skoarpion::new_from_skoar(skoar));
        noad->children.clear();
    }},

    {ESkoarNoad::skoarpion, SpellOfSkoarmantics {
        noad->skoarpuscle = make_shared<SkoarpuscleSkoarpion>(Skoarpion::new_from_skoar_noad(skoar, noad));
        noad->children.clear();
    }},

    {ESkoarNoad::meditation, SpellOfSkoarmantics {
        noad->skoarpuscle = make_shared<SkoarpuscleMeditation>(skoar, noad);
        noad->children.clear();
    }},

    {ESkoarNoad::conditional, SpellOfSkoarmantics {
        noad->skoarpuscle = make_shared<SkoarpuscleConditional>(skoar, noad);
    }},

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

    {ESkoarNoad::regular_beat, SpellOfSkoarmantics {
        auto xp = noad->next_skoarpuscle();
        noad->skoarpuscle = xp;
        
        if (noad->parent->name == L"assignment") {
            noad->on_enter = [&](SkoarMinstrelPtr m) {
                dynamic_cast<SkoarpuscleBeat&>(*xp).on_enter_sometimes(m);
            };
        }
    }},

    {ESkoarNoad::exact_beat, SpellOfSkoarmantics {
        auto skoarpuscle = noad->next_skoarpuscle();
        auto end_noad = SkoarNoad::NewArtificial(L"exact_beat_end", noad);
        end_noad->on_enter = [=](SkoarMinstrelPtr m) {
            dynamic_cast<SkoarpuscleExactBeat&>(*skoarpuscle).after(m);
        };

        noad->add_noad(end_noad);
    }},

    {ESkoarNoad::exact_rest, SpellOfSkoarmantics {
        auto skoarpuscle = noad->next_skoarpuscle();
        auto end_noad = SkoarNoad::NewArtificial(L"exact_rest_end", noad);
        end_noad->on_enter = [=](SkoarMinstrelPtr m) {
            dynamic_cast<SkoarpuscleExactRest&>(*skoarpuscle).after(m);
        };

        noad->add_noad(end_noad);
    }},

    {ESkoarNoad::loop, SpellOfSkoarmantics {
        noad->skoarpuscle = make_shared<SkoarpuscleLoop>(skoar, noad);
        noad->children.clear();
    }},

    {ESkoarNoad::musical_keyword_misc, SpellOfSkoarmantics {
        noad->skoarpuscle = noad->next_skoarpuscle();
        noad->children.clear();
    }},

    {ESkoarNoad::cthulhu, SpellOfSkoarmantics {
        noad->on_enter = [&](SkoarMinstrelPtr m) {
            skoar->cthulhu(noad);
        };
    }},

    {ESkoarNoad::dal_goto, SpellOfSkoarmantics {
        noad->skoarpuscle = make_shared<SkoarpuscleGoto>(noad);
    }},

    {ESkoarNoad::marker, SpellOfSkoarmantics {
        auto x = noad->next_skoarpuscle();
        noad->skoarpuscle = x;

        if (typeid(*x) == typeid(SkoarpuscleBars)) {
            auto y = dynamic_cast<SkoarpuscleBars&>(*x);
            y.noad = noad;
            noad->children.clear();
        }

    }},

    // deref*         : Deref MsgNameWithArgs listy_suffix
    //                | Deref MsgName
    {ESkoarNoad::deref, SpellOfSkoarmantics {
        auto end_noad = SkoarNoad::NewArtificial(L"deref_end", noad);

        auto it = noad->children.begin();
        auto msg_name = (*(++it))->skoarpuscle->val.extract<SkoarString>();

        SkoarpusclePtr args = nullptr;
        if (noad->children.size() > 2) {
            args = make_shared<SkoarpuscleArgs>();
        }

        auto x = make_shared<SkoarpuscleDeref>(msg_name, args);
        noad->skoarpuscle = x;

        end_noad->on_enter = [=](SkoarMinstrelPtr m) {
            x->on_exit(m);
        };

    }},

    {ESkoarNoad::listy, SpellOfSkoarmantics {
        noad->skoarpuscle = make_shared<SkoarpuscleList>();
    }},

    {ESkoarNoad::arg_listy, SpellOfSkoarmantics {
        noad->skoarpuscle = make_shared<SkoarpuscleArgList>(noad);
    }},

    {ESkoarNoad::arg_expr, SpellOfSkoarmantics {
        noad->skoarpuscle = make_shared<SkoarpuscleArgExpr>();
        noad->children.clear();
    }},

    {ESkoarNoad::skrp_sig, SpellOfSkoarmantics {
        noad->skoarpuscle = make_shared<SkoarpuscleSkoarpionSig>(noad);
    }},

    {ESkoarNoad::msg, SpellOfSkoarmantics {
        SkoarpusclePtr msg = noad->next_skoarpuscle();

        if (msg != nullptr) {
            if (typeid(*msg) == typeid(SkoarpuscleList)) {
                // i'm not sure what i want this to mean
                noad->children.clear();
            }
            else if (typeid(*msg) == typeid(SkoarpuscleLoop)) {
                noad->skoarpuscle = make_shared<SkoarpuscleLoopMsg>(msg);
                noad->on_enter = [=](SkoarMinstrelPtr m) {
                    auto listy = m->fairy->impression;
                    auto loopy = dynamic_cast<SkoarpuscleLoop&>(*msg);
                    loopy.foreach(listy);
                    loopy.on_enter(m);
                };
                noad->children.clear();
            }
            else if (typeid(*msg) == typeid(SkoarpuscleMsgNameWithArgs)) {
                // we need the tree to have the same
                // structure as below. I don't want to
                // treat these too differently (with args or without)
                //
                // this code constructs and passes args, otherwise the same.
                shared_ptr<SkoarpuscleArgs> args = make_shared<SkoarpuscleArgs>();
                SkoarString val = msg->val;
                auto x = make_shared<SkoarpuscleMsg>(val, args);

                auto end_noad = SkoarNoad::NewArtificial(L"msg_end", noad);
                end_noad->skoarpuscle = x;
                noad->add_noad(end_noad);
            }
            else if (typeid(*msg) == typeid(SkoarpuscleMsgName)) {
                // we need the tree to have the same
                // structure as above. I don't want to
                // treat these too differently (with args or without)
                //
                // this code passes nullptr as args, otherwise same.
                SkoarString val = msg->val;
                auto x = make_shared<SkoarpuscleMsg>(val, nullptr);

                auto end_noad = SkoarNoad::NewArtificial(L"msg_end", noad);
                end_noad->skoarpuscle = x;
                noad->add_noad(end_noad);
            }
        }
    }},

    {ESkoarNoad::ugen_simple, SpellOfSkoarmantics {
        auto ugen_ptr = noad->next_skoarpuscle();
        auto ugen = dynamic_cast<SkoarpuscleUGen&>(*ugen_ptr);
        auto msg = make_shared<SkoarpuscleMsg>(ugen.defaultMsg(), nullptr);
        msg->dest = ugen_ptr;

        auto end_noad = SkoarNoad::NewArtificial(L"ugen_s_end", noad);
        end_noad->skoarpuscle = msg;
        noad->add_noad(end_noad);
    }},

    {ESkoarNoad::ugen_with_args, SpellOfSkoarmantics {
        auto ugen_ptr = noad->next_skoarpuscle();
        auto ugen = dynamic_cast<SkoarpuscleUGen&>(*ugen_ptr); //not a skoarpuscle ugen with args?
        auto args = make_shared<SkoarpuscleArgs>();
        auto msg = make_shared<SkoarpuscleMsg>(ugen.defaultMsg(), args);
        msg->dest = ugen_ptr;
        
        auto end_noad = SkoarNoad::NewArtificial(L"ugen_wa_end", noad);
        end_noad->skoarpuscle = msg;
        noad->add_noad(end_noad);
    }},

    {ESkoarNoad::lute, SpellOfSkoarmantics {
        auto lute_ptr = noad->next_skoarpuscle();
        auto lute = dynamic_cast<SkoarpuscleLute&>(*lute_ptr);
        
        if (lute.has_messages) {
            auto args = make_shared<SkoarpuscleArgs>();
            auto msg = make_shared<SkoarpuscleMsg>(L"string", args);
            msg->dest = lute_ptr;

            auto end_noad = SkoarNoad::NewArtificial(L"lute_string_end", noad);
            end_noad->skoarpuscle = msg;
            noad->add_noad(end_noad);
        }
    }},

    {ESkoarNoad::expr, SpellOfSkoarmantics {
        // we insert a node at the end of the expression
        // so we can impress the result
        auto end_noad = SkoarNoad::NewArtificial(L"expr_end", noad);
        auto child = noad->children.front()->skoarpuscle;
        auto needs_compile = false;

        for (auto x : *noad->collect_skoarpuscles()) {
            if (typeid(*x) == typeid(SkoarpuscleUGen)) {
                needs_compile = true;
            }
        }

        if (typeid(*child) == typeid(SkoarpuscleSymbolColon)) {
            
            noad->on_enter = [](SkoarMinstrelPtr m) {
                m->fairy->push_noating();
            };

            end_noad->on_enter = [=](SkoarMinstrelPtr m) {
                auto x = m->fairy->cast_arcane_magic();
                auto p = make_shared<SkoarpusclePair>(child, x);

                m->fairy->impress(p);

                if (needs_compile) {
                    m->fairy->compile_ugen();
                }

                m->fairy->pop_noating();
            };

        }
        else {
            end_noad->on_enter = [=](SkoarMinstrelPtr m) {
                m->fairy->cast_arcane_magic();
                if (needs_compile) {
                    m->fairy->compile_ugen();
                }
            };
        }

        noad->add_noad(end_noad);
    }},

    {ESkoarNoad::msgable, SpellOfSkoarmantics {
        auto skoarpuscle = noad->next_skoarpuscle();
        
        if (typeid(*skoarpuscle) == typeid(SkoarpuscleUGen)) {

            auto end_noad = SkoarNoad::NewArtificial(L"msgable_end", noad);
            end_noad->on_enter = [](SkoarMinstrelPtr m) {
                m->fairy->compile_ugen();
            };
            noad->add_noad(end_noad);
        }

        auto has_messages = false;

        // strip out the msg operators
        noad->children.remove_if([&](SkoarNoadPtr x) {
            if (x->toke == nullptr)
                return false;
            if (x->toke->kind == ESkoarToke::MsgOp) {
                has_messages = true;
                return true;
            }
            return false;
        });

        // chain the messages
        SkoarpusclePtr last = skoarpuscle;
        for (auto x : noad->children) {
            for (auto y : x->children) {
                auto ys = y->skoarpuscle;
                if (ys == nullptr)
                    continue;
                if (typeid(*ys) == typeid(SkoarpuscleMsg)) {
                    auto oMsg = dynamic_cast<SkoarpuscleMsg&>(*ys);
                    oMsg.dest = last;
                    last = ys;
                }
            }
        }

        if (has_messages) {
            if (typeid(*skoarpuscle) == typeid(SkoarpuscleList)) {
                auto listy = dynamic_cast<SkoarpuscleList&>(*skoarpuscle);
                listy.noaty = false;
            }
        }
    }},

    {ESkoarNoad::assignment, SpellOfSkoarmantics {
        auto child = noad->children.begin();
        auto op = (*child++)->toke->lexeme;

        auto settable = (*child)->next_skoarpuscle();

        if (op == L"=>") {
            noad->on_enter = [=](SkoarMinstrelPtr m) {
                auto x = m->fairy->cast_arcane_magic();
                //skoar->ops->assign(m, x, settable);
                m->fairy->impress(x);
            };
        }
        else if (op == L"+>") {
            noad->on_enter = [=](SkoarMinstrelPtr m) {
                auto x = m->fairy->impression;
                //skoar->ops->increment(m, x, settable);
            };
        }
        else if (op == L"->") {
            noad->on_enter = [=](SkoarMinstrelPtr m) {
                auto x = m->fairy->impression;
                //skoar->ops->decrement(m, x, settable);
            };
        }
        else if (op == L"*>") {
            noad->on_enter = [=](SkoarMinstrelPtr m) {
                auto x = m->fairy->impression;
                //skoar->ops->multr(m, x, settable);
            };
        }
    }},

    {ESkoarNoad::math, SpellOfSkoarmantics {
        auto op = noad->children.front()->skoarpuscle;

        noad->on_enter = [=](SkoarMinstrelPtr m) {
            auto left = m->fairy->cast_arcane_magic();

            m->fairy->charge_arcane_magic(
                [=]() {
                    SkoarpusclePtr right = m->fairy->impression;
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


