src = """
#
# Skoar Tokes
#
# format (at very start of line): TokeName: regex
#
# If token carries information: TokeName*: regex
#   -  be sure an inspector for TokeName exists
#

<e>:            unused
Eof:            unused
Whitespace:     [ \\t]*
Newline:        [ \\t]*[\\n\\r][\\n\\r \\t]*

True:           yes|true
False:          no|false
Cat:            =\\^\\.\\^=

Voice*:         \\.(([a-zA-Z_][a-zA-Z0-9_]*)?|\\.+)

Comment:        ;.*

# careful not to steal from floats
Int*:           (-)?(0|[1-9][0-9]*)(?![0-9]*Hz|[0-9]*\\.[0-9]|:[0-9])
Float*:         (-)?(0|[1-9][0-9]*)\\.[0-9]+(?!Hz|:[0-9])

Freq*:          (0|[1-9][0-9]*)(\\.[0-9]+)?Hz

ListS:          <(?![=?])|<(?=[=]\\^\\.)
ListE:          >(?![=])
ListSep:        ,

# one ^ but don't eat ^^( which is cthulhu's left wing
Carrot*:        \\^(?!\\^[(])
LWing:          \\^\\^[(]
RWing:          [)]\\^\\^

Tuplet*:        /\\d+(:\\d+)?|(du|tri|quadru)plets?|(quin|sex|sep|oc)tuplets?
Crotchets*:     [}]+\\.?
Quavers*:       o+/\\.?

ExactBeat:      [(](?![+])
ExactRest:      [{](?![=?:!])
Duration:       [0-9]+:[0-9]+(\\.[0-9]+)?

Quarters*:      \\.?[)]+(?:__?)?\\.?
Eighths*:       \\.?\\]+(?:__?)?\\.?

#Caesura:        //
#Slash:          /(?![/0-9])

HashLevel:      \\[#*[ ]*\\]

Lute:           &(?!<)
LuteWithArgs:   &<

# we can't allow f for forte as f is a noat, so we allow
#
#  forte fforte ffforte ff fff, but not f
#
#  for consisentecy, piano, ppiano, pppiano work too.
#
#  default velocity:
#    ppp (16), pp (32), p (48), mp (64), mf (80), f (96), ff (112), fff (127)

DynPiano*:        (m(ezzo)?p|p+)(iano)?(?![a-oq-zA-Z0-9_])
DynForte*:        m(ezzo)?f(orte)?|f+orte|ff+(?![a-oq-zA-Z0-9_])
DynSFZ:           sfz(?![a-oq-zA-Z0-9_])
DynFP:            fp(?![a-oq-zA-Z0-9_])

MsgOp:            \\.(?![)\\]])
MathOp:           [+*\\-/%](?!>) 

NamedNoat*:       (?:_?)(?:[a-g](?![ac-zA-Z_]))(#|b)?(?![ \\t]*:(?![}:|]))
Choard*:          ~*[ABCDEFG](?![.ce-hj-ln-rt-zA-LN-Z]|a[l ])(#|b)?([Mm0-9]|sus|dim|aug|dom)*~*

BooleanOp*:       ==|!=|<=|>=|and|or|xor
CondS:            [{][?]
CondIf:           [?][?](?![}])
CondE:            [?][}]
Semicolon:        ;

MeditationS:      [{]=
MeditationE:      =[}]

LoopS:            [{]:
LoopE:            :[}]
LoopSep:          ::(?![|])

Fairy:            [$]

# we do this, because skoaroids can follow skoaroids.
MsgName*:         [a-zA-Z_][a-zA-Z0-9_]*(?!<)
MsgNameWithArgs*: [a-zA-Z_][a-zA-Z0-9_]*<

Symbol*:          @[a-zA-Z0-9_][a-zA-Z0-9_]*
SymbolName*:      [a-zA-Z0-9_][a-zA-Z0-9_]*(?![[a-zA-Z0-9_fi \\t]*:)
SymbolColon*:     [a-zA-Z_][a-zA-Z0-9_]*[ \\t]*:(?![:|}])

SkoarpionStartWithSig:  [{]!(?=([^!](?!![}]))*!!)
SkoarpionStart:         [{]!(?=([^!](?!!!))*![}])
SkoarpionEnd:           ![}]
SkoarpionSep:           !!

Deref:            !(?![!}]|=)
Nosey:            ,

Coda:             \\([+]\\)(\\s*:\\s*[a-zA-Z0-9_]+)?
AlCoda:           al [cC]oda(\\s*:\\s*[a-zA-Z0-9_]+)? 

AUGen*:           a[A-Z][a-zA-Z0-9_]*(?![a-zA-Z0-9_]*<)
AUGenWithArgs*:   a[A-Z][a-zA-Z0-9_]*<
KUGen*:           k[A-Z][a-zA-Z0-9_]*(?![a-zA-Z0-9_]*<)
KUGenWithArgs*:   k[A-Z][a-zA-Z0-9_]*<
DUGen*:           d[A-Z][a-zA-Z0-9_]*(?![a-zA-Z0-9_]*<)
DUGenWithArgs*:   d[A-Z][a-zA-Z0-9_]*<

OctaveShift*:     ~+o|o~+

# TODO: deal with \"
String*:          \'[^']*\'

Bars*:            :?\\|+:?

Times:            [Tt]imes
"""

#
#
#

list_of_names = None
inspectables = None
tokens = None
Empty = None
Eof = None
Whitespace = None

odd_balls = None


def init():
    from Skoarcery.langoids import Terminal
    global src, list_of_names, tokens, Eof, Empty, Whitespace, odd_balls, inspectables

    list_of_names = []
    inspectables = []
    tokens = dict()

    for token_line in src.split("\n"):

        token_line = token_line.strip()
        if len(token_line) > 0 and not token_line.startswith("#"):

            (token, v, regex) = token_line.partition(":")

            token = token.strip()
            regex = regex.strip()

            if token.endswith("*"):
                token = token.rstrip("*")
                inspectables.append(token)

            list_of_names.append(token)

            tokens[token] = Terminal(token, regex)

    #print("# tokens initialized.")

    Empty = Terminal("<e>", None)
    Eof = Terminal("Eof", None)
    Whitespace = tokens["Whitespace"]

    odd_balls = {Empty, Eof, Whitespace}


