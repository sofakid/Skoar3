#include "skoarcery.hpp"

#if SKOAR_DEBUG_MEMORY
#include "testing_util.hpp"

// ----------------------------------------------------------------------------------------------------------------------------------------
// Test Creating SkoarLites - these don't decorate the tree or try to play it.. just creates tokes and noads..
// ----------------------------------------------------------------------------------------------------------------------------------------

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


TEST_CASE("skoar lite memories", "[memory]") {

    SkoarNullLogger SkoarLog;

    SkoarMemories::o().reset();

    require_no_memory_consumed();

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

    SECTION("SkoarLite memory cleanup - valid skoar") {
        SkoarLite(L"a) ]]{! derp<x> !!!x ) 0 a# !} !derp<2>  \n\n\n55 nine : 9 @food {!dorp<s:6> !!@worp !s )) !} {: )) :: 3 times :}", &SkoarLog);
        require_no_memory_consumed();
    }

    SECTION("SkoarLite memory cleanup - invalid skoar 1 - malformed skoarpion start") {
        SkoarLite(L"a) ]]{ ! derp<x> !!!x ) 0 a# !} !derp<2>  \n\n\n55 nine : 9 @food {!dorp<s:6> !!@worp !s )) !} {: )) :: 3 times :}", &SkoarLog);
        require_no_memory_consumed();
    }

    SECTION("SkoarLite memory cleanup - invalid skoar 2 - unending skoarpion") {
        SkoarLite(L"a) ]]{! derp<x> !!!x ) 0 a# !} !derp<2>  \n\n\n55 nine : 9 @food {!dorp<s:6> !!@worp !s )) !} {: )) :: 3 times }", &SkoarLog);
        require_no_memory_consumed();
    }

    SECTION("SkoarLite memory cleanup - invalid skoar 3 - unexpected end of skoarpion") {
        SkoarLite(L"a) ]]{! derp<x> !!!x ) 0 a# !} !derp<2>  \n\n\n55 nine : 9 @food dorp<s:6> !!@worp !s )) !} {: )) :: 3 times !}", &SkoarLog);
        require_no_memory_consumed();
    }

    SECTION("SkoarLite memory cleanup - invalid skoar 4 - huge int") {
        SkoarLite(L"9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999", &SkoarLog);
        require_no_memory_consumed();
    }
    
}

#if 0
// ----------------------------------------------------------------------------------------------------------------------------------------
// Test Creating Skoars
// ----------------------------------------------------------------------------------------------------------------------------------------

TEST_CASE("Skoar Memories", "[memory]") {

    SkoarConsoleLogger SkoarLog;

    SkoarMemories::o().reset();

    require_no_memory_consumed();
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

    SECTION("Skoar memory cleanup - valid skoar") {
        Skoar(L"a) ]]{! derp<x> !!!x ) 0 a# !} !derp<2>  \n\n\n55 nine : 9 @food {!dorp<s:6> !!@worp !s )) !} {: )) :: 3 times :}", &SkoarLog);
        require_no_memory_consumed();
    }

    SECTION("Skoar memory cleanup - invalid skoar 1 - malformed skoarpion start") {
        Skoar(L"a) ]]{ ! derp<x> !!!x ) 0 a# !} !derp<2>  \n\n\n55 nine : 9 @food {!dorp<s:6> !!@worp !s )) !} {: )) :: 3 times :}", &SkoarLog);
        require_no_memory_consumed();
    }

    SECTION("Skoar memory cleanup - invalid skoar 2 - unending skoarpion") {
        Skoar(L"a) ]]{! derp<x> !!!x ) 0 a# !} !derp<2>  \n\n\n55 nine : 9 @food {!dorp<s:6> !!@worp !s )) !} {: )) :: 3 times }", &SkoarLog);
        require_no_memory_consumed();
    }

    SECTION("Skoar memory cleanup - invalid skoar 3 - unexpected end of skoarpion") {
        Skoar(L"a) ]]{! derp<x> !!!x ) 0 a# !} !derp<2>  \n\n\n55 nine : 9 @food dorp<s:6> !!@worp !s )) !} {: )) :: 3 times !}", &SkoarLog);
        require_no_memory_consumed();
    }

    SECTION("Skoar memory cleanup - invalid skoar 4 - huge int") {
        Skoar(L"9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999", &SkoarLog);
        require_no_memory_consumed();
    }

}
#endif


#endif