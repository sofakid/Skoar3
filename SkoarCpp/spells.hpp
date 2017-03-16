#pragma once
#include "skoarcery.hpp"
#include "minstrel_fwd.hpp"
#include "skoarpuscle_fwd.hpp"
#include "noad_fwd.hpp"
#include "lex_fwd.hpp"
#include "skoar_fwd.hpp"

typedef long long SkoarInt;
typedef double SkoarFloat;

typedef unique_ptr<SkoarToke> SkoarTokePtr;
typedef shared_ptr<SkoarNoad> SkoarNoadPtr;

typedef list<Skoarpuscle*> ListOfSkoarpuscles;
typedef shared_ptr<ListOfSkoarpuscles> ListOfSkoarpusclesPtr;
typedef wstring SkoarString;


typedef function<void(SkoarMinstrel *)> SpellOfMinstrels;
typedef function<void(SkoarNoad *)> SpellOfNoads;
typedef function<void(SkoarNoadPtr)> SpellOfNoadPtrs;

typedef function<void(Skoarpuscle *)> SpellOfSkoarpucles;

typedef function<void(SkoarToke *, SkoarNoadPtr)> SpellOfTokeyDecoration;
typedef function<void(Skoar *, SkoarNoadPtr)> SpellOfNoadyDecoration;


typedef function<Skoarpuscle*()> ArcaneMagic;
#define HarmlessMagic [](){return nullptr;}
