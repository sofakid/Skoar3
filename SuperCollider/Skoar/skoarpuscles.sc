// Skoarpuscles are the closest thing we have to "types".
//
// They represent value types, as well as most things that
// can be spoken of as things, like a statement, boolean expression, etc.
//
Skoarpuscle {

    var <>val;
	var <>impressionable;
	var <>county;

    *new { | v | ^super.new.init(v); }
    init { 
		| v |
		//"Skoarpuscle.init".postln;
		val = v;
		impressionable = true;
	}

    on_enter { | m, nav | }

    // override and implement .asNoat;
    isNoatworthy { ^false; }
    asNoat {SkoarError("asNoat called on " ++ this.class.asString ++ ", which is not noatworthy.").throw;}

	// override and implement .asCount;
    isCounty { ^false; }
    asCount {SkoarError("asCount called on " ++ this.class.asString ++ ", which is not county.").throw;}
	isZero { ^(val == 0) }
 	
    flatten { | m | ^val; }
	flatten_forgetfully {
		| m |
		var r;
		
		//m.fairy.push_impression;
		r = this.flatten(m);

		// reimpresses something that might not have been noatworthy 
		//m.fairy.pop_impression;
		
		^r;
	}

    asString {
        var s = super.asString ++ ": " ++ val.asString;
        ^s;
    }

	
    skoar_msg {
        | msg, minstrel |
        var o = msg.get_msg_arr(minstrel);
        var ret = val.performMsg(o);

        ^Skoarpuscle.wrap(ret);
    }

    *wrap {
        | x |
        case {x.isNil} {
            //"wrapping: =^.^=".postln;
			//Error.new.postProtectedBacktrace;
            ^SkoarpuscleCat();

		} {x == false} {
            //"wrapping: False".postln;
            ^SkoarpuscleFalse();

        } {x == true} {
            //"wrapping: True".postln;
            ^SkoarpuscleTrue();

        } {x.isKindOf(Skoarpuscle)} {
            //"already wrapped".postln;
            ^x;

        } {x.isKindOf(Skoarpion)} {
            //"wrapping: skoarpion".postln;
            ^SkoarpuscleSkoarpion(x);

        } {x.isKindOf(Integer)} {
            //("wrapping: int: " ++ x.asString).postln;
            ^SkoarpuscleInt(x);

        } {x.isKindOf(Number)} {
            //"wrapping: float".postln;
            ^SkoarpuscleFloat(x);

        } {x.isKindOf(String)} {
            //"wrapping: str".postln;
            ^SkoarpuscleString(x);

        } {x.isKindOf(Symbol)} {
            //"wrapping: symbol".postln;
            ^SkoarpuscleSymbol(x);

		} {x.isKindOf(UGen)} {
			//"derp".postln;
			^SkoarpuscleUGen.new_raw(x);

		} {x.isKindOf(Env)} {
			^SkoarpuscleEnvelope.wrap_env(x);
			
        } {x.isKindOf(SkoarNoad)} {
			if (x.name == \expr) {
				//"Wrapping expression".postln;
				^SkoarpuscleExpr(x);
			};

			^SkoarpuscleUnknown(x);
			
        } {x.isKindOf(Array)} {
            var a = Array.newClear(x.size);
            var i = -1;
            //"wrapping: array".postln;
            x.do {
                | el |
                i = i + 1;
                a[i] = Skoarpuscle.wrap(el);
            };

            ^SkoarpuscleList(a);
			
        }  {x.isKindOf(Routine)} {
			//"wrapping routine".postln;
            ^SkoarpuscleRoutine(x);
        } {
            ("wrapping: unknown: " ++ x).postln;
            ^SkoarpuscleUnknown(x);
        };

    }
}

SkoarpuscleUnknown : Skoarpuscle {

}

// Cats show up in unexpected places.
SkoarpuscleCat : Skoarpuscle {

	init {
		val = "=^.^=";
		impressionable = true;
	}

    asString {^"=^.^="}

    skoar_msg {}
    flatten {^nil}

	amp {^nil}

	on_enter {
        | m, nav |
		//"=^.^=".postln;
		m.fairy.impress(this);
    }
}

SkoarpuscleFalse : Skoarpuscle {
	
	init {
		val = false;
	}

	asString {^"false"}

    skoar_msg {}
    flatten {^false}

	on_enter {
        | m, nav |
        m.fairy.impress(this);
    }
}

SkoarpuscleTrue : Skoarpuscle {

	init {
		val = true;
	}

	asString {^"true"}

    skoar_msg {}
    flatten {^true}
	
	on_enter {
        | m, nav |
        m.fairy.impress(this);
    }
}

