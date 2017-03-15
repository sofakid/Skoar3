import unittest
from Skoarcery import langoids, terminals, terminals_colours, nonterminals, nonterminals_colours, dragonsets, parsetable, emissions
from Skoarcery.langoids import Terminal, Nonterminal


class Code_Parser_Sc(unittest.TestCase):

    def setUp(self):
        terminals.init()
        terminals_colours.init()
        nonterminals.init()
        nonterminals_colours.init()
        langoids.init()
        dragonsets.init()
        parsetable.init()
        emissions.init()

    def test_SC_rdpp(self):
        from Skoarcery.dragonsets import FIRST, FOLLOW
        from Skoarcery.terminals import Empty

        fd = open("SuperCollider/Skoar/rdpp.sc", "w")
        ____SC = SC = emissions.SC
        SC.fd = fd

        # Header
        # Imports
        # class SkoarParseException
        # class SkoarParser:
        #     init
        #     fail
        self.code_start()

        SC.tab += 1
        N = nonterminals.nonterminals.values()

        # precompute desirables
        SC.static_method("init_desirables")
        for A in N:

            R = A.production_rules

            SC.nl()
            SC.cmt(str(A))

            # each production
            for P in R:

                if P.derives_empty:
                    continue

                # A -> alpha
                alpha = P.production

                desires = FIRST(alpha)

                if Empty in desires:
                    desires.discard(Empty)
                    desires.update(FOLLOW(A))

                i = 0

                n = len(desires)
                SC.dict_set("desirables", str(P), "[", end="")
                for toke in desires:
                    SC.raw(toke.toker_name)
                    i += 1
                    if i != n:
                        if i % 5 == 0:
                            SC.raw(",\n")
                            SC.stmt("           ", end="")
                        else:
                            SC.raw(", ")

                else:
                    SC.raw("]);\n")

        SC.end()

        # write each nonterminal as a function
        for A in N:

            R = A.production_rules

            #SC.cmt(str(A))
            SC.method(A.name, "parent")

            if A.intermediate:
                SC.var("noad", "parent")
            else:
                SC.var("noad", SC.v_new("SkoarNoad", SC.v_sym(A.name), "parent"))

            SC.var("desires", SC.null)
            SC.nl()

            SC.stmt("deep = deep + 1")
            SC.if_("deep > 1000")
            ____SC.stmt("this.fail_too_deep")
            SC.end_if()

            # each production
            for P in R:

                if P.derives_empty:
                    continue

                # A -> alpha
                alpha = P.production

                SC.stmt("desires = " + SC.v_dict_get("SkoarParser.desirables", str(P)))

                SC.cmt(str(P))

                SC.if_("toker.sees(desires).notNil")

                # debugging
                #SC.print(str(P))

                for x in alpha:
                    if isinstance(x, Terminal):
                        SC.stmt('runtime.add_toke(noad, ' + SC.v_sym(x.toker_name) + ', toker.burn(' + x.toker_name + '))')

                        # debugging
                        #SC.print("burning: " + x.name)
                    else:
                        if x.intermediate:
                            SC.stmt(SC.this + "." + x.name + "(noad)")
                        else:
                            SC.stmt("noad.add_noad(this." + x.name + "(noad))")
                else:
                    SC.stmt("deep = deep - 1")
                    SC.return_("noad")

                SC.end_if()

            if A.derives_empty:
                SC.cmt("<e>")

                # debugging
                #SC.print("burning empty")

                SC.stmt("deep = deep - 1")
                SC.return_("noad")

            else:
                SC.cmt("Error State")
                SC.stmt("this.fail")

            SC.end()

        SC.end()

        fd.close()

    def code_start(self):
        SC = emissions.SC
        SC.file_header("rdpp", "Code_Parser_Sc - Create Recursive Descent Predictive Parser")
        SC.raw("""
SkoarParseException : Exception {

}

SkoarParser {

    classvar <desirables;
    var runtime, toker, deep;

    *new {
        | rt |
        ^super.new.init( rt )
    }

    init {
        | rt |
        runtime = rt;
        toker = runtime.toker;
        deep = 0;
    }

    *initClass {
        desirables = IdentityDictionary();
        SkoarParser.init_desirables;
    }

    fail {
        //toker.dump;
        SkoarParseException("Fail").throw;
    }

    fail_too_deep {
        "Parse tree too deep!".postln;
        //toker.dump;
        SkoarParseException("Parse tree too deep").throw;
    }


    //print {
    //    | line, end |
    //    (line ++ end).postln;
    //}

""")

    def test_SC_style_template(self):

        fd = open("SuperCollider/Skoar/ui_colour_template.sc", mode="w")

        _ = emissions.SC
        _.fd = fd
        _.file_header("ui_colour_template.sc", "Code_Sc_Parser")

        _.cmt_hdr("Noad Colours")
        _.raw("""
SkoarUiColourTemplate {

    classvar <defaults;

    *initClass {
        defaults = (
            """)
        x = ""
        for token in terminals.tokens.values():
            colour = terminals_colours.token_colours.get(token.name)
            if colour is not None:
                _.raw(x + "'" + token.toker_name + "': Color.fromHexString(\"" + colour + "\")")
                x = ",\n            "

        for noad in nonterminals.nonterminals.values():
            colour = nonterminals_colours.nonterminals_colours.get(noad.name)
            if colour is not None:
                _.raw(x + "'" + noad.name + "': Color.fromHexString(\"" + colour + "\")")
                x = ",\n            "

        _.raw("""
        );
    }
}
        """)
        fd.close()

