#include "testing_util.hpp"

MakeEventSep X;
SkoarString a = L"a";
SkoarString b = L"b";
SkoarString c = L"c";

SkoarString dur = L"dur";
SkoarString isRest = L"isRest";

SkoarString tony = L"tony";
SkoarString socrates = L"socrates";
SkoarString qux = L"qux";
SkoarString foo = L"foo";
SkoarString fee = L"fee";
SkoarString yay = L"yay";
SkoarString amp_ = L"amp";
SkoarString octave = L"octave";
SkoarString num_impression = L"num_impression";

SkoarpusclePtr cat = make_skoarpuscle(nullptr);

TEST_CASE("Beats and Rests", "[sanity]") {

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
    
}


TEST_CASE("Lists", "[sanity]") {

    SECTION("simple list assignment") {
        run_and_expect(L"a: <0, true, 'qux'> )", make_events_vec(
            a, make_listy(0, true, qux), X
        ));
    }

    SECTION("nested list 1") {
        run_and_expect(L"a: <0, true, 'qux', <'socrates', 6, <'yay'>>> )", make_events_vec(
            a, make_listy(0, true, qux, make_listy(socrates, 6, make_listy(yay))), X
        ));
    }

    SECTION ("nested list 2") {
        run_and_expect (L"a: <0, <true, false>, 'qux', <'socrates', 6, <'yay'>>> )", make_events_vec (
            a, make_listy (0, make_listy(true, false), qux, make_listy (socrates, 6, make_listy (yay))), X
        ));
    }

    SECTION ("nested list 3") {
        run_and_expect (L"a: <<0,1>, true, 'qux', <'socrates', 6, <'yay'>>> )", make_events_vec (
            a, make_listy (make_listy(0,1), true, qux, make_listy (socrates, 6, make_listy (yay))), X
        ));
    }

    SECTION("list of expr 1") {
        run_and_expect(L"a: <0 + 2, 3 + 4 + 5, 3.0 + 0.14> )", make_events_vec(
            a, make_listy(2, 12, 3.14), X
        ));
    }

    SECTION("list of deref") {
        run_and_expect(L"b: 6 c: 5 a: <!b, !c> )", make_events_vec(
            a, make_listy(6, 5), X
        ));
    }

    SECTION("list of deref expr 1") {
        run_and_expect(L"b: 6 c: 5 a: <!b + !c> )", make_events_vec(
            a, make_listy(11), X
        ));
    }

    SECTION("list of deref expr 2") {
        run_and_expect(L"b: 6 c: 5 a: <3.5 + !c, !b + 2.4> )", make_events_vec(
            a, make_listy(8.5, 8.4), X
        ));
    }

    SECTION("list of deref expr 3") {
        run_and_expect(L"b: 6 c: 5 d: <!b, !c + 2> a: <!b + !c, !d, <!d>> )", make_events_vec(
            a, make_listy(11, 
                make_listy(6, 7),
                make_listy(
                    make_listy(6, 7)
                )
            ), X
        ));
    }

    SECTION("list as skoarpion arg") {
        // todo
    }
}



