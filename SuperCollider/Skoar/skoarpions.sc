// The Skoarpion is our general purpose control structure.
Skoarpion {

    var skoar;
    var <name;
    var <n;

    var <body;
    var <stinger;

    var <args;

    *new {
        | skr, noad |
        ^super.new.init(skr, noad);
    }

    *new_from_skoar {
        | skr |
        ^super.new.init_from_skoar(skr);
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
        // 1 - sig
        sig = kids[1];
        // 2 - sep
        // 3 - suffix
        suffix = kids[3];

        sig.children.do {
            | x |
            case {x.skoarpuscle.isKindOf(SkoarpuscleSymbolName)} {
                name = x.skoarpuscle.val;
            } {x.name == \args} {
                args = x.skoarpuscle;
            };
        };

        "SIG: ".post; name.post; args.postln;

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
        if (sections.size == 1) {
            stinger = nil;
        } {
            stinger = SkoarNoad(\stinger);
            stinger.children = sections[1..];
        };

        n = body.size;

    }

    projection {
        | koar_name |
        ^SkoarpionProjection(this, koar_name);
    }

    post_tree {
        var s = if (name == nil) {
                    "anonymous"
                } {
                    name
                };

        debug("---< Skoarpion " ++ s ++ " >---");

        if (args != nil) {
            "args: ".post;

            args.val.do {
                | x |
                x.val.post; " ".post;
            };
            "".postln;
        };

        if (body != nil) {
            "body:".postln;
            body.draw_tree.post;
        };

        if (stinger != nil) {
            "stinger: ".postln;
            stinger.draw_tree.post;
        };

        "".postln;
    }
}

SkoarpionProjection {

    var <>i;
    var <>n;
    var body;
    var proj;
    var <skip_to;

    *new {
        | skrp, koar_name |
        ^super.new.init(skrp, koar_name);
    }

    init {
        | skrp, koar_name |
        var kids = skrp.body.children;
        i = -1;
        proj = SkoarNoad(\projection);

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
            };
        };

        n = proj.children.size;
        i = -1;
    }

    block {
        ^proj;
    }

    // this is returning noads
    selector {
        | f |
        i = f.value % n;
        ^proj.children[i];
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

    map_dst {
        | dst |
        var j = dst.address.pop;
        if (j == nil) {
            ^dst;
        };
        ^proj.children[skip_to[j]];
    }

}
