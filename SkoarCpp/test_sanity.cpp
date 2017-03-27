#include "testing_util.hpp"

TEST_CASE("Beats and Rests", "[sanity]") {

    MakeEventSep X;
    SkoarString dur = L"dur";
    SkoarString isRest = L"isRest";

    SECTION("long_beats") {
        run_and_expect(L") ). )) )). ))) )))) .))))) )))))) )))))))", make_events_vec(
            dur, 1.0, X, dur, 1.5, X, dur, 2.0, X, dur, 3.0, X,
            dur, 4.0, X, dur, 8.0, X, dur, 16.0, X, dur, 32.0, X,
            dur, 64.0, X
        ));
    }

    SECTION("short_beats") {
        run_and_expect(L"] ]] ]]]  ]]]] ]]. ]]].  ]]]]] .]]]]]] ]]]]]]]", make_events_vec(
            dur, 0.5, X, dur, 0.25, X, dur, 1.0 / 8.0, X, dur, 1.0 / 16.0, X,
            dur, 3.0 / 8.0, X, dur, 3.0 / 16.0, X, dur, 1.0 / 32.0, X, dur, 1.0 / 64.0, X,
            dur, 1.0 / 128.0, X
        ));
    }

    SECTION("long_rests") {
        run_and_expect(L"} }} }}} }}}} }. }}.", make_events_vec(
            dur, 1.0, isRest, true, X, dur, 2.0, isRest, true, X,
            dur, 4.0, isRest, true, X, dur, 8.0, isRest, true, X,
            dur, 1.5, isRest, true, X, dur, 3.0, isRest, true, X
        ));
    }

    SECTION("short_rests") {
        run_and_expect(L"o/ oo/ ooo/ oooo/ ooooo/   o/. oo/. ooo/.", make_events_vec(
            dur, 1.0 / 2.0, isRest, true, X, dur, 1.0 / 4.0, isRest, true, X,
            dur, 1.0 / 8.0, isRest, true, X, dur, 1.0 / 16.0, isRest, true, X,
            dur, 1.0 / 32.0, isRest, true, X, dur, 3.0 / 4.0, isRest, true, X,
            dur, 3.0 / 8.0, isRest, true, X, dur, 3.0 / 16.0, isRest, true, X
            ));
    }

    SECTION("fancy_beats") {
        run_and_expect(L".] .]]. ]. .)__ .)__. ]__.", make_events_vec(
            dur, 1.0 / 2.0, X, dur, 3.0 / 8.0, X, 
            dur, 3.0 / 4.0, X, dur, 1.0, X,
            dur, 1.5, X, dur, 3.0 / 4.0, X
        ));
    }
    
    // todo: port more from sanity.sc
}


TEST_CASE("Assignments", "[sanity]") {

    MakeEventSep X;
    SkoarString a = L"a";
    SkoarString b = L"b";
    SkoarString c = L"c";

    SkoarString tony = L"tony";
    SkoarString socrates = L"socrates";
    SkoarString qux = L"qux";
    SkoarString yay = L"yay";

    SECTION("simple assignments 1") {
        run_and_expect(L"a: 4 ) b: 7.0 ) c: 'yay' )", make_events_vec(
            a, 4, X,
            a, 4, b, 7.0, X,
            a, 4, b, 7.0, c, yay, X
        ));
    }

    SECTION("simple assignments 2") {
        run_and_expect(L"a: 'tony' ) a: false b: false ) b: true c: 2 )", make_events_vec(
            a, tony, X,
            a, false, b, false , X,
            a, false, b, true, c, 2, X
        ));
    }

    SECTION("simple assignments 3") {
        run_and_expect(L"socrates: 4 ) tony: 7.0 ) qux: 'yay' )", make_events_vec(
            socrates, 4, X,
            socrates, 4, tony, 7.0, X,
            socrates, 4, tony, 7.0, qux, yay, X
        ));
    }

}


TEST_CASE("Derefs", "[sanity]") {

    MakeEventSep X;
    SkoarString a = L"a";
    SkoarString b = L"b";
    SkoarString c = L"c";

    SkoarString tony = L"tony";
    SkoarString socrates = L"socrates";
    SkoarString qux = L"qux";
    SkoarString yay = L"yay";

    SkoarString num_impression = L"num_impression";

    SECTION("simple deref 0") {
        run_and_expect(L"a: 4 7 ) !a )", make_events_vec(
            a, 4, num_impression, 7, X,
            a, 4, num_impression, 4, X
        ));
    }
    
    SECTION("simple deref 1") {
        run_and_expect(L"a: 4 ) b: 7.0 ) c: !a )", make_events_vec(
            a, 4, X,
            a, 4, b, 7.0, X,
            a, 4, b, 7.0, c, 4, X
        ));
    }
    
    SECTION("simple deref 2") {
        run_and_expect(L"a: 'tony' ) b: !a a: false )", make_events_vec(
            a, tony, X,
            a, false, b, tony, X
        ));
    }
    
}


TEST_CASE("Skoarpions", "[sanity]") {

    MakeEventSep X;
    SkoarString a = L"a";
    SkoarString b = L"b";
    SkoarString c = L"c";

    SkoarString tony = L"tony";
    SkoarString socrates = L"socrates";
    SkoarString qux = L"qux";
    SkoarString foo = L"foo";
    SkoarString yay = L"yay";

    
    SECTION("define nice") {
        run_and_expect(L"{! !} {! x !! !} {! x<a> !! !} {! x<a:2, b : 3> !! !} {! c# !} foo:2)", make_events_vec(
            foo, 2, X
        ));
    }

    SECTION("define with no whitespace") {
        run_and_expect(L"{!!}{!x!!!}{!x<a>!!!}{!x<a:2,b:3>!!!}{!c#!}foo:2)", make_events_vec(
            foo, 2, X
        ));
    }
 
    SECTION("skoarpion_sigless") {
        run_and_expect(L"foo: 3 {! foo: 2 ) !} )", make_events_vec(
            foo, 3, X
        ));
    }

    /* sort out lists first
    SECTION("skoarpion_scope with args") {
        run_and_expect_d(L"foo: 3 {! x<foo:2> !! ) !} ) !x<7> )", make_events_vec(
            foo, 3, X,
            foo, 7, X,
            foo, 3, X
        ));
    }
    /*
    SECTION("skoarpion_scope with named args") {
        run_and_expect(L"foo: 3 {! x<foo:2> !! ) !} ) !x<foo:7> )", make_events_vec(
            foo, 3, X,
            foo, 7, X,
            foo, 3, X
        ));
    }

    /*
    SECTION("skoarpion_scope with incorrectly named args") {
        run_and_expect(L"foo: 3 {! x<foo:2> !! ) !} ) !x<fee:7> )", make_events_vec(
            foo, 3, X,
            foo, 2, X,
            foo, 3, X
        ));
    }

    /*
    SECTION("skoarpion_scope without args") {
        run_and_expect(L"foo: 3 {! x<foo:2> !! )) !} ) !x )).", make_events_vec(
            foo, 3, X,
            foo, 2, X,
            foo, 3, X
        ));
    }

    SECTION("verbosing") {
        SkoarConsoleLogger SkoarLog;
        SkoarString skoarce(L"foo: 3 {! x<foo:2> !! )) !} ) !x )).");

        Skoar skoar(skoarce, &SkoarLog);

        REQUIRE(skoar.parsedOk);
        auto events = skoar_get_events(&skoar);
        //compare_desires_to_events(desires, events);

    }*/
}

