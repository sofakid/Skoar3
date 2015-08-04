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

// =====
// Skoar
// =====

Skoar::Skoar(std::wstring &skoarce, ISkoarLog *log) {
	this->log = log;
	this->skoarce = skoarce;
	//long start_time;
	//long parse_time;
	//long decorate_time;

	this->skoarce = skoarce + L"\n";
	tree = nullptr;
	toker = new SkoarToker(this->skoarce);
	auto parser = new SkoarParser(toker);

	all_voice = new SkoarKoar(new wstring(L"all"));
	voices[L"all"] = all_voice;

	//skoarpions = List[];

	//start_time = Process.elapsedTime;

	log->i(L">>> parsing skoar...");
	tree = parser->skoar(nullptr);

	try {
		toker->eof();
	} catch (SkoarError &e) {
		//log(e.what());
		toker->dump();
		throw e;
	}

	// parse_time = (Process.elapsedTime - start_time).round(0.01);
	
	//"---< Undecorated Skoar Tree >---".postln; tree.draw_tree.postln;
	log->i(L"---< Undecorated Skoar Tree >---" + tree->draw_tree());

	log->i(L"<<< tree created, now decorating...");
	decorate();
	// decorate_time = (Process.elapsedTime - start_time - parse_time).round(0.01);

	log->i(L"---< Decorated Skoar Tree >---" + tree->draw_tree());

	draw_skoarpions();

	log->i(L"+++ Skoar Parsed +++" + tree->draw_tree());
	// debug("Skoar parsed in " ++parse_time++ " seconds, decorated in  "
	//	++decorate_time++ ". Total: " ++(parse_time + decorate_time)++ " sec.");
}


void Skoar::decorate() {

	auto inspector = new SkoarTokeInspector();
	auto skoarmantics = new Skoarmantics();

	tree->depth_visit([&](SkoarNoad *noad) {
		auto t = noad->toke;

		noad->skoarce_len = 0;
		for (SkoarNoad *y : noad->children) {
			noad->skoarce += y->skoarce;
			noad->skoarce_len += y->skoarce_len;
		}

		if (t != nullptr) {
			inspector->decorate(t, noad);
		}
		else {
			auto g = skoarmantics->table[noad->name];
			
			if (g != nullptr) {
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

void Skoar::cthulhu(SkoarNoad *noad) {

	// TODO more
	//"^^(;,;)^^".postln;
	//dump();
	throw new SkoarError(L"^^(;,;)^^");

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

#include <Windows.h>
int main(int argc, TCHAR *argv[]) {

}
