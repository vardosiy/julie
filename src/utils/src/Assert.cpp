#include "utils/Assert.hpp"
#include "utils/LogDefs.hpp"

//-----------------------------------------------------------------------------

namespace utils {

//-----------------------------------------------------------------------------

void assertImpl(bool _cond, AssertData _data)
{
	if (!_cond)
	{
		LOG(
			"[ASSERT] {} [DETAILS] {} ({}, line {})",
			_data.message,
			_data.expr,
			_data.file,
			_data.line
		);
		std::terminate();
	}
}

//-----------------------------------------------------------------------------

} // namespace utils

//-----------------------------------------------------------------------------
