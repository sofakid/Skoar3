SkoarpuscleDuration : Skoarpuscle {
	var <minutes;
	var <seconds;
	
	init {
        | toke |
        var n, s, i;

        s = toke.lexeme;
        n = s.size;
        i = s.findRegexpAt(".*:", 0)[1];

		minutes = s[0..i].asInteger;
		seconds = s[i..n].asFloat;

		val = (minutes * 60) + seconds;

		//("DURATION :: " ++ minutes ++ ":" ++ seconds).postln; 
    }

	on_enter {
		| m, nav |
		m.fairy.impress(this);
	}
}

SkoarpuscleExactBeat : Skoarpuscle {

	init {
		| toke |
		impressionable = false;
	}

	on_enter {
		| m, nav |

		m.fairy.push_noating;
		m.fairy.push;
		
	}
		
	after {
		| m, nav |
		var dur = m.fairy.impression.flatten_forgetfully(m);
        var noat;
        var e;

		m.fairy.pop;
		m.fairy.pop_noating;
		
		noat = m.fairy.noat.asNoat;

        noat.execute(m);

        // create an event with everything we've collected up until now
        e = m.koar.event(m);

		e[\dur] = dur * e[\tempo];
		m.fairy.consider(e);
        
    }

}

SkoarpuscleExactRest : Skoarpuscle {

	init {
		| toke |
		impressionable = false;
	}

	on_enter {
		| m, nav |
		
		m.fairy.push_noating;
		m.fairy.push;
		
	}
	
	after {
        | m, nav |
		var dur = m.fairy.impression.flatten(m);
		var e;

		m.fairy.pop_noating;
		m.fairy.pop;
        // create an event with everything we've collected up until now
        e = m.koar.event(m);

        e[\dur] = dur * e[\tempo]; 
		e[\isRest] = true;

		m.fairy.consider(e);
        
	}
}

SkoarpuscleBeat : Skoarpuscle {

    var <s;
    var <is_staccato;
    var <has_tie;
    var <is_grace;
	var <>is_exact;
	
    *beat_short {
        | s, n |
        var is_dotted = s.endsWith(".");
        var x = 0.0;

        if (is_dotted == true) {
            n = n - 1;
        };

        x = 2 ** (-1 * n);

        if (is_dotted == true) {
            x = x * 1.5;
        };
        ^x;
    }

    *beat_long {
        | s, n |
        var is_dotted = s.endsWith(".");
        var x = 0.0;

        if (is_dotted == true) {
            n = n - 1;
        };

        x = 2 ** (n - 1);

        if (is_dotted == true) {
            x = x * 1.5;
        };
        ^x;
    }


    init {
        | toke |
        var n;
        s = toke.lexeme;
        n = s.size;
	
		impressionable = false;		
		
        is_staccato = if (s.beginsWith(".")) {
                          n = n - 1;
                          true
                      } {
                          false
                      };

        case {s.contains("__")} {
            has_tie = true;
            is_grace = false;
            n = n - 2;
        } {s.contains("_")} {
            is_grace = true;
            has_tie = false;
            n = n - 1;
        };

        val = if (toke.isKindOf(Toke_Eighths)) {
            SkoarpuscleBeat.beat_short(s, n);
        } {
            SkoarpuscleBeat.beat_long(s, n);
        };

    }

    on_enter_sometimes {
        | m, nav |
        var noat = m.fairy.noat.asNoat;
        var e;

        noat.execute(m);
		
        // create an event with everything we've collected up until now
        e = m.koar.event(m);

		e[\dur] = val;

		m.fairy.consider(e);
    }

}

SkoarpuscleRest : SkoarpuscleBeat {

    init {
        | toke |
        var n;

        s = toke.lexeme;
        n = s.size;

        val = if (toke.isKindOf(Toke_Quavers)) {
            // size -1 for the / (we just count the o's)
            SkoarpuscleBeat.beat_short(s, n - 1)
        } {
            SkoarpuscleBeat.beat_long(s, n)
        };

    }

    on_enter_sometimes {
        | m, nav |
		var noat = m.fairy.noat.asNoat;
        var e;
		
        noat.execute(m);
        // create an event with everything we've collected up until now
        e = m.koar.event(m);

        e[\dur] = val;
		e[\isRest] = true;

		m.fairy.consider(e);
     
    }

}
