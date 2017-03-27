#include "skoarcery.hpp"

#if SKOAR_DEBUG_MEMORY
#include "testing_util.hpp"

// ----------------------------------------------------------------------------------------------------------------------------------------
// Test Creating SkoarLites - these don't decorate the tree or try to play it.. just creates tokes and noads..
// ----------------------------------------------------------------------------------------------------------------------------------------


TEST_CASE("skoar lite memories", "[memory]") {

    SkoarConsoleLogger SkoarLog;

    SkoarMemories.reset();

    REQUIRE(SkoarMemories.Tokes == 0);
    REQUIRE(SkoarMemories.Noads == 0);
    REQUIRE(SkoarMemories.Skoars == 0);
    REQUIRE(SkoarMemories.Skoarpuscles == 0);
    REQUIRE(SkoarMemories.Skoarpions == 0);
    REQUIRE(SkoarMemories.Projections == 0);
    REQUIRE(SkoarMemories.Koars == 0);
    REQUIRE(SkoarMemories.Fairies == 0);
    REQUIRE(SkoarMemories.Minstrels == 0);
    REQUIRE(SkoarMemories.SkoarDics == 0);
    REQUIRE(SkoarMemories.Events == 0);

    REQUIRE(SkoarMemories.TokesMap.size() == 0);
    REQUIRE(SkoarMemories.NoadsMap.size() == 0);
    REQUIRE(SkoarMemories.SkoarpusclesMap.size() == 0);
    REQUIRE(SkoarMemories.SkoarpionsMap.size() == 0);
    REQUIRE(SkoarMemories.ProjectionsMap.size() == 0);
    REQUIRE(SkoarMemories.KoarsMap.size() == 0);
    REQUIRE(SkoarMemories.FairiesMap.size() == 0);
    REQUIRE(SkoarMemories.MinstrelsMap.size() == 0);
    REQUIRE(SkoarMemories.SkoarDicsMap.size() == 0);
    REQUIRE(SkoarMemories.EventsMap.size() == 0);

    SECTION("SkoarLite memory cleanup - valid skoar") {
        SkoarLite(L"a) ]]{! derp<x> !!!x ) 0 a# !} !derp<2>  \n\n\n55 nine : 9 @food {!dorp<s:6> !!@worp !s )) !} {: )) :: 3 times :}", &SkoarLog);

        INFO(SkoarMemories);
        REQUIRE(SkoarMemories.Tokes == 0);
        REQUIRE(SkoarMemories.Noads == 0);
        REQUIRE(SkoarMemories.Skoars == 0);
        REQUIRE(SkoarMemories.Skoarpuscles == 0);
        REQUIRE(SkoarMemories.Skoarpions == 0);
        REQUIRE(SkoarMemories.Projections == 0);
        REQUIRE(SkoarMemories.Koars == 0);
        REQUIRE(SkoarMemories.Fairies == 0);
        REQUIRE(SkoarMemories.Minstrels == 0);
        REQUIRE(SkoarMemories.SkoarDics == 0);
        REQUIRE(SkoarMemories.Events == 0);

    }

    SECTION("SkoarLite memory cleanup - invalid skoar 1 - malformed skoarpion start") {
        SkoarLite(L"a) ]]{ ! derp<x> !!!x ) 0 a# !} !derp<2>  \n\n\n55 nine : 9 @food {!dorp<s:6> !!@worp !s )) !} {: )) :: 3 times :}", &SkoarLog);

        INFO(SkoarMemories);
        REQUIRE(SkoarMemories.Tokes == 0);
        REQUIRE(SkoarMemories.Noads == 0);
        REQUIRE(SkoarMemories.Skoars == 0);
        REQUIRE(SkoarMemories.Skoarpuscles == 0);
        REQUIRE(SkoarMemories.Skoarpions == 0);
        REQUIRE(SkoarMemories.Projections == 0);
        REQUIRE(SkoarMemories.Koars == 0);
        REQUIRE(SkoarMemories.Fairies == 0);
        REQUIRE(SkoarMemories.Minstrels == 0);
        REQUIRE(SkoarMemories.SkoarDics == 0);
        REQUIRE(SkoarMemories.Events == 0);

    }

    SECTION("SkoarLite memory cleanup - invalid skoar 2 - unending skoarpion") {
        SkoarLite(L"a) ]]{! derp<x> !!!x ) 0 a# !} !derp<2>  \n\n\n55 nine : 9 @food {!dorp<s:6> !!@worp !s )) !} {: )) :: 3 times }", &SkoarLog);

        INFO(SkoarMemories);
        REQUIRE(SkoarMemories.Tokes == 0);
        REQUIRE(SkoarMemories.Noads == 0);
        REQUIRE(SkoarMemories.Skoars == 0);
        REQUIRE(SkoarMemories.Skoarpuscles == 0);
        REQUIRE(SkoarMemories.Skoarpions == 0);
        REQUIRE(SkoarMemories.Projections == 0);
        REQUIRE(SkoarMemories.Koars == 0);
        REQUIRE(SkoarMemories.Fairies == 0);
        REQUIRE(SkoarMemories.Minstrels == 0);
        REQUIRE(SkoarMemories.SkoarDics == 0);
        REQUIRE(SkoarMemories.Events == 0);

    }

    SECTION("SkoarLite memory cleanup - invalid skoar 3 - unexpected end of skoarpion") {
        SkoarLite(L"a) ]]{! derp<x> !!!x ) 0 a# !} !derp<2>  \n\n\n55 nine : 9 @food dorp<s:6> !!@worp !s )) !} {: )) :: 3 times !}", &SkoarLog);

        INFO(SkoarMemories);
        REQUIRE(SkoarMemories.Tokes == 0);
        REQUIRE(SkoarMemories.Noads == 0);
        REQUIRE(SkoarMemories.Skoars == 0);
        REQUIRE(SkoarMemories.Skoarpuscles == 0);
        REQUIRE(SkoarMemories.Skoarpions == 0);
        REQUIRE(SkoarMemories.Projections == 0);
        REQUIRE(SkoarMemories.Koars == 0);
        REQUIRE(SkoarMemories.Fairies == 0);
        REQUIRE(SkoarMemories.Minstrels == 0);
        REQUIRE(SkoarMemories.SkoarDics == 0);
        REQUIRE(SkoarMemories.Events == 0);

    }

    SECTION("SkoarLite memory cleanup - invalid skoar 4 - huge int") {
        SkoarLite(L"9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999", &SkoarLog);

        INFO(SkoarMemories);
        REQUIRE(SkoarMemories.Tokes == 0);
        REQUIRE(SkoarMemories.Noads == 0);
        REQUIRE(SkoarMemories.Skoars == 0);
        REQUIRE(SkoarMemories.Skoarpuscles == 0);
        REQUIRE(SkoarMemories.Skoarpions == 0);
        REQUIRE(SkoarMemories.Projections == 0);
        REQUIRE(SkoarMemories.Koars == 0);
        REQUIRE(SkoarMemories.Fairies == 0);
        REQUIRE(SkoarMemories.Minstrels == 0);
        REQUIRE(SkoarMemories.SkoarDics == 0);
        REQUIRE(SkoarMemories.Events == 0);

    }
    
}