SkoarpuscleInt : Skoarpuscle {

    isNoatworthy { ^true; }

    asNoat {
        ^SkoarNoat_Degree(val.asInteger);
    }

    isCounty { ^true; }

    asCount {
        ^val.asInteger;
    }

    flatten {
        | m |
        ^val.asInteger;
    }

	on_enter {
        | m, nav |
        m.fairy.impress(this);
    }

}

SkoarpuscleFloat : Skoarpuscle {

    isNoatworthy { ^true; }

    asNoat {
        ^SkoarNoat_Degree(val.asFloat);
    }

    flatten {
        | m |
        ^val.asFloat;
    }

	on_enter {
        | m, nav |
        m.fairy.impress(this);
    }

}

SkoarpuscleFreq : Skoarpuscle {

    init {
        | lexeme |
		if (lexeme.isKindOf(String)) {
			val = lexeme[0..lexeme.size-3].asFloat;
		} {
			val = lexeme.asFloat;
		};
	}

    isNoatworthy { ^true; }

    asNoat {
        ^SkoarNoat_Freq(val);
    }

    on_enter {
        | m, nav |
        m.fairy.impress(this);
    }
}


SkoarpuscleString : Skoarpuscle {

    on_enter {
        | m, nav |
        m.fairy.impress(this);
    }

	skoar_msg {
        | msg, minstrel |
        var ret = this;

		var sel = msg.val;

		case {sel == \sample} {
			ret = SkoarpuscleFileSample.new(val);
		} {
			ret = SkoarpuscleCat.new;
		};
		("SKRP_String :: " ++ ret).postln;
		^ret;
    }
	
}

SkoarpuscleSymbolName : Skoarpuscle {
}

SkoarpuscleSymbol : Skoarpuscle {

	var klass;
	var pref;
	
	init {
		| v |

		if (v.isKindOf(Symbol) == false) {
			v = v.asSymbol;
		};
		val = v;
		klass = val.asClass;

		pref = "SKRP_Symbol :: " ++ v ++ " :: ";
	}

    on_enter {
        | m, nav |
        m.fairy.impress(this);
    }

    skoar_msg {
        | msg, minstrel |
        var ret = this;

		var sel = msg.val;
		var arg_spec, arg_prot;

		
		var meth = klass.class.findRespondingMethodFor(sel);
		(pref ++ " klass :: " ++ klass ++ " ::  meth :: " ++ meth).postln;
		if (meth.notNil) {
			var arg_names = meth.argNames;
			if (arg_names.notNil) {
				arg_spec = meth.argNames.drop(1);
				arg_prot = meth.prototypeFrame.drop(1);

				arg_prot = msg.get_args_from_prototype(minstrel, arg_spec, arg_prot);

				(pref ++ val ++ ".performList(" ++ sel ++", " ++ arg_prot ++ ");" ).postln;	
				ret = klass.performList(sel, arg_prot);	
			} {
				(pref ++ val ++ ".performMsg([" ++ sel ++"]);" ).postln;	
				ret = klass.performMsg([sel]);
			};
		};

		^Skoarpuscle.wrap(ret);
    }
}

SkoarpuscleSymbolColon : Skoarpuscle {

	init {
		| lex |
		// lexeme was matched by: [a-zA-Z0-9_][a-zA-Z0-9_]*[ \t]*:(?![:|}])
        var regex = "[a-zA-Z0-9_][a-zA-Z0-9_]*";
        val = lex.findRegexpAt(regex, 0)[0].asSymbol;

		//("SSC :: init :: lex:" ++ lex ++ " val:" ++ val.asString).postln; 
		
		impressionable = true;	
	}

}


