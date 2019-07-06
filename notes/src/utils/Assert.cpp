#include "Pch.hpp"

#include "Assert.hpp"

//-----------------------------------------------------------------------------

void assertion(const char * _expr, const char * _file, int _line, const char * _message)
{
	LOG("ASSERT: %1% DETAILS: %2% (%3%, line %4%)", _message, _expr, _file, _line);

	std::terminate();
}

//-----------------------------------------------------------------------------
