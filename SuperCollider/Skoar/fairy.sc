SkoarFairy {

    var <name;
    var <minstrel;
    var <noat;
    var <impression;
	var impression_stack;
    
    var magic;
    var listy_stack;
    var magic_stack;
	var i_stack;
	var i;
	var j;
	var compare_stack;
	var boolean_stack;
	var <boolean_impression;

	var <l_value;

	var noating;
	var noating_stack;
	var noatworthy;
	var noatworthy_stack;
	
	
	var times_seen_stack;
	var times_seen;

	var exact;

	var <lute;
	
	var worry_stack;
	var worries;
	var <num_impression;
	var <sym_impression;
	var <dyn_impression;
	

    *new {
        | nom, m |
        //"new SkoarFairy: ".post; nom.postln;
        ^super.new.init(nom, m);
    }

    init {
        | nom, m |
        name = nom;
        minstrel = m;
        impression = nil;
        magic = nil;
        noat = nil;
		noatworthy = false;
        listy_stack = [];
        magic_stack = [];
		i_stack = [];
		i = 0;
		j = 0;
		compare_stack = [];
		boolean_stack = [];
		boolean_impression = false;
		l_value = nil;

		times_seen_stack = [];
		times_seen = IdentityDictionary.new;

		worry_stack = [];
		worries = nil;

		noating = true;
		noating_stack = [];

		lute = SkoarLute(minstrel);
		lute.compile_synthdef;

		this.impress(0);
		
    }
	
	get_top_listy {
        var n = listy_stack.size;
        if (n == 0) {
            ^nil;
        };
        ^listy_stack[n - 1];
    }

    set_top_listy {
        | x |
        var n = listy_stack.size;
        listy_stack[n - 1] = x;
    }

    push_impression {
		impression_stack = impression_stack.add(impression);
		noatworthy_stack = noatworthy_stack.add(noatworthy);
    }											  

    pop_impression {
		noatworthy = noatworthy_stack.pop;
		if (noatworthy == true) {
			this.impress(impression_stack.pop);
		};
    }

	push {
		magic_stack = magic_stack.add(magic);
        magic = nil;
        listy_stack = listy_stack.add([]);
		minstrel.koar.push_state;
        //(name ++ " :: push").postln;

		lute.push;
    }											  

    pop {
		var x;
		lute.pop;
        magic = magic_stack.pop;
        minstrel.koar.pop_state;
		x = listy_stack.pop;
		if (x.notNil and: x != []) {
			//	this.impress(SkoarpuscleCat.new);
			//} {
			this.impress(x);
		};
        //(name ++ " :: pop :: " ++ impression).postln;
	
    }

    next_listy {
        var listy = this.get_top_listy;

        if (listy.notNil) {
            listy = listy.add(impression);
            this.set_top_listy(listy);
        };
		lute.reset;
    }

	// we push_noating when we enter a state where we don't want to
	// noatice noatworthy things.
	// like in arguments, or boolean expressions
	push_noating {
		| n = false |
		name = if (n == true) {"."} {"!"} ++ name;
		//(name ++ ".push noating").postln;
		
		noating_stack = noating_stack.add(noating);
		noating = n;
	}

    pop_noating {
		name = name[1..];
		//(name ++ ".pop noating").postln;
		
		noating = noating_stack.pop;
		//(name ++ ".pop noating :: " ++ noating).postln;
		
		//("$.POP NOATING: " ++ noating).postln;
    }

	push_i {
        i_stack = i_stack.add(i);
    }

    pop_i {
        i = i_stack.pop;
    }

	incr_i {
		i = i + 1;
	}

	push_times_seen {
        times_seen_stack = times_seen_stack.add(times_seen);
		times_seen = IdentityDictionary.new;
    }

    pop_times_seen {
        times_seen = times_seen_stack.pop;
    }

	how_many_times_have_you_seen {
		| thing |

		var times = times_seen[thing];

		if (times.isNil) {
			times_seen[thing] = 1;
			^1;
		};
		
		times = times + 1;
		times_seen[thing] = times;
		^times;	
	}

	forget_that_you_have_seen {
		| skoarpuscleKind | 
		
		times_seen.keysValuesChange {
            | key, value |

            if (key.isKindOf(skoarpuscleKind)) {
				0   
            } {
				value
			}
		};
	}

	push_compare {
        compare_stack = compare_stack.add(l_value);
		l_value = nil;
    }

    pop_compare {
        l_value = compare_stack.pop;
		//"popped l_value:".post; l_value.postln;
    }

	compare_impress {
		| m |
		l_value = this.impression;

		if (l_value.isKindOf(SkoarpuscleFairy))	{
			// we want the impression now
			l_value = m.fairy.impression;
		};
		
		//"l_value from impression: ".post; l_value.postln;
	}

	push_boolean {
        boolean_stack = boolean_stack.add(this.impression);
		this.push_noating;
    }

    pop_boolean {
		boolean_impression = this.impression;
		//(name++".pop_boolean").postln;
        this.impress(boolean_stack.pop);
		this.pop_noating;
    }

	impress_i {
		^this.impress(i);
	}

    impress {
        | x |
		var koar = minstrel.koar;
		
        //(name ++ ".impression: " ++ x.asString).postln;
		
		/*if (x.isKindOf(Array)) {
			Error.new.postProtectedBacktrace;
		};
		*/
		
		if (x.isKindOf(SkoarpuscleFairy)) {
            ^impression;
        };

		if (x.isKindOf(SkoarpusclePair)) {
			//("$..ASSIGN PAIR :: " ++ x.asString).postln; 
			x.assign(minstrel);
		};

        if (x.isKindOf(SkoarpuscleDeref)) {
            x = x.lookup(minstrel);
			//("$..DEREF :: " ++ x.asString).postln;
        };

        if (x.isKindOf(Skoarpuscle)) {
			if (x.impressionable == false) {
				^impression; 
			};
			impression = x;
        } {
			//(name ++ ".impression :: wrapping :: " ++ x).postln;
            impression = Skoarpuscle.wrap(x)
        };

		if (noating == true) {
			if (impression.isNoatworthy == true) {
				//(name ++ ".impression :: NOATWORTHY").postln;
				//impression.dump;
				noat = impression;
				noatworthy = true;
			} {
				noatworthy = false;
			};
		} {
			noatworthy = false;
		};

		koar[\impression] = impression;
		
		case {impression.isKindOf(SkoarpuscleUGen)} {
			lute.impress(impression);
			
		} {impression.isKindOf(SkoarpuscleLute)} {
			//impression = lute.ugen;
			
		} {impression.isKindOf(SkoarpuscleInt) || impression.isKindOf(SkoarpuscleFloat)} {
			//(name ++ ".num_impression = " ++ impression.val).postln;
			koar[\num_impression] = impression;
			num_impression = impression;
			koar[\exact_dur] = impression;

			
		} {impression.isKindOf(SkoarpuscleSymbol)} {
			koar[\sym_impression] = impression;
			sym_impression = impression;

		} {impression.isKindOf(SkoarpuscleDynamic)} {
			koar[\dyn_impression] = impression;
			dyn_impression = impression;
			
		} {impression.isKindOf(SkoarpuscleDuration)} {
			koar[\exact_dur] = impression;
		}; 
		
        ^impression;
    }

	compile_ugen {
		lute.compile_ugen;
	}

	exact_duration {
		//("$.EXACT :: " ++ exact).postln;
		^exact;
	}
		
	//------------------
	// arcane magic
	//----
    charge_arcane_magic {
        | spell |
        var f = magic;

        magic = {
            var x;
            if (f.notNil) {
                //(name ++ ".ARCANE :: alpha").postln;
                f.();
            };
            //(name ++ ".ARCANE :: omega").postln;
            x = spell.();
            if (x.notNil) {
				//(name ++ ".DEEP ARCANE").postln;
                this.impress(x);
            };
        };
    }

    cast_arcane_magic {
		//(name ++ ".CASTING").postln;
        if (magic.notNil) {
            magic.();
            magic = nil;
        };
		//(name ++ ".CASTED").postln;
        ^this.impression;
    }

	consider {
		| e |
		var x;
		
		x = e[\tempo];
		if (x <= 0) {
			x = 1;
		};
		e[\dur_by_tempo] = e[\dur] / x;
		
		//(name++".consider :: " ++ e).postln;
		e.yield;
	}

	consider_amp {
		| skrpe, m |

		if (worries.isNil) {
			if (noating == true) {
				var a = skrpe.amp;
				var offs = a - m.koar[\amp];
				m.controls.amp_bus.set(a);
				m.koar[\amp] = a;
			};
		} {
			dyn_impression = skrpe;
		};
	}
}

SkoarpuscleFairy : Skoarpuscle {
    var msg_arr;

    *new { ^super.new.init; }

    init {
        msg_arr = #[];
    }

    flatten {
        | m |
        var x = m.fairy.impression;

        if (x.isKindOf(Skoarpuscle)) {
            x = x.flatten(m);
        };
		//"Flattening the fairy: ".post; x.postln;
        ^x;
    }

    skoar_msg {
        | msg, minstrel |
		var s;
		msg_arr = msg.get_msg_arr(minstrel);

        //"Fairy got msg: ".post; msg_arr.dump;
		
		s = msg_arr[0];

		if (s == \i) {
			^minstrel.fairy.impress_i;
		};

        ^this;
    }

    //isNoatworthy { ^true; }

    //asNoat {
        // need a reference to the fairy
    //}
}