SkoarpuscleDeref : Skoarpuscle {

    var msg_arr;
    var <args;

    *new {
        | v, a |
        ^super.new.init(v, a);
    }

    init {
        | v, a |
        val = v;
        args = a;
    }

    lookup {
        | m |
        ^m.koar[val];
    }

    flatten {
        | m |
        ^this.lookup(m);
    }

    on_enter {
        | m, nav |
		if (args.notNil) {
			args.on_enter(m, nav);
		};
    }

	on_exit {
		| m, nav |
		if (args.notNil) {
			args.on_deref_exit(m, nav);
		};
		this.do_deref(m, nav);
	}

	do_deref {
		| m, nav |
		var x = this.lookup(m);

		//"deref :: on_enter :: SYMBOL LOOKEDUP :: ".post; val.post; " ".post; x.postln;
		x = Skoarpuscle.wrap(x);

		case {x.isKindOf(SkoarpuscleSkoarpion)} {
			x.run(m, nav);

		} {x.isKindOf(SkoarpuscleExpr)} {
			var result = x.result;

			//("SKRP_Deref.do_deref :: pushing noating").postln;
			m.fairy.push_noating;
			if (result.notNil) {
				m.fairy.impress(result);
			} {
				x.flatten(m, nav);
			};
			//("SKRP_Deref.do_deref :: popping noating").postln;
			m.fairy.pop_noating;
			
		} {x.isKindOf(SkoarpuscleBook)} {
			var args = m.fairy.impression;
			
			//("SKRP_Deref.do_deref :: book :: args :: " ++ args).postln;
			if (args.isKindOf(SkoarpuscleList)) {
				var entry = args.val[0];

				if (entry.isKindOf(SkoarpusclePair)) {
					entry = entry.flatten(m);
				};
				
				if (entry.isKindOf(SkoarpuscleSymbol)) {
					m.fairy.impress(x.lookup(entry.val));
				};
			};
				
		} {
			m.fairy.impress(x);
		};
	}

    skoar_msg {
        | msg, minstrel |
        var ret = val;
        var x = this.lookup(minstrel);

		// "deref :: skoar_msg :: SYMBOL LOOKEDUP :: ".post; val.post; " ".post; x.postln;
        msg_arr = msg.get_msg_arr(minstrel);

        if (x.isKindOf(SkoarpuscleSkoarpion)) {
			^SkoarpuscleSkoarpion.new_copy_with_args(x, msg_arr);
        };

		if (x.isKindOf(Skoarpuscle)) {
			//"SNURF".postln;
			^x.skoar_msg(msg, minstrel);
		};
		
        // we don't recognise that name, did they mean a SuperCollider class?
        if (x.isNil) {
            x = val.asClass;
        };

        if (x.notNil) {
            if (x.isKindOf(SkoarpuscleString)) {
                x = x.val;
            };
            ret = x.performMsg(msg_arr);
        };

        ^Skoarpuscle.wrap(ret);
    }

}

SkoarpuscleMathOp : Skoarpuscle {
    var f;

    init {
        | toke |
        val = toke.lexeme;

        f = switch (val)
            {"+"}  {{
                | minstrel, a, b |
                Skoar.ops.add(minstrel, a, b);
            }}

            {"*"}  {{
                | minstrel, a, b |
                Skoar.ops.multiply(minstrel, a, b);
            }}

		    {"/"}  {{
                | minstrel, a, b |
                Skoar.ops.divide(minstrel, a, b);
            }}

            {"-"}  {{
                | minstrel, a, b |
                Skoar.ops.sub(minstrel, a, b);
            }};
    }

    calculate {
        | m, nav, left, right |

        // the result is impressed by the operation
        f.(m, left, right);
    }

}

SkoarpuscleBooleanOp : Skoarpuscle {

    var f;
	var <noad;

    *new {
        | n, toke |
        ^super.new.init_two(n, toke);
    }

    init_two {
        | n, toke |
        val = toke.lexeme;
		noad = n;

        // ==|!=|<=|>=|in|nin|and|or|xor
        f = switch (val)
            {"=="}  {{
                | a, b |
                a == b
            }}
            {"!="}  {{
                | a, b |
                a != b
            }}
            {"<="}  {{
                | a, b |
                a <= b
            }}
            {"<"}  {{
                | a, b |
                a < b
            }}
            {">="}  {{
                | a, b |
                a >= b
            }}
            {">"}  {{
                | a, b |
                a > b
            }}
            {"and"} {{
                | a, b |
                a and: b
            }}
            {"or"}  {{
                | a, b |
                a or: b
            }}
            {"xor"} {{
                | a, b |
                a xor: b
            }};

    }

    compare {
        | m, nav, a, b |
     
        if (a.isKindOf(Skoarpuscle)) {
            //debug(a);
            a = a.flatten(m);
        };

        if (b.isKindOf(Skoarpuscle)) {
            //debug(b);
            b = b.flatten(m);
        };

        //("===========   {? " ++ a.asString ++ " " ++ val ++ " " ++ b.asString ++ " ?}").postln;

		//a !? b !? {
		^f.(a, b)
		//};
		
        //^false
    }

	on_enter {
		| m, nav |
		m.fairy.cast_arcane_magic;
		m.fairy.compare_impress(m);
	}

}

SkoarpuscleBoolean : Skoarpuscle {

    var <op;

    init {
        | noad |
        op = noad.children[0].next_skoarpuscle;
		//("Found Boolean OP: " ++ op.asString).postln;
    }

	on_enter {
		| m, nav |
		m.fairy.push_compare;
	}

    evaluate {
        | m, nav, a, b |
		//("slrp " ++ a.asString ++ " imp: " ++ b.asString).postln;
        ^op.compare(m, nav, a, b);
    }

}


