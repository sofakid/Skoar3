
#include "testoar_streams.hpp"

TestoarOutStream::TestoarOutStream(const SpellOfUtterance &spell) :
    std::ostream(&buffer), buffer(std::cout, spell)
{
}

int TestoarOutStream::StreamBuffer::sync()
{
    auto s = str();
    str(""); 
    spell(s);
    return 0;
}

TestoarOutStream::StreamBuffer::StreamBuffer(std::ostream& str, const SpellOfUtterance &utterance)
    : out(str), spell(utterance)
{
}

static std::unique_ptr<TestoarCatchStreamoar> instance;
TestoarCatchStreamoar* TestoarCatchStreamoar::getInstance() {
    return instance.get();
};

void TestoarCatchStreamoar::setInstance(SpellOfUtterance outSpell, SpellOfUtterance errSpell) {
    instance = std::make_unique<TestoarCatchStreamoar>(outSpell, errSpell);
}


TestoarCatchStreamoar::TestoarCatchStreamoar(SpellOfUtterance outSpell, SpellOfUtterance errSpell) :
    outStream(outSpell),
    errStream(errSpell)
{
}

