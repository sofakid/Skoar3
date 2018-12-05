#include "operators.hpp"
#include "magic_words.hpp"

#define MathMagicWithM [](SkoarpusclePtr x, SkoarpusclePtr y, SkoarMinstrelPtr m)
#define MathMagicJustX [](SkoarpusclePtr x, SkoarpusclePtr, SkoarMinstrelPtr)
#define MathMagicJustY [](SkoarpusclePtr, SkoarpusclePtr y, SkoarMinstrelPtr)
#define MathMagicNoArgs [](SkoarpusclePtr, SkoarpusclePtr, SkoarMinstrelPtr)
#define MathMagic [](SkoarpusclePtr x, SkoarpusclePtr y, SkoarMinstrelPtr)
#define EMath ESkoarpuscle

#define JustACat MathMagicNoArgs { return make_skoarpuscle (nullptr); }
#define JustX MathMagicJustX { return x; }
#define JustY MathMagicJustY { return y; }
#define JustZero MathMagicNoArgs { return 0.0; }
#define JustOne MathMagicNoArgs { return 1.0; }

class SkoarOpsTables
{
public:

    XTable assignment = {
        { EMath::Symbol, { {
            EMath::Any, MathMagicWithM {
                auto str (skoarpuscle_ptr<SkoarpuscleSymbol> (x)->val);
                if (handle_magic_words (str, y, m))
                    return y;
                m->koar->put (str, y); return y; }
            } } },

        { EMath::SymbolColon, { {
            EMath::Any, MathMagicWithM {
            auto str (skoarpuscle_ptr<SkoarpuscleSymbolColon> (x)->val);
            if (handle_magic_words (str, y, m))
                return y;
            m->koar->put (str, y); return y; }
        } } }

    };


    XTable addition = {
        { EMath::Cat, { { EMath::Any, MathMagicNoArgs { return make_skoarpuscle (nullptr); } } } },
        { EMath::False, { { EMath::Any, JustX } } },
        { EMath::True, { { EMath::Any, JustY } } },

        { EMath::Envelope, { { EMath::Any, MathMagicNoArgs { return make_skoarpuscle (nullptr); } } } },

        { EMath::UGen, {
            { EMath::Int,       MathMagic { return skoarpuscle_ptr<SkoarpuscleUGen> (x)->add (y); } },
            { EMath::Float,     MathMagic { return skoarpuscle_ptr<SkoarpuscleUGen> (x)->add (y); } },
            { EMath::HashLevel, MathMagic { return skoarpuscle_ptr<SkoarpuscleUGen> (x)->add (y); } },
            { EMath::Freq,      JustACat },

            { EMath::Noat,   JustACat },
            { EMath::Choard, JustACat },

            { EMath::False, MathMagicJustX { return skoarpuscle_ptr<SkoarpuscleUGen> (x)->mul (make_skoarpuscle (0.0)); } },
            { EMath::True,  JustX },

            { EMath::Symbol, JustACat },
            { EMath::String, JustACat },

            { EMath::List,     JustACat },
            { EMath::UGen,     MathMagic { return skoarpuscle_ptr<SkoarpuscleUGen> (y)->add (x); } },
            { EMath::Envelope, JustACat }
        } },

        { EMath::Int, {
            { EMath::Int,       MathMagic {
                return make_skoarpuscle (
                    skoarpuscle_ptr<SkoarpuscleInt> (x)->val +
                    skoarpuscle_ptr<SkoarpuscleInt> (y)->val
                );
            } },
            { EMath::Float,     MathMagic {
                return make_skoarpuscle (
                    static_cast<SkoarFloat>(skoarpuscle_ptr<SkoarpuscleInt> (x)->val) +
                    skoarpuscle_ptr<SkoarpuscleFloat> (y)->val
                );
            } },

            { EMath::HashLevel, MathMagic {
                return make_skoarpuscle (
                    static_cast<SkoarFloat>(skoarpuscle_ptr<SkoarpuscleInt> (x)->val) +
                    skoarpuscle_ptr<SkoarpuscleHashLevel> (y)->val
                );
            } },
            { EMath::Freq,      MathMagic {
                return make_shared<SkoarpuscleFreq> (
                    static_cast<SkoarFloat>(skoarpuscle_ptr<SkoarpuscleInt> (x)->val) +
                    skoarpuscle_ptr<SkoarpuscleFreq> (y)->val
                );
            } },

            { EMath::Noat,   JustACat },
            { EMath::Choard, JustACat },

            { EMath::False, JustY },
            { EMath::True,  JustX },

            { EMath::Symbol, JustACat },
            { EMath::String, JustACat },

            { EMath::List,     JustACat },
            { EMath::UGen,     JustACat },
            { EMath::Envelope, JustACat }
        } },

        { EMath::Float, {
            { EMath::Int, MathMagic {
                return make_skoarpuscle (
                    skoarpuscle_ptr<SkoarpuscleFloat> (x)->val +
                    static_cast<SkoarFloat> (skoarpuscle_ptr<SkoarpuscleInt> (y)->val)
                );
            } },
            { EMath::Float, MathMagic {
                return make_skoarpuscle (
                    skoarpuscle_ptr<SkoarpuscleFloat> (x)->val +
                    skoarpuscle_ptr<SkoarpuscleFloat> (y)->val
                );
            } },
            { EMath::HashLevel, MathMagic {
                return make_skoarpuscle (
                    skoarpuscle_ptr<SkoarpuscleFloat> (x)->val +
                    skoarpuscle_ptr<SkoarpuscleHashLevel> (y)->val
                );
            } },
            { EMath::Freq, MathMagic {
                return make_shared<SkoarpuscleFreq> (
                    skoarpuscle_ptr<SkoarpuscleFloat> (x)->val +
                    skoarpuscle_ptr<SkoarpuscleFreq> (y)->val
                );
            } },

            { EMath::Noat,   JustACat },
            { EMath::Choard, JustACat },

            { EMath::False, JustY },
            { EMath::True,  JustX },

            { EMath::Symbol, JustACat },
            { EMath::String, JustACat },

            { EMath::List, JustACat },
            { EMath::UGen, JustACat },
            { EMath::Envelope, JustACat }
        } },

        { EMath::HashLevel, {
            { EMath::Int, MathMagic {
                return make_skoarpuscle (
                    skoarpuscle_ptr<SkoarpuscleHashLevel> (x)->val +
                    static_cast<SkoarFloat> (skoarpuscle_ptr<SkoarpuscleInt> (y)->val)
                );
            } },
            { EMath::Float, MathMagic {
                return make_skoarpuscle (
                    skoarpuscle_ptr<SkoarpuscleHashLevel> (x)->val +
                    skoarpuscle_ptr<SkoarpuscleFloat> (y)->val
                );
            } },
            { EMath::HashLevel, MathMagic {
                return make_shared<SkoarpuscleHashLevel> (
                    skoarpuscle_ptr<SkoarpuscleHashLevel> (x)->val +
                    skoarpuscle_ptr<SkoarpuscleHashLevel> (y)->val
                );
            } },
            { EMath::Freq, MathMagic {
                return make_shared<SkoarpuscleFreq> (
                    skoarpuscle_ptr<SkoarpuscleFloat> (x)->val +
                    skoarpuscle_ptr<SkoarpuscleFreq> (y)->val
                    );
            } },

            { EMath::Noat,   JustACat },
            { EMath::Choard, JustACat },

            { EMath::False, JustY },
            { EMath::True,  JustX },

            { EMath::Symbol, JustACat },
            { EMath::String, JustACat },

            { EMath::List, JustACat},
            { EMath::UGen, JustACat },
            { EMath::Envelope, JustACat }
        } }


    };

