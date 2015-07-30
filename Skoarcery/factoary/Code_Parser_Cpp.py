import unittest
from Skoarcery import langoids, terminals, nonterminals, dragonsets, parsetable, emissions
from Skoarcery.langoids import Terminal, Nonterminal
from Skoarcery.emissions import Arg    



class Code_Parser_Cpp(unittest.TestCase):

    def setUp(self):
        terminals.init()
        nonterminals.init()
        langoids.init()
        dragonsets.init()
        parsetable.init()
        emissions.init()

    def test_CPP_rdpp(self):
        from Skoarcery.dragonsets import FIRST, FOLLOW
        from Skoarcery.terminals import Empty

        fd = open("SkoarCpp/rdpp.cpp", "w")
        fdh = open("SkoarCpp/rdpp.hpp", "w")

        ____CPP = CPP = emissions.CPP
        CPP.fd = fd

        ____HPP = HPP = emissions.HPP
        HPP.fd = fdh

        # Header
        # Imports
        # class SkoarParseException
        # class SkoarParser:
        #     init
        #     fail
        self.code_start()

        CPP.tab += 1
        N = nonterminals.nonterminals.values()

        # precompute desirables
        #HPP.class_("SkoarParser")
        CPP.set_class("SkoarParser")

        init_desirables = Arg("void", "init_desirables")
        HPP.method_h(init_desirables)
        CPP.method(init_desirables)

        for A in N:

            R = A.production_rules

            CPP.nl()
            CPP.cmt(str(A))

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
                CPP.dict_set("desirables", str(P), "{", end="")
                for toke in desires:
                    CPP.raw(toke.toker_name +"::instance()")
                    i += 1
                    if i != n:
                        if i % 5 == 0:
                            CPP.raw(",\n")
                            CPP.stmt("           ", end="")
                        else:
                            CPP.raw(", ")

                else:
                    CPP.raw("};\n")

        CPP.end()

        # write each nonterminal as a function
        for A in N:

            R = A.production_rules

            #CPP.cmt(str(A))
            
            Ax = Arg("SkoarNoad*", A.name)
            AStrx = Arg("string", '"'+ A.name +'"')
            Noadx = Arg("SkoarNoad*", "noad")
            Parentx = Arg("SkoarNoad*", "parent")
            Desiresx = Arg("list<SkoarToke *>*", "desires")
            
            HPP.method_h(Ax, Parentx)
            CPP.method(Ax, Parentx)
            
            if A.intermediate:
                CPP.var(Noadx, Parentx.name)
            else:
                CPP.var(Noadx, "new SkoarNoad(string(\""+ A.name +"\"), SkoarNoad* parent);")

            CPP.var(Desiresx, CPP.null)
            CPP.nl()

            CPP.if_("++deep > 100")
            ____CPP.stmt("this->fail_too_deep()")
            CPP.end_if()

            # each production
            for P in R:

                if P.derives_empty:
                    continue

                # A -> alpha
                alpha = P.production

                CPP.stmt("desires = &" + CPP.v_dict_get("desirables", str(P)))

                CPP.cmt(str(P))

                CPP.if_("toker.sees(desires) != nullptr")

                # debugging
                #CPP.print(str(P))

                for x in alpha:
                    if isinstance(x, Terminal):
                        CPP.stmt('noad->add_toke("' + x.toker_name + '", toker.burn(' + x.toker_name + '))')

                        # debugging
                        #CPP.print("burning: " + x.name)
                    else:
                        if x.intermediate:
                            CPP.stmt(CPP.this + "->" + x.name + "(noad)")
                        else:
                            CPP.stmt("noad->add_noad(this->" + x.name + "(noad))")
                else:
                    CPP.stmt("--deep;")
                    CPP.return_("noad")

                CPP.end_if()

            if A.derives_empty:
                CPP.cmt("<e>")

                # debugging
                #CPP.print("burning empty")

                CPP.stmt("--deep")
                CPP.return_("noad")

            else:
                CPP.cmt("Error State")
                CPP.stmt("this->fail()")
                CPP.return_(CPP.null)

            CPP.end()

        CPP.end()
        HPP.end_class()

        fd.close()
        fdh.close()

    def code_start(self):
        CPP = emissions.CPP
        CPP.file_header("rdpp", "Code_Parser_Cpp - Create Recursive Descent Predictive Parser")
        
        HPP = emissions.HPP
        HPP.file_header("rdpp", "Code_Parser_Cpp - Create Recursive Descent Predictive Parser")

        HPP.raw("""#pragma once
#include "skoar.hpp"
#include "toker.hpp"

""")
        CPP.raw("""#include "rdpp.hpp"
""")
        
        s_ = Arg("string", "s")
        HPP.class_("SkoarParseException", "SkoarError")
        HPP.constructor_h()
        HPP.constructor_h(s_)
        HPP.end_class()

        CPP.set_class("SkoarParseException")
        CPP.constructor()
        CPP.stmt("sWhat = string(\"Unknown reason.\")")
        CPP.end()

        CPP.constructor(s_)
        CPP.stmt("sWhat = s");
        CPP.end()
        
        HPP.class_("SkoarParser")
        CPP.set_class("SkoarParser")
        
        fail_ = Arg("void","fail")
        fail_too_deep_ = Arg("void","fail_too_deep")
        
        HPP.method_h(fail_)
        CPP.method(fail_)
        CPP.stmt("toker.dump()")
        CPP.stmt("throw new SkoarParseException(\"Fail\");")
        CPP.end()

        HPP.method_h(fail_too_deep_)
        CPP.method(fail_too_deep_)
        CPP.stmt("toker.dump()")
        CPP.stmt("throw new SkoarParseException(\"Parse tree too deep!\");")
        CPP.end()

        HPP.raw("""
    Skoar *runtime;
    SkoarToker toker;
    int deep;
    map<string, list<SkoarToke*>> desirables;
        """)

        runtime_ = Arg("Skoar *", "runtime")
        
        HPP.constructor_h(runtime_)
        CPP.constructor(runtime_)
        CPP.raw("""
    this->runtime = runtime;
    this->deep = 0;
    this->init_desirables();
""")
        CPP.end()
