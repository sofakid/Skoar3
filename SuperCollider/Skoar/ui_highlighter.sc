
SkoarUiHighlighter {

    var editor;
    //var view;
    var log;
    var last_tree;
    var mutex;

    *new {
        | e, v |
        ^super.new.init(e, v);
    }

    init {
        | e, v |
        editor = e;
        //view = v;
        log = SkoarLogger("SkoarUiHighlighter");
        last_tree = nil;
        mutex = Semaphore(1);
    }

    syntax_highlight {
        | buffer |


        Routine({
            var skoarce;
            var chars;
            var skoar;
            var f;
            var x;

            mutex.wait;

            skoarce = buffer.string;
            chars = buffer.char_buf;
            //x = view.selectionStart;
            //view.string = skoarce;
            //view.select(x, 0);

            skoar = Skoar.new_for_highlighting(skoarce);
            //log.d("syntax_highlight", "skoar.parsed_ok", skoar.parsed_ok, "last_tree", last_tree);

            f = {
                | noad |
                var offs = noad.offs;
                if (noad.style.notNil) {
                    noad.size.do {
                        | i |
                        chars[offs + i].fg = noad.style;
                    };
                    //chars.setStringColor(noad.style, noad.offs, noad.size);
                    //0.wait;
                };
            };

            if (skoar.parsed_ok == true) {

                if (last_tree.isNil) {
                    skoar.tree.inorder(f);
                } {

                    skoar.tree.children.do {
                        | branch, branch_number |
                        if (last_tree.children.size <= branch_number) {
                            branch.inorder(f);
                        };

                        branch.line_diffs_visit(last_tree.children[branch_number], f);
                    };
                };


                last_tree = skoar.tree;

            };
            mutex.signal;
        }).play(AppClock);

    }
}