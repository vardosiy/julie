#pragma once

#include "utils/AssertData.hpp"

//-----------------------------------------------------------------------------

namespace utils {

void assertImpl(bool _cond, AssertData _data);

} // namespace utils

//-----------------------------------------------------------------------------

#define ASSERT_IMPL(_expr, _message)								\
do {																\
	::utils::assertImpl(											\
		!!(_expr),													\
		::utils::AssertData{ _message, #_expr, __FILE__, __LINE__ }	\
	);																\
} while(false)

//-----------------------------------------------------------------------------

#if defined(_DEBUG)
#	define ASSERT(_expr, _message) ASSERT_IMPL(_expr, _message)
#else
#	define ASSERT(_expr, _message) void(0)
#endif

//-----------------------------------------------------------------------------
