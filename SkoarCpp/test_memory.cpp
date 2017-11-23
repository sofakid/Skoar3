#include "skoarcery.hpp"

#if SKOAR_DEBUG_MEMORY
#include "testing_util.hpp"

void require_no_memory_consumed () {
    INFO (SkoarMemories::o ());
    REQUIRE (SkoarMemories::o ().Tokes == 0);
    REQUIRE (SkoarMemories::o ().Noads == 0);
    REQUIRE (SkoarMemories::o ().Skoars == 0);
    REQUIRE (SkoarMemories::o ().Skoarpuscles == 0);
    REQUIRE (SkoarMemories::o ().Skoarpions == 0);
    REQUIRE (SkoarMemories::o ().Projections == 0);
    REQUIRE (SkoarMemories::o ().Koars == 0);
    REQUIRE (SkoarMemories::o ().Fairies == 0);
    REQUIRE (SkoarMemories::o ().Minstrels == 0);
    REQUIRE (SkoarMemories::o ().SkoarDics == 0);
    REQUIRE (SkoarMemories::o ().Events == 0);
}

void require_fresh_memory_tables () {
    INFO (SkoarMemories::o ());
    REQUIRE (SkoarMemories::o ().TokesMap.size () == 0);
    REQUIRE (SkoarMemories::o ().NoadsMap.size () == 0);
    REQUIRE (SkoarMemories::o ().SkoarpusclesMap.size () == 0);
    REQUIRE (SkoarMemories::o ().SkoarpionsMap.size () == 0);
    REQUIRE (SkoarMemories::o ().ProjectionsMap.size () == 0);
    REQUIRE (SkoarMemories::o ().KoarsMap.size () == 0);
    REQUIRE (SkoarMemories::o ().FairiesMap.size () == 0);
    REQUIRE (SkoarMemories::o ().MinstrelsMap.size () == 0);
    REQUIRE (SkoarMemories::o ().SkoarDicsMap.size () == 0);
    REQUIRE (SkoarMemories::o ().EventsMap.size () == 0);
}

void createSkoarLite (wstring skoarce) {
    SkoarNullLogger SkoarLog;
    INFO ("SkoarBegin :: \"" << SkoarString_to_s (skoarce) << "\" :: SkoarEnd");
    SkoarLite (skoarce, &SkoarLog);
    require_no_memory_consumed ();

}

void createSkoar (wstring skoarce) {
    SkoarNullLogger SkoarLog;
    INFO ("SkoarBegin :: \"" << SkoarString_to_s (skoarce) << "\" :: SkoarEnd");
    Skoar (skoarce, &SkoarLog);
    require_no_memory_consumed ();
}

// ----------------------------------------------------------------------------------------------------------------------------------------
// Test Creating SkoarLites - these don't decorate the tree or try to play it.. just creates tokes and noads..
// ----------------------------------------------------------------------------------------------------------------------------------------
TEST_CASE ("SkoarLite Memories", "[memory]") {

    SkoarNullLogger SkoarLog;

    SkoarMemories::o ().reset ();

    require_no_memory_consumed ();
    require_fresh_memory_tables ();

    SECTION ("valid skoar") {
        createSkoarLite (L"a) ]] derp:!! x {! !x ) 0 a# !} !derp<2>  \n\n\n55 nine : 9 @food dorp: !! s:6 {! @worp !s )) !} {: )) :: 3 times :}");
    }

    SECTION ("unending loop") {
        createSkoarLite (L"a) ]] derp:!! x {! !x ) 0 a# !} !derp<2>  \n\n\n55 nine : 9 @food dorp: !! s:6 {! @worp !s )) !} {: )) :: 3 times }");
    }

    SECTION ("unending loop2") {
        createSkoarLite (L"a) ]] derp:!! x {! !x ) 0 a# !} !derp<2>  \n\n\n55 nine : 9 @food dorp: !! s:6 {! @worp !s )) !} {: )) :: 3 times ");
    }
    SECTION ("unending loop3") {
        createSkoarLite (L"a) ]] derp:!! x {! !x ) 0 a# !} !derp<2>  \n\n\n55 nine : 9 @food dorp: !! s:6 {! @worp !s )) !} {: ))  ");
    }

    SECTION ("malformed skoarpion start") {
        createSkoarLite (L"a) ]]derp:!! x { !!x ) 0 a# !} !derp<2>  \n\n\n55 nine : 9 @food dorp: !! s:6 {!@worp !s )) !} {: )) :: 3 times :}");
    }

    SECTION ("unending skoarpion") {
        createSkoarLite (L"a) ]]derp:!! x {!!x ) 0 a# !} !derp<2>  \n\n\n55 nine : 9 @food dorp: !! s:6 {!@worp !s )) {: )) :: 3 times :}");
    }

    SECTION ("unexpected end of skoarpion") {
        createSkoarLite (L"a) ]]derp:!! x {! !x ) 0 a# !} !derp<2>  \n\n\n55 nine : 9 @food !} dorp: !! s:6 {! @worp !s )) !} {: )) :: 3 times !}");
    }

    SECTION ("huge int") {
        createSkoarLite (L"9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999");
    }

}


