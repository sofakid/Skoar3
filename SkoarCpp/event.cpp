#include "event.hpp"

#include "skoarpuscle.hpp"
#include "exception.hpp"

SkoarDic::SkoarDic() {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o().allocSkoarDic(L"dic");
#endif
	//not_found = nullptr;
}

SkoarDic::~SkoarDic() {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o().deallocSkoarDic(L"dic");
#endif
    //not_found = nullptr;
    table.clear();
}

void SkoarDic::put(SkoarString k, SkoarpusclePtr v) {
    table[k] = v;
}

SkoarpusclePtr SkoarDic::at(const SkoarString &k) {
    return table[k];
}

void SkoarDic::clear() {
    for (auto kv : table)
    {
        auto v = kv.second;
        if (v != nullptr)
            v->clear ();

    }
    table.clear();
}

size_t SkoarDic::size() {
    return table.size();
}


// --- SkoarEvent --------------------------------------------
SkoarEvent::SkoarEvent() {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o().allocSkoarDic(L"event");
#endif
    //not_found = nullptr;
}

SkoarEvent::~SkoarEvent() {
#if SKOAR_DEBUG_MEMORY
    SkoarMemories::o().deallocSkoarDic(L"event");
#endif
    //not_found = nullptr;
    table.clear();
}

void SkoarEvent::from(SkoarDicPtr dic) {
	auto src = dic->table;
	if (src.empty())
		return;

	for (auto pair : src) {
		auto key = pair.first;
		auto skoarpuscle = pair.second;
		table[key] = skoarpuscle;
	}
}

// --- SkoarEventStream --------------------------------------------
SkoarEventStream::SkoarEventStream() {

}
SkoarEventStream::~SkoarEventStream() {

}

SkoarEventPtr SkoarEventStream::next() {
    return nullptr;
}

