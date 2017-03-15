// ==========================
// The Parse Tree - SkoarNoad
// ==========================
SkoarNoad {

    var   address;         // a list code to find the noad quickly
    var <>parent;          // the parent noad
    var <>children;        // a list of child noads

    var <>name;            // name of the nonterminal (a \symbol)
    var <>skoarpuscle;     // skoarpuscle types go here
    var <>toke;

    var <>on_enter;

    var <>voice;           // what voice to use
    var <>skoap;           // what skoap are we in

	var tabby;

	var <>offs;
	var <>size;
	var <>style;

	var <>line;
	var <>line_number;
	var <>line_offs;
	var <>line_size;

	var <>subtree_hash;
	var <>line_hash;
    var log;

    *new {
        | name, parent=nil |
        ^super.new.init(name, parent);
    }

    init {
        | n, p |
        parent = p;
        name = n;
        children = List[];
        address = [];
		tabby = 0;
		skoarpuscle = nil;
		on_enter = nil;
		address = nil;
		voice = nil;
		skoap = nil;
		log = SkoarLogger(name);
    }

    asString {
        var ns = name.asString;

		if (skoarpuscle.notNil) {
			ns = ns ++ ": " ++ skoarpuscle.asString
		};
		^ns;
    }

    // here we return a copy, as whomever uses it is likely going to start
    // popping numbers off of it.
    address {
        ^Array.newFrom(address);
    }

    // -------------------
    // decorating the tree
    // -------------------
    decorate_zero {
        | v, s, parent_address, i=0 |

        if (voice.isNil) {
            voice = v;
        } {
            // the voice has changed, this is what the children get
            v = voice;
        };

		// this is the difference.
        address = [];
        skoap = s;

        i = 0;
        children.do {
            | y |
			//("blurg::"++v.name).postln;
            y.decorate(v, s, address, i);
            i = i + 1;
        };

    }

    decorate {
        | v, s, parent_address, i=0 |

        if (voice.isNil) {
            voice = v;
        } {
            // the voice has changed, this is what the children get
            v = voice;
        };

        address = [i] ++ parent_address;
        skoap = s;

        i = 0;
        children.do {
            | y |
            y.decorate(v, s, address, i);
            i = i + 1;
        };

    }

    // ----------------
    // growing the tree
    // ----------------
    add_noad {
        | noad |
        children = children.add(noad);
    }

    add_toke {
        | name, t |
        var x = SkoarNoad(name, this);
        x.toke = t;

        children = children.add(x);
    }

    // ----------------
    // showing the tree
    // ----------------
    draw_tree {
        | tab = 1 |
        var n = 16;
        var s;
        var sa = skoap.asString ++ ":";
        var sv;

        address.reverseDo {
            | x |
            sa = sa ++ x.asString ++ ";";
        };

        sv = if (voice.notNil) {
                voice.name.asString.padLeft(n) ++ ":"
             } {
                ":".padLeft(n + 1)
             };

        s = sa.padRight(n) ++ sv ++ " ".padLeft(tab) ++ name;

        if (skoarpuscle.notNil) {
            s = s ++ ": " ++ skoarpuscle.val;
        };

        s = s ++ "\n";
        children.do {
            | x |
            s = if (x.isKindOf(SkoarNoad)) {
                    s ++ x.draw_tree(tab + 1)
                } {
                    s ++ " ".padLeft(tab + 1) ++ x.class.asString ++ "\n"
                };
        };

        ^s;
    }

    // -----------------
    // climbing the Tree
    // -----------------

    // depth-first, find the leaves, run handler, working towards trunk
    //
    // if it's crashing during the decorating stage, here's a good place to
    // start debugging
    depth_visit {
        | f |
        //var s = " " ++ if (toke.notNil) {toke.lexeme} {""};
        //debug(">>> depth_visit: " ++ name ++ s);

        children.do {
            | y |
            y.depth_visit(f);
        };

        //debug("--- depth_visit: " ++ name ++ s);

        // note: leaves first
        f.(this);

        //debug("<<< depth_visit: " ++ name ++ s);
    }

    inorder {
        | f, tabby=0 |

		tabby = tabby + 2;
		
        //debug(" ".padLeft(tabby) ++ "### ::  " ++ name);
        
        f.(this);

        children.do {
            | y |
            y.inorder(f, tabby);
        };

        //debug( " ".padLeft(tabby) ++ "<<< inorder: " ++ name);
		tabby = tabby - 2;
		
    }

    inorder_before_after {
        | before, after |

        before.(this);

        children.do {
            | y |
            y.inorder_before_after(before, after);
        };

        after.(this);


    }

    diffs_visit {
        | other, f |
        var oc;
        var ocz;
        var osh;

        if (other.notNil) {
            oc = other.children;
            ocz = oc.size;
            osh = other.subtree_hash;
        } {
            oc = nil;
            ocz = -1;
            osh = 0;
        };

        if (osh != subtree_hash) {
            //log.d("f.(this), inordering");
            f.(this);
            children.do {
                | y |
                y.inorder(f);
            };
        } {
            children.do {
                | y, i |
                var oy;

                if (i >= ocz) {
                    //log.d("inorder the rest");
                    y.inorder(f);
                } {
                    oy = oc[i];
                    if (oy.subtree_hash != y.subtree_hash) {
                        //log.d("descending");
                        y.diffs_visit(oy, f);
                    } {
                        //log.d("not descending");
                    };
                };
            };
        };
    }

    line_diffs_visit {
        | other, f |
        var oc;
        var ocz;
        var osh;
        var olh;

        if (other.notNil) {
            oc = other.children;
            ocz = oc.size;
            osh = other.subtree_hash;
            olh = other.line_hash;
        } {
            oc = nil;
            ocz = -1;
            osh = 0;
            olh = 0;
        };

        //log.d("noad", "line_size", line_size, "line_hash", line_hash);
        if (olh != line_hash) {
            //log.d("f.(this), inordering");
            f.(this);
            children.do {
                | y, i |
                y.inorder(f);
            };
        } {
            children.do {
                | y, i |
                var oy;

                if (i >= ocz) {
                    //log.d("inorder the rest");
                    y.inorder(f);
                } {
                    oy = oc[i];
                    if (oy.subtree_hash != y.subtree_hash) {
                        //log.d("descending");
                        y.line_diffs_visit(oy, f);
                    } {
                        //log.d("not descending");
                    };
                };
            };
        };

    }


    // debug here if it's crashing while performing the skoar
    inorder_from_here {
        | here, f |
        var j = here.pop;
        var n = children.size - 1;

        //debug("inorder_from_here: j:" ++ j ++ " " ++ name);

        if (j.isNil) {
            this.inorder(f);
        } {
            children[j].inorder_from_here(here, f);

            j = j + 1;
            if (j <= n) {
                for (j, n, {
                    | k |
                    children[k].inorder(f);
                });
            };
        };
    }

    inorder_deep {
        | f |
        this.inorder({
            | noad |
            var skoarpuscle = noad.skoarpuscle;
            var x;

            f.(noad);

            case {skoarpuscle.isKindOf(SkoarpuscleSkoarpion)} {
                skoarpuscle.val.body.inorder_deep(f);

            } {skoarpuscle.isKindOf(SkoarpuscleMeditation)} {
                skoarpuscle.skoarpion.body.inorder_deep(f);

            } {skoarpuscle.isKindOf(SkoarpuscleLoop)} {
                skoarpuscle.body.body.inorder_deep(f);
                x = skoarpuscle.condition;
                if (x.notNil) {
                    x.body.inorder_deep(f);
                };

            } {skoarpuscle.isKindOf(SkoarpuscleLoopMsg)} {
                skoarpuscle.val.body.body.inorder_deep(f);
                x = skoarpuscle.val.condition;
                if (x.notNil) {
                    x.body.inorder_deep(f);
                };

            } {skoarpuscle.isKindOf(SkoarpuscleConditional)} {
                skoarpuscle.ifs.do {
                    | y |
                    y.body.inorder_deep(f);
                };
            };

        });
    }

    // expect skoarpuscle
    next_skoarpuscle {
        var x;

        if (skoarpuscle.notNil) {
            ^skoarpuscle;
        };

        x = children[0];

        if (x.notNil) {
            ^x.next_skoarpuscle;
        };

        ^nil;
    }

    next_toke {
        var x;

        if (toke.notNil) {
            ^toke;
        };

        x = children[0];

        if (x.notNil) {
            ^x.next_toke;
        };

        ^nil;
    }

    // -------------------
    // performing the tree
    // -------------------
    enter_noad {
        | minstrel, nav |

        if (on_enter.notNil) {
            on_enter.(minstrel, nav);
        };

		if (skoarpuscle.notNil and: skoarpuscle.respondsTo(\on_enter)) {
			skoarpuscle.on_enter(minstrel, nav);
		};
    }

	evaluate {
		| minstrel, nav |
		this.inorder({
			| x |
			x.enter_noad(minstrel, nav); }
		);
	}

    // ------------------
    // searching the tree
    // ------------------

    // desires - array of names of noads as symbol, or SkoarToke implementation classes
    // writer - a function that will do something with the matches
    match {
        | desires, writer |

        desires.do {
            | item |

            if (item == name) {
                writer.(this);
            };
        };
    }

    collect {
        | desires |

        var results = List.new;

        this.depth_visit({
            | x |
            x.match(desires, {
                | y |
                results.add(y);
            });
        });

        ^results.asArray;
    }

    collect_skoarpuscles {
        | j=0 |

        var results = List.new;
        while {j < children.size} {

            children[j].inorder({
                | x |
                if (x.skoarpuscle.notNil) {
                    //debug("found skoarpuscle: " ++ x.skoarpuscle.asString);
                    results.add(x.skoarpuscle);
                };
            });

            j = j + 1;
        };
        ^results.asArray;

    }

    find_last_child {
        var n = children.size;

        if (n > 0) {
            ^children[n-1].find_last_child
        };

        ^this;
    }

}



