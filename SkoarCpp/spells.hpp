#pragma once
#include "skoarcery.hpp"
#include "minstrel_fwd.hpp"
#include "skoarpuscle_fwd.hpp"
#include "noad_fwd.hpp"
#include "lex_fwd.hpp"
#include "skoar_fwd.hpp"
#include "event_fwd.hpp"
#include "skoarpion_fwd.hpp"
#include "koar_fwd.hpp"

typedef long long SkoarInt;
typedef double SkoarFloat;

typedef unique_ptr<SkoarToke> SkoarTokePtr;
typedef shared_ptr<SkoarNoad> SkoarNoadPtr;
typedef shared_ptr<Skoarpuscle> SkoarpusclePtr;
typedef shared_ptr<SkoarDic> SkoarDicPtr;
typedef shared_ptr<SkoarMinstrel> SkoarMinstrelPtr;
typedef shared_ptr<Skoarpion> SkoarpionPtr;
typedef shared_ptr<SkoarProjection> SkoarProjectionPtr;
typedef shared_ptr<SkoarKoar> SkoarKoarPtr;


typedef list<SkoarDicPtr> ListOfSkoarDics;
typedef unique_ptr<ListOfSkoarDics> ListOfSkoarDicsPtr;

typedef list<SkoarpusclePtr> ListOfSkoarpuscles;
typedef shared_ptr<ListOfSkoarpuscles> ListOfSkoarpusclesPtr;

typedef list<SkoarpionPtr> ListOfSkoarpions;
typedef shared_ptr<ListOfSkoarpions> ListOfSkoarpionsPtr;

typedef list<SkoarProjectionPtr> ListOfSkoarProjections;
typedef shared_ptr<ListOfSkoarProjections> ListOfSkoarProjectionsPtr;


typedef wstring SkoarString;

typedef function<void(SkoarMinstrelPtr)> SpellOfMinstrels;
typedef function<void(SkoarNoad *)> SpellOfNoads;
typedef function<void(SkoarNoadPtr)> SpellOfNoadPtrs;

typedef function<void(SkoarpusclePtr)> SpellOfSkoarpucles;

typedef function<void(SkoarToke *, SkoarNoadPtr)> SpellOfTokeyDecoration;
typedef function<void(Skoar *, SkoarNoadPtr)> SpellOfNoadyDecoration;

typedef function<SkoarpusclePtr()> ArcaneMagic;
#define HarmlessMagic [](){return nullptr;}
