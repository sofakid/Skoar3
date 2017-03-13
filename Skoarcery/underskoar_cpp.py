from Skoarcery import terminals, emissions
from Skoarcery.emissions_sc import ScTongue
from Skoarcery.emissions_py import PyTongue
from Skoarcery.emissions_cpp import CppTongue
from Skoarcery.emissions import Arg    

# underskoarcery :P
_ = _____ = _________ = _____________ = _________________ = _____________________ = None

# -------
# Symbols
# -------
SkoarToke_ = "SkoarToke"
lexeme_ = Arg("wstring", "lexeme")
regex_ = Arg("const wregex", "rgx")
size_ = Arg("size_t", "size")
inspectable_ = "inspectable"
burn_ = Arg("size_t", "burn")
match_obj_ = Arg("wsmatch", "matches")
buf_ = Arg("wstring *", "buf")
offs_ = Arg("size_t", "offs")
toke_class_ = "toke_class"
match_toke_ = Arg("SkoarToke*", "match_toke")
s_ = Arg("wstring", "s")
n_ = Arg("size_t", "n")
kind_ = Arg("ESkoarToke::Kind", "kind");
style_ = Arg("SkoarStyles::EStyle", "style")
  
SkoarError_ = "SkoarError"
SubclassResponsibilityError_ = "SubclassResponsibilityError"


#
# configure schematics to output a language
# implemented by one of the tongues in emissions
def init(tongue):
    global _, _____, _________, _____________, _________________, _____________________
    assert tongue in emissions.tongues
    _ = _____ = _________ = _____________ = _________________ = _____________________ = tongue


def skoarToke_cpp():

    _.static_var(match_obj_)

    _.cmt_hdr("Abstract SkoarToke")

    _.last_class = SkoarToke_

    _.constructor()
    _____.stmt("kind = ESkoarToke::Unknown")
    _____.stmt("style = SkoarStyles::EStyle::nostyle")
    _.end()

    _.constructor(s_, offs_, n_)
    _____.stmt(_.v_ass(_.v_attr(lexeme_), s_))
    _____.stmt(_.v_ass(_.v_attr(offs_), offs_))
    _____.stmt(_.v_ass(_.v_attr(size_), n_))
    _____.stmt("kind = ESkoarToke::Unknown")
    _____.stmt("style = SkoarStyles::EStyle::nostyle")
    _____.stmt("++SkoarMemories.Tokes")
    _.end()
    
    _.destructor()
    _____.stmt("--SkoarMemories.Tokes")
    _.end()

    _.cmt("how many characters to burn from the buffer")
    _.method(burn_)
    _____.return_(size_)
    _.end()

    #_.cmt("we override and return " + _.null + " for no match, new toke otherwise")
    #_.method(match_toke_, buf_, offs_)
    #_____.return_("nullptr")
    #_.end()

    #_____.abstract_static_method(match_meth_, buf_, offs_)
    #_________.throw(SubclassResponsibilityError_, _.v_str("What are you doing human?"))
    #_____.end()


def skoarToke_h():

    regex = toke_class_ + _.v_static_accessor() + regex_.name

    _.cmt_hdr("Abstract Token")

    _.abstract_class(SkoarToke_)

    _____.attrvar("<", lexeme_)
    _____.attrvar("", offs_)
    _____.attrvar("", size_)
    _____.attrvar("", kind_)
    _____.attrvar("", style_)


    _____.nl()

    _____.constructor_h()
    _____.constructor_h(s_, offs_, n_)

    _____.destructor_h()
    
    _____.cmt("how many characters to burn from the buffer")
    _____.method_h(burn_)
    
    #_____.cmt("match requested toke")
    #_____.virtual_method_h(match_toke_, buf_, offs_)
    #_____.stmt("template<typename T>", end="\n")
    #_____.static_method(match_toke_, buf_,offs_)
    #_________.var(match_obj_)
    ##_________.find_regex(match_, regex, buf_, offs_)
    #_________.if_(match_obj_.name +" == "+ _.null)
    #_____________.return_(_.null)
    #_________.end_if()

    # todo: use matched string and length of match
    #_________.return_(_.v_new("T", buf_, offs_))
    #_____.end()

    
    _.end_class()

