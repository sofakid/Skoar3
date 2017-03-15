var qrt = (\dur:1);
var eth = (\dur:1/2);
var sxt = (\dur:1/4);

SkoarTestRunner((

	skoarpion_skeletons: [
        "
{! !}
{! x !! !}
{! x<a> !! !}
{! <a> !! !}
{! x<a:2,b:3> !! !}
{! c# !}

foo:2 )",
        [(\foo:2)]
    ],
	
	skoarpion_sigless: [
        "foo: 3 {! foo: 2 !} )",
        [(\foo:3)]
    ],

	skoarpion_scope: [
        "foo: 3 {! x<foo:2> !! ) !} ) !x ) !x<7> )",
        [(\foo:3), (\foo:2), (\foo:3), (\foo:7), (\foo:3)]
    ],

	skoarpion_scope2: [
        "foo: 3 {! x<foo:2> !! ) !} ) !x ) !x<7,5,8> )",
        [(\foo:3), (\foo:2), (\foo:3), (\foo:7), (\foo:3)]
    ],
	
	skoarpion_scope3: [
        "foo: 3 {! x<foo:2> !! ) !} ) !x ) !x<7,5,8> !x<foo:4> )",
        [(\foo:3), (\foo:2), (\foo:3), (\foo:7), (\foo: 4), (\foo:3)]
    ],

	skoarpion_scope4: [
        "foo: 3 {! x<foo:2> !! ) !} ) !x ) !x<7,5,8> )",
        [(\foo:3), (\foo:2), (\foo:3), (\foo:7, \degree:0), (\foo:3)]
    ],

));
