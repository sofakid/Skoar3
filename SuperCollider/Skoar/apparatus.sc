
// ==========================
// The Parse Tree - SkoarNoad
// ==========================
SkoarNoad {

    var  address;         // a list code to find the noad quickly
    var <>parent;          // the parent noad
    var <>children;        // a list of child noads

    var <>evaluate;        // pass functions between skoarmantic levels here
    var <>setter;          // pass functions between skoarmantic levels here

    var <>name;            // name of the nonterminal
    var <>skoarpuscle;     // skoarpuscle types go here
    var <>toke;

    var <>performer;       // function to set when defining semantics.
    var <>one_shots;       // function to set for stuff that applies for one beat.

    var <>voice;           // what voice to use
    var <>skoap;           // what skoap are we in

    *new {
        | name, parent=nil |
        ^super.new.init(name, parent);
    }

    init {
        | nameArg, parentArg |

        parent = parentArg;
        name = nameArg;

        children = List[];
        address = [];
    }

    asString {
        ^name.asString;
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

        if (voice == nil) {
            voice = v;
        } {
            // the voice has changed, this is what the children get
            v = voice;
        };

        address = [];
        skoap = s;

        i = 0;
        children.do {
            | y |
            y.decorate(v, s, address, i);
            i = i + 1;
        };

    }

    decorate {
        | v, s, parent_address, i=0 |

        if (voice == nil) {
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
        children.add(noad);
    }

    add_toke {
        | name, t |
        var x = SkoarNoad(t.class.name, this);
        x.toke = t;
        children.add(x);
    }

    // ----------------
    // showing the tree
    // ----------------
    draw_tree {
        | tab = 1 |
        var n = 16;
        var s;
        var sa = ":";
        var sv;

        address.reverseDo {
            | x |
            sa = sa ++ x.asString ++ ";";
        };

        sv = if (voice != nil) {
                voice.name.asString.padLeft(n) ++ ":"
            } {
                ":".padLeft(n+1)
            };

        s = sa.padRight(n) ++ sv ++ " ".padLeft(tab) ++ name;

        if (skoarpuscle != nil) {
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
        //var s = " " ++ if (toke != nil) {toke.lexeme} {""};
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
        | f, stinger=nil |

        //debug(">>> inorder: " ++ name);
        if ((stinger != nil) && skoarpuscle.isKindOf(SkoarpuscleBeat)) {
            //debug("!!! stinger: " ++ stinger.asString);
            stinger.inorder(f);
        };

        f.(this);

        children.do {
            | y |
            y.inorder(f, stinger);
        };

        //debug("<<< inorder: " ++ name);
    }

    // debug here if it's crashing while performing the skoar
    inorder_from_here {
        | here, f, stinger |
        var j = here.pop;
        var n = children.size - 1;

        //debug("inorder_from_here: j:" ++ j ++ " " ++ name);

        if (j == nil) {
            this.inorder(f, stinger);
        } {
            children[j].inorder_from_here(here, f, stinger);

            j = j + 1;
            if (j <= n) {
                for (j, n, {
                    | k |
                    children[k].inorder(f, stinger);
                });
            };
        };
    }

    // this finds the preceding noad
    prev_noad {
        var i = address[address.size-1];

        // are we leftmost sibling?
        if (i == 0) {
            if (parent == nil) {
                ^nil;
            };

            ^parent.prev_noad;
        };

        // return sibling to left
        ^parent.children[i-1];
    }

    // expect skoarpuscle
    next_skoarpuscle {
        var x;

        if (skoarpuscle != nil) {
            ^skoarpuscle;
        };

        x = children[0];
        if (x != nil) {
            ^x.next_skoarpuscle;
        };

        ^nil;
    }

    next_toke {
        var x;

        if (toke != nil) {
            ^toke;
        };

        x = children[0];
        if (x != nil) {
            ^x.next_toke;
        };

        ^nil;
    }

    // -------------------
    // performing the tree
    // -------------------
    perform {
        | minstrel, nav |

        if (performer != nil) {
            performer.(minstrel, nav);

        };

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
                if (x.skoarpuscle != nil) {
                    //debug("found skoarpuscle: " ++ x.skoarpuscle.asString);
                    results.add(x.skoarpuscle);
                };
            });

            j = j + 1;
        };
        ^results.asArray;

    }


}



