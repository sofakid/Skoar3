80 => )

.h {= @lin 0 (0.0001) 1 ]]]] 0.3 ]]] 0 =}.env.a * aWhiteNoise * aLFTri * 2  piano       aPan2<pos:-0.3>
.s aSaw<{= 500 (0.08) 400 =}.env.k> + aSaw<{= 350 (0.08) 400 =}.env.k> + aWhiteNoise /3  ff    aPan2<pos:0.1>

.k aNormalizer<aSinOsc<freq:{= 400 (0.08) 66 =}.env.k, phase:3.14159265 * 0.5>, 1>  aRLPF<@in, 300> fff  aPan2<pos:0>


.high mf aLFTri * aLFNoise0<mul:0.1> + aLFNoise1<mul:kMouseY<0,2>> * aSinOsc + aLFTri<mul:kMouseY<1.2,0.2>> aPan2<pos:kMouseX<-0.3,1>>
.low o~~ ff aLFSaw + aLFNoise2 aRLPF<@in, kMouseY<300,500>> aPan2<pos:kMouseX<-1,0.3>>

{! high_a !!  4/4

  {! foo<x> !! {: !x.{: ]] :} :: 4 times :} !}

  <<_g , _a#, d, d#>,
   <_f#, _a#, d, d#>,
   <_f , _g#, d, d#>,
   <_e , _g , d, d#>,
   <_d#, _g , c, d >,
   <_d , _g , c, d >>.{: !foo<$> :}

!}

{! high_b !! 5/4
  < _c, _f#, _a,  c ,   _f#, _a,  c, d#,   _a, c, d#,     c, d#, f#,  d#, f#,  a,  _f#,  a, ~o  c>.{: ]] :} o~
!}

{! low_a !!  4/4
  |  g ))                                                a# )     ~o d )                                      |
  |   c# ) o~                   f# )).                                                                        |
  |  f ))                                                   f ].             g# ].             ~o c# ]        |
  |   c ) o~                   e )).                                                                          |
  | _d# ]] _d ]] _d# ).                                     g ].        ~o   d# ].                 d ]  o~    |
  | _d ]] _c# ]]  _d ).                                     g ].         ~o   d ].                c# ]  o~    |
!}

{! low_b !! 5/4
   ~o < _d, _f#, _a, _f#,      _a,  c, _a,  c,      d#, c, d#,  ~o  f#,     a , f#,  d#,  c,    d#,  c, _a, _f#>.{: ]] :} o~~
!}

{! drumsBasic !! 4/4
  .h  {: {? 3 times ?? ] ]  ] ]  ] ]  }  ?? ]] oo/ ]  oo/ ]] ]] ]]  ]] oo/ ]] oo/  ]] ]] oo/ ]] ?} :: 6 times :}
  .s  {: {? 4 times ?? }   )   }   )     ?? )         ] ]           ]] ]]  ]       }            ?} :: 6 times :}
  .k  {: ))      ))      :: 6 times :}
!}


{! drumsFun !! 5/4
  .h | ] ]   ] ]] ]]   }  ] ]] ]]   ]] ]] ]] ]]  |
  .s | }     )         }  ] ]       )            |
  .k | ))              }  ))                     |
!}

,segno`

!drumsBasic !drumsFun

.high   !high_a !high_b
.low    !low_a  !low_b

D.S.

