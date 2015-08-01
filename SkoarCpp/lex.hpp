// ======================================================================
// lex.cpp - Generated by Code_Cpp_Lexer on 2015-08-01 00:03:39 for C++14
// ======================================================================
#pragma once
#include "skoarcery.hpp"
// --------------
// Abstract Token
// --------------
class SkoarToke {
public:
    static SkoarToke * aninstance;
    static     SkoarToke * instance();
    string * lexeme;
    size_t size;

     SkoarToke();
     SkoarToke(string * s, size_t n);
    // how many characters to burn from the buffer
    size_t burn();
    // match requested toke
    SkoarToke* match_toke(string * buf, size_t offs);
};

// --------------
// EOF is special
// --------------
class Toke_EOF: public SkoarToke {
public:
    static Toke_EOF * aninstance;
    static     Toke_EOF * instance();

     Toke_EOF();
    static     size_t burn(string * buf, size_t offs);
    static     SkoarToke* match_toke(string * buf, size_t offs);
};

// ---------------------
// Whitespace is special
// ---------------------
class Toke_Whitespace: public SkoarToke {
public:
    static const regex rgx;

    static Toke_Whitespace * aninstance;
     Toke_Whitespace();
    static     Toke_Whitespace * instance();
    static     size_t burn(string * buf, size_t offs);
};

// --------------
// Everyday Tokes
// --------------
class Toke_DynFP: public SkoarToke {
public:
    static const regex rgx;

    static Toke_DynFP * aninstance;
    static     Toke_DynFP * instance();

     Toke_DynFP();
     Toke_DynFP(string * s, size_t n);
    static     SkoarToke* match_toke(string * buf, size_t offs);
};

class Toke_Semicolon: public SkoarToke {
public:
    static const regex rgx;

    static Toke_Semicolon * aninstance;
    static     Toke_Semicolon * instance();

     Toke_Semicolon();
     Toke_Semicolon(string * s, size_t n);
    static     SkoarToke* match_toke(string * buf, size_t offs);
};

class Toke_Slash: public SkoarToke {
public:
    static const regex rgx;

    static Toke_Slash * aninstance;
    static     Toke_Slash * instance();

     Toke_Slash();
     Toke_Slash(string * s, size_t n);
    static     SkoarToke* match_toke(string * buf, size_t offs);
};

class Toke_OctaveShift: public SkoarToke {
public:
    static const regex rgx;

    static Toke_OctaveShift * aninstance;
    static     Toke_OctaveShift * instance();

     Toke_OctaveShift();
     Toke_OctaveShift(string * s, size_t n);
    static     SkoarToke* match_toke(string * buf, size_t offs);
};

class Toke_Loco: public SkoarToke {
public:
    static const regex rgx;

    static Toke_Loco * aninstance;
    static     Toke_Loco * instance();

     Toke_Loco();
     Toke_Loco(string * s, size_t n);
    static     SkoarToke* match_toke(string * buf, size_t offs);
};

class Toke_PedalUp: public SkoarToke {
public:
    static const regex rgx;

    static Toke_PedalUp * aninstance;
    static     Toke_PedalUp * instance();

     Toke_PedalUp();
     Toke_PedalUp(string * s, size_t n);
    static     SkoarToke* match_toke(string * buf, size_t offs);
};

class Toke_Crotchets: public SkoarToke {
public:
    static const regex rgx;

    static Toke_Crotchets * aninstance;
    static     Toke_Crotchets * instance();

     Toke_Crotchets();
     Toke_Crotchets(string * s, size_t n);
    static     SkoarToke* match_toke(string * buf, size_t offs);
};

class Toke_DynForte: public SkoarToke {
public:
    static const regex rgx;

    static Toke_DynForte * aninstance;
    static     Toke_DynForte * instance();

     Toke_DynForte();
     Toke_DynForte(string * s, size_t n);
    static     SkoarToke* match_toke(string * buf, size_t offs);
};

class Toke_CondE: public SkoarToke {
public:
    static const regex rgx;

    static Toke_CondE * aninstance;
    static     Toke_CondE * instance();

     Toke_CondE();
     Toke_CondE(string * s, size_t n);
    static     SkoarToke* match_toke(string * buf, size_t offs);
};

class Toke_Float: public SkoarToke {
public:
    static const regex rgx;

    static Toke_Float * aninstance;
    static     Toke_Float * instance();

     Toke_Float();
     Toke_Float(string * s, size_t n);
    static     SkoarToke* match_toke(string * buf, size_t offs);
};

class Toke_SymbolName: public SkoarToke {
public:
    static const regex rgx;