    XTable subtraction = {
        { EMath::Cat, { { EMath::Any, JustACat } } },
        { EMath::False, { { EMath::Any, JustX } } },
        { EMath::True, { { EMath::Any, JustY } } },

        { EMath::Envelope, { { EMath::Any, JustACat } } },

        { EMath::UGen, {
            { EMath::Int,       MathMagic { return skoarpuscle_ptr<SkoarpuscleUGen> (x)->sub (y); } },
            { EMath::Float,     MathMagic { return skoarpuscle_ptr<SkoarpuscleUGen> (x)->sub (y); } },
            { EMath::HashLevel, MathMagic { return skoarpuscle_ptr<SkoarpuscleUGen> (x)->sub (y); } },
            { EMath::Freq,      JustACat },

            { EMath::Noat,   JustACat},
            { EMath::Choard, JustACat },

            { EMath::False, MathMagicJustX { return skoarpuscle_ptr<SkoarpuscleUGen> (x)->mul (make_skoarpuscle (0.0)); } },
            { EMath::True,  JustX },

            { EMath::Symbol, JustACat },
            { EMath::String, JustACat },

            { EMath::List,     JustACat },
            { EMath::UGen,     MathMagic { return skoarpuscle_ptr<SkoarpuscleUGen> (y)->sub (x); } },
            { EMath::Envelope, JustACat }
        } },

        { EMath::Int, {
            { EMath::Int,       MathMagic {
                return make_skoarpuscle (
                    skoarpuscle_ptr<SkoarpuscleInt> (x)->val -
                    skoarpuscle_ptr<SkoarpuscleInt> (y)->val
                );
            } },
            { EMath::Float,     MathMagic {
                return make_skoarpuscle (
                    static_cast<SkoarFloat>(skoarpuscle_ptr<SkoarpuscleInt> (x)->val) -
                    skoarpuscle_ptr<SkoarpuscleFloat> (y)->val
                );
            } },

            { EMath::HashLevel, MathMagic {
                return make_skoarpuscle (
                    static_cast<SkoarFloat>(skoarpuscle_ptr<SkoarpuscleInt> (x)->val) -
                    skoarpuscle_ptr<SkoarpuscleHashLevel> (y)->val
                );
            } },
            { EMath::Freq,      MathMagic {
                return make_shared<SkoarpuscleFreq> (
                    static_cast<SkoarFloat>(skoarpuscle_ptr<SkoarpuscleInt> (x)->val) -
                    skoarpuscle_ptr<SkoarpuscleFreq> (y)->val
                    );
            } },

            { EMath::Noat,   JustACat },
            { EMath::Choard, JustACat },

            { EMath::False, JustY },
            { EMath::True,  JustX },

            { EMath::Symbol, JustACat },
            { EMath::String, JustACat },

            { EMath::List,     JustACat },
            { EMath::UGen,     JustACat },
            { EMath::Envelope, JustACat }
        } },

        { EMath::Float, {
            { EMath::Int, MathMagic {
                return make_skoarpuscle (
                    skoarpuscle_ptr<SkoarpuscleFloat> (x)->val -
                    static_cast<SkoarFloat> (skoarpuscle_ptr<SkoarpuscleInt> (y)->val)
                );
            } },
            { EMath::Float, MathMagic {
                return make_skoarpuscle (
                    skoarpuscle_ptr<SkoarpuscleFloat> (x)->val -
                    skoarpuscle_ptr<SkoarpuscleFloat> (y)->val
                );
            } },
            { EMath::HashLevel, MathMagic {
                return make_skoarpuscle (
                    skoarpuscle_ptr<SkoarpuscleFloat> (x)->val -
                    skoarpuscle_ptr<SkoarpuscleHashLevel> (y)->val
                );
            } },
            { EMath::Freq, MathMagic {
                return make_shared<SkoarpuscleFreq> (
                    skoarpuscle_ptr<SkoarpuscleFloat> (x)->val -
                    skoarpuscle_ptr<SkoarpuscleFreq> (y)->val
                    );
            } },

            { EMath::Noat,   JustACat },
            { EMath::Choard, JustACat },

            { EMath::False, JustY },
            { EMath::True,  JustX },

            { EMath::Symbol, JustACat },
            { EMath::String, JustACat },

            { EMath::List, JustACat },
            { EMath::UGen, JustACat },
            { EMath::Envelope, JustACat }
        } },

        { EMath::HashLevel, {
            { EMath::Int, MathMagic {
                return make_skoarpuscle (
                    skoarpuscle_ptr<SkoarpuscleHashLevel> (x)->val -
                    static_cast<SkoarFloat> (skoarpuscle_ptr<SkoarpuscleInt> (y)->val)
                );
            } },
            { EMath::Float, MathMagic {
                return make_skoarpuscle (
                    skoarpuscle_ptr<SkoarpuscleHashLevel> (x)->val -
                    skoarpuscle_ptr<SkoarpuscleFloat> (y)->val
                );
            } },
            { EMath::HashLevel, MathMagic {
                return make_shared<SkoarpuscleHashLevel> (
                    skoarpuscle_ptr<SkoarpuscleHashLevel> (x)->val -
                    skoarpuscle_ptr<SkoarpuscleHashLevel> (y)->val
                    );
            } },
            { EMath::Freq, MathMagic {
                return make_shared<SkoarpuscleFreq> (
                    skoarpuscle_ptr<SkoarpuscleFloat> (x)->val -
                    skoarpuscle_ptr<SkoarpuscleFreq> (y)->val
                    );
            } },

            { EMath::Noat,   JustACat },
            { EMath::Choard, JustACat },

            { EMath::False, JustY },
            { EMath::True,  JustX },

            { EMath::Symbol, JustACat },
            { EMath::String, JustACat },

            { EMath::List, JustACat },
            { EMath::UGen, JustACat },
            { EMath::Envelope, JustACat }
        } }


    };

