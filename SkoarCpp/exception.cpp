#include "exception.hpp"

SkoarError::SkoarError() {
	sWhat = string("Unknown");
}

SkoarError::SkoarError(string s) {
	sWhat = s;
}

const char* SkoarError::what() const throw() {
	return sWhat.c_str();
}


SkoarParseException::SkoarParseException() {
	sWhat = string("Parse fail.");
}

SkoarParseException::SkoarParseException(string s) {
	sWhat = s;
}

