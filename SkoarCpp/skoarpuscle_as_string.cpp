#include "skoarpuscle.hpp"

#include "lex.hpp"
#include "minstrel.hpp"
#include "fairy.hpp"
#include "skoar.hpp"
#include "koar.hpp"
#include "noad.hpp"
#include "skoarpion.hpp"
#include "skoarpion_skoarpuscle.hpp"
#include "make_skoarpuscle.hpp"


void SkoarpuscleUnknown::asString(wostream &out) {
    out << "SkoarpuscleUnknown";
}

void SkoarpuscleCat::asString(wostream &out) {
    out << "=^.^=";
}

void SkoarpuscleTrue::asString(wostream &out) {
    out << "true";
}

void SkoarpuscleFalse::asString(wostream &out) {
    out << "false";
}

void SkoarpuscleFreq::asString(wostream &out) {
    out << val << "Hz";
}

void SkoarpuscleInt::asString(wostream &out) {
    out << val;
}

void SkoarpuscleFloat::asString(wostream &out) {
    out << val;
}

void SkoarpuscleNoat::asString(wostream &out) {
    out << "SkoarpuscleNoat" << " :: " << val;
}

void SkoarpuscleChoard::asString(wostream &out) {
    out << "SkoarpuscleChoard" << " :: " << val;
}

void SkoarpuscleString::asString(wostream &out) {
    out << val;
}

void SkoarpuscleSymbol::asString(wostream &out) {
    out << "@" << val;
}

void SkoarpuscleSymbolName::asString(wostream &out) {
    out << "SkoarpuscleSymbolName" << " :: " << val;
}

void SkoarpuscleSymbolColon::asString(wostream &out) {
    out << "SkoarpuscleSymbolColon" << " :: " << val;
}

void SkoarpuscleTimes::asString(wostream &out) {
    out << "SkoarpuscleTimes";
}

void SkoarpuscleBars::asString(wostream &out) {
    out << "SkoarpuscleBars";
}

void SkoarpuscleCarrots::asString(wostream &out) {
    out << "SkoarpuscleCarrots" << " :: " << val;
}

void SkoarpuscleTuplet::asString(wostream &out) {
    out << "SkoarpuscleTuplet" << " :: " << val;
}

void SkoarpuscleDynamic::asString(wostream &out) {
    out << "SkoarpuscleDynamic" << " :: " << val;
}

void SkoarpuscleOctaveShift::asString(wostream &out) {
    out << "SkoarpuscleOctaveShift" << " :: " << val;
}

void SkoarpuscleBooleanOp::asString(wostream &out) {
    out << "SkoarpuscleBooleanOp";
}

void SkoarpuscleVoice::asString(wostream &out) {
    out << "SkoarpuscleVoice" << " :: " << val;
}

void SkoarpuscleSegno::asString(wostream &out) {
    out << "SkoarpuscleSegno";
}

void SkoarpuscleFine::asString(wostream &out) {
    out << "SkoarpuscleFine";
}

void SkoarpuscleMsgName::asString(wostream &out) {
    out << "SkoarpuscleMsgName" << " :: " << val;
}

void SkoarpuscleMsgNameWithArgs::asString(wostream &out) {
    out << "SkoarpuscleMsgNameWithArgs" << " :: " << val;
}

void SkoarpuscleMathOp::asString(wostream &out) {
    out << "SkoarpuscleMathOp" << " :: " << val;
}

void SkoarpuscleList::asString(wostream &out) {
    out << "SkoarpuscleList";
}

void SkoarpuscleListSep::asString(wostream &out) {
    out << "SkoarpuscleListSep";
}

void SkoarpuscleListEnd::asString(wostream &out) {
    out << "SkoarpuscleListEnd";
}

void SkoarpuscleDeref::asString(wostream &out) {
    out << "SkoarpuscleDeref" << " :: " << val;
}

void SkoarpuscleConditional::asString(wostream &out) {
    out << "SkoarpuscleConditional";
}

void SkoarpuscleBoolean::asString(wostream &out) {
    out << "SkoarpuscleBoolean";
}

void SkoarpuscleLoop::asString(wostream &out) {
    out << "SkoarpuscleLoop";
}

void SkoarpuscleLoopMsg::asString(wostream &out) {
    out << "SkoarpuscleLoopMsg";
}

void SkoarpuscleGoto::asString(wostream &out) {
    out << "SkoarpuscleGoto";
}

void SkoarpuscleArgs::asString(wostream &out) {
    out << "SkoarpuscleArgs";
}

void SkoarpuscleMsg::asString(wostream &out) {
    out << "SkoarpuscleMsg" << " :: " << val;
}

void SkoarpuscleExprEnd::asString(wostream &out) {
    out << "SkoarpuscleExprEnd";
}

void SkoarpuscleHashLevel::asString(wostream &out) {
    out << "SkoarpuscleHashLevel" << " :: " << val;
}

void SkoarpusclePair::asString(wostream &out) {
    out << "SkoarpusclePair" << " :: " << val.first;
}

void SkoarpuscleExpr::asString(wostream &out) {
    out << "SkoarpuscleExpr";
}


