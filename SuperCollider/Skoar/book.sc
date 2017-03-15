SkoarpuscleBooks : Skoarpuscle {

	var pref;
	var books;
	
	init {
		| e=nil |

		books = if (e.notNil) {
			[e]
		} {
			[]
		};
		
		pref = "SKRP_Books :: ";

	}

	add_book {
		| book |

		books = books.add(book);

	}

	read {
		| m |

		books.size.do {
			| i |
			this.read_book(m, i);
		};
		
	}

	read_book {
		| m, i, symbols=nil |

		//(pref ++ "reading book " ++ i).postln;
		var x = books[i];

		if (x.notNil) {
			x.read(m, symbols);
		};
		
	}

	lookup {
		| entry, book=0 |
		^books[book].lookup(entry);
	}

	skoar_msg {
        | msg, minstrel |
        var name = msg.val;
		var args = msg.get_msg_arr(minstrel);
		
        case {name == \book} {

			var book_i = args[0];
			//(pref ++ "---------------------------------------------------------").postln;
			case {book_i.isKindOf(SkoarpuscleInt)} {
				book_i = book_i.val;
				
			} {book_i.isKindOf(Skoarpuscle)} {
				minstrel.fairy.push_noating;
				book_i = book_i.flatten(minstrel);
				minstrel.fairy.pop_noating;

			} {
				book_i = nil;
			};

			if (book_i.notNil) {
				^SkoarpuscleBook.new_book(books[book_i], nil);
			} {
				^SkoarpuscleCat.new();
			};
			
		    //(pref ++ "---------------------------------------------------------").postln;			
		} {name == \read} {

			var book_i = args[1];
			(pref ++ "book_i :: " ++book_i).postln;
			
			//(pref ++ "---------------------------------------------------------").postln;
			case {book_i.isKindOf(SkoarpuscleInt)} {
				book_i = book_i.val;
				
			} {book_i.isKindOf(Skoarpuscle)} {
				minstrel.fairy.push_noating;
				book_i = book_i.flatten(minstrel);
				minstrel.fairy.pop_noating;

			} {
				book_i = nil;
			};
			//(pref ++ " ARGS :: " ++ args).postln;

			if (book_i.isNil) {
				this.read(minstrel);
			} {
				this.read_page(minstrel, book_i);
			};
				
		    //(pref ++ "---------------------------------------------------------").postln;			
		};

    }
}

SkoarpuscleBook : Skoarpuscle {

	var pref;
	

	*new_book {
		| e=nil, symbols=nil |
		^super.new.init_book(e, symbols);
	}
		
	init_book {
		| e, symbols |
		pref = "SKRP_Book :: ";
		
		val = if (e.notNil) {
			if (symbols.isNil or: symbols.size == 0) {
				e
			} {
				IdentityDictionary.new
			}
		} {
			IdentityDictionary.new
		};

		//(pref ++ "val     :: " ++ val).postln;
		//(pref ++ "e       :: " ++ e).postln;
		//(pref ++ "symbols :: " ++ symbols).postln;
		
		if (symbols.notNil) {
			symbols.do {
				| k |
				//(pref ++ "writing symbol " ++ k).postln;
				val[k] = e[k];
			};
		};
		
		

	}

	read {
		| m, symbols=nil |

		var f = {
			| k, v |
			//(pref ++ "   m.koar[" ++ k ++ "] = " ++ v ++ ";").postln;
			m.koar[k] = v;
		};

		//(pref ++ "symbols :: " ++symbols).postln;
		
		if (symbols.isNil or: symbols.size == 0) {
			//(pref ++ "symbols is nil").postln;
			val.keysValuesDo {
				| k, v |
				//(pref ++ "["++k++"] == "++v).postln;
				f.(k,v);
			};
		} {
			symbols.do {
				| k |
				f.(k, val[k]);
			};
		};
	}

	lookup {
		| entry |
		^val[entry];
	}

	skoar_msg {
        | msg, minstrel |
        var name = msg.val;
		var args = msg.get_msg_arr(minstrel);

        case {name == \read} {
			var symbols = args[1..];
			
			this.read(minstrel, symbols);
		};

    }
}