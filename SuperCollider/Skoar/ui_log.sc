SkoarLogger {

    var tag;

    *new {
        | t |
        ^super.new.init(t);
    }

    init {
        | t |
        tag = t;
    }

    expand {
        | message, args |
        var s = message;
    	args.do {
    	    | x |
    	    s = s ++ " :: " ++ x;
    	};
    	^s
    }

    d {
    	| message ... args |
	    SkoarLog.d(tag, this.expand(message, args));
    }

    i {
    	| message ... args |
        SkoarLog.i(tag, this.expand(message, args));
    }

    w {
    	| message ... args |
        SkoarLog.w(tag, this.expand(message, args));
    }

    e {
    	| message ... args |
        SkoarLog.e(tag, this.expand(message, args));
    }

}

SkoarLog {

    classvar <text;
    classvar d, i, w, e;
    classvar <>listener;

    *initClass {
        text = "";
        d = "--- ";
        i = "*** ";
        w = "??? ";
        e = "!!! ";
        listener = nil;
    }

    *d {
    	| tag, message |
	    SkoarLog.log(d, tag, message);
    }

    *i {
    	| tag, message |
	    SkoarLog.log(i, tag, message);
    }

    *w {
    	| tag, message |
	    SkoarLog.log(w, tag, message);
    }

    *e {
    	| tag, message |
	    SkoarLog.log(e, tag, message);
    }

    *log {
		| prefix, tag, message, end="\n" |
		var out = prefix ++ tag ++ " :: " ++ message ++ end;
		text = text ++ out;

		if (listener.notNil) {
		    listener.update_log(text, out);
		} {
		    out.post;
		};
	}

}


SkoarUiLog : SkoarUiView {

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

        view.palette = palette;
        view.font = Font("Consolas", 18);
        view.enterInterpretsSelection = false;
        view.editable = false;

        SkoarLog.listener = this;
    }

    update_log {
        | whole_text, one_line |
        view.string = whole_text;
        view.select(whole_text.size, 1)
    }

}