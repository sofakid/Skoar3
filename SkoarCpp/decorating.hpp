#pragma once
#include "skoarcery.hpp"

#include "lex_fwd.hpp"
#include "noad_fwd.hpp"
#include "skoar_fwd.hpp"
#include "fairy_fwd.hpp"
#include "spells.hpp"

class SkoarTokeInspector {
public:
	SkoarTokeInspector();

    // -----------------------------------------------------------------
    void decorate(Toke_Fairy *toke, SkoarNoadPtr noad);
    void decorate(Toke_Cat *toke, SkoarNoadPtr noad);
    void decorate(Toke_True *toke, SkoarNoadPtr noad);
    void decorate(Toke_False *toke, SkoarNoadPtr noad);

    // -----------------------------------------------------------------
    void decorate(Toke_Freq *toke, SkoarNoadPtr noad);
    void decorate(Toke_Int *toke, SkoarNoadPtr noad);
	void decorate(Toke_Float *toke, SkoarNoadPtr noad);
	
    // -----------------------------------------------------------------
    void decorate(Toke_NamedNoat *toke, SkoarNoadPtr noad);
	void decorate(Toke_Choard *toke, SkoarNoadPtr noad);
	
    // -----------------------------------------------------------------
    void decorate(Toke_String *toke, SkoarNoadPtr noad);
	void decorate(Toke_Symbol *toke, SkoarNoadPtr noad);
	void decorate(Toke_SymbolName *toke, SkoarNoadPtr noad);
    void decorate(Toke_SymbolColon *toke, SkoarNoadPtr noad);

    // -----------------------------------------------------------------
    void decorate(Toke_Crotchets *toke, SkoarNoadPtr noad);
	void decorate(Toke_Quavers *toke, SkoarNoadPtr noad);
	void decorate(Toke_Quarters *toke, SkoarNoadPtr noad);
	void decorate(Toke_Eighths *toke, SkoarNoadPtr noad);
    void decorate(Toke_ExactBeat *toke, SkoarNoadPtr noad);
    void decorate(Toke_ExactRest *toke, SkoarNoadPtr noad);
    void decorate(Toke_Duration *toke, SkoarNoadPtr noad);

    // -----------------------------------------------------------------
    void decorate(Toke_Bars *toke, SkoarNoadPtr noad);
	void decorate(Toke_Carrot *toke, SkoarNoadPtr noad);
	void decorate(Toke_Tuplet *toke, SkoarNoadPtr noad);
	void decorate(Toke_DynPiano *toke, SkoarNoadPtr noad);
	void decorate(Toke_DynForte *toke, SkoarNoadPtr noad);
	void decorate(Toke_OctaveShift *toke, SkoarNoadPtr noad);
	void decorate(Toke_OttavaA *toke, SkoarNoadPtr noad);
	void decorate(Toke_OttavaB *toke, SkoarNoadPtr noad);
	void decorate(Toke_QuindicesimaA *toke, SkoarNoadPtr noad);
	void decorate(Toke_QuindicesimaB *toke, SkoarNoadPtr noad);
    void decorate(Toke_Segno *toke, SkoarNoadPtr noad);
    void decorate(Toke_Fine *toke, SkoarNoadPtr noad);

    // -----------------------------------------------------------------
    void decorate(Toke_BooleanOp *toke, SkoarNoadPtr noad);
	void decorate(Toke_Voice *toke, SkoarNoadPtr noad);	
    void decorate(Toke_MsgName *toke, SkoarNoadPtr noad);
	void decorate(Toke_MsgNameWithArgs *toke, SkoarNoadPtr noad);
	void decorate(Toke_MathOp *toke, SkoarNoadPtr noad);
	void decorate(Toke_ListSep *toke, SkoarNoadPtr noad);
	void decorate(Toke_ListE *toke, SkoarNoadPtr noad);

    // -----------------------------------------------------------------
    void decorate(Toke_Times *toke, SkoarNoadPtr noad);
    void decorate(Toke_HashLevel *toke, SkoarNoadPtr noad);

    // -----------------------------------------------------------------
    void decorate(Toke_AUGen *toke, SkoarNoadPtr noad);
    void decorate(Toke_KUGen *toke, SkoarNoadPtr noad);
    void decorate(Toke_DUGen *toke, SkoarNoadPtr noad);
    void decorate(Toke_AUGenWithArgs *toke, SkoarNoadPtr noad);
    void decorate(Toke_KUGenWithArgs *toke, SkoarNoadPtr noad);
    void decorate(Toke_DUGenWithArgs *toke, SkoarNoadPtr noad);

    // -----------------------------------------------------------------
    void decorate(Toke_Lute *toke, SkoarNoadPtr noad);
    void decorate(Toke_LuteWithArgs *toke, SkoarNoadPtr noad);

	// default
	void decorate(SkoarToke *toke, SkoarNoadPtr noad);
};

class Skoarmantics {
public:
	map<ESkoarNoad::Kind, SpellOfNoadyDecoration> table;

	Skoarmantics();

};
