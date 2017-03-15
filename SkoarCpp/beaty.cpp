#include "beaty.hpp"
#include "skoarpuscle.hpp"
#include "lex.hpp"

SkoarpuscleRest::SkoarpuscleRest(SkoarToke *toke) {
	val = toke->lexeme.length();
}

SkoarpuscleBeat::SkoarpuscleBeat(SkoarToke *toke) {
	val = 0;

}