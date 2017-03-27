import unittest
from Skoarcery import langoids, terminals, nonterminals, dragonsets, parsetable, emissions
from Skoarcery.langoids import Terminal, Nonterminal
from Skoarcery.emissions import Arg    

SortedTerminals = []

class Code_Parser_Cpp(unittest.TestCase):

    def setUp(self):
        global SortedTerminals
        terminals.init()
        nonterminals.init()
        langoids.init()
        dragonsets.init()
        parsetable.init()
        emissions.init()
        SortedTerminals = sorted(terminals.tokens.values())

    def test_CPP_rdpp(self):
        global SortedTerminals
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

        N = nonterminals.nonterminals.values()

        # precompute desirables
        num_productions = 0
        for A in N:
            R = A.production_rules
            # each production
            for P in R:
                if P.derives_empty:
                    continue
                P.index = num_productions
                num_productions = num_productions + 1

        CPP.set_class("SkoarStats")
        CPP.constructor()
        
        for token in SortedTerminals:
            if token not in terminals.odd_balls:
                ____CPP.raw("    tokeFreq[ESkoarToke::" + token.name + "] = 0.0f;\n")

        ____CPP.nl()
        ____CPP.stmt("desirables = new list<ESkoarToke::Kind>[" + str(num_productions) + "]")
       
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
                CPP.array_set("desirables", P.index, "{", end="")
                for toke in desires:
                    CPP.raw("ESkoarToke::" + toke.name)
                    i += 1
                    if i != n:
                        if i % 4 == 0:
                            CPP.raw(",\n")
                            CPP.stmt("                  ", end="")
                        else:
                            CPP.raw(", ")

                else:
                    CPP.raw("};\n")

        CPP.end() # CPP.constructor

        CPP.raw("""
static SkoarStats* skoarStats = nullptr;

bool localCmp(const ESkoarToke::Kind &a, const ESkoarToke::Kind &b) {
    return skoarStats->tokeFreq[a] > skoarStats->tokeFreq[b]; 
}
    
void localSortDesirables() {
    for (int i = 0; i < """ + str(num_productions) + """; ++i) {
        skoarStats->desirables[i].sort(localCmp);    
    }
}

""")

        CPP.set_class("SkoarParser")

        CPP.raw("""

void SkoarParser::init() {
    skoarStats = new SkoarStats();
}

""")
        HPP.stmt("static void init()");

        # write each nonterminal as a function
        for A in N:

            R = A.production_rules

            #CPP.cmt(str(A))
            
            Ax = Arg("SkoarNoadPtr", A.name)
            AStrx = Arg("wstring", '"'+ A.name +'"')
            Noadx = Arg("SkoarNoadPtr", "noad")
            Parentx = Arg("SkoarNoadPtr", "parent")
            Desiresx = Arg("list<ESkoarToke::Kind>*", "desires")
            
            HPP.method_h(Ax, Parentx)
            CPP.method(Ax, Parentx)

            if A.intermediate:
                CPP.var(Noadx, Parentx.name)
            else:
                CPP.var(Noadx, "SkoarNoad::New<ESkoarNoad::"+ A.name +">(wstring(L\""+ A.name +"\"), parent)")

            CPP.var(Desiresx, CPP.null)
            CPP.nl()

            CPP.if_("++deep > 1000")
            ____CPP.stmt("this->fail_too_deep(parent)")
            CPP.end_if()

            # each production
            for P in R:

                if P.derives_empty:
                    continue

                # A -> alpha
                alpha = P.production

                CPP.cmt(str(P))
                CPP.stmt("desires = &" + CPP.v_array_get("skoarStats->desirables", P.index))


                CPP.if_("toker->sees(desires) != nullptr")
                ____CPP.stmt('SkoarNoadPtr toke_noad')

                # debugging
                #CPP.print(str(P))

                for x in alpha:
                    if isinstance(x, Terminal):
                        CPP.stmt('skoarStats->tokeFreq[ESkoarToke::' + x.name + '] += 0.1f')
                        CPP.stmt('toke_noad = SkoarNoad::New(wstring(L"' + x.toker_name + '"), noad, toker->burn(ESkoarToke::' + x.name + ', noad))')
                        CPP.stmt('noad->add_noad(toke_noad)')

                        # debugging
                        #CPP.print("burning: " + x.name)
                    else:
                        if x.intermediate:
                            CPP.stmt(CPP.this + "->" + x.name + "(noad)")
                        else:
                            CPP.stmt("noad->add_noad(this->" + x.name + "(noad))")
                else:
                    CPP.stmt("--deep")
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
                CPP.stmt("this->fail(noad)")
                CPP.return_(CPP.null)

            CPP.end() # CPP.method(Ax, Parentx)

        CPP.nl()

        SortDesirables = Arg("void", "sortDesirables")
        HPP.method_h(SortDesirables)
        CPP.method(SortDesirables)
        CPP.stmt("localSortDesirables()")
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
#include "skoarcery.hpp"
#include "noad_fwd.hpp"
#include "exception_fwd.hpp"
#include "toker.hpp"
#include "spells.hpp"

struct SkoarStats {

    SkoarStats();

    // use a float so it never overflows when adding a small constant to it, 
    // just eventually stops making a difference.
    map<ESkoarToke::Kind, float> tokeFreq;
    list<ESkoarToke::Kind> *desirables;

};

""")

        CPP.raw("""#include "rdpp.hpp"
#include "exception.hpp"
#include "lex.hpp"
#include "noad.hpp"

""")
        
        HPP.class_("SkoarParser")
        CPP.set_class("SkoarParser")
        
        fail_ = Arg("void","fail")
        noad_ = Arg("SkoarNoadPtr","noad")

        fail_too_deep_ = Arg("void","fail_too_deep")

        toker_fail_ = Arg("void","toker_fail")
        skoar_error_ = Arg("SkoarError&","e")
        
        HPP.method_h(fail_, noad_)
        CPP.method(fail_, noad_)
        CPP.stmt("toker->dump()")
        CPP.stmt("throw SkoarParseException(L\"Fail\", noad)")
        CPP.end()

        HPP.method_h(fail_too_deep_, noad_)
        CPP.method(fail_too_deep_, noad_)
        CPP.stmt("toker->dump()")
        CPP.stmt("throw SkoarParseException(L\"Parse tree too deep!\", noad)")
        CPP.end()

        HPP.raw("""
    SkoarToker *toker;
    int deep;
""")
        toker_ = Arg("SkoarToker *", "tokr")
        HPP.constructor_h(toker_)
        CPP.constructor(toker_)
        CPP.raw("""
    deep = 0;
    toker = tokr;
    
""")
        CPP.end()
