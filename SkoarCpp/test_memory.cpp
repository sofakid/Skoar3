#include "skoarcery.hpp"

#if SKOAR_DEBUG_MEMORY
#include "testing_util.hpp"

void require_no_memory_consumed() {
    INFO(SkoarMemories::o());
    REQUIRE(SkoarMemories::o().Tokes == 0);
    REQUIRE(SkoarMemories::o().Noads == 0);
    REQUIRE(SkoarMemories::o().Skoars == 0);
    REQUIRE(SkoarMemories::o().Skoarpuscles == 0);
    REQUIRE(SkoarMemories::o().Skoarpions == 0);
    REQUIRE(SkoarMemories::o().Projections == 0);
    REQUIRE(SkoarMemories::o().Koars == 0);
    REQUIRE(SkoarMemories::o().Fairies == 0);
    REQUIRE(SkoarMemories::o().Minstrels == 0);
    REQUIRE(SkoarMemories::o().SkoarDics == 0);
    REQUIRE(SkoarMemories::o().Events == 0);
}

void require_fresh_memory_tables() {
    INFO(SkoarMemories::o());
    REQUIRE(SkoarMemories::o().TokesMap.size() == 0);
    REQUIRE(SkoarMemories::o().NoadsMap.size() == 0);
    REQUIRE(SkoarMemories::o().SkoarpusclesMap.size() == 0);
    REQUIRE(SkoarMemories::o().SkoarpionsMap.size() == 0);
    REQUIRE(SkoarMemories::o().ProjectionsMap.size() == 0);
    REQUIRE(SkoarMemories::o().KoarsMap.size() == 0);
    REQUIRE(SkoarMemories::o().FairiesMap.size() == 0);
    REQUIRE(SkoarMemories::o().MinstrelsMap.size() == 0);
    REQUIRE(SkoarMemories::o().SkoarDicsMap.size() == 0);
    REQUIRE(SkoarMemories::o().EventsMap.size() == 0);
}

// ----------------------------------------------------------------------------------------------------------------------------------------
// Test Creating SkoarLites - these don't decorate the tree or try to play it.. just creates tokes and noads..
// ----------------------------------------------------------------------------------------------------------------------------------------
TEST_CASE("SkoarLite Memories", "[memory]") {

    SkoarNullLogger SkoarLog;

    SkoarMemories::o().reset();

    require_no_memory_consumed();
    require_fresh_memory_tables();

    SECTION("valid skoar") {
        SkoarLite(L"a) ]]{! derp<x> !!!x ) 0 a# !} !derp<2>  \n\n\n55 nine : 9 @food {!dorp<s:6> !!@worp !s )) !} {: )) :: 3 times :}", &SkoarLog);
        require_no_memory_consumed();
    }

    SECTION("malformed skoarpion start") {
        SkoarLite(L"a) ]]{ ! derp<x> !!!x ) 0 a# !} !derp<2>  \n\n\n55 nine : 9 @food {!dorp<s:6> !!@worp !s )) !} {: )) :: 3 times :}", &SkoarLog);
        require_no_memory_consumed();
    }

    SECTION("unending skoarpion") {
        SkoarLite(L"a) ]]{! derp<x> !!!x ) 0 a# !} !derp<2>  \n\n\n55 nine : 9 @food {!dorp<s:6> !!@worp !s )) !} {: )) :: 3 times }", &SkoarLog);
        require_no_memory_consumed();
    }

    SECTION("unexpected end of skoarpion") {
        SkoarLite(L"a) ]]{! derp<x> !!!x ) 0 a# !} !derp<2>  \n\n\n55 nine : 9 @food dorp<s:6> !!@worp !s )) !} {: )) :: 3 times !}", &SkoarLog);
        require_no_memory_consumed();
    }

    SECTION("huge int") {
        SkoarLite(L"9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999", &SkoarLog);
        require_no_memory_consumed();
    }
    
}


// ----------------------------------------------------------------------------------------------------------------------------------------
// Test Creating Skoars
// ----------------------------------------------------------------------------------------------------------------------------------------

TEST_CASE("Memories - Simple Skoars", "[memory]") {

    SkoarConsoleLogger SkoarLog;

    SkoarMemories::o().reset();

    require_no_memory_consumed();
    require_fresh_memory_tables();

    SECTION("simple beats") {
        Skoar(L") ) )) ))) } } } }.", &SkoarLog);
        require_no_memory_consumed();
    }

    SECTION("simple data types") {
        Skoar(L"a _a# 7 2.182818459045 2600Hz true false @foo 'socrates' =^.^=", &SkoarLog);
        require_no_memory_consumed();
    }

    SECTION("a loop 3 times") {
        Skoar(L"{: )) :: 3 times :}", &SkoarLog);
        require_no_memory_consumed();
    }

    SECTION("a foreach loop") {
        Skoar(L"<0,1,2>.{: )) :}", &SkoarLog);
        require_no_memory_consumed();
    }

    SECTION("a list") {
        Skoar(L"<0,1,2>", &SkoarLog);
        require_no_memory_consumed();
    }

    SECTION("a deref - no args") {
        Skoar(L"!derp", &SkoarLog);
        require_no_memory_consumed();
    }

    SECTION("a deref - some args") {
        Skoar(L"!derp<3,true>", &SkoarLog);
        require_no_memory_consumed();
    }

    SECTION("a msg - no args") {
        Skoar(L"!derp.flerb", &SkoarLog);
        require_no_memory_consumed();
    }

    SECTION("a msg - some args") {
        Skoar(L"!derp.flerb<3,true>", &SkoarLog);
        require_no_memory_consumed();
    }

    SECTION("a msg chain") {
        Skoar(L"!derp.flerb.florb", &SkoarLog);
        require_no_memory_consumed();
    }

    SECTION("a msg chain - some args 1") {
        Skoar(L"!derp.flerb.florb<2>", &SkoarLog);
        require_no_memory_consumed();
    }

    SECTION("a msg chain - some args 2") {
        Skoar(L"!derp.flerb<1>.florb", &SkoarLog);
        require_no_memory_consumed();
    }

    SECTION("assignment") {
        Skoar(L"x: 7", &SkoarLog);
        require_no_memory_consumed();
    }

    SECTION("assignment expr") {
        Skoar(L"x: 7 + 3", &SkoarLog);
        require_no_memory_consumed();
    }

    SECTION("ops - add") {
        Skoar(L"2 + 3", &SkoarLog);
        require_no_memory_consumed();
    }

    SECTION("fairy") {
        Skoar(L"$", &SkoarLog);
        require_no_memory_consumed();
    }

    SECTION("hashlevels") {
        Skoar(L"[######   ]", &SkoarLog);
        require_no_memory_consumed();
    }

    SECTION("cthulhu") {
        Skoar(L"^^(;,;)^^", &SkoarLog);
        require_no_memory_consumed();
    }
}


