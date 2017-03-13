#pragma once
#include <sstream>

class SkoarMem {
public:
    SkoarMem();

    long Tokes;
    long Noads;
    long Skoars;

    friend std::wostream& operator << (std::wostream& out, const SkoarMem& obj);

};

extern SkoarMem SkoarMemories;
