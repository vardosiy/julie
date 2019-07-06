#ifndef __ASSERT_HPP__
#define __ASSERT_HPP__

//-----------------------------------------------------------------------------

void assertion(const char * _expr, const char * _file, int _line, const char * _message);

//-----------------------------------------------------------------------------

#define ASSERT_IMPL(_expr, _message)										\
do {																		\
	if (!(_expr))															\
	{																		\
		assertion(#_expr, __FILE__, __LINE__, _message);					\
	}																		\
} while(false)

//-----------------------------------------------------------------------------

#if defined(_DEBUG)
#	define ASSERT(_expr, _message) ASSERT_IMPL(_expr, _message)
#	define ASSERT_FALSE(_message) ASSERT_IMPL(false, _message)
#else
#	define ASSERT(_expr) void(0)
#	define ASSERT_FALSE(_message) void(0)
#endif

//-----------------------------------------------------------------------------

#endif // __ASSERT_HPP__
