#pragma once
#include "skoarcery.hpp"

class SkoarError : public exception
{
public:

	std::string sWhat;
	SkoarError() {
		sWhat = string("Unknown");
	}

	SkoarError(std::string s) {
		sWhat = s;
	}

	virtual const char* what() const throw()
	{
		return sWhat.c_str();
	}
};

class SkoarParseException : public SkoarError {
public:
	SkoarParseException();
	SkoarParseException(string s);
};
