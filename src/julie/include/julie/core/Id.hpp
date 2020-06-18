#pragma once

#include <string>

//-----------------------------------------------------------------------------

class Id
{
public:
	using ValueType = std::string;

public:
	Id(ValueType _value) noexcept;

	Id(const Id& _rhs) noexcept;
	Id(Id&& _rhs) noexcept;

	Id& operator= (const Id& _rhs) noexcept;
	Id& operator= (Id&& _rhs) noexcept;

	bool operator== (const Id& _rhs) const noexcept;
	bool operator!= (const Id& _rhs) const noexcept;

	const ValueType& getValue() const noexcept;

private:
	ValueType m_value;
};

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