SkoarpuscleConditional : Skoarpuscle {

    var <ifs;

    *new {
        | skoar, noad |
        ^super.new.init_two(skoar, noad);
    }

    init_two {
        | skoar, noad |
		var i = 0;
        ifs = [];

		//("CONDITIONAL::").postln;
        noad.collect(\cond_if).do {
            | x |
			var boolean_expr;
            var condition;
            var if_body;
            var else_body;

			boolean_expr = SkoarNoad(\cond_cond);

			boolean_expr.add_noad(x.children[0]);
			condition = Skoarpion.new_from_subtree(skoar, boolean_expr);
			if_body = Skoarpion.new_from_subtree(skoar, x.children[2]);

            else_body = x.children[4];
            if (else_body.notNil) {
                else_body = Skoarpion.new_from_subtree(skoar, else_body);
            };

            ifs = ifs.add([condition, if_body, else_body]);
        };
		noad.children = #[];

    }

    on_enter {
        | m, nav |

        ifs.do {
            | x |
            var condition = x[0];
            var if_body = x[1];
            var else_body = x[2];
			var impression;

			//("SKRP_Conditional :: pushing noating").postln;
			m.fairy.push_noating;
			m.koar.do_skoarpion(condition,
                m, nav, [\inline], nil
            );
			//("SKRP_Conditional :: popping noating").postln;
			m.fairy.pop_noating;

			impression = m.fairy.boolean_impression;

			//("SKRP_Conditional :: pushing noating true").postln;
			m.fairy.push_noating(true);
            m.koar.do_skoarpion(
                if (impression.isKindOf(SkoarpuscleFalse) or: impression.isKindOf(SkoarpuscleCat)) {
						else_body
					} {
						if_body
					},
                m, nav, [\inline], nil
            );
			//("SKRP_Conditional :: popping noating").postln;
			m.fairy.pop_noating;
			
        };
    }

}

SkoarpuscleSkoarpion : Skoarpuscle {

    var msg_arr;

	new_copy_with_args {
		| x, args |
		^super.new.init_copy_with_args(x, args);
	}

	init_copy_with_args {
		| x, args |
		val = x.val;
		msg_arr = args;
	}

    skoar_msg {
        | msg, minstrel |
        msg_arr = msg.get_msg_arr(minstrel);
        ^this;
    }

    on_enter {
        | m, nav |
        if (val.name.notNil) {
            m.koar[val.name] = this;
        };

		if (val.name.isNil) {
			m.fairy.impress(this);
		};
	}

	run {
		| m, nav |
		var impression = m.fairy.impression;
		//("SKRP_Skoarpion :: msg_arr :: " ++ msg_arr ++ " :: impression :: " ++  impression).postln;													
		m.koar.do_skoarpion(val, m, nav, msg_arr, impression);
		//("SKRP_Skoarpion :: done :: " ++ m.fairy.impression).postln;
	}
	
	flatten {
		| m |
		var impression = m.fairy.impression;
		^{
			| ... args |
			var msg_args = \block ++ args;

			args = Skoarpuscle.wrap(args);
			//("Flat Skoarpion :: args :: " ++ args).postln;
			block {
				| nav |
				//this.run(m, nav);
				m.koar.do_skoarpion(val, m, nav, [\block], args);
			};

			m.fairy.impression.flatten(m);
			
		};
	}

}

SkoarpuscleTimes : Skoarpuscle {

	on_enter {
        | m, nav |
		var desired_times = m.fairy.cast_arcane_magic;
		
		if (desired_times.isCounty) {
			var times_seen = m.fairy.how_many_times_have_you_seen(this);
			desired_times = desired_times.asCount;

			//("desired_times: " ++ desired_times.asString ++ "\n times seen: " ++ times_seen.asString).postln;
			m.fairy.impress( ( times_seen % desired_times != 0) );
		};
		 
    }

}

