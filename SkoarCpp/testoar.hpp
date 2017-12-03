#pragma once
#include "skoarcery.hpp"
#include "spells.hpp"

typedef std::vector<std::pair<std::string, size_t>> ListOfTagCountPairs;
typedef std::vector<std::string> ListOfTags;
typedef std::vector<std::string> ListOfTestCases;

void TestoarInitialize(SpellOfUtterance out, SpellOfUtterance err);

ListOfTags TestoarGetListOfTags();
ListOfTestCases TestoarGetListOfTestCases(string tag);


int TestoarRunTests();
int TestoarRunTestsByTag(string tag);
int TestoarRunTestsByTestCase(string tag);
int TestoarRunTestsByTestCaseSection(string tc, string section);
