#pragma once
#include "skoarcery.hpp"
#include "minstrel_fwd.hpp"
#include "skoarpuscle_fwd.hpp"
#include "noad_fwd.hpp"
#include "noadite_fwd.hpp"

typedef long long SkoarInt;
typedef double SkoarFloat;

typedef function<void(SkoarMinstrel *)> SpellOfMinstrels;
typedef function<void(SkoarNoad *)> SpellOfScrying;
typedef function<void(SkoarNoad *)> SpellOfNoads;
typedef function<void(Noadite *)> SpellOfNoadites;
typedef function<void(Skoarpuscle *)> SpellOfSkoarpucles;


typedef function<Skoarpuscle*()> ArcaneMagic;
#define HarmlessMagic [](){return nullptr;}
