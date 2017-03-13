#include "beaty.hpp"
#include "skoarpuscle.hpp"
#include "lex.hpp"

SkoarpuscleRest::SkoarpuscleRest(SkoarToke *toke) {
	val.Int = toke->lexeme.length();
}

SkoarpuscleBeat::SkoarpuscleBeat(SkoarToke *toke) {
	val.Int = 0;

}