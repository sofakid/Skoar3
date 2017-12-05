#define CATCH_CONFIG_NOSTDOUT 
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "testoar_reporter.hpp"

#include "exception.hpp"
#include "testoar.hpp"
#include "testoar_streams.hpp"

#ifdef CATCH_CONFIG_NOSTDOUT
namespace Catch {
    // I #define CATCH_CONFIG_NOSTDOUT so then I must implement these functions

    std::ostream& cout() {
        return TestoarCatchStreamoar::getInstance()->outStream;
    }
    std::ostream& cerr() {
        return TestoarCatchStreamoar::getInstance()->errStream;
    }
}
#endif

// --- private (this file) functions ----------------------------------------------------------------------

static ListOfTagCountPairs getListOfTagsCounts(Catch::Config const& config);
static ListOfTestCases getListOfTestCases(Catch::Config const& config);

static ListOfTagCountPairs getListOfTagsCounts(Catch::Config const& config) {
    Catch::TestSpec testSpec = config.testSpec();
    if (config.testSpec().hasFilters() == false) {
        testSpec = Catch::TestSpecParser(Catch::ITagAliasRegistry::get()).parse("*").testSpec();
    }

    std::map<std::string, Catch::TagInfo> tagCounts;
    ListOfTagCountPairs outList;

    std::vector<Catch::TestCase> matchedTestCases = filterTests(getAllTestCasesSorted(config), testSpec, config);
    for (std::vector<Catch::TestCase>::const_iterator it = matchedTestCases.begin(), itEnd = matchedTestCases.end();
        it != itEnd;
        ++it) {
        for (std::set<std::string>::const_iterator  tagIt = it->getTestCaseInfo().tags.begin(),
            tagItEnd = it->getTestCaseInfo().tags.end();
            tagIt != tagItEnd;
            ++tagIt) {
            std::string tagName = *tagIt;
            std::string lcaseTagName = Catch::toLower(tagName);
            std::map<std::string, Catch::TagInfo>::iterator countIt = tagCounts.find(lcaseTagName);
            if (countIt == tagCounts.end())
                countIt = tagCounts.insert(std::make_pair(lcaseTagName, Catch::TagInfo())).first;
            countIt->second.add(tagName);
        }
    }

    for (std::map<std::string, Catch::TagInfo>::const_iterator countIt = tagCounts.begin(),
        countItEnd = tagCounts.end();
        countIt != countItEnd;
        ++countIt) {

        outList.push_back(make_pair(countIt->second.all(), countIt->second.count));

    }

    return outList;
}


static ListOfTestCases getListOfTestCases(Catch::Config const& config) {
    Catch::TestSpec testSpec = config.testSpec();
    if (config.testSpec().hasFilters() == false) {
        testSpec = Catch::TestSpecParser(Catch::ITagAliasRegistry::get()).parse("*").testSpec();
    }

    std::map<std::string, Catch::TagInfo> tagCounts;
    ListOfTestCases outList;

    std::vector<Catch::TestCase> matchedTestCases = filterTests(getAllTestCasesSorted(config), testSpec, config);
    for (std::vector<Catch::TestCase>::const_iterator it = matchedTestCases.begin(), itEnd = matchedTestCases.end();
        it != itEnd;
        ++it) {

        outList.push_back(it->name);
    }

    return outList;
}


// --- public functions ----------------------------------------------------------------------------

void TestoarInitialize(SpellOfUtterance out, SpellOfUtterance err) {
    TestoarCatchStreamoar::setInstance(out, err);
    Catch::Session();
}

ListOfTags TestoarGetListOfTags() {
    Catch::ConfigData configData;
    configData.listTags = true;
    Catch::Config config(configData);
    ListOfTags out;
    auto pairs = getListOfTagsCounts(config);
    for (auto kv : pairs) {
        out.push_back(kv.first);
    }
    return out;
}

ListOfTestCases TestoarGetListOfTestCases(string tag) {
    Catch::ConfigData configData;
    configData.listTests = true;
    configData.testsOrTags.push_back(tag);
    Catch::Config config(configData);
    return getListOfTestCases(config);
}

int TestoarRunTests() {
    const char* argv[] = { "Testoar", "-r", "skoar" };
    return Catch::Session().run(sizeof(argv) / sizeof(*argv), argv);

}

int TestoarRunTestsByTag(string tag) {
    const char* argv[] = { "Testoar", "-r", "skoar", tag.c_str() };
    Catch::Session().run(sizeof(argv) / sizeof(*argv), argv);
    return 0;
}

int TestoarRunTestsByTestCase(string tc) {
    const char* argv[] = { "Testoar", "-r", "skoar", tc.c_str() };
    return Catch::Session().run(sizeof(argv) / sizeof(*argv), argv);
}

int TestoarRunTestsByTestCaseSection(string tc, string section) {
    const char* argv[] = { "Testoar", "-r", "skoar", tc.c_str(), "-c", section.c_str() };
    return Catch::Session().run(sizeof(argv) / sizeof(*argv), argv);
}
