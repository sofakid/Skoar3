
SkoarUiEditorLanguage {
    *skoar {^\skoar}
    *supercollider {^\supercollider}
    *plain {^\plain}
    *sclog {^\sclog}
}

SkoarUiBuffer {

    classvar untitled_i = 0;

    var <buf;
    var <char_buf;
    var <name;
    var <id;
    var file;
    var <editor;
    var language;
    var pos;
    var log;
    var newlines;

    *next_untitled {
        ^untitled_i = untitled_i + 1;
    }

    *new {
        | ... args |
        ^super.new.init(*args);
    }

    init {
        | nom, ed |
        editor = ed;
        buf = List[];
        char_buf = List[];
        newlines = SortedList[];

        if (nom.isNil) {
            name = "untitled";
            id = (name ++ SkoarUiBuffer.next_untitled).asSymbol;
        } {
            name = nom;
            id = nom.asSymbol;
        };

        file = "";
        language = SkoarUiEditorLanguage.skoar;
        pos = 0;
        log = SkoarLogger("SkoarUiEditorBuffer");

        this.insert_char($\n);
        pos = 0;
    }

    set_file {
        | filename |
        file = filename;
    }

    size {
        ^buf.size;
    }

    string {
        ^String.newFrom(buf);
    }

    clear {
        buf = List[];
        char_buf.do {
            | x |
            x.remove;
        };
        char_buf = List[];
        newlines = SortedList[];
        pos = 0;
    }

    update_range {
        | s, start, end |
    }

    remove_range {
        | start, end |
    }

    insert_char {
        | c |
        var char;
        var last_char;

        if (pos > 0) {
            last_char = char_buf[pos - 1];
        };

        if (c == $\n) {
            char = SkoarUiNewlineChar(c, this, last_char);
            this.incr_newlines;
            newlines.add(pos);
            //log.i("newlines", this.newlines, "line_sizes", this.line_sizes);
        } {
            char = SkoarUiChar(c, this, last_char);
            this.incr_newlines;
        };

        //log.d("I have", c.ascii, $\n.ascii, $\r.ascii, char.class.asString);
        buf.insert(pos, c);
        char_buf.insert(pos, char);
        pos = pos + 1;

        ^char
    }

    incr_newlines {
        var x = 0;
        var n = newlines.size;

        n.do {
            | i |
            x = newlines[i];
            if (x >= pos) {
                newlines[i] = x + 1;
            };
        };

    }

    line_sizes {
        var out = List[];
        var x = -1;

        newlines.do {
            | p |
            out.add(p - x);
            x = p;
        };

        ^out;
    }

    newlines {
        ^newlines.asArray;
    }


    delete_at_pos {
        var c, x, v;
        if (pos < buf.size) {
            c = buf.removeAt(pos);
            //char_buf[pos].remove;
            v = char_buf.removeAt(pos);

            v.remove;

            if (c === $\n) {
                newlines.remove(pos);
            };

            newlines.size.do {
                | i |
                x = newlines[i];
                if (x > pos) {
                    newlines[i] = x - 1;
                };
            };

            newlines.sort;
        };
    }

    delete_char_before {
        if (pos > 0) {
            //log.d("delete_char_before", "pos", pos, "next", pos - 1);
            pos = pos - 1;
            this.delete_at_pos;
        }
    }

    delete_char_after {
        if (pos < buf.size) {
            this.delete_at_pos;
        };
    }

    delete_range {
        | from, size |
        //var s = List[];
        pos = from.pos;

        size.do {
            //s.add(buf[pos]);
            this.delete_at_pos;
        };

        //log.d("Deleting range", String.newFrom(s));
    }

    save_file {
        var f;

        if (file.isNil) {
            log.e("Filename is nil.");
            ^this;
        };

        try {
            f = File.open(file, "w");
            f.write(String.newFrom(buf));
            f.close;
        } {
            | e |
            log.e("Error saving file.", e.errorString);
        };

    }

    load_file_with_view {
        | view, on_complete |
        var file_mode = 0;
        var accept_mode = 0;
        var f;

        FileDialog.new({
            | ... paths |
            var s;
            file = paths[0];
            name = PathName(file).fileName.asSymbol;

            f = File.open(file, "r");
            s = f.readAllString;
            f.close;

            // textview cleans or otherwise corrupts the string.
            // (for instance, line endings)
            // we load the buffer from the view.
            view.string = s;
            buf = List.newFrom(view.string);

            on_complete.(this);

        }, {}, file_mode, accept_mode, true);

    }

    load_file {
        | on_complete |
        var file_mode = 0;
        var accept_mode = 0;
        var f;
        var last_char;
        var x;

        FileDialog.new({
            | ... paths |
            var s;
            var n;
            file = paths[0];
            name = PathName(file).fileName.asSymbol;

            f = File.open(file, "r");
            s = f.readAllString;
            f.close;

            s = s.replace("\r","");
            n = s.size;
            buf = List.newFrom(s);
            char_buf = List.new(n);
            newlines = SortedList[];
            buf.do {
                | c, p |
                if (c == $\n) {
                    x = SkoarUiNewlineChar(c, this, last_char);
                    char_buf.add(x);
                    newlines.add(p);
                    last_char = x;
                } {
                    x = SkoarUiChar(c, this, last_char);
                    char_buf.add(x);
                    last_char = x;
                };
            };

            buf.add($\n);
            char_buf.add(SkoarUiNewlineChar($\n, this, last_char));
            newlines.add(n);

            on_complete.(this);

        }, {}, file_mode, accept_mode, true);

    }

    to_view {
        | v |
        //v.string = String.newFrom(buf);
    }

    from_view {
        | v |
        //buf = List.newFrom(v.string);
    }

    move_to {
        | p |
        pos = p;
    }

    recreate_views {
        | parent |
        char_buf.do {
            | c |
            c.recreate_view(parent);
        };
    }

    char_range_do {
        | start, end, f |
        for (start, end, {
            | i |
            var x = char_buf[i];
            if (x.notNil) {
                f.(x);
            };
        });
    }
}

SkoarUiBufferPile : SkoarUiView {

    var pile;
    var active;
    var list;
    var editor;



    init {
        | ed |
        editor = ed;
        pile = IdentityDictionary();
        list = SkoarUiListView("buffers", Color.grey(0), Color.gray(0.3));
        view = list.view;
    }

    new_buffer {
        | name |
        var b = SkoarUiBuffer(name, editor);
        var id = b.id;
        pile[id] = b;

        list.add_option(id, SkoarUiButton(b.name, Color.cyan(0.73), Color.black, Color.grey(0.5), {
            editor.choose_buffer(id);
        }));

        ^b
    }

    refresh_buffer_name {
        | id |
        list.rename_option(id, pile[id].name);
    }

    kill_buffer {
        | name |
        pile[name] = nil;
        list.remove_option(name);
    }

    select_buffer {
        | id |
        list.select_option(id);
        ^pile[id];
    }


}