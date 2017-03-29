#pragma once
#include "skoarcery.hpp"
#include "spells.hpp"
#include <iostream>

class TestoarOutStream : public std::ostream
{
    friend std::ostream& operator<< (std::ostream &out, const TestoarOutStream var);
private:

    class StreamBuffer : public std::stringbuf
    {
    private:
        std::ostream &out;
        SpellOfUtterance spell;

    public:
        StreamBuffer(std::ostream& str, const SpellOfUtterance &utterance);
        virtual int sync();
    };

    StreamBuffer buffer;

public:
    TestoarOutStream(const SpellOfUtterance &utterance);
};

class TestoarCatchStreamoar {
public:

    static TestoarCatchStreamoar* getInstance();
    static void setInstance(SpellOfUtterance outSpell, SpellOfUtterance errSpell);

    TestoarOutStream outStream;
    TestoarOutStream errStream;

    TestoarCatchStreamoar(SpellOfUtterance outSpell, SpellOfUtterance errSpell);

};

