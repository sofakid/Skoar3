#include "toke_inspector.hpp"

#include "lex.hpp"
#include "noad.hpp"
#include "skoarpuscle.hpp"
#include "skoarpion.hpp"
#include "fairy.hpp"
#include "event.hpp"
#include "skoar.hpp"
#include "minstrel.hpp"
#include "beaty.hpp"
#include "skoarpion_skoarpuscle.hpp"
#include "dsp.hpp"
#include "lute.hpp"
#include "meditation.hpp"

// ==============
// toke_inspector
// ==============
//
// Here we pick the values out of the tokens
// and set its attributes appropriately
SkoarTokeInspector::SkoarTokeInspector() {

}

void SkoarTokeInspector::decorate(SkoarToke *, SkoarNoadPtr) {
    ;
};

void SkoarTokeInspector::decorate(Toke_Fairy *toke, SkoarNoadPtr noad) {
    noad->skoarpuscle = make_shared<SkoarpuscleFairy>();
    noad->toke = nullptr;
};

void SkoarTokeInspector::decorate(Toke_Cat *toke, SkoarNoadPtr noad) {
    noad->skoarpuscle = make_shared<SkoarpuscleCat>();
    noad->toke = nullptr;
};

void SkoarTokeInspector::decorate(Toke_True *toke, SkoarNoadPtr noad) {
    noad->skoarpuscle = make_shared<SkoarpuscleTrue>();
    noad->toke = nullptr;
}

void SkoarTokeInspector::decorate(Toke_False *toke, SkoarNoadPtr noad) {
    noad->skoarpuscle = make_shared<SkoarpuscleFalse>();
    noad->toke = nullptr;
}


// -----------------------------------------------------------------
void SkoarTokeInspector::decorate(Toke_Freq *toke, SkoarNoadPtr noad) {
    noad->skoarpuscle = make_shared<SkoarpuscleFreq>(toke->lexeme);
    noad->toke = nullptr;
}

void SkoarTokeInspector::decorate(Toke_Int *toke, SkoarNoadPtr noad) {
    noad->skoarpuscle = make_shared<SkoarpuscleInt>(stoi(toke->lexeme));
    noad->toke = nullptr;
}

void SkoarTokeInspector::decorate(Toke_Float *toke, SkoarNoadPtr noad) {
    noad->skoarpuscle = make_shared<SkoarpuscleFloat>(stod(toke->lexeme));
    noad->toke = nullptr;
}


// -----------------------------------------------------------------
void SkoarTokeInspector::decorate(Toke_NamedNoat *toke, SkoarNoadPtr noad) {
    noad->skoarpuscle = make_shared<SkoarpuscleNoat>(toke->lexeme);
    noad->toke = nullptr;
}

void SkoarTokeInspector::decorate(Toke_Choard *toke, SkoarNoadPtr noad) {
    noad->skoarpuscle = make_shared<SkoarpuscleChoard>(toke->lexeme);
    noad->toke = nullptr;
}


// -----------------------------------------------------------------
void SkoarTokeInspector::decorate(Toke_String *toke, SkoarNoadPtr noad) {
    noad->skoarpuscle = make_shared<SkoarpuscleString>(toke->lexeme);
    noad->toke = nullptr;
}

void SkoarTokeInspector::decorate(Toke_Symbol *toke, SkoarNoadPtr noad) {
    noad->skoarpuscle = make_shared<SkoarpuscleSymbol>(toke->lexeme.substr(1));
    noad->toke = nullptr;
}

void SkoarTokeInspector::decorate(Toke_SymbolName *toke, SkoarNoadPtr noad) {
    noad->skoarpuscle = make_shared<SkoarpuscleSymbolName>(toke->lexeme);
    noad->toke = nullptr;
}

void SkoarTokeInspector::decorate(Toke_SymbolColon *toke, SkoarNoadPtr noad) {
    noad->skoarpuscle = make_shared<SkoarpuscleSymbolColon>(toke->lexeme);
    noad->toke = nullptr;
}


// -----------------------------------------------------------------
// rests
// } }} }}}
void SkoarTokeInspector::decorate(Toke_Crotchets *toke, SkoarNoadPtr noad) {
    noad->skoarpuscle = make_shared<SkoarpuscleRest>(toke);
    noad->toke = nullptr;
}

// o/ oo/ ooo/
void SkoarTokeInspector::decorate(Toke_Quavers *toke, SkoarNoadPtr noad) {
    noad->skoarpuscle = make_shared<SkoarpuscleRest>(toke);
    noad->toke = nullptr;
}

