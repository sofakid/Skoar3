#include "skoarcery.hpp"
#include "skoar_public.hpp"
#include "logging.hpp"
#include <iostream>

// ---------------------------------------------------
void SkoarNullLogger::log_d(const std::wstring &) {}
void SkoarNullLogger::log_i(const std::wstring &) {}
void SkoarNullLogger::log_w(const std::wstring &) {}
void SkoarNullLogger::log_e(const std::wstring &) {}

// ---------------------------------------------------
void SkoarConsoleLogger::log_d(const std::wstring &s) {
    std::wcout << L"D .. " << s;// << std::endl;
}
void SkoarConsoleLogger::log_i(const std::wstring &s) {
    std::wcout << L"I -- " << s;// << std::endl;
}
void SkoarConsoleLogger::log_w(const std::wstring &s) {
    std::wcout << L"W == " << s;// << std::endl;
}
void SkoarConsoleLogger::log_e(const std::wstring &s) {
    std::wcout << L"E !! " << s;// << std::endl;
}