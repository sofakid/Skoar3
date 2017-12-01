#include "operators.hpp"
#include "magic_words.hpp"

#define MathMagic [](SkoarpusclePtr x, SkoarpusclePtr y, SkoarMinstrelPtr m)
#define EMath ESkoarpuscle

class SkoarOpsTables
{
public:

    XTable assignment = {
        { EMath::Symbol, { {
            EMath::Any, MathMagic {
                auto str (skoarpuscle_ptr<SkoarpuscleSymbol> (x)->val);
                if (handle_magic_words (str, y, m))
                    return y;
                m->koar->put (str, y); return y; }
            } } },

        { EMath::SymbolColon, { {
            EMath::Any, MathMagic {
            auto str (skoarpuscle_ptr<SkoarpuscleSymbolColon> (x)->val);
            if (handle_magic_words (str, y, m))
                return y;
            m->koar->put (str, y); return y; }
        } } }

    };


    XTable addition = {
        { EMath::Cat, { { EMath::Any, MathMagic { return make_skoarpuscle (nullptr); } } } },
        { EMath::False, { { EMath::Any, MathMagic { return x; } } } },
        { EMath::True, { { EMath::Any, MathMagic { return y; } } } },

        { EMath::Envelope, { { EMath::Any, MathMagic { return make_skoarpuscle (nullptr); } } } },

        { EMath::UGen, {
            { EMath::Int,       MathMagic { return skoarpuscle_ptr<SkoarpuscleUGen> (x)->add (y); } },
            { EMath::Float,     MathMagic { return skoarpuscle_ptr<SkoarpuscleUGen> (x)->add (y); } },
            { EMath::HashLevel, MathMagic { return skoarpuscle_ptr<SkoarpuscleUGen> (x)->add (y); } },
            { EMath::Freq,      MathMagic { return make_skoarpuscle (nullptr); } },

            { EMath::Noat,   MathMagic { return make_skoarpuscle (nullptr); } },
            { EMath::Choard, MathMagic { return make_skoarpuscle (nullptr); } },

            { EMath::False, MathMagic { return skoarpuscle_ptr<SkoarpuscleUGen> (x)->mul (make_skoarpuscle (0.0)); } },
            { EMath::True,  MathMagic { return x; } },

            { EMath::Symbol, MathMagic { return make_skoarpuscle (nullptr); } },
            { EMath::String, MathMagic { return make_skoarpuscle (nullptr); } },

            { EMath::List,     MathMagic { return make_skoarpuscle (nullptr); } },
            { EMath::UGen,     MathMagic { return skoarpuscle_ptr<SkoarpuscleUGen> (y)->add (x); } },
            { EMath::Envelope, MathMagic { return make_skoarpuscle (nullptr); } }
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

            { EMath::Noat,   MathMagic { return make_skoarpuscle (nullptr); } },
            { EMath::Choard, MathMagic { return make_skoarpuscle (nullptr); } },

            { EMath::False, MathMagic { return y; } },
            { EMath::True,  MathMagic { return x; } },

            { EMath::Symbol, MathMagic { return make_skoarpuscle (nullptr); } },
            { EMath::String, MathMagic { return make_skoarpuscle (nullptr); } },

            { EMath::List,     MathMagic { return make_skoarpuscle (nullptr); } },
            { EMath::UGen,     MathMagic { return make_skoarpuscle (nullptr); } },
            { EMath::Envelope, MathMagic { return make_skoarpuscle (nullptr); } }
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

            { EMath::Noat,   MathMagic { return make_skoarpuscle (nullptr); } },
            { EMath::Choard, MathMagic { return make_skoarpuscle (nullptr); } },

            { EMath::False, MathMagic { return y; } },
            { EMath::True,  MathMagic { return x; } },

            { EMath::Symbol, MathMagic { return make_skoarpuscle (nullptr); } },
            { EMath::String, MathMagic { return make_skoarpuscle (nullptr); } },

            { EMath::List, MathMagic { return make_skoarpuscle (nullptr); } },
            { EMath::UGen, MathMagic { return make_skoarpuscle (nullptr); } },
            { EMath::Envelope, MathMagic { return make_skoarpuscle (nullptr); } }
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

            { EMath::Noat,   MathMagic { return make_skoarpuscle (nullptr); } },
            { EMath::Choard, MathMagic { return make_skoarpuscle (nullptr); } },

            { EMath::False, MathMagic { return y; } },
            { EMath::True,  MathMagic { return x; } },

            { EMath::Symbol, MathMagic { return make_skoarpuscle (nullptr); } },
            { EMath::String, MathMagic { return make_skoarpuscle (nullptr); } },

            { EMath::List, MathMagic { return make_skoarpuscle (nullptr); } },
            { EMath::UGen, MathMagic { return make_skoarpuscle (nullptr); } },
            { EMath::Envelope, MathMagic { return make_skoarpuscle (nullptr); } }
        } }


    };

