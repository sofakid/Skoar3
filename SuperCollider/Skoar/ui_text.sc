


SkoarUiTextoarSwitcher : SkoarUiView {

    var editor;

    init {
        | ed |
        editor = ed;
    }
}

SkoarUiTextoar : SkoarUiView {

    var cursor_canvas;
    var text_canvas;
    var canvas;
    var rows;
    var columns;

    var editor;
    var <buffer;

    var <selection_start;
    var <selection_end;

    var <selection_size;

    var <cursor;
    var <coords;

    var <selecting;

    init {
        | ed, buf |
        editor = ed;
        buffer = buf;

        view = ScrollView();
        view.hasBorder = false;

        canvas = View();
        cursor_canvas = SkoarUiCursorCanvas(editor);
        cursor = cursor_canvas.make_cursor;
        coords = SkoarUiCoords(buffer, 0,0,0,0,0);
        selection_start = coords;
        selection_end = coords;

        text_canvas = View();

        text_canvas.background = Color.black;
        text_canvas.fixedHeight = SkoarUiChar.height;
        text_canvas.minWidth = SkoarUiChar.width;

        selecting = false;

        text_canvas.mouseDownAction = {
            | v, x, y, mod, button_number, click_count |
            this.unselect_all;
            this.move_cursor_to(x, y);
            this.select_region_start;
        };

        text_canvas.mouseMoveAction = {
            | v, x, y, modifiers |
            this.move_cursor_to(x, y);
            this.select_region(coords);

            //log.d("move", x, y, SkoarUiCoords.new_from_x_y(buffer,x,y));
        };

        text_canvas.mouseUpAction = {
            | v, x, y, modifiers |
            this.move_cursor_to(x, y);
            this.select_region(coords);
            //log.d("mouseUpAction", x, y, SkoarUiCoords.new_from_x_y(buffer,x,y));

            selecting = false;
            text_canvas.focus;
        };

        text_canvas.keyUpAction = {
            | v, char, mod, unicode, keycode, key |
            var should_highlight = false;
            //log.i("keyUpAction", "mod", mod, "key", key);

            if (mod.isCtrl or: {mod.isAlt} or: {mod.isCmd} ) {
                if (SkoarUiCodes.key_one_of(key, 'V', 'X', 'Z')) {
                    should_highlight = true;
                };
            };

            if (SkoarUiCodes.key_one_of(key, 'Delete', 'Backspace')) {
                should_highlight = true;
            };

            if (char.notNil and: {char.isPrint}) {
                this.unselect_all;
                should_highlight = true;
            };

            if (should_highlight) {
                editor.syntax_highlight;
            };
        };

        text_canvas.keyDownAction = {
            | v, char, mod, unicode, keycode, key |
            //log.i("keyDownAction", "mod", mod, "key", key);

            //log.d("keyDownAction", "start", coords);

            if (mod == 0) {
                if (key == SkoarUiCodes.key['Backspace']) {

                    if (selection_size == 0) {
                        this.delete_key_backspace;
                    } {
                        this.delete_selection;
                    }
                };

                if (key == SkoarUiCodes.key['Delete']) {

                    if (selection_size == 0) {
                        this.delete_key_delete;
                    } {
                        this.delete_selection;
                    }
                };

                if (key == SkoarUiCodes.key['Up']) {
                    this.up;
                };

                if (key == SkoarUiCodes.key['Down']) {
                    this.down;
                };

                if (key == SkoarUiCodes.key['Left']) {
                    this.back;
                };

                if (key == SkoarUiCodes.key['Right']) {
                    this.forward;
                };
            };

            if (mod.isShift) {
                if (key == SkoarUiCodes.key['Up']) {
                    this.up_select;
                };

                if (key == SkoarUiCodes.key['Down']) {
                    this.down_select;
                };

                if (key == SkoarUiCodes.key['Left']) {
                    this.back_select;
                };

                if (key == SkoarUiCodes.key['Right']) {
                    this.forward_select;
                };
            };

            if (char.notNil) {
                if (mod.isCtrl.not and: {mod.isAlt.not} and: {mod.isCmd.not}) {

                    if (char.isSpace or: {char.isPrint}) {
                        if (selection_size > 0) {
                            this.delete_selection;
                        };
                        if (SkoarUiCodes.key_one_of(key, 'Enter', 'Return')) {
                            this.insert_char(buffer.insert_char($\n));
                            this.repack_to_end;
                        } {
                            this.insert_char(buffer.insert_char(char));
                            this.repack_this_line;
                        };
                        this.move_cursor_to_coords;
                    };

                };
            };

            if (mod == 0) {
                this.unselect_all;
            };
            //log.d("keyDownAction", "done ", coords);

            false
        };

        text_canvas.focus;

        canvas.layout = StackLayout(text_canvas, cursor_canvas.view);
        canvas.layout.mode = \stackAll;
        canvas.layout.index = 1;
        canvas.background = Color.black;

        view.canvas = canvas;


        this.clear;

    }

    get_on_screen_string {
        var screen_chars = List[];
        var on_screen = text_canvas.children;

        on_screen = on_screen.sort({
            | a, b |
            var ar, br;
            var ax, ay, bx, by;

            ar = a.bounds;
            ax = ar.left;
            ay = ar.top;

            br = b.bounds;
            bx = br.left;
            by = br.top;

            case {ay == by} {
                if (ax < bx) {
                    true
                } {
                    false
                }
            } {ay < by} {
                true
            } {
                false
            }
        });

        on_screen.do {
            | v |
            if (v.isKindOf(StaticText)) {
                screen_chars.add(v.string);
            } {
                screen_chars.add("\n");
            };
        };
        ^screen_chars.join;
    }

    resize {
        var line_sizes = buffer.line_sizes;
        var n = (line_sizes.size + 10) * SkoarUiChar.height;
        var m = 132 * SkoarUiChar.width;
        var x ;

        line_sizes.do {
            | z |
            x = (z + 10) * SkoarUiChar.width;
            if (x > m) {
                m = x;
            };
        };

        text_canvas.fixedHeight = n;
        cursor_canvas.view.fixedHeight = n;

        text_canvas.fixedWidth = m;
        cursor_canvas.view.fixedWidth = m;
    }

    clear {

        text_canvas.removeAll;

        selection_size = 0;

        coords = SkoarUiCoords(buffer, 0, 0, 0, 0, 0);

        this.move_cursor_to_coords();
        this.resize;
    }

    load_buffer {
        | buf |
        this.clear;

        buffer = buf;

        coords = SkoarUiCoords(buffer, 0, 0, 0, 0, 0);
        this.move_cursor_to_coords();

        buffer.char_buf.do {
            | c |
            this.insert_char(c);
        };

        coords = SkoarUiCoords(buffer, 0, 0, 0, 0, 0);
        this.move_cursor_to_coords();

        this.repack_to_end;
    }

    repack_this_line {
        var last;

        var start = coords.pos;
        var line_size = buffer.line_sizes[coords.line_number];
        var line_end = start + (line_size - coords.line_pos);
        var x = start - 1;

        buffer.char_range_do(x, x, {
            | char |
            last = char;
        });

        buffer.char_range_do(start, line_end, {
            | char |
            char.place_after(last);
            last = char;
        });

        this.resize;
    }

    repack_to_end {
        var last;

        var start = coords.pos;
        var end = buffer.size;
        var x = start - 1;

        buffer.char_range_do(x, x, {
            | char |
            last = char;
        });

        buffer.char_range_do(start, end, {
            | char |
            char.place_after(last);
            last = char;
        });

        this.resize;
    }

    insert_char {
        | char |
        char.init_view(text_canvas);
        this.forward;
    }

    delete_key_backspace {
        //log.d("delete_key_backspace", coords);
        this.back;
        //log.d("delete_key_backspace", coords);

        this.delete_key_delete;
    }

    delete_key_delete {
        //log.d("delete_key_delete", "merp", coords);

        selection_start = SkoarUiCoords.new_from_pos(buffer, coords.pos);
        selection_end = SkoarUiCoords.new_from_pos(buffer, coords.pos+1);

        //log.d("delete_key_delete", coords);

        if (selection_start.is_eof or: {selection_end.is_eof}) {
            //log.d("delete_key_delete", "eof", selection_start.is_eof, selection_end.is_eof);
            ^this;
        };

        selection_size = 1;
        //log.d("delete_key_delete", coords);

        this.delete_selection;
        selection_size = 0;
    }

    delete_selection {
        var ln_start = selection_start.line_number;
        var ln_end = selection_end.line_number;
        var start_line;
        var end_line;
        var x, y;
        var cb = buffer.char_buf;

        var last;

        //log.d("delete_selection");
        coords = selection_start;
        if (coords.pos < 0 or: {coords.is_eof} or: {selection_end.is_eof}) {
            ^this;
        };

        if (selection_start.pos + selection_size >= buffer.size) {
            selection_size = buffer.size - selection_start.pos;
        };

        this.move_cursor_to_coords();

        buffer.delete_range(selection_start, selection_size);

        selection_size = 0;
        selection_end = selection_start = coords;

        this.repack_to_end;
    }

    select_region_start {
        if (selecting == false) {
            selection_start = coords;
            selecting = true;
        };
    }

    select_region {
        | to |
        var start = selection_start.pos;
        var end = to.pos;
        var chars = buffer.char_buf;
        var t;

        //log.d("select_region");
        if (start > end) {
            start = start bitXor: end;
            end   = start bitXor: end;
            start = start bitXor: end;

            t = selection_start;
            selection_start = to;

            selection_end = t;
        } {
            selection_end = to;
        };

        while {selection_end.is_eof and: {end > 0}} {
            selection_end = selection_end.back;
            end = selection_end.pos;
            //log.d("select_region", "looping");
        };

        selection_size = end - start + 1;

        if (selection_size > 1) {

            chars.do {
                | c, i |
                if (i >= start and: {i <= end}) {
                    c.select;
                } {
                    c.unselect;
                };
            };
        } {
            selection_size = 0;
        };

    }

    unselect_all {
        selection_size = 0;
        selection_start = selection_end = coords;

        buffer.char_buf.do {
            | c |
            c.unselect;
        };

        selecting = false;
    }

    cut {

    }

    copy {

    }

    paste {

    }

    coords_ {
        | cds |
        coords = cds;
        this.move_cursor_to_coords;
    }

    move_cursor_to {
        | x, y |
        coords = SkoarUiCoords.new_from_x_y(buffer, x, y);
        this.move_cursor_to_coords;
    }

    move_cursor_to_x_ln {
        | x, ln |
        coords = SkoarUiCoords.new_from_x_ln(buffer, x, ln);
        this.move_cursor_to_coords;
    }

    move_cursor_to_coords {
        cursor.move_to_coords(coords);
        editor.move_buffer_to_coords(coords);
    }

    back {
        coords = coords.back;
        this.move_cursor_to_coords;
    }

    forward {
        coords = coords.forward;
        this.move_cursor_to_coords;
    }

    up {
        coords = coords.up;
        this.move_cursor_to_coords;
    }

    down {
        coords = coords.down;
        this.move_cursor_to_coords;
    }

    back_select {
        this.select_region_start;
        this.back;
        this.select_region(coords);
    }

    forward_select {
        this.select_region_start;
        this.forward;
        this.select_region(coords);
    }

    up_select {
        this.select_region_start;
        this.up;
        this.select_region(coords);
    }

    down_select {
        this.select_region_start;
        this.down;
        this.select_region(coords);
    }

}