    XTable multiplication = {
        { EMath::Cat, { { EMath::Any, JustACat } } },
        { EMath::False, { { EMath::Any, JustX } } },
        { EMath::True, { { EMath::Any, JustY } } },

        { EMath::Envelope, { { EMath::Any, JustACat } } },

        { EMath::UGen, {
            { EMath::Int,       MathMagic { return skoarpuscle_ptr<SkoarpuscleUGen> (x)->mul (y); } },
            { EMath::Float,     MathMagic { return skoarpuscle_ptr<SkoarpuscleUGen> (x)->mul (y); } },
            { EMath::HashLevel, MathMagic { return skoarpuscle_ptr<SkoarpuscleUGen> (x)->mul (y); } },
            { EMath::Freq,      JustACat },

            { EMath::Noat,   JustACat },
            { EMath::Choard, JustACat },

            { EMath::False, MathMagicJustX { return skoarpuscle_ptr<SkoarpuscleUGen> (x)->mul (make_skoarpuscle (0.0)); } },
            { EMath::True,  JustX },

            { EMath::Symbol, JustACat },
            { EMath::String, JustACat },

            { EMath::List,     JustACat },
            { EMath::UGen,     MathMagic { return skoarpuscle_ptr<SkoarpuscleUGen> (y)->add (x); } },
            { EMath::Envelope, JustACat }
        } },

        { EMath::Int, {
            { EMath::Int,       MathMagic {
                return make_skoarpuscle (
                    skoarpuscle_ptr<SkoarpuscleInt> (x)->val *
                    skoarpuscle_ptr<SkoarpuscleInt> (y)->val
                );
            } },
            { EMath::Float,     MathMagic {
                return make_skoarpuscle (
                    static_cast<SkoarFloat>(skoarpuscle_ptr<SkoarpuscleInt> (x)->val) *
                    skoarpuscle_ptr<SkoarpuscleFloat> (y)->val
                );
            } },

            { EMath::HashLevel, MathMagic {
                return make_skoarpuscle (
                    static_cast<SkoarFloat>(skoarpuscle_ptr<SkoarpuscleInt> (x)->val) *
                    skoarpuscle_ptr<SkoarpuscleHashLevel> (y)->val
                );
            } },
            { EMath::Freq,      MathMagic {
                return make_shared<SkoarpuscleFreq> (
                    static_cast<SkoarFloat>(skoarpuscle_ptr<SkoarpuscleInt> (x)->val) *
                    skoarpuscle_ptr<SkoarpuscleFreq> (y)->val
                    );
            } },

            { EMath::Noat,   JustACat },
            { EMath::Choard, JustACat },

            { EMath::False, JustY },
            { EMath::True,  JustX },

            { EMath::Symbol, JustACat },
            { EMath::String, JustACat },

            { EMath::List,     JustACat },
            { EMath::UGen,     JustACat },
            { EMath::Envelope, JustACat }
        } },

        { EMath::Float, {
            { EMath::Int, MathMagic {
                return make_skoarpuscle (
                    skoarpuscle_ptr<SkoarpuscleFloat> (x)->val *
                    static_cast<SkoarFloat> (skoarpuscle_ptr<SkoarpuscleInt> (y)->val)
                );
            } },
            { EMath::Float, MathMagic {
                return make_skoarpuscle (
                    skoarpuscle_ptr<SkoarpuscleFloat> (x)->val *
                    skoarpuscle_ptr<SkoarpuscleFloat> (y)->val
                );
            } },
            { EMath::HashLevel, MathMagic {
                return make_skoarpuscle (
                    skoarpuscle_ptr<SkoarpuscleFloat> (x)->val *
                    skoarpuscle_ptr<SkoarpuscleHashLevel> (y)->val
                );
            } },
            { EMath::Freq, MathMagic {
                return make_shared<SkoarpuscleFreq> (
                    skoarpuscle_ptr<SkoarpuscleFloat> (x)->val *
                    skoarpuscle_ptr<SkoarpuscleFreq> (y)->val
                    );
            } },

            { EMath::Noat,   JustACat },
            { EMath::Choard, JustACat },

            { EMath::False, JustY },
            { EMath::True,  JustX },

            { EMath::Symbol, JustACat },
            { EMath::String, JustACat },

            { EMath::List, JustACat },
            { EMath::UGen, JustACat },
            { EMath::Envelope, JustACat }
        } },

        { EMath::HashLevel, {
            { EMath::Int, MathMagic {
                return make_skoarpuscle (
                    skoarpuscle_ptr<SkoarpuscleHashLevel> (x)->val *
                    static_cast<SkoarFloat> (skoarpuscle_ptr<SkoarpuscleInt> (y)->val)
                );
            } },
            { EMath::Float, MathMagic {
                return make_skoarpuscle (
                    skoarpuscle_ptr<SkoarpuscleHashLevel> (x)->val *
                    skoarpuscle_ptr<SkoarpuscleFloat> (y)->val
                );
            } },
            { EMath::HashLevel, MathMagic {
                return make_shared<SkoarpuscleHashLevel> (
                    skoarpuscle_ptr<SkoarpuscleHashLevel> (x)->val *
                    skoarpuscle_ptr<SkoarpuscleHashLevel> (y)->val
                    );
            } },
            { EMath::Freq, MathMagic {
                return make_shared<SkoarpuscleFreq> (
                    skoarpuscle_ptr<SkoarpuscleFloat> (x)->val *
                    skoarpuscle_ptr<SkoarpuscleFreq> (y)->val
                    );
            } },

            { EMath::Noat,   JustACat },
            { EMath::Choard, JustACat },

            { EMath::False, JustY },
            { EMath::True,  JustX },

            { EMath::Symbol, JustACat },
            { EMath::String, JustACat },

            { EMath::List, JustACat },
            { EMath::UGen, JustACat },
            { EMath::Envelope, JustACat }
        } }


    };

