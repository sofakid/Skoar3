#include "skoar.hpp"

#include "exception.hpp"
#include "decorating.hpp"
#include "noad.hpp"
#include "toker.hpp"
#include "koar.hpp"
#include "rdpp.hpp"
#include "operators.hpp"
#include "skoarpion.hpp"
#include "spells.hpp"
#include "logging.hpp"
#include "styles.hpp"
#include "toke_inspector.hpp"
#include "minstrel.hpp"

#include <ctime>

#include "memories.hpp"


// =====
// Skoar
// =====

void Skoar::init() {
    static bool isInitialized = false;
    if (isInitialized == false) {
        SkoarToker::init();
        SkoarParser::init();
        SkoarTokeInspector::init();
        Skoarmantics::init();
        SkoarOps::init();

        isInitialized = true;
    }
}

Skoar::Skoar(SkoarString skoarce, ISkoarLog *log) :
    skoarce(skoarce + L"\n"), // i don't like this + L"\n" business.
    log(log),
    toker(this->skoarce),
    parsedOk(false)
{
    Skoar::init();

#if SKOAR_DEBUG_MEMORY
    SkoarMemories.allocSkoar();
#endif

	//this->skoarce = skoarce;
	clock_t start_time;
    clock_t parse_time;
    clock_t decorate_time;

    float f_parse_time;
    float f_decorate_time;

	tree = nullptr;
	auto parser = SkoarParser(&toker);

	all_voice = make_shared<SkoarKoar>(this, SkoarString(L"all"));
	voices[L"all"] = all_voice;

	//skoarpions = List[];

    log->d(">>> parsing skoar...");
	start_time = clock();
    try {
        tree = parser.skoar(nullptr);
    }
    catch (SkoarParseException *e) {
        // someday we can like, underline the error or something.
        log->e("parse fail", e->wwhat());

        // delete the unfinished tree
        auto x = e->noad;
        while (x->parent != nullptr)
            x = x->parent;

        x->clear();
        x = nullptr;
        e->noad = nullptr;

        return;
    }
    parser.sortDesirables();

	try {
		toker.eof();
	}
    catch (SkoarError &e) {
        // someday we can like, underline the error or something.
        log->e("parse fail", e.wwhat());

        // delete the broken tree
        tree->clear();
        tree = nullptr;
    }

	parse_time = clock() - start_time;
	
	//"---< Undecorated Skoar Tree >---".postln; tree.draw_tree.postln;
	//log->i("---< Undecorated Skoar Tree >---");
	//tree->log_tree(log);

	//log->i("<<< tree created, now decorating...");
	decorate();
	decorate_time = clock()- start_time - parse_time;

    f_parse_time = static_cast<float>(parse_time) / CLOCKS_PER_SEC;
    f_decorate_time = static_cast<float>(decorate_time) / CLOCKS_PER_SEC;

	log->d("---< Decorated Skoar Tree >---");
	tree->log_tree(log);

	draw_skoarpions(log);

	log->d("+++ Skoar Parsed +++");// +tree->draw_tree());
    parsedOk = true;
    

	log->d("seconds parsing",    f_parse_time, 
           "seconds decorating", f_decorate_time, 
           "seconds total: ",    f_parse_time + f_decorate_time);
}

Skoar::~Skoar() {
    if (parsedOk) {
        for (auto skoarpion : skoarpions) {
            skoarpion->clear();
        }
        skoarpions.clear();
        
        for (auto v_pair : voices) {
            auto voice = v_pair.second;
            if (voice != nullptr)
                voice->clear();
        }
        
        voices.clear();
        all_voice = nullptr;
        
        tree->clear();

    }
    tree = nullptr;

#if SKOAR_DEBUG_MEMORY
    SkoarMemories.deallocSkoar();
#endif
}


void Skoar::decorate() {
    auto f = [&](SkoarNoadPtr noad) {
        auto t = noad->toke.get();
        if (t != nullptr) {
            SkoarTokeInspector::instance()->decorate(t, noad);
        }
        else {
            Skoarmantics::instance()->decorate(this, noad);
        }
    };

	SkoarNoad::depth_visit(tree, f);
}

