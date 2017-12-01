#include "pitchy.hpp"
#include "all_skoarpuscles.hpp"
#include "minstrel.hpp"
#include "fairy.hpp"

SkoarpuscleKey::SkoarpuscleKey (SkoarpusclePtr choard) 
{
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().allocSkoarpuscle (L"Key");
#endif
    noatworthy = false;
    impressionable = true;

    int i_root (0);
    SkoarString s_scale_name (L"");

    if (is_skoarpuscle<SkoarpuscleList> (choard))
    {
        auto a = skoarpuscle_ptr<SkoarpuscleList> (choard)->val;

        if (a->size () > 0)
        {
            auto& x (a->front ());

            if (is_skoarpuscle<SkoarpuscleChoard> (x))
                choard = x;

            if (a->size () > 1)
            {
                auto iter (a->cbegin ());
                auto y (*(++iter));

                if (is_skoarpuscle<SkoarpuscleSymbol> (y))
                    s_scale_name = skoarpuscle_ptr<SkoarpuscleSymbol> (y)->val;
            }
        }
    }

    if (is_skoarpuscle<SkoarpuscleChoard> (choard))
    {
        auto ch = skoarpuscle_ptr<SkoarpuscleChoard> (choard);
            
        auto &c_letter (ch->letter.front ());
        switch (c_letter)
        {
        case L'C':
            i_root = 0;
            break;
        case L'D':
            i_root = 2;
            break;
        case L'E':
            i_root = 4;
            break;
        case L'F':
            i_root = 5;
            break;
        case L'G':
            i_root = 7;
            break;
        case L'A':
            i_root = -1;
            break;
        case L'B':
            i_root = -3;
            break;
        };
        
        i_root += ch->sharps;
        auto minor = ch->lexeme.find(L'm', 0);
        if (minor != SkoarString::npos && s_scale_name == L"")
            s_scale_name = L"minor";

    }

    if (s_scale_name == L"")
        s_scale_name = L"major";

    scale = make_skoarpuscle(nullptr);
    scale_name = make_skoarpuscle (s_scale_name);
    root = make_skoarpuscle (i_root);
    // ... uhh..
    //
    //scale = Scale.all[scale_name];
}

SkoarpuscleKey::~SkoarpuscleKey () {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().deallocSkoarpuscle (L"Key");
#endif
    scale = nullptr;
    scale_name = nullptr;
    root = nullptr;
}

void SkoarpuscleKey::apply (SkoarEventPtr e)
{
    e->put (L"scale", scale);
    e->put (L"scale_name", scale_name);
    e->put (L"root", root);
}

// --- SkoarpuscleNoat ---------------------------------------------------------

const wregex noat_regex (wregex (L"^(_?)([a-g])", regex_constants::optimize));
const wregex sharps_regex (wregex (L"[a-g](#*|b*)$", regex_constants::optimize)); // leave this => " quote char for emacs.

SkoarpuscleNoat::SkoarpuscleNoat (SkoarString& lex) :
    Skoarpuscle (ESkoarpuscle::Noat),
    lexeme (lex) {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().allocSkoarpuscle (L"Noat");
#endif
    noatworthy = true;
    impressionable = true;

    SkoarString s = lex;
    SkoarString sletter;

    wsmatch r;
    std::regex_search (s.cbegin (), s.cend (), r, noat_regex);

    low = r[1] != L"";
    sletter = r[2];
    wchar_t &letter = sletter.front ();

    std::regex_search (s.cbegin (), s.cend (), r, sharps_regex);
    s = r[1];

    int x = -1;
    if (s.find (L'#', 0) != SkoarString::npos)
        x = 1;

    sharps = static_cast<int>(s.length()) * x;

    switch (letter)
    {
    case L'c':
        x = 0;
        break;
    case L'd':
        x = 2;
        break;
    case L'e':
        x = 4;
        break;
    case L'f':
        x = 5;
        break;
    case L'g':
        x = 7;
        break;
    case L'a':
        x = 9;
        break;
    case L'b':
        x = 11;
        break;
    }

    if (sharps > 0)
        ++x;
    else if (sharps < 0)
        --x;


    if (low == false)
        x = x + 12;

    val = x;
}

