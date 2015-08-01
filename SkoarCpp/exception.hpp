#pragma once
#include "skoarcery.hpp"

class SkoarError : public exception
{
public:
	std::string sWhat;
	SkoarError();
	SkoarError(std::string s);
	virtual const char* what() const throw();
};

class SkoarParseException : public SkoarError {
public:
	SkoarParseException();
	SkoarParseException(string s);
};
