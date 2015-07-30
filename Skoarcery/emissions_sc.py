from datetime import datetime
import sys
import abc
from Skoarcery.emissions import Tongue

# --------------------
# SuperCollider Tongue
# --------------------
class ScTongue(Tongue):

    def __init__(self):
        super().__init__()

    @property
    def cmt_char(self):
        return "//"

    @property
    def language(self):
        return "SuperCollider 3.7"

    @property
    def ext(self):
        return ".sc"

    @property
    def this(self):
        return "this"

    @property
    def null(self):
        return "nil"

    @property
    def true(self):
        return "true"

    @property
    def false(self):
        return "false"

    def stmt(self, line, end=";\n"):
        self._emit(self.tabby + line, end=end)

    def if_(self, condition):
        self.stmt("if (" + condition + ") {", end="\n")
        self.tab += 1

    def else_(self):
        self.tab -= 1
        self.stmt("} {", end="\n")
        self.tab += 1

    def end_if(self):
        self.tab -= 1
        self.stmt("}")
        self.nl()

    def end(self):
        self.tab -= 1
        self.stmt("}", end="\n")
        self.nl()

    def return_(self, val=""):
        self.stmt("^" + val)

    def function(self, ret, name, *args, **kwargs):
        self.stmt(name + " {", end="\n")
        self.tab += 1

        a = self.expand_args(*args, **kwargs)
        if a != "":
            self.stmt("| " + a + " |", end="\n")
            self.nl()

    def abstract_static_method(self, ret, name, *args, **kwargs):
        self.static_method(ret, name, *args, **kwargs)

    def method(self, ret, name, *args, **kwargs):
        self.function(ret, name, *args, **kwargs)

    def static_method(self, ret, name, *args, **kwargs):
        name = "*" + name
        self.function(ret, name, *args, **kwargs)

    def constructor(self, *args, **kwargs):
        a = self.expand_args_just_keys(*args, **kwargs)

        self.static_method("", "new", *args, **kwargs)
        self.return_("super.new.init( " + a + " )")
        self.end()

        self.function("init", *args, **kwargs)

    def abstract_class(self, name, extends=None):
        self.class_(name, extends)

    def class_(self, name, extends=None):
        s = name
        if extends:
            s += " : " + extends
        s += " {"
        self.stmt(s, end="\n")
        self.tab += 1

    def classvar(self, prefix, name, val=None):
        s = prefix + name
        if val is not None:
            s += " = " + val

        self.stmt("classvar " + s)

    def attrvar(self, prefix, name, val=None):
        self.stmt("var " + prefix + name)

    def var(self, name, val=None):
        s = name
        if val is not None:
            s += " = " + val
        self.stmt("var " + s)

    def throw(self, name, msg):
        self.stmt(name + "(" + msg + ").throw")

    def print(self, s, end="\n"):
        self.stmt('"' + s + end + '".post')

    def if_regex_match_not_found(self, regex, buf, offs):
        self.if_(self.v_match_regex(regex, buf, offs) + " == " + self.false)

    def find_regex(self, match, regex, buf, offs):
        self.stmt(match + " = " + buf + ".findRegexpAt(" + regex + ", " + offs + ")")

    def try_(self):
        self.stmt("try {", end="\n")
        self.tab += 1

    def except_any(self):
        self.tab -= 1
        self.stmt("} {", end="\n")
        self.tab += 1

    def nop(self):
        self.stmt("// pass", end="\n")

    def dict_new(self, name):
        self.stmt(name + " = IdentityDictionary()", end="\n")

    def dict_set(self, name, str_key, value, end=");\n"):
        self.stmt(name + ".put('" + str_key + "', " + value, end=end)

    # ------------------------------------
    # these v_guys return rather than code
    # ------------------------------------
    def v_dict_get(self, name, str_key):
        return name + "['" + str_key + "']"

    def v_match_regex(self, regex, buf, offs):
        return regex + ".matchRegexp(" + buf + "," + offs + ")"

    def v_ass(self, dst, src):
        return dst + " = " + src

    def v_regex_group_zero(self, match):
        return match + "[0][1]"

    def v_new(self, cls, *args):
        a = self.expand_args(*args)
        return cls + ".new(" + a + ")"

    def v_length(self, x):
        return x + ".size"

    def v_attr(self, attr):
        return attr

    def v_def_regex(self, regex):
        return '"' + regex.replace("\\", "\\\\") + '"'

    def v_match(self, match):
        return self.v_length(match) + " > 0"

    def v_static_accessor(self):
        return "."

    # ignore return types
    def r_int(self):
        return ""

    def r_toke(self):
        return ""

    def expand_args(self, *args, **kwargs):
        a = ""
        for arg in args:
            if a != "":
                a += ", "
            a += arg

        for k, v in kwargs.items():
            if a != "":
                a += ", "
            a += k + "=" + v

        return a

    def expand_args_just_keys(self, *args, **kwargs):
        a = ""
        for arg in args:
            if a != "":
                a += ", "
            a += arg

        for k, v in kwargs.items():
            if a != "":
                a += ", "
            a += k + "=" + v

        return a
