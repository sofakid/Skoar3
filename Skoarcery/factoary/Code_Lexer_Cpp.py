import unittest

from Skoarcery import terminals, emissions, underskoar_cpp


bs = "{"
be = "}"


class Code_Lexer_Cpp(unittest.TestCase):

    def setUp(self):
        terminals.init()
        emissions.init()
        
    def preamble(self):
        emissions.CPP.raw("""#include "lex.hpp"
#include "exception.hpp"
""")

    def exceptions(self):

        CPP = emissions.CPP
        
    def base_token(self):
        underskoar_cpp.skoarToke_cpp()

    def odd_balls(self):
        underskoar_cpp.EOF_token()
        underskoar_cpp.whitespace_token()

    def typical_token(self, token):
        underskoar_cpp.typical_token_cpp(token)

    def preamble_h(self):
        emissions.CPP.raw("""#pragma once
#include "skoarcery.hpp"
""")
  
    def base_token_h(self):
        underskoar_cpp.skoarToke_h()

    def odd_balls_h(self):
        underskoar_cpp.EOF_token_h()
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
        for token in terminals.tokens.values():
            if token not in terminals.odd_balls:
                self.typical_token(token)

        fd.close()

    def test_HPP_lexer(self):

        underskoar_cpp.init(emissions.CPP)

        fd = open("SkoarCpp/lex.hpp", mode="w")

        emissions.CPP.fd = fd
        emissions.CPP.file_header("lex", "Code_Cpp_Lexer")

        self.preamble_h()
        self.base_token_h()
        self.odd_balls_h()

        emissions.CPP.cmt_hdr("Everyday Tokes")
        for token in terminals.tokens.values():
            if token not in terminals.odd_balls:
                self.typical_token_h(token)

        fd.close()

        # fwd headers
        fd = open("SkoarCpp/lex_fwd.hpp", mode="w")

        HPP = emissions.CPP
        HPP.fd = fd
        HPP.file_header("lex_fwd", "Code_Cpp_Lexer")

        HPP.raw("""#pragma once
class SkoarToke;
class Toke_Whitespace;
class Toke_EOF;

""")
        for token in terminals.tokens.values():
            if token not in terminals.odd_balls:
                HPP.stmt("class "+ token.toker_name)

        fd.close()