    XTable subtraction = {
        { EMath::Cat, { { EMath::Any, MathMagic { return make_skoarpuscle (nullptr); } } } },
        { EMath::False, { { EMath::Any, MathMagic { return x; } } } },
        { EMath::True, { { EMath::Any, MathMagic { return y; } } } },

        { EMath::Envelope, { { EMath::Any, MathMagic { return make_skoarpuscle (nullptr); } } } },

        { EMath::UGen, {
            { EMath::Int,       MathMagic { return skoarpuscle_ptr<SkoarpuscleUGen> (x)->sub (y); } },
            { EMath::Float,     MathMagic { return skoarpuscle_ptr<SkoarpuscleUGen> (x)->sub (y); } },
            { EMath::HashLevel, MathMagic { return skoarpuscle_ptr<SkoarpuscleUGen> (x)->sub (y); } },
            { EMath::Freq,      MathMagic { return make_skoarpuscle (nullptr); } },

            { EMath::Noat,   MathMagic { return make_skoarpuscle (nullptr); } },
            { EMath::Choard, MathMagic { return make_skoarpuscle (nullptr); } },

            { EMath::False, MathMagic { return skoarpuscle_ptr<SkoarpuscleUGen> (x)->mul (make_skoarpuscle (0.0)); } },
            { EMath::True,  MathMagic { return x; } },

            { EMath::Symbol, MathMagic { return make_skoarpuscle (nullptr); } },
            { EMath::String, MathMagic { return make_skoarpuscle (nullptr); } },

            { EMath::List,     MathMagic { return make_skoarpuscle (nullptr); } },
            { EMath::UGen,     MathMagic { return skoarpuscle_ptr<SkoarpuscleUGen> (y)->sub (x); } },
            { EMath::Envelope, MathMagic { return make_skoarpuscle (nullptr); } }
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

            { EMath::Noat,   MathMagic { return make_skoarpuscle (nullptr); } },
            { EMath::Choard, MathMagic { return make_skoarpuscle (nullptr); } },

            { EMath::False, MathMagic { return y; } },
            { EMath::True,  MathMagic { return x; } },

            { EMath::Symbol, MathMagic { return make_skoarpuscle (nullptr); } },
            { EMath::String, MathMagic { return make_skoarpuscle (nullptr); } },

            { EMath::List,     MathMagic { return make_skoarpuscle (nullptr); } },
            { EMath::UGen,     MathMagic { return make_skoarpuscle (nullptr); } },
            { EMath::Envelope, MathMagic { return make_skoarpuscle (nullptr); } }
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

            { EMath::Noat,   MathMagic { return make_skoarpuscle (nullptr); } },
            { EMath::Choard, MathMagic { return make_skoarpuscle (nullptr); } },

            { EMath::False, MathMagic { return y; } },
            { EMath::True,  MathMagic { return x; } },

            { EMath::Symbol, MathMagic { return make_skoarpuscle (nullptr); } },
            { EMath::String, MathMagic { return make_skoarpuscle (nullptr); } },

            { EMath::List, MathMagic { return make_skoarpuscle (nullptr); } },
            { EMath::UGen, MathMagic { return make_skoarpuscle (nullptr); } },
            { EMath::Envelope, MathMagic { return make_skoarpuscle (nullptr); } }
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

            { EMath::Noat,   MathMagic { return make_skoarpuscle (nullptr); } },
            { EMath::Choard, MathMagic { return make_skoarpuscle (nullptr); } },

            { EMath::False, MathMagic { return y; } },
            { EMath::True,  MathMagic { return x; } },

            { EMath::Symbol, MathMagic { return make_skoarpuscle (nullptr); } },
            { EMath::String, MathMagic { return make_skoarpuscle (nullptr); } },

            { EMath::List, MathMagic { return make_skoarpuscle (nullptr); } },
            { EMath::UGen, MathMagic { return make_skoarpuscle (nullptr); } },
            { EMath::Envelope, MathMagic { return make_skoarpuscle (nullptr); } }
        } }


    };

