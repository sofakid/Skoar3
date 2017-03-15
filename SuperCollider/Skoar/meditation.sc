SkoarpuscleMeditation : Skoarpuscle {

    var <skoarpion;

    *new {
        | skoar, noad |
        ^super.new.init_two(skoar, noad);
    }

    init_two {
        | skoar, noad |
		var med_root = SkoarNoad(\meditation);

		med_root.children = noad.children;

		skoarpion = Skoarpion.new_from_subtree(skoar, med_root);
    }

	new_routine {
		| m, impression |
		^Routine({
            var running = true;
            var nav_result = nil;
			var e, n, s, d;

            while {running} {

                nav_result = block {
                    | nav |
                    m.koar.do_skoarpion(skoarpion, m, nav, [\meditation], impression);
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

			e = m.koar.event(m);
			e[\dur] = 0;
			e[\dur_by_tempo] = 0;

			n = m.fairy.num_impression;
			e[\num_impression] = if (n.isKindOf(Skoarpuscle)) {
			 	n.flatten(m)
			} { 
				n
			};

			s = m.fairy.sym_impression;
			e[\sym_impression] = if (s.isKindOf(Skoarpuscle)) {
				s.flatten(m)
			} { 
				s
			};

			d = m.fairy.dyn_impression;
			e[\dyn_impression] = if (d.isKindOf(Skoarpuscle)) {
				d.flatten(m)
			} { 
				d
			};
			
			yield(e);
			
            //("Minstrel " ++ koar.name ++ " done.").postln;
        });

	}
	
    on_enter {
        | m, nav_unused |
		var impression = m.fairy.impression;
        
		m.fairy.impress(this.new_routine(m, impression));
		
    }

	skoar_msg {
        | msg, minstrel |
		var impression = minstrel.fairy.impression;
        var routine = this.new_routine(minstrel, impression);
        var name = msg.val;
        var ret = this; 

		var f_env = {

			var aLevels = [];
			var aTimes  = [];
			var aCurves = [];

			var pref = (minstrel.fairy.name ++ ". ENV: ");
			var result = routine.next;

			
			//"---------------------------------------------------------".postln;
			//(pref ++ result).postln;
			
			while {result.notNil} {
				var level = result[\num_impression];
				var time  = result[\dur_by_tempo];
				var curve = result[\sym_impression];
				//(pref ++ result).postln;

				if (level.notNil) {
					aLevels = aLevels.add(level);
				};

				if (time.notNil) {
					aTimes = aTimes.add(time);
				};

				if (curve.notNil) {
					aCurves = aCurves.add(curve);
				};

				result = routine.next;
			};
			//(pref ++ "Env(" ++ aLevels ++ ", " ++ aTimes ++ ", " ++ aCurves ++ ")").postln;
			ret = Env(aLevels.asArray, aTimes.asArray, aCurves.asArray);		

			//"---------------------------------------------------------".postln;
			
		};
		
        case {name == \env} {

			f_env.();
			
		} {name == \aEnv} {

			f_env.();
			ret = Skoarpuscle.wrap(ret).a;
			
		} {name == \kEnv} {

			f_env.();
			ret = Skoarpuscle.wrap(ret).k;
			
		} {name == \amp} {
			
			var aLevels = [];
			var aTimes  = [];
			var aCurves = [];

			var pref = (minstrel.fairy.name ++ ". AMP: ");
			var result = routine.next;

			//"---------------------------------------------------------".postln;
				
			while {result.notNil} {
				var ilevel = result[\num_impression];
				var dlevel = result[\dyn_impression];
				var time   = result[\dur_by_tempo];
				var curve  = result[\sym_impression];
				
				case {dlevel.notNil} {
					aLevels = aLevels.add(dlevel * 2);
				} {ilevel.notNil} {
					aLevels = aLevels.add(ilevel);
				};

				if (time.notNil) {
					aTimes = aTimes.add(time);
				};

				if (curve.notNil) {
					aCurves = aCurves.add(curve);
				};
			};
			
			ret = Env(aLevels.asArray, aTimes.asArray, aCurves.asArray);

			minstrel.controls.apply_env(ret);

			//"---------------------------------------------------------".postln;
			
        } {name == \worries} {

			var pref = (minstrel.fairy.name ++ ". WORRY :: ");
			var result = routine.next;

			"---------------------------------------------------------".postln;
			
			while {result.notNil} {
				(pref ++ result).postln;
				result = routine.next;
			};
			
			"---------------------------------------------------------".postln;			
		} {name == \books} {

			var args = msg.get_msg_arr(minstrel);
			var result;
			var pref = (minstrel.fairy.name ++ ". BOOK :: ");

			args = args[1..];
			//(pref ++ "args :: " ++ args).postln;

			ret = SkoarpuscleBooks.new;

			minstrel.fairy.push;
			result = routine.next;
			
			//"---------------------------------------------------------".postln;
			
			while {result.notNil} {
				//(pref ++ result).postln;
				ret.add_book(SkoarpuscleBook.new_book(result, args));
				result = routine.next;
			};
			
			minstrel.fairy.pop;
			//"---------------------------------------------------------".postln;			
		} {name == \book} {

			var args = msg.get_msg_arr(minstrel);
			var result;
			var pref = (minstrel.fairy.name ++ ". BOOK :: ");

			args = args[1..];
			//(pref ++ "args :: " ++ args).postln;

			minstrel.fairy.push;
			result = routine.next;
			
		    ret = SkoarpuscleBook.new_book(result, args);
			
			minstrel.fairy.pop;
			//"---------------------------------------------------------".postln;			
		};

        ^Skoarpuscle.wrap(ret);
    }
}


SkoarpuscleMeditationMsg : Skoarpuscle {
}

SkoarpuscleRoutine : Skoarpuscle {

	asString {
		^'SkoarpuscleRoutine';
	}
	
	next {
		^val.next;
	}

}
