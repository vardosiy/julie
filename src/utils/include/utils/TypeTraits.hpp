#pragma once

#include <variant>

//-----------------------------------------------------------------------------

namespace utils {

//-----------------------------------------------------------------------------

template<typename T, typename TVariant>
struct VariantHasAlternative
{
};

template<typename T, typename ... Args>
struct VariantHasAlternative<T, std::variant<Args...>>
{
	static constexpr bool value = std::disjunction_v< std::is_same<Args, T>... >;
};

template<typename TVariant, typename T>
constexpr bool VariantHasAlternative_v = VariantHasAlternative<TVariant, T>::value;

//-----------------------------------------------------------------------------

} // namespace utils

//-----------------------------------------------------------------------------
