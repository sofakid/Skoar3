// ================================================================================
// lex.sc - Generated by Code_Sc_Lexer on 2014-10-27 18:15:22 for SuperCollider 3.6
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
    var <>val;
    var <>pre_repeat;
    var <>post_repeat;
    classvar <regex = nil;
    classvar <inspectable = false;

    *new {
        | s |

        ^super.new.init( s );
    }

    init {
        | s |

        lexeme = s;
    }

    // how many characters to burn from the buffer
    burn {
        ^lexeme.size;
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
        try {
            match = buf.findRegexp(toke_class.regex, offs);
            if (match[0][0] == offs) {
                ^toke_class.new(match[0][1]);
            };

        } {
            // pass
        }

        ^nil;
    }

}

// ---------------------
// Whitespace is special
// ---------------------
Toke_Whitespace : SkoarToke {
    classvar <regex = "^([ \\t]*)";

    *burn {
        | buf, offs |

        var match;
        try {
            match = buf.findRegexp(Toke_Whitespace.regex, offs);
            if (match[0][0] == offs) {
                ^match[0][1].size;
            };

        } {
            // pass
        }

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
Toke_DynFP : SkoarToke {
    classvar <regex = "^(fp)";
    classvar <inspectable = false;

    *match {
        | buf, offs |

        ^SkoarToke.match_toke(buf, offs, Toke_DynFP);
    }

}

Toke_QuindicesimaA : SkoarToke {
    classvar <regex = "^(15ma|alla quindicesima)";
    classvar <inspectable = false;

    *match {
        | buf, offs |

        ^SkoarToke.match_toke(buf, offs, Toke_QuindicesimaA);
    }

}

Toke_NamedNoat : SkoarToke {
    classvar <regex = "^((?:_?)(?:[a-eg]|f(?![ac-zA-Z_]))(#*|b*))";
    classvar <inspectable = true;

    *match {
        | buf, offs |

        ^SkoarToke.match_toke(buf, offs, Toke_NamedNoat);
    }

}

Toke_ListSep : SkoarToke {
    classvar <regex = "^(,)";
    classvar <inspectable = false;

    *match {
        | buf, offs |

        ^SkoarToke.match_toke(buf, offs, Toke_ListSep);
    }

}

Toke_Caesura : SkoarToke {
    classvar <regex = "^(//)";
    classvar <inspectable = false;

    *match {
        | buf, offs |

        ^SkoarToke.match_toke(buf, offs, Toke_Caesura);
    }

}

Toke_ListS : SkoarToke {
    classvar <regex = "^(<(?![=?]))";
    classvar <inspectable = false;

    *match {
        | buf, offs |

        ^SkoarToke.match_toke(buf, offs, Toke_ListS);
    }

}

Toke_SkoarpionEnd : SkoarToke {
    classvar <regex = "^(![}])";
    classvar <inspectable = false;

    *match {
        | buf, offs |

        ^SkoarToke.match_toke(buf, offs, Toke_SkoarpionEnd);
    }

}

Toke_PedalDown : SkoarToke {
    classvar <regex = "^(Ped)";
    classvar <inspectable = false;

    *match {
        | buf, offs |

        ^SkoarToke.match_toke(buf, offs, Toke_PedalDown);
    }

}

Toke_Volta : SkoarToke {
    classvar <regex = "^(\\[\\d+\\.\\])";
    classvar <inspectable = true;

    *match {
        | buf, offs |

        ^SkoarToke.match_toke(buf, offs, Toke_Volta);
    }

}

Toke_DynForte : SkoarToke {
    classvar <regex = "^(mf(orte)?|f+orte|ff+)";
    classvar <inspectable = true;

    *match {
        | buf, offs |

        ^SkoarToke.match_toke(buf, offs, Toke_DynForte);
    }

}

Toke_Crotchets : SkoarToke {
    classvar <regex = "^([}]+\\.?)";
    classvar <inspectable = true;

    *match {
        | buf, offs |

        ^SkoarToke.match_toke(buf, offs, Toke_Crotchets);
    }

}

Toke_Tuplet : SkoarToke {
    classvar <regex = "^(/\\d+(:\\d+)?|(du|tri|quadru)plets?|(quin|sex|sep|oc)tuplets?)";
    classvar <inspectable = true;

    *match {
        | buf, offs |

        ^SkoarToke.match_toke(buf, offs, Toke_Tuplet);
    }

}

Toke_CurNoat : SkoarToke {
    classvar <regex = "^([$])";
    classvar <inspectable = false;

    *match {
        | buf, offs |

        ^SkoarToke.match_toke(buf, offs, Toke_CurNoat);
    }

}

Toke_Float : SkoarToke {
    classvar <regex = "^((-)?(0|[1-9][0-9]*)\\.[0-9]+)";
    classvar <inspectable = true;

    *match {
        | buf, offs |

        ^SkoarToke.match_toke(buf, offs, Toke_Float);
    }

}

Toke_Carrot : SkoarToke {
    classvar <regex = "^(\\^(?!\\^[(]))";
    classvar <inspectable = true;

    *match {
        | buf, offs |

        ^SkoarToke.match_toke(buf, offs, Toke_Carrot);
    }

}

Toke_Newline : SkoarToke {
    classvar <regex = "^([\\n\\r\\f]+)";
    classvar <inspectable = false;

    *match {
        | buf, offs |

        ^SkoarToke.match_toke(buf, offs, Toke_Newline);
    }

}

Toke_Comment : SkoarToke {
    classvar <regex = "^(<[?](.|[\\n\\r\\f])*?[?]>)";
    classvar <inspectable = false;

    *match {
        | buf, offs |

        ^SkoarToke.match_toke(buf, offs, Toke_Comment);
    }

}

Toke_DalSegno : SkoarToke {
    classvar <regex = "^(D\\.S\\.|Dal Segno)";
    classvar <inspectable = false;

    *match {
        | buf, offs |

        ^SkoarToke.match_toke(buf, offs, Toke_DalSegno);
    }

}

Toke_Int : SkoarToke {
    classvar <regex = "^((-)?(0|[1-9][0-9]*)(?![mv][ab]|\\.[0-9]|/))";
    classvar <inspectable = true;

    *match {
        | buf, offs |

        ^SkoarToke.match_toke(buf, offs, Toke_Int);
    }

}

Toke_Slur : SkoarToke {
    classvar <regex = "^([+][+])";
    classvar <inspectable = false;

    *match {
        | buf, offs |

        ^SkoarToke.match_toke(buf, offs, Toke_Slur);
    }

}

Toke_CondSep : SkoarToke {
    classvar <regex = "^(;)";
    classvar <inspectable = false;

    *match {
        | buf, offs |

        ^SkoarToke.match_toke(buf, offs, Toke_CondSep);
    }

}

Toke_AlCoda : SkoarToke {
    classvar <regex = "^(al(la)? coda)";
    classvar <inspectable = false;

    *match {
        | buf, offs |

        ^SkoarToke.match_toke(buf, offs, Toke_AlCoda);
    }

}

Toke_AlFine : SkoarToke {
    classvar <regex = "^(al fine)";
    classvar <inspectable = false;

    *match {
        | buf, offs |

        ^SkoarToke.match_toke(buf, offs, Toke_AlFine);
    }

}

Toke_Choard : SkoarToke {
    classvar <regex = "^((D(?![a.])|[ABCEFG])([Mm0-9]|sus|dim)*)";
    classvar <inspectable = true;

    *match {
        | buf, offs |

        ^SkoarToke.match_toke(buf, offs, Toke_Choard);
    }

}

Toke_AlSegno : SkoarToke {
    classvar <regex = "^(al segno)";
    classvar <inspectable = false;

    *match {
        | buf, offs |

        ^SkoarToke.match_toke(buf, offs, Toke_AlSegno);
    }

}

Toke_RWing : SkoarToke {
    classvar <regex = "^([)]\\^\\^)";
    classvar <inspectable = false;

    *match {
        | buf, offs |

        ^SkoarToke.match_toke(buf, offs, Toke_RWing);
    }

}

Toke_MsgName : SkoarToke {
    classvar <regex = "^([a-zA-Z_][a-zA-Z0-9_]*(?!<))";
    classvar <inspectable = true;

    *match {
        | buf, offs |

        ^SkoarToke.match_toke(buf, offs, Toke_MsgName);
    }

}

Toke_Quarters : SkoarToke {
    classvar <regex = "^(\\.?[)]+(?:__)?\\.?)";
    classvar <inspectable = true;

    *match {
        | buf, offs |

        ^SkoarToke.match_toke(buf, offs, Toke_Quarters);
    }

}

Toke_Symbol : SkoarToke {
    classvar <regex = "^([\\\\@][a-zA-Z_][a-zA-Z0-9_]*)";
    classvar <inspectable = true;

    *match {
        | buf, offs |

        ^SkoarToke.match_toke(buf, offs, Toke_Symbol);
    }

}

Toke_Nosey : SkoarToke {
    classvar <regex = "^(,)";
    classvar <inspectable = false;

    *match {
        | buf, offs |

        ^SkoarToke.match_toke(buf, offs, Toke_Nosey);
    }

}

Toke_OttavaA : SkoarToke {
    classvar <regex = "^(8va|ottava (alta|sopra)|all' ottava)";
    classvar <inspectable = false;

    *match {
        | buf, offs |

        ^SkoarToke.match_toke(buf, offs, Toke_OttavaA);
    }

}

Toke_SymbolName : SkoarToke {
    classvar <regex = "^([a-zA-Z_][a-zA-Z0-9_]*)";
    classvar <inspectable = true;

    *match {
        | buf, offs |

        ^SkoarToke.match_toke(buf, offs, Toke_SymbolName);
    }

}

Toke_CondE : SkoarToke {
    classvar <regex = "^([?][}])";
    classvar <inspectable = false;

    *match {
        | buf, offs |

        ^SkoarToke.match_toke(buf, offs, Toke_CondE);
    }

}

Toke_String : SkoarToke {
    classvar <regex = "^('[^']*')";
    classvar <inspectable = true;

    *match {
        | buf, offs |

        ^SkoarToke.match_toke(buf, offs, Toke_String);
    }

}

Toke_Coda : SkoarToke {
    classvar <regex = "^(\\([+]\\))";
    classvar <inspectable = false;

    *match {
        | buf, offs |

        ^SkoarToke.match_toke(buf, offs, Toke_Coda);
    }

}

Toke_Eighths : SkoarToke {
    classvar <regex = "^(\\.?\\]+(?:__)?\\.?)";
    classvar <inspectable = true;

    *match {
        | buf, offs |

        ^SkoarToke.match_toke(buf, offs, Toke_Eighths);
    }

}

Toke_Portamento : SkoarToke {
    classvar <regex = "^(port\\.?)";
    classvar <inspectable = false;

    *match {
        | buf, offs |

        ^SkoarToke.match_toke(buf, offs, Toke_Portamento);
    }

}

Toke_MsgOp : SkoarToke {
    classvar <regex = "^(\\.(?![)\\]]))";
    classvar <inspectable = false;

    *match {
        | buf, offs |

        ^SkoarToke.match_toke(buf, offs, Toke_MsgOp);
    }

}

Toke_SkoarpionSep : SkoarToke {
    classvar <regex = "^(!!)";
    classvar <inspectable = false;

    *match {
        | buf, offs |

        ^SkoarToke.match_toke(buf, offs, Toke_SkoarpionSep);
    }

}

Toke_Quavers : SkoarToke {
    classvar <regex = "^(o+/\\.?)";
    classvar <inspectable = true;

    *match {
        | buf, offs |

        ^SkoarToke.match_toke(buf, offs, Toke_Quavers);
    }

}

Toke_CondS : SkoarToke {
    classvar <regex = "^([{][?])";
    classvar <inspectable = false;

    *match {
        | buf, offs |

        ^SkoarToke.match_toke(buf, offs, Toke_CondS);
    }

}

Toke_ListE : SkoarToke {
    classvar <regex = "^(>)";
    classvar <inspectable = false;

    *match {
        | buf, offs |

        ^SkoarToke.match_toke(buf, offs, Toke_ListE);
    }

}

Toke_Loco : SkoarToke {
    classvar <regex = "^(loco)";
    classvar <inspectable = false;

    *match {
        | buf, offs |

        ^SkoarToke.match_toke(buf, offs, Toke_Loco);
    }

}

Toke_Rep : SkoarToke {
    classvar <regex = "^(%+)";
    classvar <inspectable = true;

    *match {
        | buf, offs |

        ^SkoarToke.match_toke(buf, offs, Toke_Rep);
    }

}

Toke_MsgNameWithArgs : SkoarToke {
    classvar <regex = "^([a-zA-Z_][a-zA-Z0-9_]*<)";
    classvar <inspectable = true;

    *match {
        | buf, offs |

        ^SkoarToke.match_toke(buf, offs, Toke_MsgNameWithArgs);
    }

}

Toke_OctaveShift : SkoarToke {
    classvar <regex = "^(~+o|o~+)";
    classvar <inspectable = true;

    *match {
        | buf, offs |

        ^SkoarToke.match_toke(buf, offs, Toke_OctaveShift);
    }

}

Toke_DaCapo : SkoarToke {
    classvar <regex = "^(D\\.C\\.|Da Capo)";
    classvar <inspectable = false;

    *match {
        | buf, offs |

        ^SkoarToke.match_toke(buf, offs, Toke_DaCapo);
    }

}

Toke_Bars : SkoarToke {
    classvar <regex = "^(:?\\|+:?)";
    classvar <inspectable = true;

    *match {
        | buf, offs |

        ^SkoarToke.match_toke(buf, offs, Toke_Bars);
    }

}

Toke_Fine : SkoarToke {
    classvar <regex = "^(fine)";
    classvar <inspectable = false;

    *match {
        | buf, offs |

        ^SkoarToke.match_toke(buf, offs, Toke_Fine);
    }

}

Toke_DynPiano : SkoarToke {
    classvar <regex = "^((mp|p+)(iano)?)";
    classvar <inspectable = true;

    *match {
        | buf, offs |

        ^SkoarToke.match_toke(buf, offs, Toke_DynPiano);
    }

}

Toke_QuindicesimaB : SkoarToke {
    classvar <regex = "^(15mb|alla quindicesimb)";
    classvar <inspectable = false;

    *match {
        | buf, offs |

        ^SkoarToke.match_toke(buf, offs, Toke_QuindicesimaB);
    }

}

Toke_Segno : SkoarToke {
    classvar <regex = "^(,segno`(?:_[a-zA-Z_][a-zA-Z0-9_]*`)*)";
    classvar <inspectable = true;

    *match {
        | buf, offs |

        ^SkoarToke.match_toke(buf, offs, Toke_Segno);
    }

}

Toke_DynSFZ : SkoarToke {
    classvar <regex = "^(sfz)";
    classvar <inspectable = false;

    *match {
        | buf, offs |

        ^SkoarToke.match_toke(buf, offs, Toke_DynSFZ);
    }

}

Toke_PedalUp : SkoarToke {
    classvar <regex = "^([*])";
    classvar <inspectable = false;

    *match {
        | buf, offs |

        ^SkoarToke.match_toke(buf, offs, Toke_PedalUp);
    }

}

Toke_AssOp : SkoarToke {
    classvar <regex = "^(=>|[+]>|->)";
    classvar <inspectable = false;

    *match {
        | buf, offs |

        ^SkoarToke.match_toke(buf, offs, Toke_AssOp);
    }

}

Toke_Meter : SkoarToke {
    classvar <regex = "^([1-9][0-9]*/[1-9][0-9]*)";
    classvar <inspectable = true;

    *match {
        | buf, offs |

        ^SkoarToke.match_toke(buf, offs, Toke_Meter);
    }

}

Toke_LWing : SkoarToke {
    classvar <regex = "^(\\^\\^[(])";
    classvar <inspectable = false;

    *match {
        | buf, offs |

        ^SkoarToke.match_toke(buf, offs, Toke_LWing);
    }

}

Toke_Voice : SkoarToke {
    classvar <regex = "^(\\.(([a-zA-Z_][a-zA-Z0-9_]*)?|\\.+))";
    classvar <inspectable = true;

    *match {
        | buf, offs |

        ^SkoarToke.match_toke(buf, offs, Toke_Voice);
    }

}

Toke_SkoarpionStart : SkoarToke {
    classvar <regex = "^([{]!)";
    classvar <inspectable = false;

    *match {
        | buf, offs |

        ^SkoarToke.match_toke(buf, offs, Toke_SkoarpionStart);
    }

}

Toke_BooleanOp : SkoarToke {
    classvar <regex = "^(==|!=|<=|>=|in|nin|and|or|xor)";
    classvar <inspectable = true;

    *match {
        | buf, offs |

        ^SkoarToke.match_toke(buf, offs, Toke_BooleanOp);
    }

}

Toke_OttavaB : SkoarToke {
    classvar <regex = "^(8vb|ottava (bassa|sotto))";
    classvar <inspectable = false;

    *match {
        | buf, offs |

        ^SkoarToke.match_toke(buf, offs, Toke_OttavaB);
    }

}

Toke_SeqRef : SkoarToke {
    classvar <regex = "^(!(?![!}]))";
    classvar <inspectable = false;

    *match {
        | buf, offs |

        ^SkoarToke.match_toke(buf, offs, Toke_SeqRef);
    }

}

Toke_Slash : SkoarToke {
    classvar <regex = "^(/(?!/))";
    classvar <inspectable = false;

    *match {
        | buf, offs |

        ^SkoarToke.match_toke(buf, offs, Toke_Slash);
    }

}

