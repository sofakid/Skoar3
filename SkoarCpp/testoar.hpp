#pragma once
#include "skoarcery.hpp"
#include "spells.hpp"

typedef std::vector<std::pair<std::string, size_t>> ListOfTagCountPairs;
typedef std::vector<std::string> ListOfTags;
typedef std::vector<std::string> ListOfTestCases;

void TestoarInitialize(SpellOfUtterance out, SpellOfUtterance err);

ListOfTags TestoarGetListOfTags();
ListOfTestCases TestoarGetListOfTestCases(std::string tag);


int TestoarRunTests();
int TestoarRunTestsByTag(std::string tag);
int TestoarRunTestsByTestCase(std::string tag);
int TestoarRunTestsByTestCaseSection(std::string tc, std::string section);