// ----
// misc
// ----

// creates a new one if needed
SkoarKoarPtr Skoar::get_voice(const SkoarString &k) {
	SkoarKoarPtr voice = voices[k];
	if (voice != nullptr) {
        return voice;
	}

    voice = make_shared<SkoarKoar>(this, k);
	voices[k] = voice;

	return voice;
}

void Skoar::cthulhu(SkoarNoadPtr noad) {

	// TODO more
	//"^^(;,;)^^".postln;
	//dump();
	throw SkoarError(L"^^(;,;)^^");

}

void Skoar::play(const SpellOfHappening& spell) {
    Skoarchestra x(this, spell);
    for (auto m : x.minstrels) {
        m->start();
    }
}

void Skoar::draw_skoarpions(ISkoarLog *log) {

    if (log->getLevel() != ISkoarLog::debug)
        return;

    wostringstream stream;

	for (auto x : skoarpions) {
        stream << "\n";
		x->draw_tree(stream);

        stream << "\nProjections:\n";
		for (auto pairs : voices) {
			auto koar_name = pairs.first;
			auto projection = Skoarpion::projection(x, koar_name);

            projection = Skoarpion::projection(x, koar_name);
            projection->proj->draw_tree(stream);
            stream << "\n";
        }
	}
    
    log->i("draw_skoarpions\n", stream.str());
}

void Skoar::one_less_running() {
    // todo: lock a mutex
    --running;
    // todo: unlock the mutex
}

// --------------------------------------------------------------------------------
// for highlighting

SkoarLite::SkoarLite(SkoarString skoarce, ISkoarLog *log) :
    skoarce(skoarce + L"\n"), // i don't like this + L"\n" business.
    log(log),
    toker(this->skoarce),
    parsedOk(false)
{
    Skoar::init();

    auto parser = SkoarParser(&toker);
    
    try {
        tree = parser.skoar(nullptr);
        parser.sortDesirables();
        
    }
    catch (SkoarParseException &e) {
        // someday we can underline the error or something.
        log->d("parse fail", e.wwhat());
       
        // delete the unfinished tree
        auto x = e.noad;
        while (x->parent != nullptr)
            x = x->parent;

        x->clear();
        x = nullptr;
        e.noad = nullptr;
        return;
    }
    
    try {
        toker.eof();
        parsedOk = true; 
    }
    catch (SkoarError &e) {
        // someday we can underline the error or something.
        log->d("parse fail", e.wwhat());

        // delete the broken tree
        tree->clear();
        tree = nullptr;
    }
    
    if (parsedOk) {
        //log->i("parsing...", "noadites");
        //auto iter = noadites.elements.cbegin();

        size_t pos = 0;

        tree->inorderBeforeAfter(

            // Before
            [&](SkoarNoad* noad) {
                auto toke = noad->toke.get();

                if (toke != nullptr) {
                    pos = toke->offs + toke->size;
                    noad->offs = toke->offs;
                }
                else {
                    noad->offs = pos;
                }
            },

            // After
            [&](SkoarNoad* noad) {
                noad->size = pos - noad->offs;
            });

    }

    //log->e("False style", SkoarStyles::style<ESkoarToke::False>());
}

SkoarLite::~SkoarLite() {
    clock_t start_time;
    clock_t elapsed_time;

    float f_elapsed_time;

    start_time = clock();

    //log->i("\n\n");
    //log->i("----------------------------------");
    //log->i("Deleting SkoarLite...");
    //log->w("Memories", SkoarMemories);

    if (parsedOk) {
        tree->clear();
    }
    tree = nullptr;

    elapsed_time = clock() - start_time;
    f_elapsed_time = static_cast<float>(elapsed_time) / CLOCKS_PER_SEC;

    //log->i("Deleted SkoarLite.", "elapsed_time", f_elapsed_time);
    //log->w("Memories", SkoarMemories);
    //log->i("----------------------------------\n\n");

}
