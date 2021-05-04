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

template<int N1, int N2>
struct IsGreater
{
	static constexpr bool value = N1 > N2;
};

template<int N1, int N2>
constexpr bool IsGreater_v = IsGreater<N1, N2>::value;

//-----------------------------------------------------------------------------
} // namespace utils
//-----------------------------------------------------------------------------
