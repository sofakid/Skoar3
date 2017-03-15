
SkoarUiCursorCanvas : SkoarUiView {
    var <editor;

    init {
        | ed |
        editor = ed;
        view = View();
        view.acceptsMouse = false;
    }

    make_cursor {
        ^SkoarUiCursor(this);
    }

}

SkoarUiCursor : SkoarUiView {
    var <char;
    var fg;
    var bg;
    var font;
    var <coords;
    var canvas;

    init {
        | c |
        canvas = c;
        fg = Color.white(1);
        bg = Color.blue(1, 0.5);

        font = Font("Consolas", 20);

        view = StaticText(canvas.view);
        view.fixedWidth = SkoarUiChar.width;
        view.fixedHeight = SkoarUiChar.height;
        view.align = \center;
        view.string = "_";
        view.stringColor = fg;
        view.background = bg;
        view.font = font;

    }

    move_to {
        | x, y |
        //log.d("Moving cursor", x, y);
        view.moveTo(x,y);
    }

    move_to_coords {
        | co |
        coords = co;
        //log.d("Moving cursor", co.x, co.y, "pos", co.pos);
        view.moveTo(co.x, co.y);
    }

}