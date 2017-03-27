#include "testing_util.hpp"

TEST_CASE("Sanity", "[sanity]") {

    SkoarConsoleLogger SkoarLog;

    vector<SkoarEventPtr> events;

    MakeEventSep X;
    SkoarString dur = L"dur";
    SkoarString isRest = L"isRest";

    SECTION("long_beats") {

        Skoar skoar(L") ). )) )). ))) )))) .))))) )))))) )))))))", &SkoarLog);
        REQUIRE(skoar.parsedOk);

        auto events = skoar_get_events(&skoar);

        auto desires = make_events_vec(
            dur, 1.0, X,
            dur, 1.5, X,
            dur, 2.0, X,
            dur, 3.0, X,
            dur, 4.0, X,
            dur, 8.0, X,
            dur, 16.0, X,
            dur, 32.0, X,
            dur, 64.0, X
        );

        compare_desires_to_events(desires, events);
    }
}