    XTable multiplication = {
        { EMath::Cat, { { EMath::Any, MathMagic { return make_skoarpuscle (nullptr); } } } },
        { EMath::False, { { EMath::Any, MathMagic { return x; } } } },
        { EMath::True, { { EMath::Any, MathMagic { return y; } } } },

        { EMath::Envelope, { { EMath::Any, MathMagic { return make_skoarpuscle (nullptr); } } } },

        { EMath::UGen, {
            { EMath::Int,       MathMagic { return skoarpuscle_ptr<SkoarpuscleUGen> (x)->mul (y); } },
            { EMath::Float,     MathMagic { return skoarpuscle_ptr<SkoarpuscleUGen> (x)->mul (y); } },
            { EMath::HashLevel, MathMagic { return skoarpuscle_ptr<SkoarpuscleUGen> (x)->mul (y); } },
            { EMath::Freq,      MathMagic { return make_skoarpuscle (nullptr); } },

            { EMath::Noat,   MathMagic { return make_skoarpuscle (nullptr); } },
            { EMath::Choard, MathMagic { return make_skoarpuscle (nullptr); } },

            { EMath::False, MathMagic { return skoarpuscle_ptr<SkoarpuscleUGen> (x)->mul (make_skoarpuscle (0.0)); } },
            { EMath::True,  MathMagic { return x; } },

            { EMath::Symbol, MathMagic { return make_skoarpuscle (nullptr); } },
            { EMath::String, MathMagic { return make_skoarpuscle (nullptr); } },

            { EMath::List,     MathMagic { return make_skoarpuscle (nullptr); } },
            { EMath::UGen,     MathMagic { return skoarpuscle_ptr<SkoarpuscleUGen> (y)->add (x); } },
            { EMath::Envelope, MathMagic { return make_skoarpuscle (nullptr); } }
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

            { EMath::Noat,   MathMagic { return make_skoarpuscle (nullptr); } },
            { EMath::Choard, MathMagic { return make_skoarpuscle (nullptr); } },

            { EMath::False, MathMagic { return y; } },
            { EMath::True,  MathMagic { return x; } },

            { EMath::Symbol, MathMagic { return make_skoarpuscle (nullptr); } },
            { EMath::String, MathMagic { return make_skoarpuscle (nullptr); } },

            { EMath::List,     MathMagic { return make_skoarpuscle (nullptr); } },
            { EMath::UGen,     MathMagic { return make_skoarpuscle (nullptr); } },
            { EMath::Envelope, MathMagic { return make_skoarpuscle (nullptr); } }
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

            { EMath::Noat,   MathMagic { return make_skoarpuscle (nullptr); } },
            { EMath::Choard, MathMagic { return make_skoarpuscle (nullptr); } },

            { EMath::False, MathMagic { return y; } },
            { EMath::True,  MathMagic { return x; } },

            { EMath::Symbol, MathMagic { return make_skoarpuscle (nullptr); } },
            { EMath::String, MathMagic { return make_skoarpuscle (nullptr); } },

            { EMath::List, MathMagic { return make_skoarpuscle (nullptr); } },
            { EMath::UGen, MathMagic { return make_skoarpuscle (nullptr); } },
            { EMath::Envelope, MathMagic { return make_skoarpuscle (nullptr); } }
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

            { EMath::Noat,   MathMagic { return make_skoarpuscle (nullptr); } },
            { EMath::Choard, MathMagic { return make_skoarpuscle (nullptr); } },

            { EMath::False, MathMagic { return y; } },
            { EMath::True,  MathMagic { return x; } },

            { EMath::Symbol, MathMagic { return make_skoarpuscle (nullptr); } },
            { EMath::String, MathMagic { return make_skoarpuscle (nullptr); } },

            { EMath::List, MathMagic { return make_skoarpuscle (nullptr); } },
            { EMath::UGen, MathMagic { return make_skoarpuscle (nullptr); } },
            { EMath::Envelope, MathMagic { return make_skoarpuscle (nullptr); } }
        } }


    };

