import unittest

from Skoarcery import terminals, nonterminals, emissions, underskoar_cpp


bs = "{"
be = "}"

SortedTerminals = []
SortedNonterminals = []

class Code_Lexer_Cpp(unittest.TestCase):

    def setUp(self):
        global SortedTerminals, SortedNonterminals
        terminals.init()
        nonterminals.init()
        emissions.init()

        SortedTerminals = sorted(terminals.tokens.values())
        SortedNonterminals = sorted(nonterminals.nonterminals.values())
        
    def preamble(self):
        emissions.CPP.raw("""#include "lex.hpp"
#include "exception.hpp"
#include "memories.hpp"

""")

    def dispensary(self):
        emissions.CPP.raw("""
   
SkoarDispensary::SkoarDispensary() :
   table({
""")
        comma = ""
        for token in SortedTerminals:
            if token not in terminals.odd_balls:
                emissions.CPP.raw(comma)
                comma = ",\n"
                emissions.CPP.raw("        { ESkoarToke::"+ token.name +""", 
            [](wstring *buf, size_t offs) {
                return """+ token.toker_name +"""::match_toke(buf, offs);
            }
        }""")            
        emissions.CPP.raw("""
   })
{
}

SkoarToke* SkoarDispensary::match_toke(ESkoarToke::Kind want, wstring *buf, size_t offs) {
    auto f = table[want];
    if (f) 
        return f(buf, offs);
    return nullptr;
}
""")

    def exceptions(self):

        CPP = emissions.CPP
        
    def base_token(self):
        underskoar_cpp.skoarToke_cpp()

    def odd_balls(self):
        underskoar_cpp.Eof_token()
        underskoar_cpp.whitespace_token()

    def typical_token(self, token):
        underskoar_cpp.typical_token_cpp(token)

    def preamble_h(self):
        CPP = emissions.CPP
        CPP.raw("""#pragma once
#include "skoarcery.hpp"

""")
  
    def enum_h(self):
        ____CPP = CPP = emissions.CPP
        CPP.raw("""
namespace ESkoarToke {
    enum Kind : unsigned int {
        Unknown = 0,
        Eof,
        Whitespace,
""")
        for token in SortedTerminals:
            if token not in terminals.odd_balls:
                CPP.raw("        " + token.name + ",\n")

        CPP.raw("""
    };
};

namespace ESkoarNoad {
    enum Kind : unsigned int {
        unknown = 0,
        toke,
        artificial,
        alias,
""")

        for x in SortedNonterminals:
            CPP.raw("        " + x.name + ",\n")

        CPP.raw('''    \n};\n};

#include "styles.hpp"

''')

    def dispensary_h(self):
        emissions.CPP.raw("""
class SkoarDispensary {
    map<ESkoarToke::Kind, function<SkoarToke* (wstring *buf, size_t offs)>> table;
public: 
    SkoarDispensary();   
    SkoarToke* match_toke(ESkoarToke::Kind want, wstring *buf, size_t offs);
};
""")

    def base_token_h(self):
        underskoar_cpp.skoarToke_h()

    def odd_balls_h(self):
        underskoar_cpp.Eof_token_h()
        underskoar_cpp.whitespace_token_h()

    def typical_token_h(self, token):
        underskoar_cpp.typical_token_h(token)

    def test_CPP_lexer(self):

        underskoar_cpp.init(emissions.CPP)

        fd = open("SkoarCpp/lex.cpp", mode="w")

        emissions.CPP.fd = fd
        emissions.CPP.file_header("lex", "Code_Cpp_Lexer")

        self.preamble()
        self.base_token()
        self.odd_balls()

        emissions.CPP.cmt_hdr("Everyday Tokes")
        for token in SortedTerminals:
            if token not in terminals.odd_balls:
                self.typical_token(token)

        self.dispensary()
        fd.close()

    def test_HPP_lexer(self):

        underskoar_cpp.init(emissions.CPP)

        fd = open("SkoarCpp/lex.hpp", mode="w")

        emissions.CPP.fd = fd
        emissions.CPP.file_header("lex", "Code_Cpp_Lexer")

        self.preamble_h()
        self.enum_h()
        self.base_token_h()
        self.odd_balls_h()

        emissions.CPP.cmt_hdr("Everyday Tokes")
        for token in SortedTerminals:
            if token not in terminals.odd_balls:
                self.typical_token_h(token)

        self.dispensary_h()
        fd.close()

        # fwd headers
        fd = open("SkoarCpp/lex_fwd.hpp", mode="w")

        HPP = emissions.CPP
        HPP.fd = fd
        HPP.file_header("lex_fwd", "Code_Cpp_Lexer")

        HPP.raw("""#pragma once

namespace ESkoarToke {
    enum Kind : unsigned int;
};
namespace ESkoarNoad {
    enum Kind : unsigned int;
};
class SkoarDispensary;
class SkoarToke;
class Toke_Whitespace;
class Toke_Eof;

""")
        for token in SortedTerminals:
            if token not in terminals.odd_balls:
                HPP.stmt("class "+ token.toker_name)

        fd.close()
