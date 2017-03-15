SkoarLute {

	var last_ugen;
	var last_ugen_stack;

	var fairy_level;
	
	var troll_food;
	var skoarsfjord;
	var minstrel;
	var fairy;

	var pref;

	var <strings;
	var <current_string;

	var <synthdef;
	var <synth_name;

	var num_channels;

	*new {
		| f |
		^super.new.init(f);
	}

	init {
		| m |
		minstrel = m;
		skoarsfjord = minstrel.skoar.skoarsfjord;

		pref = "& :: " ++ minstrel.koar.name ++ " :: ";

		last_ugen = nil;
		last_ugen_stack = [];
		
		// we only put stuff on the string when the fairy level is 0.
		// pushing and popping affect it.
		fairy_level = 0;
		
		troll_food = [];
		
		current_string = \0;
		num_channels = 2;
		strings = (
			\0: SkoarLuteString.new(\0, minstrel);
		);
	}

	apply_ugen {
		| string |
		
		if (last_ugen.notNil) {
			string.apply_ugen(last_ugen);
		};
	}
	
	choose_part {
		| part |
		var string = strings[current_string];
		//(pref ++ ":: choose_part :: " ++ part).postln;
		this.apply_ugen(string);
		
		string.choose_part(part);

		last_ugen = nil;
	}
	
	choose_string {
		| name |
		var s;
		var string = strings[current_string];

		this.apply_ugen(string);
		
		//(pref ++ ":: choose_string :: " ++ name).postln;
		if (name.isKindOf(Symbol) == false) {
			name = name.asSymbol;
		};
		
		s = strings[name];

		if (s.isNil) {
			s = SkoarLuteString.new(name, minstrel);
			strings[name] = s;
		};
		
		s.choose_part(\src);
		last_ugen = nil;
		current_string = name;
		
	}

	load_troll_food {
		| s |
		if (s.notNil) {
			troll_food = troll_food.add(s);
		};
	}

	take_troll_food_away {
		if (troll_food.size != 0) {
			//(pref ++ "compile_ugen :: leaving " ++ troll_food ++ " on the beach.").postln;
			skoarsfjord.leave_on_beach(troll_food);
			troll_food = [];
		};	
	}
	
	
	flush_everything {
		//(pref ++ "flush_everything").postln;
		strings.do {
			| x |
			this.load_troll_food(x);
		};
		
		this.take_troll_food_away;
	}

	reset {
		last_ugen = nil;
	}
		
	push {
		last_ugen_stack = last_ugen_stack.add(last_ugen);
		last_ugen = nil;
		
		//(pref ++ "push :: last_ugen_stack :: " ++ last_ugen_stack).postln;
    }

	pop {
		//(pref ++ "pop :: " ++ last_ugen_stack).postln;
		last_ugen = last_ugen_stack.pop;
		
    }

	detail {
		| a |
		var r = ":: ";
		a.do {
			| x |
			r = r ++ x.val ++ " ";
		};
		^(r ++ "::");
	}

	o_strings {
		var r = "(";
		
		strings.do {
			| s |
			r = r ++ "'" ++ s.name ++ "': " ++ s.list_ugens_text ++ ",";
		};
		
		r = r ++ " magic:'=^.^=')";
		^r	
	}
	
	impress {
		| impression |
		var string = strings[current_string];

		//(pref ++ "impressing :: " ++ impression).postln;
		if (impression != last_ugen) {
			//ugen_sequence = ugen_sequence.add(impression);
			impression.set_in(last_ugen);
		};
		
		if (impression.rate == \audio) { 
			last_ugen = impression;
			this.apply_ugen(string);
		};
	}

	compile_ugen {

		this.compile_synthdef;
		/*var string = strings[current_string];

		//(pref ++ "compile?").postln;
		if (last_ugen.rate == \audio) {
			//(pref ++ "yes").postln;
			this.load_troll_food(string);
			this.take_troll_food_away;

			//(pref ++ "applying").postln;
			string.apply_ugen(last_ugen);
			(pref ++ "compiling").postln;
			string.compile_synthdef;

			if (string.synthdef.notNil) {
				minstrel.koar[\instrument] = string.synth_name;
			};
		};*/
		
	}

	compile_synthdef {
		var controls = minstrel.controls;
		var amp_bus = controls.amp_bus;
		
		var n = strings.size;
		//var parts = Array.newClear(n);

		var last_synth = synth_name;
			
		//("COMPILING :: " ++ env.lute_a.debug).postln;
		try {
			
			synthdef = {
				| sustain, pan, freq |
				var amp = amp_bus.kr;
				var outs = Array.newClear(n);
				
				if (sustain.isKindOf(OutputProxy) == false) {
					sustain = 1;
				};

				strings.do {
					| x, i |
					outs.slotPut(i,
						// everything is contained in the last ugen of the lute string
						x.env.lute_a.func.(controls, freq, sustain, amp, pan) * amp;
					);
				};
				
				Mix(outs)
				
			}.asSynthDef();
			
			synthdef.add;
			synth_name = synthdef.asDefName;
			//(synth_name ++ " defined").postln;
			
			//dirty = false;

			minstrel.koar[\instrument] = synth_name;
			
		} {
			| error |
			"!!! Synthdef failed to compile !!!".postln;
			error.errorString.postln;
			error.postProtectedBacktrace;

			SkoarError("Synthdef failed to compile :: Lute String :: " ++ this.debug).throw;
		};
		
		this.load_troll_food(last_synth);
		this.take_troll_food_away;

	}

}

