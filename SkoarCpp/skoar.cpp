#include "skoar.hpp"

#include "exception.hpp"
#include "decorating.hpp"
#include "noad.hpp"
#include "toker.hpp"
#include "koar.hpp"
#include "rdpp.hpp"
#include "operators.hpp"
#include "skoarpion.hpp"

// =====
// Skoar
// =====
Skoar::Skoar(std::string &skoarce) {
	this->skoarce = skoarce;
	long start_time;
	long parse_time;
	long decorate_time;

	this->skoarce = skoarce + "\n";
	tree = nullptr;
	toker = new SkoarToker(skoarce);
	auto parser = new SkoarParser();

	all_voice = new SkoarKoar(new string("all"));
	voices["all"] = all_voice;

	//skoarpions = List[];

	//start_time = Process.elapsedTime;

	//log(">>> parsing skoar...");
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

	//"<<< tree created, now decorating...".postln;
	decorate();
	// decorate_time = (Process.elapsedTime - start_time - parse_time).round(0.01);

	draw_skoarpions();

	// debug("Skoar parsed in " ++parse_time++ " seconds, decorated in  "
	//	++decorate_time++ ". Total: " ++(parse_time + decorate_time)++ " sec.");
}


void Skoar::decorate() {

	auto inspector = new SkoarTokeInspector();
	auto skoarmantics = new Skoarmantics();

	tree->depth_visit([&](SkoarNoad *noad) {
		auto t = noad->toke;

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
SkoarKoar *Skoar::get_voice(string *k) {
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
	throw SkoarError("^^(;,;)^^");

}

void Skoar::play() {
	//pskoar().play();
}

void Skoar::pskoar() {
	//return new Skoarchestra(this)->pfunk();
}

void Skoar::pvoice(string *voice_name) {
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
