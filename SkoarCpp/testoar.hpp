#pragma once
#include "skoarcery.hpp"
#include "spells.hpp"

typedef std::list<std::pair<std::string, size_t>> ListOfTagCountPairs;
typedef std::list<std::string> ListOfTags;
typedef std::list<std::string> ListOfTestCases;

void TestoarInitialize(SpellOfUtterance out, SpellOfUtterance err);

ListOfTags TestoarGetListOfTags();
ListOfTestCases TestoarGetListOfTestCases(string tag);


int TestoarRunTests();
int TestoarRunTestsByTag(string tag);
int TestoarRunTestsByTestCase(string tag);
int TestoarRunTestsByTestCaseSection(string tc, string section);
