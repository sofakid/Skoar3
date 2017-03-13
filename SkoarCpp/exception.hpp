#pragma once
#include "skoarcery.hpp"
#include "noad_fwd.hpp"
#include "spells.hpp"

class SkoarError : public exception
{
public:
	std::wstring sWhat;

	SkoarError();
	SkoarError(std::wstring s);
	virtual const wchar_t* wwhat() const throw();
};

class SkoarParseException : public SkoarError {
public:
    SkoarNoadPtr noad;

	SkoarParseException();
	SkoarParseException(wstring s, SkoarNoadPtr noad);
};
