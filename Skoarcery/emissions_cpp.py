from datetime import datetime
import sys
import abc
from Skoarcery.emissions import Tongue, Arg


class CppTongue(Tongue):

    def __init__(self, ext=".cpp"):
        super().__init__()
        self.last_class = ""
        self._ext = ext

    @property
    def cmt_char(self):
        return "//"

    @property
    def language(self):
        return "C++14"

    @property
    def ext(self):
        return self._ext

    @property
    def this(self):
        return "this"

    @property
    def null(self):
        return "nullptr"

    @property
    def false(self):
        return "false"

    @property
    def true(self):
        return "true"

    def stmt(self, line, end=";\n"):
        self._emit(self.tabby + line, end=end)

    def if_(self, condition):
        self.stmt("if (" + condition + ") {", end="\n")
        self.tab += 1

    def else_(self):
        self.tab -= 1
        self.stmt("} else {", end="\n")
        self.tab += 1

    def return_(self, val=""):
        if isinstance(val, Arg):
            val = val.name
        self.stmt("return " + val)

    def end_if(self):
        self.end()

    def end_class(self):
        self.tab -= 1
        self.stmt("}", end=";\n")
        self.nl()

    def end(self):
        self.tab -= 1
        self.stmt("}", end="\n")
        self.nl()



    def expand_args(self, *args, **kwargs):
        a = ""
        for arg in args:
            if a != "":
                a += ", "
            t = ""
            n = ""
            if isinstance(arg, Arg):
                n = arg.name
                t = arg.type
            a += t +" "+ n
    
        # let's not do this in c++
        for k, v in kwargs.items():
            if a != "":
                a += ", "
            a += k + "=" + v

        return a

    def abstract_class(self, name, extends=None):
        self.class_(name, extends)
        
    def class_(self, name, extends=None):
        s = "class "+ name
        self.last_class = name;
        if extends:
            s += ": public "+ extends
        s += " {"
        self.stmt(s, end = "\n")
        self.stmt("public:", end = "\n")
        self.tab += 1

    def set_class(self, class_):
        self.last_class = class_

    def classvar_declare(self, prefix, arg, val=None):
        self.stmt("static "+ arg.type +" "+ arg.name)

    def static_var(self, arg, val=None):
        self.stmt("static "+ arg.type +" "+ arg.name)

    def classvar_assign(self, arg, val=None):
        self.stmt(arg.type +" "+ self.last_class + "::"+ arg.name +" = "+ val)

    def attrvar(self, prefix, name, val=None):
        self.var(name, val)

    def static_var(self, arg, val=None):
        self.stmt("static "+ arg.type +" "+ arg.name)

    def var(self, arg, val=None):
        s = arg.type +" "+ arg.name
        if val:
            s += " = "+ val
        self.stmt(s)

    def throw(self, name, msg):
        self.stmt("throw "+ name +"("+ msg +")")

    def constructor(self, *args, **kwargs):
        name = Arg("", self.last_class +"::"+ self.last_class)
        self.function(name, *args, **kwargs)

    def destructor(self, *args, **kwargs):
        name = Arg("", self.last_class +"::~"+ self.last_class)
        self.function(name, *args, **kwargs)

    def function(self, name, *args, **kwargs):
        s = name.type + " " + name.name + "("
        s += self.expand_args(*args, **kwargs) + ") {"
        self.stmt(s, end="\n")
        self.tab += 1

    def method(self, name, *args, **kwargs):
        x = Arg(name.type, self.last_class +"::"+ name.name)
        self.function(x, *args, **kwargs)

    def abstract_static_method(self, name, *args, **kwargs):
        pass

    def static_method(self, name, *args, **kwargs):
        self.stmt("static ", end="")
        self.method(name, *args, **kwargs)



    def constructor_h(self, *args, **kwargs):
        name = Arg("", self.last_class)
        self.method_h(name, *args, **kwargs)

    def destructor_h(self, *args, **kwargs):
        name = Arg("", "~" + self.last_class)
        self.method_h(name, *args, **kwargs)

    def virtual_destructor_h(self, *args, **kwargs):
        name = Arg("", "~" + self.last_class)
        self.virtual_method_h(name, *args, **kwargs)

    def destructor_override_h(self, *args, **kwargs):
        name = Arg("", "~" + self.last_class)
        self.method_override_h(name, *args, **kwargs)


    def function_h(self, name, *args, **kwargs):
        s = name.type + " " + name.name + "("
        s += self.expand_args(*args, **kwargs) + ")"
        self.stmt(s, end=";\n")
    
    def function_override_h(self, name, *args, **kwargs):
        s = name.type + " " + name.name + "("
        s += self.expand_args(*args, **kwargs) + ") override"
        self.stmt(s, end=";\n")
             
    def method_h(self, name, *args, **kwargs):
        self.function_h(name, *args, **kwargs)

    def method_override_h(self, name, *args, **kwargs):
        self.function_override_h(name, *args, **kwargs)

    def static_method_h(self, name, *args, **kwargs):
        self.stmt("static ", end="")
        self.method_h(name, *args, **kwargs)

    def virtual_method_h(self, name, *args, **kwargs):
        self.stmt("virtual ", end="")
        self.method_h(name, *args, **kwargs)
    
    def static_function_h(self, name, *args, **kwargs):
        self.stmt("static ", end="")
        self.function_h(name, *args, **kwargs)




    def find_regex(self, match_obj, regex, buf, offs):
        self.stmt("auto found = " + self.v_match_regex(match_obj, regex, buf, offs))

    def if_regex_match_not_found(self, regex, buf, offs):
        self.if_("!found")

    def print(self, s, end="\n"):
        self.stmt('cout << "' + s + end + '"')

    def try_(self):
        self.stmt("try {", end="\n")
        self.tab += 1

    def except_any(self):
        self.tab -= 1
        self.stmt("} catch (Exception e) {", end="\n")
        self.tab += 1

    def nop(self):
        self.stmt("/* nop */;")

    # ------------------------------------
    # these v_guys return rather than code
    # ------------------------------------
    def v_match_regex(self, match_obj, regex, buf, offs):
        return "regex_search("+ buf.name +".begin() + "+ offs.name +", "+ regex.name +", "+ match_obj.name +")"

    def v_regex_group_zero(self, match):
        return "result[0]"

    def v_new(self, cls, *args):
        a = self.expand_args(*args)
        return "new " + cls + "(" + a + ")"

    def v_ass(self, dst, src):
        if isinstance(dst, Arg):
            dst = dst.name
        if isinstance(src, Arg):
            src = src.name

        return dst + " = " + src

    def v_length(self, x):
        return x + ".size()"

    def v_attr(self, attr):
        return "this->" + attr.name

    def v_def_regex(self, regex):
        return 'wregex(L"' + regex.replace('\\','\\\\') + '")'

    def v_match(self, match):
        return match

    def dict_new(self, name):
        self.stmt("map<wstring,list<SkoarToke*>> *" + name + " = new map<wstring, list<SkoarToke*>>;", end="\n")

    def dict_set(self, name, str_key, value, end="\n"):
        self.stmt(name + '[L"' + str_key + '"] = ' + value, end=end)

    def v_dict_get(self, name, str_key):
        return name + '[L"' + str_key + '"]'

    def array_new(self, name, length):
        self.stmt("list<ESkoarToke::Kind> " + name + "[" + str(length) + "];", end="\n")

    def array_set(self, name, index, value, end="\n"):
        self.stmt(name + '[' + str(index) + '] = ' + value, end=end)

    def v_array_get(self, name, index):
        return name + '[' + str(index) + ']'

    def v_static_accessor(self):
        return "::"

    def r_int(self):
        return "int"

    def r_toke(self):
        return "SkoarToke"

    def v_str(self, s):
        return 'L"' + s + '"'

def box(text, char="-"):
    n = len(text)

    line = ("{:" + char + ">" + str(n) + "}").format(char)

    return "{line}\n{text}\n{line}".format(line=line, text=text)
