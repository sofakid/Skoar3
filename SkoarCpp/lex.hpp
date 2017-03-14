// ======================================================================
// lex.cpp - Generated by Code_Cpp_Lexer on 2017-03-14 02:07:14 for C++14
// ======================================================================
#pragma once
#include "skoarcery.hpp"


namespace ESkoarToke {
    enum Kind {
        Unknown = 0,
        Eof,
        Whitespace,
        AlCoda,
        AlFine,
        AlSegno,
        ArgSpec,
        AssOp,
        Bars,
        BooleanOp,
        Caesura,
        Carrot,
        Choard,
        Coda,
        Comment,
        CondE,
        CondIf,
        CondS,
        Crap,
        Crotchets,
        DaCapo,
        DalSegno,
        Deref,
        DynFP,
        DynForte,
        DynPiano,
        DynSFZ,
        Eighths,
        Fairy,
        False,
        Fine,
        Float,
        Freq,
        HashLevel,
        Int,
        LWing,
        ListE,
        ListS,
        ListSep,
        Loco,
        LoopE,
        LoopS,
        LoopSep,
        MathOp,
        Meter,
        MsgName,
        MsgNameWithArgs,
        MsgOp,
        NamedNoat,
        Newline,
        Nosey,
        OctaveShift,
        OttavaA,
        OttavaB,
        PedalDown,
        PedalUp,
        Portamento,
        Quarters,
        Quavers,
        QuindicesimaA,
        QuindicesimaB,
        RWing,
        Rep,
        Segno,
        Semicolon,
        SkoarpionEnd,
        SkoarpionSep,
        SkoarpionStart,
        Slash,
        String,
        Symbol,
        SymbolName,
        Times,
        True,
        Tuplet,
        Voice,
        Volta,

    };
};

namespace ESkoarNoad {
    enum Kind {
        unknown = 0,
        toke,
        artificial,
        args,
        al_x,
        assignment,
        beat,
        boolean,
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
        expr,
        expr_prime,
        if_body,
        listy,
        listy_entries,
        listy_suffix,
        loop,
        loop_body,
        loop_condition,
        marker,
        math,
        moar_listy_entries,
        msg,
        msg_chain_node,
        msgable,
        musical_keyword,
        musical_keyword_misc,
        nouny,
        nouny_literal,
        opt_arg_spec,
        optional_al_coda,
        optional_voice,
        ottavas,
        pedally,
        phrases,
        phrasey,
        settable,
        skoar,
        skoarpion,
        skrp_lines,
        skrp_moar_lines,
        skrp_sig,
        skrp_suffix,
        times,
    
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
     ~SkoarToke();
    // how many characters to burn from the buffer
    size_t burn();
};

// --------------
// Eof is special
// --------------
class Toke_Eof: public SkoarToke {
public:

     Toke_Eof();
     ~Toke_Eof();
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
class Toke_AlCoda: public SkoarToke {
public:
    static const wregex rgx;