// unrests
void SkoarTokeInspector::decorate(Toke_Quarters *toke, SkoarNoadPtr noad) {
    noad->skoarpuscle = make_shared<SkoarpuscleBeat>(toke);
    noad->toke = nullptr;
}

void SkoarTokeInspector::decorate(Toke_Eighths *toke, SkoarNoadPtr noad) {
    noad->skoarpuscle = make_shared<SkoarpuscleBeat>(toke);
    noad->toke = nullptr;
}

void SkoarTokeInspector::decorate(Toke_ExactBeat *toke, SkoarNoadPtr noad) {
    noad->skoarpuscle = make_shared<SkoarpuscleExactBeat>(toke);
    noad->toke = nullptr;
}

void SkoarTokeInspector::decorate(Toke_ExactRest *toke, SkoarNoadPtr noad) {
    noad->skoarpuscle = make_shared<SkoarpuscleExactRest>(toke);
    noad->toke = nullptr;
}

void SkoarTokeInspector::decorate(Toke_Duration *toke, SkoarNoadPtr noad) {
    noad->skoarpuscle = make_shared<SkoarpuscleDuration>(toke);
    noad->toke = nullptr;
}


// -----------------------------------------------------------------
void SkoarTokeInspector::decorate(Toke_Bars *toke, SkoarNoadPtr noad) {
    noad->skoarpuscle = make_shared<SkoarpuscleBars>(toke);
    noad->toke = nullptr;
}

void SkoarTokeInspector::decorate(Toke_Carrot *toke, SkoarNoadPtr noad) {
    noad->skoarpuscle = make_shared<SkoarpuscleCarrots>(toke);
    noad->toke = nullptr;
}

void SkoarTokeInspector::decorate(Toke_Tuplet *toke, SkoarNoadPtr noad) {
    noad->skoarpuscle = make_shared<SkoarpuscleTuplet>(toke);
    noad->toke = nullptr;
}

void SkoarTokeInspector::decorate(Toke_DynPiano *toke, SkoarNoadPtr noad) {
    noad->skoarpuscle = make_shared<SkoarpuscleDynamic>(toke);
    noad->toke = nullptr;
}

void SkoarTokeInspector::decorate(Toke_DynForte *toke, SkoarNoadPtr noad) {
    noad->skoarpuscle = make_shared<SkoarpuscleDynamic>(toke);
    noad->toke = nullptr;
}

void SkoarTokeInspector::decorate(Toke_OctaveShift *toke, SkoarNoadPtr noad) {
    noad->skoarpuscle = make_shared<SkoarpuscleOctaveShift>(toke);
    noad->toke = nullptr;
}

void SkoarTokeInspector::decorate(Toke_OttavaA *toke, SkoarNoadPtr noad) {
    noad->skoarpuscle = make_shared<SkoarpuscleOctaveShift>(toke);
    noad->toke = nullptr;
}

void SkoarTokeInspector::decorate(Toke_OttavaB *toke, SkoarNoadPtr noad) {
    noad->skoarpuscle = make_shared<SkoarpuscleOctaveShift>(toke);
    noad->toke = nullptr;
}

void SkoarTokeInspector::decorate(Toke_QuindicesimaA *toke, SkoarNoadPtr noad) {
    noad->skoarpuscle = make_shared<SkoarpuscleOctaveShift>(toke);
    noad->toke = nullptr;
}

void SkoarTokeInspector::decorate(Toke_QuindicesimaB *toke, SkoarNoadPtr noad) {
    noad->skoarpuscle = make_shared<SkoarpuscleOctaveShift>(toke);
    noad->toke = nullptr;
}

void SkoarTokeInspector::decorate(Toke_Segno *toke, SkoarNoadPtr noad) {
    noad->skoarpuscle = make_shared<SkoarpuscleSegno>(noad, toke);
    noad->toke = nullptr;
}

void SkoarTokeInspector::decorate(Toke_Fine *toke, SkoarNoadPtr noad) {
    noad->skoarpuscle = make_shared<SkoarpuscleFine>();
    noad->toke = nullptr;
}


// -----------------------------------------------------------------
void SkoarTokeInspector::decorate(Toke_BooleanOp *toke, SkoarNoadPtr noad) {
    noad->skoarpuscle = make_shared<SkoarpuscleBooleanOp>(noad, toke);
    noad->toke = nullptr;
}