// ----------------------------------------------------------------------------------------------------------------------------------------
// Test Creating Skoars
// ----------------------------------------------------------------------------------------------------------------------------------------

TEST_CASE ("Memories - Simple Skoars", "[memory]") {

    SkoarMemories::o ().reset ();

    require_no_memory_consumed ();
    require_fresh_memory_tables ();

    SECTION ("simple beats") {
        createSkoar (L") ) )) ))) } } } }.");
    }

    SECTION ("simple data types") {
        createSkoar (L"a _a# 7 2.182818459045 2600Hz true false @foo 'socrates' =^.^=");
    }

    SECTION ("a loop 3 times") {
        createSkoar (L"{: )) :: 3 times :}");
    }

    SECTION ("a foreach loop") {
        createSkoar (L"<0,1,2>.{: )) :}");
    }

    SECTION ("a list") {
        createSkoar (L"<0,1,2>");
    }

    SECTION ("a deref - no args") {
        createSkoar (L"!derp");
    }

    SECTION ("a deref - some args") {
        createSkoar (L"!derp<3,true>");
    }

    SECTION ("a msg - no args") {
        createSkoar (L"!derp.flerb");
    }

    SECTION ("a msg - some args") {
        createSkoar (L"!derp.flerb<3,true>");
    }

    SECTION ("a msg chain") {
        createSkoar (L"!derp.flerb.florb");
    }

    SECTION ("a msg chain - some args 1") {
        createSkoar (L"!derp.flerb.florb<2>");
    }

    SECTION ("a msg chain - some args 2") {
        createSkoar (L"!derp.flerb<1>.florb");
    }

    SECTION ("assignment") {
        createSkoar (L"x: 7");
    }

    SECTION ("assignment expr") {
        createSkoar (L"x: 7 + 3");
    }

    SECTION ("ops - add") {
        createSkoar (L"2 + 3");
    }

    SECTION ("fairy") {
        createSkoar (L"$");
    }

    SECTION ("hashlevels") {
        createSkoar (L"[######   ]");
    }

    SECTION ("cthulhu") {
        createSkoar (L"^^(;,;)^^");
    }
}


TEST_CASE ("Memories - Musical keywords", "[memory]") {

    SkoarMemories::o ().reset ();

    require_no_memory_consumed ();
    require_fresh_memory_tables ();
    SECTION ("dynamics") {
        createSkoar (L"fff ff fforte forte mf mp piano ppiano ppp");
    }

    SECTION ("bars") {
        createSkoar (L"| )) |: )) :| )) :|: ))");
    }

    SECTION ("D.C. al fine") {
        createSkoar (L"D.C. al fine");
    }

    SECTION ("fine") {
        createSkoar (L"fine");
    }

    SECTION ("ottavas") {
        createSkoar (L"~~~o");
    }

}

