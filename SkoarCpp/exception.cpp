#include "exception.hpp"

// --- SkoarError --------------------------------------------------------
SkoarError::SkoarError() {
	sWhat = SkoarString(L"Unknown");
}

SkoarError::SkoarError(SkoarString s) :
    sWhat(s) {
}

const wchar_t* SkoarError::wwhat() const throw() {
	return sWhat.c_str();
}

// --- SkoarParseException --------------------------------------------------------
SkoarParseException::SkoarParseException() {
	sWhat = SkoarString(L"Parse fail.");
}

SkoarParseException::SkoarParseException(wstring s, SkoarNoadPtr noad) :
    SkoarError(s), noad(noad) {
}

// --- SkoarpuscleException --------------------------------------------------------
SkoarpuscleException::SkoarpuscleException() : SkoarError() {
}

SkoarpuscleException::SkoarpuscleException(SkoarString s) :
    SkoarError(s) {
}

// --- SkoarDecoratingException --------------------------------------------------------
SkoarDecoratingException::SkoarDecoratingException() : 
    SkoarError(), skoarpuscle(nullptr) {
    sWhat = SkoarString(L"Decorate fail.");
}

SkoarDecoratingException::SkoarDecoratingException(SkoarString s) :
    SkoarError(s), skoarpuscle(nullptr) {
}


SkoarDecoratingException::SkoarDecoratingException(SkoarString s, SkoarpusclePtr p) :
    SkoarError(s), skoarpuscle(p) {
}

// --- SkoarRuntimeException --------------------------------------------------------
SkoarRuntimeException::SkoarRuntimeException() :
    SkoarRuntimeException(L"???") {
}

SkoarRuntimeException::SkoarRuntimeException(SkoarString s) :
    SkoarRuntimeException(s, nullptr) {
}

SkoarRuntimeException::SkoarRuntimeException(SkoarString s, SkoarpusclePtr p) :
    SkoarError(L"^^(;,;)^^ :: Runtime Exception :: " + s), skoarpuscle(p) {
}