SkoarpuscleNoat::SkoarpuscleNoat (SkoarString& lex, bool low, int val, int sharps) :
    Skoarpuscle (ESkoarpuscle::Noat),
    lexeme (lex),
    low (low),
    val (val),
    sharps (sharps)
    {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().allocSkoarpuscle (L"Noat");
#endif
    noatworthy = true;
    impressionable = true;
}

SkoarpuscleNoat::~SkoarpuscleNoat () {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().deallocSkoarpuscle (L"Noat");
#endif
}

// --- SkoarpuscleNoat ---------------------------------------------------------

void SkoarpuscleNoat::on_enter (SkoarMinstrelPtr m) {
    m->fairy->impress (duplicate ());
}

SkoarpusclePtr SkoarpuscleNoat::duplicate ()
{
    return make_shared<SkoarpuscleNoat>(lexeme, low, val, sharps);
}

void SkoarpuscleNoat::execute (SkoarMinstrelPtr m) {
    auto& koar (*m->koar);
    koar.put (L"freq", nullptr);
    koar.put (L"note", make_skoarpuscle (val));
    koar.put (L"choard", nullptr);
}



// --- SkoarpuscleChoard ---------------------------------------------------------

// lexeme was matched by: (D(?![a.])|[ABCEFG])(#|b)?([Mm0-9]|sus|dim)*
const wregex ch_noat_regex (wregex (L"^~*([A-G])", regex_constants::optimize));
const wregex ch_sharps_regex (wregex (L"^~*[A-G](#|b)?", regex_constants::optimize));
const wregex ch_im_regex (wregex (L"[^i]m", regex_constants::optimize));

SkoarpuscleChoard::SkoarpuscleChoard (SkoarString& lex) :
    Skoarpuscle (ESkoarpuscle::Choard),
    lexeme (lex),
    val (make_shared<ListOfSkoarpuscles>())
{
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().allocSkoarpuscle (L"Choard");
#endif
    noatworthy = true;
    impressionable = true;

    SkoarString s (lex);

    wsmatch r;
    std::regex_search (s.cbegin (), s.cend (), r, ch_noat_regex);
    letter = r[1];
    wchar_t& c_letter (letter.front ());

    std::regex_search (s.cbegin (), s.cend (), r, ch_sharps_regex);
    s = r[1];

    s = r[1];

    int x = -1;
    if (s.find (L'#', 0) != SkoarString::npos)
        x = 1;

    sharps = static_cast<int>(s.length ()) * x;

    switch (c_letter)
    {
    case L'C':
        x = 0;
        break;
    case L'D':
        x = 2;
        break;
    case L'E':
        x = 4;
        break;
    case L'F':
        x = 5;
        break;
    case L'G':
        x = 7;
        break;
    case L'A':
        x = 9;
        break;
    case L'B':
        x = 11;
        break;
    }

    if (sharps > 0)
        ++x;
    else if (sharps < 0)
        --x;

    auto first = x;
    auto third = x + 4;
    auto fifth = x + 7;

    std::regex_search (lex.cbegin (), lex.cend (), r, ch_im_regex);
    if (r.length() != 0)
        --third;

    if (lex.find (L"sus2", 0) != SkoarString::npos)
        third -= 2;

    if (lex.find (L"sus4", 0) != SkoarString::npos)
        ++third;

    if (lex.find (L"dim", 0) != SkoarString::npos)
    {
        --third;
        --fifth;
    }

    if (lex.find (L"aug", 0) != SkoarString::npos)
        ++fifth;

    val->push_back (make_skoarpuscle (first));
    val->push_back (make_skoarpuscle (third));
    val->push_back (make_skoarpuscle (fifth));

    if (lex.find (L"M7", 0) != SkoarString::npos)
        val->push_back (make_skoarpuscle (first + 11));
    else
        if (lex.find (L"7", 0) != SkoarString::npos)
            val->push_back (make_skoarpuscle (first + 10));

    // fifth has already been incremented, so just + 1.
    if (lex.find (L"aug6", 0) != SkoarString::npos)
        val->push_back (make_skoarpuscle (fifth + 1)); 

}


SkoarpuscleChoard::SkoarpuscleChoard (SkoarString& lex, SkoarString& letter, int sharps, ListOfSkoarpusclesPtr v) :
    Skoarpuscle (ESkoarpuscle::Choard),
    lexeme (lex),
    letter (letter),
    sharps (sharps),
    val (v)
{
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().allocSkoarpuscle (L"Choard");
#endif
    noatworthy = true;
    impressionable = true;

}
SkoarpuscleChoard::~SkoarpuscleChoard () {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().deallocSkoarpuscle (L"Choard");
#endif
}

