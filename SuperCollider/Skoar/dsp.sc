

SkoarControls {

	var voice;
	var <amp_bus;
	var <freq_bus;
	var <sustain_bus;
	var <group;

	*new {
		| v |
		^super.new.init(v);
	}

	init {
		| v |
		voice = v;
		amp_bus = Bus.control;
		amp_bus.set(0.2);

		freq_bus = Bus.control;
		freq_bus.set(880);

		sustain_bus = Bus.control;
		sustain_bus.set(1);
		
		//{amp_bus.kr.poll}.play;
		
	}

	set_amp {
		| offs |
		//amp_bus.set(a);
		var e = Env.new([0, offs], [0.4], \lin);
		{ Out.kr(amp_bus, EnvGen.kr(e, doneAction:2)) }.play;
	}
	
	apply_env {
		| e |
		{ Out.kr(amp_bus, EnvGen.kr(e, doneAction:2)) }.play;
	}
	
}

SkoarpuscleUGen : Skoarpuscle {

	var <klass;
	var <ugen;
	var <name;
	var <>func;
	var <rate;
	var <in_ugen;
	var <>args;


	var <>debug;

	*new_raw {
		| u |
		super.new.init_raw(u);
	}

	*new_copy {
		| o |
		^super.new.init_copy(o);
	}
	
	*new_with {
		| k, f, d, r |
		//("SKRP_UGen :: new with :: " ++ d ).postln;
		^super.new.init_with(k, f, d, r);
	}

	*new_copy_with {
		| o, f, d |
		^super.new.init_copy_with(o, f, d);
	}

	*new_from_toke {
		| t, rate |
		^super.new.init_toke(t, rate);
	}

	*new_passthru {
		| in |
		^super.new.init_passthru(in);
	}

	init_passthru {
		| in |
		var that = this;
		val = \passthru;
		klass = nil;
		in_ugen = in;
		
		func = {
			|c,f,s,a,p|
			that.in_ugen.func.(c,f,s,a,p)
		};
		debug = "{ |c,f,s,a,p| in.func(c,f,s,a,p) }";

		rate = \audio;
		
	}
		
		
	init_raw {
		| u |
		var rat = u.defaultMsg;
		var msg = [rat] ++ u.inputs;
		//"==============".postln;
		//"SUgen.init_raw".postln;
		//"==============".postln;

		rate = u.rate;
		val = u.asString;

		klass = u.class;
		func = {
			|c,f,s,a,p|
			klass.performMsg([rat])
		};
		
		//val.postln;

		debug = "{ |c,f,s,a,p| " ++ val ++ ".performMsg([" ++ rat ++"])}}";
	}

	init_toke {
		| t, r |
		var rat;
		//"SUgen.init_toke".postln;
		
		val = t;
		klass = val.asClass;
		rate = r;
		
		rat = this.defaultMsg;
		
		func = {
			|c,f,s,a,p|
			klass.performMsg([rat])
		};

		debug = "{ |c,f,s,a,p| " ++ val ++ ".performMsg([" ++ rat ++ "]) }";

		//("SUgen.init_toke :: " ++ this).postln;

		if (klass.isNil) {
			SkoarError("Unknown UGen :: " ++ val).throw;
		};
	}
	
	init_copy {
		| o |
		//("SUgen.init_copy :: " ++ o).postln;
		klass = o.klass;
		val = o.val;
		func = o.func;

		in_ugen = o.in_ugen;
		if (in_ugen.notNil) {
			debug = in_ugen.debug ++ "\n --> " ++ o.debug;
		} {
			debug = o.debug;
		};
		
		rate = o.rate;

		args = o.args;
		
	}

	init_copy_with {
		| o, f, d |
		//("SUgen.init_copy_with :: " ++ d).postln;
		
		klass = o.klass;
		val = o.val;
		func = f;
		debug = d;
		rate = o.rate;
	}

	init_with {
		| k, f, d, r |
		//("SUgen.init_with :: " ++ k ++ " :: " ++ r ++ " :: " ++ d).postln;
		
		klass = k;
		val = k.asClass;
		func = f;
		debug = d;
		rate = r;
	}
	
	asString {
		^("v: " ++ val.asString ++  " :: k: " ++ klass ++ " :: r: " ++ rate ++ " :: f:" ++ func ++ " :: d: " ++ debug)
	}

	list_names {
		var s = if (in_ugen.notNil) {
			(in_ugen.list_names ++ [val])
		} {
			[val]
		};
		("list names :: " ++ s).postln;
		^s
	}

	list_details {
		var s = if (in_ugen.notNil) {
			(in_ugen.list_details ++ [this.details])
		} {
			[this.details]
		};
		//("list names :: " ++ s).postln;
		^s
	}

	details {
		var sin = if (in_ugen.isNil) {"=^.^="} {in_ugen.val};
		var sargs = if (args.isNil) {"=^.^="} {args.args};
		^"\n(" ++ "val:'" ++ val ++ "', in_ugen:'" ++ sin++ "', rate:" ++ rate ++ ", args:" ++ sargs ++ ")\n";
	}

	defaultMsg {
		^case {rate == \audio}  {\ar}
	          {rate == \control} {\kr}
		      {rate == \demand}  {\ir};
	}	

	uncache {
		if (args.notNil) {
			args.uncache;
		};
	}
	
	set_in {
		| in |
		in_ugen = in;
		//this.uncache;
	}
	
	add {
		| x |
		var fn = if (x.isKindOf(SkoarpuscleUGen) ||
		             x.isKindOf(SkoarpuscleEnvelope)) {
			{ |c,f,s,a,p| func.(c,f,s,a,p) + x.func.(c,f,s,a,p) }
		} {
			{ |c,f,s,a,p| func.(c,f,s,a,p) + x.val }
		};

		var d = if (x.isKindOf(SkoarpuscleUGen) ||
		            x.isKindOf(SkoarpuscleEnvelope)) {
			"{\n   |c,f,s,a,p| "++debug++".(c,f,s,a,p) + "++ x.debug++".(c,f,s,a,p)\n}"
		} {
			"{\n   |c,f,s,a,p| "++debug++".(c,f,s,a,p) + "++ x.val ++"\n}"
		};

		^SkoarpuscleUGen.new_copy_with(this, fn, d);
	}

	sub {
		| x |
		var fn = if (x.isKindOf(SkoarpuscleUGen) ||
		             x.isKindOf(SkoarpuscleEnvelope)) {
			{ |c,f,s,a,p| func.(c,f,s,a,p) - x.func.value(c,f,s,a,p) }
		} {
			{ |c,f,s,a,p| func.(c,f,s,a,p) - x.val }
		};

		var d = if (x.isKindOf(SkoarpuscleUGen) ||
		            x.isKindOf(SkoarpuscleEnvelope)) {
			"{\n   |c,f,s,a,p|"++debug++".(c,f,s,a,p) - "++ x.debug++".(c,f,s,a,p)\n}"
		} {
			"{\n   |c,f,s,a,p| "++debug++".(c,f,s,a,p) - "++ x.val ++"\n}"
		};

		^SkoarpuscleUGen.new_copy_with(this, fn, d);
	}

	mul {
		| x |
		var fn = if (x.isKindOf(SkoarpuscleUGen) ||
		             x.isKindOf(SkoarpuscleEnvelope)) {
			{ |c,f,s,a,p| func.(c,f,s,a,p) * x.func.(c,f,s,a,p) }
		} {
			{ |c,f,s,a,p| func.(c,f,s,a,p) * x.val }
		};

		var d = if (x.isKindOf(SkoarpuscleUGen) ||
		            x.isKindOf(SkoarpuscleEnvelope)) {
			"{\n   |c,f,s,a,p| "++debug++".(c,f,s,a,p) * "++ x.debug++".(c,f,s,a,p)\n}"
		} {
			"{\n   |c,f,s,a,p|"++debug++".(c,f,s,a,p) * "++ x.val ++"\n}"
		};
("mul :: " ++ x).postln;
		^SkoarpuscleUGen.new_copy_with(this, fn, d);
	}

	div {
		| x |
		var fn = if (x.isKindOf(SkoarpuscleUGen) ||
		             x.isKindOf(SkoarpuscleEnvelope)) {
			{ |c,f,s,a,p| func.(c,f,s,a,p) / x.func.(c,f,s,a,p) }
		} {
			{ |c,f,s,a,p| func.(c,f,s,a,p) / x.val }
		};
		
		var d = if (x.isKindOf(SkoarpuscleUGen) ||
		            x.isKindOf(SkoarpuscleEnvelope)) {
			"{\n   |c,f,s,a,p| "++debug++".(c,f,s,a,p) / "++ x.debug++".(c,f,s,a,p)\n}"
		} {
			"{\n   |c,f,s,a,p| "++debug++".(c,f,s,a,p) / "++ x.val ++"\n}"
		};

		^SkoarpuscleUGen.new_copy_with(this, fn, d);
	}
	
	flatten {
		| m |
		^func;
	}

	on_enter {
        | m, nav |
		//"UGEN ON_ENTER".postln;
	}

	// this is like the skoar_msg one, but has no minstrel, for simple,
	// non-skoarpuscular use (Lute)
	make_new_with_args {
		| sel, supplied |
        var arg_spec, arg_prot;
		
		var meth = klass.class.findRespondingMethodFor(sel);

		var out = SkoarpuscleUGen.new_copy(this);
		var args_skoarpuscle;
		
		//("MAKE_NEW :: sel: " ++ sel ++ " klass:" ++ klass ++ " meth:" ++ meth).postln;
		
		if (meth.notNil) {
			args_skoarpuscle = SkoarpuscleUGenArgs.new_two(sel, out);
			args_skoarpuscle.msg_selector = sel;
			arg_spec = meth.argNames.drop(1);
			arg_prot = meth.prototypeFrame.drop(1);

			//("MAKE_NEW :: supplied: "++ supplied ++" ::  arg_spec:" ++ arg_spec ++ " :: arg_prot:" ++ arg_prot).postln;
			args_skoarpuscle.load_args_simple(supplied, arg_spec, arg_prot);

			out.args = args_skoarpuscle;
			
			out.func = {
				|c,f,s,a,p|
				klass.performMsg(out.args.get_final_args(c,f,s,a,p))
			};
			out.debug = "{ |c,f,s,a,p| " ++ val ++ ".performMsg(args_skoarpuscle.get_final_args(c,f,s,a,p) }";
			
		} {
			out.func = {
				|c,f,s,a,p|
				klass.performMsg([sel])
			};
			out.debug = "{ |c,f,s,a,p| " ++ val ++ ".performMsg([" ++ sel ++ "]) }";

		};
		
		//("ugen msg created new ugen:: " ++ out).postln;
		^out;
	}
	
	// here's where we make new ones in skoar
	skoar_msg {
		| msg, minstrel |
        var sel = msg.val;
        var arg_spec, arg_prot;
		
		var meth = klass.class.findRespondingMethodFor(sel);
		var args_skoarpuscle;

		var out = SkoarpuscleUGen.new_copy(this);

		//("sel: " ++ sel ++ " klass:" ++ klass ++ " msg:" ++ msg ++ " meth:" ++ meth).postln;
		
		if (meth.notNil) {
			args_skoarpuscle = SkoarpuscleUGenArgs.new_two(sel, out);
			out.args = args_skoarpuscle;
			
			arg_spec = meth.argNames.drop(1);
			arg_prot = meth.prototypeFrame.drop(1);

			args_skoarpuscle.load_args(minstrel, msg, arg_spec, arg_prot);
			
			out.func = {
				|c,f,s,a,p|
				klass.performMsg(out.args.get_final_args(c,f,s,a,p))
			};
			out.debug = "{ |c,f,s,a,p| " ++ val ++ ".performMsg((out.args.get_final_args(c,f,s,a,p) }";
			
		} {
			out.func = {
				|c,f,s,a,p|
				klass.performMsg([sel])
			};
			out.debug = "{ |c,f,s,a,p| " ++ val ++ ".performMsg([" ++ sel ++ "]) }";

		};
		
		//("ugen msg created new ugen:: " ++ out).postln;
		^minstrel.fairy.impress(out);
	}
		
}

