#pragma once
#include "skoarcery.hpp"
#include "noad_fwd.hpp"
#include "spells.hpp"

class SkoarError : public exception
{
public:
    SkoarString sWhat;

	SkoarError();
	SkoarError(SkoarString s);
	virtual const wchar_t* wwhat() const throw();
};

class SkoarParseException : public SkoarError {
public:
    SkoarNoadPtr noad;

	SkoarParseException();
	SkoarParseException(SkoarString s, SkoarNoadPtr noad);
};

class SkoarpuscleException : public SkoarError {
public:
    
    SkoarpuscleException();
    SkoarpuscleException(SkoarString s);
};
