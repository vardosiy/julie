#pragma once

#include <string_view>
#include <array>

//-----------------------------------------------------------------------------

namespace utils {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

constexpr int k_minEnumValue{ 0 };

template<std::size_t EnumValuesCount>
constexpr std::array<std::string_view, EnumValuesCount> getEnumNamesFromValues(std::string_view _valuesStr) noexcept
{
	std::array<std::string_view, EnumValuesCount> result = { "" };

	constexpr std::string_view delim = ", ";

	std::size_t tokenStart{ 0 };
	for (std::size_t i{ 0 }; i < EnumValuesCount; ++i)
	{
		const std::size_t tokenEnd = _valuesStr.find(delim, tokenStart);
		result[i] = _valuesStr.substr(tokenStart, tokenEnd - tokenStart);
		tokenStart = tokenEnd + delim.size();
	}

	return result;
}

template<typename T, typename = std::enable_if_t<std::is_enum_v<T>>>
constexpr std::underlying_type_t<T> toUnderlying(T _val)
{
	return static_cast<std::underlying_type_t<T>>(_val);
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

template<typename T, typename>
constexpr T operator| (T _lhs, T _rhs)
{
	return static_cast<T>(utils::details::toUnderlying(_lhs) | utils::details::toUnderlying(_rhs));
}

template<typename T, typename>
constexpr T operator& (T _lhs, T _rhs)
{
	return static_cast<T>(utils::details::toUnderlying(_lhs) & utils::details::toUnderlying(_rhs));
}

template<typename T, typename>
constexpr T& operator|= (T& _lhs, T _rhs)
{
	_lhs = _lhs | _rhs;
	return _lhs;
}

template<typename T, typename>
constexpr T operator&= (T _lhs, T _rhs)
{
	_lhs = _lhs & _rhs;
	return _lhs;
}

//-----------------------------------------------------------------------------