    XTable division = {
        { EMath::Cat, { { EMath::Any, JustACat } } },
        { EMath::False, { { EMath::Any, JustX } } },
        { EMath::True, { { EMath::Any, JustY } } },

        { EMath::Envelope, { { EMath::Any, JustACat } } },

        { EMath::UGen, {
            { EMath::Int,       MathMagic { return skoarpuscle_ptr<SkoarpuscleUGen> (x)->divBy (y); } },
            { EMath::Float,     MathMagic { return skoarpuscle_ptr<SkoarpuscleUGen> (x)->divBy (y); } },
            { EMath::HashLevel, MathMagic { return skoarpuscle_ptr<SkoarpuscleUGen> (x)->divBy (y); } },
            { EMath::Freq,      JustACat },

            { EMath::Noat,   JustACat },
            { EMath::Choard, JustACat },

            { EMath::False, MathMagicJustX { return skoarpuscle_ptr<SkoarpuscleUGen> (x)->mul (make_skoarpuscle (0.0)); } },
            { EMath::True,  JustX },

            { EMath::Symbol, JustACat },
            { EMath::String, JustACat },

            { EMath::List,     JustACat },
            { EMath::UGen,     MathMagic { return skoarpuscle_ptr<SkoarpuscleUGen> (y)->divBy (x); } },
            { EMath::Envelope, JustACat }
        } },

        { EMath::Int, {
            { EMath::Int,       MathMagic {
                auto& denom (skoarpuscle_ptr<SkoarpuscleInt> (y)->val);
                if (denom == 0)
                    return make_skoarpuscle (nullptr);
                return make_skoarpuscle (
                    skoarpuscle_ptr<SkoarpuscleInt> (x)->val /
                    denom
                );
            } },
            { EMath::Float,     MathMagic {
                auto& denom (skoarpuscle_ptr<SkoarpuscleFloat> (y)->val);
                if (denom == 0.0)
                    return make_skoarpuscle (nullptr);
                return make_skoarpuscle (
                    static_cast<SkoarFloat>(skoarpuscle_ptr<SkoarpuscleInt> (x)->val) /
                    denom
                );
            } },

            { EMath::HashLevel, MathMagic {
                auto& denom (skoarpuscle_ptr<SkoarpuscleHashLevel> (y)->val);
                if (denom == 0.0)
                    return make_skoarpuscle (nullptr);
                return make_skoarpuscle (
                    static_cast<SkoarFloat>(skoarpuscle_ptr<SkoarpuscleInt> (x)->val) /
                    denom
                );
            } },

            { EMath::Noat,   JustACat },
            { EMath::Choard, JustACat },

            { EMath::False, JustY },
            { EMath::True,  JustX },

            { EMath::Symbol, JustACat },
            { EMath::String, JustACat },

            { EMath::List,     JustACat },
            { EMath::UGen,     JustACat },
            { EMath::Envelope, JustACat }
        } },

        { EMath::Float, {
            { EMath::Int, MathMagic {
                auto& denom (skoarpuscle_ptr<SkoarpuscleInt> (y)->val);
                if (denom == 0)
                    return make_skoarpuscle (nullptr);
                return make_skoarpuscle (
                    skoarpuscle_ptr<SkoarpuscleFloat> (x)->val /
                    static_cast<SkoarFloat> (denom)
                );
            } },
            { EMath::Float, MathMagic {
                auto& denom (skoarpuscle_ptr<SkoarpuscleFloat> (y)->val);
                if (denom == 0.0)
                    return make_skoarpuscle (nullptr);
                return make_skoarpuscle (
                    skoarpuscle_ptr<SkoarpuscleFloat> (x)->val /
                    denom
                );
            } },
            { EMath::HashLevel, MathMagic {
                auto& denom (skoarpuscle_ptr<SkoarpuscleHashLevel> (y)->val);
                if (denom == 0.0)
                    return make_skoarpuscle (nullptr);
                return make_skoarpuscle (
                    skoarpuscle_ptr<SkoarpuscleFloat> (x)->val /
                    denom
                );
            } },

            { EMath::Noat,   JustACat },
            { EMath::Choard, JustACat },

            { EMath::False, JustY },
            { EMath::True,  JustX },

            { EMath::Symbol, JustACat },
            { EMath::String, JustACat },

            { EMath::List, JustACat },
            { EMath::UGen, JustACat },
            { EMath::Envelope, JustACat }
        } },

        { EMath::HashLevel, {
            { EMath::Int, MathMagic {
                auto& denom (skoarpuscle_ptr<SkoarpuscleInt> (y)->val);
                if (denom == 0)
                    return make_skoarpuscle (nullptr);
                return make_skoarpuscle (
                    skoarpuscle_ptr<SkoarpuscleHashLevel> (x)->val /
                    static_cast<SkoarFloat> (denom)
                );
            } },
            { EMath::Float, MathMagic {
                auto& denom (skoarpuscle_ptr<SkoarpuscleFloat> (y)->val);
                if (denom == 0.0)
                    return make_skoarpuscle (nullptr);
                return make_skoarpuscle (
                    skoarpuscle_ptr<SkoarpuscleHashLevel> (x)->val / denom
                );
            } },
            { EMath::HashLevel, MathMagic {
                auto& denom (skoarpuscle_ptr<SkoarpuscleHashLevel> (y)->val);
                if (denom == 0.0)
                    return make_skoarpuscle (nullptr);
                return static_cast<SkoarpusclePtr> (
                    make_shared<SkoarpuscleHashLevel> (
                    skoarpuscle_ptr<SkoarpuscleHashLevel> (x)->val / denom
                    ));
            } },


            { EMath::Noat,   JustACat },
            { EMath::Choard, JustACat },

            { EMath::False, JustY },
            { EMath::True,  JustX },

            { EMath::Symbol, JustACat },
            { EMath::String, JustACat },

            { EMath::List, JustACat },
            { EMath::UGen, JustACat },
            { EMath::Envelope, JustACat }
        } }
    };

