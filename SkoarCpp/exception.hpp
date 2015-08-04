#pragma once
#include "skoarcery.hpp"

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
	SkoarParseException();
	SkoarParseException(wstring s);
};
