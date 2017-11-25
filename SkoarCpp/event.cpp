#include "event.hpp"

#include "all_skoarpuscles.hpp"
#include "exception.hpp"

SkoarDic::SkoarDic () {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().allocSkoarDic (L"dic");
#endif
    //not_found = nullptr;
}

SkoarDic::~SkoarDic () {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().deallocSkoarDic (L"dic");
#endif
    //not_found = nullptr;
    clear ();
}

void SkoarDic::put (SkoarString k, SkoarpusclePtr v) {
    table[k] = v;
}

SkoarpusclePtr SkoarDic::at (const SkoarString &k) {
    return table[k];
}

void SkoarDic::clear () {
    /*
    
    Oh how tempting this is. Do not.
    There are stacks of these SkoarDics, when one is popped off, you don't want to go erasing everything.
    Lists in particular. 

    for (auto& kv : table)
    {
        auto& v (kv.second);
        if (v != nullptr)
            v->clear ();
    }*/
    table.clear ();
}

size_t SkoarDic::size () {
    return table.size ();
}


// --- SkoarEvent --------------------------------------------
SkoarEvent::SkoarEvent () {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().allocSkoarDic (L"event");
#endif
    //not_found = nullptr;
}

SkoarEvent::~SkoarEvent () {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o ().deallocSkoarDic (L"event");
#endif
    //not_found = nullptr;
    table.clear ();
}

void SkoarEvent::from (SkoarDicPtr dic) {
    auto src (dic->table);
    if (src.empty ())
        return;

    for (auto pair : src)
    {
        auto key (pair.first);
        if (key == SkoarString (L"num_impression"))
            continue;
        if (key == SkoarString (L"dyn_impression"))
            continue;
        if (key == SkoarString (L"sym_impression"))
            continue;

        auto skoarpuscle (pair.second);
        if (is_skoarpuscle<SkoarpuscleSkoarpion> (skoarpuscle))
            continue;

        table[key] = skoarpuscle;
    }
}

shared_ptr<SkoarEvent> SkoarEvent::duplicate ()
{
    auto ev (make_shared<SkoarEvent> ());

    for (auto& kv : table)
    {
        auto val (kv.second);
        if (val == nullptr)
            val = make_skoarpuscle (nullptr);

        ev->table[kv.first] = val->duplicate ();
    }

    return ev;
}

// --- SkoarEventStream --------------------------------------------
SkoarEventStream::SkoarEventStream () {

}
SkoarEventStream::~SkoarEventStream () {

}

SkoarEventPtr SkoarEventStream::next () {
    return nullptr;
}

