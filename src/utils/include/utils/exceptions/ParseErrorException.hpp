#pragma once

#include "utils/exceptions/LoggingException.hpp"

//-----------------------------------------------------------------------------

class ParseErrorException : public LoggingException
{
public:
	ParseErrorException(std::string_view _message)
		: LoggingException(_message)
	{
	}
};

//-----------------------------------------------------------------------------
