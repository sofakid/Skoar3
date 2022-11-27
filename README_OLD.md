Skoar and Skoarcery
===================


THIS IS OLD AND WRONG.
=====================

__Skoar__ is a high-level language for coding music.

It runs on [SuperCollider], a free and fantastic audio programming environment.

__Skoarcery__ is a set of tools to define, test, and build the Skoar language.

Example
=======

[listen on soundcloud](https://soundcloud.com/lucas-cornelisse/zelda)

    <? Zelda Theme - inspired by piano arrangement by Shinobu Amayake ?>

    130 => )

    .alice    @default => @instrument [#####   ] => @amp
    .bob      @default => @instrument [#####   ] => @amp
    .bass    @sawpulse => @instrument [###     ] => @amp  o~~~~
    .hats        @hats => @instrument [##      ] => @amp
    .snare      @snare => @instrument [##      ] => @amp
    .kick        @kick => @instrument [###     ] => @amp

    {! bass_end<x>    !! !x ) ) ) ] ]     !}
    {! bass_climb     !! | _e ]] _a# ]] c# ]  e ]] a# ]] ~o c# ] e ) } | f ) o~ _f ]] ]] ] ) } | !}

    {! bassline_a !!
      <a#, g#, f#, c#, b, a#, c>.{: .) ]] ]] ] ) ) :}
      !bass_end<f>
    !}

    {! bassline_b !!
      <a#, g#, f#, f>.{: ) ]] ]] ] ) ) :}
      !bass_climb !bass_climb
      <b, a#, c     >.{: ) ]] ]] ] ) ) :} !bass_end<f>
    !}


    {! intro !!

      .hats  {: }}} :: 4 times :}
      .snare {: }}} :: 4 times :}
      .kick  {: }}} :: 4 times :}

      .alice | _a# ))        o/. ]]  ]] ]] ] |     ]. _g#  ]] _a# )        o/.  ]]  ]] ]] ] |
      .bob   | _d  ))        o/. ]]  ]] ]] ] | _c  ].      ]]     )        o/.  ]]  ]] ]] ] |
      .bass  |  a# ) ]] ]] ] )       ]] ]] ] |  g# )              ]] ]] ]  )        ]] ]] ] |

      .alice |     ]. _g# ]] _a# )       o/. ]] ]] ]] ] |   ]    _f ]] ]]  ] ]] ]]  ] ]] ]]  ]     ] |
      .bob   | _c# ].     ]]     )       o/. ]] ]] ]] ] |   ] o~ _a ]] ]]  ] ]] ]]  ] ]] ]]  ]     ] |
      .bass  |  f# )             ]] ]] ] )      ]] ]] ] | f )              )        )      g ]   a ] |
    !}

    {! melody_a !!

      .bass !bassline_a

      .hats  {: }}} :: 7 times :} | ] ] ] ] ] ] ] ] |
      .snare {: }}} :: 8 times :}
      .kick  {: }}} :: 8 times :}

      .alice | _a# ) _f )__          o/. _a# ]]  ]]   c ]]  d ]] d# ]] |
      .bob   | _d  )    ]] ]] _c ] _d ].     ]]  ]] _d# ]] _f ]] _g ]] |

      .alice |  f  ))                             o/ ]   f ]  f# ]] g# ]] |
      .bob   | _g# ]. _a# ]] ]] c ]] d ]] d# ]] f )    _g# ] _a# ]] c  ]] |

      .alice |  a# ))                                  o/ a# ]  ]  g# ]]  f# ]] |
      .bob   |  c# ]. _f# ]]  ]] _g# ]] _a# ]] c ]] c# ]. ]]    ]  c  ]] _a# ]] |

      .alice | g# ].  f# ]]  f ))                      )               |
      .bob   | c# ]. _g# ]]    ]] ]] _f# ]  _g# ]. ]]  ]] _f# ]] _g# ] |

      .alice |  d# ] ]]  f ]]  f# ))                  f ] d#  ] |
      .bob   | _f# ] ]] _f ]] _f# ] ]] _g# ]] _a# ) _g# ] _f# ] |

      .alice |  c# ] ]]  d# ]]  f ))                 d# ]  c# ] |
      .bob   | _f  ] ]] _d# ]] _f ] ]] _f# ]] _g# ) _f# ] _d# ] |

      .alice |  c ] ]]  d ]]  e ))                      g )     |
      .bob   | _e ] ]] _d ]] _e ] ]] _g ] ]] _a ]] ]] _a# ] c ] |

      .alice |  f ]     _f ]] ]]  ] ]] ]]   ] ]] ]]   ]  ]    |
      .bob   | _a ] o~  _a ]] ]]  ] ]] ]]   ] ]] ]]   ]  ] ~o |

    !}


    {! melody_b !!

      .bass !bassline_b

      .hats  {: ] ] ] ] ] ] ] ]] ]] :: 12 times :}
      .kick  {: )   }   )   }       :: 12 times :}
      .snare {: }   )   }   )       :: 11 times :} | ] ]]  ]]  ] ]] ]]  ]  ] |

      .alice | _a# ) _f )             o/.  _a# ]]  ]]   c ]]  d ]] d# ]] |
      .bob   | _d  )    ]] ]] _c ]  _d ].      ]]  ]] _d# ]] _f ]] _g ]] |

      .alice |  f  ))                             o/ ]   f ]  f# ]] g# ]] |
      .bob   | _g# ]. _a# ]] ]] c ]] d ]] d# ]] f )    _g# ] _a# ]] c  ]] |

      .alice | a# )). ~o c# ) | c  ) o~ a )) f  ) |  f# )).  a# ) | a )  f )) ) |
      .bob   | c# )).    e  ) | d# )    c )) _a ) | _b  )).  c# ) | c ) _a )) ) |

      .alice |  f# )). a# ) | a )  f )) d ) |  d# )).  f# ) |  f  )  c# )) _a# ) |
      .bob   | _b  )). c# ) | c ) _a ))   ) | _f# )). _b  ) | _a# ) _f  )) _c# ) |

      .alice |  c ] ]]  d ]]  e ))                        g  )     |
      .bob   | _e ] ]] _d ]] _e ] ]] _f ]] _g ] ]] _a ]] _a# ] c ] |

      .alice |  f ]    _f ]] ]]  ] ]] ]]   ] ]] ]]   ]  ]    |
      .bob   | _a ] o~ _a ]] ]]  ] ]] ]]   ] ]] ]]   ]  ] ~o |

    !}

    {! fill !!
      .alice |  f ]    _f ]] ]]  ] ]] ]]   ] ]] ]]   ]  ]    |
      .bob   | _a ] o~ _a ]] ]]  ] ]] ]]   ] ]] ]]   ]  ] ~o |
      .snare |    ]       ]] ]]  ] ]] ]]   ] ]] ]]   ]  ]    |
      .hats  |    ]       ]      ] ]       ] ]       ]  ]    |
      .kick  |    )              }         )         )       |
      .bass !bass_end<f>
    !}

    !intro
    !melody_a
    !fill
    !melody_b
    !fill
