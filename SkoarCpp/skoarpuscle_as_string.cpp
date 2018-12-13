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


void SkoarpuscleUnknown::asString (std::wostream &out) {
    out << "Unknown";
}
void SkoarpuscleUnknown::typeAsString (std::wostream &out) {
    out << "Unknown";
}
void SkoarpuscleUnknown::valAsString (std::wostream &out) {
    out << "Unknown";
}


void SkoarpuscleCat::asString (std::wostream &out) {
    out << "Cat";
}
void SkoarpuscleCat::typeAsString (std::wostream &out) {
    out << "Cat";
}
void SkoarpuscleCat::valAsString (std::wostream &out) {
    out << "=^.^=";
}



void SkoarpuscleTrue::asString (std::wostream &out) {
    out << "True";
}
void SkoarpuscleTrue::typeAsString (std::wostream &out) {
    out << "True";
}
void SkoarpuscleTrue::valAsString (std::wostream &out) {
    out << "true";
}


void SkoarpuscleFalse::asString (std::wostream &out) {
    out << "False";
}
void SkoarpuscleFalse::typeAsString (std::wostream &out) {
    out << "False";
}
void SkoarpuscleFalse::valAsString (std::wostream &out) {
    out << "false";
}





void SkoarpuscleFreq::asString (std::wostream &out) {
    out << val << "Hz";
}
void SkoarpuscleFreq::typeAsString (std::wostream &out) {
    out << "Freq";
}
void SkoarpuscleFreq::valAsString (std::wostream &out) {
    out << val << "Hz";
}



void SkoarpuscleInt::asString (std::wostream &out) {
    out << "Int" << " :: " << val;
}
void SkoarpuscleInt::typeAsString (std::wostream &out) {
    out << "Int";
}
void SkoarpuscleInt::valAsString (std::wostream &out) {
    out << val;
}



void SkoarpuscleFloat::asString (std::wostream &out) {
    out << "Float" << " :: " << val;
}
void SkoarpuscleFloat::typeAsString (std::wostream &out) {
    out << "Float";
}
void SkoarpuscleFloat::valAsString (std::wostream &out) {
    out << val;
}


void SkoarpuscleKey::asString (std::wostream & out)
{
    out << L"Key :: root :: ";
    skoarpuscle_ptr<SkoarpuscleInt> (root)->valAsString (out);
    out << L" :: scale_name :: ";
    skoarpuscle_ptr<SkoarpuscleString> (scale_name)->valAsString (out);
}



void SkoarpuscleNoat::asString (std::wostream &out) {
    out << "Noat" << " :: " << lexeme;
}
void SkoarpuscleNoat::typeAsString (std::wostream &out) {
    out << "Noat";
}
void SkoarpuscleNoat::valAsString (std::wostream &out) {
    out << lexeme;
}



void SkoarpuscleChoard::asString (std::wostream &out) {
    out << "Choard" << " :: " << lexeme;
}
void SkoarpuscleChoard::typeAsString (std::wostream &out) {
    out << "Choard";
}
void SkoarpuscleChoard::valAsString (std::wostream &out) {
    out << lexeme;
}



void SkoarpuscleString::asString (std::wostream &out) {
    out << val;
}
void SkoarpuscleString::typeAsString (std::wostream &out) {
    out << "String";
}
void SkoarpuscleString::valAsString (std::wostream &out) {
    out << val;
}



void SkoarpuscleSymbol::asString (std::wostream &out) {
    out << "@" << val;
}
void SkoarpuscleSymbol::typeAsString (std::wostream &out) {
    out << "Symbol";
}
void SkoarpuscleSymbol::valAsString (std::wostream &out) {
    out << "@" << val;
}



void SkoarpuscleSymbolColon::asString (std::wostream &out) {
    out << "SymbolColon" << " :: " << val;
}
void SkoarpuscleSymbolColon::typeAsString (std::wostream &out) {
    out << "SymbolColon";
}
void SkoarpuscleSymbolColon::valAsString (std::wostream &out) {
    out << val;
}



