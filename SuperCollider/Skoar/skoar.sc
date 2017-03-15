// =====
// Skoar
// =====
Skoar {

    classvar <ops;      // operations tables object

    var   skoarse;      // the skoarse code
    var   parser;       // the parser
    var  <tree;         // root of tree
    var  <toker;        // toker
    var  <voices;       // all the voices
    var  <all_voice;    // the all voice
    var  <skoarpions;   // all the skoarpions

	var  <controls;     // volume and panning controls
	var  <skoarsfjord;  // the troll lives here
	var <>running;
	var   mutex;

	var   tokes;        // list of tokes, in order, for syntax highlighting
    var  <toke_lines;
    var  <styles;
    var  <parsed_ok;

    var <log;
    *initClass {
        ops = SkoarOps.new;
    }

    *new {
        | code |
        ^super.new.init(code);
    }

    *new_for_highlighting {
        | code |
        ^super.new.init_for_highlighting(code);
    }

    init {
        | code |
        var start_time;
        var parse_time;
        var decorate_time;

        log = SkoarLogger("Skoar");
        skoarse = code ++ "\n";
        tree = nil;
        tokes = [];
        toke_lines = [];
        parsed_ok = false;

        toker = Toker(skoarse);
        parser = SkoarParser(this);

		mutex = Semaphore(1);
		skoarsfjord = Skoarsfjord(this);
		running = 0;
		
        voices = ();
        all_voice = SkoarKoar(this, \all);
        voices[\all] = all_voice;

        ops = SkoarOps.new;

        skoarpions = List[];

        start_time = Process.elapsedTime;

        //">>> parsing skoar...".postln;
        tree = parser.skoar(nil);

        try {
            toker.eof;
        } {
            | e |
            e.postln;
            toker.dump;
            e.throw;
        };

        parsed_ok = true;
        parse_time = (Process.elapsedTime - start_time).round(0.01);

		//log.d("---< Undecorated Skoar Tree >---");
		//log.d("\n" ++ tree.draw_tree);
		//log.d("<<< tree created, now decorating...");

		this.decorate;
        decorate_time = (Process.elapsedTime - start_time - parse_time).round(0.01);

        //this.draw_skoarpions;

        log.i("Skoar parsed in " ++ parse_time ++ " seconds, decorated in  "
            ++ decorate_time ++ ". Total: " ++ (parse_time + decorate_time) ++ " sec.");

        // next time it should be faster.
        this.sort_parser_desirables;

    }

    init_for_highlighting {
        | code |
        var start_time;
        var parse_time;
        var decorate_time;
        var line_number = 0;
        var pos = 0;
        var line = [];
        var line_pos = 0;

        log = SkoarLogger("Skoar - Highlighting");
        skoarse = code;
        tree = nil;
        tokes = [];
        toke_lines = [];
        styles = List[];
        parsed_ok = false;

        toker = Toker(skoarse);
        parser = SkoarParser(this);

		mutex = nil;
		skoarsfjord = nil;
		running = 0;

        voices = nil;
        all_voice = nil;

        skoarpions = nil;
        start_time = Process.elapsedTime;

        //">>> parsing skoar...".postln;
        try {
            tree = parser.skoar(nil);
            toker.eof;
            parsed_ok = true;
            parse_time = (Process.elapsedTime - start_time).round(0.01);

            //log.d("---< Undecorated Skoar Tree >---");
            //log.d("\n" ++ tree.draw_tree);
            //log.d("<<< tree created, now decorating...");

            tree.inorder_before_after({
                | noad |
                var toke = noad.toke;
                var style;

                if (toke.notNil) {
                    pos = toke.offs + toke.size;
                    noad.offs = toke.offs;
                    noad.line_number = line_number;

                    if (toke.isKindOf(Toke_Newline)) {
                        line_number = line_number + 1;
                        line_pos = pos;
                    };

                    noad.line_offs = pos - line_pos;
                    style = SkoarUiColourTemplate.defaults[toke.class.asSymbol];
                } {
                    noad.offs = pos;
                    noad.line_offs = pos - line_pos;
                    noad.line_number = line_number;
                    style = SkoarUiColourTemplate.defaults[noad.name];
                };

                if (style.notNil) {
                    noad.style = style;
                    styles.add(noad);
                };
            }, {
                | noad |
                var first_newline;
                noad.size = pos - noad.offs;

                first_newline = block {
                    | ret |
                    noad.inorder({
                        | x |
                        if (x.line_number > noad.line_number) {
                            ret.(x);
                        };
                    });
                    ret.(nil);
                };

                if (first_newline.isNil) {
                    noad.line_size = noad.size;
                } {
                    noad.line_size = first_newline.offs - noad.offs;
                };
            });

            tree.depth_visit({
                | noad |
                var x = noad.line_offs.hash bitXor: noad.line_size.hash bitXor: noad.name.hash;
                var y = x bitXor: noad.size.hash;

                noad.line_hash = x;

                noad.children.do {
                    | child |
                    y = y bitXor: child.subtree_hash;
                };
                noad.subtree_hash = y;
            });

            decorate_time = (Process.elapsedTime - start_time - parse_time).round(0.01);

            //log.i("parsed in " ++ parse_time ++ " seconds.", "decorated in " ++ decorate_time ++ " seconds");

            // next time it should be faster.
            this.sort_parser_desirables;
        } {
            | e |
            log.d("highlight exception", e.errorString);
        };

    }

    add_toke {
        | noad, name, toke |
        tokes = tokes.add(toke);
        noad.add_toke(name, toke);

        if (name == 'Toke_Newline') {
            toke_lines = toke_lines.add(tokes);
            tokes = [];
        };

        // use a float so it never overflows, just eventually
        // stops making a difference when adding 0.1
        toke.class.freq = toke.class.freq + 0.1;
    }

    decorate {

        var inspector = SkoarTokeInspector.new;
        var skoarmantics = Skoarmantics.new;

        var f = {
            | noad |
            var t = noad.toke;

            if (t.notNil) {
                var g = inspector[t.class.asSymbol];

                if (g.isKindOf(Function)) {
                    g.(this, noad, t);
                };
            } {
                var g = skoarmantics[noad.name];

                if (g.isKindOf(Function)) {
                    g.(this, noad);
                };
            };
        };

        tree.depth_visit(f);
    }

    // ----
    // misc
    // ----

    // creates a new one if needed
    get_voice {
        | k |

        var voice = nil;

        if (voices.includesKey(k)) {
            voice = voices[k];
        } {
            voice = SkoarKoar(this, k);
            voices[k] = voice;
        };

        ^voice;

    }

    cthulhu {
        | noad |

        // TODO more
        "^^(;,;)^^".postln;

        this.dump;

        "".postln;
        SkoarError("^^(;,;)^^").throw;

    }

    play {
        this.pskoar.play;
    }

    pskoar {
        ^Skoarchestra.new(this).pfunk;
    }

    pvoice {
        | voice_name |
        ^SkoarMinstrel.new(this.tree, voices[voice_name], this).pfunk;
    }

	json {
		var pf = Skoarchestra.new(this).pfunk;

		"[".postln;
		pf.do({
			| event | 
			"  { ".post;
			//event.play;

			event.keysValuesDo({
				| key, value | 
				("'" ++ key ++ "':'").post;
				value.printOn(Post, 2000);
				"', ".post;
			});
			"}, ".postln;
		});
		"]".postln;
		
	}

    draw_skoarpions {
        skoarpions.do {
            | x |
            x.post_tree;

            "Projections: ".postln;
            voices.keysDo {
                | koar_name |
                var projection = x.projection(koar_name);

				("\n --- Projection<" ++ koar_name ++">:").postln;
                projection.block.draw_tree.postln;
            };
        };
    }

    draw_skoarpions_string {
        var out = "";
        skoarpions.do {
            | x |
            out = out ++ x.draw_tree;

            out = out ++ "Projections: \n";
            voices.keysDo {
                | koar_name |
                var projection = x.projection(koar_name);

				out = out ++ ("\n --- Projection<" ++ koar_name ++">:\n") ++
                    projection.block.draw_tree;
            };
        };
        ^out;
    }


	one_less_running {
		mutex.wait;
		running = running - 1;
		mutex.signal;
	}

	sort_parser_desirables {
        SkoarParser.desirables.keysValuesDo {
            | k, v |
            SkoarParser.desirables[k] = v.sort({
                | a, b |
                a.freq > b.freq
            });
        };
	}

    // stats
    toke_stats {
        var x = SkoarToke.subclasses.copy;
        ("Toke Stats").postln;
        x.sort({
            | a, b |
            a.freq > b.freq
        }).do {
            | t |
            (t.asString ++ ": " ++ t.freq).postln;
        };
    }

    number_of_noads {
        ^this.number_of_noads_with({true})
    }

    number_of_noads_with {
        | f |
        var x = 0;
        tree.inorder_deep({
            | noad |
            if (f.(noad)) {
                x = x + 1
            };
        });

        ^x
    }

}


+String {
	skoar {
        ^Skoar(this);
    }

    pskoar {
        ^this.skoar.pskoar;
	}
}