    XTable modulo = {
        { EMath::Cat, { { EMath::Any, JustACat } } },
        { EMath::False, { { EMath::Any, JustACat } } },
        { EMath::True, { { EMath::Any, JustACat } } },

        { EMath::Envelope, { { EMath::Any, JustACat } } },

        { EMath::UGen, {
            { EMath::Int,       MathMagic { return skoarpuscle_ptr<SkoarpuscleUGen> (x)->divBy (y); } },
            { EMath::Float,     MathMagic { return skoarpuscle_ptr<SkoarpuscleUGen> (x)->divBy (y); } },
            { EMath::HashLevel, MathMagic { return skoarpuscle_ptr<SkoarpuscleUGen> (x)->divBy (y); } },
            { EMath::Freq,      JustACat },

            { EMath::Noat,   JustACat },
            { EMath::Choard, JustACat },

            { EMath::False, MathMagicJustX { return skoarpuscle_ptr<SkoarpuscleUGen> (x)->mul (make_skoarpuscle (0.0)); } },
            { EMath::True,  JustX },

            { EMath::Symbol, JustACat },
            { EMath::String, JustACat },

            { EMath::List,     JustACat },
            { EMath::UGen,     MathMagic { return skoarpuscle_ptr<SkoarpuscleUGen> (y)->divBy (x); } },
            { EMath::Envelope, JustACat }
        } },

        { EMath::Int, {
            { EMath::Int,       MathMagic {
                auto& denom (skoarpuscle_ptr<SkoarpuscleInt> (y)->val);
                if (denom == 0)
                    return make_skoarpuscle (nullptr);
                return make_skoarpuscle (
                    skoarpuscle_ptr<SkoarpuscleInt> (x)->val %
                    denom
                );
            } },
            { EMath::Float,     MathMagic {
                auto& denom (skoarpuscle_ptr<SkoarpuscleFloat> (y)->val);
                if (denom == 0.0)
                    return make_skoarpuscle (nullptr);
                return make_skoarpuscle (
                    static_cast<SkoarFloat>(
                        skoarpuscle_ptr<SkoarpuscleInt> (x)->val %
                        static_cast<SkoarInt>(denom)
                    )
                );
            } },

            { EMath::HashLevel, JustACat },

            { EMath::Noat,   JustACat },
            { EMath::Choard, JustACat },

            { EMath::False, JustY },
            { EMath::True,  JustX },

            { EMath::Symbol, JustACat },
            { EMath::String, JustACat },

            { EMath::List,     JustACat },
            { EMath::UGen,     JustACat },
            { EMath::Envelope, JustACat }
        } },

        { EMath::Float, {
            { EMath::Int, MathMagic {
                auto& denom (skoarpuscle_ptr<SkoarpuscleInt> (y)->val);
                if (denom == 0)
                    return make_skoarpuscle (nullptr);
                return make_skoarpuscle (
                    static_cast<SkoarFloat>(
                        static_cast<SkoarInt>(skoarpuscle_ptr<SkoarpuscleFloat> (x)->val) %
                        denom
                    )
                );
            } },
            { EMath::Float, MathMagic {
                auto& denom (skoarpuscle_ptr<SkoarpuscleFloat> (y)->val);
                if (denom == 0.0)
                    return make_skoarpuscle (nullptr);
                return make_skoarpuscle (
                    static_cast<SkoarFloat>(
                        static_cast<SkoarInt>(skoarpuscle_ptr<SkoarpuscleFloat> (x)->val) %
                        static_cast<SkoarInt>(denom)
                    )
                );
            } },
            { EMath::HashLevel, JustACat },

            { EMath::Noat,   JustACat },
            { EMath::Choard, JustACat },

            { EMath::False, JustY },
            { EMath::True,  JustX },

            { EMath::Symbol, JustACat },
            { EMath::String, JustACat },

            { EMath::List, JustACat },
            { EMath::UGen, JustACat },
            { EMath::Envelope, JustACat }
        } },

        { EMath::HashLevel, {
            { EMath::Any, JustACat }
        } }
    };