[listen on soundcloud](https://soundcloud.com/lucas-cornelisse/zelda)

More examples: [examples.md]

See also: [listen to dungeontimes](https://soundcloud.com/lucas-cornelisse/dungeontimes)

And also: [listen to brand new shoes](https://soundcloud.com/lucas-cornelisse/radar-and-zuzu)

What's New in Skoar 2
=====================

# Exact Beats

    (0:30) (0.001)

# simpler assignment

    foo: 7
    blerg: 7 + !foo

# default arguments

    {! foo<x:2, y:3> !! !x + !y !}

    !foo
    !foo<1>
    !foo<1, 9>
    !foo<y: 9, x: 1>
    !foo<y: 9>
    
# meditations

    {= "skoar code..." =}

# books

    {= =}.book

# envelopes

    {= =}.env

    what can we do with envelopes?

    	 .a
	 .k

	 .plot

# ugens

## `k` rate

    kMouseX<440, 880>
     
## `a` rate

    aSinOsc

## ugen math

## ugen chaining

With positional arguments, use the magic word `@in` where the `in` argument should be. The previous ugen will be used here.

   aSinOsc aHPF<@in, 300> aPan2<@in, kMouseX<-1,1>>

With named arguments, you can omit the magic word `@in`, it is assumed. 

   aSinOsc aHPF<freq:300> aPan2<pos:kMouseX<-1,1>>
   

Skoar
=====

Skoar is a language for coding music, combining a grand-staff-like notation
with a flexible programming notation.

# beats and rests

    __beats_______________   __rests_______________

    ))) - whole               }}} - whole
    ))  - half                 }} - quarter
    )   - quarter               } - quarter
    ]   - eighth               o/ - eighth
    ]]  - sixteenth           oo/ - sixteenth
    ]]] - thirty secondth    ooo/ - thirthy secondth


