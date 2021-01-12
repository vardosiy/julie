#pragma once

#include <utility>

//-----------------------------------------------------------------------------

namespace utils {

template<typename T, typename V>
class Identifier
{
public:
	using ValueType = V;

public:
	constexpr Identifier() noexcept					: m_value(static_cast<V>(0)) {}
	constexpr Identifier(const V& _val) noexcept	: m_value(_val) {}

	constexpr Identifier(const Identifier<T, V>&) = default;
	constexpr Identifier(Identifier<T, V>&&) = default;

	constexpr Identifier<T, V>& operator= (const Identifier<T, V>&) = default;
	constexpr Identifier<T, V>& operator= (Identifier<T, V>&&) = default;

	constexpr const ValueType& getValue() const noexcept { return m_value; }

	constexpr bool operator== (const Identifier<T, V>& _rhs) const noexcept { return m_value == _rhs.m_value; }
	constexpr bool operator!= (const Identifier<T, V>& _rhs) const noexcept { return !(this == _rhs); }

private:
	ValueType m_value;
};

} // namespace utils

//-----------------------------------------------------------------------------

namespace std {

template<typename T, typename V>
struct hash< utils::Identifier<T, V> >
{
	std::size_t operator() (const utils::Identifier<T, V>& _id) const noexcept
	{
		using ValueType = utils::Identifier<T, V>::ValueType;
		return std::hash<ValueType>{} (_id.getValue());
	}
};

}

//-----------------------------------------------------------------------------
