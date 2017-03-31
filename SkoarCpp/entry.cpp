#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "testoar_reporter.hpp"
/*
#include "skoar_public.hpp"
#include <iostream>

#include <Windows.h>
#include "memories.hpp"
#include "operators.hpp"
#include "testoar.hpp"

int wmain(int argc, wchar_t *argv[], wchar_t *envp[]) {

    TestoarInitialize([](string s) { cout << s; }, [](string s) { cout << s; });
    
    auto listOfTags = TestoarGetListOfTags();
    for (auto tag_pair : listOfTags) {
        cout << tag_pair.first << " :: " << tag_pair.second << "\n";
        auto listOfTests = TestoarGetListOfTestCases(tag_pair.first);
        for (auto test_case : listOfTests) {
            cout << "\n// --- Test Case: " << test_case << "--------------------------------------\n";
            TestoarRunTestsByTestCase(test_case);
        }
    }
    
}

*/