    XTable division = {
        { EMath::Cat, { { EMath::Any, MathMagic { return make_skoarpuscle (nullptr); } } } },
        { EMath::False, { { EMath::Any, MathMagic { return x; } } } },
        { EMath::True, { { EMath::Any, MathMagic { return y; } } } },

        { EMath::Envelope, { { EMath::Any, MathMagic { return make_skoarpuscle (nullptr); } } } },

        { EMath::UGen, {
            { EMath::Int,       MathMagic { return skoarpuscle_ptr<SkoarpuscleUGen> (x)->divBy (y); } },
            { EMath::Float,     MathMagic { return skoarpuscle_ptr<SkoarpuscleUGen> (x)->divBy (y); } },
            { EMath::HashLevel, MathMagic { return skoarpuscle_ptr<SkoarpuscleUGen> (x)->divBy (y); } },
            { EMath::Freq,      MathMagic { return make_skoarpuscle (nullptr); } },

            { EMath::Noat,   MathMagic { return make_skoarpuscle (nullptr); } },
            { EMath::Choard, MathMagic { return make_skoarpuscle (nullptr); } },

            { EMath::False, MathMagic { return skoarpuscle_ptr<SkoarpuscleUGen> (x)->mul (make_skoarpuscle (0.0)); } },
            { EMath::True,  MathMagic { return x; } },

            { EMath::Symbol, MathMagic { return make_skoarpuscle (nullptr); } },
            { EMath::String, MathMagic { return make_skoarpuscle (nullptr); } },

            { EMath::List,     MathMagic { return make_skoarpuscle (nullptr); } },
            { EMath::UGen,     MathMagic { return skoarpuscle_ptr<SkoarpuscleUGen> (y)->divBy (x); } },
            { EMath::Envelope, MathMagic { return make_skoarpuscle (nullptr); } }
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

            { EMath::Noat,   MathMagic { return make_skoarpuscle (nullptr); } },
            { EMath::Choard, MathMagic { return make_skoarpuscle (nullptr); } },

            { EMath::False, MathMagic { return y; } },
            { EMath::True,  MathMagic { return x; } },

            { EMath::Symbol, MathMagic { return make_skoarpuscle (nullptr); } },
            { EMath::String, MathMagic { return make_skoarpuscle (nullptr); } },

            { EMath::List,     MathMagic { return make_skoarpuscle (nullptr); } },
            { EMath::UGen,     MathMagic { return make_skoarpuscle (nullptr); } },
            { EMath::Envelope, MathMagic { return make_skoarpuscle (nullptr); } }
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

            { EMath::Noat,   MathMagic { return make_skoarpuscle (nullptr); } },
            { EMath::Choard, MathMagic { return make_skoarpuscle (nullptr); } },

            { EMath::False, MathMagic { return y; } },
            { EMath::True,  MathMagic { return x; } },

            { EMath::Symbol, MathMagic { return make_skoarpuscle (nullptr); } },
            { EMath::String, MathMagic { return make_skoarpuscle (nullptr); } },

            { EMath::List, MathMagic { return make_skoarpuscle (nullptr); } },
            { EMath::UGen, MathMagic { return make_skoarpuscle (nullptr); } },
            { EMath::Envelope, MathMagic { return make_skoarpuscle (nullptr); } }
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


            { EMath::Noat,   MathMagic { return make_skoarpuscle (nullptr); } },
            { EMath::Choard, MathMagic { return make_skoarpuscle (nullptr); } },

            { EMath::False, MathMagic { return y; } },
            { EMath::True,  MathMagic { return x; } },

            { EMath::Symbol, MathMagic { return make_skoarpuscle (nullptr); } },
            { EMath::String, MathMagic { return make_skoarpuscle (nullptr); } },

            { EMath::List, MathMagic { return make_skoarpuscle (nullptr); } },
            { EMath::UGen, MathMagic { return make_skoarpuscle (nullptr); } },
            { EMath::Envelope, MathMagic { return make_skoarpuscle (nullptr); } }
        } }
    };

