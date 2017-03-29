
#include "testoar_streams.hpp"

TestoarOutStream::TestoarOutStream(const SpellOfUtterance &spell) :
    std::ostream(&buffer), buffer(std::cout, spell)
{
}

int TestoarOutStream::StreamBuffer::sync()
{
    spell(str());
    str("");
    return 0;
}

TestoarOutStream::StreamBuffer::StreamBuffer(std::ostream& str, const SpellOfUtterance &utterance)
    : out(str), spell(utterance)
{
}

static unique_ptr<TestoarCatchStreamoar> instance;
TestoarCatchStreamoar* TestoarCatchStreamoar::getInstance() {
    return instance.get();
};

void TestoarCatchStreamoar::setInstance(SpellOfUtterance outSpell, SpellOfUtterance errSpell) {
    instance = make_unique<TestoarCatchStreamoar>(outSpell, errSpell);
}


TestoarCatchStreamoar::TestoarCatchStreamoar(SpellOfUtterance outSpell, SpellOfUtterance errSpell) :
    outStream(outSpell),
    errStream(errSpell)
{
}

