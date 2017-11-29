#include "skoarpuscle.hpp"

#include "lex.hpp"
#include "minstrel.hpp"
#include "fairy.hpp"
#include "skoar.hpp"
#include "koar.hpp"
#include "noad.hpp"
#include "skoarpion.hpp"
#include "skoarpion_skoarpuscle.hpp"
#include "pitchy.hpp"
#include "make_skoarpuscle.hpp"


void SkoarpuscleUnknown::asString (wostream &out) {
    out << "Unknown";
}
void SkoarpuscleUnknown::typeAsString (wostream &out) {
    out << "Unknown";
}
void SkoarpuscleUnknown::valAsString (wostream &out) {
    out << "Unknown";
}


void SkoarpuscleCat::asString (wostream &out) {
    out << "Cat";
}
void SkoarpuscleCat::typeAsString (wostream &out) {
    out << "Cat";
}
void SkoarpuscleCat::valAsString (wostream &out) {
    out << "=^.^=";
}



void SkoarpuscleTrue::asString (wostream &out) {
    out << "True";
}
void SkoarpuscleTrue::typeAsString (wostream &out) {
    out << "True";
}
void SkoarpuscleTrue::valAsString (wostream &out) {
    out << "true";
}


void SkoarpuscleFalse::asString (wostream &out) {
    out << "False";
}
void SkoarpuscleFalse::typeAsString (wostream &out) {
    out << "False";
}
void SkoarpuscleFalse::valAsString (wostream &out) {
    out << "false";
}





void SkoarpuscleFreq::asString (wostream &out) {
    out << val << "Hz";
}
void SkoarpuscleFreq::typeAsString (wostream &out) {
    out << "Freq";
}
void SkoarpuscleFreq::valAsString (wostream &out) {
    out << val << "Hz";
}



void SkoarpuscleInt::asString (wostream &out) {
    out << "Int" << " :: " << val;
}
void SkoarpuscleInt::typeAsString (wostream &out) {
    out << "Int";
}
void SkoarpuscleInt::valAsString (wostream &out) {
    out << val;
}



void SkoarpuscleFloat::asString (wostream &out) {
    out << "Float" << " :: " << val;
}
void SkoarpuscleFloat::typeAsString (wostream &out) {
    out << "Float";
}
void SkoarpuscleFloat::valAsString (wostream &out) {
    out << val;
}


void SkoarpuscleKey::asString (wostream & out)
{
    out << L"Key :: root :: ";
    skoarpuscle_ptr<SkoarpuscleInt> (root)->valAsString (out);
    out << L" :: scale_name :: ";
    skoarpuscle_ptr<SkoarpuscleString> (scale_name)->valAsString (out);
}



void SkoarpuscleNoat::asString (wostream &out) {
    out << "Noat" << " :: " << lexeme;
}
void SkoarpuscleNoat::typeAsString (wostream &out) {
    out << "Noat";
}
void SkoarpuscleNoat::valAsString (wostream &out) {
    out << lexeme;
}



void SkoarpuscleChoard::asString (wostream &out) {
    out << "Choard" << " :: " << lexeme;
}
void SkoarpuscleChoard::typeAsString (wostream &out) {
    out << "Choard";
}
void SkoarpuscleChoard::valAsString (wostream &out) {
    out << lexeme;
}



void SkoarpuscleString::asString (wostream &out) {
    out << val;
}
void SkoarpuscleString::typeAsString (wostream &out) {
    out << "String";
}
void SkoarpuscleString::valAsString (wostream &out) {
    out << val;
}



void SkoarpuscleSymbol::asString (wostream &out) {
    out << "@" << val;
}
void SkoarpuscleSymbol::typeAsString (wostream &out) {
    out << "Symbol";
}
void SkoarpuscleSymbol::valAsString (wostream &out) {
    out << "@" << val;
}



void SkoarpuscleSymbolColon::asString (wostream &out) {
    out << "SymbolColon" << " :: " << val;
}
void SkoarpuscleSymbolColon::typeAsString (wostream &out) {
    out << "SymbolColon";
}
void SkoarpuscleSymbolColon::valAsString (wostream &out) {
    out << val;
}