    XTable modulo = {
        { EMath::Cat, { { EMath::Any, MathMagic { return make_skoarpuscle (nullptr); } } } },
        { EMath::False, { { EMath::Any, MathMagic { return make_skoarpuscle (nullptr); } } } },
        { EMath::True, { { EMath::Any, MathMagic { return make_skoarpuscle (nullptr); } } } },

        { EMath::Envelope, { { EMath::Any, MathMagic { return make_skoarpuscle (nullptr); } } } },

        { EMath::UGen, {
            { EMath::Int,       MathMagic { return skoarpuscle_ptr<SkoarpuscleUGen> (x)->divBy (y); } },
            { EMath::Float,     MathMagic { return skoarpuscle_ptr<SkoarpuscleUGen> (x)->divBy (y); } },
            { EMath::HashLevel, MathMagic { return skoarpuscle_ptr<SkoarpuscleUGen> (x)->divBy (y); } },
            { EMath::Freq,      MathMagic { return make_skoarpuscle (nullptr); } },

            { EMath::Noat,   MathMagic { return make_skoarpuscle (nullptr); } },
            { EMath::Choard, MathMagic { return make_skoarpuscle (nullptr); } },

            { EMath::False, MathMagic { return skoarpuscle_ptr<SkoarpuscleUGen> (x)->mul (make_skoarpuscle (0.0)); } },
            { EMath::True,  MathMagic { return x; } },

            { EMath::Symbol, MathMagic { return make_skoarpuscle (nullptr); } },
            { EMath::String, MathMagic { return make_skoarpuscle (nullptr); } },

            { EMath::List,     MathMagic { return make_skoarpuscle (nullptr); } },
            { EMath::UGen,     MathMagic { return skoarpuscle_ptr<SkoarpuscleUGen> (y)->divBy (x); } },
            { EMath::Envelope, MathMagic { return make_skoarpuscle (nullptr); } }
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

            { EMath::HashLevel, MathMagic { return make_skoarpuscle (nullptr); } },

            { EMath::Noat,   MathMagic { return make_skoarpuscle (nullptr); } },
            { EMath::Choard, MathMagic { return make_skoarpuscle (nullptr); } },

            { EMath::False, MathMagic { return y; } },
            { EMath::True,  MathMagic { return x; } },

            { EMath::Symbol, MathMagic { return make_skoarpuscle (nullptr); } },
            { EMath::String, MathMagic { return make_skoarpuscle (nullptr); } },

            { EMath::List,     MathMagic { return make_skoarpuscle (nullptr); } },
            { EMath::UGen,     MathMagic { return make_skoarpuscle (nullptr); } },
            { EMath::Envelope, MathMagic { return make_skoarpuscle (nullptr); } }
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
            { EMath::HashLevel, MathMagic { return make_skoarpuscle (nullptr); } },

            { EMath::Noat,   MathMagic { return make_skoarpuscle (nullptr); } },
            { EMath::Choard, MathMagic { return make_skoarpuscle (nullptr); } },

            { EMath::False, MathMagic { return y; } },
            { EMath::True,  MathMagic { return x; } },

            { EMath::Symbol, MathMagic { return make_skoarpuscle (nullptr); } },
            { EMath::String, MathMagic { return make_skoarpuscle (nullptr); } },

            { EMath::List, MathMagic { return make_skoarpuscle (nullptr); } },
            { EMath::UGen, MathMagic { return make_skoarpuscle (nullptr); } },
            { EMath::Envelope, MathMagic { return make_skoarpuscle (nullptr); } }
        } },

        { EMath::HashLevel, {
            { EMath::Any, MathMagic { return make_skoarpuscle (nullptr); } }
        } }
    };

