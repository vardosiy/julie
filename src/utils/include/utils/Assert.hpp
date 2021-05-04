#pragma once

#include "utils/LogDefs.hpp"

#include <fmt/format.h>

#include <string_view>

//-----------------------------------------------------------------------------
namespace utils {
//-----------------------------------------------------------------------------

struct AssertData
{
	const char* expr;
	const char* file;
	int line;
};

inline void assertImpl(AssertData _data)
{
	LOG_ASSERT("\"{}\" ({}, line {})", _data.expr, _data.file, _data.line);
	__debugbreak();
}

template<typename ... Args>
inline void assertMessageImpl(AssertData _data, std::string_view _message, Args&& ... _args)
{
	std::string message = fmt::format(_message.data(), std::forward<Args>(_args)...);
	LOG_ASSERT("\"{}\" {} ({}, line {})", _data.expr, message, _data.file, _data.line);
	__debugbreak();
}

//-----------------------------------------------------------------------------
} // namespace utils
//-----------------------------------------------------------------------------

#define CREATE_ASSERT_DATA(_expr) utils::AssertData{ _expr, __FILE__, __LINE__ }

#define ASSERTM_IMPL(_expr, _message, ...) \
do { if (!(_expr)) utils::assertMessageImpl(CREATE_ASSERT_DATA(#_expr), _message, __VA_ARGS__); } while(false)

#define ASSERT_IMPL(_expr) \
do { if (!(_expr)) utils::assertImpl(CREATE_ASSERT_DATA(#_expr)); } while(false)

//-----------------------------------------------------------------------------

#if defined(_DEBUG)
#	define ASSERTM(_expr, _message, ...) ASSERTM_IMPL(_expr, _message, __VA_ARGS__)
#	define ASSERT(_expr) ASSERT_IMPL(_expr)
#else
#	define ASSERTM(_expr, _message, ...) void(0)
#	define ASSERT(_expr) void(0)
#endif

//-----------------------------------------------------------------------------
