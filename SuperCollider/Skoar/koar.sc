
SkoarKoar {
    var   skoar;        // global skoar
    var  <skoarboard;   //
    var  <stack;        // stack of vars visible to the skoar code
    var  <state_stack;  // stack of vars invisible to the skoar code

    var  <name;         // name of voice as Symbol
	

    *new {
        | skr, nom |
        ^super.new.init(skr, nom);
    }

    init {
        | skr, nom |

        skoar = skr;
        name = nom;

        stack = List[];
        state_stack = List[];
        skoarboard = (\voice: name);
        stack.add(skoarboard);

    }

    // ---------------------
    // State and scope stuff
    // ---------------------
    put {
        | k, v |
        this.top_args[k] = v;
    }

    at {
        | k |
        var out = nil;

        stack.reverseDo {
            | skrb |
            out = skrb[k];
            if (out.notNil) {
                ^out;
            };
        };

        ^out;
    }

    state_put {
        | k, v |
        state_stack[state_stack.size - 1].put(k, v);
    }

    state_at {
        | k |
        var out = nil;

        state_stack.reverseDo {
            | skrb |
            out = skrb[k];
            if (out.notNil) {
                ^out;
            };
        };

        ^out;
    }

    // constructs the event that will be played by SC
    event {
        | minstrel |
        var e = Event.new;

		//("KOAR.EVENT :: " ).postln;
        stack.do {
            | skrb |
			var mus_key;

            // native function constructs the event quickly
            e = skrb.transformEvent(e);

			//("KOAR.EVENT :: e :: " ++ e).postln;
            // but we need to change stuff
            e.keysValuesChange {
                | key, value |
	
                case {value.isKindOf(SkoarpuscleKey)} {
                    // we don't modify this one yet, we deal with key next.
                    value

                } {value.isKindOf(Skoarpuscle)} {
					var x;
					// we want values, not skoarpuscles
					//("koar :: event :: flattening").postln;
					x = value.flatten_forgetfully(minstrel);
					//("koar :: event :: done flattening").postln;
					x
                } {
                    // perfect
                    value
                }
            };

			if (e[\choard].notNil) {
				e[\note] = e[\choard];
				e[\choard] = nil;
			} {
				mus_key = e[\key];

				if (mus_key.isKindOf(SkoarpuscleKey)) {
					mus_key.apply(e);
					e[\key] = nil;
				}; 
			};

        }

        ^e
    }

	set_args {
        | minstrel, arg_spec, args_provided |
        var i = 0;
        var vars = stack[stack.size - 1];

		if (arg_spec.isNil) {
			//"ARG_SPEC IS NIL".postln;
			^nil;
		};

		//"koar:: ARG_SPEC: ".post; arg_spec.dump;
		//("koar:: ARGS    : " ++ args_provided.flatten(minstrel) ).postln;

		if (args_provided.isKindOf(SkoarpuscleList)) {
			args_provided = args_provided.val;
		} {
			args_provided = Array.newClear(arg_spec.args_names.size).fill(nil);
		};

		//("koar.set_args :: pushing noating").postln;
		minstrel.fairy.push_noating;
		arg_spec.args_names.do {
			| arg_name, i |

			var x = args_provided[i];

			//("koar:: arg " ++ i ++ " name " ++ arg_name ++ " provided " ++ x).postln;
			
			case {x.isNil} {
				// not found, use default
				var y = arg_spec.args_dict[arg_name];
				//("koar:: 1: y = " ++ y).postln;
				if (y.isKindOf(SkoarpuscleExpr)) {
					y = y.flatten(minstrel);
					//("koar:: 1.3: y = " ++ y).postln;
				};

				//("koar:: 1.7: vars["++arg_name++"] = " ++ y).postln;
				vars[arg_name] = y;
			} {x.isKindOf(SkoarpusclePair)} {
				// pair sets arbitrary key
				vars[x.key.val] = x.val;
				//("koar:: 2: vars["++x.key.val++"] = " ++ vars[x.key.val]).postln;
				
			} {
				// use positional arg
				vars[arg_name] = x;
			};
		};

		//("koar.set_args :: popping noating").postln;
		minstrel.fairy.pop_noating;
		//"koar:: args set".postln;
    }

    top_args {
        ^stack[stack.size - 1];
    }

    push_state {
        var state = IdentityDictionary.new;
        var projections = IdentityDictionary.new;

        state_stack = state_stack.add(state);

        state[\colons_burned] = Dictionary.new;
        state[\al_fine] = false;
        state[\projections] = projections;

        stack = stack.add(IdentityDictionary.new);

		// this is where i want this, but i don't have a fairy here.
		// fairy.push_times_seen;

    }

    pop_state {
        stack.pop;
        state_stack.pop;
		// this is where i want this, but i don't have a fairy here.
		// fairy.pop_times_seen;
    }

    do_skoarpion {
        | skoarpion, minstrel, up_nav, msg_arr, args |

        var subtree;
        var projection;
        var projections;
        var msg_name;
        var inlined;

        if (skoarpion.isKindOf(Skoarpion) == false) {
            "This isn't a skoarpion: ".post; skoarpion.postln;
            ^nil;
        };

        // default behaviour (when unmessaged)
        if (msg_arr.isNil) {
            msg_arr = [\block];
        };

        msg_name = msg_arr[0];

        inlined = (msg_name == \inline);
        if (inlined == false) {
            this.push_state;
			minstrel.fairy.push_times_seen;
        };

        // load arg values into their names
		this.set_args(minstrel, skoarpion.arg_list, args);
		
        projections = this.state_at(\projections);
        if (skoarpion.name.notNil) {
            projection = projections[skoarpion.name];

 			//("KOAR<" ++ name ++ ">" ++ projection).postln;

			// start a new one if we haven't seen it
            if (projection.isNil) {
                projection = skoarpion.projection(name);
				//("KOAR<" ++ name ++ ">" ++ projection.name).postln;
                projections[skoarpion.name] = projection;
            };
        } {
			
            projection = skoarpion.projection(name);
			//("KOAR< ??? >" ++ projection).postln;
            
		};

        subtree = projection.performMsg(msg_arr);

		//("KOAR<" ++ name ++ "> about to loop through projection:").postln;
		//subtree.draw_tree.postln;
		
        this.nav_loop(subtree, projection, minstrel, up_nav, inlined);

        if (inlined == false) {
            this.pop_state;
			minstrel.fairy.pop_times_seen;
        };
    }

    nav_loop {
        | dst, projection, minstrel, up_nav, inlined |

        var nav_result;
        var running = true;
        var subtree = dst;

        while {running} {

            // you can think of this like a try/catch for nav signals
            nav_result = block {
                | nav |

                // map dst to an address relative to the projection
                var here = projection.map_dst(dst);

                subtree.inorder_from_here(
                    here,

                    {   | x |
                        x.enter_noad(minstrel, nav); });

                // our metaphorical throws look like this,
                // you'll also find them in the navigational
                // skoarpuscles' on_enters. (segno, bars, etc..)
				//
				// that is, once nav.(\something) is called, execution is aborted and continues
				// at the top of this this block, with block returning the \something into nav_result.
                nav.(\nav_done);
            };

            // here's our metaphorical catch
            switch (nav_result)

                {\nav_done} {
                    running = false;
                }

                {\nav_fine} {
                    this.bubble_up_nav(minstrel, up_nav, \nav_fine, inlined);
                }

                {\nav_coda} {

                }

                {\nav_da_capo} {
                    this.bubble_up_nav(minstrel, up_nav, \nav_da_capo, inlined);
                }

                {\nav_segno} {
                    dst = this.state_at(\segno_seen);

                    if ((dst !? (_.skoap)) != subtree.skoap) {
                        this.bubble_up_nav(minstrel, up_nav, \nav_segno, inlined);
                    };
                }

                {\nav_colon} {
                    dst = this.state_at(\colon_seen);
                    
					if ((dst !? (_.skoap)) != subtree.skoap) {
                        this.bubble_up_nav(minstrel, up_nav, \nav_colon, inlined);
                    };
                };

        };
    }

    bubble_up_nav {
        | minstrel, nav, cmd, inlined |

        // the nav command will abort do_skoarpion,
        // we have to clean up here.
        if (inlined == false) {
            this.pop_state;
			minstrel.fairy.pop_times_seen;
        };

        // metaphorically rethrowing to a higher level
        nav.(cmd);
    }
}

