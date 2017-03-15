Skoarpion {

    var skoar;
    var <name;
    var <n;

    var <body;

    var <arg_list;

    *new {
        | skr, noad |
        ^super.new.init(skr, noad);
    }

    *new_from_skoar {
        | skr |
        ^super.new.init_from_skoar(skr);
    }

    *new_from_subtree {
        | skr, subtree |
        ^super.new.init_from_subtree(skr, subtree);
    }

    init_from_skoar {
        | skr |
        name = \skoar;
        body = SkoarNoad(\section);

        skoar = skr;
        skoar.skoarpions.add(this);

        skoar.tree.children.do {
            | line |
            var i = 0;
            var v = line.next_skoarpuscle;

            if (v.isKindOf(SkoarpuscleVoice)) {
                line.voice = skoar.get_voice(v.val);
            };

            if (line.children.size != 0) {
                body.add_noad(line);
            };
        };

        body.decorate_zero(skoar.all_voice, body, [], 0);
        n = body.size;
    }

    init_from_subtree {
        | skr, subtree |
        name = nil;

        skoar = skr;
        skoar.skoarpions.add(this);

        body = subtree;

        subtree.children.do {
            | line |
            var v = line.next_skoarpuscle;

            if (v.isKindOf(SkoarpuscleVoice)) {
                line.voice = skoar.get_voice(v.val);
				//(" VOICE :: " ++ line.voice).postln;
            };

        };

        subtree.decorate_zero(skoar.all_voice, subtree, [], 0);
        n = subtree.size;
    }

	/*                          :      skoarpion
nil:                            :       Toke_SkoarpionStart
nil:                            :       skrp_sig
nil:                            :       skrp_suffix
nil:                            :        beat
nil:                            :         Toke_Eighths
nil:                            :        Toke_SkoarpionEnd
*/
    init {
        | skr, noad |
        var kids = noad.children;
        var sig, suffix;
        var i = 0;
        var line = SkoarNoad(\line);
        var section = SkoarNoad(\section);
        var sections = List[];

        skoar = skr;
        skoar.skoarpions.add(this);

        // 0 - start
        // 1 - sig or suffix
        sig = kids[1].skoarpuscle;

		if (sig.isKindOf(SkoarpuscleSkoarpionSig)) {
			name = sig.name;
			arg_list = sig.arg_list;
			suffix = kids[2];
		} {
			suffix = kids[1];
		};
        
        //("SIG: " ++ name ++ " args: " ++ arg_list).postln;

        suffix.children.do {
            | x |
            var process_line = {
                var v = line.next_skoarpuscle;
                if (v.isKindOf(SkoarpuscleVoice)) {
                    line.voice = skoar.get_voice(v.val);
                };

                if (line.children.size != 0) {
                    section.add_noad(line);
                };

            };

            case {x.toke.isKindOf(Toke_SkoarpionSep)} {
                process_line.();
                sections.add(section);

                section = SkoarNoad(\section);
                line = SkoarNoad(\line);

            } {x.toke.isKindOf(Toke_Newline)} {

                process_line.();
                line = SkoarNoad(\line);

            } {x.toke.isKindOf(Toke_SkoarpionEnd)} {

                process_line.();
                sections.add(section);
            } {
                line.add_noad(x);
            };

        };

        sections.do {
            | sec |
            var i = 0;
            sec.decorate_zero(skoar.all_voice, sec, [], i);
        };

        body = sections[0];        
        n = body.size;
    }

    projection {
        | koar_name |
        ^SkoarpionProjection(this, koar_name);
    }

    post_tree {
        var s = name ?? "anonymous";

        debug("---< Skoarpion " ++ s ++ " >---");

        if (arg_list.notNil) {
            "arg_list: ".post; arg_list.postln;

            arg_list.val.do {
                | x |
                if (x.isKindOf(Skoarpuscle)) {
                    x.val.post; " ".post;
                } {
                    x.post; " ".post;
                };
            };
            "".postln;
        };

        if (body.notNil) {
            "body:".postln;
            body.draw_tree.post;
        };

        "".postln;
    }

    draw_tree {
        var s = name ?? "anonymous";

        var out = "---< Skoarpion " ++ s ++ " >---\n";

        if (arg_list.notNil) {
            out = out ++ "arg_list: " ++ arg_list ++ "\n";

            arg_list.val.do {
                | x |
                if (x.isKindOf(Skoarpuscle)) {
                    out = out ++ x.val ++ " ";
                } {
                    out = out ++ x ++ " ";
                };
            };
            out = out ++ "\n";
        };

        if (body.notNil) {
            out = out ++ "body:\n" ++ body.draw_tree;
        };

        ^out ++ "\n";
    }
}

