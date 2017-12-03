#include "toker.hpp"
#include "lex.hpp"
#include "exception.hpp"

// =========
// The Toker
// =========

static SkoarDispensary* dispensary (nullptr);
void SkoarToker::init () {
    dispensary = new SkoarDispensary ();
}

SkoarToker::SkoarToker (wstring &s) :
    i_am_here (0),
    i_saw (nullptr),
    skoarce (&s)
{
}

SkoarToke* SkoarToker::see (ESkoarToke::Kind want) {

    if (i_saw != nullptr)
    {
        if (i_saw->kind == want)
            return i_saw;

        return nullptr;
    }

    i_saw = dispensary->match_toke (want, skoarce, i_am_here);
    return i_saw;

}

SkoarToke* SkoarToker::sees (ListOfSkoarTokeKinds *wants) {

    i_am_here += Toke_Whitespace::burn (skoarce, i_am_here);

    for (auto want : *wants)
    {
        auto x (see (want));

        if (x != nullptr)
            return x;
    }

    return nullptr;
}

SkoarTokePtr SkoarToker::burn (ESkoarToke::Kind want, SkoarNoadPtr noad) {

    auto toke (i_saw);

    if (toke == nullptr)
        toke = see (want);

    if (toke != nullptr && toke->kind == want)
    {
        i_saw = nullptr;
        i_am_here = i_am_here + toke->burn ();
        i_am_here = i_am_here + Toke_Whitespace::burn (skoarce, i_am_here);
        return unique_ptr<SkoarToke> (toke);
    };

    //msg = "Tried to burn " + want->name + ", but saw " + toke->asString;

    //puts("Toker Fail.");
    //this->dump();

    throw SkoarTokerException (wstring (L"toker fail"), noad);
}

void SkoarToker::eof () {
    Toke_Eof::burn (skoarce, i_am_here);
}

void SkoarToker::dump () {
    /*("\nToker Dump" ++
    "\nhere   : " ++i_am_here.asString++
    "\nsaw    : " ++i_saw.asString++
    "\nskoarce: " ++skoarce.copyRange(0, i_am_here)
    ++ "_$_" ++skoarce.copyRange(i_am_here, skoarce.size)).postln;
  */
}