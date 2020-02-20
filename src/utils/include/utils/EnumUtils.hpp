#pragma once

#include <string_view>
#include <array>

//-----------------------------------------------------------------------------

namespace utils {

//-----------------------------------------------------------------------------

namespace details {

template<std::size_t EnumValuesCount>
constexpr auto getEnumNamesFromValues(std::string_view _valuesStr, std::string_view _delim) noexcept;

} // namespace details

//-----------------------------------------------------------------------------

template<typename T>
constexpr std::enable_if_t<std::is_enum_v<T>, bool> isEnumValueValid(const T _value) noexcept;

template<typename T>
constexpr std::enable_if_t<std::is_enum_v<T>, T> fromString(std::string_view _str) noexcept;

//-----------------------------------------------------------------------------

} // namespace utils

//-----------------------------------------------------------------------------

#define NAMESPACE_ENUM_WITH_UTILITY(_namespace, _enumName, ...)										\
namespace _namespace {																				\
enum class _enumName																				\
{																									\
	__VA_ARGS__,																					\
	Count																							\
};																									\
}																									\
																									\
namespace utils {																					\
namespace details {																					\
constexpr std::string_view __##_namespace##_##_enumName##_initData{ #__VA_ARGS__ };					\
}																									\
																									\
constexpr std::string_view toString(const _namespace::_enumName _value) noexcept					\
{																									\
	constexpr std::size_t k_valuesCount{ static_cast<std::size_t>(_namespace::_enumName::Count) };	\
	constexpr std::string_view k_valuesStr{ details::__##_namespace##_##_enumName##_initData };		\
																									\
	constexpr auto k_enumValuesNames{																\
		details::getEnumNamesFromValues<k_valuesCount>(k_valuesStr, ", ")							\
	};																								\
																									\
	if (isEnumValueValid(_value))																	\
	{																								\
		return k_enumValuesNames[static_cast<std::size_t>(_value)];									\
	}																								\
	return "";																						\
}																									\
} // namespace utils

//-----------------------------------------------------------------------------

#include "utils/details/EnumUtils.inl"

//-----------------------------------------------------------------------------