def whitespace_token():

    Whitespace = terminals.Whitespace

    _.cmt_hdr("Whitespace is special")
    _.set_class(Whitespace.toker_name)

    _.classvar_assign(regex_, _.v_def_regex(Whitespace.regex))
    _.nl()
    _.method(burn_, buf_, offs_)
    #_____.var(match_obj_)

    _____.stmt("auto found = std::regex_search(buf->cbegin() + offs, buf->cend(), "+ match_obj_.name +", "+ 
               Whitespace.toker_name +"::"+ regex_.name +", regex_constants::match_continuous)")
    
    _____.if_("!found")
    _________.return_("0")
    _____.end_if()

    _____.return_(match_obj_.name +"[0].length()")
    _.end()
    
def whitespace_token_h():

    Whitespace = terminals.Whitespace
   
    _.cmt_hdr("Whitespace is special")
    _.set_class(Whitespace.toker_name)

    _.class_(Whitespace.toker_name, SkoarToke_)
    _____.classvar_declare("<", regex_)
    _____.nl()

    _____.static_method_h(burn_, buf_, offs_)
    _.end_class()

    
def Eof_token():

    Eof = terminals.Eof

    _.cmt_hdr("Eof is special")
    _.set_class(Eof.toker_name)
    
    _.constructor()
    _____.stmt("kind = ESkoarToke::Eof")
    _____.stmt("++SkoarMemories.Tokes")
    _.end()
    
    _.destructor()
    _____.stmt("--SkoarMemories.Tokes")
    _.end()

    _.method(burn_, buf_, offs_)
    _____.if_(buf_.name + "->size() > " + offs_.name)
    _________.throw(SkoarError_, _.v_str("Tried to burn Eof when there's more input."))
    _____.end_if()
    _____.return_("0")
    _.end()

    _.method(match_toke_, buf_, offs_)
    #_____.if_(buf_.name + "->size() < " + offs_.name)
    #_________.throw(SkoarError_, _.v_str("Tried to burn Eof when there's more input."))
    #_____.end_if()
    _____.if_(buf_.name + "->size() == " + offs_.name)
    _________.return_("new "+ Eof.toker_name +"()")
    _____.end_if()
    _____.return_(_.null)
    _.end()
   
def Eof_token_h():

    Eof = terminals.Eof

    _.cmt_hdr("Eof is special")
    _.class_(Eof.toker_name, SkoarToke_)
    
    _____.nl()
    _____.constructor_h()
    _____.destructor_h()
    
    _____.static_method_h(burn_, buf_, offs_)
    _____.static_method_h(match_toke_, buf_, offs_)
    _.end_class()

def typical_token_cpp(token):

    #inspectable = _.true if token.name in terminals.inspectables else _.false
    _.set_class(token.toker_name)

    _.stmt("const std::wregex "+ token.toker_name +"::"+ regex_.name +" = "+ _.v_def_regex(token.regex))
  
    kind_token_ = Arg("ESkoarToke::Kind", "ESkoarToke::" + token.name);
    style_token_ = Arg("SkoarStyles::EStyle", "SkoarStyles::style<ESkoarToke::" + token.name + ">()")

    _.constructor(s_, offs_, n_)
    _____.stmt(_.v_ass(_.v_attr(lexeme_), s_))
    _____.stmt(_.v_ass(_.v_attr(offs_), offs_))
    _____.stmt(_.v_ass(_.v_attr(size_), n_))
    _____.stmt(_.v_ass(_.v_attr(kind_), kind_token_))
    _____.stmt(_.v_ass(_.v_attr(style_), style_token_))
    _____.stmt("++SkoarMemories.Tokes")
    _.end()
    
    _.destructor()
    _____.stmt("--SkoarMemories.Tokes")
    _.end()

    _.method(match_toke_, buf_, offs_)
    #_____.var(match_obj_)
    _____.stmt("auto found = std::regex_search(buf->cbegin() + offs, buf->cend(), "+ match_obj_.name +", "+ 
               token.toker_name +"::"+ regex_.name +", regex_constants::match_continuous)")
    
    _____.if_("!found")
    _________.return_(_.null)
    _____.end_if()
    _____.stmt("auto s = wstring("+ match_obj_.name +".str())")
    _____.return_("new "+ token.toker_name +"(s,offs,s.length())")
    #_________.return_(SkoarToke_ + _.v_static_accessor() + match_toke_.name +"<"+ token.toker_name +">("+ buf_.name +", "+ offs_.name +")")
    _.end()

def typical_token_h(token):

    _.class_(token.toker_name, SkoarToke_)
    _____.classvar_declare("<", regex_)
    _____.nl()
   
    _____.nl()
    _____.constructor_h(s_, offs_, n_)
    _____.destructor_h()

    _____.static_method_h(match_toke_, buf_, offs_)
    _.end_class()


