#include "testing_util.hpp"




TEST_CASE("skoar simple", "[simple]") {
    
    SkoarConsoleLogger SkoarLog;

    Skoar fun(L"nerf: 7 )", &SkoarLog);

    REQUIRE(fun.parsedOk);

    SECTION("simple assignment works") {
        SkoarpusclePtr xs;
        SkoarpusclePtr ds;

        fun.play([&](SkoarEventPtr e) {
            xs = e->at(L"nerf");
            ds = e->at(L"dur");
        });

        REQUIRE( check_skoarpuscle_int(xs, 7) == true );
        REQUIRE( check_skoarpuscle_float(ds, 1.0) );

    }
}

TEST_CASE("skoar memories", "[simple]") {

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

    SECTION("SkoarLite memory cleanup - invalid skoar 1") {
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

    SECTION("SkoarLite memory cleanup - invalid skoar 2") {
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

}
