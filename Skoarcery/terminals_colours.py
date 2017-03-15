src = """
#
# Skoar Toke Colours
#
# format (at very start of line): TokeName: RRGGBBAA

# skip any that don't need colouring

True:           FFF82EFF
False:          FFF82EFF
Cat:            FFF82EFF

Voice:          0B6BD9FF
Comment:        5E5B55FF

Int:           FFF82EFF
Float:         FFF82EFF

Freq:          FFF82EFF

Carrot:         B340B1FF

Tuplet:         B340B1FF

Duration:       F8FF2EFF

HashLevel:      FFF82EFF

AssOp:            B340B1FF
MsgOp:            B340B1FF
MathOp:           B340B1FF

NamedNoat:        1EFA67FF
Choard:           1EFA67FF

BooleanOp:        B340B1FF

Fairy:            FF99FFFF

Symbol*:          EEEECCFF
SymbolColon*:     EEEECCFF

String*:          B58962FF

Bars*:            9DB562FF

Times:            FFF82EFF
"""

#
#
#

token_colours = None

def init():
    global src, token_colours

    token_colours = dict()

    for token_line in src.split("\n"):

        token_line = token_line.strip()
        if len(token_line) > 0 and not token_line.startswith("#"):

            (token, v, colour) = token_line.partition(":")

            token = token.strip()
            colour = colour.strip()

            if token.endswith("*"):
                token = token.rstrip("*")

            token_colours[token] = colour

    print("# token colours initialized.")


