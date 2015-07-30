from Skoarcery.emissions import Tongue
import sys
import abc


class PyTongue(Tongue):

    def __init__(self):
        super().__init__()

    @property
    def cmt_char(self):
        return "#"

    @property
    def language(self):
        return "Python 3.3.2"

    @property
    def ext(self):
        return ".py"

    @property
    def this(self):
        return "self"

    @property
    def null(self):
        return "None"

    @property
    def false(self):
        return "False"

    @property
    def true(self):
        return "True"

    def stmt(self, line, end="\n"):
        self._emit(self.tabby + line, end=end)

    def if_(self, condition):
        self.stmt("if " + condition + ":")
        self.tab += 1

    def else_(self):
        self.tab -= 1
        self.stmt("else:", end="\n")
        self.tab += 1

    def return_(self, val=""):
        self.stmt("return " + val)

    def end_if(self):
        self.end()

    def end(self):
        self.tab -= 1
        self.nl()

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

    def constructor(self, *args, **kwargs):
        self.function(ret, "__init__", "self", *args, **kwargs)

    def function(self, ret, name, *args, **kwargs):
        s = "def " + name + "("
        s += self.expand_args(*args, **kwargs) + "):"
        self.stmt(s)
        self.tab += 1

    def abstract_class(self, name, extends=None):
        self.class_(name, extends)
        self.stmt("__metaclass__ = abc.ABCMeta")

    def class_(self, name, extends=None):
        s = "class " + name
        if extends:
            s += "(" + extends + ")"
        s += ":"
        self.stmt(s)
        self.tab += 1

    def classvar(self, prefix, name, val=None):
        s = name
        if val:
            s += " = " + val
        self.stmt(s)

    def attrvar(self, prefix, name, val=None):
        # skip in python
        pass

    def var(self, name, val=None):
        if val:
            s = name + " = " + val
            self.stmt(s)

    def method(self, ret, name, *args, **kwargs):
        self.function(ret, name, "self", *args, **kwargs)

    def throw(self, name, msg):
        self.stmt("raise " + name + "(" + msg + ")")

    def abstract_static_method(self, ret, name, *args, **kwargs):
        self.stmt("@staticmethod")
        self.stmt("@abc.abstractstaticmethod")
        self.function(ret, name, *args, **kwargs)

    def static_method(self, ret, name, *args, **kwargs):
        self.stmt("@staticmethod")
        self.function(ret, name, *args, **kwargs)

    def find_regex(self, match, regex, buf, offs):
        self.stmt(match + " = " + self.v_match_regex(regex, buf, offs))

    def if_regex_match_not_found(self, regex, buf, offs):
        self.if_(self.v_match_regex(regex, buf, offs) + " is None")

    def print(self, s, end="\\n"):
        self.stmt("print(\"" + s + "\", end='" + end + "')")

    def try_(self):
        self.stmt("try:")
        self.tab += 1

    def except_any(self):
        self.tab -= 1
        self.stmt("except:")
        self.tab += 1

    def nop(self):
        self.stmt("pass")

    # ------------------------------------
    # these v_guys return rather than code
    # ------------------------------------
    def v_match_regex(self, regex, buf, offs):
        return regex + ".match(" + buf + ", " + offs + ")"

    def v_regex_group_zero(self, match):
        return match + ".group(0)"

    def v_new(self, cls, *args):
        a = self.expand_args(*args)
        return cls + "(" + a + ")"

    def v_ass(self, dst, src):
        return dst + " = " + src

    def v_length(self, x):
        return "len(" + x + ")"

    def v_attr(self, attr):
        return "self." + attr

    def v_def_regex(self, regex):
        return 're.compile(r"' + regex + '")'

    def v_match(self, match):
        return match

    def dict_new(self, name):
        self.stmt(name + " = dict()", end="\n")

    def dict_set(self, name, str_key, value, end="\n"):
        self.stmt(name + "['" + str_key + "'] = " + value, end=end)

    def v_dict_get(self, name, str_key):
        return name + "['" + str_key + "']"

    def v_static_accessor(self):
        return "."

    # ignore return types
    def r_int(self):
        return ""

    def r_toke(self):
        return ""