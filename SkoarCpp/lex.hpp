// ======================================================================
// lex.cpp - Generated by Code_Cpp_Lexer on 2017-12-03 05:39:52 for C++14
// ======================================================================
#pragma once
#include "skoarcery.hpp"


namespace ESkoarToke {
    enum Kind {
        Unknown = 0,
        Eof,
        Whitespace,
        AUGen,
        AUGenWithArgs,
        AlCoda,
        Bars,
        BooleanAnd,
        BooleanOr,
        BracketE,
        BracketS,
        Carrot,
        Cat,
        Choard,
        CmpEqNeq,
        CmpGtLt,
        Coda,
        Comment,
        CondE,
        CondIf,
        CondS,
        Crotchets,
        DUGen,
        DUGenWithArgs,
        Deref,
        Duration,
        Eighths,
        ExactBeat,
        ExactRest,
        ExpoartsE,
        ExpoartsS,
        Fairy,
        False,
        Float,
        Freq,
        HashLevel,
        Int,
        KUGen,
        KUGenWithArgs,
        LWing,
        ListE,
        ListS,
        ListSep,
        LoopE,
        LoopS,
        LoopSep,
        Lute,
        LuteWithArgs,
        MathOpAddSub,
        MathOpMulDivMod,
        MeditationE,
        MeditationS,
        MsgName,
        MsgNameWithArgs,
        MsgOp,
        NamedNoat,
        Newline,
        Nosey,
        OctaveShift,
        Quarters,
        Quavers,
        RWing,
        Semicolon,
        SkoarpionArgs,
        SkoarpionEnd,
        SkoarpionStart,
        String,
        Symbol,
        SymbolColon,
        SymbolName,
        Times,
        True,
        Tuplet,
        Voice,

    };
};

namespace ESkoarNoad {
    enum Kind {
        unknown = 0,
        toke,
        artificial,
        alias,
        al_goto,
        args,
        args_entries,
        assignment,
        beat,
        boolean_and,
        boolean_and_prime,
        boolean_expr,
        boolean_or,
        boolean_or_prime,
        branch,
        branches,
        cloasures,
        cloasures_end,
        cloasures_entries,
        cloasures_suffix,
        cmp_eq_neq,
        cmp_eq_neq_prime,
        cmp_gt_lt,
        cmp_gt_lt_prime,
        cond_else,
        cond_if,
        conditional,
        cthulhu,
        cthulhu_prime,
        deref,
        deref_prime,
        exact_beat,
        exact_rest,
        expoarts,
        expoarts_end,
        expoarts_entries,
        expoarts_suffix,
        expr,
        expr_h,
        if_body,
        listy,
        listy_entries,
        listy_suffix,
        loop,
        loop_body,
        loop_condition,
        lute,
        marker,
        math_add_sub,
        math_add_sub_prime,
        math_mul_div_mod,
        math_mul_div_mod_prime,
        meditation,
        moar_args_entries,
        moar_args_entries_prime,
        moar_cloasures_entries,
        moar_expoarts_entries,
        moar_listy_entries,
        msg,
        msg_chain_node,
        msgable,
        musical_keyword,
        musical_keyword_misc,
        nouny,
        nouny_literal,
        opt_args,
        opt_cloasures,
        opt_expoarts,
        opt_newline,
        opt_sig,
        opt_times,
        opt_voiced_phrases,
        optional_voice,
        ottavas,
        phrases,
        phrasey,
        phrasish,
        phrasishes,
        regular_beat,
        skoar,
        skoarpion,
        skrp_lines,
        skrp_moar_lines,
        skrp_suffix,
        times,
        ugen,
        ugen_simple,
        ugen_with_args,
    
};
};

#include "styles.hpp"

// --------------
// Abstract Token
// --------------
class SkoarToke {
public:
    wstring lexeme;
    size_t offs;
    size_t size;
    ESkoarToke::Kind kind;
    SkoarStyles::EStyle style;

     SkoarToke();
     SkoarToke(wstring s, size_t offs, size_t n);
    virtual      ~SkoarToke();
    // how many characters to burn from the buffer
    size_t burn();
};

// --------------
// Eof is special
// --------------
class Toke_Eof: public SkoarToke {
public:

     Toke_Eof();
     ~Toke_Eof() override;
    static     size_t burn(wstring * buf, size_t offs);
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

// ---------------------
// Whitespace is special
// ---------------------
class Toke_Whitespace: public SkoarToke {
public:
    static const wregex rgx;