#if 0
// ----------------------------------------------------------------------------------------------------------------------------------------
// Test Creating Skoars
// ----------------------------------------------------------------------------------------------------------------------------------------

TEST_CASE("Skoar Memories", "[memory]") {

    SkoarConsoleLogger SkoarLog;

    SkoarMemories.reset();

    REQUIRE(SkoarMemories.Tokes == 0);
    REQUIRE(SkoarMemories.Noads == 0);
    REQUIRE(SkoarMemories.Skoars == 0);
    REQUIRE(SkoarMemories.Skoarpuscles == 0);
    REQUIRE(SkoarMemories.Skoarpions == 0);
    REQUIRE(SkoarMemories.Projections == 0);
    REQUIRE(SkoarMemories.Koars == 0);
    REQUIRE(SkoarMemories.Fairies == 0);
    REQUIRE(SkoarMemories.Minstrels == 0);
    REQUIRE(SkoarMemories.SkoarDics == 0);
    REQUIRE(SkoarMemories.Events == 0);

    REQUIRE(SkoarMemories.TokesMap.size() == 0);
    REQUIRE(SkoarMemories.NoadsMap.size() == 0);
    REQUIRE(SkoarMemories.SkoarpusclesMap.size() == 0);
    REQUIRE(SkoarMemories.SkoarpionsMap.size() == 0);
    REQUIRE(SkoarMemories.ProjectionsMap.size() == 0);
    REQUIRE(SkoarMemories.KoarsMap.size() == 0);
    REQUIRE(SkoarMemories.FairiesMap.size() == 0);
    REQUIRE(SkoarMemories.MinstrelsMap.size() == 0);
    REQUIRE(SkoarMemories.SkoarDicsMap.size() == 0);
    REQUIRE(SkoarMemories.EventsMap.size() == 0);

    SECTION("Skoar memory cleanup - valid skoar") {
        Skoar(L"a) ]]{! derp<x> !!!x ) 0 a# !} !derp<2>  \n\n\n55 nine : 9 @food {!dorp<s:6> !!@worp !s )) !} {: )) :: 3 times :}", &SkoarLog);

        INFO(SkoarMemories);
        REQUIRE(SkoarMemories.Tokes == 0);
        REQUIRE(SkoarMemories.Noads == 0);
        REQUIRE(SkoarMemories.Skoars == 0);
        REQUIRE(SkoarMemories.Skoarpuscles == 0);
        REQUIRE(SkoarMemories.Skoarpions == 0);
        REQUIRE(SkoarMemories.Projections == 0);
        REQUIRE(SkoarMemories.Koars == 0);
        REQUIRE(SkoarMemories.Fairies == 0);
        REQUIRE(SkoarMemories.Minstrels == 0);
        REQUIRE(SkoarMemories.SkoarDics == 0);
        REQUIRE(SkoarMemories.Events == 0);

    }

    SECTION("Skoar memory cleanup - invalid skoar 1 - malformed skoarpion start") {
        Skoar(L"a) ]]{ ! derp<x> !!!x ) 0 a# !} !derp<2>  \n\n\n55 nine : 9 @food {!dorp<s:6> !!@worp !s )) !} {: )) :: 3 times :}", &SkoarLog);

        INFO(SkoarMemories);
        REQUIRE(SkoarMemories.Tokes == 0);
        REQUIRE(SkoarMemories.Noads == 0);
        REQUIRE(SkoarMemories.Skoars == 0);
        REQUIRE(SkoarMemories.Skoarpuscles == 0);
        REQUIRE(SkoarMemories.Skoarpions == 0);
        REQUIRE(SkoarMemories.Projections == 0);
        REQUIRE(SkoarMemories.Koars == 0);
        REQUIRE(SkoarMemories.Fairies == 0);
        REQUIRE(SkoarMemories.Minstrels == 0);
        REQUIRE(SkoarMemories.SkoarDics == 0);
        REQUIRE(SkoarMemories.Events == 0);

    }

    SECTION("Skoar memory cleanup - invalid skoar 2 - unending skoarpion") {
        Skoar(L"a) ]]{! derp<x> !!!x ) 0 a# !} !derp<2>  \n\n\n55 nine : 9 @food {!dorp<s:6> !!@worp !s )) !} {: )) :: 3 times }", &SkoarLog);

        INFO(SkoarMemories);
        REQUIRE(SkoarMemories.Tokes == 0);
        REQUIRE(SkoarMemories.Noads == 0);
        REQUIRE(SkoarMemories.Skoars == 0);
        REQUIRE(SkoarMemories.Skoarpuscles == 0);
        REQUIRE(SkoarMemories.Skoarpions == 0);
        REQUIRE(SkoarMemories.Projections == 0);
        REQUIRE(SkoarMemories.Koars == 0);
        REQUIRE(SkoarMemories.Fairies == 0);
        REQUIRE(SkoarMemories.Minstrels == 0);
        REQUIRE(SkoarMemories.SkoarDics == 0);
        REQUIRE(SkoarMemories.Events == 0);

    }

    SECTION("Skoar memory cleanup - invalid skoar 3 - unexpected end of skoarpion") {
        Skoar(L"a) ]]{! derp<x> !!!x ) 0 a# !} !derp<2>  \n\n\n55 nine : 9 @food dorp<s:6> !!@worp !s )) !} {: )) :: 3 times !}", &SkoarLog);

        INFO(SkoarMemories);
        REQUIRE(SkoarMemories.Tokes == 0);
        REQUIRE(SkoarMemories.Noads == 0);
        REQUIRE(SkoarMemories.Skoars == 0);
        REQUIRE(SkoarMemories.Skoarpuscles == 0);
        REQUIRE(SkoarMemories.Skoarpions == 0);
        REQUIRE(SkoarMemories.Projections == 0);
        REQUIRE(SkoarMemories.Koars == 0);
        REQUIRE(SkoarMemories.Fairies == 0);
        REQUIRE(SkoarMemories.Minstrels == 0);
        REQUIRE(SkoarMemories.SkoarDics == 0);
        REQUIRE(SkoarMemories.Events == 0);

    }

    SECTION("Skoar memory cleanup - invalid skoar 4 - huge int") {
        Skoar(L"9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999", &SkoarLog);

        INFO(SkoarMemories);
        REQUIRE(SkoarMemories.Tokes == 0);
        REQUIRE(SkoarMemories.Noads == 0);
        REQUIRE(SkoarMemories.Skoars == 0);
        REQUIRE(SkoarMemories.Skoarpuscles == 0);
        REQUIRE(SkoarMemories.Skoarpions == 0);
        REQUIRE(SkoarMemories.Projections == 0);
        REQUIRE(SkoarMemories.Koars == 0);
        REQUIRE(SkoarMemories.Fairies == 0);
        REQUIRE(SkoarMemories.Minstrels == 0);
        REQUIRE(SkoarMemories.SkoarDics == 0);
        REQUIRE(SkoarMemories.Events == 0);

    }

}
#endif


#endif