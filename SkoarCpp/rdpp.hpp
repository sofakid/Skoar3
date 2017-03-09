// =====================================================================================================================
// rdpp.hpp - Generated by Code_Parser_Cpp - Create Recursive Descent Predictive Parser on 2017-03-09 23:05:59 for C++14
// =====================================================================================================================
#pragma once
#include "skoarcery.hpp"
#include "noad_fwd.hpp"
#include "toker.hpp"

struct SkoarStats {

    SkoarStats();

    map<ESkoarToke::Kind, float> tokeFreq;
    list<ESkoarToke::Kind> *desirables;

};

class SkoarParser {
public:
    void fail();
    void fail_too_deep();

    SkoarToker *toker;
    int deep;
     SkoarParser(SkoarToker * tokr);
    SkoarNoad* branches(SkoarNoad* parent);
    SkoarNoad* skoar(SkoarNoad* parent);
    SkoarNoad* branch(SkoarNoad* parent);
    SkoarNoad* optional_voice(SkoarNoad* parent);
    SkoarNoad* phrases(SkoarNoad* parent);
    SkoarNoad* phrasey(SkoarNoad* parent);
    SkoarNoad* marker(SkoarNoad* parent);
    SkoarNoad* expr(SkoarNoad* parent);
    SkoarNoad* dal_goto(SkoarNoad* parent);
    SkoarNoad* beat(SkoarNoad* parent);
    SkoarNoad* skrp_sig(SkoarNoad* parent);
    SkoarNoad* skrp_suffix(SkoarNoad* parent);
    SkoarNoad* skoarpion(SkoarNoad* parent);
    SkoarNoad* opt_arg_spec(SkoarNoad* parent);
    SkoarNoad* skrp_lines(SkoarNoad* parent);
    SkoarNoad* skrp_moar_lines(SkoarNoad* parent);
    SkoarNoad* listy_suffix(SkoarNoad* parent);
    SkoarNoad* listy(SkoarNoad* parent);
    SkoarNoad* listy_entries(SkoarNoad* parent);
    SkoarNoad* moar_listy_entries(SkoarNoad* parent);
    SkoarNoad* coda(SkoarNoad* parent);
    SkoarNoad* optional_al_coda(SkoarNoad* parent);
    SkoarNoad* al_x(SkoarNoad* parent);
    SkoarNoad* dynamic(SkoarNoad* parent);
    SkoarNoad* musical_keyword(SkoarNoad* parent);
    SkoarNoad* ottavas(SkoarNoad* parent);
    SkoarNoad* pedally(SkoarNoad* parent);
    SkoarNoad* musical_keyword_misc(SkoarNoad* parent);
    SkoarNoad* cthulhu(SkoarNoad* parent);
    SkoarNoad* nouny(SkoarNoad* parent);
    SkoarNoad* conditional(SkoarNoad* parent);
    SkoarNoad* loop(SkoarNoad* parent);
    SkoarNoad* nouny_literal(SkoarNoad* parent);
    SkoarNoad* deref(SkoarNoad* parent);
    SkoarNoad* deref_prime(SkoarNoad* parent);
    SkoarNoad* msgable(SkoarNoad* parent);
    SkoarNoad* expr_prime(SkoarNoad* parent);
    SkoarNoad* assignment(SkoarNoad* parent);
    SkoarNoad* math(SkoarNoad* parent);
    SkoarNoad* boolean(SkoarNoad* parent);
    SkoarNoad* times(SkoarNoad* parent);
    SkoarNoad* settable(SkoarNoad* parent);
    SkoarNoad* msg_chain_node(SkoarNoad* parent);
    SkoarNoad* msg(SkoarNoad* parent);
    SkoarNoad* cthulhu_prime(SkoarNoad* parent);
    SkoarNoad* cond_ifs(SkoarNoad* parent);
    SkoarNoad* cond_if(SkoarNoad* parent);
    SkoarNoad* cond_ifs_suffix(SkoarNoad* parent);
    SkoarNoad* if_body(SkoarNoad* parent);
    SkoarNoad* cond_else(SkoarNoad* parent);
    SkoarNoad* loop_body(SkoarNoad* parent);
    SkoarNoad* loop_condition(SkoarNoad* parent);
    void sortDesirables();
};

