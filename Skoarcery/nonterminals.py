src = """
#
# Skoar Nonterminals
#
# like_this for nonterminals, LikeThis for terminals
#
# <e> is the empty string
#
# + before a nonterminal indicates this is an intermediate step that can be
# skipped in the constructed parse tree, it will not create a new skoarnode,
# instead appending its noads to its parent's children list.


skoar              : branches
+branches          : branch branches | <e>
branch             : opt_voiced_phrases Newline

opt_voiced_phrases : optional_voice phrases
+optional_voice    : Voice | <e>

+phrases           : phrasey phrases | <e>
+phrasey           : Comment | marker | expr | al_goto | beat

+phrasishes        : phrasish phrasishes | <e>
+phrasish          : Comment | marker | expr | al_goto | beat | Newline optional_voice

+opt_sig            : SkoarpionArgs opt_args opt_cloasures opt_expoarts | <e>
+opt_args           : args | <e>
args                : opt_newline args_entries 
args_entries        : SymbolColon expr moar_args_entries | SymbolName moar_args_entries
+moar_args_entries       : opt_newline moar_args_entries_prime
+moar_args_entries_prime : ListSep opt_newline args_entries | <e>
+opt_newline             : Newline | <e>

skoarpion          : opt_sig SkoarpionStart skrp_suffix
skrp_suffix        : skrp_lines SkoarpionEnd

+opt_cloasures         : cloasures | <e>
cloasures              : ListS cloasures_suffix
+cloasures_suffix      : opt_newline cloasures_entries cloasures_end
+cloasures_end         : ListE opt_newline
+cloasures_entries     : SymbolName moar_cloasures_entries
+moar_cloasures_entries: ListSep moar_cloasures_entries | Newline moar_cloasures_entries | cloasures_entries | <e>

+opt_expoarts         : expoarts | <e>
expoarts              : ExpoartsS expoarts_suffix
+expoarts_suffix      : opt_newline expoarts_entries expoarts_end | expoarts_end
+expoarts_end         : ExpoartsE opt_newline
+expoarts_entries     : SymbolName moar_expoarts_entries
+moar_expoarts_entries: ListSep moar_expoarts_entries | Newline moar_expoarts_entries | expoarts_entries | <e>


+skrp_lines        : opt_voiced_phrases skrp_moar_lines
+skrp_moar_lines   : Newline skrp_lines | <e>

listy              : ListS listy_suffix
+listy_suffix      : Newline listy_entries ListE | listy_entries ListE | ListE
+listy_entries     : expr moar_listy_entries
+moar_listy_entries: ListSep moar_listy_entries | Newline moar_listy_entries | listy_entries | <e>

marker             : Coda | Bars
al_goto            : AlCoda 

beat               : regular_beat | exact_beat | exact_rest 
regular_beat       : Crotchets | Quavers | Quarters | Eighths
exact_beat         : ExactBeat expr Quarters
exact_rest         : ExactRest expr Crotchets

# dynamic | 
musical_keyword      : ottavas | musical_keyword_misc
musical_keyword_misc : Carrot
ottavas              : OctaveShift 
#dynamic              : DynPiano | DynForte | DynSFZ | DynFP

nouny            : cthulhu | meditation | conditional | loop | nouny_literal | musical_keyword | listy | deref | skoarpion
+nouny_literal   : Duration | ugen | Tuplet | Freq | Int | Float | String | Choard | NamedNoat | Symbol | Fairy | HashLevel | False | True | Cat | lute

lute             : Lute | LuteWithArgs listy_suffix

deref            : Deref deref_prime
+deref_prime     : MsgNameWithArgs listy_suffix | MsgName

cthulhu          : LWing Semicolon cthulhu_prime
+cthulhu_prime   : boolean_expr Semicolon RWing | Nosey Semicolon RWing

conditional      : CondS cond_if CondE
cond_if          : opt_newline boolean_expr opt_newline CondIf if_body cond_else
cond_else        : CondIf if_body | <e>

# +cond_ifs        : cond_if cond_ifs_suffix
# +cond_ifs_suffix : Newline cond_ifs | <e>
# cond_if          : optional_voice boolean_expr CondIf if_body cond_else
# +cond_else       : CondIf if_body | <e>

if_body          : phrasishes

loop             : LoopS loop_body loop_condition LoopE
loop_body        : phrasishes
loop_condition   : LoopSep boolean_expr | <e>

meditation       : MeditationS skrp_lines MeditationE

ugen             : ugen_with_args | ugen_simple
ugen_simple      : AUGen | KUGen | DUGen
ugen_with_args   : AUGenWithArgs listy_suffix | KUGenWithArgs listy_suffix | DUGenWithArgs listy_suffix




#expr             : SymbolColon expr | msgable expr_prime
#expr_prime       : math expr_prime | boolean | times | <e> 
times            : Times

#boolean          : BooleanOp expr
boolean_expr     : expr
#math*            : MathOp msgable

# right recursive version:
#expr             : expr_a 
#expr_a           : SymbolColon expr_b | expr_b 
#expr_b           : expr_b BooleanOr expr_c | expr_c
#expr_c           : expr_c BooleanAnd expr_d | expr_d
#expr_d           : expr_d CmpEqNeq expr_e | expr_e
#expr_e           : expr_e CmpGtLt expr_f | expr_f
#expr_f           : expr_f MathOpAddSub expr_g | expr_g
#expr_g           : expr_g MathOpMulDivMod expr_h | expr_h
#expr_h           : BracketS expr BracketE | msgable

# after eliminating left recursion:
expr             : assignment opt_times
assignment       : SymbolColon boolean_or | boolean_or 

boolean_or           : boolean_and boolean_or_prime
+boolean_or_prime    : BooleanOr boolean_and boolean_or_prime | <e>

boolean_and           : cmp_eq_neq boolean_and_prime
+boolean_and_prime    : BooleanAnd cmp_eq_neq boolean_and_prime | <e>

cmp_eq_neq           : cmp_gt_lt cmp_eq_neq_prime
+cmp_eq_neq_prime    : CmpEqNeq cmp_gt_lt cmp_eq_neq_prime | <e>

cmp_gt_lt           : math_add_sub cmp_gt_lt_prime
+cmp_gt_lt_prime    : CmpGtLt math_add_sub cmp_gt_lt_prime | <e>

math_add_sub           : math_mul_div_mod math_add_sub_prime
+math_add_sub_prime    : MathOpAddSub math_mul_div_mod math_add_sub_prime | <e>

math_mul_div_mod           : msgable math_mul_div_mod_prime
+math_mul_div_mod_prime    : MathOpMulDivMod msgable math_mul_div_mod_prime | <e>

#+expr_h           : BracketS expr BracketE | msgable


msgable          : nouny msg_chain_node | BracketS expr BracketE msg_chain_node
+msg_chain_node  : MsgOp msg msg_chain_node | <e>
msg              : MsgNameWithArgs listy_suffix | MsgName | listy | loop

+opt_times        : times | <e>

"""