# fancy beats - dotted, staccato, ties

    ).  - dotted quarter
    ]]. - dotted sixteenth
    o/. - dotted eighth rest

    .)   - staccato quarter
    .]]. - staccato and dotted sixteenth

    )__  - quarter with a tie (ties to the next beat)
    )__. - dotted quarter with a tie


# noats

We call them __noats__, not __notes__, you see, __notes__ are already things;
nor are these __noats__ the nearly named __noads__, which are also totally things..

    <? use # or b after the noat to sharp or flat it. Or use scale degree numbers. ?>

    c ) d ) eb ) f ]] ]] g ] ] g# )

    <? you get two octaves to work with, prepend _ for the lower octave. ?>

    <_c, _d, _e, _f, _g, _a, _b, c, d, e, f, g, a, b>.choose ]]
    
# key
    
    {! foo !! <0,1,2,3,4,5,6,7>.{: ]] :} !}
    
    Am => @key !foo
    Fb => @key !foo
    
    <E, @dorian> => @key !foo
    <F, @minorPentatonic> => @key !foo

# transpose

Just set @tranpose.

    -3 => @transpose

# tempo

Sort of like a metronome marker, set the bpm to a beat length:

    80 => ) <? 80 quarter notes per minute ?>
    80 => ] <? 80 eighth notes per minute ?>
       
# choards

    A Am A#m Asus2 Adim etc..

Or we can use lists of noats:

    <_a,c,e> )  <_a,c#,e> ) <0,2,4> ))

# changing the octave

    <? up one octave ?>    <? down one ?>
    ~o                     o~
    8va                    8vb
    ottava alta            ottava bassa

    <? up two ?>           <? down two ?>
    ~~o                    o~~
    15ma                   15mb
    alla quindicesima

# dynamics

We have to use the full word `forte`, `f` is a noat.

    fff ffforte ppp pppiano piano mp mf ff pp p 
    
or, use a hash level, and set `@amp`:

    .strings  [###  ] => @amp
    .piano    [#### ] => @amp
    .bass     [#### ] => @amp
  
Hash levels can be any length: 

    [ ] is 0
    [#] is 1
    [## ] is 0.66ish
    
# repeats

Colons:

    |: _a ]]] c ]]] e ]]] :| g ]]] ooo/ ]]] :|

Segnos and Codas: (Codas currently not implemented)

    | _a ) c ) e ) | ,segno` ) ]] ]] e ]] | f D.S. al fine ) ) ) fine

    | ,segno` c ]] e ]] (+) ]] ]] D.S. al Coda '.......'  (+) | a) c) e) } |

