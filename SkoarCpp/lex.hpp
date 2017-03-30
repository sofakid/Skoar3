// ======================================================================
// lex.cpp - Generated by Code_Cpp_Lexer on 2017-03-30 11:19:24 for C++14
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
        AlFine,
        AlSegno,
        AssOp,
        Bars,
        BooleanOp,
        Carrot,
        Cat,
        Choard,
        Coda,
        Comment,
        CondE,
        CondIf,
        CondS,
        Crotchets,
        DUGen,
        DUGenWithArgs,
        DaCapo,
        DalSegno,
        Deref,
        Duration,
        DynFP,
        DynForte,
        DynPiano,
        DynSFZ,
        Eighths,
        ExactBeat,
        ExactRest,
        Fairy,
        False,
        Fine,
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
        Loco,
        LoopE,
        LoopS,
        LoopSep,
        Lute,
        LuteWithArgs,
        MathOp,
        MeditationE,
        MeditationS,
        MsgName,
        MsgNameWithArgs,
        MsgOp,
        NamedNoat,
        Newline,
        Nosey,
        OctaveShift,
        OttavaA,
        OttavaB,
        Quarters,
        Quavers,
        QuindicesimaA,
        QuindicesimaB,
        RWing,
        Segno,
        Semicolon,
        SkoarpionEnd,
        SkoarpionSep,
        SkoarpionStart,
        SkoarpionStartWithSig,
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
        al_x,
        arg_expr,
        arg_listy,
        arg_listy_entries,
        arg_listy_suffix,
        assignment,
        beat,
        boolean,
        boolean_expr,
        branch,
        branches,
        coda,
        cond_else,
        cond_if,
        cond_ifs,
        cond_ifs_suffix,
        conditional,
        cthulhu,
        cthulhu_prime,
        dal_goto,
        deref,
        deref_prime,
        dynamic,
        exact_beat,
        exact_rest,
        expr,
        expr_prime,
        if_body,
        listy,
        listy_entries,
        listy_suffix,
        loop,
        loop_body,
        loop_condition,
        lute,
        marker,
        math,
        meditation,
        moar_arg_listy_entries,
        moar_listy_entries,
        msg,
        msg_chain_node,
        msgable,
        musical_keyword,
        musical_keyword_misc,
        nouny,
        nouny_literal,
        opt_voiced_phrases,
        optional_al_coda,
        optional_voice,
        ottavas,
        phrases,
        phrasey,
        regular_beat,
        settable,
        skoar,
        skoarpion,
        skrp_lines,
        skrp_moar_lines,
        skrp_sig,
        skrp_sig_prime,
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

class Toke_AlFine: public SkoarToke {
public:
    static const wregex rgx;


     Toke_AlFine(wstring s, size_t offs, size_t n);
     ~Toke_AlFine() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_AlSegno: public SkoarToke {
public:
    static const wregex rgx;


     Toke_AlSegno(wstring s, size_t offs, size_t n);
     ~Toke_AlSegno() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_AssOp: public SkoarToke {
public:
    static const wregex rgx;


     Toke_AssOp(wstring s, size_t offs, size_t n);
     ~Toke_AssOp() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_Bars: public SkoarToke {
public:
    static const wregex rgx;


     Toke_Bars(wstring s, size_t offs, size_t n);
     ~Toke_Bars() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_BooleanOp: public SkoarToke {
public:
    static const wregex rgx;


     Toke_BooleanOp(wstring s, size_t offs, size_t n);
     ~Toke_BooleanOp() override;
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

class Toke_DaCapo: public SkoarToke {
public:
    static const wregex rgx;


     Toke_DaCapo(wstring s, size_t offs, size_t n);
     ~Toke_DaCapo() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_DalSegno: public SkoarToke {
public:
    static const wregex rgx;


     Toke_DalSegno(wstring s, size_t offs, size_t n);
     ~Toke_DalSegno() override;
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

class Toke_DynFP: public SkoarToke {
public:
    static const wregex rgx;


     Toke_DynFP(wstring s, size_t offs, size_t n);
     ~Toke_DynFP() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_DynForte: public SkoarToke {
public:
    static const wregex rgx;


     Toke_DynForte(wstring s, size_t offs, size_t n);
     ~Toke_DynForte() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_DynPiano: public SkoarToke {
public:
    static const wregex rgx;


     Toke_DynPiano(wstring s, size_t offs, size_t n);
     ~Toke_DynPiano() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_DynSFZ: public SkoarToke {
public:
    static const wregex rgx;


     Toke_DynSFZ(wstring s, size_t offs, size_t n);
     ~Toke_DynSFZ() override;
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

class Toke_Fine: public SkoarToke {
public:
    static const wregex rgx;


     Toke_Fine(wstring s, size_t offs, size_t n);
     ~Toke_Fine() override;
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

class Toke_Loco: public SkoarToke {
public:
    static const wregex rgx;


     Toke_Loco(wstring s, size_t offs, size_t n);
     ~Toke_Loco() override;
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

class Toke_MathOp: public SkoarToke {
public:
    static const wregex rgx;


     Toke_MathOp(wstring s, size_t offs, size_t n);
     ~Toke_MathOp() override;
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

class Toke_OttavaA: public SkoarToke {
public:
    static const wregex rgx;


     Toke_OttavaA(wstring s, size_t offs, size_t n);
     ~Toke_OttavaA() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_OttavaB: public SkoarToke {
public:
    static const wregex rgx;


     Toke_OttavaB(wstring s, size_t offs, size_t n);
     ~Toke_OttavaB() override;
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

class Toke_QuindicesimaA: public SkoarToke {
public:
    static const wregex rgx;


     Toke_QuindicesimaA(wstring s, size_t offs, size_t n);
     ~Toke_QuindicesimaA() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_QuindicesimaB: public SkoarToke {
public:
    static const wregex rgx;


     Toke_QuindicesimaB(wstring s, size_t offs, size_t n);
     ~Toke_QuindicesimaB() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_RWing: public SkoarToke {
public:
    static const wregex rgx;


     Toke_RWing(wstring s, size_t offs, size_t n);
     ~Toke_RWing() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_Segno: public SkoarToke {
public:
    static const wregex rgx;


     Toke_Segno(wstring s, size_t offs, size_t n);
     ~Toke_Segno() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_Semicolon: public SkoarToke {
public:
    static const wregex rgx;


     Toke_Semicolon(wstring s, size_t offs, size_t n);
     ~Toke_Semicolon() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_SkoarpionEnd: public SkoarToke {
public:
    static const wregex rgx;


     Toke_SkoarpionEnd(wstring s, size_t offs, size_t n);
     ~Toke_SkoarpionEnd() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_SkoarpionSep: public SkoarToke {
public:
    static const wregex rgx;


     Toke_SkoarpionSep(wstring s, size_t offs, size_t n);
     ~Toke_SkoarpionSep() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_SkoarpionStart: public SkoarToke {
public:
    static const wregex rgx;


     Toke_SkoarpionStart(wstring s, size_t offs, size_t n);
     ~Toke_SkoarpionStart() override;
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_SkoarpionStartWithSig: public SkoarToke {
public:
    static const wregex rgx;


     Toke_SkoarpionStartWithSig(wstring s, size_t offs, size_t n);
     ~Toke_SkoarpionStartWithSig() override;
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
