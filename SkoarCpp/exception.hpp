#pragma once
#include "skoarcery.hpp"
#include "noad_fwd.hpp"
#include "spells.hpp"

class SkoarError : public std::exception
{
public:
    SkoarString sWhat;

	SkoarError();
	SkoarError(SkoarString s);
	virtual const wchar_t* wwhat() const throw();
    virtual const char* what() const throw();
};


class SkoarTokerException : public SkoarError {
public:
    SkoarNoadPtr noad;

    SkoarTokerException();
    SkoarTokerException(SkoarString s);
    SkoarTokerException(SkoarString s, SkoarNoadPtr noad);
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


class SkoarDecoratingException : public SkoarError {
public:
    SkoarpusclePtr skoarpuscle;

    SkoarDecoratingException();
    SkoarDecoratingException(SkoarString s);
    SkoarDecoratingException(SkoarString s, SkoarpusclePtr p);

};

class SkoarRuntimeException : public SkoarError {
public:
    SkoarpusclePtr skoarpuscle;

    SkoarRuntimeException();
    SkoarRuntimeException(SkoarString s);
    SkoarRuntimeException(SkoarString s, SkoarpusclePtr p);

};
