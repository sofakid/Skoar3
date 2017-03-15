
SkoarpuscleEnvelope : Skoarpuscle {
	var <func;
	var <name;
	var <oEnv;
	var <offset;

	var <debug;
	var <vdebug;

	var <in_ugen;
	
	*new_from_toke {
		| t |
		^super.new.init_toke(t);
	}

	*wrap_env {
		| e |
		^super.new.init_env(e);
	}

	*default_normal {
		| dur = 1 |
		var x = Env.new(#[0,1, 0.7, 0.7, 0.1, 0], #[0.04, 0.06, 0.7, 0.15, 0.5], \sin);
		x.duration = dur;
		^x;
	}

	*default_stacatto {
		| dur = 1 |		
		^Env.new(#[0,1, 0.7, 0.3, 0], #[0.01, 0.09, 0.6, 0.3] * dur, \sin);
	}

	*default_final {
		| dur = 1 |
		var x = Env.new(#[0,1,1,0], #[0.001, 0.998, 0.001], \sin);
		x.duration = dur;
		^x;
	}

	init {
		| k |
		name = k;
		val = {
			| s |
			SkoarpuscleEnvelope.default_normal(s)			
		};
		
		func = {
			| c,f,s,a,p |
			EnvGen.kr(val.value(s), doneAction:2)
		};

		vdebug = "{ | s | SkoarpuscleEnvelope.default_normal(s) }"; 

		debug = " { | c,f,s,a,p | \n EnvGen.kr(" ++ vdebug ++ ".value(s), doneAction:2) \n }";
		in_ugen = 1;
		
	}

	init_toke {
		| t |
		name = t.lexeme[1..].asSymbol;
		val = {
			| s |
			SkoarpuscleEnvelope.default_normal(s)
		};
		
		func = {
			| c,f,s,a,p |
			EnvGen.kr(val.value(s), doneAction:2)
		};

		vdebug = "{ | s | SkoarpuscleEnvelope.default_normal(s) }"; 

		debug = "{ | c,f,s,a,p | EnvGen.kr(" ++ vdebug ++ ".value(s), doneAction:2)}";
		in_ugen = 1;
	}

	init_env {
		| e |
		var levels, times, curves;
		oEnv = e;

		val = {
			| s |
			e
		};

		
		func = {
			| c,f,s,a,p |
			EnvGen.kr(val.value(s), doneAction:2)
		};
		
		vdebug = "{ | s | " ++ e ++ "}"; 

		debug = " {\n| c,f,s,a,p |\n	EnvGen.kr(" ++ vdebug ++ ".value(s), doneAction:2)\n}";

		in_ugen = 1;
		
	}

	init_copy {
		| v, f, d |
		val = v;
		func = f;
		debug = d;
		in_ugen = 1;
	}

	set_in {
		| in |
		in_ugen = in;
	}
	
	add {
		| x |
		var ret = case {x.isKindOf(SkoarpuscleEnvelope)} {
			Env(oEnv.levels ++ x.oEnv.levels,
				oEnv.times ++ x.oEnv.times,
				oEnv.curves ++ x.oEnv.curves,
				offset:oEnv.offset + x.oEnv.offset)
		} {x.isKindOf(SkoarpuscleInt) || x.isKindOf(SkoarpuscleFloat)} {
			Env(oEnv.levels, oEnv.times, oEnv.curves, offset + x.val)
		} {
			nil
		};

		^SkoarpuscleEnvelope.wrap(ret);
	}

	sub {
		| x |
		var ret = case {x.isKindOf(SkoarpuscleInt) || x.isKindOf(SkoarpuscleFloat)} {
			Env(oEnv.levels, oEnv.times, oEnv.curves, offset:offset - x.val)
		} {
			nil
		};

		^SkoarpuscleEnvelope.wrap(ret);
	}

	mul {
		| x |
		var ret = case {x.isKindOf(SkoarpuscleEnvelope)} {
			oEnv.blend(x.val)
		} {x.isKindOf(SkoarpuscleInt) || x.isKindOf(SkoarpuscleFloat)} {
			Env(oEnv.levels * x.val, oEnv.times, oEnv.curves, offset:oEnv.offset)
		} {
			nil
		};

		^SkoarpuscleEnvelope.wrap(ret);
	}

	div {
		| x |
		var ret = case {x.isKindOf(SkoarpuscleInt) || x.isKindOf(SkoarpuscleFloat)} {
			Env(oEnv.levels / x.val, oEnv.times, oEnv.curves, offset:oEnv.offset)
		} {
			nil
		};
		
		^SkoarpuscleEnvelope.wrap(ret);
	}
	
	
	flatten {
		| m |
		^val.value;
	}

	on_enter {
        | m, nav |
		//"ON_ENTER".postln;
		m.fairy.impress(this);
	}

	a {
		| done_action=2 |
		var fn = {
			| c,f,s,a,p |
			EnvGen.ar(val.value(s), doneAction:done_action)
		};
		var d = "{ | c,f,s,a,p | EnvGen.ar("++ vdebug ++".value(s), doneAction::" ++ done_action ++") }";

		^SkoarpuscleUGen.new_with(\EnvGen.asClass, fn, d, \audio);
	}

	k {
		| done_action=2 |
		var fn = {
			| c,f,s,a,p |
			EnvGen.kr(val.value(s), doneAction:done_action)
		};
		var d = "{ | c,f,s,a,p | EnvGen.kr("++ vdebug ++".value(s), doneAction:" ++ done_action ++") }";

		^SkoarpuscleUGen.new_with(\EnvGen.asClass, fn, d, \control);
	}

	mult_a {
		| in |
		var fn = {
			| c,f,s,a,p |
			in.func.(c,f,s,a,p) * EnvGen.ar(val.value(s), doneAction:2)
		};
		var d = in.debug ++ "\n --> { | c,f,s,a,p | in.func.(c,f,s,a,p) * EnvGen.ar("++ vdebug ++".value(s), doneAction:2) }";

		^SkoarpuscleUGen.new_with(\EnvGen.asClass, fn, d, \audio);
	}

	mult_k {
		| in |
		var fn = {
			| c,f,s,a,p |
			in.func.(c,f,s,a,p) * EnvGen.kr(val.value(s), doneAction:2)
		};
		var d = in.debug ++ "\n --> { | c,f,s,a,p | in.func.(c,f,s,a,p) * EnvGen.kr("++ vdebug ++".value(s), doneAction:2) }";

		^SkoarpuscleUGen.new_with(\EnvGen.asClass, fn, d, \control);
	}

	lute_a {
		^this.mult_a(in_ugen);
	}

	lute_k {
		^this.mult_k(in_ugen);
	}
	
	skoar_msg {
		| msg, minstrel |
        var ret = this;
        
		var msg_selector = msg.val;
        var args = msg.get_msg_arr(minstrel);
		//args.postln;

		case {msg_selector == \a} {
			ret = this.a;

		} {msg_selector == \k} {
			ret = this.k;
			
		} {msg_selector == \plot} {
			AppClock.sched(0.1,{oEnv.plot});
		};
		/*{msg_selector == \normalize} {
			var len_x = 1/oEnv.times.sum;
			var a = [];

			// normalize time to 1 second
			oEnv.times.do {
				| x |
				a = a.add(x * len_x);
			};
			oEnv.times = a;
			
			// normalize values to [0,1]
			oEnv.range;
			
			};*/

		//"FIMLORP".postln;
		^minstrel.fairy.impress(ret);
	}
	

}