SkoarpuscleLoop : Skoarpuscle {

    var <condition;
    var <body;
    var <each;

    *new {
        | skoar, noad |
        ^super.new.init_two(skoar, noad);
    }

    init_two {
        | skoar, noad |

        noad.collect(\loop_condition).do {
            | x |
			if (x.children.size > 0) {
				condition = Skoarpion.new_from_subtree(skoar, x);
			};
        };

        noad.collect(\loop_body).do {
            | x |
            body = Skoarpion.new_from_subtree(skoar, x);
        };

        each = nil;
    }

    on_enter {
        | m, nav |
        
		m.fairy.push_i;
		//("SKRP_Loop :: pushing noating true").postln;
		m.fairy.push_noating(true);
		
        block {
            | break |
            while {true} {
                var f = {
                    | element |

                    // this is how we foreach
                    if (element.isKindOf(Skoarpuscle)) {
                        m.fairy.impress(element);
                    };

                    m.koar.do_skoarpion(body, m, nav, [\inline], m.fairy.impression);
                    m.fairy.incr_i;

					if (condition.notNil) {
						var x;

						//("SKRP_Loop :: condition :: pushing noating").postln;
			
						m.fairy.push_noating;
						m.koar.do_skoarpion(condition, m, nav, [\inline]);
						m.fairy.pop_noating;
						//("SKRP_Loop :: condition :: popping noating").postln;
			
						
						x = m.fairy.boolean_impression;
						if (x.isKindOf(SkoarpuscleFalse) or: x.isKindOf(SkoarpuscleCat)) {
							break.();
						};
                    };
                };

                if (each.isNil) {
                    f.(nil);
                } {
                    //debug("each: " ++ each.asString);
                    each.val.do {
                        | element |
                        //debug("each:el: " ++ element.asString);
                        f.(element);
                    };
                };
				
				//"zorp: condition: ".post; condition.postln;
                if (condition.isNil) {
                    break.();
                };
            };
        };

		//("SKRP_Loop :: popping noating").postln;
			
		m.fairy.pop_noating;
		m.fairy.pop_i;
    }

    // when we send a loop as a message, the receiver
    // goes into _each_ and _this_ becomes the new receiver.
    foreach {
        | listy |
        each = listy;
        ^this;
    }
}


SkoarpuscleLoopMsg : Skoarpuscle {
}



SkoarpuscleExprEnd : Skoarpuscle {

    on_enter {
        | m, nav |
        m.fairy.cast_arcane_magic;
    }
}

SkoarpuscleListSep : Skoarpuscle {

    on_enter {
        | m, nav |
        m.fairy.next_listy;
    }
}

SkoarpuscleListEnd : Skoarpuscle {

    on_enter {
        | m, nav |
		//("SKRP_ListEnd :: popping").postln;
        m.fairy.next_listy;
        m.fairy.pop;
		m.fairy.pop_noating;
		//"snarps".postln;
    }

	
}

SkoarpuscleList : Skoarpuscle {

	var <>noaty;
	
    init {
        | x |
		val = if (x.isNil) {
			[]
		} {
			x
		};

		noaty = true;
		//"new list: ".post; val.postln;
    }

	mul {
		| minstrel, y |
		var out = [];
		
		val.do {
			| x |
			out = out.add(Skoar.ops.multiply_unimpressively(minstrel, x, y));
		};

		^SkoarpuscleList.new(out);
	}

	div {
		| minstrel, y |
		var out = [];
		
		val.do {
			| x |
			out = out.add(Skoar.ops.divide_unimpressively(minstrel, y, x));
		};

		^SkoarpuscleList.new(out);
	}

	divBy {
		| minstrel, y |
		var out = [];
		
		val.do {
			| x |
			out = out.add(Skoar.ops.divide_unimpressively(minstrel, x, y));
		};

		^SkoarpuscleList.new(out);
	}
	
	size {
		^val.size;
	}
	
	flatten { | m | 
		var arr = [];
		val.do {
			| x |
			var y = x.flatten(m);
			//("x: " ++ x.asString ++ "    y: " ++ y.asString).postln;
			
			if (y.isKindOf(SkoarpusclePair)) {
				y = y.flatten(m);
			};
			
			//("Adding " ++ y).postln;
			arr = arr.add(y);
		};
		^arr; 
	}

    on_enter {
        | m, nav |
		//("SKRP_List :: pushing noating :: " ++ noaty).postln;
		m.fairy.push_noating(noaty);
        m.fairy.push;
    }

    isNoatworthy {

        val.do {
            | x |
            if (x.isNoatworthy == false) {
                ^false;
            };
        };

        ^true;
    }

    asNoat {

        var n = val.size;
        var noats = Array.newClear(n);
        var i = -1;
		var theseAreNoats = true;
		var theseAreFreq = false;
		
        val.do {
            | x |
            i = i + 1;

			if (x.isKindOf(SkoarpuscleFreq)) {
				theseAreNoats = false;
				theseAreFreq = true;
			};

			if (x.isKindOf(SkoarpuscleInt)) {
				theseAreNoats = false;
			};

			if (x.isKindOf(SkoarpuscleFloat)) {
				theseAreNoats = false;
			};
			noats[i] = x.asNoat;
        };

		if (theseAreNoats == true) {
			^SkoarNoat_NoteList(noats);
		};

		if (theseAreFreq == true) {
			^SkoarNoat_FreqList(noats);
		};

		^SkoarNoat_DegreeList(noats);
	}


	skoar_msg {
        | msg, minstrel |
        var o = msg.get_msg_arr(minstrel);
        var name = msg.val;
        var ret;

		// todo teach the fairy to next and last
        case {name == \next} {
            ret = val.performMsg(o);
        } {name == \last} {
            ret = val.performMsg(o);
        } {name == \choose} {
            ret = val.choose();
        } {
            ret = val.performMsg(o);
        };

        ^Skoarpuscle.wrap(ret);
    }
    

}