    // --- cmp -----------------------------------------------------------------------------
    XCmpTable cmp = {
        { EMath::Cat, { 
            { EMath::Cat,       JustZero },
            { EMath::Int,       JustOne },
            { EMath::Float,     JustOne },
            { EMath::HashLevel, JustOne },
            { EMath::Noat,      JustOne },
            { EMath::Choard,    JustOne },
            { EMath::False,     JustOne },
            { EMath::True,      JustOne },
            { EMath::Symbol,    JustOne },
            { EMath::String,    JustOne },
            { EMath::List,      JustOne },
            { EMath::UGen,      JustOne },
            { EMath::Envelope,  JustOne }
        } },
        { EMath::False, { 
            { EMath::Cat,       JustOne },
            { EMath::Int,       JustOne },
            { EMath::Float,     JustOne },
            { EMath::HashLevel, JustOne },
            { EMath::Noat,      JustOne },
            { EMath::Choard,    JustOne },
            { EMath::False,     JustZero },
            { EMath::True,      JustOne },
            { EMath::Symbol,    JustOne },
            { EMath::String,    JustOne },
            { EMath::List,      JustOne },
            { EMath::UGen,      JustOne },
            { EMath::Envelope,  JustOne }
        } },
        { EMath::True, { 
            { EMath::Cat,       JustOne },
            { EMath::Int,       JustOne },
            { EMath::Float,     JustOne },
            { EMath::HashLevel, JustOne },
            { EMath::Noat,      JustOne },
            { EMath::Choard,    JustOne },
            { EMath::False,     JustOne },
            { EMath::True,      JustZero },
            { EMath::Symbol,    JustOne },
            { EMath::String,    JustOne },
            { EMath::List,      JustOne },
            { EMath::UGen,      JustOne },
            { EMath::Envelope,  JustOne }
        } },

        { EMath::Envelope, { { EMath::Any, JustOne } } },
        { EMath::UGen,     { { EMath::Any, JustOne } } },
        
        { EMath::Int, {
            { EMath::Int,       MathMagic {
                return static_cast<SkoarFloat>(
                    skoarpuscle_ptr<SkoarpuscleInt> (x)->val -
                    skoarpuscle_ptr<SkoarpuscleInt> (y)->val
                );
            } },
            { EMath::Float,     MathMagic {
                return
                    static_cast<SkoarFloat>(skoarpuscle_ptr<SkoarpuscleInt> (x)->val) -
                    skoarpuscle_ptr<SkoarpuscleFloat> (y)->val;
            } },

            { EMath::HashLevel, MathMagic {
                return
                    static_cast<SkoarFloat>(skoarpuscle_ptr<SkoarpuscleInt> (x)->val) -
                    skoarpuscle_ptr<SkoarpuscleHashLevel> (y)->val;
            } },

            { EMath::Noat,      JustOne },
            { EMath::Choard,    JustOne },
            { EMath::False,     JustOne },
            { EMath::True,      JustOne },
            { EMath::Symbol,    JustOne },
            { EMath::String,    JustOne },
            { EMath::List,      JustOne },
            { EMath::UGen,      JustOne },
            { EMath::Envelope,  JustOne }
        } },

        { EMath::Float, {
            { EMath::Int, MathMagic {
                return
                    skoarpuscle_ptr<SkoarpuscleFloat> (x)->val -
                    static_cast<SkoarFloat> (skoarpuscle_ptr<SkoarpuscleInt> (y)->val);
            } },
            { EMath::Float, MathMagic {
                return
                    skoarpuscle_ptr<SkoarpuscleFloat> (x)->val -
                    skoarpuscle_ptr<SkoarpuscleFloat> (y)->val;
            } },
            { EMath::HashLevel, MathMagic {
                return
                    skoarpuscle_ptr<SkoarpuscleFloat> (x)->val -
                    skoarpuscle_ptr<SkoarpuscleHashLevel> (y)->val;
            } },

            { EMath::Noat,      JustOne },
            { EMath::Choard,    JustOne },
            { EMath::False,     JustOne },
            { EMath::True,      JustOne },
            { EMath::Symbol,    JustOne },
            { EMath::String,    JustOne },
            { EMath::List,      JustOne },
            { EMath::UGen,      JustOne },
            { EMath::Envelope,  JustOne }
        } },

        { EMath::HashLevel, {
            { EMath::Int, MathMagic {
                return
                    skoarpuscle_ptr<SkoarpuscleHashLevel> (x)->val -
                    static_cast<SkoarFloat> (skoarpuscle_ptr<SkoarpuscleInt> (y)->val);
            } },
            { EMath::Float, MathMagic {
                return
                    skoarpuscle_ptr<SkoarpuscleHashLevel> (x)->val -
                    skoarpuscle_ptr<SkoarpuscleFloat> (y)->val;
            } },
            { EMath::HashLevel, MathMagic {
                return
                    skoarpuscle_ptr<SkoarpuscleHashLevel> (x)->val -
                    skoarpuscle_ptr<SkoarpuscleHashLevel> (y)->val;
            } },

            { EMath::Noat,      JustOne },
            { EMath::Choard,    JustOne },
            { EMath::False,     JustOne },
            { EMath::True,      JustOne },
            { EMath::Symbol,    JustOne },
            { EMath::String,    JustOne },
            { EMath::List,      JustOne },
            { EMath::UGen,      JustOne },
            { EMath::Envelope,  JustOne }
        } }

    };



};