void SkoarpuscleSymbolName::asString (std::wostream &out) {
    out << "SymbolName" << " :: " << val;
}
void SkoarpuscleSymbolName::typeAsString (std::wostream &out) {
    out << "SymbolName";
}
void SkoarpuscleSymbolName::valAsString (std::wostream &out) {
    out << val;
}



void SkoarpuscleTimes::asString (std::wostream &out) {
    out << "Times";
}
void SkoarpuscleTimes::typeAsString (std::wostream &out) {
    out << "Times";
}



void SkoarpuscleBars::asString (std::wostream &out) {
    out << "Bars";
}
void SkoarpuscleBars::typeAsString (std::wostream &out) {
    out << "Bars";
}
void SkoarpuscleBars::valAsString (std::wostream &out) {
    out << val;
}



void SkoarpuscleCarrots::asString (std::wostream &out) {
    out << "Carrots" << " :: " << val;
}
void SkoarpuscleCarrots::typeAsString (std::wostream &out) {
    out << "Carrots";
}
void SkoarpuscleCarrots::valAsString (std::wostream &out) {
    out << val;
}



void SkoarpuscleTuplet::asString (std::wostream &out) {
    out << "Tuplet" << " :: " << val;
}
void SkoarpuscleTuplet::typeAsString (std::wostream &out) {
    out << "Tuplet";
}
void SkoarpuscleTuplet::valAsString (std::wostream &out) {
    out << val;
}



void SkoarpuscleDynamic::asString (std::wostream &out) {
    out << "Dynamic" << " :: " << val;
}
void SkoarpuscleDynamic::typeAsString (std::wostream &out) {
    out << "Dynamic";
}
void SkoarpuscleDynamic::valAsString (std::wostream &out) {
    out << val;
}



void SkoarpuscleOctaveShift::asString (std::wostream &out) {
    out << "OctaveShift" << " :: " << val;
}
void SkoarpuscleOctaveShift::typeAsString (std::wostream &out) {
    out << "OctaveShift";
}
void SkoarpuscleOctaveShift::valAsString (std::wostream &out) {
    out << val;
}



void SkoarpuscleBooleanOp::asString (std::wostream &out) {
    out << "BooleanOp";
}
void SkoarpuscleBooleanOp::typeAsString (std::wostream &out) {
    out << "BooleanOp";
}
void SkoarpuscleBooleanOp::valAsString (std::wostream &out) {
    out << "BooleanOp";
}



void SkoarpuscleVoice::asString (std::wostream &out) {
    out << "Voice" << " :: " << val;
}
void SkoarpuscleVoice::typeAsString (std::wostream &out) {
    out << "Voice";
}
void SkoarpuscleVoice::valAsString (std::wostream &out) {
    out << val;
}


void SkoarpuscleCoda::asString (std::wostream &out) {
    out << "(+):" << label << " @ " << offs;
}
void SkoarpuscleCoda::typeAsString (std::wostream &out) {
    out << "Coda";
}
void SkoarpuscleCoda::valAsString (std::wostream &out) {
    out << "(+):" << label << " @ " << offs;
}


void SkoarpuscleMsgName::asString (std::wostream &out) {
    out << "MsgName" << " :: " << val;
}
void SkoarpuscleMsgName::typeAsString (std::wostream &out) {
    out << "MsgName";
}
void SkoarpuscleMsgName::valAsString (std::wostream &out) {
    out << val;
}



void SkoarpuscleMsgNameWithArgs::asString (std::wostream &out) {
    out << "MsgNameWithArgs" << " :: " << val;
}
void SkoarpuscleMsgNameWithArgs::typeAsString (std::wostream &out) {
    out << "MsgNameWithArgs";
}
void SkoarpuscleMsgNameWithArgs::valAsString (std::wostream &out) {
    out << val;
}



void SkoarpuscleMathOp::asString (std::wostream &out) {
    out << "MathOp" << " :: " << val;
}
void SkoarpuscleMathOp::typeAsString (std::wostream &out) {
    out << "MathOp";
}
void SkoarpuscleMathOp::valAsString (std::wostream &out) {
    out << val;
}



