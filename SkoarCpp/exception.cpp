#include "exception.hpp"

SkoarError::SkoarError() {
	sWhat = wstring(L"Unknown");
}

SkoarError::SkoarError(wstring s) :
    sWhat(s) {
}

const wchar_t* SkoarError::wwhat() const throw() {
	return sWhat.c_str();
}

SkoarParseException::SkoarParseException() {
	sWhat = wstring(L"Parse fail.");
}

SkoarParseException::SkoarParseException(wstring s, SkoarNoadPtr noad) :
    SkoarError(s), noad(noad) {
}

SkoarAnyException::SkoarAnyException() : SkoarError() {
}

SkoarAnyException::SkoarAnyException(wstring s) :
    SkoarError(s) {
}

