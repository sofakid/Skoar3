#include "testing_util.hpp"
#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <locale>
#include <codecvt>


std::wstring read_file_contents (std::string filename) {
    std::wifstream infile { filename };
    infile.imbue (std::locale (infile.getloc (), new std::codecvt_utf16<wchar_t, 0x10ffff, std::little_endian>));
    std::wstring file_contents { std::istreambuf_iterator<wchar_t> (infile), std::istreambuf_iterator<wchar_t> () };
    return file_contents;
}
/*
TEST_CASE ("Skoars", "[skoars]") {

    string files[] { "derp", "dorp" };

    for (auto filename : files)
    {
        SECTION (filename) {
            SkoarString skoarce (read_file_contents (filename));

            INFO (filename);
            INFO (SkoarString_to_s (skoarce));
            REQUIRE (false);

        }
    }

}
*/