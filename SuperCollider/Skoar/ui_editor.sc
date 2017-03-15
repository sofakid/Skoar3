
SkoarUiEditor : SkoarUiView {

    var top_panel;
    var left_panel;
    var <textoar;
    var <buffers;
    var buffers_menu;
    var <buffer;
    var output;
    var status_bar;
    var ui;
    var mutex;

    var <highlighter;

    var highlight_timer;

    init {
        | parent |
        var textoar_view;

        ui = parent;
        view = View();

        top_panel = SkoarUiEditorTopPanel(this);
        buffers = SkoarUiBufferPile(this);
        left_panel = SkoarUiEditorLeftPanel(this);

        buffer = buffers.new_buffer('scratch', this);

        textoar = SkoarUiTextoar(this, buffer);
        textoar_view = textoar.view;
        //output = SkoarUiTextView();
        status_bar = SkoarUiStatusBar();
        layout = HLayout(
            VLayout(
                left_panel.view
            ),

            [VLayout(
                top_panel.view,
                textoar_view,
                //textoar_view,
                //output.view,
                status_bar.view
            ), stretch:1]
        );

        status_bar.view.mouseUpAction = {
            this.toggle_log;
        };

        highlighter = SkoarUiHighlighter(this, textoar.view);
        //output.view.editable = false;
        mutex = Semaphore(1);
        highlight_timer = -1;

        view.keyDownAction = {
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

        view.layout = layout;

        textoar.load_buffer(buffer);
    }

    move_buffer_to_coords {
        | coords |
        buffer.move_to(coords.pos);
    }

    syntax_highlight {
        //this.test_buffers_same;
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
            textoar.load_buffer(buf);
            this.syntax_highlight;
        });
    }

    save_file {
        buffer.save_file;
    }

    new_buffer {
        buffer = buffers.new_buffer();
        //buffer.to_view(textoar.view);
        textoar.load_buffer(buffer);
        buffers.select_buffer(buffer.id);
        this.syntax_highlight;
    }

    choose_buffer {
        | id |
        buffer = buffers.select_buffer(id);
        //buffer.to_view(textoar.view);
        //buffer.recreate_views();
        textoar.load_buffer(buffer);
        this.syntax_highlight;
    }

    toggle_log {
        ui.toggle_log;
    }

    test_buffers_same {
        ^SkoarUiTesting_Textoar(textoar).buffers_are_same;
    }

    test_deleting {
        var testing = SkoarUiTesting_Textoar(textoar);
        var pass = true;

        Routine({
            while {pass == true and: {buffer.size > 0}} {
                pass = testing.test_delete;
                0.wait;
            };

        }).play(AppClock);
    }

    test_many_deletes {
        var testing = SkoarUiTesting_Textoar(textoar);
        var pass = true;

        Routine({
            var loops = buffer.size + 50;
            var i = 0;

            while {pass == true and: {loops > 0}} {
                    loops = loops - 1;
                    pass = case {2.rand == 0} {
                        testing.test_delete_key_backspace;
                    } {
                        testing.test_delete_key_delete;
                    };

                    if (i % 8 == 0) {
                        0.wait;
                    };

                    i = i + 1;
            };

            if (loops < 0) {
                log.e("test_many_deletes", "couldn't empty buffer", "FAIL");
                pass = false;
            };
            if (pass == true) {
                log.d("test_many_deletes", "OK");
            };

        }).play(AppClock);
    }

    test_coords {
        ^SkoarUiTesting_Textoar(textoar).test_coords;
    }

    test_many_coords {
        ^SkoarUiTesting_Textoar(textoar).test_many_coords;
    }

}

SkoarUiEditorTopPanel : SkoarUiView {

    var editor;
    var supercollider;

    var btn_play;


    init {
        | ed |
        editor = ed;

        view = View();
        supercollider = SkoarUiSuperCollider();

        btn_play = SkoarUiButton("Play", Color.yellow(0.7), Color.black, Color.gray(0.5), {
            editor.skoar_play;
        });

        layout = HLayout(
            btn_play.view,
            nil,
            supercollider.view
        );

        view.layout = layout;
    }

}

SkoarUiEditorLeftPanel : SkoarUiView {

    var editor;
    var content;

    init {
        | ed |
        var vline = View();
        var buf_options = SkoarUiListView("options", Color.grey(0), Color.gray(0.3));

        editor = ed;

        view = View();
        content = View();

        vline.fixedWidth = 20;
        vline.background = Color.gray(0.2);

        vline.mouseUpAction = {
            vline.background = Color.gray(0.2);
            this.toggle;
        };

        vline.mouseDownAction = {
            vline.background = Color.gray(0.3);
        };


        buf_options.add_option(\new, SkoarUiButton("New", Color.yellow(0.7), Color.black, Color.gray(0.5), {
            editor.new_buffer;
        }));

        buf_options.add_option(\load, SkoarUiButton("Open File", Color.magenta(0.7), Color.black, Color.gray(0.5), {
            editor.new_buffer;
            editor.load_file;
        }));

        buf_options.add_option(\log_buf, SkoarUiButton("Log Buffer", Color.blue(0.7), Color.black, Color.gray(0.5), {
            editor.log_buf;
        }));

        buf_options.add_option(\save, SkoarUiButton("Save", Color.magenta(0.7), Color.black, Color.gray(0.5), {
            editor.save_file;
        }));

        buf_options.add_option(\test_buffers, SkoarUiButton("check buffers", Color.magenta(0.45), Color.black, Color.gray(0.5), {
            editor.test_buffers_same;
        }));

        buf_options.add_option(\test_delete, SkoarUiButton("delete test", Color.magenta(0.45), Color.black, Color.gray(0.5), {
            editor.test_deleting;
        }));

        buf_options.add_option(\test_many_deletes, SkoarUiButton("many deletes", Color.magenta(0.45), Color.black, Color.gray(0.5), {
            editor.test_many_deletes;
        }));



        buf_options.add_option(\test_coords, SkoarUiButton("coords test", Color.magenta(0.45), Color.black, Color.gray(0.5), {
            editor.test_coords;
        }));

        buf_options.add_option(\test_many_coords, SkoarUiButton("many coords", Color.magenta(0.45), Color.black, Color.gray(0.5), {
            editor.test_many_coords;
        }));




        content.layout = VLayout(
            buf_options.view,
            editor.buffers.view,
            nil
        );

        layout = HLayout(
            content,
            vline
        );


        view.layout = layout;
    }

    hide {
        content.visible = false;
    }

    show {
        content.visible = true;
    }

    toggle {
        if (content.visible) {
            this.hide;
        } {
            this.show;
        };
    }

}

SkoarUiStatusBar : SkoarUiView {

    var text;

    init {
        view = View();

        text = StaticText();
        text.background = Color.yellow(0.7);
        text.stringColor = Color.black;
        text.font = Font.sansSerif(18);

        layout = HLayout(
            text
        );

        view.layout = layout;
    }

}
