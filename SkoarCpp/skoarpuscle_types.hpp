#pragma once

namespace ESkoarpuscle {

    enum Kind {
        // can do math and compare these kinds
        Cat,
        Int,
        Float,
        HashLevel,
        Freq,

        Noat,
        Choard,

        False,
        True,

        Symbol,
        String,

        List,
        UGen,
        Envelope,

        Beat,
        Rest,

        SymbolColon,

        Other,
        Any,

        // other kinds we need to know about,
        Times,
        Bars,
        Colons,
        RepeatSigns,
    };
}


