#ifndef __ENUM_UTILS_HPP__
#define __ENUM_UTILS_HPP__

//-----------------------------------------------------------------------------

namespace enum_utils {

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
	assert(!"Invalid enumerator name");
}

//-----------------------------------------------------------------------------

} // namespace utils

//-----------------------------------------------------------------------------

#endif // __ENUM_UTILS_HPP__