    static Toke_SymbolName * aninstance;
    static     Toke_SymbolName * instance();

     Toke_SymbolName();
     Toke_SymbolName(string * s, size_t n);
    static     SkoarToke* match_toke(string * buf, size_t offs);
};

class Toke_QuindicesimaB: public SkoarToke {
public:
    static const regex rgx;

    static Toke_QuindicesimaB * aninstance;
    static     Toke_QuindicesimaB * instance();

     Toke_QuindicesimaB();
     Toke_QuindicesimaB(string * s, size_t n);
    static     SkoarToke* match_toke(string * buf, size_t offs);
};

class Toke_Segno: public SkoarToke {
public:
    static const regex rgx;

    static Toke_Segno * aninstance;
    static     Toke_Segno * instance();

     Toke_Segno();
     Toke_Segno(string * s, size_t n);
    static     SkoarToke* match_toke(string * buf, size_t offs);
};

class Toke_DynPiano: public SkoarToke {
public:
    static const regex rgx;

    static Toke_DynPiano * aninstance;
    static     Toke_DynPiano * instance();

     Toke_DynPiano();
     Toke_DynPiano(string * s, size_t n);
    static     SkoarToke* match_toke(string * buf, size_t offs);
};

class Toke_RWing: public SkoarToke {
public:
    static const regex rgx;

    static Toke_RWing * aninstance;
    static     Toke_RWing * instance();

     Toke_RWing();
     Toke_RWing(string * s, size_t n);
    static     SkoarToke* match_toke(string * buf, size_t offs);
};

class Toke_MsgName: public SkoarToke {
public:
    static const regex rgx;

    static Toke_MsgName * aninstance;
    static     Toke_MsgName * instance();

     Toke_MsgName();
     Toke_MsgName(string * s, size_t n);
    static     SkoarToke* match_toke(string * buf, size_t offs);
};

class Toke_NamedNoat: public SkoarToke {
public:
    static const regex rgx;

    static Toke_NamedNoat * aninstance;
    static     Toke_NamedNoat * instance();

     Toke_NamedNoat();
     Toke_NamedNoat(string * s, size_t n);
    static     SkoarToke* match_toke(string * buf, size_t offs);
};

class Toke_MsgNameWithArgs: public SkoarToke {
public:
    static const regex rgx;

    static Toke_MsgNameWithArgs * aninstance;
    static     Toke_MsgNameWithArgs * instance();

     Toke_MsgNameWithArgs();
     Toke_MsgNameWithArgs(string * s, size_t n);
    static     SkoarToke* match_toke(string * buf, size_t offs);
};

class Toke_ListE: public SkoarToke {
public:
    static const regex rgx;

    static Toke_ListE * aninstance;
    static     Toke_ListE * instance();

     Toke_ListE();
     Toke_ListE(string * s, size_t n);
    static     SkoarToke* match_toke(string * buf, size_t offs);
};

class Toke_Coda: public SkoarToke {
public:
    static const regex rgx;

    static Toke_Coda * aninstance;
    static     Toke_Coda * instance();

     Toke_Coda();
     Toke_Coda(string * s, size_t n);
    static     SkoarToke* match_toke(string * buf, size_t offs);
};

class Toke_AlCoda: public SkoarToke {
public:
    static const regex rgx;

    static Toke_AlCoda * aninstance;
    static     Toke_AlCoda * instance();

     Toke_AlCoda();
     Toke_AlCoda(string * s, size_t n);
    static     SkoarToke* match_toke(string * buf, size_t offs);
};

class Toke_Portamento: public SkoarToke {
public:
    static const regex rgx;

    static Toke_Portamento * aninstance;
    static     Toke_Portamento * instance();

     Toke_Portamento();
     Toke_Portamento(string * s, size_t n);
    static     SkoarToke* match_toke(string * buf, size_t offs);
};

class Toke_LoopS: public SkoarToke {
public:
    static const regex rgx;

    static Toke_LoopS * aninstance;
    static     Toke_LoopS * instance();

     Toke_LoopS();
     Toke_LoopS(string * s, size_t n);
    static     SkoarToke* match_toke(string * buf, size_t offs);
};

class Toke_Newline: public SkoarToke {
public:
    static const regex rgx;

    static Toke_Newline * aninstance;
    static     Toke_Newline * instance();

     Toke_Newline();
     Toke_Newline(string * s, size_t n);
    static     SkoarToke* match_toke(string * buf, size_t offs);
};

class Toke_AlSegno: public SkoarToke {
public:
    static const regex rgx;

    static Toke_AlSegno * aninstance;
    static     Toke_AlSegno * instance();