SkoarLuteString {

	var <>src;
	var <>beat_env;
	var <>filter;

	var <>env;
	var env_ugen;
	
	var <>panner;
	var <>safeties;
	var <name;

	var <synthdef;
	var <synth_name;

	var <>part;

	var minstrel;
	
	*new {
		| n, m |
		^super.new.init(n, m);
	}
	
	init {
		| n, m |
		var b;
		name = n;
		minstrel = m;
		
		part = \src;
		
		src = SkoarpuscleUGen.new_from_toke(\SinOsc, \audio).make_new_with_args(\ar, [\freq]);

		b = SkoarpuscleEnvelope.wrap_env(SkoarpuscleEnvelope.default_normal);
		beat_env = SkoarLuteEnvelope.new_wrap_env(src,b);
		
		filter = SkoarpuscleUGen.new_passthru;
		filter.set_in(beat_env.ugen);

		panner = SkoarpuscleUGen.new_from_toke(\Pan2, \audio).make_new_with_args(\ar, [\in]);
		panner.set_in(filter);
		
		safeties = SkoarpuscleLuteSafeties.new_safeties;
		safeties.set_in(panner);
		
		env = SkoarpuscleEnvelope.wrap_env(SkoarpuscleEnvelope.default_final);
		env.set_in(safeties);
		
	}

	choose_part {
		| p |
		case {p == \src} {
			part = p;
			//filter.uncache;
			^src;
			
		} {p == \beat_env} {
			part = p;
			//panner.uncache;
			^beat_env;
			
		} {p == \filter} {
			part = p;
			//panner.uncache;
			^filter;
			
		} {p == \panner} {
			part = p;
			//safeties.uncache;
			^panner;
			
		} {p == \safeties} {
			part = p;
			//env.uncache;
			^safeties;
			
		} {p == \env} {
			part = p;
			^env;
		};

		SkoarError("Choosing a nonexistent Lute String :: " ++ p).throw; 
	}

	
	apply_ugen {
		| ugen |

		if (ugen.isNil) {
			^this
		};

		//(name ++ ":: apply_ugen :: part:" ++ part ++ " :: " ++ ugen.list_details).postln;
		
		case {part == \src} {
			this.set_src(ugen);

		} {part == \beat_env} {
			this.set_beat_env(ugen);
			
		} {part == \filter} {
			this.set_filter(ugen);
			
		} {part == \panner} {
			this.set_panner(ugen);
			
		} {part == \safeties} {
			this.set_safeties(ugen);

		} {part == \env} {
			this.set_env(ugen);
		};
		
	}

	set_src {
		| ugen |
		if (src != ugen) {
			src = ugen;
			src.set_in(nil);
			beat_env.set_in(src);
			filter.set_in(beat_env.ugen);
		};
	}

	set_beat_env {
		| e |
		case {e.isKindOf(SkoarpuscleEnvelope)} {
			beat_env = SkoarLuteEnvelope.new_wrap_env(src, e);
			
		} {e.isKindOf(SkoarpuscleUGen)} {
			// They passed their own ugen, wrap it.
			beat_env = SkoarLuteEnvelope.new_wrap_ugen(src, e);
		};

		filter.set_in(beat_env.ugen);
	}
	
	set_filter {
		| ugen |
		if (filter != ugen) {
			filter = ugen;
			filter.set_in(beat_env.ugen);
			panner.set_in(filter);
		};
	}
	
	set_panner {
		| ugen |
		if (panner != ugen) {
			panner = ugen;
			panner.set_in(filter);
			safeties.set_in(panner);
		};
	}
	
	set_safeties {
		| ugen |
		if (safeties != ugen) {
			safeties = ugen;
			safeties.set_in(panner);
			env.set_in(safeties);
		};
	}

	set_env {
		| e |
		case {e.isKindOf(SkoarpuscleEnvelope)} {
			env = e;
			env.set_in(safeties);
			
		} {e.isKindOf(SkoarpuscleUGen)} {
			// They passed their own ugen, wrap it.
			env = SkoarLuteEnvelope.new_wrap_ugen(safeties, e);
		};
		
	}
	
	entire_seq {
		^[src, beat_env, filter, panner, safeties, env];
	}
		
	compile_synthdef {
		var controls = minstrel.controls;
		var amp_bus = controls.amp_bus;

		//("COMPILING :: " ++ env.lute_a.debug).postln;
		try {
			synthdef = {
				| sustain, pan, freq |
				var amp = amp_bus.kr;
				
				if (sustain.isKindOf(OutputProxy) == false) {
					sustain = 1;
				};

				// everything is contained in the last ugen of the lute string
				//env.lute_a.func.(controls, freq, sustain) * amp;
				env.lute_a.func.(controls, freq, sustain, amp, pan) * amp;
				
				
			}.asSynthDef();
			
			synthdef.add;
			synth_name = synthdef.asDefName;
			//(synth_name ++ " defined").postln;
			
			//dirty = false;
			
		} {
			| error |
			"!!! Synthdef failed to compile !!!".postln;
			error.postProtectedBacktrace;

			SkoarError("Synthdef failed to compile :: Lute String :: " ++ this.debug).throw;
		};
	}

	debug {
		var s = "::\n";
		this.entire_seq.do {
			| x |
			s = s ++ " --> " ++ x.val ++ " :: " ++ x.debug ++ "\n";
		};
		s = s ++ "::";
		^s
	}

	list_ugens_text {
		var s = "[";
		this.list_ugens.do {
			| x |
			s = s ++ x ++ ", ";
		};
		s = s ++ "]";
		^s
	}

	list_ugens {
		^env.in_ugen.list_details
	}
}

