
SkoarUiCoords {

    var buffer;

    var <x;
    var <y;
    var <line_number;
    var <line_pos;
    var <pos;
    var <is_eof;
    var log;

    var is_initialized;

    *new {
        | ... args |
        ^super.new.init(*args)
    }

    *new_from_pos {
        | ... args |
        ^super.new.init_with_pos(*args)
    }

    *new_from_x_y {
        | ... args |
        ^super.new.init_with_x_y(*args)
    }

    *new_from_x_ln {
        | ... args |
        ^super.new.init_with_x_ln(*args)
    }

    *new_from_lp_ln {
        | ... args |
        ^super.new.init_with_lp_ln(*args)
    }


    copy {
        ^SkoarUiCoords(buffer, x, y, line_number, line_pos, pos)
    }

    init {
        | o, xx, yy, ln, lp, p |
        if (is_initialized == true) {
            ^this;
        };

        buffer = o;
        x = xx;
        y = yy;
        line_number = ln;
        line_pos = lp;
        pos = p;

        log = SkoarLogger("coords");

        this.pos_sanity;

        is_initialized = true;
    }

    init_with_pos {
        | o, p |

        if (is_initialized == true) {
            ^this;
        };

        buffer = o;
        x = 0;
        y = 0;
        line_number = 0;
        line_pos = 0;
        pos = 0;

        log = SkoarLogger("coords");

        this.delta_pos(p);
        is_initialized = true;
    }

    init_with_x_ln {
        | o, xx, ln |
        this.init_with_lp_ln(o, (xx / (SkoarUiChar.width)).asInteger, ln);
    }

    init_with_lp_ln {
        | o, lp, ln |

        var char, line;
        var h = 0;
        var line_sizes;
        var ls = 0;
        var num_lines;

        if (is_initialized == true) {
            ^this;
        };

        log = SkoarLogger("coords");

        buffer = o;

        line_sizes = buffer.line_sizes;
        num_lines = line_sizes.size;

        line_pos = lp;

        line_number = if (ln >= num_lines) {
            num_lines - 1;
        } {
            ln;
        };

        if (line_number < 0) {
            line_number = 0;
        };

        ls = line_sizes[line_number];

        if (line_pos >= ls) {
            line_pos = ls - 1;
        };

        if (line_pos < 0) {
            line_pos = 0;
        };

        pos = line_pos;
        line_number.do {
            | i |
            pos = pos + line_sizes[i];
        };

        this.pos_sanity;

        x = line_pos * SkoarUiChar.width;
        y = line_number * SkoarUiChar.height;

        //log.d("line_sizes", line_sizes.asArray, "ls", ls, "num_lines", num_lines, "newlines", buffer.newlines);
        //log.d("ln", ln, "line_number", line_number, "line_pos", line_pos, "lp", lp, "pos", pos, "x", x, "y", y);
        //log.d("")
        is_initialized = true;
    }

    // if this stops working, look for stray views in the layout, causing squashy.
    init_with_x_y {
        | o, xx, yy |
        var char, line;
        var h = 0;
        var line_sizes;
        var ls = 0;
        var num_lines;

        if (is_initialized == true) {
            ^this;
        };

        log = SkoarLogger("coords");

        buffer = o;

        line_sizes = buffer.line_sizes;
        num_lines = line_sizes.size;

        line_number = (yy / (SkoarUiChar.height)).asInteger;
        line_pos = (xx / (SkoarUiChar.width)).asInteger;

        if (line_number >= num_lines) {
            line_number = num_lines - 1;
        };

        if (line_number < 0) {
            line_number = 0;
        };

        ls = line_sizes[line_number];

        if (line_pos >= ls) {
            line_pos = ls - 1;
        };

        if (line_pos < 0) {
            line_pos = 0;
        };

        pos = line_pos;
        line_number.do {
            | i |
            pos = pos + line_sizes[i];
        };

        this.pos_sanity;

        x = line_pos * SkoarUiChar.width;
        y = line_number * SkoarUiChar.height;

        //log.d("line_sizes", line_sizes.asArray, "ls", ls, "num_lines", num_lines, "newlines", buffer.newlines);
        //log.d("line_number", line_number, "line_pos", line_pos, "pos", pos, "x", x, "y", y);
        //log.d("")
        is_initialized = true;

    }

    pos_sanity {
        var buf_size;
        var line_sizes;
        var ls = 0;
        var num_lines;

        line_sizes = buffer.line_sizes;
        num_lines = line_sizes.size;

        if (pos < 0) {
            //log.d("Cursor underflow", "pos", pos);
            pos = 0;
            line_pos = 0;
            line_number = 0;
        };

        buf_size = buffer.char_buf.size;
        if (pos >= buf_size) {
            //log.d("Cursor overflow", "buf_size", buf_size, "pos", pos);
            while {pos >= buf_size} {
                pos = pos - 1;
                line_pos = line_pos - 1;
            };

            if (line_pos < 0) {
                line_pos = 0;
            };

            if (line_number > num_lines) {
                line_number = num_lines;
                line_pos = 0;
            };
        };

        is_eof = (pos >= (buf_size - 1));

        //log.d("here", this.asString);
    }

    delta_pos {
        | p |

        var i = 0;

        var d = pos - p;
        var line_sizes;
        var ls = 0;
        var num_lines;

        if (is_initialized == true) {
            ^this;
        };

        line_sizes = buffer.line_sizes;
        num_lines = line_sizes.size;

        //log.d("delta_pos", "finding line_pos", "d", d);
        line_pos = line_pos - d;
        //log.d("delta_pos", "line_pos", line_pos);

        if (p > pos) {
            line_number = 0;
            ls = line_sizes[line_number];

            while {ls.notNil and: {line_pos >= ls}} {
                //log.d("line_pos >= line.size", line_pos, line.size);

                line_pos = line_pos - (ls);
                //log.d("delta_pos", "-", "line_pos", line_pos);

                line_number = line_number + 1;
                ls = line_sizes[line_number];
                if (ls.isNil) {
                    ls = line_sizes[line_number - 1];
                    line_pos = ls - 1;
                    //log.d("delta_pos", "=", "line_pos", line_pos);
                };
            };

        } {

            ls = line_sizes[line_number];
            while {line_pos < 0 and: {line_number >= 0}} {
                line_number = line_number - 1;
                ls = line_sizes[line_number];
                if (ls.isNil) {
                    line_pos = 0;
                } {
                    line_pos = line_pos + ls;
                };
                //log.d("delta_pos", "+", "line_pos", line_pos);
            };

        };

        if (line_number < 0) {
            line_number = 0;
        };

        if (line_pos < 0) {
            line_pos = 0;
            //log.d("delta_pos", "line_pos", line_pos);
        };

        pos = p;

        this.pos_sanity;

        x = line_pos * SkoarUiChar.width;
        y = line_number * SkoarUiChar.height;

        is_initialized = true;

    }


    asString {
        ^("coords: <"++ x ++", "++ y ++"> ln: " ++ line_number ++", lp: "++ line_pos ++", pos:"++ pos);
    }

    == {
        | o |
        ^pos == o.pos
            and: {line_pos == o.line_pos}
            and: {line_number == o.line_number}
            and: {x == o.x}
            and: {y == o.y};
    }

    != {
        | o |
        ^(this == o).not
    }

    hash {
        ^pos.hash;
    }

    back {
        ^SkoarUiCoords.new_from_pos(buffer, pos - 1);
    }

    forward {
        ^SkoarUiCoords.new_from_pos(buffer, pos + 1);
    }

    up {
        if (line_number == 0) {
            ^SkoarUiCoords(buffer, 0,0, 0,0,0)
        };
        ^SkoarUiCoords.new_from_lp_ln(buffer, line_pos, line_number - 1)
    }

    down {
        var line_sizes = buffer.line_sizes;
        var num_lines = line_sizes.size;

        if (line_number == (num_lines - 1)) {
            ^SkoarUiCoords.new_from_lp_ln(buffer, (line_sizes[line_number] - 1), line_number)
        };
        ^SkoarUiCoords.new_from_lp_ln(buffer, line_pos, line_number + 1)
    }

    back_same_line {
        ^SkoarUiCoords(
            buffer,
            x - SkoarUiChar.width,
            y,
            line_number,
            line_pos - 1,
            pos - 1)
    }

    forward_same_line {
        ^SkoarUiCoords(
            buffer,
            x + SkoarUiChar.width,
            y,
            line_number,
            line_pos + 1,
            pos + 1)
    }

    up_just_x_y {
        ^SkoarUiCoords(
            buffer,
            x,
            y + SkoarUiChar.height,
            0,
            0,
            0)
    }

    down_just_x_y {
        ^SkoarUiCoords(
            buffer,
            x,
            y + SkoarUiChar.height,
            0,
            0,
            0)
    }

}
