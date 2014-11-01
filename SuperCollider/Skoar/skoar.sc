// =====
// Skoar
// =====
Skoar {

    var   skoarse;      // the skoarse code
    var   parser;       // the parser
    var  <tree;         // root of tree
    var  <toker;        // toker
    var  <voices;       // all the voices
    var  <conductoar;

    *new {
        | code |
        ^super.new.init(code);
    }

    init {
        | code |

        skoarse = code;
        tree = nil;
        toker = Toker(skoarse);
        parser = SkoarParser.new(this);

        voices = IdentityDictionary.new;
        conductoar = SkoarKoar.new(this, \all);
        voices[\all] = conductoar;

    }

    parse {
        tree = parser.skoar(nil);

        try {
            toker.eof;
        } {
            | e |
            e.postln;
            toker.dump;
            e.throw;
        }
    }

    decorate {

        var inspector = SkoarTokeInspector.new;
        var skoarmantics = Skoarmantics.new;

        var f = {
            | noad |
            var t = noad.toke;

            if (t != nil) {
                var g = inspector[t.class.asSymbol];

                if (g.isKindOf(Function)) {
                    g.(noad, t);
                };
            } {
                var g = skoarmantics[noad.name];

                if (g.isKindOf(Function)) {
                    g.(this, noad);
                };
            };
        };

        tree.depth_visit(f);

        ">>> second pass...".postln;
        tree.voice = conductoar;
        tree.skoap = tree;

        tree.decorate_pass_two(conductoar, nil, [0]);
        "<<< second pass done.".postln;
    }

    // ----
    // misc
    // ----
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

    draw_skoarpions {
        tree.collect([\nouny]).do {
            | x |

            x = x.skoarpuscle;
            if (x.isKindOf(SkoarpuscleSkoarpion)) {
                x.val.post_tree;
            };
        };
    }

    draw_tree {
        "---< Skoar Tree >---".postln;
        tree.draw_tree.postln;
    }
}


+String {
	skoar {
        try {
            var r = Skoar.new(this++"\n");
            ">>> parsing skoar...".postln;
            r.parse;
            "<<< tree created, now decorating...".postln;
            //"---< Undecorated Skoar Tree >---".postln;
            //r.tree.draw_tree.postln;

            r.decorate;

            r.draw_tree;
            r.draw_skoarpions;
            "Skoar parsed.".postln;

            ^r;
        } {
            | e |
            e.postln;
            e.throw;
        }
    }

    pskoar {
        ^this.skoar.pskoar;
	}
}
