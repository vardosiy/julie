#ifndef __STRING_CONVERTER_HPP__
#define __STRING_CONVERTER_HPP__

//-----------------------------------------------------------------------------

#define TO_STRING_CASE(_case) case _case: return #_case

//-----------------------------------------------------------------------------

namespace utils {

template<typename T>
typename T::Enum enumFromString(std::string_view _str) 
{
	for (int i{ 0 }; i < T::Count; ++i)
	{
		if (T::toString(static_cast<T::Enum>(i)) == _str)
		{
			return static_cast<T::Enum>(i);
		}
	}

	assert(!"Invalid enumerator name");
}

} // namespace utils

//-----------------------------------------------------------------------------

#endif // __STRING_CONVERTER_HPP__
