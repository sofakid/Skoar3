#include "toke_inspector.hpp"

#include "event.hpp"
#include "skoar.hpp"
#include "minstrel.hpp"
#include "beaty.hpp"
#include "skoarpion_skoarpuscle.hpp"
#include "pitchy.hpp"
#include "dsp.hpp"
#include "lute.hpp"
#include "meditation.hpp"
#include "fairy.hpp"
#include "exception.hpp"

static SkoarTokeInspector* inspector (nullptr);
void SkoarTokeInspector::init () {
    inspector = new SkoarTokeInspector ();
}

SkoarTokeInspector* SkoarTokeInspector::instance() {
    return inspector;
}

#define SpellOfSimpleToking [] (Skoar*, SkoarNoadPtr noad, SkoarToke*)
#define SpellOfToking [] (Skoar*, SkoarNoadPtr noad, SkoarToke* toke)
#define SpellOfTokingItAll [] (Skoar* skoar, SkoarNoadPtr noad, SkoarToke* toke)

// ==============
// toke_inspector
// ==============
//
// Here we pick the values out of the tokens
// and set its attributes appropriately
SkoarTokeInspector::SkoarTokeInspector() : table({

    { ESkoarToke::Fairy, SpellOfSimpleToking {
        noad->skoarpuscle = std::make_shared<SkoarpuscleFairy>();
        noad->toke = nullptr;
    } },

    { ESkoarToke::Cat, SpellOfSimpleToking {
        noad->skoarpuscle = std::make_shared<SkoarpuscleCat>();
        noad->toke = nullptr;
    } },

    { ESkoarToke::True, SpellOfSimpleToking {
        noad->skoarpuscle = std::make_shared<SkoarpuscleTrue>();
        noad->toke = nullptr;
    } },

    { ESkoarToke::False, SpellOfSimpleToking {
        noad->skoarpuscle = std::make_shared<SkoarpuscleFalse>();
        noad->toke = nullptr;
    } },

    // -----------------------------------------------------------------
    { ESkoarToke::Freq, SpellOfToking {
        try
        {
            noad->skoarpuscle = std::make_shared<SkoarpuscleFreq> (toke->lexeme);
            noad->toke = nullptr;
        }
        catch (const std::invalid_argument& /*ia*/)
        {
            throw SkoarDecoratingException (L"stod - invalid arg");
        }
        catch (const std::out_of_range& /*oor*/)
        {
            throw SkoarDecoratingException (L"stod - out of range");
        }
    } },

    { ESkoarToke::Int, SpellOfToking {
        try {
            noad->skoarpuscle = std::make_shared<SkoarpuscleInt> (stoll (toke->lexeme));
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
            noad->skoarpuscle = std::make_shared<SkoarpuscleFloat> (stod (toke->lexeme));
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
        noad->skoarpuscle = std::make_shared<SkoarpuscleNoat> (toke->lexeme);
        noad->toke = nullptr;
    } },

    { ESkoarToke::Choard, SpellOfToking {
        noad->skoarpuscle = std::make_shared<SkoarpuscleChoard> (toke->lexeme);
        noad->toke = nullptr;
    } },
    
    // -----------------------------------------------------------------
    { ESkoarToke::String, SpellOfToking {
        auto s (toke->lexeme);
        auto n (s.length());
        noad->skoarpuscle = std::make_shared<SkoarpuscleString> (s.substr (1, n - 2));
        noad->toke = nullptr;
    } },

    { ESkoarToke::Symbol, SpellOfToking {
        noad->skoarpuscle = std::make_shared<SkoarpuscleSymbol> (toke->lexeme.substr (1));
        noad->toke = nullptr;
    } },

    { ESkoarToke::SymbolColon, SpellOfToking {
        noad->skoarpuscle = std::make_shared<SkoarpuscleSymbolColon> (toke->lexeme);
        noad->toke = nullptr;
    } },

    { ESkoarToke::SymbolName, SpellOfToking {
        noad->skoarpuscle = std::make_shared<SkoarpuscleSymbolName> (toke->lexeme);
        noad->toke = nullptr;
    } },

    // -----------------------------------------------------------------
    // rests
    // } }} }}}
    { ESkoarToke::Crotchets, SpellOfToking {
        noad->skoarpuscle = std::make_shared<SkoarpuscleRest> (toke);
        noad->toke = nullptr;
    } },
    // o/ oo/ ooo/
    { ESkoarToke::Quavers, SpellOfToking {
        noad->skoarpuscle = std::make_shared<SkoarpuscleRest> (toke);
        noad->toke = nullptr;
    } },

    { ESkoarToke::Quarters, SpellOfToking {
        noad->skoarpuscle = std::make_shared<SkoarpuscleBeat> (toke);
        noad->toke = nullptr;
    } },

    { ESkoarToke::Eighths, SpellOfToking {
        noad->skoarpuscle = std::make_shared<SkoarpuscleBeat> (toke);
        noad->toke = nullptr;
    } },

    { ESkoarToke::ExactBeat, SpellOfToking {
        noad->skoarpuscle = std::make_shared<SkoarpuscleExactBeat> (toke);
        noad->toke = nullptr;
    } },

    { ESkoarToke::ExactRest, SpellOfToking {
        noad->skoarpuscle = std::make_shared<SkoarpuscleExactRest> (toke);
        noad->toke = nullptr;
    } },

    { ESkoarToke::Duration, SpellOfToking {
        noad->skoarpuscle = std::make_shared<SkoarpuscleDuration> (toke);
        noad->toke = nullptr;
    } },
    
    // -----------------------------------------------------------------
    { ESkoarToke::Bars, SpellOfToking {
        noad->skoarpuscle = std::make_shared<SkoarpuscleBars> (toke, noad);
        noad->toke = nullptr;
    } },

    { ESkoarToke::Carrot, SpellOfToking {
        noad->skoarpuscle = std::make_shared<SkoarpuscleCarrots> (toke);
        noad->toke = nullptr;
    } },

    { ESkoarToke::Tuplet, SpellOfToking {
        noad->skoarpuscle = std::make_shared<SkoarpuscleTuplet> (toke);
        noad->toke = nullptr;
    } },

    { ESkoarToke::OctaveShift, SpellOfToking {
        noad->skoarpuscle = std::make_shared<SkoarpuscleOctaveShift> (toke);
        noad->toke = nullptr;
    } },

    { ESkoarToke::Coda, SpellOfToking {
        noad->skoarpuscle = std::make_shared<SkoarpuscleCoda> (noad, toke);
        noad->toke = nullptr;
    } },
 
    // -----------------------------------------------------------------
    { ESkoarToke::BooleanOr, SpellOfToking {
        noad->skoarpuscle = std::make_shared<SkoarpuscleBooleanOp> (noad, toke);
        noad->toke = nullptr;
    } },

    { ESkoarToke::BooleanAnd, SpellOfToking {
        noad->skoarpuscle = std::make_shared<SkoarpuscleBooleanOp> (noad, toke);
        noad->toke = nullptr;
    } },

    { ESkoarToke::CmpEqNeq, SpellOfToking {
        noad->skoarpuscle = std::make_shared<SkoarpuscleBooleanOp> (noad, toke);
        noad->toke = nullptr;
    } },

    { ESkoarToke::CmpGtLt, SpellOfToking {
        noad->skoarpuscle = std::make_shared<SkoarpuscleBooleanOp> (noad, toke);
        noad->toke = nullptr;
    } },

    { ESkoarToke::Voice, SpellOfTokingItAll {
        std::shared_ptr<SkoarpuscleVoice> v = std::make_shared<SkoarpuscleVoice> (toke);
        noad->skoarpuscle = v;
        noad->toke = nullptr;
        noad->voice = skoar->get_voice (v->val);
    } },

    { ESkoarToke::MsgName, SpellOfToking {
        noad->skoarpuscle = std::make_shared<SkoarpuscleMsgName> (toke->lexeme);
        noad->toke = nullptr;
    } },

    { ESkoarToke::MsgNameWithArgs, SpellOfToking {
        auto s (toke->lexeme);
        auto n (s.length () - 1);
        noad->skoarpuscle = std::make_shared<SkoarpuscleMsgNameWithArgs> (s.substr (0, n));
        noad->toke = nullptr;
    } },

    { ESkoarToke::MathOpAddSub, SpellOfToking {
        noad->skoarpuscle = std::make_shared<SkoarpuscleMathOp> (toke);
        noad->toke = nullptr;
    } },

    { ESkoarToke::MathOpMulDivMod, SpellOfToking {
        noad->skoarpuscle = std::make_shared<SkoarpuscleMathOp> (toke);
        noad->toke = nullptr;
    } },

    { ESkoarToke::ListSep, SpellOfSimpleToking {
        auto x (std::make_shared<SkoarpuscleListSep> ());
        noad->skoarpuscle = x;
        noad->toke = nullptr;
    } },

    { ESkoarToke::ListE, SpellOfSimpleToking {
        auto x (std::make_shared<SkoarpuscleListEnd> ());
        noad->skoarpuscle = x;
        noad->toke = nullptr;
    } },

    // -----------------------------------------------------------------
    { ESkoarToke::Times, SpellOfSimpleToking {
        noad->skoarpuscle = std::make_shared<SkoarpuscleTimes> (noad);
        noad->toke = nullptr;
    } },

    { ESkoarToke::HashLevel, SpellOfToking {
        noad->skoarpuscle = std::make_shared<SkoarpuscleHashLevel> (toke->lexeme);
        noad->toke = nullptr;
    } },
        
    // -----------------------------------------------------------------
    { ESkoarToke::AUGen, SpellOfToking {
        noad->skoarpuscle = std::make_shared<SkoarpuscleUGen> (toke->lexeme.substr (1), SkoarpuscleUGen::Type::audio);
        noad->toke = nullptr;
    } },

    { ESkoarToke::KUGen, SpellOfToking {
        noad->skoarpuscle = std::make_shared<SkoarpuscleUGen> (toke->lexeme.substr (1), SkoarpuscleUGen::Type::control);
        noad->toke = nullptr;
    } },

    { ESkoarToke::DUGen, SpellOfToking {
       noad->skoarpuscle = std::make_shared<SkoarpuscleUGen>(toke->lexeme.substr (1), SkoarpuscleUGen::Type::demand);
       noad->toke = nullptr;
    } },

    { ESkoarToke::AUGenWithArgs, SpellOfToking {
        auto s (toke->lexeme);
        noad->skoarpuscle = std::make_shared<SkoarpuscleUGenWithArgs>(s.substr(1, s.size () - 2), SkoarpuscleUGen::Type::audio);
        noad->toke = nullptr;
    } },

    { ESkoarToke::KUGenWithArgs, SpellOfToking {
        auto s (toke->lexeme);
        noad->skoarpuscle = std::make_shared<SkoarpuscleUGenWithArgs>(s.substr(1, s.size () - 2), SkoarpuscleUGen::Type::control);
        noad->toke = nullptr;
    } },

    { ESkoarToke::DUGenWithArgs, SpellOfToking {
        auto s (toke->lexeme);
        noad->skoarpuscle = std::make_shared<SkoarpuscleUGenWithArgs>(s.substr(1, s.size () - 2), SkoarpuscleUGen::Type::demand);
        noad->toke = nullptr;
    } },

    // -----------------------------------------------------------------
    { ESkoarToke::Lute, SpellOfToking {
        noad->skoarpuscle = std::make_shared<SkoarpuscleLute> (toke);
        noad->toke = nullptr;
    } },

    { ESkoarToke::LuteWithArgs, SpellOfToking {
        noad->skoarpuscle = std::make_shared<SkoarpuscleLute> (toke);
        noad->toke = nullptr;
    } }

}) {
}

void SkoarTokeInspector::decorate(Skoar* skoar, SkoarNoadPtr noad, SkoarToke* toke) {
    // it is a pair<key, value>
    auto it (table.find (toke->kind));
    if (it != table.end ())
        (it->second) (skoar, noad, toke);
}