SkoarpuscleLute : Skoarpuscle {

    var msg_arr;
	var name;
	var <has_messages;
	
    *new { ^super.new.init; }

	*new_from_toke {
		| toke |
		^super.new.init_from_toke(toke);
	}

	init_from_toke {
		| toke |
		msg_arr = #[];
		val = toke.lexeme;
		has_messages = if (val.size == 2) {true} {false};
		name = "["++ val ++"] ";
		
		//(name ++ ":: init_from_toke :: has_messages:" ++has_messages).postln;
	}
	
    init {
        msg_arr = #[];
		name = "[&] ";
		has_messages = false;
		val = "_&_";
    }

	on_enter {
		| m, nav |
		if (has_messages == false) {
			m.fairy.impress(this);
		} {
			m.fairy.push_noating;
			m.fairy.push;	
		};
	}
	
    flatten {
        | m |
        //var x = m.fairy.lute;
		//^x;
		^this;
    }

    skoar_msg {
        | msg, minstrel |
		var s;
		var lute = minstrel.fairy.lute;
		
		msg_arr = msg.get_msg_arr(minstrel);

		s = msg_arr[0];

		//(name ++ s).postln;
		case {s == \s} {
			lute.choose_part(\src);

		} {s == \b} {
			lute.choose_part(\beat_env);

		} {s == \e} {
			lute.choose_part(\env);

		} {s == \f} {
			lute.choose_part(\filter);

		} {s == \p} {
			lute.choose_part(\panner);

		} {s == \safeties} {
			lute.choose_part(\safeties);

		} {s == \final_env} {
			lute.choose_part(\final_env);

		} {s == \o_strings} {
			^lute.o_strings;
			
		} {s == \p_strings} {
			"\nLute Strings: \n".postln;
			lute.o_strings.postln;
			"\n".postln;
			
		} {s == \string} {
			var x = msg_arr[1];
			
			lute.choose_string(x);
		};
		
        ^this;
    }

    //isNoatworthy { ^true; }

    //asNoat {
        // need a reference to the fairy
    //}
}

SkoarLuteEnvelope {

	var <in_ugen;
	var <ugen;
	var env;
	
	*new_wrap_env {
		| in, e |
		^super.new.init_wrap_env(in, e);
	}

	init_wrap_env {
		| in, e |
		in_ugen = in;
		e.set_in(in);
		env = e;
		ugen = e.lute_a;
	}
	
	*new_wrap_ugen {
		| in, u |
		^super.new.init_wrap_ugen(in, u);
	}

	init_wrap_ugen {
		| in, u |
		in_ugen = in;
		ugen = u;
	}

	lute_a {
		^ugen.mul(in_ugen);
	}

	lute_k {
		^ugen.mul(in_ugen);
	}

	func {
		^ugen.func
	}

	debug {
		^ugen.debug;
	}

	uncache {
		ugen.uncache;
	}

	set_in {
		| in |
		in_ugen = in;
		env.set_in(in);
		ugen = env.lute_a;
		ugen.set_in(in);
		//this.uncache;
	}
		
}

SkoarpuscleLuteSafeties : SkoarpuscleUGen {

	var <>in_ugen;
	var ugen;

	*new_safeties {
		^super.new.init_safeties;
	}

	init_safeties {
		this.init_toke(\LPF, \audio);
		^this.make_new_with_args(\ar, [\in, 22000]);
	}
}
