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
#include "all_skoarpuscles.hpp"
#include "operators.hpp"

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

static Skoarmantics* decorator;
void Skoarmantics::init () {
    decorator = new Skoarmantics ();
}

Skoarmantics* Skoarmantics::instance () {
    return decorator;
}

#define SpellOfSkoarmantics [](Skoar *skoar, SkoarNoadPtr noad)
#define SpellOfSimpleSkoarmantics [](Skoar* /*skoar*/, SkoarNoadPtr noad)

auto expr_spell (SpellOfSimpleSkoarmantics {
    // expr_b could be <e>
    if (noad->children.size () == 0)
        return;

    // we insert a node at the end of the expression
    // so we can impress the result
    auto end_noad (SkoarNoad::NewArtificial (L"expr_end", noad));
    auto child (noad->children.front ()->skoarpuscle);
    auto needs_compile (false);

    auto listy (noad->collect_skoarpuscles ());
    for (auto x : listy)
        if (is_skoarpuscle<SkoarpuscleUGen> (x))
            needs_compile = true;

    if (is_skoarpuscle<SkoarpuscleSymbolColon> (child))
    {

        noad->on_enter = [](SkoarMinstrelPtr m) {
            m->fairy->push_noating ();
        };

        end_noad->on_enter = [=](SkoarMinstrelPtr m) {
            auto& fairy (*m->fairy);
            auto x (fairy.cast_arcane_magic ());
            SkoarpusclePtr p (std::make_shared<SkoarpusclePair> (
                skoarpuscle_ptr<SkoarpuscleSymbolColon> (child)->val, x));

            fairy.impress (p);

            if (needs_compile)
                fairy.compile_ugen ();

            fairy.pop_noating ();
        };

        // name the named skoarpions
        if (noad->children.size () > 1)
        {
            auto it (noad->children.begin ());
            auto next_expr (*(++it));
            auto next_skrp (next_expr->next_skoarpuscle ());

            if (is_skoarpuscle <SkoarpuscleSkoarpion> (next_skrp))
            {
                auto p (skoarpuscle_ptr <SkoarpuscleSkoarpion> (next_skrp));
                p->val->name = skoarpuscle_ptr<SkoarpuscleSymbolColon> (child)->val;
            }

        }

    }
    else
    end_noad->on_enter = [=](SkoarMinstrelPtr m) {
        auto& fairy (*m->fairy);
        fairy.cast_arcane_magic ();
        if (needs_compile)
            fairy.compile_ugen ();
    };

    noad->add_noad (end_noad);
});

auto math_spell (SpellOfSimpleSkoarmantics {
    if (noad->children.size () <= 1)
        return;
    
    noad->on_enter = [=](SkoarMinstrelPtr m) {
        m->fairy->push_magic ();
    };
    auto end_noad (SkoarNoad::NewArtificial (L"math_end", noad));
    end_noad->on_enter = [=](SkoarMinstrelPtr m) {
        auto& fairy (*m->fairy);
        fairy.cast_arcane_magic ();
        fairy.pop_magic ();
    };

    noad->add_noad (end_noad);
});


