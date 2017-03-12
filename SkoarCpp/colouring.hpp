#pragma once

#include "lex.hpp"

class SkoarColouring {
public:
    enum class EStyle {
        nostyle,
        False,
        True,
        Times,
        Choard,
        SymbolColon,
        Symbol,
        Comment,
        MathOp,
        BooleanOp,
        HashLevel,
        Bars,
        AssOp,
        Carrot,
        Cat,
        Voice,
        Fairy,
        Freq,
        String,
        NamedNoat,
        MsgOp,
        Tuplet,
        Duration,
        Int,
        Float,

        lute,
        meditation,
        dynamic,
        msg,
        arg_listy,
        cthulhu,
        marker,
        ugen,
        deref,
        ottavas,
        listy,
        beat,
        conditional,
        skoarpion,
        loop
    };


    friend std::wostream& operator << (std::wostream& out, const EStyle& e)
    {
        if (e == EStyle::nostyle)
            out << L"_";
        else
            out << static_cast<std::underlying_type<EStyle>::type>(e);
        return out;
    }

    SkoarColouring();

    EStyle getTokeStyle(ESkoarToke::Kind kind);
    EStyle getNoadStyle(ESkoarNoad::Kind kind);

private:
    std::map<ESkoarToke::Kind, EStyle> tokeStyles;
    std::map<ESkoarNoad::Kind, EStyle> noadStyles;
};
