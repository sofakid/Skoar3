// =====================================================================================================================
// rdpp.hpp - Generated by Code_Parser_Cpp - Create Recursive Descent Predictive Parser on 2017-03-14 14:00:23 for C++14
// =====================================================================================================================
#pragma once
#include "skoarcery.hpp"
#include "noad_fwd.hpp"
#include "exception_fwd.hpp"
#include "toker.hpp"
#include "spells.hpp"

struct SkoarStats {

    SkoarStats();

    // use a float so it never overflows when adding a small constant to it, 
    // just eventually stops making a difference.
    map<ESkoarToke::Kind, float> tokeFreq;
    list<ESkoarToke::Kind> *desirables;

};

class SkoarParser {
public:
    void fail(SkoarNoadPtr noad);
    void fail_too_deep(SkoarNoadPtr noad);
    void toker_fail(SkoarError& e, SkoarNoadPtr noad);

    SkoarToker *toker;
    int deep;
     SkoarParser(SkoarToker * tokr);
    SkoarNoadPtr branches(SkoarNoadPtr parent);
    SkoarNoadPtr skoar(SkoarNoadPtr parent);
    SkoarNoadPtr branch(SkoarNoadPtr parent);
    SkoarNoadPtr optional_voice(SkoarNoadPtr parent);
    SkoarNoadPtr phrases(SkoarNoadPtr parent);
    SkoarNoadPtr phrasey(SkoarNoadPtr parent);
    SkoarNoadPtr marker(SkoarNoadPtr parent);
    SkoarNoadPtr expr(SkoarNoadPtr parent);
    SkoarNoadPtr dal_goto(SkoarNoadPtr parent);
    SkoarNoadPtr beat(SkoarNoadPtr parent);
    SkoarNoadPtr skrp_sig(SkoarNoadPtr parent);
    SkoarNoadPtr skrp_suffix(SkoarNoadPtr parent);
    SkoarNoadPtr skoarpion(SkoarNoadPtr parent);
    SkoarNoadPtr opt_arg_spec(SkoarNoadPtr parent);
    SkoarNoadPtr skrp_lines(SkoarNoadPtr parent);
    SkoarNoadPtr skrp_moar_lines(SkoarNoadPtr parent);
    SkoarNoadPtr listy_suffix(SkoarNoadPtr parent);
    SkoarNoadPtr listy(SkoarNoadPtr parent);
    SkoarNoadPtr listy_entries(SkoarNoadPtr parent);
    SkoarNoadPtr moar_listy_entries(SkoarNoadPtr parent);
    SkoarNoadPtr coda(SkoarNoadPtr parent);
    SkoarNoadPtr optional_al_coda(SkoarNoadPtr parent);
    SkoarNoadPtr al_x(SkoarNoadPtr parent);
    SkoarNoadPtr dynamic(SkoarNoadPtr parent);
    SkoarNoadPtr musical_keyword(SkoarNoadPtr parent);
    SkoarNoadPtr ottavas(SkoarNoadPtr parent);
    SkoarNoadPtr pedally(SkoarNoadPtr parent);
    SkoarNoadPtr musical_keyword_misc(SkoarNoadPtr parent);
    SkoarNoadPtr cthulhu(SkoarNoadPtr parent);
    SkoarNoadPtr nouny(SkoarNoadPtr parent);
    SkoarNoadPtr conditional(SkoarNoadPtr parent);
    SkoarNoadPtr loop(SkoarNoadPtr parent);
    SkoarNoadPtr nouny_literal(SkoarNoadPtr parent);
    SkoarNoadPtr deref(SkoarNoadPtr parent);
    SkoarNoadPtr deref_prime(SkoarNoadPtr parent);
    SkoarNoadPtr msgable(SkoarNoadPtr parent);
    SkoarNoadPtr expr_prime(SkoarNoadPtr parent);
    SkoarNoadPtr assignment(SkoarNoadPtr parent);
    SkoarNoadPtr math(SkoarNoadPtr parent);
    SkoarNoadPtr boolean(SkoarNoadPtr parent);
    SkoarNoadPtr times(SkoarNoadPtr parent);
    SkoarNoadPtr settable(SkoarNoadPtr parent);
    SkoarNoadPtr msg_chain_node(SkoarNoadPtr parent);
    SkoarNoadPtr msg(SkoarNoadPtr parent);
    SkoarNoadPtr cthulhu_prime(SkoarNoadPtr parent);
    SkoarNoadPtr cond_ifs(SkoarNoadPtr parent);
    SkoarNoadPtr cond_if(SkoarNoadPtr parent);
    SkoarNoadPtr cond_ifs_suffix(SkoarNoadPtr parent);
    SkoarNoadPtr if_body(SkoarNoadPtr parent);
    SkoarNoadPtr cond_else(SkoarNoadPtr parent);
    SkoarNoadPtr loop_body(SkoarNoadPtr parent);
    SkoarNoadPtr loop_condition(SkoarNoadPtr parent);
    void sortDesirables();
};

