#pragma once

#include "utils/Assert.hpp"

#include <fmt/format.h>
#include <string_view>
#include <array>

//-----------------------------------------------------------------------------

namespace details {

constexpr int k_minEnumValue{ 0 };

template<typename T>
constexpr auto getEnumNamesFromValues(std::string_view _string, std::string_view _delimiter)
{
	std::array<std::string_view, static_cast<int>(T::Count)> result;

	int tokenStart = 0;
	for (int i{ 0 }; i < static_cast<int>(T::Count); ++i)
	{
		int tokenEnd = _string.find(_delimiter, tokenStart);
		if (tokenEnd == std::string_view::npos)
		{
			tokenEnd = _string.size();
		}

		result[i] = _string.substr(tokenStart, tokenEnd);
		tokenStart = tokenEnd + _delimiter.size();
	}

	return result;
}

} // namespace details

//-----------------------------------------------------------------------------

template<typename T>
constexpr std::enable_if_t<std::is_enum_v<T>, bool> isEnumValueValid(T _value) noexcept
{
	return static_cast<int>(_value) >= details::k_minEnumValue && _value < T::Count;
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

#define NAMESPACE_ENUM_WITH_UTILITY(_namespace, _enumName, ...)									\
namespace _namespace {																			\
enum class _enumName																			\
{																								\
	__VA_ARGS__,																				\
	Count																						\
};																								\
}																								\
																								\
namespace details {																				\
constexpr std::string_view __##_enumName##_initData = #__VA_ARGS__;								\
}																								\
																								\
constexpr std::string_view toString(_enumName _value)											\
{																								\
	using EnumValuesNames = std::array<std::string_view, static_cast<int>(_enumName::Count)>;	\
	constexpr EnumValuesNames k_enumValuesNames =												\
		details::getEnumNamesFromValues<_enumName>(details::__##_enumName##_initData, ", ");	\
																								\
	if (isEnumValueValid(_value))																\
	{																							\
		return k_enumValuesNames[static_cast<int>(_value)];										\
	}																							\
	ASSERT(0);																					\
	return "";																					\
}																								\
																								\
ENUM_NAME_GETTER(_enumName)

//-----------------------------------------------------------------------------

template<typename T>
constexpr std::enable_if_t<std::is_enum_v<T>, T> fromString(std::string_view _str)
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
}

//-----------------------------------------------------------------------------
