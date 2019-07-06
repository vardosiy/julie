#ifndef __ENUM_UTILS_HPP__
#define __ENUM_UTILS_HPP__

//-----------------------------------------------------------------------------

namespace enums::utils {

//-----------------------------------------------------------------------------

#define ENUM_TO_STRING_CASE(_case) case _case: return #_case

//-----------------------------------------------------------------------------

template<typename T>
constexpr typename T::Enum fromString(std::string_view _str)
{
	for (int i{ 0 }; i < T::Count; ++i)
	{
		if (T::toString(static_cast<T::Enum>(i)) == _str)
		{
			return static_cast<T::Enum>(i);
		}
	}

	// throw std::runtime_error("Invalid enumerator name");
	ASSERT_FALSE("Invalid enumerator name");
}

//-----------------------------------------------------------------------------

} // namespace enums::utils

//-----------------------------------------------------------------------------

#endif // __ENUM_UTILS_HPP__