void SkoarpuscleSymbolName::asString (wostream &out) {
    out << "SymbolName" << " :: " << val;
}
void SkoarpuscleSymbolName::typeAsString (wostream &out) {
    out << "SymbolName";
}
void SkoarpuscleSymbolName::valAsString (wostream &out) {
    out << val;
}



void SkoarpuscleTimes::asString (wostream &out) {
    out << "Times";
}
void SkoarpuscleTimes::typeAsString (wostream &out) {
    out << "Times";
}



void SkoarpuscleBars::asString (wostream &out) {
    out << "Bars";
}
void SkoarpuscleBars::typeAsString (wostream &out) {
    out << "Bars";
}
void SkoarpuscleBars::valAsString (wostream &out) {
    out << val;
}



void SkoarpuscleCarrots::asString (wostream &out) {
    out << "Carrots" << " :: " << val;
}
void SkoarpuscleCarrots::typeAsString (wostream &out) {
    out << "Carrots";
}
void SkoarpuscleCarrots::valAsString (wostream &out) {
    out << val;
}



void SkoarpuscleTuplet::asString (wostream &out) {
    out << "Tuplet" << " :: " << val;
}
void SkoarpuscleTuplet::typeAsString (wostream &out) {
    out << "Tuplet";
}
void SkoarpuscleTuplet::valAsString (wostream &out) {
    out << val;
}



void SkoarpuscleDynamic::asString (wostream &out) {
    out << "Dynamic" << " :: " << val;
}
void SkoarpuscleDynamic::typeAsString (wostream &out) {
    out << "Dynamic";
}
void SkoarpuscleDynamic::valAsString (wostream &out) {
    out << val;
}



void SkoarpuscleOctaveShift::asString (wostream &out) {
    out << "OctaveShift" << " :: " << val;
}
void SkoarpuscleOctaveShift::typeAsString (wostream &out) {
    out << "OctaveShift";
}
void SkoarpuscleOctaveShift::valAsString (wostream &out) {
    out << val;
}



void SkoarpuscleBooleanOp::asString (wostream &out) {
    out << "BooleanOp";
}
void SkoarpuscleBooleanOp::typeAsString (wostream &out) {
    out << "BooleanOp";
}
void SkoarpuscleBooleanOp::valAsString (wostream &out) {
    out << "BooleanOp";
}



void SkoarpuscleVoice::asString (wostream &out) {
    out << "Voice" << " :: " << val;
}
void SkoarpuscleVoice::typeAsString (wostream &out) {
    out << "Voice";
}
void SkoarpuscleVoice::valAsString (wostream &out) {
    out << val;
}


void SkoarpuscleCoda::asString (wostream &out) {
    out << "(+):" << label << " @ " << offs;
}
void SkoarpuscleCoda::typeAsString (wostream &out) {
    out << "Coda";
}
void SkoarpuscleCoda::valAsString (wostream &out) {
    out << "(+):" << label << " @ " << offs;
}


void SkoarpuscleMsgName::asString (wostream &out) {
    out << "MsgName" << " :: " << val;
}
void SkoarpuscleMsgName::typeAsString (wostream &out) {
    out << "MsgName";
}
void SkoarpuscleMsgName::valAsString (wostream &out) {
    out << val;
}



void SkoarpuscleMsgNameWithArgs::asString (wostream &out) {
    out << "MsgNameWithArgs" << " :: " << val;
}
void SkoarpuscleMsgNameWithArgs::typeAsString (wostream &out) {
    out << "MsgNameWithArgs";
}
void SkoarpuscleMsgNameWithArgs::valAsString (wostream &out) {
    out << val;
}



void SkoarpuscleMathOp::asString (wostream &out) {
    out << "MathOp" << " :: " << val;
}
void SkoarpuscleMathOp::typeAsString (wostream &out) {
    out << "MathOp";
}
void SkoarpuscleMathOp::valAsString (wostream &out) {
    out << val;
}



void SkoarpuscleList::asString (wostream &out) {
    valAsString(out);
}
void SkoarpuscleList::typeAsString (wostream &out) {
    out << "List";
}
void SkoarpuscleList::valAsString (wostream &out) {
    out << "List <";
    wstring comma (L"");
    for (auto v : *val)
    {
        out << comma;
        v->valAsString (out);
        comma = L", ";
    }
    out << ">";
}



