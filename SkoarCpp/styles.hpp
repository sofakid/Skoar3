#pragma once

#include <sstream>

namespace SkoarStyles
{

    const enum class EStyle
    {
        nostyle = 0,
        parseFail,

        False,
        True,
        Times,
        Choard,

        Symbol,
        Comment,
        MathOp,
        BooleanOp,

        HashLevel,
        Bars,
        Carrot,

        Voice,
        Fairy,
        Freq,
        String,

        NamedNoat,
        MsgOp,
        Tuplet,
        Int,

        Float,

        SymbolColon,
        Duration,
        Cat,

        dynamic,
        msg,
        cthulhu,

        al_goto,
        marker,
        deref,
        ottavas,
        listy,

        beat,
        conditional,
        skoarpion,
        loop,

        lute,
        meditation,
        ugen,
        arg_listy,


    };

    // --- tokes ----------------------------------------
    namespace Toke
    {
        template <const ESkoarToke::Kind tokeKind>
        constexpr const EStyle style (void) {
            return EStyle::nostyle;
        }

        // --- specific tokes -------------------------------------------------
        template<>
        constexpr const EStyle style<ESkoarToke::False> (void) {
            return EStyle::False;
        }

        template <>
        constexpr const EStyle style<ESkoarToke::True> (void) {
            return EStyle::True;
        }

        template <>
        constexpr const EStyle style<ESkoarToke::Times> (void) {
            return EStyle::Times;
        }

        template <>
        constexpr const EStyle style<ESkoarToke::Choard> (void) {
            return EStyle::Choard;
        }

        template <>
        constexpr const EStyle style<ESkoarToke::Symbol> (void) {
            return EStyle::Symbol;
        }

        template <>
        constexpr const EStyle style<ESkoarToke::Comment> (void) {
            return EStyle::Comment;
        }

        template <>
        constexpr const EStyle style<ESkoarToke::BracketS> (void) {
            return EStyle::MathOp;
        }

        template <>
        constexpr const EStyle style<ESkoarToke::BracketE> (void) {
            return EStyle::MathOp;
        }

        template <>
        constexpr const EStyle style<ESkoarToke::MathOpAddSub> (void) {
            return EStyle::MathOp;
        }

        template <>
        constexpr const EStyle style<ESkoarToke::MathOpMulDivMod> (void) {
            return EStyle::MathOp;
        }

        template <>
        constexpr const EStyle style<ESkoarToke::BooleanOr> (void) {
            return EStyle::BooleanOp;
        }

        template <>
        constexpr const EStyle style<ESkoarToke::BooleanAnd> (void) {
            return EStyle::BooleanOp;
        }

        template <>
        constexpr const EStyle style<ESkoarToke::CmpEqNeq> (void) {
            return EStyle::BooleanOp;
        }

        template <>
        constexpr const EStyle style<ESkoarToke::CmpGtLt> (void) {
            return EStyle::BooleanOp;
        }

        template <>
        constexpr const EStyle style<ESkoarToke::HashLevel> (void) {
            return EStyle::HashLevel;
        }

        template <>
        constexpr const EStyle style<ESkoarToke::Bars> (void) {
            return EStyle::Bars;
        }

        template <>
        constexpr const EStyle style<ESkoarToke::Carrot> (void) {
            return EStyle::Carrot;
        }

        template <>
        constexpr const EStyle style<ESkoarToke::Voice> (void) {
            return EStyle::Voice;
        }

        template <>
        constexpr const EStyle style<ESkoarToke::Fairy> (void) {
            return EStyle::Fairy;
        }

        template <>
        constexpr const EStyle style<ESkoarToke::Freq> (void) {
            return EStyle::Freq;
        }

        template <>
        constexpr const EStyle style<ESkoarToke::String> (void) {
            return EStyle::String;
        }

        template <>
        constexpr const EStyle style<ESkoarToke::NamedNoat> (void) {
            return EStyle::NamedNoat;
        }

        template <>
        constexpr const EStyle style<ESkoarToke::MsgOp> (void) {
            return EStyle::MsgOp;
        }

        template <>
        constexpr const EStyle style<ESkoarToke::Tuplet> (void) {
            return EStyle::Tuplet;
        }

        template <>
        constexpr const EStyle style<ESkoarToke::Int> (void) {
            return EStyle::Int;
        }

        template <>
        constexpr const EStyle style<ESkoarToke::Float> (void) {
            return EStyle::Float;
        }

        template <>
        constexpr const EStyle style<ESkoarToke::SymbolColon> (void) {
            return EStyle::SymbolColon;
        }

        template <>
        constexpr const EStyle style<ESkoarToke::Duration> (void) {
            return EStyle::Duration;
        }

        template <>
        constexpr const EStyle style<ESkoarToke::Cat> (void) {
            return EStyle::Cat;
        }
    }

    // --- tokes ----------------------------------------
    namespace Noad
    {

        template <ESkoarNoad::Kind noadKind>
        constexpr const EStyle style (void) {
            return EStyle::nostyle;
        }

        // --- specific noads -------------------------------------------------
        //template <>
        //constexpr const EStyle style<ESkoarNoad::dynamic> (void) {
        //    return EStyle::dynamic;
        //}

        template <>
        constexpr const EStyle style<ESkoarNoad::msg> (void) {
            return EStyle::msg;
        }

        template <>
        constexpr const EStyle style<ESkoarNoad::cthulhu> (void) {
            return EStyle::cthulhu;
        }

        template <>
        constexpr const EStyle style<ESkoarNoad::marker> (void) {
            return EStyle::marker;
        }

        template <>
        constexpr const EStyle style<ESkoarNoad::al_goto> (void) {
            return EStyle::al_goto;
        }

        template <>
        constexpr const EStyle style<ESkoarNoad::deref> (void) {
            return EStyle::deref;
        }

        template <>
        constexpr const EStyle style<ESkoarNoad::ottavas> (void) {
            return EStyle::ottavas;
        }

        template <>
        constexpr const EStyle style<ESkoarNoad::listy> (void) {
            return EStyle::listy;
        }

        template <>
        constexpr const EStyle style<ESkoarNoad::beat> (void) {
            return EStyle::beat;
        }

        template <>
        constexpr const EStyle style<ESkoarNoad::conditional> (void) {
            return EStyle::conditional;
        }

        template <>
        constexpr const EStyle style<ESkoarNoad::skoarpion> (void) {
            return EStyle::skoarpion;
        }

        template <>
        constexpr const EStyle style<ESkoarNoad::loop> (void) {
            return EStyle::loop;
        }

        template <>
        constexpr const EStyle style<ESkoarNoad::lute> (void) {
            return EStyle::lute;
        }

        template <>
        constexpr const EStyle style<ESkoarNoad::meditation> (void) {
            return EStyle::meditation;
        }

        template <>
        constexpr const EStyle style<ESkoarNoad::ugen> (void) {
            return EStyle::ugen;
        }
    }


    /*

    // these don't work in VS2015.. They work sometimes, but many tokes get styled as nostyle.
    // it seems the specialization doesn't always apply.

    template <ESkoarNoad::Kind noadKind>
    constexpr const EStyle style() {
        return Noad::style<noadKind>();
    }

    template <ESkoarToke::Kind tokeKind>
    constexpr const EStyle style() {
        return Toke::style<tokeKind>();
    }
    */

    std::wostream& operator << (std::wostream& out, const EStyle& obj);

    inline int to_int (const EStyle& e) {
        return static_cast<int> (static_cast<std::underlying_type<SkoarStyles::EStyle>::type> (e));
    }
}