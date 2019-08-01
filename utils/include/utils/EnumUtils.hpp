#pragma once

#include <string_view>

//-----------------------------------------------------------------------------

namespace utils::enums {

//-----------------------------------------------------------------------------

constexpr int k_minEnumValue{ 0 };

//-----------------------------------------------------------------------------

template<typename T>
class CheckableEnum
{
public:
	static constexpr bool isValid(typename T::Enum _value) noexcept
	{
		return _value >= k_minEnumValue && _value < T::Count;
	}
};

//-----------------------------------------------------------------------------

#define ENUM_TO_STRING_CASE(_case) case _case: return #_case

//-----------------------------------------------------------------------------

template<typename T>
constexpr typename T::Enum fromString(std::string_view _str)
{
	for (int i{ k_minEnumValue }; i < T::Count; ++i)
	{
		if (T::toString(static_cast<typename T::Enum>(i)) == _str)
		{
			return static_cast<typename T::Enum>(i);
		}
	}

	//throw EnumParseException();
	ASSERT_FALSE("Invalid enumerator name");
}

//-----------------------------------------------------------------------------

} // namespace utils::enums

//-----------------------------------------------------------------------------
