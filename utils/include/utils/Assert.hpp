#ifndef __ASSERT_HPP__
#define __ASSERT_HPP__

//-----------------------------------------------------------------------------

namespace utils {

void assertImpl(
	bool _cond,
	const char * _expr,
	const char * _file,
	int _line,
	const char * _message
);

} // namespace utils

//-----------------------------------------------------------------------------

#define ASSERT_IMPL(_expr, _message)										\
do {																		\
	::utils::assertImpl(!!(_expr), #_expr, __FILE__, __LINE__, _message);	\
} while(false)

//-----------------------------------------------------------------------------

#if defined(_DEBUG)
#	define ASSERT(_expr, _message) ASSERT_IMPL(_expr, _message)
#	define ASSERT_FALSE(_message) ASSERT(false, _message)
#else
#	define ASSERT(_expr, _message) void(0)
#	define ASSERT_FALSE(_message) void(0)
#endif

//-----------------------------------------------------------------------------

#endif // __ASSERT_HPP__
