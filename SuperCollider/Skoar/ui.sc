SkoarUiView {
    var <view;
    var layout;

    var <>log;

    *new {
        | ... args |
        var o = super.new;
        o.log = SkoarLogger(o.class.asString);
        ^o.init(*args);
    }

    remove {
        view.removeAll;
        view.remove;
    }
}

SkoarUi : SkoarUiView {

    var supercollider;
    var player;
    var editor;
    var log_pane;

    *new_with_view {
        | v |
        ^super.new.init_with_view(v);
    }

    init {
        this.init_window;
    }

    init_window {
        var w = Window("skoar");
        w.front;
        w.fullScreen;

        this.init_with_view(w);
    }

    init_with_view {
        | v |
        view = v;

        view.background = Color.black;

        editor = SkoarUiEditor(this);
        log_pane = SkoarUiLog();
        log_pane.view.fixedHeight = 500;

        layout = VLayout(
            [editor.view, stretch:1],
            log_pane.view
        );
        view.layout = layout;
    }

    toggle_log {
        var v = log_pane.view;
        if (v.visible) {
            v.visible = false;
        } {
            v.visible = true;
        };
    }
}

SkoarUiButton : SkoarUiView {

	var <>on_click;
	var  <colour;
	var  <unselected_colour;

	init {
		| label, bg, fg, clicking_colour, oc |

		on_click = oc;

		view = StaticText();

		view.string = label;

		view.fixedWidth = 140;
		view.fixedHeight = 60;

		view.font = Font.sansSerif(18, bold: true);
		view.align = \center;

		view.stringColor = fg;
		view.background = bg;
		colour = bg;

		view.mouseDownAction = {
			| v, x, y, modifiers |
			view.background = clicking_colour;
		};

		view.mouseUpAction = {
			| v, x, y, modifiers |
			this.on_click.();
			view.background = colour;
		};
	}

	colour_ {
	    | c |
	    colour = c;
	    view.background = c;
	}

	unselect {
	    view.background = Color.gray(0.3);
	}

	select {
        view.background = colour;
	}

	string_ {
	    | s |
	    view.string = s;
	}

	string {
	    ^view.string;
	}
}

SkoarUiListView : SkoarUiView {

    var options;
    var label;
	var  <colour;

	init {
		| label_text, bg, fg |

		view = View();

//        view.fixedWidth = 140;
        label = StaticText();
		label.string = label_text;

		label.fixedWidth = 120;
		//label.fixedHeight = 60;

		label.font = Font.sansSerif(18, bold: true);
		label.align = \left;

		label.stringColor = fg;
		label.background = bg;
		view.background = bg;
		colour = bg;
        options = IdentityDictionary();

		layout = VLayout(
		    label,
		    nil
		);

		view.layout = layout;
	}

	colour_ {
	    | c |
	    colour = c;
	    view.background = c;
	}

	add_option {
	    | id, o |
	    options[id] = o;
        layout.insert(o.view, options.size);
	}

	remove_option {
	    | id |
	    var o = options[id];

	    if (o.notNil) {
	        layout.delete(o.view);
	        options[id] = nil;
	    };
	}

	rename_option {
	    | id, new_name |
	    //log.d("renaming", new_name);
	    options[id].string = new_name;
	}

	select_option {
	    | id |
	    options.keysValuesDo {
	        | k, v |
	        if (k == id) {
	            v.select;
	        } {
	            v.unselect;
	        };
	    };
	}
}


