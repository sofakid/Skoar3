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

opt_args           : SkoarpionArgs args | <e>
+args              : opt_newline args_entries
args_entries       : SymbolColon expr moar_args_entries | SymbolName moar_args_entries
+moar_args_entries       : opt_newline moar_args_entries_prime
+moar_args_entries_prime : ListSep opt_newline args_entries | <e>
+opt_newline             : Newline | <e>

skoarpion          : opt_args SkoarpionStart skrp_suffix
skrp_suffix        : skrp_lines SkoarpionEnd

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

musical_keyword      : dynamic | ottavas | musical_keyword_misc
musical_keyword_misc : Carrot
ottavas              : OctaveShift 
dynamic              : DynPiano | DynForte | DynSFZ | DynFP

nouny            : cthulhu | meditation | conditional | loop | nouny_literal | musical_keyword | listy | deref | skoarpion
+nouny_literal   : Duration | ugen | Tuplet | Freq | Int | Float | String | Choard | NamedNoat | Symbol | Fairy | HashLevel | False | True | Cat | lute

lute             : Lute | LuteWithArgs listy_suffix

deref            : Deref deref_prime
+deref_prime     : MsgNameWithArgs listy_suffix | MsgName

expr             : SymbolColon expr | msgable expr_prime
expr_prime       : math expr_prime | boolean | times | <e> 

times            : Times
boolean          : BooleanOp expr
boolean_expr     : expr
math*            : MathOp msgable

msgable          : nouny msg_chain_node
+msg_chain_node  : MsgOp msg msg_chain_node | <e>
msg              : MsgNameWithArgs listy_suffix | MsgName | listy | loop

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
