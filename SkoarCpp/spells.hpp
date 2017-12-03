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
#include "fairy_fwd.hpp"

typedef long long SkoarInt;
typedef double SkoarFloat;
typedef wstring SkoarString;

typedef vector<SkoarInt> ListOfSkoarInts;
typedef vector<SkoarFloat> ListOfSkoarFloats;
typedef vector<SkoarString> ListOfSkoarStrings;

typedef shared_ptr<vector<SkoarInt>> ListOfSkoarIntsPtr;
typedef shared_ptr<vector<SkoarFloat>> ListOfSkoarFloatsPtr;
typedef shared_ptr<vector<SkoarString>> ListOfSkoarStringsPtr;

typedef unique_ptr<SkoarToke> SkoarTokePtr;
typedef shared_ptr<SkoarNoad> SkoarNoadPtr;
typedef shared_ptr<Skoarpuscle> SkoarpusclePtr;
typedef shared_ptr<SkoarDic> SkoarDicPtr;
typedef shared_ptr<SkoarMinstrel> SkoarMinstrelPtr;
typedef shared_ptr<Skoarpion> SkoarpionPtr;
typedef shared_ptr<SkoarpionProjection> SkoarpionProjectionPtr;
typedef shared_ptr<SkoarKoar> SkoarKoarPtr;
typedef shared_ptr<SkoarEvent> SkoarEventPtr;
typedef shared_ptr<SkoarEventStream> SkoarEventStreamPtr;

typedef shared_ptr<SkoarFairy> SkoarFairyPtr;

typedef vector<SkoarMinstrelPtr> ListOfMinstrels;

typedef vector<SkoarDicPtr> ListOfSkoarDics;
typedef unique_ptr<ListOfSkoarDics> ListOfSkoarDicsPtr;

typedef vector<SkoarEventPtr> ListOfSkoarEvents;
typedef shared_ptr<ListOfSkoarEvents> ListOfSkoarEventsPtr;


typedef vector<SkoarEventPtr> VectorOfSkoarEvents;
typedef shared_ptr<VectorOfSkoarEvents> VectorOfSkoarEventsPtr;

typedef vector<SkoarNoadite> VectorOfNoadites;

typedef vector<SkoarpusclePtr> ListOfSkoarpuscles;
typedef shared_ptr<ListOfSkoarpuscles> ListOfSkoarpusclesPtr;

typedef vector<SkoarpionPtr> ListOfSkoarpions;
typedef shared_ptr<ListOfSkoarpions> ListOfSkoarpionsPtr;

typedef vector<SkoarpionProjectionPtr> ListOfSkoarpionProjections;
typedef shared_ptr<ListOfSkoarpionProjections> ListOfSkoarpionProjectionsPtr;

typedef function<void(SkoarMinstrelPtr)> SpellOfMinstrels;
typedef function<void(SkoarNoad *)> SpellOfNoads;
typedef function<void(SkoarNoadPtr)> SpellOfNoadPtrs;

typedef function<void(SkoarpusclePtr)> SpellOfSkoarpucles;

typedef function<void(SkoarMinstrelPtr, SkoarNoadite*)> SpellOfDebuggingNoads;
typedef function<void(SkoarMinstrelPtr, SkoarpusclePtr)> SpellOfDebuggingSkoarpuscles;
typedef function<void(SkoarMinstrelPtr, SkoarpionPtr)> SpellOfDebuggingSkoarpions;
typedef function<void()> SpellOfDebuggingExiting;

typedef function<void(Skoar*, SkoarNoadPtr, SkoarToke*)> SpellOfTokeyDecoration;
typedef function<void(Skoar*, SkoarNoadPtr)> SpellOfNoadyDecoration;

typedef function<void()> SpellOfDecency;


typedef function<void()> AncientArcaneMagic;
typedef function<SkoarpusclePtr()> ArcaneMagic;
#define HarmlessMagic [](){}

typedef function<void()> SpellOfSimplicity;
typedef function<void(SkoarEventPtr)> SpellOfHappening;


typedef function<void(string&)> SpellOfUtterance;
