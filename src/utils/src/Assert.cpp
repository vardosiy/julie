#include "utils/Assert.hpp"
#include "utils/LogDefs.hpp"

//-----------------------------------------------------------------------------

namespace utils {

//-----------------------------------------------------------------------------

void assertImpl(
	bool _cond,
	const char * _expr,
	const char * _file,
	int _line,
	const char * _message
)
{
	if (!_cond)
	{
		LOG("[ASSERT] {} [DETAILS] {} ({}, line {})", _message, _expr, _file, _line);
		std::terminate();
	}
}

//-----------------------------------------------------------------------------

} // namespace utils

//-----------------------------------------------------------------------------
