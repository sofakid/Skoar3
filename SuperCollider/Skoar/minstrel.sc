
SkoarMinstrel {

    var  <skoar;
    var  <koar;
    var  <all_voice;
    var  <fairy;

    var   event_stream;

	var <controls;

    *new {
        | nom, k, skr |
        //"new SkoarMinstrel: ".post; nom.postln;
        ^super.new.init(nom, k, skr);
    }

    init {
        | nom, k, skr |
        var skoarpion;

        skoar = skr;
        koar = k;

        // some defaults
        koar[\octave] = 5;
        koar[\tempo] = 1;
        koar[\amp] = 0.2;
		koar[\legato] = 1;
		koar[\stretch] = 1;

		koar[\num_impression] = SkoarpuscleInt.new(0);
		koar[\sym_impression] = \lin;
		koar[\dyn_impression] = SkoarpuscleCat.new;
		

		controls = SkoarControls(nom);

        fairy = SkoarFairy("$" ++ nom, this); // emacs needs ->"

        all_voice = skr.all_voice;

        skoarpion = skoar.tree.next_skoarpuscle.val;

        event_stream = Routine({
            var running = true;
            var nav_result = nil;

            while {running} {

                nav_result = block {
                    | nav |
                    koar.do_skoarpion(skoarpion, this, nav, nil, nil);
                    nav.(\nav_done);
                };

                switch (nav_result)

                    {\nav_done} { running = false; }
                    {\nav_fine} { running = false; }

                    {\nav_da_capo} {
                        //"Da Capo time.".postln;
                        // do nothing, will enter skoarpion again
                    }

                    {\nav_colon} {
                        // do nothing, will enter skoarpion again
                    }

                    {
                        SkoarError("Unhandled nav: " ++ nav_result).throw;
                    };

            };

            //("Minstrel " ++ koar.name ++ " done.").postln;
			if (fairy.lute.notNil) {
				fairy.lute.flush_everything;
			};
			
			skoar.one_less_running;
        });

    }

    nextEvent {
        ^event_stream.next;
    }

    pfunk {
        ^Pfunc({this.nextEvent;});
    }
	
    reset_colons {
		fairy.forget_that_you_have_seen(SkoarpuscleBars);
        koar.state_put(\colons_burned, Dictionary.new;);
    }

}

// ----------------------------------
// Skoarchestra - A band of minstrels
// ----------------------------------
Skoarchestra {

    var minstrels;
	var troll;

    *new {
        | skoar |
        ^super.new.init(skoar);
    }

    init {
        | skoar |
        minstrels = List.new;

        if (skoar.voices.size == 1) {
            minstrels.add(SkoarMinstrel.new(\all, skoar.all_voice, skoar));
        } {
            skoar.voices.do {
                | v |
                if (v != skoar.all_voice) {
                    minstrels.add(SkoarMinstrel.new(v.name, v, skoar));
                };
            };
        };
		
		minstrels.add(skoar.skoarsfjord.troll);
		skoar.running = minstrels.size;
    }

    eventStream {
        var funkStreams = List.new;

        minstrels.do {
            | m |
            funkStreams.add(m.pfunk);
        };

        ^Ppar.new(funkStreams).asStream;
    }

    pfunk {
        var x = this.eventStream;

        ^Pfunc({x.next;});
    }

}