SkoarUiChar : SkoarUiView {

    classvar <>height = 28;
    classvar <>width = 12;

    var <char;
    var fg;
    var bg;
    var font;
    var <>sel_bg;
    var <>sel_fg;
    var selected;

    var coords;
    var buffer;

    init {
        | c, buf, last_char |
        var last_coords, x, y;
        char = c;

        buffer = buf;

        if (last_char.isNil) {
            coords = SkoarUiCoords.new(buf, 0, 0, 0,0,0);
        } {
            coords = last_char.coords_next;
        };
        //coords = SkoarUiCoords.new_from_pos(buf, pos);

        fg = Color.white;
        bg = Color.black;
        sel_fg = fg;
        sel_bg = Color.gray(0.2);

        font = Font("Consolas", 20);
//        font = Font("Source Code Pro Medium", 20);

        selected = false;

    }

    coords_next {
        ^coords.forward_same_line
    }

    init_view {
        | parent |
        view = StaticText(parent, Rect(coords.x, coords.y, SkoarUiChar.height, SkoarUiChar.width));

        view.fixedWidth = SkoarUiChar.width;
        view.fixedHeight = SkoarUiChar.height;
        view.minHeight = SkoarUiChar.height;

        view.align = \center;
        view.string = char.asString;
        view.stringColor = fg;
        view.background = if (selected == true) {sel_bg} {bg};

        view.font = font;
        view.front;

        //log.d("init_view", char, coords.x, coords.y, coords.pos);
    }

    place_after {
        | last |
        if (last.isNil) {
            coords = SkoarUiCoords.new(buffer, 0,0, 0,0,0);
        } {
            coords = last.coords_next;
        };
        this.move_to_current_coords;
    }

    move_to_current_coords {
        if (view.notNil) {
            view.moveTo(coords.x, coords.y);
        };
    }

    move_forward {
        coords = coords.forward_same_line;
        this.move_to_current_coords;
    }

    move_back {
        coords = coords.back_same_line;
        this.move_to_current_coords;
    }

    move_up {
        coords = coords.up_just_x_y;
        this.move_to_current_coords;
    }

    move_down {
        coords = coords.down_just_x_y;
        this.move_to_current_coords;
    }

    move_to_pos {
        | pos |
        coords = SkoarUiCoords.new_from_pos(buffer, pos);
        this.move_to_current_coords;
    }

    char_ {
        | c |
        char = c;
        view.string = c.asString;
    }

    fg_ {
        | colour |
        fg = colour;
        view.stringColor = fg;
    }

    bg_ {
        | colour |
        bg = colour;
        view.background = bg;
    }

    select {
        if (selected == false) {
            selected = true;
            view.background = sel_bg;
            //view.stringColor = sel_fg;
        };
    }

    unselect {
        if (selected == true) {
            selected = false;
            view.background = bg;
        };
    }

    recreate_view {
        | parent |
        if (view.notNil and: {view.isClosed != true}) {
            view.remove;
        };

        this.init_view(parent);
    }

    remove {
        if (view.notNil) {
            view.remove;
            view = nil;
        };
    }

}

SkoarUiNewlineChar : SkoarUiChar {

    init_view {
        | parent |
        view = View(parent, Rect(coords.x, coords.y, SkoarUiChar.width, SkoarUiChar.height));
        view.fixedWidth = SkoarUiChar.width;
        view.fixedHeight = SkoarUiChar.height;
        view.background = if (selected == true) {sel_bg} {bg};
    }

    coords_next {
        var x = 0;
        var y = coords.y + SkoarUiChar.height;
        ^SkoarUiCoords(buffer, x, y, 0,0,0);
    }

    char {
        ^"\n"
    }

    fg_ {
        | colour |
    }

}

SkoarUiFreeSpace : SkoarUiChar {

    init {
        bg = Color.cyan(0.1);
        sel_bg = Color.grey(0.2);
        selected = false;

        this.init_view;
    }

    init_view {
        view = View();
        view.minWidth = SkoarUiChar.width;
        view.fixedHeight = SkoarUiChar.height;
        view.background = if (selected == true) {sel_bg} {bg};
    }

    char {
        ^" "
    }

    fg_ {
        | colour |
    }

}