SkoarpuscleArgs : SkoarpuscleList {

	var <pairs;

	on_enter {
		| m |
		//("SKRP_Args :: pushing noating").postln;
		m.fairy.push_noating;
		m.fairy.push;
	}

	on_deref_exit {
		| m, nav |
		m.fairy.pop;
		m.fairy.pop_noating;
	}

}

// {! f<a,b,c> !! '[\a,\b,\c] is the ArgsSpec' !}
SkoarpuscleArgSpec : Skoarpuscle {

    init {
        | toke |
        var matches = toke.lexeme.findRegexp("[a-zA-Z_]*",1);

		if (matches.notNil) {
			matches.do {
				| x |
				var m = x[1];
				if (m != "") {
					val = val.add(SkoarpuscleSymbolName(m.asSymbol));
				};
			};
		};
    }
}

SkoarpuscleMsg : Skoarpuscle {

    var <>args;
	var <>dest;
	var pref;
	
    *new {
        | v, a |
        ^super.new.init(nil).init(v, a);
    }

    init {
        | v, a |
        val = v;
        args = a;
		pref = "SKRP_Msg :: ";
	}

	asString {
		^("(" ++ super.asString ++ " -> " ++ dest.asString ++ ")");
	}

    on_enter {
        | m, nav |
		var result;

		//(pref ++ "on_enter :: " ++ this).postln;
		if (args.notNil) {
			args = m.fairy.impression;
			//(pref ++ "impression (args) ::  " ++ args).postln;
		};

		case {dest.isKindOf(SkoarpuscleList)} {
			result = m.fairy.impression;
			//(pref ++ "List :: messaging :: impression :: " ++ result).postln;
			result = result.skoar_msg(this, m);
			//(pref ++ "List :: impressing :: " ++ result).postln;

		} {dest.isKindOf(SkoarpuscleSymbol)} {
			//(pref ++ "Symbol :: messaging :: dest :: " ++ dest).postln;
			result = dest.skoar_msg(this, m);
			//(pref ++ "Symbol :: impressing :: " ++ result).postln;

		} {
			//(pref ++ "ELSE messaging").postln;
			result = dest.skoar_msg(this, m);
			//(pref ++ "ELSE ::: impressing :: " ++ result).postln;
		};
		m.fairy.impress(result);
    }

	skoar_msg {
		| msg, minstrel |
		var result = minstrel.fairy.impression;

		result = result.skoar_msg(msg, minstrel);
		//(pref ++ "skoar_msg :: impressing :: " ++ result).postln;
		minstrel.fairy.impress(result);
		^result;
	}
	
    get_msg_arr {
        | m |
		var x, z;
		var i;

		if (args.isNil) {
			^[val];
		};

		//("MSG::"++val++"::get_msg_arr::args:"++ args).postln;
		//("Args exist, x will be " ++ (args.size + 1).asString).postln; 
		x = Array.newClear(args.size + 1);
		i = 0;

		//"args: ".post; args.postln;
		//("SKRP_Msg.get_msg_arr :: pushing noating").postln;
		m.fairy.push_noating;
		
		x[0] = val;
		args.val.do {
			| y |
			//"y: ".post; y.postln;
			i = i + 1;
			case {y.isKindOf(SkoarpusclePair)} {
				x[i] = [y.key.val, y.val.flatten(m)];
			} {y.isKindOf(Skoarpuscle)} {
				x[i] = y.flatten(m);
			} {
				x[i] = y;
			};
		};
		//("SKRP_Msg.get_msg_arr :: popping noating").postln;
		m.fairy.pop_noating;
		
		//("MSG::get_msg_arr::  x :"++ x).postln;
		^x;
		
    }

	get_args_from_prototype {
		| m, arg_spec, arg_prot |
		var e = ();
		var j = 0;
		var ret = [];
		var w;
		var p = pref ++ " g_a_f_proto :: ";
		
		//(p ++ "arg_prot :: " ++ arg_prot).postln;

		if (args.notNil) {
			args.val.do {
				| x |
				if (x.isKindOf(SkoarpusclePair)) {
					e[x.key.val] = x.val.flatten(m);
					//(p ++ "e[" ++ x.key.val ++ "] = e[x.key.val] =" ++ e[x.key.val] ++ ";").postln;
				} {
					e[j] = x.flatten(m);
					//(p ++ "e[" ++ j ++ "] = e[j] =" ++ e[j] ++ ";").postln;
					
				};
				j = j + 1;
			};
		};
	
		arg_spec.do {
			| x, i |
			var v = e[x];
			var y;
			
			if (v.notNil) {
				arg_prot[i] = v;
				//(p ++ "arg_prot[" ++ i ++ "] = v = " ++ v ++ ";").postln;
			} {
				y = e[i]; 
				//(p ++ "arg_prot[" ++ i ++ "] = e[i] =" ++ e[i] ++ ";").postln;

				if (y.notNil) {
					arg_prot[i] = y;
				};
			};
		};

		//(p ++ "arg_prot :: "++ arg_prot).postln;
		
		^arg_prot;
	}
		
}