     Toke_AlSegno();
     Toke_AlSegno(string * s, size_t n);
    static     SkoarToke* match_toke(string * buf, size_t offs);
};

class Toke_Quarters: public SkoarToke {
public:
    static const regex rgx;

    static Toke_Quarters * aninstance;
    static     Toke_Quarters * instance();

     Toke_Quarters();
     Toke_Quarters(string * s, size_t n);
    static     SkoarToke* match_toke(string * buf, size_t offs);
};

class Toke_CondS: public SkoarToke {
public:
    static const regex rgx;

    static Toke_CondS * aninstance;
    static     Toke_CondS * instance();

     Toke_CondS();
     Toke_CondS(string * s, size_t n);
    static     SkoarToke* match_toke(string * buf, size_t offs);
};

class Toke_Freq: public SkoarToke {
public:
    static const regex rgx;

    static Toke_Freq * aninstance;
    static     Toke_Freq * instance();

     Toke_Freq();
     Toke_Freq(string * s, size_t n);
    static     SkoarToke* match_toke(string * buf, size_t offs);
};

class Toke_Rep: public SkoarToke {
public:
    static const regex rgx;

    static Toke_Rep * aninstance;
    static     Toke_Rep * instance();

     Toke_Rep();
     Toke_Rep(string * s, size_t n);
    static     SkoarToke* match_toke(string * buf, size_t offs);
};

class Toke_ListS: public SkoarToke {
public:
    static const regex rgx;

    static Toke_ListS * aninstance;
    static     Toke_ListS * instance();

     Toke_ListS();
     Toke_ListS(string * s, size_t n);
    static     SkoarToke* match_toke(string * buf, size_t offs);
};

class Toke_Bars: public SkoarToke {
public:
    static const regex rgx;

    static Toke_Bars * aninstance;
    static     Toke_Bars * instance();

     Toke_Bars();
     Toke_Bars(string * s, size_t n);
    static     SkoarToke* match_toke(string * buf, size_t offs);
};

class Toke_ListSep: public SkoarToke {
public:
    static const regex rgx;

    static Toke_ListSep * aninstance;
    static     Toke_ListSep * instance();

     Toke_ListSep();
     Toke_ListSep(string * s, size_t n);
    static     SkoarToke* match_toke(string * buf, size_t offs);
};

class Toke_SkoarpionEnd: public SkoarToke {
public:
    static const regex rgx;

    static Toke_SkoarpionEnd * aninstance;
    static     Toke_SkoarpionEnd * instance();

     Toke_SkoarpionEnd();
     Toke_SkoarpionEnd(string * s, size_t n);
    static     SkoarToke* match_toke(string * buf, size_t offs);
};

class Toke_Eighths: public SkoarToke {
public:
    static const regex rgx;

    static Toke_Eighths * aninstance;
    static     Toke_Eighths * instance();

     Toke_Eighths();
     Toke_Eighths(string * s, size_t n);
    static     SkoarToke* match_toke(string * buf, size_t offs);
};

class Toke_DynSFZ: public SkoarToke {
public:
    static const regex rgx;

    static Toke_DynSFZ * aninstance;
    static     Toke_DynSFZ * instance();

     Toke_DynSFZ();
     Toke_DynSFZ(string * s, size_t n);
    static     SkoarToke* match_toke(string * buf, size_t offs);
};

class Toke_AssOp: public SkoarToke {
public:
    static const regex rgx;

    static Toke_AssOp * aninstance;
    static     Toke_AssOp * instance();

     Toke_AssOp();
     Toke_AssOp(string * s, size_t n);
    static     SkoarToke* match_toke(string * buf, size_t offs);
};

class Toke_Caesura: public SkoarToke {
public:
    static const regex rgx;

    static Toke_Caesura * aninstance;
    static     Toke_Caesura * instance();

     Toke_Caesura();
     Toke_Caesura(string * s, size_t n);
    static     SkoarToke* match_toke(string * buf, size_t offs);
};

class Toke_String: public SkoarToke {
public:
    static const regex rgx;

    static Toke_String * aninstance;
    static     Toke_String * instance();

     Toke_String();
     Toke_String(string * s, size_t n);
    static     SkoarToke* match_toke(string * buf, size_t offs);
};

class Toke_Volta: public SkoarToke {
public:
    static const regex rgx;

    static Toke_Volta * aninstance;
    static     Toke_Volta * instance();

     Toke_Volta();
     Toke_Volta(string * s, size_t n);
    static     SkoarToke* match_toke(string * buf, size_t offs);
};

class Toke_QuindicesimaA: public SkoarToke {
public:
    static const regex rgx;