SkoarpuscleUGenWithArgs : SkoarpuscleUGen {
	on_enter {
		| m, nav |
		m.fairy.push_noating;
		m.fairy.push;
	}
}


SkoarpuscleUGenArgs : Skoarpuscle {

	var msg_string;
	var >msg_selector;
	var arg_spec;
	var arg_prot;
	
	var <overrides; // args we have specified, taking precedence

	var <args;      // the final output array of args

	var ugen;

	var args_cache;

	*new_two {
		| msg, u |
		^super.new.init_two(msg, u);
	}
	
	init_two {
		| msg, u |
		overrides = ();
		ugen = u;
		args_cache = nil;
		//("SkoarpuscleUGenArgs::init::ugen :" ++ ugen).postln;
	}

	uncache {
		args_cache = nil;
	}
	
	// this is just when we want to create ugens from sc code, and want to pass args
	// (i.e. from the Lute, for the defaults)
	load_args_simple {
		| supplied, spec, prot |
		var e = ();
		var j = 0;
		var ret = [];
		//("LAS :: arg_prot :"++ arg_prot).postln;

		arg_spec = spec;
		arg_prot = prot;
		
		// get args supplied by skoar
		supplied.do {
			| x |
			//("LAS :: " ++ x).postln;
			e[j] = x;
			j = j + 1;
		};
		
	
		// apply over defaults
		arg_spec.do {
			| x, i |
			var v = e[x];
			var y;
			
			if (v.notNil) {
				// specified by name
				arg_prot[i] = v;
				overrides[i] = i;
				overrides[x] = i;
				//("LAS :: arg_prot[" ++ i ++ "] = v = " ++ v ++ ";").postln;
			} {
				// specified by position
				y = e[i]; 
				//("LAS :: arg_prot[" ++ i ++ "] = e[i] =" ++ e[i] ++ ";").postln;

				if (y.notNil) {
					arg_prot[i] = y;
					overrides[i] = i;
				};
			};
		};

		//("LAS :: arg_prot ::"++ arg_prot).postln;
		
		args = arg_prot;
	}

	// this is for normal operation
    load_args {
		| m, msg, spec, prot |
		var e = ();
		var j = 0;
		var ret = [];
		var w;
		var msg_args = msg.args;
		msg_string = msg.asString;

		msg_selector = msg.val;
		//("MSG :: load_args :: prot :"++ prot).postln;

		arg_spec = spec;
		arg_prot = prot;
		
		// get args supplied by skoar
		if (msg_args.notNil) {
			msg_args.val.do {
				| x |
				if (x.isKindOf(SkoarpusclePair)) {
					e[x.key.val] = x.val.flatten(m);
					//("MSG :: load_args :: e[" ++ x.key.val ++ "] = e[x.key.val] =" ++ e[x.key.val] ++ ";").postln;
					
				} {
					e[j] = x.flatten(m);
					
					//("MSG :: load_args ::e[" ++ j ++ "] = e[j] =" ++ e[j] ++ ";").postln;
					
				};
				j = j + 1;
			};
		};
	

		// apply over defaults
		arg_spec.do {
			| x, i |
			var v = e[x];
			var y;
			
			if (v.notNil) {
				// specified by name
				arg_prot[i] = v;
				overrides[i] = i;
				overrides[x] = i;
				//("MSG :: load_args :: arg_prot[" ++ i ++ "] = v = " ++ v ++ ";").postln;
			} {
				// specified by position
				y = e[i]; 
				//("MSG :: load_args :: arg_prot[" ++ i ++ "] = e[i] =" ++ e[i] ++ ";").postln;

				if (y.notNil) {
					arg_prot[i] = y;
					overrides[i] = i;
				} {
					// in skoar event? 
					w = m.koar[x];
					if (w.notNil) {
						arg_prot[i] = y;
						// 
					};
				};
			};
		};

		//("MSG :: load_args :: arg_prot:"++ arg_prot).postln;
		
		args = arg_prot;
		args_cache = args;
	}

	get_final_args {
		| controls, freq, sustain, amp, pan |
		var las_get_final_args = 0;
		var prot;

		//if (args_cache.notNil) {
		//	^args_cache
		//};
		
		prot = arg_prot.copy;
		
		//("MSG :: get_args :: " ++ ugen.val).postln; // freq ::" ++ freq ++ " :: sustain ::" ++ sustain).postln;
		arg_spec.do {
			| x, i |
			var v;
			var y;

			//("MSG :: " ++ ugen.val ++ " :: get_args:: x ::"++ x).postln;
			case {x == \freq} {
				/*("MSG :: get_args:: freq :: ___" ++ freq ++
					" :: overrides[\\freq] ::" ++ overrides[\freq]  ++
					" :: overrides[" ++ i ++ "] ::" ++ overrides[i]
					).postln;*/
			
				if (overrides[\freq].isNil and: overrides[i].isNil) {
					//("MSG :: get_args :: not overriding freq, using default.").postln;
					prot[i] = freq;
				};

				if (prot[i] == \freq) {
					prot[i] = freq;
				};
			//} {x == \sustain} {
				//if (overrides[\sustain].isNil and: overrides[i].isNil) {
				//	arg_prot[i] = controls.sustain_bus.kr;
				//};
			} {x == \in} {
				if (overrides[\in].isNil and: overrides[i].isNil) {
					//("MSG::get_args:: overriding @in :: ugen:" ++ugen).postln;
					if (ugen.in_ugen.isNil) {
						SkoarError("ugen fail. @in specified, but no input ugen in path.").throw;
					};
					prot[i] = ugen.in_ugen.func;
					//("MSG::get_args:: overridden prot["++i++"] :: "++ prot[i] ++ " :: " ++  ugen.in_ugen.list_names).postln;
				} {
					// did they specify @in as a placeholder?
					//
					// i.e. uPan2<@in, 0.3> rather than uPan2<pos:0.3>
					//
					//("MSG::get_args:: arg_prot["++i++"] :: "++ arg_prot[i]).postln;
					if (prot[i] == \in) {
						if (ugen.in_ugen.isNil) {
							SkoarError("ugen fail. @in specified, but no input ugen in path.").throw;
						};
						prot[i] = ugen.in_ugen.func;

						//("MSG::get_args:: overridden prot["++i++"] :: "++ prot[i] ++ " :: " ++  ugen.in_ugen.list_names).postln;
					};
				
				};

				//("MSG::get_args:: overrides[\in] :: "++ overrides[\in]).postln;
				//("MSG::get_args:: overrides["++i++"] :: "++ overrides[i]).postln;
			
			} {x == \pan} {
				if (overrides[\pan].isNil and: overrides[i].isNil) {
					//("MSG::get_args:: overriding @in").postln;
					prot[i] = pan;
					//("MSG::get_args:: overridden arg_prot["++i++"] :: "++ arg_prot[i]).postln;
				};

				//("MSG::get_args:: overrides[\pan] :: "++ overrides[\in]).postln;
				//("MSG::get_args:: overrides["++i++"] :: "++ overrides[i]).postln;
			
			} {x == \pos} {
				if (overrides[\pos].isNil and: overrides[i].isNil) {
					//("MSG::get_args:: overriding @in").postln;
					prot[i] = pan;
					//("MSG::get_args:: overridden arg_prot["++i++"] :: "++ arg_prot[i]).postln;
				};

				//("MSG::get_args:: overrides[\pan] :: "++ overrides[\in]).postln;
				//("MSG::get_args:: overrides["++i++"] :: "++ overrides[i]).postln;
			
			};
		};

		//("MSG::get_args:: building final args").postln;
		
		args = Array.newClear(arg_prot.size + 1);
		args[0] = msg_selector;
		this.eval_array(controls, freq, sustain, amp, pan, prot, args, 1);

		args_cache = args;
		//args = [msg_selector] ++ arg_prot;
		//("MSG::get_args:: final args ::"++ args).postln;
		^args;
	}

	eval_array {
		| controls, freq, sustain, amp, pan, src, dst, shift = 0 |
		src.do {
			| x, i |
			//("MSG::eval_array:: x :: " ++ x ++ " :: i :: " ++ i).postln;
			dst[i + shift] = if (x.isKindOf(Function)) {
				x.(controls, freq, sustain, amp, pan)
			} {
				if (x.isKindOf(Array)) {
					var n = x.size;
					n.do {
						| j |
						var z = x[j];
						//("MSG::eval_array:: isArray :: j :: " ++ j).postln;
		
						if (z.isKindOf(Function)) {
							x.slotPut(j, z.(controls, freq, sustain, amp, pan));
						};
					};
				};

				x
			};
		};
	}
	
}


	