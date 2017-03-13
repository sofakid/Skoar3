#include "memories.hpp"

SkoarMem::SkoarMem() :
    Tokes(0),
    Noads(0),
    Skoars(0)
{
}

std::wostream& operator << (std::wostream& out, const SkoarMem& o) {
    out << L"Tokes: " << o.Tokes << L", Noads: " << o.Noads << L", Skoars: " << o.Skoars;
    return out;
}

SkoarMem SkoarMemories;