SkoarpuscleMsgName : Skoarpuscle {
	
}

SkoarpuscleMsgNameWithArgs : Skoarpuscle {
	on_enter {
		| m, nav |
		//("SKRP_MsgNWA :: pushing noating ").postln; 
		m.fairy.push_noating;
		m.fairy.push;
	}
}

// -----------------------------
// musical keywords skoarpuscles
// -----------------------------

SkoarpuscleBars : Skoarpuscle {

    var <>noad; // is set in \markers skoarmantics
    var <pre_repeat;
    var <post_repeat;

    init {
        | toke |

        val = toke.lexeme;
        pre_repeat = val.beginsWith(":");
        post_repeat = val.endsWith(":");
    }

	asString {
		var s = ("SkoarpuscleBars: " ++ val ++ "noad:"++ noad.asString ++ 
		    " pre_repeat:" ++ pre_repeat ++ " post_repeat:" ++ post_repeat);
		^s;
	}

    on_enter {
        | m, nav |

		//"on_enter: ".post; this.asString.postln;
        
		// :|
        if (pre_repeat == true) {

			var burned = m.koar.state_at(\colons_burned);

			// asking counts as observing
			if (m.fairy.how_many_times_have_you_seen(this) < 2) {
				nav.(\nav_colon);
			};	

			if (burned.falseAt(noad)) {
                burned[noad] = true;
            };

        };

        // |:
        if (post_repeat == true) {
            m.koar.state_put(\colon_seen, noad);
        };
    }
}

SkoarpuscleFine : Skoarpuscle {

    on_enter {
        | m, nav |
        if (m.koar.state_at(\al_fine) == true) {
            //debug("fine");
            nav.(\nav_fine);
        };
    }
}

SkoarpuscleSegno : Skoarpuscle {

    var <noad;

    *new {
        | nod, toke |
        ^super.new.init_two(nod, toke);
    }

    init_two {
        | nod, toke |
        var s = toke.lexeme;
        var n = s.size;

        noad = nod;

        // ,segno`label`
        if (n > 8) {
            s[6..n-2].asSymbol;
        } {
            \segno
        };
        val = s[1..n].asSymbol;
    }

    on_enter {
        | m, nav |
        m.koar.state_put(\segno_seen, noad);
    }

}

SkoarpuscleGoto : Skoarpuscle {

    var nav_cmd;
    var al_fine;

    init {
        | noad |

        var toke = noad.children[0].next_toke;
        var al_x = noad.children[1];

        nav_cmd = case {toke.isKindOf(Toke_DaCapo)} {\nav_da_capo}
                       {toke.isKindOf(Toke_DalSegno)} {\nav_segno};

        al_fine = false;
        if (al_x.notNil) {
            if (al_x.next_toke.isKindOf(Toke_AlFine)) {
                al_fine = true;
            };
        };
    }

    on_enter {
        | m, nav |
        if (al_fine == true) {
            m.koar.state_put(\al_fine, true);
        };

        m.reset_colons;
        //"goto:".post; nav_cmd.postln;
        nav.(nav_cmd);
    }

}

SkoarpuscleVolta : Skoarpuscle {

    var <noad;

    *new {
        | nod, toke |
        ^super.new.init_two(nod, toke);
    }

    init_two {
        | nod, toke |
        val = toke.lexeme.strip("[.]").asInteger;
        noad = nod;
    }

    on_enter {
        | m, nav |
    }

}