TEST_CASE("Assignments", "[sanity]") {

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

TEST_CASE ("Ints Floats and Freqs", "[sanity]") {

    SECTION ("ints and floats") {
        SkoarString point_one_hz (L"0.1Hz");
        run_and_expect (L"a: 400 b: 401.02) a: 0.002 b: 702 ) a: 0.1Hz b: 420.5Hz c: 2600Hz )", make_events_vec (
            a, 400, b, 401.02, X,
            a, 0.002, b, 702, X,

            a, std::make_shared<SkoarpuscleFreq> (point_one_hz),
            b, std::make_shared<SkoarpuscleFreq> (420.5),
            c, std::make_shared<SkoarpuscleFreq> (static_cast<SkoarInt> (2600)), X
        ));
    }
}



TEST_CASE("Derefs", "[sanity]") {

    SECTION("simple deref 0") {
        run_and_expect(L"a: 4 7 ) b: !a )", make_events_vec(
            a, 4, X,
            a, 4, b, 4, X
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
    
    SECTION("define nice") {
        run_and_expect(L"{! !} x: {! !} a: !! a {! !} !! a:2, b : 3{! !} {! c# !} foo:2)", make_events_vec(
            foo, 2, X
        ));
    }

    SECTION("define with no whitespace") {
        run_and_expect(L"{!!}x:{!!}a:!!a{!!}!!a:2,b:3{!!}{!c#!}foo:2)", make_events_vec(
            foo, 2, X
        ));
    }
 
    SECTION("skoarpion_sigless") {
        run_and_expect(L"foo: 3 {! foo: 2 ) !} )", make_events_vec(
            foo, 3, X
        ));
    }

    SECTION ("skoarpion_simple no args") {
        run_and_expect (L"] x: {! ]] ]] !} ) !x )", make_events_vec (
            dur, 0.5, X,
            dur, 1.0, X,
            dur, 0.25, X,
            dur, 0.25, X,
            dur, 1.0, X
        ));
    }

    SECTION ("skoarpion_scope no args defined or supplied") {
        run_and_expect (L"] f: {! foo: 3 ]] ]] !} )) !f ) )", make_events_vec (
            dur, 0.5, X,
            dur, 2.0, X,
            dur, 0.25, foo, 3, X,
            dur, 0.25, foo, 3, X,
            dur, 1.0, X,
            dur, 1.0, X

        ));
    }

    SECTION("skoarpion_scope with args") {
        run_and_expect(L"foo: 3 x:!! foo:2 {! ) !} ) !x<7> )", make_events_vec(
            foo, 3, X,
            foo, 7, X,
            foo, 3, X
        ));
    }
    
    SECTION("skoarpion_scope with named args") {
        run_and_expect(L"foo: 3 f:!! foo:2 {! ) !} ) !f<foo:7> )", make_events_vec(
            foo, 3, X,
            foo, 7, X,
            foo, 3, X
        ));
    }

    
    SECTION("skoarpion_scope with incorrectly named args") {
        run_and_expect(L"foo: 3 f:!! foo:2 {! ) !} ) !f<fee:7> )", make_events_vec(
            foo, 3, X,
            foo, 2, X, // should expect a cthulu here probably..
            foo, 3, X
        ));
    }

    
    SECTION("skoarpion_scope without args") {
        run_and_expect(L"foo: 3 x:!! foo:2 {! )) !} ) !x )).", make_events_vec(
            foo, 3, X,
            foo, 2, X,
            foo, 3, X
        ));
    }

    SECTION ("skoarpion_scope with two args") {
        run_and_expect (L"foo: 3 qux:9 x:!! foo:2, qux:3 {! )) !} ) !x<4,6> )).", make_events_vec (
            foo, 3, qux, 9, dur, 1.0, X,
            foo, 4, qux, 6, X,
            foo, 3, qux, 9, X
        ));
    }

    SECTION ("skoarpion_scope with two args named") {
        run_and_expect (L"foo: 3 qux:9 x:!! foo:2, qux:3 {! )) !} ) !x<foo:4,qux:6> )).", make_events_vec (
            foo, 3, qux, 9, dur, 1.0, X,
            foo, 4, qux, 6, X,
            foo, 3, qux, 9, X
        ));
    }

    SECTION ("skoarpion_scope with two args named backwards") {
        run_and_expect (L"foo: 3 qux:9 x:!! foo:2, qux:3 {! )) !} ) !x<qux:6,foo:4> )).", make_events_vec (
            foo, 3, qux, 9, dur, 1.0, X,
            foo, 4, qux, 6, X,
            foo, 3, qux, 9, X
        ));
    }

    SECTION ("skoarpion_scope with two args named wack") {
        run_and_expect (L"foo: 3 qux:9 x:!! foo:2, qux:3 {! )) !} ) !x<qux:6,4> )).", make_events_vec (
            foo, 3, qux, 9, dur, 1.0, X,
            foo, 4, qux, 6, X,
            foo, 3, qux, 9, X
        ));
    }

    SECTION ("skoarpion_scope with two args named wiggity wack") {
        run_and_expect (L"foo: 3 qux:9 x:!! foo:2, qux:3 {! )) !} ) !x<6,foo:4> )).", make_events_vec (
            foo, 3, qux, 9, dur, 1.0, X,
            foo, 4, qux, 6, X,
            foo, 3, qux, 9, X
        ));
    }

    SECTION ("skoarpion_scope with two args two defaults") {
        run_and_expect (L"foo: 3 qux:9 x:!! foo:2, qux:3 {! )) !} ) !x )).", make_events_vec (
            foo, 3, qux, 9, dur, 1.0, X,
            foo, 2, qux, 3, X,
            foo, 3, qux, 9, X
        ));
    }

    SECTION ("skoarpion_scope with two args first default") {
        run_and_expect (L"foo: 3 qux:9 x:!! foo:2, qux:3 {! )) !} ) !x<qux:5> )).", make_events_vec (
            foo, 3, qux, 9, dur, 1.0, X,
            foo, 2, qux, 5, X,
            foo, 3, qux, 9, X
        ));
    }

    SECTION ("skoarpion_scope with two args second default") {
        run_and_expect (L"foo: 3 qux:9 x: !! foo:2, qux:3 {! )) !} ) !x<4> )).", make_events_vec (
            foo, 3, qux, 9, dur, 1.0, X,
            foo, 4, qux, 3, X,
            foo, 3, qux, 9, X
        ));
    }

}


TEST_CASE("Loops", "[sanity]") {
   
    SECTION("simple loop once 1") {
        run_and_expect(L"{: ) :}", make_events_vec(
            dur, 1.0, X
        ));
    }

    SECTION("simple loop once 2") {
        run_and_expect(L"{: ) :: 1 times :}", make_events_vec(
            dur, 1.0, X
        ));
    }

    SECTION ("simple loop minus times") {
        run_and_expect (L"{: ) :: -7 times :}", make_events_vec (
            X
        ));
    }
    
    /* i'm undecided what i want to do here.. doing through the loop once is correct at the moment.. it's like a do while.. */
    SECTION("simple loop no times") {
        run_and_expect(L"{: ) :: 0 times :}", make_events_vec(
            X
        ));
    }

    SECTION("simple loop no times") {
        run_and_expect(L"{: ) :: =^.^= times :}", make_events_vec(
            X
        ));
    }

    SECTION("simple loop no times") {
        run_and_expect(L"{: ) :: false :}", make_events_vec(
            X
        ));
    }
    
    SECTION("simple loop 2 times") {
        run_and_expect(L"{: ) :: 2 times :}", make_events_vec(
            dur, 1.0, X,
            dur, 1.0, X
        ));
    }

    SECTION("simple loop 3 times") {
        run_and_expect(L"{: ) :: 3 times :}", make_events_vec(
            dur, 1.0, X,
            dur, 1.0, X,
            dur, 1.0, X
        ));
    }

    SECTION("simple loop 7 times") {
        run_and_expect(L"{: ) :: 7 times :}", make_events_vec(
            dur, 1.0, X,
            dur, 1.0, X,
            dur, 1.0, X,
            dur, 1.0, X,
            dur, 1.0, X,
            dur, 1.0, X,
            dur, 1.0, X
        ));
    }

    SECTION("foreach") {
        run_and_expect(L"<0, 1, 2.5, true, 'yay'>.{: a: $ ) :}", make_events_vec(
            a, 0,    dur, 1.0, X,
            a, 1,    dur, 1.0, X,
            a, 2.5,  dur, 1.0, X,
            a, true, dur, 1.0, X,
            a, yay,  dur, 1.0, X
        ));
    }

    SECTION("foreach expr") {
        run_and_expect(L"<0 + 2, 1 + 3.0>.{: a: $ ) :}", make_events_vec(
            a, 2, dur, 1.0, X,
            a, 4.0, dur, 1.0, X
        ));
    }

    SECTION ("nested loop 1 times in 1 times") {
        run_and_expect (L"{: ) {: )) :: 1 times :} :: 1 times :}", make_events_vec (
            dur, 1.0, X,
            dur, 2.0, X
        ));

    }

    SECTION ("nested loop 2 times in 1 times") {
        run_and_expect (L"{: ) {: )) :: 2 times :} :: 1 times :}", make_events_vec (
            dur, 1.0, X,
            dur, 2.0, X,
            dur, 2.0, X
        ));

    }

    SECTION ("nested loop 1 times in 2 times") {
        run_and_expect (L"{: ) {: )) :: 1 times :} :: 2 times :}", make_events_vec (
            dur, 1.0, X,
            dur, 2.0, X,
            dur, 1.0, X,
            dur, 2.0, X
        ));

    }

    SECTION ("nested loop 2 times in 2 times") {
        run_and_expect (L"{: ) {: )) :: 2 times :} :: 2 times :}", make_events_vec (
            dur, 1.0, X,
            dur, 2.0, X,
            dur, 2.0, X,

            dur, 1.0, X,
            dur, 2.0, X,
            dur, 2.0, X
        ));

    }

    SECTION ("nested loop 2 times in 7 times") {
        run_and_expect (L"{: ) {: )) :: 2 times :} :: 7 times :}", make_events_vec (
            dur, 1.0, X,
            dur, 2.0, X,
            dur, 2.0, X,

            dur, 1.0, X,
            dur, 2.0, X,
            dur, 2.0, X,

            dur, 1.0, X,
            dur, 2.0, X,
            dur, 2.0, X,

            dur, 1.0, X,
            dur, 2.0, X,
            dur, 2.0, X,

            dur, 1.0, X,
            dur, 2.0, X,
            dur, 2.0, X,

            dur, 1.0, X,
            dur, 2.0, X,
            dur, 2.0, X,

            dur, 1.0, X,
            dur, 2.0, X,
            dur, 2.0, X
        ));

    }
}

/* 

Gotos aren't a priority, and shouldn't break sanity, better tested in skoar. disabling for now, keeping for future reference.

TEST_CASE ("Gotos - colons", "[sanity]") {

    SECTION ("Simple colons") {
        run_and_expect (L") |: )) :|", make_events_vec (
            dur, 1.0, X,
            dur, 2.0, X,
            dur, 2.0, X
        ));
    }

    SECTION ("unbalanced colons - no start") {
        run_and_expect (L") | )) :|", make_events_vec (
            dur, 1.0, X,
            dur, 2.0, X,
            dur, 1.0, X,
            dur, 2.0, X
        ));
    }

    SECTION ("unbalanced colons - no end") {
        run_and_expect (L") |: )) |", make_events_vec (
            dur, 1.0, X,
            dur, 2.0, X
        ));
    }

    SECTION ("nested colons") {
        run_and_expect (L") |: )) |: ))) :| :|", make_events_vec (
            dur, 1.0, X,
            dur, 2.0, X,
            dur, 4.0, X,
            dur, 4.0, X,
            dur, 4.0, X
        ));
    }

}

TEST_CASE ("Gotos - Coda", "[sanity]") {

    SECTION ("coda exists") {
        run_and_expect (L") (+) )) ))) ", make_events_vec (
            dur, 1.0, X,
            dur, 2.0, X,
            dur, 4.0, X
        ));
    }

    SECTION ("coda named exists") {
        run_and_expect (L") (+):derp )) ))) ", make_events_vec (
            dur, 1.0, X,
            dur, 2.0, X,
            dur, 4.0, X
        ));
    }

    SECTION ("coda al coda before") {
        run_and_expect_inf (L") (+) )) al coda ))) ", make_events_vec (
            dur, 1.0, X,
            dur, 2.0, X,
            dur, 2.0, X,
            dur, 4.0, X
        ));
    }

    SECTION ("coda al coda after") {
        run_and_expect_inf (L") )) al coda ))) (+) ] ", make_events_vec (
            dur, 1.0, X,
            dur, 2.0, X,
            dur, 0.5, X
        ));
    }

    SECTION ("coda - named coda, unnamed al coda") {
        run_and_expect_inf (L") (+):derp )) al coda )))", make_events_vec (
            dur, 1.0, X,
            dur, 2.0, X,
            dur, 2.0, X,
            dur, 4.0, X
        ));
    }

    SECTION ("coda - named coda, named al coda") {
        run_and_expect_inf (L") (+):frankenstein )) al coda:frankenstein ))) ", make_events_vec (
            dur, 1.0, X,
            dur, 2.0, X,
            dur, 2.0, X,
            dur, 3.0, X
        ));
    }

    SECTION ("coda - multiple named codas, named al coda, inf loop") {
        run_and_expect_inf (L"(+):foo ) (+):frankenstein )) al coda:frankenstein ))) ", make_events_vec (
            dur, 1.0, X,
            dur, 2.0, X,
            dur, 2.0, X,
            dur, 2.0, X,
            dur, 2.0, X,
            dur, 2.0, X
        ));
    }

    SECTION ("coda - multiple named codas, named al coda one") {
        run_and_expect_inf (L") al coda:frankenstein ))) (+):foo ]] (+):frankenstein )) ", make_events_vec (
            dur, 1.0, X,
            dur, 2.0, X
        ));
    }

    SECTION ("coda - multiple named codas, named al coda two") {
        run_and_expect_inf (L") al coda:foo ))) (+):foo ]] (+):frankenstein )) ", make_events_vec (
            dur, 1.0, X,
            dur, 0.25, X,
            dur, 2.0, X
        ));
    }

    SECTION ("coda - coda in loop") {
        run_and_expect_inf (L") al coda:foo ))) {: ] (+):foo ]] :: 3 times :} (+):frankenstein )) ", make_events_vec (
            dur, 1.0, X,
            dur, 0.25, X,
            dur, 0.5, X,
            dur, 0.25, X,
            dur, 0.5, X,
            dur, 0.25, X,
            dur, 2.0, X
        ));
    }

    SECTION ("coda - coda in skoarpion - 1") {
        run_and_expect_inf (L") al coda:socrates ))) !! foo:3, qux:2 {! ] (+):socrates ]] !} (+):frankenstein )) ", make_events_vec (
            dur, 1.0, X,
            dur, 0.25, foo, 3, qux, 2, X,
            dur, 2.0, X
        ));
    }

    SECTION ("coda - coda in skoarpion - 2") {
        run_and_expect_inf (L") al coda:foo ))) !! foo:3, qux:2 {! ] (+):foo ]] !} (+):frankenstein )) ", make_events_vec (
            dur, 1.0, X,
            dur, 0.25, foo, 3, qux, 2, X,
            dur, 2.0, X
        ));
    }

    SECTION ("coda - coda in conditional - when true") {
        run_and_expect_inf (L") al coda:foo ))) {? true ?? ] (+):foo ]] ?} (+):frankenstein )) ", make_events_vec (
            dur, 1.0, X,
            dur, 0.25, foo, 3, qux, 2, X,
            dur, 2.0, X
        ));
    }

    SECTION ("coda - coda in conditional - when false") {
        run_and_expect_inf (L") al coda:foo ))) {? false ?? ] (+):foo ]] ?} )) ", make_events_vec (
            dur, 1.0, X,
            dur, 0.25, foo, 3, qux, 2, X,
            dur, 2.0, X
        ));
    }

}
*/

TEST_CASE("Fairy", "[sanity]") {
  
    SECTION("literal fairy with simple skoarpion") {
        run_and_expect(L"foo: $ ) x: {! foo: 2 )) 7 !} ). 3 !x foo: $ )))", make_events_vec(
            foo, cat, dur, 1.0, X,
            foo, cat, dur, 1.5, X,
            foo, 2, dur, 2.0, X,
            foo, 7, dur, 4.0, X
        ));
    }

}

TEST_CASE ("Octaves", "[sanity]") {

    SECTION ("octave tails") {
        run_and_expect (L"0 ) ~o ) ~~o ) o~ ) o~ ) o~~~ ) o~~ ) o~ ) o~~~ ) ~~~~~o )", make_events_vec (
            octave, 5, X,
            octave, 6, X,
            octave, 8, X,
            octave, 7, X,
            octave, 6, X,
            octave, 3, X,
            octave, 1, X,
            octave, 0, X,
            octave, 0, X,
            octave, 5, X
        ));
    }

}

TEST_CASE("conditionals", "[sanity]") {
    

    SECTION("if true") {
        run_and_expect(L" a: 9 {? true ?? a: 7 ?} )))", make_events_vec(
            a, 7, X
        ));
    }

    SECTION("if false") {
        run_and_expect(L" a: 9 {? false ?? a: 7 ?} )))", make_events_vec(
            a, 9, X
        ));
    }

    SECTION("if cat") {
        run_and_expect(L" a: 9 {? =^.^= ?? a: 7 ?} )))", make_events_vec(
            a, 9, X
        ));
    }

    SECTION("ifelse true") {
        run_and_expect(L"{? true ?? a: 7 ?? a: 8 ?} )))", make_events_vec(
            a, 7, X
        ));
    }

    SECTION("ifelse false") {
        run_and_expect(L"{? false ?? a: 7 ?? a: 8 ?} )))", make_events_vec(
            a, 8, X
        ));
    }

    SECTION("ifelse cat") {
        run_and_expect(L"{? =^.^= ?? a: 7 ?? a: 8 ?} )))", make_events_vec(
            a, 8, X
        ));
    }

}

TEST_CASE ("cats", "[sanity]") {

    SECTION ("list_of_cats") {
        run_and_expect (L"foo: <=^.^=,=^.^=> )", make_events_vec (
            foo, make_listy (nullptr, nullptr), X
        ));
    }

    SECTION ("cats_are_cats") {
        run_and_expect (L"foo: {? =^.^= == =^.^= ?? 3 ?? 2 ?} )", make_events_vec (
            foo, 3, X
        ));
    }

    SECTION ("cats_are_false") {
        run_and_expect (L"foo: {? =^.^= ?? 3 ?? 2 ?} )", make_events_vec (
            foo, 2, X
        ));
    }

    SECTION ("cats_nonexistant_variable") {
        run_and_expect (L"foo: {? !x == =^.^= ?? 3 ?? 2 ?} )", make_events_vec (
            foo, 3, X
        ));
    }

    SECTION ("cats_nonexistant_variable_two") {
        run_and_expect (L"foo: {? !x ?? 3 ?? 2 ?} )", make_events_vec (
            foo, 2, X
        ));
    }

    SECTION ("cats_missing_args") {
        run_and_expect (L"bar: !! x {! {? !x ?? 3 ?? 2 ?} !} foo: !bar )", make_events_vec (
            foo, 2, X
        ));
    }
                                                                                             
}
