import unittest

from Skoarcery import terminals, emissions, underskoar


bs = "{"
be = "}"


class Code_Lexer_Sc(unittest.TestCase):

    def setUp(self):
        terminals.init()
        emissions.init()
        underskoar.init(emissions.SC)

    def exceptions(self):

        SC = emissions.SC
        SC.cmt_hdr("SkoarException")
        SC.class_("SkoarError", "Exception")

        SC.static_method("new", "msg")
        SC.return_("super.new(msg)")
        SC.end()

        SC.static_method("errorString")
        SC.return_('"SKOAR" ++ super.errorString')
        SC.end()

        SC.end()

    def base_token(self):
        underskoar.skoarToke()

    def EOF_token(self):
        underskoar.EOF_token()

    def whitespace_token(self):
        underskoar.whitespace_token()

    def typical_token(self, token):
        underskoar.typical_token(token)

    def test_SC_lexer(self):

        fd = open("SuperCollider/Skoar/lex.sc", mode="w")

        emissions.SC.fd = fd
        emissions.SC.file_header("lex", "Code_Sc_Lexer")

        self.exceptions()
        self.base_token()
        self.whitespace_token()
        self.EOF_token()

        emissions.SC.cmt_hdr("Everyday Tokes")
        for token in terminals.tokens.values():
            if token not in terminals.odd_balls:
                self.typical_token(token)

        fd.close()