/*
nil:                            :        skrp_sig
nil:                            :         Toke_SymbolName
nil:                            :         arg_listy
nil:                            :          Toke_ListS
nil:                            :          arg_expr
nil:                            :           Toke_SymbolName
nil:                            :          Toke_ListSep
nil:                            :          arg_expr
nil:                            :           Toke_SymbolColon
nil:                            :           expr
*/
SkoarpuscleSkoarpionSig : Skoarpuscle {

	var <name;
	var <arg_list;
	
	init {
		| noad |
		var x = noad.children[0].skoarpuscle;

		//x.dump;
		
		if (x.isKindOf(SkoarpuscleSymbolName)) {
			name = x.val;
			x = noad.children[1].skoarpuscle;
			//("SIG::: name: " ++ name).postln;
		};
			
		if (x.isKindOf(SkoarpuscleArgList)) {
			arg_list = x;
		};
	}
}

/*
nil:                            :          arg_expr
nil:                            :           Toke_SymbolName
nil:                            :          Toke_ListSep
nil:                            :          arg_expr
nil:                            :           Toke_SymbolColon
nil:                            :           expr
*/
SkoarpuscleArgExpr : Skoarpuscle {

	var <name;
	var <expr;

	init {
		| noad |
		var x = noad.next_skoarpuscle;

		name = x.val;
		//("ARG EXPR :: name: " ++ name).postln;
		
		if (noad.children.size > 0) {
			expr = SkoarpuscleExpr(noad.children[1]);
		};
	}
}

/*
nil:                            :         arg_listy
nil:                            :          Toke_ListS
nil:                            :          arg_expr
nil:                            :          Toke_ListSep
nil:                            :          arg_expr
*/
SkoarpuscleArgList : SkoarpuscleList {

	var <args_dict;
	var <args_names;
	
	isNoatWorthy { ^false; }
	asNoat {}
	skoar_msg {"What?".postln;}

	init {
		| noad |
		args_dict = ();
		args_names = [];

		noad.collect_skoarpuscles.do {
			| x |
			
			//("SkoarpuscleArgList:: x:" ++ x).postln; 
			if (x.isKindOf(SkoarpuscleArgExpr)) {
				args_dict[x.name] = x.expr;
				args_names = args_names.add(x.name);
			};
		};
		//("SkoarpuscleArgList:: args_names:" ++ args_names).postln; 
		
	}

	on_enter {
		| m, nav |
		m.fairy.push_noating;
		m.fairy.push;
	}
	
}
	



SkoarIteratoar {
    var arr;
    var <>i;
    var <>n;

    init_iter {
        | a |
        arr = a;
        n = a.size;
        i = -1;
    }

    // this is returning noads
    selector {
        | f |
        i = f.value % n;
        ^arr[i];
    }

    at {
        | j |
        ^this.selector({j});
    }

    choose {
        ^this.selector({n.rand});
    }

    wchoose {
        | weights |
        ^this.selector({weights.val.windex});
    }

    next {
        ^this.selector({1 + i});
    }

    last {
        ^this.selector({i - 1});
    }
}

SkoarpionProjection : SkoarIteratoar {

    var body;
    var proj;
    var <skip_to;
	var <name;

    *new {
        | skrp, koar_name |
        ^super.new.init(skrp, koar_name);
    }

    init {
        | skrp, koar_name |
        var kids = skrp.body.children;
        i = -1;
        proj = SkoarNoad(\projection);
		name = koar_name;

        // map indexes in skoap to indexes in this projection
        skip_to = Array.newClear(kids.size);
        kids.do {
            | x |
            var s = x.voice.name;
            if ((s == koar_name) || (s == \all)) {
                var addr = x.address;
                var m = addr.size;

                i = i + 1;
                if (m > 0) {
                    skip_to[addr[m-1]] = i;
                };

                // don't use add_noad, it corrupts noad.
                proj.children.add(x);
                proj.skoap = x.skoap;
            };
        };

        this.init_iter(proj.children);
    }

    block {
        ^proj;
    }

    inline {
        ^proj;
    }

	meditation {
		//("meditating projection: " ++ name).postln; 
		^proj;
	}

    map_dst {
        | dst |
        var addr = dst.address.copyToEnd(0);
        var j = addr.pop;

        if (j.isNil) {
            ^addr;
        };

        ^(addr ++ skip_to[j]);
    }

}
