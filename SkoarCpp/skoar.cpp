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

#include <ctime>

#include "memories.hpp"

// =====
// Skoar
// =====

Skoar::Skoar(std::wstring &skoarce, ISkoarLog *log) {
	this->log = log;
	//this->skoarce = skoarce;
	clock_t start_time;
    clock_t parse_time;
    clock_t decorate_time;

    float f_parse_time;
    float f_decorate_time;

	this->skoarce = skoarce + L"\n";
	tree = nullptr;
	toker = new SkoarToker(this->skoarce);
	auto parser = new SkoarParser(toker);

	all_voice = new SkoarKoar(new wstring(L"all"));
	voices[L"all"] = all_voice;

	//skoarpions = List[];

	start_time = clock();

	log->i(">>> parsing skoar...");
    try {
        tree = parser->skoar(nullptr);
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
    parser->sortDesirables();

	try {
		toker->eof();
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
	log->i("---< Undecorated Skoar Tree >---");
	//tree->log_tree(log);

	log->i("<<< tree created, now decorating...");
	decorate();
	decorate_time = clock()- start_time - parse_time;

	log->i("---< Decorated Skoar Tree >---");
	tree->log_tree(log);

	//draw_skoarpions();

    log->d("derp", 1, 2.0);

	log->i("+++ Skoar Parsed +++");// +tree->draw_tree());

    f_parse_time = static_cast<float>(parse_time) / CLOCKS_PER_SEC;
    f_decorate_time = static_cast<float>(decorate_time) / CLOCKS_PER_SEC;

	log->i("seconds parsing", f_parse_time, 
        "seconds decorating", f_decorate_time, 
        "seconds total: ", f_parse_time + f_decorate_time);
}

Skoar::~Skoar() {
    tree = nullptr;
}


void Skoar::decorate() {

	auto inspector = new SkoarTokeInspector();
	auto skoarmantics = new Skoarmantics();

	SkoarNoad::depth_visit(tree, [&](SkoarNoadPtr noad) {
		auto t = noad->toke.get();

		noad->size = 0;
		for (auto y : noad->children) {
			//noad->skoarce += y->skoarce;
			noad->size += y->size;
		}

		if (t != nullptr) {
			inspector->decorate(t, noad);
		}
		else {
			auto g = skoarmantics->table[noad->kind];
			
			if (g) {
				g(this, noad);
			}
		}
	});
}

// ----
// misc
// ----

// creates a new one if needed
SkoarKoar *Skoar::get_voice(wstring *k) {
	SkoarKoar *voice = nullptr;

	auto found = voices[*k];
	if (found != nullptr) {
		voice = found;
	} else {
		voice = new SkoarKoar(k);
		voices[*k] = voice;
	}

	return voice;
}

void Skoar::cthulhu(SkoarNoadPtr noad) {

	// TODO more
	//"^^(;,;)^^".postln;
	//dump();
	throw SkoarError(L"^^(;,;)^^");

}

void Skoar::play() {
	//pskoar().play();
}

void Skoar::pskoar() {
	//return new Skoarchestra(this)->pfunk();
}

void Skoar::pvoice(wstring *voice_name) {
//	return new SkoarMinstrel(this->tree, voices[voice_name], this)->pfunk();
}

void Skoar::draw_skoarpions() {
	for (auto x : skoarpions) {
		//x->post_tree();

		//"Projections: ".postln;
		for (auto pairs : voices) {
			auto koar_name = pairs.first;
			//auto projection = x->projection(koar_name);

			//projection->block->draw_tree();
		}
	}
}

// --------------------------------------------------------------------------------
// for highlighting

SkoarLite::SkoarLite(std::wstring &skoarce, ISkoarLog *log) :
    skoarce(skoarce + L"\n"), // i don't like this + L"\n" business.
    log(log),
    toker(this->skoarce)
{
    auto parser = SkoarParser(&toker);
    parsedOk = false;
    try {
        tree = parser.skoar(nullptr);
        parser.sortDesirables();
        
    }
    catch (SkoarParseException &e) {
        // someday we can like, underline the error or something.
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
        // someday we can like, underline the error or something.
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
                } else {
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