     Toke_AlCoda(wstring s, size_t offs, size_t n);
     ~Toke_AlCoda();
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_AlFine: public SkoarToke {
public:
    static const wregex rgx;


     Toke_AlFine(wstring s, size_t offs, size_t n);
     ~Toke_AlFine();
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_AlSegno: public SkoarToke {
public:
    static const wregex rgx;


     Toke_AlSegno(wstring s, size_t offs, size_t n);
     ~Toke_AlSegno();
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_ArgSpec: public SkoarToke {
public:
    static const wregex rgx;


     Toke_ArgSpec(wstring s, size_t offs, size_t n);
     ~Toke_ArgSpec();
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_AssOp: public SkoarToke {
public:
    static const wregex rgx;


     Toke_AssOp(wstring s, size_t offs, size_t n);
     ~Toke_AssOp();
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_Bars: public SkoarToke {
public:
    static const wregex rgx;


     Toke_Bars(wstring s, size_t offs, size_t n);
     ~Toke_Bars();
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_BooleanOp: public SkoarToke {
public:
    static const wregex rgx;


     Toke_BooleanOp(wstring s, size_t offs, size_t n);
     ~Toke_BooleanOp();
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_Caesura: public SkoarToke {
public:
    static const wregex rgx;


     Toke_Caesura(wstring s, size_t offs, size_t n);
     ~Toke_Caesura();
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_Carrot: public SkoarToke {
public:
    static const wregex rgx;


     Toke_Carrot(wstring s, size_t offs, size_t n);
     ~Toke_Carrot();
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_Choard: public SkoarToke {
public:
    static const wregex rgx;


     Toke_Choard(wstring s, size_t offs, size_t n);
     ~Toke_Choard();
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_Coda: public SkoarToke {
public:
    static const wregex rgx;


     Toke_Coda(wstring s, size_t offs, size_t n);
     ~Toke_Coda();
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_Comment: public SkoarToke {
public:
    static const wregex rgx;


     Toke_Comment(wstring s, size_t offs, size_t n);
     ~Toke_Comment();
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_CondE: public SkoarToke {
public:
    static const wregex rgx;


     Toke_CondE(wstring s, size_t offs, size_t n);
     ~Toke_CondE();
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_CondIf: public SkoarToke {
public:
    static const wregex rgx;


     Toke_CondIf(wstring s, size_t offs, size_t n);
     ~Toke_CondIf();
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_CondS: public SkoarToke {
public:
    static const wregex rgx;


     Toke_CondS(wstring s, size_t offs, size_t n);
     ~Toke_CondS();
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_Crap: public SkoarToke {
public:
    static const wregex rgx;


     Toke_Crap(wstring s, size_t offs, size_t n);
     ~Toke_Crap();
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_Crotchets: public SkoarToke {
public:
    static const wregex rgx;


     Toke_Crotchets(wstring s, size_t offs, size_t n);
     ~Toke_Crotchets();
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_DaCapo: public SkoarToke {
public:
    static const wregex rgx;


     Toke_DaCapo(wstring s, size_t offs, size_t n);
     ~Toke_DaCapo();
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_DalSegno: public SkoarToke {
public:
    static const wregex rgx;


     Toke_DalSegno(wstring s, size_t offs, size_t n);
     ~Toke_DalSegno();
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_Deref: public SkoarToke {
public:
    static const wregex rgx;


     Toke_Deref(wstring s, size_t offs, size_t n);
     ~Toke_Deref();
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_DynFP: public SkoarToke {
public:
    static const wregex rgx;


     Toke_DynFP(wstring s, size_t offs, size_t n);
     ~Toke_DynFP();
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_DynForte: public SkoarToke {
public:
    static const wregex rgx;


     Toke_DynForte(wstring s, size_t offs, size_t n);
     ~Toke_DynForte();
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_DynPiano: public SkoarToke {
public:
    static const wregex rgx;


     Toke_DynPiano(wstring s, size_t offs, size_t n);
     ~Toke_DynPiano();
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_DynSFZ: public SkoarToke {
public:
    static const wregex rgx;


     Toke_DynSFZ(wstring s, size_t offs, size_t n);
     ~Toke_DynSFZ();
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_Eighths: public SkoarToke {
public:
    static const wregex rgx;


     Toke_Eighths(wstring s, size_t offs, size_t n);
     ~Toke_Eighths();
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_Fairy: public SkoarToke {
public:
    static const wregex rgx;


     Toke_Fairy(wstring s, size_t offs, size_t n);
     ~Toke_Fairy();
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_False: public SkoarToke {
public:
    static const wregex rgx;


     Toke_False(wstring s, size_t offs, size_t n);
     ~Toke_False();
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_Fine: public SkoarToke {
public:
    static const wregex rgx;


     Toke_Fine(wstring s, size_t offs, size_t n);
     ~Toke_Fine();
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_Float: public SkoarToke {
public:
    static const wregex rgx;


     Toke_Float(wstring s, size_t offs, size_t n);
     ~Toke_Float();
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_Freq: public SkoarToke {
public:
    static const wregex rgx;


     Toke_Freq(wstring s, size_t offs, size_t n);
     ~Toke_Freq();
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_HashLevel: public SkoarToke {
public:
    static const wregex rgx;


     Toke_HashLevel(wstring s, size_t offs, size_t n);
     ~Toke_HashLevel();
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_Int: public SkoarToke {
public:
    static const wregex rgx;


     Toke_Int(wstring s, size_t offs, size_t n);
     ~Toke_Int();
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_LWing: public SkoarToke {
public:
    static const wregex rgx;


     Toke_LWing(wstring s, size_t offs, size_t n);
     ~Toke_LWing();
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_ListE: public SkoarToke {
public:
    static const wregex rgx;


     Toke_ListE(wstring s, size_t offs, size_t n);
     ~Toke_ListE();
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_ListS: public SkoarToke {
public:
    static const wregex rgx;


     Toke_ListS(wstring s, size_t offs, size_t n);
     ~Toke_ListS();
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_ListSep: public SkoarToke {
public:
    static const wregex rgx;


     Toke_ListSep(wstring s, size_t offs, size_t n);
     ~Toke_ListSep();
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_Loco: public SkoarToke {
public:
    static const wregex rgx;


     Toke_Loco(wstring s, size_t offs, size_t n);
     ~Toke_Loco();
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_LoopE: public SkoarToke {
public:
    static const wregex rgx;


     Toke_LoopE(wstring s, size_t offs, size_t n);
     ~Toke_LoopE();
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_LoopS: public SkoarToke {
public:
    static const wregex rgx;


     Toke_LoopS(wstring s, size_t offs, size_t n);
     ~Toke_LoopS();
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_LoopSep: public SkoarToke {
public:
    static const wregex rgx;


     Toke_LoopSep(wstring s, size_t offs, size_t n);
     ~Toke_LoopSep();
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_MathOp: public SkoarToke {
public:
    static const wregex rgx;


     Toke_MathOp(wstring s, size_t offs, size_t n);
     ~Toke_MathOp();
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_Meter: public SkoarToke {
public:
    static const wregex rgx;


     Toke_Meter(wstring s, size_t offs, size_t n);
     ~Toke_Meter();
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_MsgName: public SkoarToke {
public:
    static const wregex rgx;


     Toke_MsgName(wstring s, size_t offs, size_t n);
     ~Toke_MsgName();
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_MsgNameWithArgs: public SkoarToke {
public:
    static const wregex rgx;


     Toke_MsgNameWithArgs(wstring s, size_t offs, size_t n);
     ~Toke_MsgNameWithArgs();
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_MsgOp: public SkoarToke {
public:
    static const wregex rgx;


     Toke_MsgOp(wstring s, size_t offs, size_t n);
     ~Toke_MsgOp();
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_NamedNoat: public SkoarToke {
public:
    static const wregex rgx;


     Toke_NamedNoat(wstring s, size_t offs, size_t n);
     ~Toke_NamedNoat();
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_Newline: public SkoarToke {
public:
    static const wregex rgx;


     Toke_Newline(wstring s, size_t offs, size_t n);
     ~Toke_Newline();
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_Nosey: public SkoarToke {
public:
    static const wregex rgx;


     Toke_Nosey(wstring s, size_t offs, size_t n);
     ~Toke_Nosey();
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_OctaveShift: public SkoarToke {
public:
    static const wregex rgx;


     Toke_OctaveShift(wstring s, size_t offs, size_t n);
     ~Toke_OctaveShift();
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_OttavaA: public SkoarToke {
public:
    static const wregex rgx;


     Toke_OttavaA(wstring s, size_t offs, size_t n);
     ~Toke_OttavaA();
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_OttavaB: public SkoarToke {
public:
    static const wregex rgx;


     Toke_OttavaB(wstring s, size_t offs, size_t n);
     ~Toke_OttavaB();
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_PedalDown: public SkoarToke {
public:
    static const wregex rgx;


     Toke_PedalDown(wstring s, size_t offs, size_t n);
     ~Toke_PedalDown();
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_PedalUp: public SkoarToke {
public:
    static const wregex rgx;


     Toke_PedalUp(wstring s, size_t offs, size_t n);
     ~Toke_PedalUp();
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_Portamento: public SkoarToke {
public:
    static const wregex rgx;


     Toke_Portamento(wstring s, size_t offs, size_t n);
     ~Toke_Portamento();
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_Quarters: public SkoarToke {
public:
    static const wregex rgx;


     Toke_Quarters(wstring s, size_t offs, size_t n);
     ~Toke_Quarters();
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_Quavers: public SkoarToke {
public:
    static const wregex rgx;


     Toke_Quavers(wstring s, size_t offs, size_t n);
     ~Toke_Quavers();
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_QuindicesimaA: public SkoarToke {
public:
    static const wregex rgx;


     Toke_QuindicesimaA(wstring s, size_t offs, size_t n);
     ~Toke_QuindicesimaA();
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_QuindicesimaB: public SkoarToke {
public:
    static const wregex rgx;


     Toke_QuindicesimaB(wstring s, size_t offs, size_t n);
     ~Toke_QuindicesimaB();
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_RWing: public SkoarToke {
public:
    static const wregex rgx;


     Toke_RWing(wstring s, size_t offs, size_t n);
     ~Toke_RWing();
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_Rep: public SkoarToke {
public:
    static const wregex rgx;


     Toke_Rep(wstring s, size_t offs, size_t n);
     ~Toke_Rep();
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_Segno: public SkoarToke {
public:
    static const wregex rgx;


     Toke_Segno(wstring s, size_t offs, size_t n);
     ~Toke_Segno();
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_Semicolon: public SkoarToke {
public:
    static const wregex rgx;


     Toke_Semicolon(wstring s, size_t offs, size_t n);
     ~Toke_Semicolon();
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_SkoarpionEnd: public SkoarToke {
public:
    static const wregex rgx;


     Toke_SkoarpionEnd(wstring s, size_t offs, size_t n);
     ~Toke_SkoarpionEnd();
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_SkoarpionSep: public SkoarToke {
public:
    static const wregex rgx;


     Toke_SkoarpionSep(wstring s, size_t offs, size_t n);
     ~Toke_SkoarpionSep();
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_SkoarpionStart: public SkoarToke {
public:
    static const wregex rgx;


     Toke_SkoarpionStart(wstring s, size_t offs, size_t n);
     ~Toke_SkoarpionStart();
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_Slash: public SkoarToke {
public:
    static const wregex rgx;


     Toke_Slash(wstring s, size_t offs, size_t n);
     ~Toke_Slash();
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_String: public SkoarToke {
public:
    static const wregex rgx;


     Toke_String(wstring s, size_t offs, size_t n);
     ~Toke_String();
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_Symbol: public SkoarToke {
public:
    static const wregex rgx;


     Toke_Symbol(wstring s, size_t offs, size_t n);
     ~Toke_Symbol();
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_SymbolName: public SkoarToke {
public:
    static const wregex rgx;


     Toke_SymbolName(wstring s, size_t offs, size_t n);
     ~Toke_SymbolName();
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_Times: public SkoarToke {
public:
    static const wregex rgx;


     Toke_Times(wstring s, size_t offs, size_t n);
     ~Toke_Times();
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_True: public SkoarToke {
public:
    static const wregex rgx;


     Toke_True(wstring s, size_t offs, size_t n);
     ~Toke_True();
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_Tuplet: public SkoarToke {
public:
    static const wregex rgx;


     Toke_Tuplet(wstring s, size_t offs, size_t n);
     ~Toke_Tuplet();
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_Voice: public SkoarToke {
public:
    static const wregex rgx;


     Toke_Voice(wstring s, size_t offs, size_t n);
     ~Toke_Voice();
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};

class Toke_Volta: public SkoarToke {
public:
    static const wregex rgx;


     Toke_Volta(wstring s, size_t offs, size_t n);
     ~Toke_Volta();
    static     SkoarToke* match_toke(wstring * buf, size_t offs);
};


class SkoarDispensary {
    map<ESkoarToke::Kind, function<SkoarToke* (wstring *buf, size_t offs)>> table;
public: 
    SkoarDispensary();   
    SkoarToke* match_toke(ESkoarToke::Kind want, wstring *buf, size_t offs);
};
