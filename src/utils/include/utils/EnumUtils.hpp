#pragma once

#include "utils/exceptions/ParseErrorException.hpp"

#include <fmt/format.h>

#include <string_view>

//-----------------------------------------------------------------------------

namespace details {
constexpr int k_minEnumValue{ 0 };
}

//-----------------------------------------------------------------------------

template<typename T>
constexpr std::enable_if_t<std::is_enum_v<T>, bool> isEnumValueValid(T _value) noexcept
{
	return static_cast<int>(_value) >= details::k_minEnumValue && _value < T::Count;
}

//-----------------------------------------------------------------------------

template<typename T>
T fromString(std::string_view _str)
{
	constexpr int count{ static_cast<int>(T::Count) };
	for (int i{ details::k_minEnumValue }; i < count; ++i)
	{
		const T current{ static_cast<T>(i) };
		if (toString(current) == _str)
		{
			return current;
		}
	}

	return T::Count;
	//throw ParseErrorException(
	//	fmt::format("Invalid enumerator: {}, while parsing enum {}", _str.data(), getEnumName<T>().data())
	//);
}

//-----------------------------------------------------------------------------

template<typename T>
constexpr std::string_view getEnumName() noexcept
{
	return "";
}

#define ENUM_NAME_GETTER(_enum)								\
template<>													\
constexpr std::string_view getEnumName<_enum>() noexcept	\
{															\
	return #_enum;											\
}

//-----------------------------------------------------------------------------

#define ENUM_TO_STRING_CASE(_enum, _case) case _enum::_case: return #_case

//-----------------------------------------------------------------------------
