#include "memories.hpp"

SkoarMem::SkoarMem() :
    Tokes(0),
    Noads(0),
    Skoars(0),
    Skoarpuscles(0),
    Skoarpions(0),
    Projections(0),
    Koars(0),
    Fairies(0),
    Minstrels(0),
    SkoarDics(0),
    Events(0)
{
}

std::wostream& operator << (std::wostream& out, const SkoarMem& o) {
    out << 
        L"\n--- Memory Summary ------------------" <<
        L"\n Tokes: " << o.Tokes << 
        L"\n Noads: " << o.Noads << 
        L"\n Skoars: " << o.Skoars <<
        L"\n Skoarpuscles: " << o.Skoarpuscles <<
        L"\n Skoarpions: " << o.Skoarpions <<
        L"\n Projections: " << o.Projections <<
        L"\n Koars: " << o.Koars <<
        L"\n Fairies: " << o.Fairies <<
        L"\n Minstrels: " << o.Minstrels <<
        L"\n SkoarDics: " << o.Minstrels <<
        L"\n Events: " << o.Events;

    list<pair<SkoarString, const MemoriesMap*>> maps = {
        make_pair<SkoarString, const MemoriesMap*>(SkoarString(L"Tokes"), &o.TokesMap),
        make_pair<SkoarString, const MemoriesMap*>(SkoarString(L"Noads"), &o.NoadsMap),
        make_pair<SkoarString, const MemoriesMap*>(SkoarString(L"Skoarpuscles"), &o.SkoarpusclesMap),
        make_pair<SkoarString, const MemoriesMap*>(SkoarString(L"Skoarpions"), &o.SkoarpionsMap),
        make_pair<SkoarString, const MemoriesMap*>(SkoarString(L"Projections"), &o.ProjectionsMap),
        make_pair<SkoarString, const MemoriesMap*>(SkoarString(L"Koars"), &o.KoarsMap),
        make_pair<SkoarString, const MemoriesMap*>(SkoarString(L"Fairies"), &o.FairiesMap),
        make_pair<SkoarString, const MemoriesMap*>(SkoarString(L"Minstrels"), &o.MinstrelsMap),
        make_pair<SkoarString, const MemoriesMap*>(SkoarString(L"SkoarDics"), &o.SkoarDicsMap),
        make_pair<SkoarString, const MemoriesMap*>(SkoarString(L"Events"), &o.EventsMap)
    };
    

    out << "\n\n";
    for (auto x_pair : maps) {
        bool show = false;
      
        for (auto entry_pair : *(x_pair.second)) {
            auto count = entry_pair.second;
            if (count != 0) {
                if (show == false) {
                    show = true;
                    out << "\n--- " << x_pair.first << " ---------------------------\n";
                }
                out << "    " << entry_pair.first << ": " << count << "\n";
            }
        }
    }

    return out;
}

// for Catch
std::ostream& operator << (std::ostream& out, const SkoarMem& o) {
    wostringstream wout;
    wout << o;
    auto ws = wout.str();
    string s(ws.begin(), ws.end());
    out << s;
    return out;

}

namespace SkoarMemories {

    // I'm tempted to use a unique_ptr here, but, when killing the app, the memories 
    // object is destroyed before a bunch of skoarpuscles dealloc...
    // This only happens in debug builds, when quitting, so I really can't be arsed to do this "better". 
    // This stops the debugger from freaking out.
    SkoarMem* Memories;

    SkoarMem& o() {
        static bool isInitialized = false;
        if (isInitialized == false) {
            Memories = new SkoarMem();
            isInitialized = true;
        }

        return *Memories;
    }

}
