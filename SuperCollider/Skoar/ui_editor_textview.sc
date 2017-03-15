
SkoarUiTextViewEditor : SkoarUiView {

    var top_panel;
    var left_panel;
    var text;
    var <matrix;
    var <buffers;
    var buffers_menu;
    var buffer;
    var output;
    var status_bar;
    var ui;
    var mutex;

    var <highlighter;

    var highlight_timer;

    init {
        | parent |
        var text_view;

        ui = parent;
        view = View();

        top_panel = SkoarUiEditorTopPanel(this);
        buffers = SkoarUiBufferPile(this);
        left_panel = SkoarUiEditorLeftPanel(this);

        buffer = buffers.new_buffer('scratch', this);

        text = SkoarUiTextView();
        text_view = text.view;

        //output = SkoarUiTextView();
        status_bar = SkoarUiStatusBar();
        layout = HLayout(
            VLayout(
                left_panel.view
            ),

            [VLayout(
                top_panel.view,
                text_view,
                //output.view,
                status_bar.view
            ), stretch:1]
        );

        status_bar.view.mouseUpAction = {
            this.toggle_log;
        };

        highlighter = SkoarUiHighlighter(this, text.view);
        //output.view.editable = false;
        mutex = Semaphore(1);
        highlight_timer = -1;

        text_view.mouseUpAction = {
            | v, x, y, mod, button_number, click_count |
            var p, q, pp, qq;
            p = text_view.selectionStart;
            q = text_view.selectionSize;
            log.d("mouseUpAction", "selectionStart", p, "selectionSize", q);
            buffer.move_to(text_view.selectionStart);

            pp = buffer.string[p..(p+q)];
            qq = text_view.string[p..(p+q)];

            log.d("buffer    |", pp, "|");
            log.d("text_view |", qq, "|");

        };


        TextView.globalKeyUpAction = {
            | v, char, mod, unicode, keycode, key |
            //log.i("TextView.globalKeyUpAction", "mod", mod, "key", key);

            if (mod.isCtrl or: {mod.isCmd}) {
                if (char == $.) {
                    // reload view
                    buffer.to_view(text_view);
                };
            };
        };

        TextView.globalKeyDownAction = {
            | v, char, mod, unicode, keycode, key |
            //log.i("TextView.globalKeyDownAction", "mod", mod, "key", key);

            if (mod.isCtrl or: {mod.isCmd}) {
                if ((key == SkoarUiCodes.key['Enter']) or:
                    {key == SkoarUiCodes.key['Return']}) {
                        this.skoar_play;
                };
            };

            if (key == SkoarUiCodes.key['MediaPlay']) {
                this.skoar_play;
            };

            if (key == SkoarUiCodes.key['MediaStop']) {
                this.skoar_stop;
            };

        };

        text_view.keyUpAction = {
            | v, char, mod, unicode, keycode, key |
            var should_highlight = false;
            //buffer.move_to(text_view.selectionStart);

            if (mod.isCtrl or: {mod.isAlt} or: {mod.isCmd} ) {
                if (SkoarUiCodes.key_one_of(key, 'V', 'X', 'Z')) {
                    // reload whole stupid thing. todo: improve
                    buffer.from_view(text_view);
                    should_highlight = true;
                };
            };

            if (SkoarUiCodes.key_one_of(key, 'Delete', 'Backspace')) {
                should_highlight = true;
            };

            if (char.notNil and: {char.isPrint}) {
                should_highlight = true;
            };

            if (should_highlight) {
                // reload whole stupid thing. todo: improve
                //buffer.from_view(text_view);
                this.syntax_highlight;
            };
        };


        text_view.keyDownAction = {
            | v, char, mod, unicode, keycode, key |
            //log.i("keyDownAction", "mod", mod, "key", key);

            if (mod == 0) {
                if (key == SkoarUiCodes.key['Backspace']) {
                    log.d("backspace", "selectionStart", text_view.selectionStart,
                        "selectionSize", text_view.selectionSize);

                    if (text_view.selectionSize == 0) {
                        buffer.delete_char_before;
                    } {
                        buffer.delete_range(text_view.selectionStart, text_view.selectionSize);
                    }
                };

                if (key == SkoarUiCodes.key['Delete']) {

                    if (text.view.selectionSize == 0) {
                        buffer.delete_char_after;
                    } {
                        buffer.delete_range(text_view.selectionStart, text_view.selectionSize);
                    }
                };
            };

            if (char.notNil) {
                if (mod.isCtrl.not and: {mod.isAlt.not} and: {mod.isCmd.not}) {

                    if (char.isSpace or: {char.isPrint}) {
                        if (text_view.selectionSize > 0) {
                            buffer.delete_range(text_view.selectionStart, text_view.selectionSize);
                        };
                        buffer.insert_char(char);
                    };
                };
            };

        };


        view.layout = layout;
    }

    delete_random {
        var n = buffer.size / 2;
        var p = n.rand;
        var q = n.rand;

        buffer.delete_range(p, q);
        matrix.repack;

    }

    update_cursor {
        buffer.move_to(text.view.selectionStart);
    }

    move_cursor_to {
        | pos |
        buffer.move_to(pos);
    }

    syntax_highlight {
        highlighter.syntax_highlight(buffer);
    }

    skoar_play {
        var x = buffer.string;
        x.skoar.play;
    }

    skoar_stop {
        var x = buffer.string;
        x.skoar.play;
    }

    log_buf {
        log.d(buffer.string)
    }

    load_file {
        buffer.load_file({
            | buf |
            buffers.select_buffer(buf.id);
            buffers.refresh_buffer_name(buf.id);
            matrix.load_buffer(buf);
            this.syntax_highlight;
        });
    }

    save_file {
        buffer.save_file;
    }

    new_buffer {
        buffer = buffers.new_buffer();
        buffer.to_view(text.view);
        buffers.select_buffer(buffer.id);
        this.syntax_highlight;
    }

    choose_buffer {
        | id |
        buffer = buffers.select_buffer(id);
        buffer.to_view(text.view);
        this.syntax_highlight;
    }

    toggle_log {
        ui.toggle_log;
    }

}


SkoarUiTextView : SkoarUiView {

    var palette;

    init {
        view = TextView();

        view.minHeight = 200;
        view.minWidth = 200;

        palette = QPalette.new;

        palette.window = Color.grey(0);
        palette.base = Color.grey(0);
        palette.baseText = Color.grey(0.7);
        palette.highlight = Color.cyan(0.6);
        palette.highlightText = Color.black;

        view.editable = false;
        view.palette = palette;
        view.font = Font("Consolas", 20);
        view.enterInterpretsSelection = false;
    }
}