#undef MathMagic
#undef EMath



static SkoarOps* instance (nullptr);
static SkoarOpsTables* ops_tables (nullptr);


void SkoarOps::init() {
    static bool initialized (false);
    if (initialized == false)
    {
        instance = new SkoarOps();
        ops_tables = new SkoarOpsTables ();
    }
}

SkoarOps* SkoarOps::getInstance() {
    return instance;
}

SpellOfMath SkoarOps::lookup(XTable &xtable, SkoarpusclePtr x, SkoarpusclePtr y) {
    static const SpellOfMath cat([](SkoarpusclePtr, SkoarpusclePtr, SkoarMinstrelPtr) {
        return make_skoarpuscle(nullptr);
    });

    try {
        auto& ytable (xtable.at(x->kind));

        try {
            return ytable.at(y->kind);
        }
        catch (const std::out_of_range&) {
            return ytable.at(ESkoarpuscle::Any);
        }
    }
    catch (const std::out_of_range&) {
    }
    return cat;
}

SpellOfCmp SkoarOps::lookup (XCmpTable & xtable, SkoarpusclePtr x, SkoarpusclePtr y)
{
    static const SpellOfCmp gt ([](SkoarpusclePtr, SkoarpusclePtr, SkoarMinstrelPtr) {
        return 1.0;
    });

    try
    {
        auto& ytable (xtable.at (x->kind));

        try
        {
            return ytable.at (y->kind);
        }
        catch (const std::out_of_range&)
        {
            return ytable.at (ESkoarpuscle::Any);
        }
    }
    catch (const std::out_of_range&)
    {
    }
    return gt;
}

