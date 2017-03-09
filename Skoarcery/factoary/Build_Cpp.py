import unittest
from Skoarcery.factoary.Buildoar import Buildoar
from Skoarcery.factoary.Code_Lexer_Cpp import Code_Lexer_Cpp
from Skoarcery.factoary.Code_Parser_Cpp import Code_Parser_Cpp
from Skoarcery.laboaratoary.TestDragonSpells import DragonTests
from Skoarcery.laboaratoary.TestParseTable import Verify_LL_1
from Skoarcery.laboaratoary.TestNonterminals import TestNonterminals
from Skoarcery.laboaratoary.TestTerminals import TestTokens
#from Skoarcery.laboaratoary.Test_Sclang import Test_Sclang


class Build_Cpp(Buildoar):

    def build(self):

        #
        # Grammar
        self.step("Test Grammar",
                  [TestTokens, TestNonterminals, Verify_LL_1, DragonTests])

        #
        # Lexer
        self.step("Build Lexer", Code_Lexer_Cpp)

        # #
        # # Toke Inspector
        #
        # self.run_tests("Build toke inspector", Code_Lexer_Inspector_Sc))

        #
        # Parser
        self.step("Build Parser", Code_Parser_Cpp)

        #
        # SuperCollider should compile class lib
        #self.step("Compile Parser", Test_Sclang)

        #
        # Apparatus
        #self.step("Sanity", [Test_Apparatus, ExamineParseTree, Test_Performer])


if __name__ == '__main__':
    unittest.main()
