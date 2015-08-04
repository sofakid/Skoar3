// ================================================================================
<<<<<<< HEAD
// lex.sc - Generated by Code_Sc_Lexer on 2015-03-29 16:05:12 for SuperCollider 3.7
=======
// lex.sc - Generated by Code_Sc_Lexer on 2015-04-21 23:59:55 for SuperCollider 3.7
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9
// ================================================================================
// --------------
// SkoarException
// --------------
SkoarError : Exception {
    *new {
        | msg |

        ^super.new(msg);
    }

    *errorString {
        ^"SKOAR" ++ super.errorString;
    }

}

// --------------
// Abstract Token
// --------------
SkoarToke {
    var <lexeme;
    var size;
    classvar <regex = nil;

    *new {
        | s, n |

        ^super.new.init( s, n );
    }

    init {
        | s, n |

        lexeme = s;
        size = n;
    }

    // how many characters to burn from the buffer
    burn {
        ^size;
    }

    // override and return nil for no match, new toke otherwise
    *match {
        | buf, offs |

        SubclassResponsibilityError("What are you doing human?").throw;
    }

    // match requested toke
    *match_toke {
        | buf, offs, toke_class |

        var match;
        match = buf.findRegexpAt(toke_class.regex, offs);
        if (match.isNil) {
            ^nil;
        };

        ^toke_class.new(match[0], match[1]);
    }

}

// ---------------------
// Whitespace is special
// ---------------------
Toke_Whitespace : SkoarToke {
    classvar <regex = "[ \\t]*";

    *burn {
        | buf, offs |

        var match;
        match = buf.findRegexpAt(Toke_Whitespace.regex, offs);
        if (match != nil) {
            ^match[1];
        };

        ^0;
    }

}

// --------------
// EOF is special
// --------------
Toke_EOF : SkoarToke {
    *burn {
        | buf, offs |

        if (buf.size > offs) {
            SkoarError("Tried to burn EOF when there's more input.").throw;
        };

        ^0;
    }

    *match {
        | buf, offs |

        if (buf.size < offs) {
            SkoarError("Tried to burn EOF when there's more input.").throw;
        };

        if (buf.size == offs) {
            ^Toke_EOF.new();
        };

        ^nil;
    }

}