Infinite repeats:

    <? from the top ?>
    | _a] c] e] | D.C. <? also accept Da Capo ?>

    <? from the segno ?>
    | _a] c] e] o/ | ,segno` _f] f] _f] o/ Dal Segno |

# variables

We can set and get values from a dictionary local to the voice. Anything set here
will be copied into the resulting event every beat; which we can use to configure the voice.

    <? names of things start with @ ?>
    @smooth => @instrument
    <0,3,5> => @detune

    <? to lookup the values, we use ! in place of @.... more on ! below.. ?>
    a# => @foo
    !foo )

# loops

This is a simple loop:

    {: ]] oo/ ]] ]] :: 8 times :} 
    
You can send a loop to an array as a message to implement a foreach loop:

    <_a, _c, c, _e, e, _a>.{: ] ]] ]] :}

If you also put a boolean condition, it will keep foreaching while the condition is true.
    
    <_a, _c, c, _e, e, _a>.{: ] ]] ]] :: !groovy == 5 :}
    
# conditionals

An if example:

    {? !x == !y ?? ]]] ?}

An if with else example:

    {? !x == !y ?? ]]] ?? ooo/ ?}
    
    
Acceptable boolean operators:

    == != >= <= and or xor
    
At the moment, don't use `<` or `>` 
    
# Skoarpions

The __Skoarpion__ is like a function, but more like a subroutine, plus a magical fairy with a very short term memory.

    {! name<args> !!
      body
      ...
    !}

Let's make a skoarpion:

    {! drumsBasic<x> !! 4/4
        .h  {: ] ] ] ] ] ] ] ] :: !x times :}
        .s  {: }   )   }   )   :: !x times :}
        .k  {: ))      ))      :: !x times :}
    !}

If `drumsBasic` is called by the `.h` voice, then `{: ] ] ] ] ] ] ] ] :: !x times :}` is executed; 
`.s` voice: `{: }   )   }   )   :: !x times :}`, `.k` etc..

If any lines are not voiced (like that `4/4`), they will be run by every voice.  

Skoarpions normally have scope, but they can be inlined with `.inline`, which can be convenient:

    {! alice !! ~o mp
      <c#, e, _a, g#> => @favorites
              <0,5,7> => @detune
                @acid => @instrument
    !}

    {! bob<x> !! o~~ forte
      @bass => @instrument
         !x => @favorites
    !}

    <? here's an anonymous skoarpion ?>
    {! <x> !! <0, 4, !x> => @detune !} => @charlie

    .a !alice.inline
    .b !bob<<a,e>>.inline
    .c !charlie<<5,7,9>.choose>.inline
    ...

Skoarpions don't return values. But, every value leaves an impression on the magical fairy, and so it can be said that 
in a way, skoarpions "return" things. But, that's not what really going on.

    {! foo<x,y> !! !x + !y !}
    
    !foo<2,3> => @x   <? x is now 5 ?>

Wait, magical fairy?    

# The Magical Fairy

*"Any sufficiently defined magic, is indistinguishable from technology."*

There is a magical fairy, who is following along the skoar when it is performed. 

Whenever the fairy encounters any kind of value, it leaves a short term impression on her. 

Whenever you do `5 => @x`, the fairy's last impression (here, `5`) is saved to @x.

The fairy can be directly referenced with `$`. 

If you need to save the impression, whatever it is at the moment, you can do `$ => @x`

Complex expressions are handled by the fairy via arcane magic. 
 
Values and operators will be operated on in the order they appear. SuperCollider users are familiar with this concept.

    5 + 2 * 3 => @x       <? x is now 21, certainly not 10 ?>
    
    <0, $+1, $+2> => @x   <? x is now <0,1,3> ?>

# Math

    0 + 2 == 2
    <0> + 2 == <0, 2>
    <_a, c> + e == <_a, c, e>
    
    0 * 2 == 0
    2 * 2 == 4
    
increments and decrements:

    2 => @x    <? x is now 2 ?>
    2 +> @x    <? x is now 4 ?>
    1 -> @x    <? x is now 3 ?>
    2 *> @x    <? x is now 6 ?>
	    
# Randomness

`.rand` for numbers, `.choose` for lists.

    <? save into @food, a random number between zero and five ?>
    5.rand => @food

    <? choose a random note ?>
    <c,d,e,f,g,a,b>.choose
    
These are messages passed down to supercollider. 
You say `.rand` because in SC, `Integer` has a `.rand` method, `Array` has `.choose`

# Cats

We don't have `nil` in Skoar. We do, however, have cats. 

    =^.^=   <? a cat ?>

Cats eat variables. If you need to unset a variable, use a cat.

	'foo' => @x     <? x is now 'foo' ?>

	=^.^= => @x     <? x is gone ?>

If you make a list of cats, they will stay.

	< =^.^=, =^.^= >    <? a list of cats. In supercollider, this will be [nil, nil] ?>

If you declare a skoarpion to take arguments, but don't supply them, cats will be supplied.

	{! foo<x> !! !x + 2 } !foo => @y   <? a cat eats y (because a cat + 2 is a cat) ?>

If you try to use a variable that doesn't exist, you will find a cat.

	<? if x doesn't exist, set it to 3 ?>

	{? !x == =^.^= ?? 3 => @x ?}

If you call a SuperCollider function, and it returns `nil`, you will have a cat. 
    

# Cthulhu

You can wake Cthulhu, crashing the skoar:

    ^^(;,;)^^


Cthulhu can also make assertions:

    ^^(;!octave == 5;)^^
    
If the octave isn't 5, Cthulhu will be so upset that he'll wake up and crash your skoar.

Cats definitely wake Cthulhu.

	^^(;=^.^=;)^^

# Recap of various skoar blocks

    <? comment ?>

    {: loop_part :: condition :}
        
    {? condition ?? if_part ?? else_part ?}
    
    {? condition ?? 
        .voice_1    if_part ?? else_part 
        .voice_2    if_part ?? else_part 
        ...
        .voice_n    if_part ?? else_part 
    ?}
    
    {! skoarpion_name<args> !! skoarpion_body !}
    {! skoarpion_name !! skoarpion_body !}
    {! <args> !! skoarpion_body !}

    {! skoarpion_name<args> !! 
        .voice_1    skoarpion_body 
        .voice_2    skoarpion_body 
        ...
        .voice_n    skoarpion_body 
    !}
    
    ^^(; cthulhu_condition ;)^^
    
    < list_item_1, list_item_2, ... >
    

Install
=======

First, clone this git repo to, for example `~/GitHub/Skoarcery`

Get the very latest [SuperCollider 3.7](http://supercollider.github.io/download.html)

Point SuperCollider at the `~/GitHub/Skoarcery/SuperCollider/Skoar` folder: In SuperCollider's interpreter options (edit->preferences->interpreter), __include__ the folder `~/GitHub/Skoarcery` and
restart the interpreter.

Try the examples in [examples]. Dungeontimes is the simplest. 

If you are seeing failures about UnitTest not found, be sure you have pointed SC at `~/GitHub/Skoarcery/SuperCollider/Skoar` rather than `~/GitHub/Skoarcery`.

Skoarcery
=========

Skoarcery is the set of tools and tests that builds skoar compilers.

The lexical and syntactic analysers, `lex.sc` and `rdpp.sc` (ditto `.py`) are built with Skoarcery.
They are built and written to `.../SuperCollider/Skoar`.

Currently the built code is checked in, you don't need to get Skoarcery working unless you want to
work on the language.


### [terminals.py]
- Tokens by convention are UpperCamelCase.

- Tokens are defined with regexes that have to work with both SuperCollider and Python.
All we do is recognise, no capture groups.

- Tokens are typically converted to Skoarpuscles in the top section of [decorating.sc]

### [nonterminals.py]
- Defines an LL(1) grammar suitable for building recursive decent predictive parsers for skoar.

- Nonterminals by convention are like_this

- \+ before a nonterminal indicates this is an intermediate step that can be skipped in the
constructed parse tree, it will not create a new skoarnode, instead appending its noads to
its parent's children list.

- Semantics defined in the second half of [decorating.sc]


### Misc Skoarcery

- [langoids.py] - Terminal, Nonterminal, Production objects,
- [dragonsets.py] - FIRST and FOLLOW sets, from the Dragon Book.
- [emissions.py] - Implements Python and SuperCollider coding.
- [underskoar.py] - Templates for lexer code


### [laboaratoary]
- These are our unit tests.
- Test the grammar for LL(1), test that it compiles in sclang, test skoars, etc..

### [factoary]
- These are written as unit tests, they build our lexers and parsers. Done this way because we
generate some information, test it, build on it, test that ...

- The important one at the moment is [Build_Sc.py], it will run tests,
build files, run more tests, etc.. it builds Skoar. This one builds Skoar.

- [Code_Lexer_Py.py], [Code_Lexer_Sc.py] - Build lex.py, lex.sc
- [Code_Parser_Py.py], [Code_Parser_Sc.py] - Build rdpp.py, rdpp.sc


### Skoar Code
### The Generated Code

- [lex.sc] - Lexical analyser, defines classes for each token, extending SkoarToke.
    - in Skoar, we call them Tokes, in Skoarcery, they are Terminals, or tokens.

- [rdpp.sc] - Recursive descent predictive parser. Builds the parse tree.

### The Hand Coded Code - Mostly The Runtime

- [skoar.sc] - The skoar object you get from compiling your skoar. From here you get a pattern object and play it.
- [apparatus.sc] - The parse tree code. Noads, searching, iteration, etc.
- [decorating.sc] - Second stage, decorate the parse tree.
- [koar.sc] - Each voice is performed on a koar by a minstrel.
- [minstrel.sc] - Minstrels are agents who read and perform their own voice of a skoar piece.
- [skoarpions.sc] - Implements the Skoarpion, our general purpose control-flow construct.
- [beaty.sc] - The code for beats and rests.
- [pitchy.sc] - The code for pitchy stuff. Noats, choards, etc.
- [toker.sc] - Toker for the parser.
- [skoarpuscles.sc] - Skoarpuscles, the thingy things are all skoarpuscles.


[examples]:    https://github.com/sofakid/Skoarcery/tree/master/SuperCollider/examples

[terminals.py]:    https://github.com/sofakid/Skoarcery/blob/master/Skoarcery/terminals.py
[nonterminals.py]: https://github.com/sofakid/Skoarcery/blob/master/Skoarcery/nonterminals.py

[toke_inspector.sc]: https://github.com/sofakid/Skoarcery/blob/master/SuperCollider/Skoar/toke_inspector.sc
[toke_inspector.py]: https://github.com/sofakid/Skoarcery/blob/master/Skoarcery/pymp/toke_inspector.py


[langoids.py]:   https://github.com/sofakid/Skoarcery/blob/master/Skoarcery/langoids.py
[dragonsets.py]: https://github.com/sofakid/Skoarcery/blob/master/Skoarcery/dragonsets.py
[emissions.py]:  https://github.com/sofakid/Skoarcery/blob/master/Skoarcery/emissions.py
[underskoar.py]: https://github.com/sofakid/Skoarcery/blob/master/Skoarcery/underskoar.py

[laboaratoary]:  https://github.com/sofakid/Skoarcery/tree/master/Skoarcery/laboaratoary/
[factoary]:      https://github.com/sofakid/Skoarcery/tree/master/Skoarcery/factoary/

[Build_Sc.py]:       https://github.com/sofakid/Skoarcery/blob/master/Skoarcery/factoary/Build_Sc.py
[Code_Lexer_Py.py]:  https://github.com/sofakid/Skoarcery/blob/master/Skoarcery/factoary/Code_Lexer_Py.py
[Code_Lexer_Sc.py]:  https://github.com/sofakid/Skoarcery/blob/master/Skoarcery/factoary/Code_Lexer_Sc.py
[Code_Parser_Py.py]: https://github.com/sofakid/Skoarcery/blob/master/Skoarcery/factoary/Code_Parser_Py.py
[Code_Parser_Sc.py]: https://github.com/sofakid/Skoarcery/blob/master/Skoarcery/factoary/Code_Parser_Sc.py

[lex.sc]:          https://github.com/sofakid/Skoarcery/blob/master/SuperCollider/Skoar/lex.sc
[rdpp.sc]:         https://github.com/sofakid/Skoarcery/blob/master/SuperCollider/Skoar/rdpp.sc
[apparatus.sc]:    https://github.com/sofakid/Skoarcery/blob/master/SuperCollider/Skoar/apparatus.sc
[decorating.sc]:   https://github.com/sofakid/Skoarcery/blob/master/SuperCollider/Skoar/decorating.sc
[skoar.sc]:        https://github.com/sofakid/Skoarcery/blob/master/SuperCollider/Skoar/skoar.sc
[minstrel.sc]:     https://github.com/sofakid/Skoarcery/blob/master/SuperCollider/Skoar/minstrel.sc
[beaty.sc]:        https://github.com/sofakid/Skoarcery/blob/master/SuperCollider/Skoar/beaty.sc
[pitchy.sc]:       https://github.com/sofakid/Skoarcery/blob/master/SuperCollider/Skoar/pitchy.sc
[skoarpions.sc]:   https://github.com/sofakid/Skoarcery/blob/master/SuperCollider/Skoar/skoarpions.sc
[koar.sc]:         https://github.com/sofakid/Skoarcery/blob/master/SuperCollider/Skoar/koar.sc
[skoarpuscles.sc]: https://github.com/sofakid/Skoarcery/blob/master/SuperCollider/Skoar/skoarpuscles.sc
[toker.sc]:        https://github.com/sofakid/Skoarcery/blob/master/SuperCollider/Skoar/toker.sc

[SuperCollider]: https://github.com/supercollider/supercollider
[examples.md]:   https://github.com/sofakid/Skoarcery/blob/master/examples.md