#pragma once

#include "utils/Assert.hpp"

#include <string_view>
#include <array>

//-----------------------------------------------------------------------------

namespace utils {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

constexpr int k_minEnumValue{ 0 };

template<std::size_t EnumValuesCount>
constexpr auto getEnumNamesFromValues(std::string_view _valuesStr, std::string_view _delim) noexcept
{
	std::array<std::string_view, EnumValuesCount> result = { "" };

	std::size_t tokenStart{ 0 };
	for (std::size_t i{ 0 }; i < EnumValuesCount; ++i)
	{
		const std::size_t tokenEnd = _valuesStr.find(_delim, tokenStart);
		result[i] = _valuesStr.substr(tokenStart, tokenEnd - tokenStart);
		tokenStart = tokenEnd + _delim.size();
	}

	return result;
}

//-----------------------------------------------------------------------------

} // namespace details

//-----------------------------------------------------------------------------

template<typename T>
constexpr std::enable_if_t<std::is_enum_v<T>, bool> isEnumValueValid(const T _value) noexcept
{
	return
		static_cast<int>(_value) >= details::k_minEnumValue &&
		static_cast<int>(_value) < static_cast<int>(T::Count);
}

//-----------------------------------------------------------------------------

template<typename T>
constexpr std::enable_if_t<std::is_enum_v<T>, T> fromString(std::string_view _str) noexcept
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

} // namespace utils

//-----------------------------------------------------------------------------