SkoarpusclePtr SkoarOps::assign(SkoarMinstrelPtr m, SkoarpusclePtr x, SkoarpusclePtr y) 
{
    SpellOfMath f (lookup(ops_tables->assignment, y, x));
    return m->fairy->impress(f(y, x, m));
}

SkoarpusclePtr SkoarOps::add(SkoarMinstrelPtr m, SkoarpusclePtr x, SkoarpusclePtr y) 
{
    const SpellOfMath &f (lookup(ops_tables->addition, x, y));
    return m->fairy->impress(f(x, y, m));
}

SkoarpusclePtr SkoarOps::sub(SkoarMinstrelPtr m, SkoarpusclePtr x, SkoarpusclePtr y) 
{
    const SpellOfMath &f (lookup(ops_tables->subtraction, x, y));
    return m->fairy->impress(f(x, y, m));
}

SkoarpusclePtr SkoarOps::mul(SkoarMinstrelPtr m, SkoarpusclePtr x, SkoarpusclePtr y) 
{
    const SpellOfMath &f (lookup(ops_tables->multiplication, x, y));
    return m->fairy->impress(f(x, y, m));
}

SkoarpusclePtr SkoarOps::div(SkoarMinstrelPtr m, SkoarpusclePtr x, SkoarpusclePtr y) 
{
    const SpellOfMath &f (lookup(ops_tables->division, x, y));
    return m->fairy->impress(f(x, y, m));
}

SkoarpusclePtr SkoarOps::mod(SkoarMinstrelPtr m, SkoarpusclePtr x, SkoarpusclePtr y) 
{
    const SpellOfMath &f (lookup(ops_tables->modulo, x, y));
    return m->fairy->impress(f(x, y, m));
}

SkoarpusclePtr SkoarOps::neq(SkoarMinstrelPtr m, SkoarpusclePtr x, SkoarpusclePtr y) 
{
    const SpellOfCmp &f (lookup(ops_tables->cmp, x, y));
    return m->fairy->impress(f (x, y, m) != 0.0);
}

SkoarpusclePtr SkoarOps::eq (SkoarMinstrelPtr m, SkoarpusclePtr x, SkoarpusclePtr y) 
{
    const SpellOfCmp &f (lookup (ops_tables->cmp, x, y));
    return m->fairy->impress (f (x, y, m) == 0.0);
}

SkoarpusclePtr SkoarOps::gt (SkoarMinstrelPtr m, SkoarpusclePtr x, SkoarpusclePtr y)
{
    const SpellOfCmp &f (lookup (ops_tables->cmp, x, y));
    return m->fairy->impress (f (x, y, m) > 0.0);
}

SkoarpusclePtr SkoarOps::gte (SkoarMinstrelPtr m, SkoarpusclePtr x, SkoarpusclePtr y)
{
    const SpellOfCmp &f (lookup (ops_tables->cmp, x, y));
    return m->fairy->impress (f (x, y, m) >= 0.0);
}

SkoarpusclePtr SkoarOps::lt (SkoarMinstrelPtr m, SkoarpusclePtr x, SkoarpusclePtr y)
{
    const SpellOfCmp &f (lookup (ops_tables->cmp, x, y));
    return m->fairy->impress (f (x, y, m) < 0.0);
}

SkoarpusclePtr SkoarOps::lte (SkoarMinstrelPtr m, SkoarpusclePtr x, SkoarpusclePtr y)
{
    const SpellOfCmp &f (lookup (ops_tables->cmp, x, y));
    return m->fairy->impress (f (x, y, m) <= 0.0);
}

// -- might want a table for these at some point (ugens?)
SkoarpusclePtr SkoarOps::and_ (SkoarMinstrelPtr m, SkoarpusclePtr x, SkoarpusclePtr y)
{
    if (is_skoarpuscle<SkoarpuscleTrue>(x) && is_skoarpuscle<SkoarpuscleTrue>(y) )
        return m->fairy->impress (x);
    return m->fairy->impress(make_skoarpuscle(false));
}

SkoarpusclePtr SkoarOps::or_ (SkoarMinstrelPtr m, SkoarpusclePtr x, SkoarpusclePtr y)
{
    if (is_skoarpuscle<SkoarpuscleTrue>(x) || is_skoarpuscle<SkoarpuscleTrue>(y) )
        return m->fairy->impress (make_skoarpuscle(true));
    return m->fairy->impress(make_skoarpuscle(false));
}


