#pragma once

#include "utils/LogDefs.hpp"

#include <string_view>
#include <exception>

//-----------------------------------------------------------------------------

class LoggingException : public std::exception
{
public:
	LoggingException(std::string_view _message)
		: std::exception(_message.data())
	{
		LOG_EXCEPTION("{}", _message);
	}
};

//-----------------------------------------------------------------------------