    static Toke_QuindicesimaA * aninstance;
    static     Toke_QuindicesimaA * instance();

     Toke_QuindicesimaA();
     Toke_QuindicesimaA(string * s, size_t n);
    static     SkoarToke* match_toke(string * buf, size_t offs);
};

class Toke_Nosey: public SkoarToke {
public:
    static const regex rgx;

    static Toke_Nosey * aninstance;
    static     Toke_Nosey * instance();

     Toke_Nosey();
     Toke_Nosey(string * s, size_t n);
    static     SkoarToke* match_toke(string * buf, size_t offs);
};

class Toke_PedalDown: public SkoarToke {
public:
    static const regex rgx;

    static Toke_PedalDown * aninstance;
    static     Toke_PedalDown * instance();

     Toke_PedalDown();
     Toke_PedalDown(string * s, size_t n);
    static     SkoarToke* match_toke(string * buf, size_t offs);
};

class Toke_LoopE: public SkoarToke {
public:
    static const regex rgx;

    static Toke_LoopE * aninstance;
    static     Toke_LoopE * instance();

     Toke_LoopE();
     Toke_LoopE(string * s, size_t n);
    static     SkoarToke* match_toke(string * buf, size_t offs);
};

class Toke_OttavaB: public SkoarToke {
public:
    static const regex rgx;

    static Toke_OttavaB * aninstance;
    static     Toke_OttavaB * instance();

     Toke_OttavaB();
     Toke_OttavaB(string * s, size_t n);
    static     SkoarToke* match_toke(string * buf, size_t offs);
};

class Toke_BooleanOp: public SkoarToke {
public:
    static const regex rgx;

    static Toke_BooleanOp * aninstance;
    static     Toke_BooleanOp * instance();

     Toke_BooleanOp();
     Toke_BooleanOp(string * s, size_t n);
    static     SkoarToke* match_toke(string * buf, size_t offs);
};

class Toke_Tuplet: public SkoarToke {
public:
    static const regex rgx;

    static Toke_Tuplet * aninstance;
    static     Toke_Tuplet * instance();

     Toke_Tuplet();
     Toke_Tuplet(string * s, size_t n);
    static     SkoarToke* match_toke(string * buf, size_t offs);
};

class Toke_LWing: public SkoarToke {
public:
    static const regex rgx;

    static Toke_LWing * aninstance;
    static     Toke_LWing * instance();

     Toke_LWing();
     Toke_LWing(string * s, size_t n);
    static     SkoarToke* match_toke(string * buf, size_t offs);
};

class Toke_Deref: public SkoarToke {
public:
    static const regex rgx;

    static Toke_Deref * aninstance;
    static     Toke_Deref * instance();

     Toke_Deref();
     Toke_Deref(string * s, size_t n);
    static     SkoarToke* match_toke(string * buf, size_t offs);
};

class Toke_AlFine: public SkoarToke {
public:
    static const regex rgx;

    static Toke_AlFine * aninstance;
    static     Toke_AlFine * instance();

     Toke_AlFine();
     Toke_AlFine(string * s, size_t n);
    static     SkoarToke* match_toke(string * buf, size_t offs);
};

class Toke_OttavaA: public SkoarToke {
public:
    static const regex rgx;

    static Toke_OttavaA * aninstance;
    static     Toke_OttavaA * instance();

     Toke_OttavaA();
     Toke_OttavaA(string * s, size_t n);
    static     SkoarToke* match_toke(string * buf, size_t offs);
};

class Toke_Symbol: public SkoarToke {
public:
    static const regex rgx;

    static Toke_Symbol * aninstance;
    static     Toke_Symbol * instance();

     Toke_Symbol();
     Toke_Symbol(string * s, size_t n);
    static     SkoarToke* match_toke(string * buf, size_t offs);
};

class Toke_Fairy: public SkoarToke {
public:
    static const regex rgx;

    static Toke_Fairy * aninstance;
    static     Toke_Fairy * instance();

     Toke_Fairy();
     Toke_Fairy(string * s, size_t n);
    static     SkoarToke* match_toke(string * buf, size_t offs);
};

class Toke_MsgOp: public SkoarToke {
public:
    static const regex rgx;

    static Toke_MsgOp * aninstance;
    static     Toke_MsgOp * instance();

     Toke_MsgOp();
     Toke_MsgOp(string * s, size_t n);
    static     SkoarToke* match_toke(string * buf, size_t offs);
};

class Toke_MathOp: public SkoarToke {
public:
    static const regex rgx;

    static Toke_MathOp * aninstance;
    static     Toke_MathOp * instance();

