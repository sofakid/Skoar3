src = """
#
# Skoar Noad Colours
#
# format (at very start of line): nonterminal: RRGGBBAA

# skip any nonterminals we won't colour


skoarpion          : 9DB562FF

listy              : 6699EEFF

arg_listy          : 333344FF

marker             : CCDDFFFF

beat               : 1EB1FAFF

ottavas            : 999999FF
dynamic            : 998877FF

lute               : CCCCCCFF
deref              : B340B1FF
msg                : 888888FF
cthulhu            : FF2E2EFF

conditional        : B59D62FF

loop               : 77EE77FF

meditation         : 62B59DFF

ugen               : 1EAE1EFF

"""


nonterminals_colours = None


def init():
    global nonterminals_colours
    nonterminals_colours = dict()

    for bnf_line in src.split("\n"):
        if len(bnf_line) == 0 or bnf_line.lstrip().startswith("#"):
            continue

        #print(bnf_line)
        (name, v, colour) = bnf_line.partition(":")

        name = name.strip()
        colour = colour.strip()

        nonterminals_colours[name] = colour

    print("# nonterminals_colours initialized.")