TEST_CASE("Memories - Musical keywords", "[memory]") {

    SkoarConsoleLogger SkoarLog;

    SkoarMemories::o().reset();

    require_no_memory_consumed();
    require_fresh_memory_tables();
    SECTION("dynamics") {
        Skoar(L"fff ff fforte forte mf mp piano ppiano ppp", &SkoarLog);
        require_no_memory_consumed();
    }

    SECTION("bars") {
        Skoar(L"| )) |: )) :| )) :|: ))", &SkoarLog);
        require_no_memory_consumed();
    }

    SECTION("D.C. al fine") {
        Skoar(L"D.C. al fine", &SkoarLog);
        require_no_memory_consumed();
    }

    SECTION("fine") {
        Skoar(L"fine", &SkoarLog);
        require_no_memory_consumed();
    }

    SECTION("ottavas") {
        Skoar(L"~~~o", &SkoarLog);
        require_no_memory_consumed();
    }

}

TEST_CASE("Memories - Skoarpions", "[memory]") {

    SkoarConsoleLogger SkoarLog;

    SkoarMemories::o().reset();

    require_no_memory_consumed();
    require_fresh_memory_tables();

    SECTION("skoarpion - no args") {
        Skoar(L"{! derp !! ) !}", &SkoarLog);
        require_no_memory_consumed();
    }

    SECTION("skoarpion - simple args") {
        Skoar(L"{! derp<x> !! ) !}", &SkoarLog);
        require_no_memory_consumed();
    }

    SECTION("skoarpion - default args") {
        Skoar(L"{! derp<x:7> !! ) !}", &SkoarLog);
        require_no_memory_consumed();
    }

    SECTION("skoarpion - default args expr") {
        Skoar(L"{! derp<x:7 + 5> !! ) !}", &SkoarLog);
        require_no_memory_consumed();
    }
}


TEST_CASE("Memories - Conditionals", "[memory]") {

    SkoarConsoleLogger SkoarLog;

    SkoarMemories::o().reset();

    require_no_memory_consumed();
    require_fresh_memory_tables();

    SECTION("if") {
        Skoar(L"{? !x ?? )) ?}", &SkoarLog);
        require_no_memory_consumed();
    }

    SECTION("ifelse") {
        Skoar(L"{? !x ?? )) ?? }} ?}", &SkoarLog);
        require_no_memory_consumed();
    }
}


TEST_CASE("Memories - Invalid Skoars", "[memory]") {

    SkoarConsoleLogger SkoarLog;

    SkoarMemories::o().reset();

    require_no_memory_consumed();
    require_fresh_memory_tables();

    // max double is ~ 10^301.. ~400 digits'l do. 
    wstring huge_float_string(L"9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999.0");
    REQUIRE_THROWS(stod(huge_float_string)); // but we make sure, because we're lazy, but still persnickity.

    SECTION("malformed skoarpion start") {
        Skoar(L"a) ]]{ ! derp<x> !!!x ) 0 a# !} !derp<2>  \n\n\n55 nine : 9 @food {!dorp<s:6> !!@worp !s )) !} {: )) :: 3 times :}", &SkoarLog);
        require_no_memory_consumed();
    }

    SECTION("unending skoarpion") {
        Skoar(L"a) ]]{! derp<x> !!!x ) 0 a# !} !derp<2>  \n\n\n55 nine : 9 @food {!dorp<s:6> !!@worp !s )) !} {: )) :: 3 times }", &SkoarLog);
        require_no_memory_consumed();
    }

    SECTION("unexpected end of skoarpion") {
        Skoar(L"a) ]]{! derp<x> !!!x ) 0 a# !} !derp<2>  \n\n\n55 nine : 9 @food dorp<s:6> !!@worp !s )) !} {: )) :: 3 times !}", &SkoarLog);
        require_no_memory_consumed();
    }

    SECTION("huge int") {
        Skoar(L"9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999", &SkoarLog);
        require_no_memory_consumed();
    }

    SECTION("huge float") {
        Skoar(huge_float_string, &SkoarLog);
        require_no_memory_consumed();
    }

}

#endif