     Toke_MathOp();
     Toke_MathOp(string * s, size_t n);
    static     SkoarToke* match_toke(string * buf, size_t offs);
};

class Toke_LoopSep: public SkoarToke {
public:
    static const regex rgx;

    static Toke_LoopSep * aninstance;
    static     Toke_LoopSep * instance();

     Toke_LoopSep();
     Toke_LoopSep(string * s, size_t n);
    static     SkoarToke* match_toke(string * buf, size_t offs);
};

class Toke_Quavers: public SkoarToke {
public:
    static const regex rgx;

    static Toke_Quavers * aninstance;
    static     Toke_Quavers * instance();

     Toke_Quavers();
     Toke_Quavers(string * s, size_t n);
    static     SkoarToke* match_toke(string * buf, size_t offs);
};

class Toke_SkoarpionStart: public SkoarToke {
public:
    static const regex rgx;

    static Toke_SkoarpionStart * aninstance;
    static     Toke_SkoarpionStart * instance();

     Toke_SkoarpionStart();
     Toke_SkoarpionStart(string * s, size_t n);
    static     SkoarToke* match_toke(string * buf, size_t offs);
};

class Toke_DaCapo: public SkoarToke {
public:
    static const regex rgx;

    static Toke_DaCapo * aninstance;
    static     Toke_DaCapo * instance();

     Toke_DaCapo();
     Toke_DaCapo(string * s, size_t n);
    static     SkoarToke* match_toke(string * buf, size_t offs);
};

class Toke_SkoarpionSep: public SkoarToke {
public:
    static const regex rgx;

    static Toke_SkoarpionSep * aninstance;
    static     Toke_SkoarpionSep * instance();

     Toke_SkoarpionSep();
     Toke_SkoarpionSep(string * s, size_t n);
    static     SkoarToke* match_toke(string * buf, size_t offs);
};

class Toke_CondIf: public SkoarToke {
public:
    static const regex rgx;

    static Toke_CondIf * aninstance;
    static     Toke_CondIf * instance();

     Toke_CondIf();
     Toke_CondIf(string * s, size_t n);
    static     SkoarToke* match_toke(string * buf, size_t offs);
};

class Toke_Meter: public SkoarToke {
public:
    static const regex rgx;

    static Toke_Meter * aninstance;
    static     Toke_Meter * instance();

     Toke_Meter();
     Toke_Meter(string * s, size_t n);
    static     SkoarToke* match_toke(string * buf, size_t offs);
};

class Toke_Int: public SkoarToke {
public:
    static const regex rgx;

    static Toke_Int * aninstance;
    static     Toke_Int * instance();

     Toke_Int();
     Toke_Int(string * s, size_t n);
    static     SkoarToke* match_toke(string * buf, size_t offs);
};

class Toke_Carrot: public SkoarToke {
public:
    static const regex rgx;

    static Toke_Carrot * aninstance;
    static     Toke_Carrot * instance();

     Toke_Carrot();
     Toke_Carrot(string * s, size_t n);
    static     SkoarToke* match_toke(string * buf, size_t offs);
};

class Toke_Voice: public SkoarToke {
public:
    static const regex rgx;

    static Toke_Voice * aninstance;
    static     Toke_Voice * instance();

     Toke_Voice();
     Toke_Voice(string * s, size_t n);
    static     SkoarToke* match_toke(string * buf, size_t offs);
};

class Toke_Comment: public SkoarToke {
public:
    static const regex rgx;

    static Toke_Comment * aninstance;
    static     Toke_Comment * instance();

     Toke_Comment();
     Toke_Comment(string * s, size_t n);
    static     SkoarToke* match_toke(string * buf, size_t offs);
};

class Toke_Choard: public SkoarToke {
public:
    static const regex rgx;

    static Toke_Choard * aninstance;
    static     Toke_Choard * instance();

     Toke_Choard();
     Toke_Choard(string * s, size_t n);
    static     SkoarToke* match_toke(string * buf, size_t offs);
};

class Toke_DalSegno: public SkoarToke {
public:
    static const regex rgx;

    static Toke_DalSegno * aninstance;
    static     Toke_DalSegno * instance();

     Toke_DalSegno();
     Toke_DalSegno(string * s, size_t n);
    static     SkoarToke* match_toke(string * buf, size_t offs);
};

class Toke_Fine: public SkoarToke {
public:
    static const regex rgx;

    static Toke_Fine * aninstance;
    static     Toke_Fine * instance();

     Toke_Fine();
     Toke_Fine(string * s, size_t n);
    static     SkoarToke* match_toke(string * buf, size_t offs);
};