// --------------
// Everyday Tokes
// --------------
<<<<<<< HEAD
Toke_DynPiano : SkoarToke {
    classvar <regex = "(mp|p+)(iano)?";
=======
Toke_QuindicesimaA : SkoarToke {
    classvar <regex = "15ma|alla quindicesima";
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9

    *match {
        | buf, offs |

<<<<<<< HEAD
        ^SkoarToke.match_toke(buf, offs, Toke_DynPiano);
=======
        ^SkoarToke.match_toke(buf, offs, Toke_QuindicesimaA);
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9
    }

}

<<<<<<< HEAD
Toke_OctaveShift : SkoarToke {
    classvar <regex = "~+o|o~+";
=======
Toke_False : SkoarToke {
    classvar <regex = "no";
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9

    *match {
        | buf, offs |

<<<<<<< HEAD
        ^SkoarToke.match_toke(buf, offs, Toke_OctaveShift);
=======
        ^SkoarToke.match_toke(buf, offs, Toke_False);
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9
    }

}

<<<<<<< HEAD
Toke_LoopE : SkoarToke {
    classvar <regex = ":[}]";
=======
Toke_Freq : SkoarToke {
    classvar <regex = "(0|[1-9][0-9]*)(\\.[0-9]+)?Hz";
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9

    *match {
        | buf, offs |

<<<<<<< HEAD
        ^SkoarToke.match_toke(buf, offs, Toke_LoopE);
=======
        ^SkoarToke.match_toke(buf, offs, Toke_Freq);
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9
    }

}

<<<<<<< HEAD
Toke_Newline : SkoarToke {
    classvar <regex = "[\\n\\r\\f][\\n\\r\\f \\t]*";
=======
Toke_QuindicesimaB : SkoarToke {
    classvar <regex = "15mb";
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9

    *match {
        | buf, offs |

<<<<<<< HEAD
        ^SkoarToke.match_toke(buf, offs, Toke_Newline);
=======
        ^SkoarToke.match_toke(buf, offs, Toke_QuindicesimaB);
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9
    }

}

<<<<<<< HEAD
Toke_Comment : SkoarToke {
    classvar <regex = "<[?](.|[\\n\\r\\f])*?[?]>";
=======
Toke_String : SkoarToke {
    classvar <regex = "'[^']*'";
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9

    *match {
        | buf, offs |

<<<<<<< HEAD
        ^SkoarToke.match_toke(buf, offs, Toke_Comment);
=======
        ^SkoarToke.match_toke(buf, offs, Toke_String);
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9
    }

}

<<<<<<< HEAD
Toke_LoopSep : SkoarToke {
    classvar <regex = "::[\\n]*(?![|])";
=======
Toke_MsgName : SkoarToke {
    classvar <regex = "[a-zA-Z_][a-zA-Z0-9_]*(?!<)";
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9

    *match {
        | buf, offs |

<<<<<<< HEAD
        ^SkoarToke.match_toke(buf, offs, Toke_LoopSep);
=======
        ^SkoarToke.match_toke(buf, offs, Toke_MsgName);
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9
    }

}

<<<<<<< HEAD
Toke_Loco : SkoarToke {
    classvar <regex = "loco";
=======
Toke_LoopS : SkoarToke {
    classvar <regex = "[{]:[\\n]*";
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9

    *match {
        | buf, offs |

<<<<<<< HEAD
        ^SkoarToke.match_toke(buf, offs, Toke_Loco);
=======
        ^SkoarToke.match_toke(buf, offs, Toke_LoopS);
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9
    }

}

<<<<<<< HEAD
Toke_PedalUp : SkoarToke {
    classvar <regex = "[*](?!>)";
=======
Toke_Volta : SkoarToke {
    classvar <regex = "\\[\\d+\\.\\]";
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9

    *match {
        | buf, offs |

<<<<<<< HEAD
        ^SkoarToke.match_toke(buf, offs, Toke_PedalUp);
=======
        ^SkoarToke.match_toke(buf, offs, Toke_Volta);
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9
    }

}

<<<<<<< HEAD
Toke_Fairy : SkoarToke {
    classvar <regex = "[$]";
=======
Toke_Newline : SkoarToke {
    classvar <regex = "[\\n\\r\\f][\\n\\r\\f \\t]*";
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9

    *match {
        | buf, offs |

<<<<<<< HEAD
        ^SkoarToke.match_toke(buf, offs, Toke_Fairy);
=======
        ^SkoarToke.match_toke(buf, offs, Toke_Newline);
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9
    }

}

<<<<<<< HEAD
Toke_Caesura : SkoarToke {
    classvar <regex = "//";
=======
Toke_PedalUp : SkoarToke {
    classvar <regex = "[*](?!>)";
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9

    *match {
        | buf, offs |

<<<<<<< HEAD
        ^SkoarToke.match_toke(buf, offs, Toke_Caesura);
=======
        ^SkoarToke.match_toke(buf, offs, Toke_PedalUp);
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9
    }

}

<<<<<<< HEAD
Toke_QuindicesimaA : SkoarToke {
    classvar <regex = "15ma|alla quindicesima";
=======
Toke_DynForte : SkoarToke {
    classvar <regex = "m(ezzo)?f(orte)?|f+orte|ff+";
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9

    *match {
        | buf, offs |

<<<<<<< HEAD
        ^SkoarToke.match_toke(buf, offs, Toke_QuindicesimaA);
=======
        ^SkoarToke.match_toke(buf, offs, Toke_DynForte);
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9
    }

}

<<<<<<< HEAD
Toke_DalSegno : SkoarToke {
    classvar <regex = "D\\.S\\.|Dal Segno";
=======
Toke_ArgSpec : SkoarToke {
    classvar <regex = "<[a-zA-Z]+(,[a-zA-Z]+)*>";
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9

    *match {
        | buf, offs |

<<<<<<< HEAD
        ^SkoarToke.match_toke(buf, offs, Toke_DalSegno);
=======
        ^SkoarToke.match_toke(buf, offs, Toke_ArgSpec);
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9
    }

}

<<<<<<< HEAD
Toke_DynFP : SkoarToke {
    classvar <regex = "fp";
=======
Toke_BooleanOp : SkoarToke {
    classvar <regex = "==|!=|<=|>=|and|or|xor";
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9

    *match {
        | buf, offs |

<<<<<<< HEAD
        ^SkoarToke.match_toke(buf, offs, Toke_DynFP);
=======
        ^SkoarToke.match_toke(buf, offs, Toke_BooleanOp);
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9
    }

}

<<<<<<< HEAD
Toke_SkoarpionSep : SkoarToke {
    classvar <regex = "!!";
=======
Toke_Portamento : SkoarToke {
    classvar <regex = "port\\.?";
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9

    *match {
        | buf, offs |

<<<<<<< HEAD
        ^SkoarToke.match_toke(buf, offs, Toke_SkoarpionSep);
=======
        ^SkoarToke.match_toke(buf, offs, Toke_Portamento);
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9
    }

}

<<<<<<< HEAD
Toke_RWing : SkoarToke {
    classvar <regex = "[)]\\^\\^";
=======
Toke_PedalDown : SkoarToke {
    classvar <regex = "Ped\\.?";
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9

    *match {
        | buf, offs |

<<<<<<< HEAD
        ^SkoarToke.match_toke(buf, offs, Toke_RWing);
=======
        ^SkoarToke.match_toke(buf, offs, Toke_PedalDown);
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9
    }

}

<<<<<<< HEAD
Toke_LoopS : SkoarToke {
    classvar <regex = "[{]:[\\n]*";
=======
Toke_CondS : SkoarToke {
    classvar <regex = "[{][?][\\n]*";
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9

    *match {
        | buf, offs |

<<<<<<< HEAD
        ^SkoarToke.match_toke(buf, offs, Toke_LoopS);
=======
        ^SkoarToke.match_toke(buf, offs, Toke_CondS);
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9
    }

}

<<<<<<< HEAD
Toke_ListSep : SkoarToke {
    classvar <regex = ",";
=======
Toke_Choard : SkoarToke {
    classvar <regex = "[ABCDEFG](?![ce-ln-rt-zA-LN-Z])(#|b)?([Mm0-9]|sus|dim|aug|dom|add)*";
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9

    *match {
        | buf, offs |

<<<<<<< HEAD
        ^SkoarToke.match_toke(buf, offs, Toke_ListSep);
=======
        ^SkoarToke.match_toke(buf, offs, Toke_Choard);
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9
    }

}

<<<<<<< HEAD
Toke_SymbolName : SkoarToke {
    classvar <regex = "[a-zA-Z_][a-zA-Z0-9_]*";
=======
Toke_DynSFZ : SkoarToke {
    classvar <regex = "sfz";
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9

    *match {
        | buf, offs |

<<<<<<< HEAD
        ^SkoarToke.match_toke(buf, offs, Toke_SymbolName);
=======
        ^SkoarToke.match_toke(buf, offs, Toke_DynSFZ);
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9
    }

}

<<<<<<< HEAD
Toke_Slash : SkoarToke {
    classvar <regex = "/(?![/0-9])";
=======
Toke_Comment : SkoarToke {
    classvar <regex = "<[?](.|[\\n\\r\\f])*?[?]>";
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9

    *match {
        | buf, offs |

<<<<<<< HEAD
        ^SkoarToke.match_toke(buf, offs, Toke_Slash);
=======
        ^SkoarToke.match_toke(buf, offs, Toke_Comment);
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9
    }

}

<<<<<<< HEAD
Toke_AlCoda : SkoarToke {
    classvar <regex = "al(la)? coda";
=======
Toke_Eighths : SkoarToke {
    classvar <regex = "\\.?\\]+(?:__?)?\\.?";
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9

    *match {
        | buf, offs |

<<<<<<< HEAD
        ^SkoarToke.match_toke(buf, offs, Toke_AlCoda);
=======
        ^SkoarToke.match_toke(buf, offs, Toke_Eighths);
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9
    }

}

<<<<<<< HEAD
Toke_QuindicesimaB : SkoarToke {
    classvar <regex = "15mb";
=======
Toke_DynPiano : SkoarToke {
    classvar <regex = "(m(ezzo)?p|p+)(iano)?";
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9

    *match {
        | buf, offs |

<<<<<<< HEAD
        ^SkoarToke.match_toke(buf, offs, Toke_QuindicesimaB);
=======
        ^SkoarToke.match_toke(buf, offs, Toke_DynPiano);
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9
    }

}

<<<<<<< HEAD
Toke_Portamento : SkoarToke {
    classvar <regex = "port\\.?";
=======
Toke_Bars : SkoarToke {
    classvar <regex = ":?\\|+:?";
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9

    *match {
        | buf, offs |

<<<<<<< HEAD
        ^SkoarToke.match_toke(buf, offs, Toke_Portamento);
=======
        ^SkoarToke.match_toke(buf, offs, Toke_Bars);
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9
    }

}

<<<<<<< HEAD
Toke_Fine : SkoarToke {
    classvar <regex = "fine";
=======
Toke_Voice : SkoarToke {
    classvar <regex = "\\.(([a-zA-Z_][a-zA-Z0-9_]*)?|\\.+)";
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9

    *match {
        | buf, offs |

<<<<<<< HEAD
        ^SkoarToke.match_toke(buf, offs, Toke_Fine);
=======
        ^SkoarToke.match_toke(buf, offs, Toke_Voice);
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9
    }

}

<<<<<<< HEAD
Toke_Deref : SkoarToke {
    classvar <regex = "!(?![!}]|=)";
=======
Toke_HashLevel : SkoarToke {
    classvar <regex = "\\[#*[ ]*\\]";
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9

    *match {
        | buf, offs |

<<<<<<< HEAD
        ^SkoarToke.match_toke(buf, offs, Toke_Deref);
=======
        ^SkoarToke.match_toke(buf, offs, Toke_HashLevel);
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9
    }

}

<<<<<<< HEAD
Toke_Symbol : SkoarToke {
    classvar <regex = "[\\\\@][a-zA-Z_][a-zA-Z0-9_]*";
=======
Toke_OttavaA : SkoarToke {
    classvar <regex = "8va|ottava (alta|sopra)|all' ottava";
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9

    *match {
        | buf, offs |

<<<<<<< HEAD
        ^SkoarToke.match_toke(buf, offs, Toke_Symbol);
=======
        ^SkoarToke.match_toke(buf, offs, Toke_OttavaA);
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9
    }

}

<<<<<<< HEAD
Toke_SkoarpionEnd : SkoarToke {
    classvar <regex = "![}]";
=======
Toke_Rep : SkoarToke {
    classvar <regex = "%+";
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9

    *match {
        | buf, offs |

<<<<<<< HEAD
        ^SkoarToke.match_toke(buf, offs, Toke_SkoarpionEnd);
=======
        ^SkoarToke.match_toke(buf, offs, Toke_Rep);
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9
    }

}

<<<<<<< HEAD
Toke_DynSFZ : SkoarToke {
    classvar <regex = "sfz";
=======
Toke_OttavaB : SkoarToke {
    classvar <regex = "8vb|ottava (bassa|sotto)";
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9

    *match {
        | buf, offs |

<<<<<<< HEAD
        ^SkoarToke.match_toke(buf, offs, Toke_DynSFZ);
=======
        ^SkoarToke.match_toke(buf, offs, Toke_OttavaB);
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9
    }

}

<<<<<<< HEAD
Toke_Quarters : SkoarToke {
    classvar <regex = "\\.?[)]+(?:__?)?\\.?";
=======
Toke_CondIf : SkoarToke {
    classvar <regex = "[?][?](?![}])";
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9

    *match {
        | buf, offs |

<<<<<<< HEAD
        ^SkoarToke.match_toke(buf, offs, Toke_Quarters);
=======
        ^SkoarToke.match_toke(buf, offs, Toke_CondIf);
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9
    }

}

<<<<<<< HEAD
Toke_AlFine : SkoarToke {
    classvar <regex = "al fine";
=======
Toke_ListS : SkoarToke {
    classvar <regex = "<(?![=?])";
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9

    *match {
        | buf, offs |

<<<<<<< HEAD
        ^SkoarToke.match_toke(buf, offs, Toke_AlFine);
=======
        ^SkoarToke.match_toke(buf, offs, Toke_ListS);
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9
    }

}

<<<<<<< HEAD
Toke_CondS : SkoarToke {
    classvar <regex = "[{][?][\\n]*";
=======
Toke_SymbolName : SkoarToke {
    classvar <regex = "[a-zA-Z_][a-zA-Z0-9_]*";
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9

    *match {
        | buf, offs |

<<<<<<< HEAD
        ^SkoarToke.match_toke(buf, offs, Toke_CondS);
=======
        ^SkoarToke.match_toke(buf, offs, Toke_SymbolName);
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9
    }

}

<<<<<<< HEAD
Toke_DaCapo : SkoarToke {
    classvar <regex = "D\\.C\\.|Da Capo";
=======
Toke_Times : SkoarToke {
    classvar <regex = "[Tt]imes";
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9

    *match {
        | buf, offs |

<<<<<<< HEAD
        ^SkoarToke.match_toke(buf, offs, Toke_DaCapo);
=======
        ^SkoarToke.match_toke(buf, offs, Toke_Times);
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9
    }

}

<<<<<<< HEAD
Toke_OttavaB : SkoarToke {
    classvar <regex = "8vb|ottava (bassa|sotto)";
=======
Toke_Crap : SkoarToke {
    classvar <regex = "crap";
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9

    *match {
        | buf, offs |

<<<<<<< HEAD
        ^SkoarToke.match_toke(buf, offs, Toke_OttavaB);
=======
        ^SkoarToke.match_toke(buf, offs, Toke_Crap);
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9
    }

}

<<<<<<< HEAD
Toke_ListS : SkoarToke {
    classvar <regex = "<(?![=?])";
=======
Toke_Segno : SkoarToke {
    classvar <regex = ",[Ss](?:egno)?`(?:[a-zA-Z_][a-zA-Z0-9_]*`)*";
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9

    *match {
        | buf, offs |

<<<<<<< HEAD
        ^SkoarToke.match_toke(buf, offs, Toke_ListS);
=======
        ^SkoarToke.match_toke(buf, offs, Toke_Segno);
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9
    }

}

<<<<<<< HEAD
Toke_Float : SkoarToke {
    classvar <regex = "(-)?(0|[1-9][0-9]*)\\.[0-9]+(?!Hz)";
=======
Toke_MathOp : SkoarToke {
    classvar <regex = "[+x\\-](?!>|or)";
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9

    *match {
        | buf, offs |

<<<<<<< HEAD
        ^SkoarToke.match_toke(buf, offs, Toke_Float);
=======
        ^SkoarToke.match_toke(buf, offs, Toke_MathOp);
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9
    }

}

<<<<<<< HEAD
Toke_MsgNameWithArgs : SkoarToke {
    classvar <regex = "[a-zA-Z_][a-zA-Z0-9_]*<";
=======
Toke_Fine : SkoarToke {
    classvar <regex = "fine";
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9

    *match {
        | buf, offs |

<<<<<<< HEAD
        ^SkoarToke.match_toke(buf, offs, Toke_MsgNameWithArgs);
=======
        ^SkoarToke.match_toke(buf, offs, Toke_Fine);
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9
    }

}

Toke_String : SkoarToke {
    classvar <regex = "'[^']*'";

    *match {
        | buf, offs |

        ^SkoarToke.match_toke(buf, offs, Toke_String);
    }

}

<<<<<<< HEAD
Toke_DynForte : SkoarToke {
    classvar <regex = "mf(orte)?|f+orte|ff+";
=======
Toke_RWing : SkoarToke {
    classvar <regex = "[)]\\^\\^";
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9

    *match {
        | buf, offs |

<<<<<<< HEAD
        ^SkoarToke.match_toke(buf, offs, Toke_DynForte);
=======
        ^SkoarToke.match_toke(buf, offs, Toke_RWing);
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9
    }

}

<<<<<<< HEAD
Toke_Voice : SkoarToke {
    classvar <regex = "\\.(([a-zA-Z_][a-zA-Z0-9_]*)?|\\.+)";
=======
Toke_Caesura : SkoarToke {
    classvar <regex = "//";
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9

    *match {
        | buf, offs |

<<<<<<< HEAD
        ^SkoarToke.match_toke(buf, offs, Toke_Voice);
=======
        ^SkoarToke.match_toke(buf, offs, Toke_Caesura);
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9
    }

}

<<<<<<< HEAD
Toke_CondE : SkoarToke {
    classvar <regex = "[?][}]";
=======
Toke_DalSegno : SkoarToke {
    classvar <regex = "D\\.S\\.|Dal Segno";
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9

    *match {
        | buf, offs |

<<<<<<< HEAD
        ^SkoarToke.match_toke(buf, offs, Toke_CondE);
=======
        ^SkoarToke.match_toke(buf, offs, Toke_DalSegno);
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9
    }

}

<<<<<<< HEAD
Toke_Choard : SkoarToke {
    classvar <regex = "(D(?![a.])|[ABCEFG])([Mm0-9]|sus|dim)*";
=======
Toke_AlSegno : SkoarToke {
    classvar <regex = "al segno";
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9

    *match {
        | buf, offs |

<<<<<<< HEAD
        ^SkoarToke.match_toke(buf, offs, Toke_Choard);
=======
        ^SkoarToke.match_toke(buf, offs, Toke_AlSegno);
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9
    }

}

<<<<<<< HEAD
Toke_Meter : SkoarToke {
    classvar <regex = "[1-9][0-9]*/[1-9][0-9]*";
=======
Toke_Quarters : SkoarToke {
    classvar <regex = "\\.?[)]+(?:__?)?\\.?";
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9

    *match {
        | buf, offs |

<<<<<<< HEAD
        ^SkoarToke.match_toke(buf, offs, Toke_Meter);
=======
        ^SkoarToke.match_toke(buf, offs, Toke_Quarters);
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9
    }

}

<<<<<<< HEAD
Toke_Freq : SkoarToke {
    classvar <regex = "(0|[1-9][0-9]*)(\\.[0-9]+)?Hz";
=======
Toke_Nosey : SkoarToke {
    classvar <regex = ",";
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9

    *match {
        | buf, offs |

<<<<<<< HEAD
        ^SkoarToke.match_toke(buf, offs, Toke_Freq);
=======
        ^SkoarToke.match_toke(buf, offs, Toke_Nosey);
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9
    }

}

<<<<<<< HEAD
Toke_MsgOp : SkoarToke {
    classvar <regex = "\\.(?![)\\]])";
=======
Toke_Symbol : SkoarToke {
    classvar <regex = "[\\\\@][a-zA-Z_][a-zA-Z0-9_]*";
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9

    *match {
        | buf, offs |

<<<<<<< HEAD
        ^SkoarToke.match_toke(buf, offs, Toke_MsgOp);
=======
        ^SkoarToke.match_toke(buf, offs, Toke_Symbol);
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9
    }

}

<<<<<<< HEAD
Toke_NamedNoat : SkoarToke {
    classvar <regex = "(?:_?)(?:[a-eg]|f(?![ac-zA-Z_]))(#*|b*)";
=======
Toke_OctaveShift : SkoarToke {
    classvar <regex = "~+o|o~+";
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9

    *match {
        | buf, offs |

<<<<<<< HEAD
        ^SkoarToke.match_toke(buf, offs, Toke_NamedNoat);
=======
        ^SkoarToke.match_toke(buf, offs, Toke_OctaveShift);
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9
    }

}

<<<<<<< HEAD
Toke_BooleanOp : SkoarToke {
    classvar <regex = "==|!=|<(?!=)|<=|>(?!=)|>=|and|or|xor";
=======
Toke_Deref : SkoarToke {
    classvar <regex = "!(?![!}]|=)";
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9

    *match {
        | buf, offs |

<<<<<<< HEAD
        ^SkoarToke.match_toke(buf, offs, Toke_BooleanOp);
=======
        ^SkoarToke.match_toke(buf, offs, Toke_Deref);
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9
    }

}

<<<<<<< HEAD
Toke_Eighths : SkoarToke {
    classvar <regex = "\\.?\\]+(?:__?)?\\.?";
=======
Toke_Float : SkoarToke {
    classvar <regex = "(-)?(0|[1-9][0-9]*)\\.[0-9]+(?!Hz)";
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9

    *match {
        | buf, offs |

<<<<<<< HEAD
        ^SkoarToke.match_toke(buf, offs, Toke_Eighths);
=======
        ^SkoarToke.match_toke(buf, offs, Toke_Float);
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9
    }

}

<<<<<<< HEAD
Toke_MathOp : SkoarToke {
    classvar <regex = "[+x\\-](?!>)";
=======
Toke_Crotchets : SkoarToke {
    classvar <regex = "[}]+\\.?";
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9

    *match {
        | buf, offs |

<<<<<<< HEAD
        ^SkoarToke.match_toke(buf, offs, Toke_MathOp);
=======
        ^SkoarToke.match_toke(buf, offs, Toke_Crotchets);
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9
    }

}

<<<<<<< HEAD
Toke_Tuplet : SkoarToke {
    classvar <regex = "/\\d+(:\\d+)?|(du|tri|quadru)plets?|(quin|sex|sep|oc)tuplets?";
=======
Toke_ListE : SkoarToke {
    classvar <regex = ">(?![=])";
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9

    *match {
        | buf, offs |

<<<<<<< HEAD
        ^SkoarToke.match_toke(buf, offs, Toke_Tuplet);
=======
        ^SkoarToke.match_toke(buf, offs, Toke_ListE);
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9
    }

}

<<<<<<< HEAD
Toke_Int : SkoarToke {
    classvar <regex = "(-)?(0|[1-9][0-9]*)(?!Hz|[mv][ab]|\\.[0-9]|/)";
=======
Toke_Tuplet : SkoarToke {
    classvar <regex = "/\\d+(:\\d+)?|(du|tri|quadru)plets?|(quin|sex|sep|oc)tuplets?";
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9

    *match {
        | buf, offs |

<<<<<<< HEAD
        ^SkoarToke.match_toke(buf, offs, Toke_Int);
=======
        ^SkoarToke.match_toke(buf, offs, Toke_Tuplet);
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9
    }

}

<<<<<<< HEAD
Toke_LWing : SkoarToke {
    classvar <regex = "\\^\\^[(]";
=======
Toke_ListSep : SkoarToke {
    classvar <regex = ",";
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9

    *match {
        | buf, offs |

<<<<<<< HEAD
        ^SkoarToke.match_toke(buf, offs, Toke_LWing);
=======
        ^SkoarToke.match_toke(buf, offs, Toke_ListSep);
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9
    }

}

Toke_MsgName : SkoarToke {
    classvar <regex = "[a-zA-Z_][a-zA-Z0-9_]*(?!<)";

    *match {
        | buf, offs |

        ^SkoarToke.match_toke(buf, offs, Toke_MsgName);
    }

}

<<<<<<< HEAD
Toke_CondIf : SkoarToke {
    classvar <regex = "[?][?](?![}])";
=======
Toke_Slash : SkoarToke {
    classvar <regex = "/(?![/0-9])";
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9

    *match {
        | buf, offs |

<<<<<<< HEAD
        ^SkoarToke.match_toke(buf, offs, Toke_CondIf);
=======
        ^SkoarToke.match_toke(buf, offs, Toke_Slash);
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9
    }

}

<<<<<<< HEAD
Toke_SkoarpionStart : SkoarToke {
    classvar <regex = "[{]!";
=======
Toke_True : SkoarToke {
    classvar <regex = "yes";
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9

    *match {
        | buf, offs |

<<<<<<< HEAD
        ^SkoarToke.match_toke(buf, offs, Toke_SkoarpionStart);
=======
        ^SkoarToke.match_toke(buf, offs, Toke_True);
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9
    }

}

<<<<<<< HEAD
Toke_Rep : SkoarToke {
    classvar <regex = "%+";
=======
Toke_CondE : SkoarToke {
    classvar <regex = "[?][}]";
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9

    *match {
        | buf, offs |

<<<<<<< HEAD
        ^SkoarToke.match_toke(buf, offs, Toke_Rep);
=======
        ^SkoarToke.match_toke(buf, offs, Toke_CondE);
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9
    }

}

<<<<<<< HEAD
Toke_Segno : SkoarToke {
    classvar <regex = ",segno`(?:_[a-zA-Z_][a-zA-Z0-9_]*`)*";
=======
Toke_Meter : SkoarToke {
    classvar <regex = "[1-9][0-9]*/[1-9][0-9]*";
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9

    *match {
        | buf, offs |

<<<<<<< HEAD
        ^SkoarToke.match_toke(buf, offs, Toke_Segno);
=======
        ^SkoarToke.match_toke(buf, offs, Toke_Meter);
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9
    }

}

<<<<<<< HEAD
Toke_Volta : SkoarToke {
    classvar <regex = "\\[\\d+\\.\\]";
=======
Toke_Int : SkoarToke {
    classvar <regex = "(-)?(0|[1-9][0-9]*)(?![0-9]*Hz|[mv][ab]|\\.[0-9]|/)";
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9

    *match {
        | buf, offs |

<<<<<<< HEAD
        ^SkoarToke.match_toke(buf, offs, Toke_Volta);
=======
        ^SkoarToke.match_toke(buf, offs, Toke_Int);
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9
    }

}

<<<<<<< HEAD
Toke_Bars : SkoarToke {
    classvar <regex = ":?\\|+:?";
=======
Toke_DaCapo : SkoarToke {
    classvar <regex = "D\\.C\\.|Da Capo";
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9

    *match {
        | buf, offs |

<<<<<<< HEAD
        ^SkoarToke.match_toke(buf, offs, Toke_Bars);
=======
        ^SkoarToke.match_toke(buf, offs, Toke_DaCapo);
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9
    }

}

<<<<<<< HEAD
Toke_ListE : SkoarToke {
    classvar <regex = ">";
=======
Toke_SkoarpionSep : SkoarToke {
    classvar <regex = "!!";
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9

    *match {
        | buf, offs |

<<<<<<< HEAD
        ^SkoarToke.match_toke(buf, offs, Toke_ListE);
=======
        ^SkoarToke.match_toke(buf, offs, Toke_SkoarpionSep);
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9
    }

}

<<<<<<< HEAD
Toke_Semicolon : SkoarToke {
    classvar <regex = ";";
=======
Toke_LWing : SkoarToke {
    classvar <regex = "\\^\\^[(]";
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9

    *match {
        | buf, offs |

<<<<<<< HEAD
        ^SkoarToke.match_toke(buf, offs, Toke_Semicolon);
=======
        ^SkoarToke.match_toke(buf, offs, Toke_LWing);
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9
    }

}

<<<<<<< HEAD
Toke_Quavers : SkoarToke {
    classvar <regex = "o+/\\.?";
=======
Toke_SkoarpionEnd : SkoarToke {
    classvar <regex = "![}]";
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9

    *match {
        | buf, offs |

<<<<<<< HEAD
        ^SkoarToke.match_toke(buf, offs, Toke_Quavers);
=======
        ^SkoarToke.match_toke(buf, offs, Toke_SkoarpionEnd);
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9
    }

}

<<<<<<< HEAD
Toke_Carrot : SkoarToke {
    classvar <regex = "\\^(?!\\^[(])";
=======
Toke_MsgOp : SkoarToke {
    classvar <regex = "\\.(?![)\\]])";
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9

    *match {
        | buf, offs |

<<<<<<< HEAD
        ^SkoarToke.match_toke(buf, offs, Toke_Carrot);
=======
        ^SkoarToke.match_toke(buf, offs, Toke_MsgOp);
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9
    }

}

<<<<<<< HEAD
Toke_AssOp : SkoarToke {
    classvar <regex = "=>|[+]>|->";
=======
Toke_LoopSep : SkoarToke {
    classvar <regex = "::[\\n]*(?![|])";
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9

    *match {
        | buf, offs |

<<<<<<< HEAD
        ^SkoarToke.match_toke(buf, offs, Toke_AssOp);
=======
        ^SkoarToke.match_toke(buf, offs, Toke_LoopSep);
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9
    }

}

<<<<<<< HEAD
Toke_AlSegno : SkoarToke {
    classvar <regex = "al segno";
=======
Toke_LoopE : SkoarToke {
    classvar <regex = ":[}]";
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9

    *match {
        | buf, offs |

<<<<<<< HEAD
        ^SkoarToke.match_toke(buf, offs, Toke_AlSegno);
=======
        ^SkoarToke.match_toke(buf, offs, Toke_LoopE);
    }

}

Toke_MsgNameWithArgs : SkoarToke {
    classvar <regex = "[a-zA-Z_][a-zA-Z0-9_]*<";

    *match {
        | buf, offs |

        ^SkoarToke.match_toke(buf, offs, Toke_MsgNameWithArgs);
    }

}

Toke_AssOp : SkoarToke {
    classvar <regex = "=>|[+]>|->";

    *match {
        | buf, offs |

        ^SkoarToke.match_toke(buf, offs, Toke_AssOp);
    }

}

Toke_Coda : SkoarToke {
    classvar <regex = "\\([+]\\)(?:`(?:[a-zA-Z_][a-zA-Z0-9_]*`)*)?";

    *match {
        | buf, offs |

        ^SkoarToke.match_toke(buf, offs, Toke_Coda);
    }

}

Toke_AlCoda : SkoarToke {
    classvar <regex = "al(la)? coda";

    *match {
        | buf, offs |

        ^SkoarToke.match_toke(buf, offs, Toke_AlCoda);
    }

}

Toke_Semicolon : SkoarToke {
    classvar <regex = ";";

    *match {
        | buf, offs |

        ^SkoarToke.match_toke(buf, offs, Toke_Semicolon);
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9
    }

}

<<<<<<< HEAD
Toke_Nosey : SkoarToke {
    classvar <regex = ",";
=======
Toke_NamedNoat : SkoarToke {
    classvar <regex = "(?:_?)(?:[a-g](?![ac-zA-Z_]))(#|b)?";
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9

    *match {
        | buf, offs |

        ^SkoarToke.match_toke(buf, offs, Toke_Nosey);
    }

}

<<<<<<< HEAD
Toke_Crotchets : SkoarToke {
    classvar <regex = "[}]+\\.?";
=======
Toke_Quavers : SkoarToke {
    classvar <regex = "o+/\\.?";
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9

    *match {
        | buf, offs |

<<<<<<< HEAD
        ^SkoarToke.match_toke(buf, offs, Toke_Crotchets);
=======
        ^SkoarToke.match_toke(buf, offs, Toke_Quavers);
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9
    }

}

<<<<<<< HEAD
Toke_PedalDown : SkoarToke {
    classvar <regex = "Ped\\.?";
=======
Toke_Fairy : SkoarToke {
    classvar <regex = "[$]";
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9

    *match {
        | buf, offs |

<<<<<<< HEAD
        ^SkoarToke.match_toke(buf, offs, Toke_PedalDown);
=======
        ^SkoarToke.match_toke(buf, offs, Toke_Fairy);
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9
    }

}

<<<<<<< HEAD
Toke_OttavaA : SkoarToke {
    classvar <regex = "8va|ottava (alta|sopra)|all' ottava";
=======
Toke_Loco : SkoarToke {
    classvar <regex = "loco";
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9

    *match {
        | buf, offs |

<<<<<<< HEAD
        ^SkoarToke.match_toke(buf, offs, Toke_OttavaA);
=======
        ^SkoarToke.match_toke(buf, offs, Toke_Loco);
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9
    }

}

<<<<<<< HEAD
Toke_Coda : SkoarToke {
    classvar <regex = "\\([+]\\)";
=======
Toke_Carrot : SkoarToke {
    classvar <regex = "\\^(?!\\^[(])";
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9

    *match {
        | buf, offs |

<<<<<<< HEAD
        ^SkoarToke.match_toke(buf, offs, Toke_Coda);
=======
        ^SkoarToke.match_toke(buf, offs, Toke_Carrot);
    }

}

Toke_SkoarpionStart : SkoarToke {
    classvar <regex = "[{]!";

    *match {
        | buf, offs |

        ^SkoarToke.match_toke(buf, offs, Toke_SkoarpionStart);
>>>>>>> 91d4f5525bf234d23a9cb6f638b65f9b9a2937d9
    }

}

