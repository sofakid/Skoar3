#include "toke_inspector.hpp"

#include "event.hpp"
#include "skoar.hpp"
#include "minstrel.hpp"
#include "beaty.hpp"
#include "skoarpion_skoarpuscle.hpp"
#include "dsp.hpp"
#include "lute.hpp"
#include "meditation.hpp"
#include "fairy.hpp"
#include "exception.hpp"

static SkoarTokeInspector* inspector;
void SkoarTokeInspector::init() {
    inspector = new SkoarTokeInspector();
}

SkoarTokeInspector* SkoarTokeInspector::instance() {
    return inspector;
}

#define SpellOfToking [](SkoarToke* toke, SkoarNoadPtr noad)
#define SpellOfSimpleToking [](SkoarToke* /*toke*/, SkoarNoadPtr noad)

// ==============
// toke_inspector
// ==============
//
// Here we pick the values out of the tokens
// and set its attributes appropriately
SkoarTokeInspector::SkoarTokeInspector() : table({

    { ESkoarToke::Fairy, SpellOfSimpleToking {
        noad->skoarpuscle = make_shared<SkoarpuscleFairy>();
        noad->toke = nullptr;
    } },

    { ESkoarToke::Cat, SpellOfSimpleToking {
        noad->skoarpuscle = make_shared<SkoarpuscleCat>();
        noad->toke = nullptr;
    } },

    { ESkoarToke::True, SpellOfSimpleToking {
        noad->skoarpuscle = make_shared<SkoarpuscleTrue>();
        noad->toke = nullptr;
    } },

    { ESkoarToke::False, SpellOfSimpleToking {
        noad->skoarpuscle = make_shared<SkoarpuscleFalse>();
        noad->toke = nullptr;
    } },

    // -----------------------------------------------------------------
    { ESkoarToke::Freq, SpellOfToking {
        noad->skoarpuscle = make_shared<SkoarpuscleFreq>(toke->lexeme);
    noad->toke = nullptr;
    } },

    { ESkoarToke::Int, SpellOfToking {
        try {
            noad->skoarpuscle = make_shared<SkoarpuscleInt>(stoll(toke->lexeme));
            noad->toke = nullptr;
        }
        catch (const std::invalid_argument& /*ia*/) {
            throw SkoarDecoratingException(L"stoll - invalid arg");
        }
        catch (const std::out_of_range& /*oor*/) {
            throw SkoarDecoratingException(L"stoll - out of range");
        }
        
    } },

    { ESkoarToke::Float, SpellOfToking {
        
        try {
            noad->skoarpuscle = make_shared<SkoarpuscleFloat>(stod(toke->lexeme));
            noad->toke = nullptr;
        }
        catch (const std::invalid_argument& /*ia*/) {
            throw SkoarDecoratingException(L"stod - invalid arg");
        }
        catch (const std::out_of_range& /*oor*/) {
            throw SkoarDecoratingException(L"stod - out of range");
        }
    } },
    
    // -----------------------------------------------------------------
    { ESkoarToke::NamedNoat, SpellOfToking {
        noad->skoarpuscle = make_shared<SkoarpuscleNoat>(toke->lexeme);
        noad->toke = nullptr;
    } },

    { ESkoarToke::Choard, SpellOfToking {
        noad->skoarpuscle = make_shared<SkoarpuscleChoard>(toke->lexeme);
        noad->toke = nullptr;
    } },
    
    // -----------------------------------------------------------------
    { ESkoarToke::String, SpellOfToking {
        auto s = toke->lexeme;
        auto n = s.length();
        noad->skoarpuscle = make_shared<SkoarpuscleString>(s.substr(1, n - 2));
        noad->toke = nullptr;
    } },

    { ESkoarToke::Symbol, SpellOfToking {
        noad->skoarpuscle = make_shared<SkoarpuscleSymbol>(toke->lexeme.substr(1));
        noad->toke = nullptr;
    } },

    { ESkoarToke::SymbolName, SpellOfToking {
        noad->skoarpuscle = make_shared<SkoarpuscleSymbolName>(toke->lexeme);
        noad->toke = nullptr;
    } },

    { ESkoarToke::SymbolColon, SpellOfToking {
        noad->skoarpuscle = make_shared<SkoarpuscleSymbolColon>(toke->lexeme);
        noad->toke = nullptr;
    } },

    // -----------------------------------------------------------------
    // rests
    // } }} }}}
    { ESkoarToke::Crotchets, SpellOfToking {
        noad->skoarpuscle = make_shared<SkoarpuscleRest>(toke);
        noad->toke = nullptr;
    } },
    // o/ oo/ ooo/
    { ESkoarToke::Quavers, SpellOfToking {
        noad->skoarpuscle = make_shared<SkoarpuscleRest>(toke);
        noad->toke = nullptr;
    } },

    { ESkoarToke::Quarters, SpellOfToking {
        noad->skoarpuscle = make_shared<SkoarpuscleBeat>(toke);
        noad->toke = nullptr;
    } },

    { ESkoarToke::Eighths, SpellOfToking {
        noad->skoarpuscle = make_shared<SkoarpuscleBeat>(toke);
        noad->toke = nullptr;
    } },

    { ESkoarToke::ExactBeat, SpellOfToking {
        noad->skoarpuscle = make_shared<SkoarpuscleExactBeat>(toke);
        noad->toke = nullptr;
    } },

    { ESkoarToke::ExactRest, SpellOfToking {
        noad->skoarpuscle = make_shared<SkoarpuscleExactRest>(toke);
        noad->toke = nullptr;
    } },

    { ESkoarToke::Duration, SpellOfToking {
        noad->skoarpuscle = make_shared<SkoarpuscleDuration>(toke);
        noad->toke = nullptr;
    } },
    
    // -----------------------------------------------------------------
    { ESkoarToke::Bars, SpellOfToking {
        noad->skoarpuscle = make_shared<SkoarpuscleBars>(toke, noad);
        noad->toke = nullptr;
    } },

    { ESkoarToke::Carrot, SpellOfToking {
        noad->skoarpuscle = make_shared<SkoarpuscleCarrots>(toke);
        noad->toke = nullptr;
    } },

    { ESkoarToke::Tuplet, SpellOfToking {
        noad->skoarpuscle = make_shared<SkoarpuscleTuplet>(toke);
        noad->toke = nullptr;
    } },

    { ESkoarToke::DynPiano, SpellOfToking {
        noad->skoarpuscle = make_shared<SkoarpuscleDynamic>(toke);
        noad->toke = nullptr;
    } },

    { ESkoarToke::DynForte, SpellOfToking {
        noad->skoarpuscle = make_shared<SkoarpuscleDynamic>(toke);
        noad->toke = nullptr;
    } },

    { ESkoarToke::OctaveShift, SpellOfToking {
        noad->skoarpuscle = make_shared<SkoarpuscleOctaveShift>(toke);
        noad->toke = nullptr;
    } },

    { ESkoarToke::OttavaA, SpellOfToking {
        noad->skoarpuscle = make_shared<SkoarpuscleOctaveShift>(toke);
        noad->toke = nullptr;
    } },

    { ESkoarToke::OttavaB, SpellOfToking {
        noad->skoarpuscle = make_shared<SkoarpuscleOctaveShift>(toke);
        noad->toke = nullptr;
    } },

    { ESkoarToke::QuindicesimaA, SpellOfToking {
        noad->skoarpuscle = make_shared<SkoarpuscleOctaveShift>(toke);
        noad->toke = nullptr;
    } },

    { ESkoarToke::QuindicesimaB, SpellOfToking {
        noad->skoarpuscle = make_shared<SkoarpuscleOctaveShift>(toke);
        noad->toke = nullptr;
    } },

    { ESkoarToke::Segno, SpellOfToking {
        noad->skoarpuscle = make_shared<SkoarpuscleSegno>(noad, toke);
        noad->toke = nullptr;
    } },

    { ESkoarToke::Fine, SpellOfSimpleToking {
        noad->skoarpuscle = make_shared<SkoarpuscleFine>();
        noad->toke = nullptr;
    } },
    
    // -----------------------------------------------------------------
    { ESkoarToke::BooleanOp, SpellOfToking {
        noad->skoarpuscle = make_shared<SkoarpuscleBooleanOp>(noad, toke);
        noad->toke = nullptr;
    } },

    { ESkoarToke::Voice, SpellOfToking {
        noad->skoarpuscle = make_shared<SkoarpuscleVoice>(toke);
        noad->toke = nullptr;
    } },

    { ESkoarToke::MsgName, SpellOfToking {
        noad->skoarpuscle = make_shared<SkoarpuscleMsgName>(toke->lexeme);
        noad->toke = nullptr;
    } },

    { ESkoarToke::MsgNameWithArgs, SpellOfToking {
        auto s = toke->lexeme;
        auto n = s.length() - 1;
        noad->skoarpuscle = make_shared<SkoarpuscleMsgNameWithArgs>(s.substr(0, n));
        noad->toke = nullptr;
    } },

    { ESkoarToke::MathOp, SpellOfToking {
        noad->skoarpuscle = make_shared<SkoarpuscleMathOp>(toke);
        noad->toke = nullptr;
    } },

    { ESkoarToke::ListSep, SpellOfSimpleToking {
        auto x = make_shared<SkoarpuscleListSep>();
        noad->skoarpuscle = x;
        noad->toke = nullptr;
    } },

    { ESkoarToke::ListE, SpellOfSimpleToking {
        auto x = make_shared<SkoarpuscleListEnd>();
        noad->skoarpuscle = x;
        noad->toke = nullptr;
    } },

    // -----------------------------------------------------------------
    { ESkoarToke::Times, SpellOfSimpleToking {
        noad->skoarpuscle = make_shared<SkoarpuscleTimes>(noad);
        noad->toke = nullptr;
    } },

    { ESkoarToke::HashLevel, SpellOfToking {
        noad->skoarpuscle = make_shared<SkoarpuscleHashLevel>(toke->lexeme);
        noad->toke = nullptr;
    } },
        
    // -----------------------------------------------------------------
    { ESkoarToke::AUGen, SpellOfToking {
        noad->skoarpuscle = make_shared<SkoarpuscleUGen>(toke->lexeme.substr(1), SkoarpuscleUGen::Type::audio);
        noad->toke = nullptr;
    } },

    { ESkoarToke::KUGen, SpellOfToking {
        noad->skoarpuscle = make_shared<SkoarpuscleUGen>(toke->lexeme.substr(1), SkoarpuscleUGen::Type::control);
        noad->toke = nullptr;
    } },

    { ESkoarToke::DUGen, SpellOfToking {
        noad->skoarpuscle = make_shared<SkoarpuscleUGen>(toke->lexeme.substr(1), SkoarpuscleUGen::Type::demand);
       noad->toke = nullptr;
    } },

    { ESkoarToke::AUGenWithArgs, SpellOfToking {
        auto s = toke->lexeme;
        noad->skoarpuscle = make_shared<SkoarpuscleUGenWithArgs>(s.substr(1, s.size() - 2), SkoarpuscleUGen::Type::audio);
        noad->toke = nullptr;
    } },

    { ESkoarToke::KUGenWithArgs, SpellOfToking {
        auto s = toke->lexeme;
        noad->skoarpuscle = make_shared<SkoarpuscleUGenWithArgs>(s.substr(1, s.size() - 2), SkoarpuscleUGen::Type::control);
        noad->toke = nullptr;
    } },

    { ESkoarToke::DUGenWithArgs, SpellOfToking {
        auto s = toke->lexeme;
        noad->skoarpuscle = make_shared<SkoarpuscleUGenWithArgs>(s.substr(1, s.size() - 2), SkoarpuscleUGen::Type::demand);
        noad->toke = nullptr;
    } },

    // -----------------------------------------------------------------
    { ESkoarToke::Lute, SpellOfToking {
        noad->skoarpuscle = make_shared<SkoarpuscleLute>(toke);
        noad->toke = nullptr;
    } },

    { ESkoarToke::LuteWithArgs, SpellOfToking {
        noad->skoarpuscle = make_shared<SkoarpuscleLute>(toke);
        noad->toke = nullptr;
    } }

}) {
}

void SkoarTokeInspector::decorate(SkoarToke* toke, SkoarNoadPtr noad) {
    // it is a pair<key, value>
    auto it = table.find(toke->kind);
    if (it != table.end())
        (it->second)(toke, noad);
}
