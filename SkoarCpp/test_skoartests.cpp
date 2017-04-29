#include "testing_util.hpp"
#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <locale>
#include <codecvt>


wstring read_file_contents (string filename) {
    wifstream infile { filename };
    infile.imbue (std::locale (infile.getloc (), new std::codecvt_utf16<wchar_t, 0x10ffff, std::little_endian>));
    wstring file_contents { istreambuf_iterator<wchar_t> (infile), istreambuf_iterator<wchar_t> () };
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