    static     size_t burn(wstring * buf, size_t offs);
};

// --------------
// Everyday Tokes
// --------------
class Toke_AUGen: public SkoarToke {
public:
    static const wregex rgx;


     Toke_AUGen(wstring s, size_t offs, size_t n);
     ~Toke_AUGen() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_AUGenWithArgs: public SkoarToke {
public:
    static const wregex rgx;


     Toke_AUGenWithArgs(wstring s, size_t offs, size_t n);
     ~Toke_AUGenWithArgs() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_AlCoda: public SkoarToke {
public:
    static const wregex rgx;


     Toke_AlCoda(wstring s, size_t offs, size_t n);
     ~Toke_AlCoda() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_Bars: public SkoarToke {
public:
    static const wregex rgx;


     Toke_Bars(wstring s, size_t offs, size_t n);
     ~Toke_Bars() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_BooleanAnd: public SkoarToke {
public:
    static const wregex rgx;


     Toke_BooleanAnd(wstring s, size_t offs, size_t n);
     ~Toke_BooleanAnd() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_BooleanOr: public SkoarToke {
public:
    static const wregex rgx;


     Toke_BooleanOr(wstring s, size_t offs, size_t n);
     ~Toke_BooleanOr() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_BracketE: public SkoarToke {
public:
    static const wregex rgx;


     Toke_BracketE(wstring s, size_t offs, size_t n);
     ~Toke_BracketE() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_BracketS: public SkoarToke {
public:
    static const wregex rgx;


     Toke_BracketS(wstring s, size_t offs, size_t n);
     ~Toke_BracketS() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_Carrot: public SkoarToke {
public:
    static const wregex rgx;


     Toke_Carrot(wstring s, size_t offs, size_t n);
     ~Toke_Carrot() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_Cat: public SkoarToke {
public:
    static const wregex rgx;


     Toke_Cat(wstring s, size_t offs, size_t n);
     ~Toke_Cat() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_Choard: public SkoarToke {
public:
    static const wregex rgx;


     Toke_Choard(wstring s, size_t offs, size_t n);
     ~Toke_Choard() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_CmpEqNeq: public SkoarToke {
public:
    static const wregex rgx;


     Toke_CmpEqNeq(wstring s, size_t offs, size_t n);
     ~Toke_CmpEqNeq() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_CmpGtLt: public SkoarToke {
public:
    static const wregex rgx;


     Toke_CmpGtLt(wstring s, size_t offs, size_t n);
     ~Toke_CmpGtLt() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_Coda: public SkoarToke {
public:
    static const wregex rgx;


     Toke_Coda(wstring s, size_t offs, size_t n);
     ~Toke_Coda() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_Comment: public SkoarToke {
public:
    static const wregex rgx;


     Toke_Comment(wstring s, size_t offs, size_t n);
     ~Toke_Comment() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_CondE: public SkoarToke {
public:
    static const wregex rgx;


     Toke_CondE(wstring s, size_t offs, size_t n);
     ~Toke_CondE() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_CondIf: public SkoarToke {
public:
    static const wregex rgx;


     Toke_CondIf(wstring s, size_t offs, size_t n);
     ~Toke_CondIf() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_CondS: public SkoarToke {
public:
    static const wregex rgx;


     Toke_CondS(wstring s, size_t offs, size_t n);
     ~Toke_CondS() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_Crotchets: public SkoarToke {
public:
    static const wregex rgx;


     Toke_Crotchets(wstring s, size_t offs, size_t n);
     ~Toke_Crotchets() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_DUGen: public SkoarToke {
public:
    static const wregex rgx;


     Toke_DUGen(wstring s, size_t offs, size_t n);
     ~Toke_DUGen() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_DUGenWithArgs: public SkoarToke {
public:
    static const wregex rgx;


     Toke_DUGenWithArgs(wstring s, size_t offs, size_t n);
     ~Toke_DUGenWithArgs() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_Deref: public SkoarToke {
public:
    static const wregex rgx;


     Toke_Deref(wstring s, size_t offs, size_t n);
     ~Toke_Deref() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_Duration: public SkoarToke {
public:
    static const wregex rgx;


     Toke_Duration(wstring s, size_t offs, size_t n);
     ~Toke_Duration() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_Eighths: public SkoarToke {
public:
    static const wregex rgx;


     Toke_Eighths(wstring s, size_t offs, size_t n);
     ~Toke_Eighths() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_ExactBeat: public SkoarToke {
public:
    static const wregex rgx;


     Toke_ExactBeat(wstring s, size_t offs, size_t n);
     ~Toke_ExactBeat() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_ExactRest: public SkoarToke {
public:
    static const wregex rgx;


     Toke_ExactRest(wstring s, size_t offs, size_t n);
     ~Toke_ExactRest() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_ExpoartsE: public SkoarToke {
public:
    static const wregex rgx;


     Toke_ExpoartsE(wstring s, size_t offs, size_t n);
     ~Toke_ExpoartsE() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_ExpoartsS: public SkoarToke {
public:
    static const wregex rgx;


     Toke_ExpoartsS(wstring s, size_t offs, size_t n);
     ~Toke_ExpoartsS() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_Fairy: public SkoarToke {
public:
    static const wregex rgx;


     Toke_Fairy(wstring s, size_t offs, size_t n);
     ~Toke_Fairy() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_False: public SkoarToke {
public:
    static const wregex rgx;


     Toke_False(wstring s, size_t offs, size_t n);
     ~Toke_False() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_Float: public SkoarToke {
public:
    static const wregex rgx;


     Toke_Float(wstring s, size_t offs, size_t n);
     ~Toke_Float() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_Freq: public SkoarToke {
public:
    static const wregex rgx;


     Toke_Freq(wstring s, size_t offs, size_t n);
     ~Toke_Freq() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_HashLevel: public SkoarToke {
public:
    static const wregex rgx;


     Toke_HashLevel(wstring s, size_t offs, size_t n);
     ~Toke_HashLevel() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_Int: public SkoarToke {
public:
    static const wregex rgx;


     Toke_Int(wstring s, size_t offs, size_t n);
     ~Toke_Int() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_KUGen: public SkoarToke {
public:
    static const wregex rgx;


     Toke_KUGen(wstring s, size_t offs, size_t n);
     ~Toke_KUGen() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_KUGenWithArgs: public SkoarToke {
public:
    static const wregex rgx;


     Toke_KUGenWithArgs(wstring s, size_t offs, size_t n);
     ~Toke_KUGenWithArgs() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_LWing: public SkoarToke {
public:
    static const wregex rgx;


     Toke_LWing(wstring s, size_t offs, size_t n);
     ~Toke_LWing() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_ListE: public SkoarToke {
public:
    static const wregex rgx;


     Toke_ListE(wstring s, size_t offs, size_t n);
     ~Toke_ListE() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_ListS: public SkoarToke {
public:
    static const wregex rgx;


     Toke_ListS(wstring s, size_t offs, size_t n);
     ~Toke_ListS() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_ListSep: public SkoarToke {
public:
    static const wregex rgx;


     Toke_ListSep(wstring s, size_t offs, size_t n);
     ~Toke_ListSep() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_LoopE: public SkoarToke {
public:
    static const wregex rgx;


     Toke_LoopE(wstring s, size_t offs, size_t n);
     ~Toke_LoopE() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_LoopS: public SkoarToke {
public:
    static const wregex rgx;


     Toke_LoopS(wstring s, size_t offs, size_t n);
     ~Toke_LoopS() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_LoopSep: public SkoarToke {
public:
    static const wregex rgx;


     Toke_LoopSep(wstring s, size_t offs, size_t n);
     ~Toke_LoopSep() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_Lute: public SkoarToke {
public:
    static const wregex rgx;


     Toke_Lute(wstring s, size_t offs, size_t n);
     ~Toke_Lute() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_LuteWithArgs: public SkoarToke {
public:
    static const wregex rgx;


     Toke_LuteWithArgs(wstring s, size_t offs, size_t n);
     ~Toke_LuteWithArgs() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_MathOpAddSub: public SkoarToke {
public:
    static const wregex rgx;


     Toke_MathOpAddSub(wstring s, size_t offs, size_t n);
     ~Toke_MathOpAddSub() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_MathOpMulDivMod: public SkoarToke {
public:
    static const wregex rgx;


     Toke_MathOpMulDivMod(wstring s, size_t offs, size_t n);
     ~Toke_MathOpMulDivMod() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_MeditationE: public SkoarToke {
public:
    static const wregex rgx;


     Toke_MeditationE(wstring s, size_t offs, size_t n);
     ~Toke_MeditationE() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_MeditationS: public SkoarToke {
public:
    static const wregex rgx;


     Toke_MeditationS(wstring s, size_t offs, size_t n);
     ~Toke_MeditationS() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_MsgName: public SkoarToke {
public:
    static const wregex rgx;


     Toke_MsgName(wstring s, size_t offs, size_t n);
     ~Toke_MsgName() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_MsgNameWithArgs: public SkoarToke {
public:
    static const wregex rgx;


     Toke_MsgNameWithArgs(wstring s, size_t offs, size_t n);
     ~Toke_MsgNameWithArgs() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_MsgOp: public SkoarToke {
public:
    static const wregex rgx;


     Toke_MsgOp(wstring s, size_t offs, size_t n);
     ~Toke_MsgOp() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_NamedNoat: public SkoarToke {
public:
    static const wregex rgx;


     Toke_NamedNoat(wstring s, size_t offs, size_t n);
     ~Toke_NamedNoat() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_Newline: public SkoarToke {
public:
    static const wregex rgx;


     Toke_Newline(wstring s, size_t offs, size_t n);
     ~Toke_Newline() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_Nosey: public SkoarToke {
public:
    static const wregex rgx;


     Toke_Nosey(wstring s, size_t offs, size_t n);
     ~Toke_Nosey() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_OctaveShift: public SkoarToke {
public:
    static const wregex rgx;


     Toke_OctaveShift(wstring s, size_t offs, size_t n);
     ~Toke_OctaveShift() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_Quarters: public SkoarToke {
public:
    static const wregex rgx;


     Toke_Quarters(wstring s, size_t offs, size_t n);
     ~Toke_Quarters() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_Quavers: public SkoarToke {
public:
    static const wregex rgx;


     Toke_Quavers(wstring s, size_t offs, size_t n);
     ~Toke_Quavers() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_RWing: public SkoarToke {
public:
    static const wregex rgx;


     Toke_RWing(wstring s, size_t offs, size_t n);
     ~Toke_RWing() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_Semicolon: public SkoarToke {
public:
    static const wregex rgx;


     Toke_Semicolon(wstring s, size_t offs, size_t n);
     ~Toke_Semicolon() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_SkoarpionArgs: public SkoarToke {
public:
    static const wregex rgx;


     Toke_SkoarpionArgs(wstring s, size_t offs, size_t n);
     ~Toke_SkoarpionArgs() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_SkoarpionEnd: public SkoarToke {
public:
    static const wregex rgx;


     Toke_SkoarpionEnd(wstring s, size_t offs, size_t n);
     ~Toke_SkoarpionEnd() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_SkoarpionStart: public SkoarToke {
public:
    static const wregex rgx;


     Toke_SkoarpionStart(wstring s, size_t offs, size_t n);
     ~Toke_SkoarpionStart() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_String: public SkoarToke {
public:
    static const wregex rgx;


     Toke_String(wstring s, size_t offs, size_t n);
     ~Toke_String() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_Symbol: public SkoarToke {
public:
    static const wregex rgx;


     Toke_Symbol(wstring s, size_t offs, size_t n);
     ~Toke_Symbol() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_SymbolColon: public SkoarToke {
public:
    static const wregex rgx;


     Toke_SymbolColon(wstring s, size_t offs, size_t n);
     ~Toke_SymbolColon() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_SymbolName: public SkoarToke {
public:
    static const wregex rgx;


     Toke_SymbolName(wstring s, size_t offs, size_t n);
     ~Toke_SymbolName() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_Times: public SkoarToke {
public:
    static const wregex rgx;


     Toke_Times(wstring s, size_t offs, size_t n);
     ~Toke_Times() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_True: public SkoarToke {
public:
    static const wregex rgx;


     Toke_True(wstring s, size_t offs, size_t n);
     ~Toke_True() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_Tuplet: public SkoarToke {
public:
    static const wregex rgx;


     Toke_Tuplet(wstring s, size_t offs, size_t n);
     ~Toke_Tuplet() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_Voice: public SkoarToke {
public:
    static const wregex rgx;


     Toke_Voice(wstring s, size_t offs, size_t n);
     ~Toke_Voice() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};


class SkoarDispensary {
    map<ESkoarToke::Kind, function<SkoarToke* (wstring *buf, size_t offs)>> table;
public: 
    SkoarDispensary();   
    SkoarToke* match_toke(ESkoarToke::Kind want, wstring *buf, size_t offs);
};
