SkoarTrollFood  {
	var val;

	*new {
		| v |
		^super.new.init(v);
	}

	init {
		| v |
		//("Troll Food :: init :: " ++ v).postln;
		val = v;
	}

	asString { ^val.asString }
		
	eat {("Troll doesn't know how to eat this. " ++ this).postln}

	*wrap { 
        | x |
		//("Troll Food :: wrapping :: " ++ x).postln;

        case {x.isKindOf(Symbol)} {
            ^SkoarTrollFood_Synth.new(x);

		} {x.isKindOf(SkoarpuscleRoutine)} {
			^SkoarTrollFood_Routine.new(x);

		} {x.isKindOf(SkoarpuscleSample)} {
            ^SkoarTrollFood_Sample(x);
		};

		^nil;
	}
		
}

SkoarTrollFood_Synth : SkoarTrollFood {

	init {
		| x |
		val = x;
		//("Troll Food :: Synth :: " ++ x.name).postln;
	}
	
	asString { ^"Troll Food :: Synth :: " ++ val }
	
	eat {
		SynthDef.removeAt(val);
	}
}

SkoarTrollFood_Routine : SkoarTrollFood {

	init {
		| x |
		val = x;
		//("Troll Food :: Routine :: " ++ x).postln;
	}

	asString { ^"Troll Food :: Routine :: " ++ val }

	eat {
		val.val.stop;
	}
}

SkoarTrollFood_Sample : SkoarTrollFood {

	init {
		| x |
		val = x;
		//("Troll Food :: Sample :: " ++ x).postln;
	}

	asString { ^"Troll Food :: Sample :: " ++ val }

	eat {
		val.buffer.free;
	}
}

Skoarsfjord {

	var <troll;
	var beach;
	var beach_access;

	*new {
		| skoar |
		^super.new.init(skoar);
	}

	init {
		| skoar |
		troll = SkoarTroll.new(skoar, this);
		beach = [];
		beach_access = Semaphore.new(1);
	}

	// leave food on the beach for the troll.
	leave_on_beach {
		| x |
		var food;
		//("Skoarsfjord :: leave_on_beach :: " ++ x).postln;
		beach_access.wait;
		if (x.isKindOf(SequenceableCollection)) {
			x.do {
				| y |
				//("Skoarsfjord :: leave_on_beach :: " ++ x ++ ".do :: " ++ y).postln;
				food = SkoarTrollFood.wrap(y);
				beach = beach.add(food);
			};
		} {
			food = SkoarTrollFood.wrap(x);
			beach = beach.add(food);
		};
		//("Skoarsfjord :: leave_on_beach :: signalling").postln;
		beach_access.signal;
	}

	// give food to the troll right now
	feed_troll {
		| skoarpuscle |
		troll.eat(skoarpuscle);
	}

	// periodically the troll strolls the beach.
	troll_stroll {
		beach_access.wait;
		beach.do {
			| food |
			troll.eat(food);
		};
		beach = [];
		beach_access.signal;
	}
	
	
}

SkoarTroll {

	var  home;
	var  skoar;
	var  event_stream;
	var >needed;
	
	eat {
		| food |
		if (food.isKindOf(SkoarTrollFood)) {
			//("Troll :: found food :: " ++ food).postln;
			food.eat;
		};
	}

	*new {
		| skr, home |
		^super.new.init(skr, home);
	}
	
	init {
        | skr, home |
        var skoarpion;

		//("Troll :: spawned").postln;
		
		skoar = skr;
        
		//("Troll :: home :: " ++ home).postln;
		
        event_stream = Routine({
            //("Troll :: rise").postln;
            while {skoar.running > 1} {
				//("Troll :: take a stroll").postln;
				home.troll_stroll;
				(\dur: 2 + 3.0.rand, \isRest:true, \isTroll:true).yield;

            };

			// one last snack before bed
			home.troll_stroll;

            //("Troll :: sleep").postln;
        });

    }

    nextEvent {
		//("Troll :: nextEvent ").postln;
		^event_stream.next;
    }

    pfunk {
		//("Troll :: pfunk").postln;
        ^Pfunc({this.nextEvent;});
    }
	
}
	