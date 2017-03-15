
SkoarUiTesting_Textoar : SkoarUiView {

    var textoar;

    init {
        | t |
        textoar = t;
    }

    buffers_are_same {
        var screen_chars = textoar.get_on_screen_string;
        var buffer_chars = "";
        var buffer_string = "";
        var pass = true;

        buffer_chars = "";
        textoar.buffer.char_buf.do {
            | c |
            buffer_chars = buffer_chars ++ (c.char);
        };

        buffer_string = textoar.buffer.string;

        if (buffer_string != buffer_chars) {
            log.e("buffers_are_same?", "buffer_string != buffer_chars", "FAIL");
            log.d("buffers_are_same?", "buffer_string.size", buffer_string.size, "buffer_chars.size", buffer_chars.size);
            log.d("buffers_are_same", "buffer_string", buffer_string, buffer_string.size);
            log.d("buffers_are_same", "buffer_chars", buffer_chars, buffer_chars.size);

            pass = false;
        };

        if (screen_chars != buffer_chars) {
            log.e("buffers_are_same?", "screen_chars != buffer_chars", "FAIL");
            log.d("buffers_are_same?", "screen_chars.size", screen_chars.size, "buffer_chars.size", buffer_chars.size);
            log.d("buffers_are_same?", "screen_chars", screen_chars, screen_chars.size);
            log.d("buffers_are_same?", "buffer_chars", buffer_chars, buffer_chars.size);
            pass = false;
        };

        if (screen_chars != buffer_string) {
            log.e("buffers_are_same?", "screen_chars != buffer_string", "FAIL");
            log.d("buffers_are_same?", "screen_chars.size", screen_chars.size, "buffer_string.size", buffer_string.size);
            log.d("buffers_are_same?", "screen_chars", screen_chars, screen_chars.size);
            log.d("buffers_are_same?", "buffer_string", buffer_string, buffer_string.size);
            pass = false;
        };

        if (pass) {
            //log.i("buffers_are_same?", "OK");
        };

        ^pass;
    }

    random_coords {
        var n = textoar.buffer.size;
        var p = n.rand;
        var x = SkoarUiCoords.new_from_pos(textoar.buffer, p);
        //log.d("random coords", x);

        ^x
    }

    move_to_random {
        textoar.coords = this.random_coords;
    }

    select_random {
        this.move_to_random;
        textoar.select_region(this.random_coords);
    }

    delete_random {
        this.select_random;
        textoar.delete_selection;
        textoar.unselect_all;
    }

    test_delete {
        var pass = true;

        this.delete_random;

        pass = this.buffers_are_same;

        if (pass == true) {
            //log.i("test_delete", "OK");
        } {
            log.e("test_delete", "delete_random", "FAIL")
        };

        ^pass;
    }

    test_delete_key_backspace {
        var pass = true;

        this.move_to_random;
        textoar.delete_key_backspace;
        textoar.unselect_all;

        pass = this.buffers_are_same;

        if (pass == true) {
            //log.i("test_delete_key_backspace", "OK");
        } {
            log.e("test_delete_key_backspace", "FAIL")
        };

        ^pass;
    }

    test_delete_key_delete {
        var pass = true;

        this.move_to_random;
        textoar.delete_key_delete;
        textoar.unselect_all;

        pass = this.buffers_are_same;

        if (pass == true) {
            //log.i("test_delete_key_delete", "OK");
        } {
            log.e("test_delete_key_delete", "FAIL")
        };

        ^pass;
    }

    test_coords {

        var x, y, z, p, q;
        var here = textoar.coords;
        var pass = true;

        x = SkoarUiCoords.new_from_pos(textoar.buffer, here.pos);

        if (x != here) {
            log.e("test_coords", "new_from_pos", x, here, "FAIL");
            pass = false;
        };

        x = SkoarUiCoords.new_from_x_y(textoar.buffer, here.x, here.y);

        if (x != here) {
            log.e("test_coords", "new_from_x_y", x, here, "FAIL");
            pass = false;
        };

        x = SkoarUiCoords.new_from_x_ln(textoar.buffer, here.x, here.line_number);

        if (x != here) {
            log.e("test_coords", "new_from_x_ln", x, here, "FAIL");
            pass = false;
        };


        if (pass == true) {
            //log.i("test_coords", "OK");
        } {
            log.e("test_coords", "FAIL")
        };

        ^pass;

    }

    test_many_coords {

        var n, x, y, z, p, q ,r, lines, line_sizes, ls;
        var pass = true;
        var failures = List[];

        n = textoar.buffer.size;
        line_sizes = textoar.buffer.line_sizes;
        Routine({
            [0,(SkoarUiChar.height/2).asInteger, SkoarUiChar.height].do {
                | h |
                line_sizes.do {
                    | ls, i |
                    y = h + (i * SkoarUiChar.height);

                    x = 0;
                    ls.do {
                        | j |

                        [0, (SkoarUiChar.width/2).asInteger, SkoarUiChar.width].do {
                            | w |
                            x = w + (j * SkoarUiChar.width);

                            textoar.move_cursor_to(x,y);

                            p = this.test_coords;

                            if (p == false) {
                                failures.add(["move_cursor_to(x,y)", x, y]);
                                pass = false;
                            };

                            0.wait;
                        };
                    };

                };

            };

            if (failures.size > 0) {
                failures.do {
                    | fail |
                    log.e("test_many_coords", fail, "FAIL");
                };
            } {
                log.i("test_many_coords", "OK");

            };

        }).play(AppClock);



        ^pass;

    }

}