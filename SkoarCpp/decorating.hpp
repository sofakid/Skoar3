#pragma once
#include "skoarcery.hpp"

#include "lex_fwd.hpp"
#include "noad_fwd.hpp"
#include "skoar_fwd.hpp"
#include "fairy_fwd.hpp"

class SkoarTokeInspector {
public:
	SkoarTokeInspector();

	void decorate(Toke_Fairy *toke, SkoarNoad* noad);
	void decorate(Toke_Freq *toke, SkoarNoad* noad);
	void decorate(Toke_Int *toke, SkoarNoad* noad);
	void decorate(Toke_Float *toke, SkoarNoad* noad);
	void decorate(Toke_NamedNoat *toke, SkoarNoad* noad);
	void decorate(Toke_Choard *toke, SkoarNoad* noad);
	void decorate(Toke_String *toke, SkoarNoad* noad);
	void decorate(Toke_Symbol *toke, SkoarNoad* noad);
	void decorate(Toke_SymbolName *toke, SkoarNoad* noad);
	void decorate(Toke_Crotchets *toke, SkoarNoad* noad);
	void decorate(Toke_Quavers *toke, SkoarNoad* noad);
	void decorate(Toke_Quarters *toke, SkoarNoad* noad);
	void decorate(Toke_Eighths *toke, SkoarNoad* noad);
	void decorate(Toke_Bars *toke, SkoarNoad* noad);
	void decorate(Toke_Volta *toke, SkoarNoad* noad);
	void decorate(Toke_Meter *toke, SkoarNoad* noad);
	void decorate(Toke_Carrot *toke, SkoarNoad* noad);
	void decorate(Toke_Tuplet *toke, SkoarNoad* noad);
	void decorate(Toke_DynPiano *toke, SkoarNoad* noad);
	void decorate(Toke_DynForte *toke, SkoarNoad* noad);
	void decorate(Toke_OctaveShift *toke, SkoarNoad* noad);
	void decorate(Toke_OttavaA *toke, SkoarNoad* noad);
	void decorate(Toke_OttavaB *toke, SkoarNoad* noad);
	void decorate(Toke_QuindicesimaA *toke, SkoarNoad* noad);
	void decorate(Toke_QuindicesimaB *toke, SkoarNoad* noad);
	void decorate(Toke_BooleanOp *toke, SkoarNoad* noad);
	void decorate(Toke_Voice *toke, SkoarNoad* noad);
	void decorate(Toke_Segno *toke, SkoarNoad* noad);
	void decorate(Toke_Rep *toke, SkoarNoad* noad);
	void decorate(Toke_Fine *toke, SkoarNoad* noad);
	void decorate(Toke_MsgName *toke, SkoarNoad* noad);
	void decorate(Toke_MsgNameWithArgs *toke, SkoarNoad* noad);
	void decorate(Toke_MathOp *toke, SkoarNoad* noad);
	void decorate(Toke_ListSep *toke, SkoarNoad* noad);
	void decorate(Toke_ListE *toke, SkoarNoad* noad);

	// default
	void decorate(SkoarToke *toke, SkoarNoad* noad);
};

class Skoarmantics {
public:
	map<string, function<void(Skoar *skoar, SkoarNoad *noad)>> table;

	Skoarmantics();

};
