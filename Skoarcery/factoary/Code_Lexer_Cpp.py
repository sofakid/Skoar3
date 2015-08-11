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

""")

    def dispensary(self):
        emissions.CPP.raw("""
   
SkoarDispensary::SkoarDispensary() {
""")
        for token in SortedTerminals:
            if token not in terminals.odd_balls:
                emissions.CPP.raw("table[ESkoarToke::"+ token.name +"""] = 
        [](wstring *buf, size_t offs) {
            return """+ token.toker_name +"""::match_toke(buf, offs);
        };
""")
        emissions.CPP.raw("""
}

SkoarToke *SkoarDispensary::match_toke(ESkoarToke::Kind want, wstring *buf, size_t offs) {
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
enum Kind {
        Unknown = 0,
        Eof,
        Whitespace,
""")
        for token in SortedTerminals:
            if token not in terminals.odd_balls:
                CPP.raw("    " + token.name + ",\n")

        CPP.raw("""
};
};

namespace ESkoarNoad {
enum Kind {
    unknown = 0,
    toke,
    artificial,
    args,
""")

        for x in SortedNonterminals:
            CPP.raw("    " + x.name + ",\n")

        CPP.raw("\n};\n};\n")

    def dispensary_h(self):
        emissions.CPP.raw("""
class SkoarDispensary {
    map<ESkoarToke::Kind, function<SkoarToke*(wstring *buf, size_t offs)>> table;
public: 
    SkoarDispensary();   
    SkoarToke *match_toke(ESkoarToke::Kind want, wstring *buf, size_t offs);
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
    enum Kind;
};
namespace ESkoarNoad {
    enum Kind;
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


    def test_HPP_styles(self):

        underskoar_cpp.init(emissions.CPP)

        fd = open("SkoarCpp/skoarstyles_unreal.hpp", mode="w")

        max_toke = 0;
        for token in SortedTerminals:
            n = len(token.name) + 1
            if n > max_toke:
                max_toke = n

        max_noad = 0;
        for x in SortedNonterminals:
            n = len(x.name) + 1
            if n > max_noad:
                max_noad = n

        _ = _____ = emissions.CPP
        _.fd = fd
        _.file_header("skoarstyles_unreal.hpp", "Code_Cpp_Lexer")

        _.raw("""#pragma once
#include "skoar_public.hpp"
#include "CodeEditorStyle.h"

typedef function<void(std::string &, FColor &)> StyleSpell;
""")

        #
        # struct FSkoarSyntaxTextStyle
        #
        #
        #
  
        _.raw("""

    /*struct FSkoarSyntaxTextStyle
	{
		FSkoarSyntaxTextStyle()
""")
        c = "            : "
        for token in SortedTerminals:
            if token not in terminals.odd_balls:
                _.raw(c + token.name +'TextStyle(FSkoarEditorStyle::Get().GetWidgetStyle<FTextBlockStyle>("SyntaxHighlight.Skoar.Toke.'+ token.name +'"))')
                c = "\n            , "
        for x in SortedNonterminals:
            _.raw(c + x.name +'TextStyle(FSkoarEditorStyle::Get().GetWidgetStyle<FTextBlockStyle>("SyntaxHighlight.Skoar.Noad.'+ x.name +'"))')
                
        _.raw('''
        {
        }

		FSkoarSyntaxTextStyle(
            ''')
        c = ""
        for token in SortedTerminals:
            if token not in terminals.odd_balls:
                _.raw(c + "const FTextBlockStyle& In" + token.name +'TextStyle')
                c = ",\n            "
        for x in SortedNonterminals:
            _.raw(c + "const FTextBlockStyle& In" + x.name +'TextStyle')

        c = ")\n            : "
        for token in SortedTerminals:
            if token not in terminals.odd_balls:
                _.raw(c + token.name +"TextStyle(In" + token.name +'TextStyle)')
                c = "\n            , "
        for x in SortedNonterminals:
            _.raw(c + x.name +"TextStyle(In" + x.name +'TextStyle)')

        _.raw('''
       {
       }

''')
 
        c = "        "
        for token in SortedTerminals:
            if token not in terminals.odd_balls:
                _.raw(c +"FTextBlockStyle "+ token.name +"TextStyle;\n")
        for x in SortedNonterminals:
            _.raw(c +"FTextBlockStyle "+ x.name +"TextStyle;\n")
            
        _.raw("""
	};
    */

    """)


