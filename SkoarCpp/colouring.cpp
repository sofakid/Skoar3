#include "lex.hpp"

SkoarColouring::SkoarColouring() {

    tokeStyles[ESkoarToke::False]       = EStyle::False;
    tokeStyles[ESkoarToke::True]        = EStyle::True;
    tokeStyles[ESkoarToke::Times]       = EStyle::Times;
    tokeStyles[ESkoarToke::Choard]      = EStyle::Choard;
    tokeStyles[ESkoarToke::Symbol]      = EStyle::Symbol;
    tokeStyles[ESkoarToke::Comment]     = EStyle::Comment;
    tokeStyles[ESkoarToke::MathOp]      = EStyle::MathOp;
    tokeStyles[ESkoarToke::BooleanOp]   = EStyle::BooleanOp;
    tokeStyles[ESkoarToke::HashLevel]   = EStyle::HashLevel;
    tokeStyles[ESkoarToke::Bars]        = EStyle::Bars;
    tokeStyles[ESkoarToke::AssOp]       = EStyle::AssOp;
    tokeStyles[ESkoarToke::Carrot]      = EStyle::Carrot;
    tokeStyles[ESkoarToke::Voice]       = EStyle::Voice;
    tokeStyles[ESkoarToke::Fairy]       = EStyle::Fairy;
    tokeStyles[ESkoarToke::Freq]        = EStyle::Freq;
    tokeStyles[ESkoarToke::String]      = EStyle::String;
    tokeStyles[ESkoarToke::NamedNoat]   = EStyle::NamedNoat;
    tokeStyles[ESkoarToke::MsgOp]       = EStyle::MsgOp;
    tokeStyles[ESkoarToke::Tuplet]      = EStyle::Tuplet;
    tokeStyles[ESkoarToke::Int]         = EStyle::Int;
    tokeStyles[ESkoarToke::Float]       = EStyle::Float;
    //tokeStyles[ESkoarToke::SymbolColon] = EStyle::SymbolColon;
    //tokeStyles[ESkoarToke::Duration]    = EStyle::Duration;
    //tokeStyles[ESkoarToke::Cat]         = EStyle::Cat;

    noadStyles[ESkoarNoad::dynamic]     = EStyle::dynamic;
    noadStyles[ESkoarNoad::msg]         = EStyle::msg;
    noadStyles[ESkoarNoad::cthulhu]     = EStyle::cthulhu;
    noadStyles[ESkoarNoad::marker]      = EStyle::marker;
    noadStyles[ESkoarNoad::deref]       = EStyle::deref;
    noadStyles[ESkoarNoad::ottavas]     = EStyle::ottavas;
    noadStyles[ESkoarNoad::listy]       = EStyle::listy;
    noadStyles[ESkoarNoad::beat]        = EStyle::beat;
    noadStyles[ESkoarNoad::conditional] = EStyle::conditional;
    noadStyles[ESkoarNoad::skoarpion]   = EStyle::skoarpion;
    noadStyles[ESkoarNoad::loop]        = EStyle::loop;
    //noadStyles[ESkoarNoad::lute]        = EStyle::lute;
    //noadStyles[ESkoarNoad::meditation]  = EStyle::meditation;
    //noadStyles[ESkoarNoad::ugen]        = EStyle::ugen;
    //noadStyles[ESkoarNoad::arg_listy]   = EStyle::arg_listy;

}

SkoarColouring::EStyle SkoarColouring::getTokeStyle(ESkoarToke::Kind kind) {
    return tokeStyles[kind];
}

SkoarColouring::EStyle SkoarColouring::getNoadStyle(ESkoarNoad::Kind kind) {
    return noadStyles[kind];
}

SkoarColouring SkoarStyles;