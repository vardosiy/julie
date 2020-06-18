#pragma once

#include <string_view>
#include <array>

//-----------------------------------------------------------------------------

namespace utils {

//-----------------------------------------------------------------------------

namespace details {

template<std::size_t EnumValuesCount>
constexpr std::array<std::string_view, EnumValuesCount> getEnumNamesFromValues(std::string_view _valuesStr) noexcept;

} // namespace details

template<typename T>
constexpr std::enable_if_t<std::is_enum_v<T>, bool> isEnumValueValid(const T _value) noexcept;

template<typename T>
constexpr std::enable_if_t<std::is_enum_v<T>, T> fromString(std::string_view _str) noexcept;

} // namespace utils

//-----------------------------------------------------------------------------

template<typename T>
struct EnableBitOperations
{
};

#define ENABLE_BIT_OPERATIONS(_enum)	\
template<>								\
struct EnableBitOperations<_enum>		\
{										\
	static constexpr bool value = true;	\
};

template<typename T, typename = std::enable_if_t<EnableBitOperations<T>::value && std::is_enum_v<T>>>
constexpr T operator| (T _lhs, T _rhs);

template<typename T, typename = std::enable_if_t<EnableBitOperations<T>::value && std::is_enum_v<T>>>
constexpr T operator& (T _lhs, T _rhs);

template<typename T, typename = std::enable_if_t<EnableBitOperations<T>::value && std::is_enum_v<T>>>
constexpr T& operator|= (T& _lhs, T _rhs);

template<typename T, typename = std::enable_if_t<EnableBitOperations<T>::value && std::is_enum_v<T>>>
constexpr T operator&= (T _lhs, T _rhs);

//-----------------------------------------------------------------------------

#define DECLARE_ENUM_WITH_UTILITY(_enumName, ...)													\
enum class _enumName																				\
{																									\
	__VA_ARGS__,																					\
	Count																							\
};																									\
DECLARE_ENUM_UTILITY(_enumName, __VA_ARGS__)														\

//-----------------------------------------------------------------------------

#define DECLARE_NS_ENUM_WITH_UTILITY(_namespace, _enumName, ...)									\
namespace _namespace {																				\
enum class _enumName																				\
{																									\
	__VA_ARGS__,																					\
	Count																							\
};																									\
}																									\
DECLARE_ENUM_UTILITY(_namespace::_enumName, __VA_ARGS__)											\

//-----------------------------------------------------------------------------

#define DECLARE_ENUM_UTILITY(_enum, ...)															\
namespace utils {																					\
constexpr std::string_view toString(const _enum _value) noexcept									\
{																									\
	constexpr std::size_t k_valuesCount{ static_cast<std::size_t>(_enum::Count) };					\
	constexpr std::string_view k_valuesStr{ #__VA_ARGS__ };											\
																									\
	constexpr auto k_enumValuesNames{ details::getEnumNamesFromValues<k_valuesCount>(k_valuesStr) };\
																									\
	if (isEnumValueValid(_value))																	\
	{																								\
		return k_enumValuesNames[static_cast<std::size_t>(_value)];									\
	}																								\
	return "";																						\
}																									\
}

//-----------------------------------------------------------------------------

#include "utils/details/EnumUtils.inl"

//-----------------------------------------------------------------------------