        #
        # class FSkoarStyle
        #
        #
        #
        _.raw("""
class FSkoarStyle {
    
public:

    map<ESkoarToke::Kind, std::string> toke_to_id;
    map<ESkoarToke::Kind, FColor> toke_to_colour;
    map<ESkoarToke::Kind, FTextBlockStyle> toke_to_style;
    
    map<ESkoarNoad::Kind, std::string> noad_to_id;
    map<ESkoarNoad::Kind, FColor> noad_to_colour;
    map<ESkoarNoad::Kind, FTextBlockStyle> noad_to_style;


    
    explicit FSkoarStyle() {
        """)
        _.cmt_hdr("Toke Ids")
        for token in SortedTerminals:
            if token not in terminals.odd_balls:
                _.stmt('toke_to_id[ESkoarToke::'+ token.name +']'.ljust(max_toke - len(token.name)) 
                       +' = "SyntaxHighlight.Skoar.Toke.'+ token.name +'"')
                
        _.nl()
        _.cmt_hdr("Noad Ids")
        for x in SortedNonterminals:
            _.stmt('noad_to_id[ESkoarNoad::'+ x.name +']'.ljust(max_noad - len(x.name)) 
                       +' = "SyntaxHighlight.Skoar.Noad.'+ x.name +'"')
        
        
        _.nl()
        _.cmt_hdr("Toke Colours")
        for token in SortedTerminals:
            if token not in terminals.odd_balls:
                _.stmt('toke_to_colour[ESkoarToke::'+ token.name +']'.ljust(max_toke - len(token.name)) 
                       +' = FColor::FromHex(L"CCCCCCFF")')
        
        _.nl()        
        _.cmt_hdr("Noad Colours")
        for x in SortedNonterminals:
            _.stmt('noad_to_colour[ESkoarNoad::'+ x.name +']'.ljust(max_noad - len(x.name)) 
                       +' = FColor::FromHex(L"CCCCCC05")')
        _.raw("""
    }

    void init_styles() {
    """)   
        _.nl()
        _.cmt_hdr("Toke Styles")
        for token in SortedTerminals:
            if token not in terminals.odd_balls:
                _.stmt('toke_to_style[ESkoarToke::'+ token.name +']'.ljust(max_toke - len(token.name)) 
                       +' = FSkoarEditorStyle::Get().GetWidgetStyle<FTextBlockStyle>("SyntaxHighlight.Skoar.Toke.'+ token.name +'")')
        
        _.nl()        
        _.cmt_hdr("Noad Styles")
        for x in SortedNonterminals:
            _.stmt('noad_to_style[ESkoarNoad::'+ x.name +']'.ljust(max_noad - len(x.name)) 
                       +' = FSkoarEditorStyle::Get().GetWidgetStyle<FTextBlockStyle>("SyntaxHighlight.Skoar.Noad.'+ x.name +'")')
                   
                    
        _.raw("""
    }

    void each(StyleSpell spell) {
        each_toke(spell);        
        each_noad(spell);        
    }

    void each_toke(StyleSpell spell) {
        for (auto kv: toke_to_id) {
            auto eKind = kv.first;
            auto id = kv.second;
            auto colour = toke_to_colour[eKind];
            spell(id, colour);        
        }
    }
    
    void each_noad(StyleSpell spell) {
        for (auto kv: noad_to_id) {
            auto eKind = kv.first;
            auto id = kv.second;
            auto colour = noad_to_colour[eKind];
            spell(id, colour);        
        }
    }

};
        """)
        
        fd.close()

    def test_HPP_style_snippets(self):

        underskoar_cpp.init(emissions.CPP)

        fd = open("SkoarCpp/skoarstyle_snippets.cpp.txt", mode="w")

        _ = _____ = emissions.CPP
        _.fd = fd
        _.file_header("skoarstyle_snippets.cpp.txt", "Code_Cpp_Lexer")

        #_.nl()
        #_.cmt_hdr("Tokes")
        #for token in terminals.tokens.values():
        #    if token not in terminals.odd_balls:
        #        _.stmt('StyleSet->Set("SyntaxHighlight.Skoar.Toke.'+ token.name +
        #              '", FTextBlockStyle(NormalText).SetColorAndOpacity(FLinearColor(FColor(0xffdfd706))))')
        #_.nl()
        #        
        #_.cmt_hdr("Noads")
        #for x in nonterminals.nonterminals.values():
        #    _.stmt('StyleSet->Set("SyntaxHighlight.Skoar.Noad.'+ x.name +
        #        '", FTextBlockStyle(NormalText).SetColorAndOpacity(FLinearColor(FColor(0xffdfd706))))')
                
      

        fd.close();