SkoarpuscleMeter : Skoarpuscle {

    init {
        | toke |
        var a = toke.lexeme.split;
        val = [a[0].asInteger, a[1].asInteger];
    }
}

SkoarpuscleCarrots : Skoarpuscle {

    init {
        | toke |
        val = toke.lexeme.size;
    }
}

SkoarpuscleTuplet : Skoarpuscle {

    init {
        | toke |
        val = toke.lexeme.size;
    }
}

SkoarpuscleDynamic : Skoarpuscle {

    init {
        | toke |
        var s = toke.lexeme;

        val = switch (s)
            {"ppp"}			{1}
            {"pppiano"}		{1}
            {"pp"}			{2}
            {"ppiano"}		{2}
            {"p"}			{3}
            {"piano"}		{3}
            {"mp"}			{4}
            {"mpiano"}		{4}
			{"mezzopiano"}  {4}
            {"mf"}			{5}
            {"mforte"}		{5}
            {"mezzoforte"}  {5}
            {"forte"}		{6}
            {"ff"}			{7}
            {"fforte"}		{7}
            {"fff"}			{8}
            {"ffforte"}		{8};
    }

    amp {
        ^(val * val) / 64;
    }

    on_enter {
        | m, nav |
        m.fairy.consider_amp(this, m);
    }

}

SkoarpuscleOctaveShift : Skoarpuscle {

    init {
        | toke |
        var f = {
            var s = toke.lexeme;
            var n = s.size - 1;

            if (s.beginsWith("o")) {
                n =  n * -1;
            };
            n
        };

        val = case {toke.isKindOf(Toke_OctaveShift)} {f.()}
                   {toke.isKindOf(Toke_OttavaA)}       { 1}
                   {toke.isKindOf(Toke_OttavaB)}       {-1}
                   {toke.isKindOf(Toke_QuindicesimaA)} { 2}
                   {toke.isKindOf(Toke_QuindicesimaB)} {-2};
    }

    on_enter {
        | m, nav |
        var octave = m.koar[\octave] ?? 5;
        m.koar[\octave] = octave + val;
    }

}

SkoarpuscleVoice : Skoarpuscle {

    init {
        | toke |
        var s = toke.lexeme;
        var n = s.size - 1;
        val = s[1..n].asSymbol;
    }

}

SkoarpuscleRep : Skoarpuscle {

    init {
        | toke |
        val = toke.lexeme.size;
    }

}

SkoarpuscleHashLevel : SkoarpuscleFloat {

	init {
		| toke |
		var n = -2, i = 0;
		toke.lexeme.do {
			| x |
			if (x.notNil) {
				n = n + 1;
				if (x == $#) {
					i = i + 1;
				};
			}; 
		};

		val = if (n <= 0) {
			0.0
		} {
			i/n
		};
	}

}


SkoarpusclePair : Skoarpuscle {

	var <key;
	
	*new {
        | k, v |
        ^super.new.init_two(k, v);
    }

    init_two {
		| k, v |
		key = k;
		val = v;
	}

	flatten {
		| m, nav |
		var x;
		//("SKRP_Pair.flatten :: pushing noating").postln;
		m.fairy.push_noating;
	
		x = val.flatten(m, nav);
		
		//("SKRP_Pair.flatten :: popping noating").postln;
		m.fairy.pop_noating;

		^x;
	}

	assign {
		| m |
		var x;

		//("SKRP_Pair.assign :: pushing noating").postln;
		m.fairy.push_noating;
	
		x = if (val.isKindOf(SkoarpuscleExpr)) {
			val.flatten(m)
		} {
			val
		};
		
		Skoar.ops.assign(m, x, key);

		//("SKRP_Pair.assign :: popping noating").postln;
		m.fairy.pop_noating;
	}
	
}


SkoarpuscleExpr : Skoarpuscle {

	var <result;
	
	init {
		| noad |
		val = noad;
		result = nil;
	}
	
	flatten {
		| m |
		//("SkoarpuscleExpr :: flatten").postln;
		m.fairy.push;
	
		if (val.notNil) {
			val.evaluate(m);
		} {
			m.fairy.impress(SkoarpuscleCat.new);
		};
		
		result = m.fairy.impression;
		result = result.flatten(m);

		m.fairy.pop;
	
		//("SkoarpuscleExpr :: result :: " ++ result).postln;

		^result;
	}

	on_enter {
		| m, nav |
		//("SkoarpuscleExpr :: on_enter").postln;
	}
}