void SkoarpuscleListSep::asString (wostream &out) {
    out << "ListSep";
}
void SkoarpuscleListSep::typeAsString (wostream &out) {
    out << "ListSep";
}
void SkoarpuscleListSep::valAsString (wostream &out) {
    out << ",";
}



void SkoarpuscleListEnd::asString (wostream &out) {
    out << "ListEnd";
}
void SkoarpuscleListEnd::typeAsString (wostream &out) {
    out << "ListEnd";
}
void SkoarpuscleListEnd::valAsString (wostream &out) {
    out << ">";
}



void SkoarpuscleDeref::asString (wostream &out) {
    out << "Deref" << " :: " << val;
}
void SkoarpuscleDeref::typeAsString (wostream &out) {
    out << "Deref";
}
void SkoarpuscleDeref::valAsString (wostream &out) {
    out << val;
}



void SkoarpuscleConditional::asString (wostream &out) {
    out << "Conditional";
}
void SkoarpuscleConditional::typeAsString (wostream &out) {
    out << "Conditional";
}
void SkoarpuscleConditional::valAsString (wostream &out) {
    out << "";
}



void SkoarpuscleBoolean::asString (wostream &out) {
    out << "Boolean";
}
void SkoarpuscleBoolean::typeAsString (wostream &out) {
    out << "Boolean";
}
void SkoarpuscleBoolean::valAsString (wostream &out) {
    out << "";
}



void SkoarpuscleLoop::asString (wostream &out) {
    out << "Loop";
}
void SkoarpuscleLoop::typeAsString (wostream &out) {
    out << "Loop";
}
void SkoarpuscleLoop::valAsString (wostream &out) {
    out << "";
}



void SkoarpuscleLoopMsg::asString (wostream &out) {
    out << "LoopMsg";
}
void SkoarpuscleLoopMsg::typeAsString (wostream &out) {
    out << "LoopMsg";
}
void SkoarpuscleLoopMsg::valAsString (wostream &out) {
    out << "";
}



void SkoarpuscleGoto::asString (wostream &out) {
    out << "Goto";
}
void SkoarpuscleGoto::typeAsString (wostream &out) {
    out << "Goto";
}
void SkoarpuscleGoto::valAsString (wostream &) {
}



void SkoarpuscleArgs::asString (wostream &out) {
    out << "Args";
}
void SkoarpuscleArgs::typeAsString (wostream &out) {
    out << "Args";
}
void SkoarpuscleArgs::valAsString (wostream &) {
}



void SkoarpuscleMsg::asString (wostream &out) {
    out << "Msg" << " :: " << val;
}
void SkoarpuscleMsg::typeAsString (wostream &out) {
    out << "Msg";
}
void SkoarpuscleMsg::valAsString (wostream &out) {
    out << val;
}



void SkoarpuscleExprEnd::asString (wostream &out) {
    out << "ExprEnd";
}
void SkoarpuscleExprEnd::typeAsString (wostream &out) {
    out << "ExprEnd";
}
void SkoarpuscleExprEnd::valAsString (wostream &) {
}



void SkoarpuscleHashLevel::asString (wostream &out) {
    out << "HashLevel" << " :: " << val;
}
void SkoarpuscleHashLevel::typeAsString (wostream &out) {
    out << "HashLevel";
}
void SkoarpuscleHashLevel::valAsString (wostream &out) {
    out << val;
}



void SkoarpusclePair::asString (wostream &out) {
    out << "Pair" << " :: " << val.first;
}
void SkoarpusclePair::typeAsString (wostream &out) {
    out << "Pair" << " :: " << val.first;
}
void SkoarpusclePair::valAsString (wostream &out) {
    out << val.first << " :: ";
    val.second->valAsString (out);
}



void SkoarpuscleExpr::asString (wostream &out) {
    out << "Expr";
}
void SkoarpuscleExpr::typeAsString (wostream &out) {
    out << "Expr";
}
void SkoarpuscleExpr::valAsString (wostream &) {
}




