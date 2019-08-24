#pragma once

#include <exception>

//-----------------------------------------------------------------------------

class ParseErrorException : public std::exception
{
public:
	ParseErrorException()
		: std::exception("Can not parse element")
	{
	}
};

//-----------------------------------------------------------------------------