SKOAR = None
nonterminals = None


def init():
    global nonterminals, SKOAR
    nonterminals = dict()

    from Skoarcery import terminals
    from Skoarcery.langoids import Nonterminal

    # create and track as they appear
    def hello(name):

        try:
            xoid = nonterminals[name]
        except KeyError:
            xoid = Nonterminal(name)
            nonterminals[name] = xoid

        return xoid

    for bnf_line in src.split("\n"):
        if len(bnf_line) == 0 or bnf_line.lstrip().startswith("#"):
            continue

        #print(bnf_line)
        a = bnf_line.split(":")

        name = a[0].strip()

        if name.startswith("+"):
            name = name.lstrip("+")
            intermediate = True
        else:
            intermediate = False

        # i'm not using this, but feel like i ought to be
        if name.endswith("*"):
            name = name.rstrip("*")
            has_semantics = True
        else:
            has_semantics = False

        for production in a[1].split("|"):

            p = []
            for langoid in production.split():

                if len(langoid) == 0:
                    continue

                toke = terminals.tokens.get(langoid)

                if toke:
                    p.append(toke)
                else:

                    if langoid[0].isupper():
                        raise Exception("Unknown token " + langoid)

                    X = hello(langoid)

                    p.append(X)

            X = hello(name)
            X.intermediate = intermediate
            X.has_semantics = has_semantics
            X.add_production(p)

    SKOAR = nonterminals["skoar"]

    print("nonterminals initialized.")
