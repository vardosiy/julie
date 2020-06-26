#pragma once

#include <string>

//-----------------------------------------------------------------------------

class Id
{
public:
	using ValueType = std::string;

public:
	Id(ValueType _value) noexcept;

	Id(const Id& _rhs) noexcept = default;
	Id& operator=(const Id& _rhs) noexcept = default;

	Id(Id&& _rhs) noexcept = default;
	Id& operator=(Id&& _rhs) noexcept = default;

	bool operator==(const Id& _rhs) const noexcept;
	bool operator!=(const Id& _rhs) const noexcept;

	const ValueType& getValue() const noexcept;

private:
	ValueType m_value;
};

//-----------------------------------------------------------------------------

inline Id::Id(ValueType _value) noexcept
	: m_value(std::move(_value))
{
}

inline bool Id::operator==(const Id& _rhs) const noexcept
{
	return getValue() == _rhs.getValue();
}

inline bool Id::operator!=(const Id& _rhs) const noexcept
{
	return !(*this == _rhs);
}

inline const Id::ValueType& Id::getValue() const noexcept
{
	return m_value;
}

//-----------------------------------------------------------------------------

namespace std {

template<>
struct hash<Id>
{
	std::size_t operator() (const Id& _id) noexcept
	{
		return std::hash<Id::ValueType>()(_id.getValue());
	}
};

}

//-----------------------------------------------------------------------------