TEST_CASE ("Memories - Skoarpions", "[memory]") {

    SkoarMemories::o ().reset ();

    require_no_memory_consumed ();
    require_fresh_memory_tables ();

    SECTION ("skoarpion - no args") {
        createSkoar (L"derp: {! ) !}");
    }

    SECTION ("skoarpion - no args with skoarpion inside - no args") {
        createSkoar (L"derp: {! ) yeez: {! ))) !} !}");
    }

    SECTION ("skoarpion - simple args") {
        createSkoar (L"derp: !! x {! ) !}");
    }

    SECTION ("skoarpion - simple args with skoarpion inside - simple args") {
        createSkoar (L"derp: !! x {! )  yeez: !! y {! ))) !} !}");
    }

    SECTION ("skoarpion - simple two args") {
        createSkoar (L"derp: !! x, y {! ) !}");
    }

    SECTION ("skoarpion - default args") {
        createSkoar (L"derp: !! x:7 {! ) !}");
    }

    SECTION ("skoarpion - default args expr") {
        createSkoar (L"derp: !! x:7+5 {! ) !}");
    }

    SECTION ("skoarpion - default args skoarpion no args") {
        createSkoar (L"derp: !! x:{! 8 !} {! ) !}");
    }

    SECTION ("skoarpion - default args skoarpion simple args") {
        createSkoar (L"derp: !! x:!! y {! 8 !} {! ) !}");
    }

    SECTION ("skoarpion - default args skoarpion default args") {
        createSkoar (L"derp: !! x:!! y:3 {! 8 !} {! ) !}");
    }

}


TEST_CASE ("Memories - Conditionals", "[memory]") {

    SkoarMemories::o ().reset ();

    require_no_memory_consumed ();
    require_fresh_memory_tables ();

    SECTION ("if") {
        createSkoar (L"{? !x ?? )) ?}");
    }

    SECTION ("ifelse") {
        createSkoar (L"{? !x ?? )) ?? }} ?}");
    }
}


TEST_CASE ("Memories - Invalid Skoars", "[memory]") {

    SkoarMemories::o ().reset ();

    require_no_memory_consumed ();
    require_fresh_memory_tables ();

    // max double is ~ 10^301.. ~400 digits'l do. 
    SkoarString huge_float_string (L"9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999.0");
    REQUIRE_THROWS (stod (huge_float_string)); // but we make sure, because we're lazy, but still persnickity.

    SkoarString hz (L"Hz");
    SkoarString huge_freq_string (huge_float_string + hz);

    SECTION ("unending loop") {
        createSkoar (L"a) ]] derp:!! x {! !x ) 0 a# !} !derp<2>  \n\n\n55 nine : 9 @food dorp: !! s:6 {! @worp !s )) !} {: )) :: 3 times }");
    }

    SECTION ("unending loop2") {
        createSkoar (L"a) ]] derp:!! x {! !x ) 0 a# !} !derp<2>  \n\n\n55 nine : 9 @food dorp: !! s:6 {! @worp !s )) !} {: )) :: 3 times ");
    }
    SECTION ("unending loop3") {
        createSkoar (L"a) ]] derp:!! x {! !x ) 0 a# !} !derp<2>  \n\n\n55 nine : 9 @food dorp: !! s:6 {! @worp !s )) !} {: ))  ");
    }

    SECTION ("malformed skoarpion start") {
        createSkoar (L"a) ]]derp:!! x { !!x ) 0 a# !} !derp<2>  \n\n\n55 nine : 9 @food dorp: !! s:6 {!@worp !s )) !} {: )) :: 3 times :}");
    }

    SECTION ("unending skoarpion") {
        createSkoar (L"a) ]]derp:!! x {!!x ) 0 a# !} !derp<2>  \n\n\n55 nine : 9 @food dorp: !! s:6 {!@worp !s )) {: )) :: 3 times :}");
    }

    SECTION ("unexpected end of skoarpion") {
        createSkoar (L"a) ]]derp:!! x {! !x ) 0 a# !} !derp<2>  \n\n\n55 nine : 9 @food !} dorp: !! s:6 {! @worp !s )) !} {: )) :: 3 times !}");
    }

    SECTION ("huge int") {
        createSkoar (L"9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999");
    }

    SECTION ("huge float") {
        createSkoar (huge_float_string);
    }

    SECTION ("huge freq") {
        createSkoar (huge_freq_string);
    }
}

#endif