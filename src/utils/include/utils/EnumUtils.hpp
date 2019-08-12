#pragma once

#include <string_view>

//-----------------------------------------------------------------------------

namespace utils::enums {

//-----------------------------------------------------------------------------

#define ENUM_TO_STRING_CASE(_enum, _case) case _enum::_case: return #_case

//-----------------------------------------------------------------------------

constexpr int k_minEnumValue{ 0 };

//-----------------------------------------------------------------------------

template<typename T>
constexpr bool isValid(T _value) noexcept
{
	return static_cast<int>(_value) >= k_minEnumValue && _value < T::Count;
}

//-----------------------------------------------------------------------------

template<typename T>
constexpr T fromString(std::string_view _str)
{
	for (int i{ k_minEnumValue }; i < T::Count; ++i)
	{
		if (toString(static_cast<T>(i)) == _str)
		{
			return static_cast<T>(i);
		}
	}

	ASSERT_FALSE("Invalid enumerator name");
	return T::Count;
	//throw EnumParseException();
}

//-----------------------------------------------------------------------------

} // namespace utils::enums

//-----------------------------------------------------------------------------