void SkoarTokeInspector::decorate(Toke_Voice *toke, SkoarNoadPtr noad) {
    noad->skoarpuscle = make_shared<SkoarpuscleVoice>(toke);
    noad->toke = nullptr;
}

void SkoarTokeInspector::decorate(Toke_MsgName *toke, SkoarNoadPtr noad) {
    noad->skoarpuscle = make_shared<SkoarpuscleMsgName>(toke->lexeme);
    noad->toke = nullptr;
}

void SkoarTokeInspector::decorate(Toke_MsgNameWithArgs *toke, SkoarNoadPtr noad) {
    auto s = toke->lexeme;
    auto n = s.length() - 2;
    noad->skoarpuscle = make_shared<SkoarpuscleMsgName>(s.substr(0, n));
    noad->toke = nullptr;
}

void SkoarTokeInspector::decorate(Toke_MathOp *toke, SkoarNoadPtr noad) {
    noad->skoarpuscle = make_shared<SkoarpuscleMathOp>(toke);
    noad->toke = nullptr;
}

void SkoarTokeInspector::decorate(Toke_ListSep *toke, SkoarNoadPtr noad) {
    auto x = make_shared<SkoarpuscleListSep>();
    noad->skoarpuscle = x;
    noad->toke = nullptr;
}

void SkoarTokeInspector::decorate(Toke_ListE *toke, SkoarNoadPtr noad) {
    auto x = make_shared<SkoarpuscleListEnd>();
    noad->skoarpuscle = x;
    noad->toke = nullptr;
}


// -----------------------------------------------------------------
void SkoarTokeInspector::decorate(Toke_Times *toke, SkoarNoadPtr noad) {
    noad->skoarpuscle = make_shared<SkoarpuscleTimes>();
    noad->toke = nullptr;
}

void SkoarTokeInspector::decorate(Toke_HashLevel *toke, SkoarNoadPtr noad) {
    noad->skoarpuscle = make_shared<SkoarpuscleHashLevel>(toke->lexeme);
    noad->toke = nullptr;
}


// -----------------------------------------------------------------
void SkoarTokeInspector::decorate(Toke_AUGen *toke, SkoarNoadPtr noad) {
    noad->skoarpuscle = make_shared<SkoarpuscleUGen>(toke->lexeme.substr(1), SkoarpuscleUGen::Type::audio);
    noad->toke = nullptr;
}

void SkoarTokeInspector::decorate(Toke_KUGen *toke, SkoarNoadPtr noad) {
    noad->skoarpuscle = make_shared<SkoarpuscleUGen>(toke->lexeme.substr(1), SkoarpuscleUGen::Type::control);
    noad->toke = nullptr;
}

void SkoarTokeInspector::decorate(Toke_DUGen *toke, SkoarNoadPtr noad) {
    noad->skoarpuscle = make_shared<SkoarpuscleUGen>(toke->lexeme.substr(1), SkoarpuscleUGen::Type::demand);
    noad->toke = nullptr;
}

void SkoarTokeInspector::decorate(Toke_AUGenWithArgs *toke, SkoarNoadPtr noad) {
    auto s = toke->lexeme;
    noad->skoarpuscle = make_shared<SkoarpuscleUGenWithArgs>(s.substr(1, s.size() - 2), SkoarpuscleUGen::Type::audio);
    noad->toke = nullptr;
}

void SkoarTokeInspector::decorate(Toke_KUGenWithArgs *toke, SkoarNoadPtr noad) {
    auto s = toke->lexeme;
    noad->skoarpuscle = make_shared<SkoarpuscleUGenWithArgs>(s.substr(1, s.size() - 2), SkoarpuscleUGen::Type::control);
    noad->toke = nullptr;
}

void SkoarTokeInspector::decorate(Toke_DUGenWithArgs *toke, SkoarNoadPtr noad) {
    auto s = toke->lexeme;
    noad->skoarpuscle = make_shared<SkoarpuscleUGenWithArgs>(s.substr(1, s.size() - 2), SkoarpuscleUGen::Type::demand);
    noad->toke = nullptr;
}


// -----------------------------------------------------------------
void SkoarTokeInspector::decorate(Toke_Lute *toke, SkoarNoadPtr noad) {
    noad->skoarpuscle = make_shared<SkoarpuscleLute>(toke);
    noad->toke = nullptr;
}

void SkoarTokeInspector::decorate(Toke_LuteWithArgs *toke, SkoarNoadPtr noad) {
    noad->skoarpuscle = make_shared<SkoarpuscleLute>(toke);
    noad->toke = nullptr;
}