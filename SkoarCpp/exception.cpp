#include "exception.hpp"

SkoarError::SkoarError() {
	sWhat = SkoarString(L"Unknown");
}

SkoarError::SkoarError(SkoarString s) :
    sWhat(s) {
}

const wchar_t* SkoarError::wwhat() const throw() {
	return sWhat.c_str();
}

SkoarParseException::SkoarParseException() {
	sWhat = SkoarString(L"Parse fail.");
}

SkoarParseException::SkoarParseException(wstring s, SkoarNoadPtr noad) :
    SkoarError(s), noad(noad) {
}

SkoarpuscleException::SkoarpuscleException() : SkoarError() {
}

SkoarpuscleException::SkoarpuscleException(SkoarString s) :
    SkoarError(s) {
}