void SkoarpuscleList::asString (std::wostream &out) {
    valAsString(out);
}
void SkoarpuscleList::typeAsString (std::wostream &out) {
    out << "List";
}
void SkoarpuscleList::valAsString (std::wostream &out) {
    out << "List <";
    std::wstring comma (L"");
    for (auto v : *val)
    {
        out << comma;
        v->valAsString (out);
        comma = L", ";
    }
    out << ">";
}



void SkoarpuscleListSep::asString (std::wostream &out) {
    out << "ListSep";
}
void SkoarpuscleListSep::typeAsString (std::wostream &out) {
    out << "ListSep";
}
void SkoarpuscleListSep::valAsString (std::wostream &out) {
    out << ",";
}



void SkoarpuscleListEnd::asString (std::wostream &out) {
    out << "ListEnd";
}
void SkoarpuscleListEnd::typeAsString (std::wostream &out) {
    out << "ListEnd";
}
void SkoarpuscleListEnd::valAsString (std::wostream &out) {
    out << ">";
}



void SkoarpuscleDeref::asString (std::wostream &out) {
    out << "Deref" << " :: " << val;
}
void SkoarpuscleDeref::typeAsString (std::wostream &out) {
    out << "Deref";
}
void SkoarpuscleDeref::valAsString (std::wostream &out) {
    out << val;
}



void SkoarpuscleConditional::asString (std::wostream &out) {
    out << "Conditional";
}
void SkoarpuscleConditional::typeAsString (std::wostream &out) {
    out << "Conditional";
}
void SkoarpuscleConditional::valAsString (std::wostream &out) {
    out << "";
}



void SkoarpuscleBoolean::asString (std::wostream &out) {
    out << "Boolean";
}
void SkoarpuscleBoolean::typeAsString (std::wostream &out) {
    out << "Boolean";
}
void SkoarpuscleBoolean::valAsString (std::wostream &out) {
    out << "";
}



void SkoarpuscleLoop::asString (std::wostream &out) {
    out << "Loop";
}
void SkoarpuscleLoop::typeAsString (std::wostream &out) {
    out << "Loop";
}
void SkoarpuscleLoop::valAsString (std::wostream &out) {
    out << "";
}



void SkoarpuscleLoopMsg::asString (std::wostream &out) {
    out << "LoopMsg";
}
void SkoarpuscleLoopMsg::typeAsString (std::wostream &out) {
    out << "LoopMsg";
}
void SkoarpuscleLoopMsg::valAsString (std::wostream &out) {
    out << "";
}



void SkoarpuscleGoto::asString (std::wostream &out) {
    out << "Goto";
}
void SkoarpuscleGoto::typeAsString (std::wostream &out) {
    out << "Goto";
}
void SkoarpuscleGoto::valAsString (std::wostream &) {
}



void SkoarpuscleArgs::asString (std::wostream &out) {
    out << "Args";
}
void SkoarpuscleArgs::typeAsString (std::wostream &out) {
    out << "Args";
}
void SkoarpuscleArgs::valAsString (std::wostream &) {
}


void SkoarpuscleExprEnd::asString (std::wostream &out) {
    out << "ExprEnd";
}
void SkoarpuscleExprEnd::typeAsString (std::wostream &out) {
    out << "ExprEnd";
}
void SkoarpuscleExprEnd::valAsString (std::wostream &) {
}



void SkoarpuscleHashLevel::asString (std::wostream &out) {
    out << "HashLevel" << " :: " << val;
}
void SkoarpuscleHashLevel::typeAsString (std::wostream &out) {
    out << "HashLevel";
}
void SkoarpuscleHashLevel::valAsString (std::wostream &out) {
    out << val;
}



void SkoarpusclePair::asString (std::wostream &out) {
    out << "Pair" << " :: " << val.first;
}
void SkoarpusclePair::typeAsString (std::wostream &out) {
    out << "Pair" << " :: " << val.first;
}
void SkoarpusclePair::valAsString (std::wostream &out) {
    out << val.first << " :: ";
    val.second->valAsString (out);
}



void SkoarpuscleExpr::asString (std::wostream &out) {
    out << "Expr";
}
void SkoarpuscleExpr::typeAsString (std::wostream &out) {
    out << "Expr";
}
void SkoarpuscleExpr::valAsString (std::wostream &) {
}




