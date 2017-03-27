#include "testing_util.hpp"




TEST_CASE("skoar simple", "[sanity]") {
    
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