    // --- cmp -----------------------------------------------------------------------------
    XCmpTable cmp = {
        { EMath::Cat, { 
            { EMath::Cat,       MathMagic { return 0.0; } },
            { EMath::Int,       MathMagic { return 1.0; } },
            { EMath::Float,     MathMagic { return 1.0; } },
            { EMath::HashLevel, MathMagic { return 1.0; } },
            { EMath::Noat,      MathMagic { return 1.0; } },
            { EMath::Choard,    MathMagic { return 1.0; } },
            { EMath::False,     MathMagic { return 1.0; } },
            { EMath::True,      MathMagic { return 1.0; } },
            { EMath::Symbol,    MathMagic { return 1.0; } },
            { EMath::String,    MathMagic { return 1.0; } },
            { EMath::List,      MathMagic { return 1.0; } },
            { EMath::UGen,      MathMagic { return 1.0; } },
            { EMath::Envelope,  MathMagic { return 1.0; } }
        } },
        { EMath::False, { 
            { EMath::Cat,       MathMagic { return 1.0; } },
            { EMath::Int,       MathMagic { return 1.0; } },
            { EMath::Float,     MathMagic { return 1.0; } },
            { EMath::HashLevel, MathMagic { return 1.0; } },
            { EMath::Noat,      MathMagic { return 1.0; } },
            { EMath::Choard,    MathMagic { return 1.0; } },
            { EMath::False,     MathMagic { return 0.0; } },
            { EMath::True,      MathMagic { return 1.0; } },
            { EMath::Symbol,    MathMagic { return 1.0; } },
            { EMath::String,    MathMagic { return 1.0; } },
            { EMath::List,      MathMagic { return 1.0; } },
            { EMath::UGen,      MathMagic { return 1.0; } },
            { EMath::Envelope,  MathMagic { return 1.0; } }
        } },
        { EMath::True, { 
            { EMath::Cat,       MathMagic { return 1.0; } },
            { EMath::Int,       MathMagic { return 1.0; } },
            { EMath::Float,     MathMagic { return 1.0; } },
            { EMath::HashLevel, MathMagic { return 1.0; } },
            { EMath::Noat,      MathMagic { return 1.0; } },
            { EMath::Choard,    MathMagic { return 1.0; } },
            { EMath::False,     MathMagic { return 1.0; } },
            { EMath::True,      MathMagic { return 0.0; } },
            { EMath::Symbol,    MathMagic { return 1.0; } },
            { EMath::String,    MathMagic { return 1.0; } },
            { EMath::List,      MathMagic { return 1.0; } },
            { EMath::UGen,      MathMagic { return 1.0; } },
            { EMath::Envelope,  MathMagic { return 1.0; } }
        } },

        { EMath::Envelope, { { EMath::Any, MathMagic { return 1.0; } } } },
        { EMath::UGen,     { { EMath::Any, MathMagic { return 1.0; } } } },
        
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

            { EMath::Noat,      MathMagic { return 1.0; } },
            { EMath::Choard,    MathMagic { return 1.0; } },
            { EMath::False,     MathMagic { return 1.0; } },
            { EMath::True,      MathMagic { return 1.0; } },
            { EMath::Symbol,    MathMagic { return 1.0; } },
            { EMath::String,    MathMagic { return 1.0; } },
            { EMath::List,      MathMagic { return 1.0; } },
            { EMath::UGen,      MathMagic { return 1.0; } },
            { EMath::Envelope,  MathMagic { return 1.0; } }
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

            { EMath::Noat,      MathMagic { return 1.0; } },
            { EMath::Choard,    MathMagic { return 1.0; } },
            { EMath::False,     MathMagic { return 1.0; } },
            { EMath::True,      MathMagic { return 1.0; } },
            { EMath::Symbol,    MathMagic { return 1.0; } },
            { EMath::String,    MathMagic { return 1.0; } },
            { EMath::List,      MathMagic { return 1.0; } },
            { EMath::UGen,      MathMagic { return 1.0; } },
            { EMath::Envelope,  MathMagic { return 1.0; } }
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

            { EMath::Noat,      MathMagic { return 1.0; } },
            { EMath::Choard,    MathMagic { return 1.0; } },
            { EMath::False,     MathMagic { return 1.0; } },
            { EMath::True,      MathMagic { return 1.0; } },
            { EMath::Symbol,    MathMagic { return 1.0; } },
            { EMath::String,    MathMagic { return 1.0; } },
            { EMath::List,      MathMagic { return 1.0; } },
            { EMath::UGen,      MathMagic { return 1.0; } },
            { EMath::Envelope,  MathMagic { return 1.0; } }
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
SkoarpusclePtr SkoarOps::and (SkoarMinstrelPtr m, SkoarpusclePtr x, SkoarpusclePtr y)
{
    if (is_skoarpuscle<SkoarpuscleTrue>(x) && is_skoarpuscle<SkoarpuscleTrue>(y) )
        return m->fairy->impress (x);
    return m->fairy->impress(make_skoarpuscle(false));
}

SkoarpusclePtr SkoarOps::or (SkoarMinstrelPtr m, SkoarpusclePtr x, SkoarpusclePtr y)
{
    if (is_skoarpuscle<SkoarpuscleTrue>(x) || is_skoarpuscle<SkoarpuscleTrue>(y) )
        return m->fairy->impress (make_skoarpuscle(true));
    return m->fairy->impress(make_skoarpuscle(false));
}


