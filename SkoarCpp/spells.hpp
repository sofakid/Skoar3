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
typedef std::wstring SkoarString;

typedef std::vector<SkoarInt> ListOfSkoarInts;
typedef std::vector<SkoarFloat> ListOfSkoarFloats;
typedef std::vector<SkoarString> ListOfSkoarStrings;

typedef std::shared_ptr<std::vector<SkoarInt>> ListOfSkoarIntsPtr;
typedef std::shared_ptr<std::vector<SkoarFloat>> ListOfSkoarFloatsPtr;
typedef std::shared_ptr<std::vector<SkoarString>> ListOfSkoarStringsPtr;

typedef std::shared_ptr<SkoarNoad> SkoarNoadPtr;
typedef std::vector<SkoarNoadPtr> ListOfSkoarNoadPtrs;
typedef std::vector<ESkoarNoad::Kind> ListOfSkoarNoadKinds;

typedef std::unique_ptr<SkoarToke> SkoarTokePtr;
typedef std::vector<ESkoarToke::Kind> ListOfSkoarTokeKinds;

typedef std::shared_ptr<Skoarpuscle> SkoarpusclePtr;
typedef std::shared_ptr<SkoarDic> SkoarDicPtr;
typedef std::shared_ptr<SkoarMinstrel> SkoarMinstrelPtr;
typedef std::shared_ptr<Skoarpion> SkoarpionPtr;
typedef std::shared_ptr<SkoarpionProjection> SkoarpionProjectionPtr;
typedef std::shared_ptr<SkoarKoar> SkoarKoarPtr;
typedef std::shared_ptr<SkoarEvent> SkoarEventPtr;
typedef std::shared_ptr<SkoarEventStream> SkoarEventStreamPtr;

typedef std::shared_ptr<SkoarFairy> SkoarFairyPtr;

typedef std::vector<SkoarMinstrelPtr> ListOfMinstrels;

typedef std::vector<SkoarDicPtr> ListOfSkoarDics;
typedef std::unique_ptr<ListOfSkoarDics> ListOfSkoarDicsPtr;

typedef std::vector<SkoarEventPtr> ListOfSkoarEvents;
typedef std::shared_ptr<ListOfSkoarEvents> ListOfSkoarEventsPtr;


typedef std::vector<SkoarEventPtr> VectorOfSkoarEvents;
typedef std::shared_ptr<VectorOfSkoarEvents> VectorOfSkoarEventsPtr;

typedef std::vector<SkoarNoadite> VectorOfNoadites;

typedef std::vector<SkoarpusclePtr> ListOfSkoarpuscles;
typedef std::shared_ptr<ListOfSkoarpuscles> ListOfSkoarpusclesPtr;

typedef std::vector<SkoarpionPtr> ListOfSkoarpions;
typedef std::shared_ptr<ListOfSkoarpions> ListOfSkoarpionsPtr;

typedef std::vector<SkoarpionProjectionPtr> ListOfSkoarpionProjections;
typedef std::shared_ptr<ListOfSkoarpionProjections> ListOfSkoarpionProjectionsPtr;

typedef std::function<void(SkoarMinstrelPtr)> SpellOfMinstrels;
typedef std::function<void(SkoarNoad *)> SpellOfNoads;
typedef std::function<void(SkoarNoadPtr)> SpellOfNoadPtrs;

typedef std::function<void(SkoarpusclePtr)> SpellOfSkoarpucles;

typedef std::function<void(SkoarMinstrelPtr, SkoarNoadite*)> SpellOfDebuggingNoads;
typedef std::function<void(SkoarMinstrelPtr, SkoarpusclePtr)> SpellOfDebuggingSkoarpuscles;
typedef std::function<void(SkoarMinstrelPtr, SkoarpionPtr)> SpellOfDebuggingSkoarpions;
typedef std::function<void()> SpellOfDebuggingExiting;

typedef std::function<void(Skoar*, SkoarNoadPtr, SkoarToke*)> SpellOfTokeyDecoration;
typedef std::function<void(Skoar*, SkoarNoadPtr)> SpellOfNoadyDecoration;

typedef std::function<void()> SpellOfDecency;


typedef std::function<void()> AncientArcaneMagic;
typedef std::function<SkoarpusclePtr()> ArcaneMagic;
#define HarmlessMagic [](){}

typedef std::function<void()> SpellOfSimplicity;
typedef std::function<void(SkoarEventPtr)> SpellOfHappening;


typedef std::function<void(std::string&)> SpellOfUtterance;