Skoarmantics::Skoarmantics () : table ({

    {ESkoarNoad::skoar, SpellOfSkoarmantics {
        noad->skoarpuscle = std::make_shared<SkoarpuscleSkoarpion> (Skoarpion::NewFromSkoar (skoar));
        noad->children.clear ();
    }},

    {ESkoarNoad::skoarpion, SpellOfSkoarmantics {
        noad->skoarpuscle = std::make_shared<SkoarpuscleSkoarpion> (Skoarpion::NewFromSkoarNoad (skoar, noad));
        noad->children.clear ();
    }},

    {ESkoarNoad::meditation, SpellOfSkoarmantics {
        noad->skoarpuscle = std::make_shared<SkoarpuscleMeditation> (skoar, noad);
        noad->children.clear ();
    }},

    {ESkoarNoad::conditional, SpellOfSkoarmantics {
        noad->skoarpuscle = std::make_shared<SkoarpuscleConditional> (skoar, noad);
    }},

    {ESkoarNoad::boolean_or,  math_spell },
    {ESkoarNoad::boolean_and, math_spell },
    {ESkoarNoad::cmp_eq_neq,  math_spell },
    {ESkoarNoad::cmp_gt_lt,   math_spell },
    {ESkoarNoad::math_add_sub, math_spell },
    {ESkoarNoad::math_mul_div_mod, math_spell },

    {ESkoarNoad::regular_beat, SpellOfSimpleSkoarmantics {
        auto xp (noad->next_skoarpuscle ());
        noad->skoarpuscle = xp;
        
        // on_enter_sometimes is because we used to not enter is assigning to a beat
        // (tempo) but we don't do that anymore. could be just on_enter and avoid all this.
        noad->on_enter = [=](SkoarMinstrelPtr m) {
            if (is_skoarpuscle<SkoarpuscleBeat> (xp))
                skoarpuscle_ptr<SkoarpuscleBeat> (xp)->on_enter_sometimes(m);
                
            else if (is_skoarpuscle<SkoarpuscleRest> (xp))
                skoarpuscle_ptr<SkoarpuscleRest> (xp)->on_enter_sometimes(m);
                
        };

        noad->clear_children ();
    }},

    {ESkoarNoad::exact_beat, SpellOfSimpleSkoarmantics {
        auto skoarpuscle (noad->next_skoarpuscle ());
        auto end_noad (SkoarNoad::NewArtificial (L"exact_beat_end", noad));
        end_noad->on_enter = [=](SkoarMinstrelPtr m) {
            skoarpuscle_ptr<SkoarpuscleExactBeat> (skoarpuscle)->after (m);
        };

        noad->add_noad(end_noad);
    }},

    {ESkoarNoad::exact_rest, SpellOfSimpleSkoarmantics {
        auto skoarpuscle (noad->next_skoarpuscle ());
        auto end_noad (SkoarNoad::NewArtificial (L"exact_rest_end", noad));
        end_noad->on_enter = [=](SkoarMinstrelPtr m) {
            skoarpuscle_ptr<SkoarpuscleExactRest> (skoarpuscle)->after (m);
        };

        noad->add_noad(end_noad);
    }},

    {ESkoarNoad::loop, SpellOfSkoarmantics {
        noad->skoarpuscle = std::make_shared<SkoarpuscleLoop> (skoar, noad);
        noad->children.clear ();
    }},

    {ESkoarNoad::musical_keyword_misc, SpellOfSimpleSkoarmantics {
        noad->skoarpuscle = noad->next_skoarpuscle ();
        noad->children.clear ();
    }},

    {ESkoarNoad::cthulhu, SpellOfSimpleSkoarmantics {
        noad->on_enter = [=](SkoarMinstrelPtr m) {
        //    noad->on_enter = nullptr;
        //    skoar->cthulhu (noad);
        };
    }},

    {ESkoarNoad::al_goto, SpellOfSimpleSkoarmantics {
        noad->skoarpuscle = std::make_shared<SkoarpuscleGoto> (noad);
    }},

    {ESkoarNoad::marker, SpellOfSimpleSkoarmantics {
        auto x (noad->next_skoarpuscle ());
        noad->skoarpuscle = x;

        if (is_skoarpuscle<SkoarpuscleBars> (x)) {
            skoarpuscle_ptr<SkoarpuscleBars> (x)->noad = noad;
            noad->children.clear ();
        }

    }},

    // deref*         : MsgNameWithArgs listy_suffix
    //                | MsgName
    {ESkoarNoad::deref, SpellOfSimpleSkoarmantics {
        auto end_noad (SkoarNoad::NewArtificial (L"deref_end", noad));

        auto it (noad->children.begin ());
        auto msg_name_sk ((*(++it))->skoarpuscle);

        SkoarString msg_name;
        
        if (is_skoarpuscle<SkoarpuscleMsgName> (msg_name_sk))
            msg_name = skoarpuscle_ptr<SkoarpuscleMsgName> (msg_name_sk)->val;

        else if (is_skoarpuscle<SkoarpuscleMsgNameWithArgs> (msg_name_sk))
            msg_name = skoarpuscle_ptr<SkoarpuscleMsgNameWithArgs> (msg_name_sk)->val;
        
        else 
            throw SkoarDecoratingException (L"Decorating msg_name fail", msg_name_sk);

        SkoarpusclePtr args = nullptr;
        if (noad->children.size () > 2)
            args = std::make_shared<SkoarpuscleArgs> ();

        auto x (std::make_shared<SkoarpuscleDeref> (msg_name, args));
        noad->skoarpuscle = x;

        end_noad->on_enter = [=](SkoarMinstrelPtr m) {
            x->on_exit (m);
        };

        noad->add_noad (end_noad);

    }},

    {ESkoarNoad::listy, SpellOfSimpleSkoarmantics {
        noad->skoarpuscle = std::make_shared<SkoarpuscleList> ();
    }},

    {ESkoarNoad::msg, SpellOfSimpleSkoarmantics {
        /*
        msgable
          0 -- nouny
          1 -- MsgOp
          2 -- msg
                - charge arcane magic with impression (msg dest)
                - push magic stack
          2.0 -- MsgWArgs
          2.1 -- listy_suffix
          2.x -- insert noad to process msg
                   - get impression: this is the args
                   - pop magic stack
                   - cast arcane magic to get msg dest
                   - send msg to dest
          3 -- MsgOp
          4 -- msg
        */
        SkoarpusclePtr msg (noad->next_skoarpuscle ());

        if (msg != nullptr) {
            if (is_skoarpuscle<SkoarpuscleList> (msg))
                // i'm not sure what i want this to mean
                noad->children.clear();
            
            else if (is_skoarpuscle<SkoarpuscleLoop>(msg)) {
                noad->skoarpuscle = std::make_shared<SkoarpuscleLoopMsg> (msg);
                noad->on_enter = [=](SkoarMinstrelPtr m) {
                    auto listy (m->fairy->impression);
                    auto loopy (skoarpuscle_ptr<SkoarpuscleLoop> (msg));
                    loopy->foreach (listy);
                    loopy->on_enter (m);
                };
                noad->children.clear();
            }
            else if (is_skoarpuscle<SkoarpuscleMsgNameWithArgs> (msg)) {
                
                auto sel (skoarpuscle_ptr<SkoarpuscleMsgNameWithArgs> (msg)->val);
                
                noad->on_enter = [=](SkoarMinstrelPtr m) {
                    auto& fairy (*m->fairy);
                    auto dest (fairy.impression);
                    fairy.charge_arcane_magic ([=]() {
                        return dest;
                    });
                    fairy.push_magic ();
                };

                auto end_noad (SkoarNoad::NewArtificial (L"msg_end", noad));
                end_noad->on_enter = [=](SkoarMinstrelPtr m) {

                    auto& fairy (*m->fairy);
                    auto args (fairy.impression);
                    fairy.pop_magic ();
                    auto dest (fairy.cast_arcane_magic ());
                    fairy.impress(dest->skoar_msg (sel, args, m));
                };
                noad->add_noad (end_noad);

            }
            else if (is_skoarpuscle<SkoarpuscleMsgName> (msg)) {
                auto sel (skoarpuscle_ptr<SkoarpuscleMsgName> (msg)->val);

                noad->on_enter = [=](SkoarMinstrelPtr m) {
                    auto& fairy (*m->fairy);
                    auto dest (fairy.impression);
                    fairy.charge_arcane_magic ([=]() {
                        return dest;
                    });
                    fairy.push_magic ();
                };

                auto end_noad (SkoarNoad::NewArtificial (L"msg_end", noad));
                end_noad->on_enter = [=](SkoarMinstrelPtr m) {
                    auto& fairy (*m->fairy);
                    fairy.pop_magic ();
                    auto dest (fairy.cast_arcane_magic ());
                    fairy.impress(dest->skoar_msg (sel, nullptr, m));
                };
                noad->add_noad (end_noad);
            }
        }
    }},

    {ESkoarNoad::ugen_simple, SpellOfSimpleSkoarmantics {
        auto ugen (noad->next_skoarpuscle ());
        //auto msg (make_shared<SkoarpuscleMsg> (skoarpuscle_ptr<SkoarpuscleUGen> (ugen)->defaultMsg (), nullptr));
        //msg->dest = ugen;

        auto end_noad (SkoarNoad::NewArtificial(L"ugen_s_end", noad));
        //end_noad->skoarpuscle = msg;
        noad->add_noad(end_noad);
    }},

    {ESkoarNoad::ugen_with_args, SpellOfSimpleSkoarmantics {
        auto ugen (noad->next_skoarpuscle ());
        auto args (std::make_shared<SkoarpuscleArgs> ());
        //auto msg (make_shared<SkoarpuscleMsg>(skoarpuscle_ptr<SkoarpuscleUGen> (ugen)->defaultMsg (), args));
        //msg->dest = ugen;
        
        auto end_noad (SkoarNoad::NewArtificial(L"ugen_wa_end", noad));
        //end_noad->skoarpuscle = msg;
        noad->add_noad (end_noad);
    }},

    {ESkoarNoad::lute, SpellOfSimpleSkoarmantics {
        auto lute (noad->next_skoarpuscle());
        auto lute_ptr (skoarpuscle_ptr<SkoarpuscleLute> (lute));
        
        if (lute_ptr->has_messages) {
            auto args (std::make_shared<SkoarpuscleArgs> ());
            //auto msg (make_shared<SkoarpuscleMsg> (L"string", args));
            //msg->dest = lute;

            auto end_noad (SkoarNoad::NewArtificial(L"lute_string_end", noad));
            //end_noad->skoarpuscle = msg;
            noad->add_noad (end_noad);
        }
    }},

    {ESkoarNoad::args , SpellOfSimpleSkoarmantics {
        noad->skoarpuscle = std::make_shared<SkoarpuscleArgList> (noad);
    }},

    {ESkoarNoad::args_entries , SpellOfSimpleSkoarmantics {
        noad->skoarpuscle = std::make_shared<SkoarpuscleArgExpr> (noad);
    }},

    {ESkoarNoad::assignment, expr_spell },
    {ESkoarNoad::expr,   expr_spell},

    {ESkoarNoad::msgable, SpellOfSimpleSkoarmantics {
        
        /*auto skoarpuscle (noad->next_skoarpuscle ());
        
        if (is_skoarpuscle<SkoarpuscleUGen> (skoarpuscle)) {

            auto end_noad (SkoarNoad::NewArtificial(L"msgable_end", noad));
            end_noad->on_enter = [](SkoarMinstrelPtr m) {
                m->fairy->compile_ugen();
            };
            noad->add_noad(end_noad);
        }

        auto has_messages (false);

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
                auto ys (y->skoarpuscle);
                if (is_skoarpuscle<SkoarpuscleMsg> (ys)) {
                    skoarpuscle_ptr<SkoarpuscleMsg> (ys)->dest = last;
                    last = ys;
                }
            }
        }

        if (has_messages && is_skoarpuscle<SkoarpuscleList>(skoarpuscle))
            skoarpuscle_ptr<SkoarpuscleList> (skoarpuscle)->noaty = false;
        */

    }}

}) {
}

void Skoarmantics::decorate(Skoar* skoar, SkoarNoadPtr noad) {
    // it is a pair<key, value>
    auto it (table.find(noad->kind));
    if (it != table.end())
        (it->second)(skoar, noad);
}


