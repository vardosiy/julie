#pragma once

#include <string_view>
#include <array>

//-----------------------------------------------------------------------------

namespace utils {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template<std::size_t EnumValuesCount>
constexpr std::array<std::string_view, EnumValuesCount> getEnumNamesFromValues(std::string_view _valuesStr) noexcept
{
	constexpr std::string_view delim = ", ";

	std::array<std::string_view, EnumValuesCount> result;

	std::size_t tokenStart{ 0 };
	for (std::size_t i{ 0 }; i < EnumValuesCount; ++i)
	{
		const std::size_t tokenEnd{ _valuesStr.find(delim, tokenStart) };
		result[i] = _valuesStr.substr(tokenStart, tokenEnd - tokenStart);
		tokenStart = tokenEnd + delim.size();
	}

	return result;
}

template<typename T>
constexpr std::enable_if_t<std::is_enum_v<T>, bool> isValid(const T _value) noexcept
{
	return static_cast<int>(_value) >= 0 && static_cast<int>(_value) < static_cast<int>(T::Count);
}

template<typename T>
constexpr std::underlying_type_t<T> toUnderlying(T _val)
{
	return static_cast<std::underlying_type_t<T>>(_val);
}

//-----------------------------------------------------------------------------

} // namespace details

//-----------------------------------------------------------------------------

template<typename T>
constexpr std::enable_if_t<std::is_enum_v<T>, T> fromString(std::string_view _str) noexcept
{
	constexpr int count{ static_cast<int>(T::Count) };
	for (int i{ 0 }; i < count; ++i)
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
constexpr T& operator&= (T& _lhs, T _rhs)
{
	_lhs = _lhs & _rhs;
	return _lhs;
}

//-----------------------------------------------------------------------------
