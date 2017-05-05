#pragma once
#include "skoarcery.hpp"
#include "spells.hpp"
#include "all_skoarpuscles.hpp"
#include "minstrel.hpp"
#include "koar.hpp"

typedef function<SkoarpusclePtr(SkoarpusclePtr, SkoarpusclePtr, SkoarMinstrelPtr)> SpellOfMath;

typedef map<ESkoarpuscle::Kind, SpellOfMath> YTable;
typedef map<ESkoarpuscle::Kind, YTable> XTable;

#define MathMagic [](SkoarpusclePtr x, SkoarpusclePtr y, SkoarMinstrelPtr m)
#define EMath ESkoarpuscle

class SkoarOps {
public:

    static void init();
    static SkoarOps* getInstance();

    XTable assignment = {
        { EMath::Symbol, {{
            EMath::Any, MathMagic {
                auto str (skoarpuscle_ptr<SkoarpuscleSymbol> (x)->val);
                m->koar->put (str, y); return y; }
        }} },

        { EMath::SymbolColon,{{
            EMath::Any, MathMagic{
                auto str (skoarpuscle_ptr<SkoarpuscleSymbolColon> (x)->val);
                m->koar->put (str, y); return y; }
        }} }

    };


    XTable addition = {
        {EMath::Cat,   {{ EMath::Any, MathMagic { return make_skoarpuscle (nullptr); } }}},
        {EMath::False, {{ EMath::Any, MathMagic { return x; } }}},
        {EMath::True,  {{ EMath::Any, MathMagic { return y; } }}},

        {EMath::Envelope, {{ EMath::Any, MathMagic { return make_skoarpuscle (nullptr); } }}},

        {EMath::UGen, {
            {EMath::Int,       MathMagic{ return skoarpuscle_ptr<SkoarpuscleUGen> (x)->add (y); }},
            {EMath::Float,     MathMagic{ return skoarpuscle_ptr<SkoarpuscleUGen> (x)->add (y); }},
            {EMath::HashLevel, MathMagic{ return skoarpuscle_ptr<SkoarpuscleUGen> (x)->add (y); }},
            {EMath::Freq,      MathMagic{ return make_skoarpuscle (nullptr); }},

            {EMath::Noat,   MathMagic{ return make_skoarpuscle (nullptr); }},
            {EMath::Choard, MathMagic{ return make_skoarpuscle (nullptr); }},

            {EMath::False, MathMagic{ return skoarpuscle_ptr<SkoarpuscleUGen> (x)->mul (make_skoarpuscle (0.0)); }},
            {EMath::True,  MathMagic{ return x; }},

            {EMath::Symbol, MathMagic{ return make_skoarpuscle (nullptr); }},
            {EMath::String, MathMagic{ return make_skoarpuscle (nullptr); }},

            {EMath::List,     MathMagic{ return make_skoarpuscle (nullptr); }},
            {EMath::UGen,     MathMagic{ return skoarpuscle_ptr<SkoarpuscleUGen> (y)->add (x); }},
            {EMath::Envelope, MathMagic{ return make_skoarpuscle (nullptr); }}
        }},

        {EMath::Int,{
            {EMath::Int,       MathMagic{
                return make_skoarpuscle(
                    skoarpuscle_ptr<SkoarpuscleInt> (x)->val +
                    skoarpuscle_ptr<SkoarpuscleInt> (y)->val
                );
            }},
            {EMath::Float,     MathMagic{
                return make_skoarpuscle(
                    static_cast<SkoarFloat>(skoarpuscle_ptr<SkoarpuscleInt> (x)->val) +
                    skoarpuscle_ptr<SkoarpuscleFloat> (y)->val
                );
            }},
            {EMath::HashLevel, MathMagic{
                return make_skoarpuscle(
                    static_cast<SkoarFloat>(skoarpuscle_ptr<SkoarpuscleInt> (x)->val) +
                    skoarpuscle_ptr<SkoarpuscleHashLevel> (y)->val
                );
            }},
            {EMath::Freq,      MathMagic{
                return make_skoarpuscle(
                    static_cast<SkoarFloat>(skoarpuscle_ptr<SkoarpuscleInt> (x)->val) +
                    skoarpuscle_ptr<SkoarpuscleFreq> (y)->val
                );
            }},

            {EMath::Noat,   MathMagic{ return make_skoarpuscle (nullptr); }},
            {EMath::Choard, MathMagic{ return make_skoarpuscle (nullptr); }},

            {EMath::False, MathMagic{ return y; }},
            {EMath::True,  MathMagic{ return x; }},

            {EMath::Symbol, MathMagic{ return make_skoarpuscle (nullptr); }},
            {EMath::String, MathMagic{ return make_skoarpuscle (nullptr); }},

            {EMath::List,     MathMagic{ return make_skoarpuscle (nullptr); }},
            {EMath::UGen,     MathMagic{ return make_skoarpuscle (nullptr); }},
            {EMath::Envelope, MathMagic{ return make_skoarpuscle (nullptr); }}
        }},

        {EMath::Float, {
            {EMath::Int, MathMagic{
                return make_skoarpuscle(
                    skoarpuscle_ptr<SkoarpuscleFloat> (x)->val +
                    static_cast<SkoarFloat> (skoarpuscle_ptr<SkoarpuscleInt> (y)->val)
                );
            }},
            {EMath::Float, MathMagic{
                return make_skoarpuscle(
                    skoarpuscle_ptr<SkoarpuscleFloat> (x)->val +
                    skoarpuscle_ptr<SkoarpuscleFloat> (y)->val
                );
            }},
            {EMath::HashLevel, MathMagic{
                return make_skoarpuscle(
                    skoarpuscle_ptr<SkoarpuscleFloat> (x)->val +
                    skoarpuscle_ptr<SkoarpuscleHashLevel> (y)->val
                );
            }},
            {EMath::Freq, MathMagic{
                return make_skoarpuscle(
                    skoarpuscle_ptr<SkoarpuscleFloat> (x)->val +
                    skoarpuscle_ptr<SkoarpuscleFreq> (y)->val
                );
            }},

            {EMath::Noat,   MathMagic{ return make_skoarpuscle (nullptr); }},
            {EMath::Choard, MathMagic{ return make_skoarpuscle (nullptr); }},

            {EMath::False, MathMagic{ return y; }},
            {EMath::True,  MathMagic{ return x; } },

            {EMath::Symbol, MathMagic{ return make_skoarpuscle (nullptr); }},
            {EMath::String, MathMagic{ return make_skoarpuscle (nullptr); }},

            {EMath::List, MathMagic{ return make_skoarpuscle (nullptr); }},
            {EMath::UGen, MathMagic{ return make_skoarpuscle (nullptr); }},
            {EMath::Envelope, MathMagic{ return make_skoarpuscle (nullptr); }}
        }}

    };

    SpellOfMath lookup (XTable &xtable, SkoarpusclePtr, SkoarpusclePtr);
    SkoarpusclePtr assign (SkoarMinstrelPtr, SkoarpusclePtr, SkoarpusclePtr);

    SkoarpusclePtr add (SkoarMinstrelPtr, SkoarpusclePtr, SkoarpusclePtr);
    SkoarpusclePtr sub (SkoarMinstrelPtr, SkoarpusclePtr, SkoarpusclePtr);

    SkoarpusclePtr mul (SkoarMinstrelPtr, SkoarpusclePtr, SkoarpusclePtr);
    SkoarpusclePtr div (SkoarMinstrelPtr, SkoarpusclePtr, SkoarpusclePtr);

};

#undef MathMagic
#undef EMath