// --- SkoarpuscleChoard ---------------------------------------------------------
//void* SkoarpuscleChoard::asNoat () { return nullptr; }

void SkoarpuscleChoard::on_enter (SkoarMinstrelPtr m) {
    m->fairy->impress (duplicate ());
}

SkoarpusclePtr SkoarpuscleChoard::duplicate ()
{
    auto new_list (make_shared<ListOfSkoarpuscles> ());
    for (auto &s : *val)
        new_list->push_back (s->duplicate ());

    return make_shared<SkoarpuscleChoard>(lexeme, letter, sharps, new_list);
}

void SkoarpuscleChoard::execute (SkoarMinstrelPtr m) {
    auto& koar (*m->koar);
    koar.put (L"freq", nullptr);
    koar.put (L"note", nullptr);
    koar.put (L"choard", make_skoarpuscle(val));
}




/*
---------------------------------------------------------------------------
---------------------------------------------------------------------------
---------------------------------------------------------------------------
---------------------------------------------------------------------------
---------------------------------------------------------------------------
---------------------------------------------------------------------------

SkoarNoat {
    var <key;
    var <val;

    *new {
        | x |
        ^super.new.init(x);
    }

    asString { ^val.asString }
    
    execute {
        | minstrel |
        //"SkoarNoat.execute: ".post; key.post; val.postln;

        minstrel.koar[\freq] = nil;
        minstrel.koar[\degree] = nil;
        minstrel.koar[\note] = nil;
        minstrel.koar[\choard] = nil;
        
        minstrel.koar[key] = val;
    }
}

SkoarNoat_Freq : SkoarNoat {

    init {
        | x |
        key = \freq;
        val = x;
    }
}

SkoarNoat_Degree : SkoarNoat {

    init {
        | x |
        key = \degree;
        val = x;
    }
}

SkoarNoat_DegreeList : SkoarNoat {

    init {
        | x |
        key = \degree;
        val = [];

        x.do {
            | y |

            case {y.isKindOf(SkoarNoat_Degree)} {
                val = val.add(y.val);

            } {y.isKindOf(SkoarNoat_Freq)} {

                // this is wrong
                //val = val.add(y.val.cpsmidi);
                val = val.add(0);
                
            } {y.isKindOf(SkoarNoat_DegreeList)} {
                y.val.do {
                    | z |
                    val = val.add(z);
                };

            } {y.isKindOf(SkoarNoat_FreqList)} {
                y.val.do {
                    | z |
                    val = val.add(0);
                    //val = val.add(z.cpsmidi);
                };
            };
        };

        val = val.asArray;
    }
}

SkoarNoat_Note : SkoarNoat {

    init {
        | x |
        key = \note;
        val = x;
    }
}

SkoarNoat_NoteList : SkoarNoat {

    init {
        | x |
        key = \note;
        val = [];

        x.do {
            | y |
            //("NoteList: " ++ y ).postln;
            case {y.isKindOf(SkoarNoat_Note)} {
                val = val.add(y.val);

            } {y.isKindOf(SkoarNoat_Freq)} {

                // this is wrong
                //val = val.add(y.val.cpsmidi);
                val = val.add(0);
                
            } {y.isKindOf(SkoarNoat_NoteList)} {
                y.val.do {
                    | z |
                    val = val.add(z);
                };

            } {y.isKindOf(SkoarNoat_FreqList)} {
                y.val.do {
                    | z |
                    val = val.add(0);
                    //val = val.add(z.cpsmidi);
                };
            };
        };

        val = val.asArray;
    }
}

SkoarNoat_FreqList : SkoarNoat {

    init {
        | x |
        key = \freq;
        val = [];

        x.do {
            | y |

            case {y.isKindOf(SkoarNoat_Degree)} {
                //val = val.add(y.val.midicps);

            } {y.isKindOf(SkoarNoat_Freq)} {
                val = val.add(y.val);

            } {y.isKindOf(SkoarNoat_DegreeList)} {
                y.val.do {
                    | z |
                    //val = val.add(z.midicps);
                };

            } {y.isKindOf(SkoarNoat_FreqList)} {
                y.val.do {
                    | z |
                    val = val.add(z);
                };
            };

        };
        
        val = val.asArray;
    }
}
*/

