#include "exception.hpp"

SkoarError::SkoarError() {
	sWhat = wstring(L"Unknown");
}

SkoarError::SkoarError(wstring s) {
	sWhat = s;
}

const wchar_t* SkoarError::wwhat() const throw() {
	return sWhat.c_str();
}


SkoarParseException::SkoarParseException() {
	sWhat = wstring(L"Parse fail.");
}

SkoarParseException::SkoarParseException(wstring s) {
	sWhat = s;
}

