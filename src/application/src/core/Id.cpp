#include "core/Id.hpp"

//-----------------------------------------------------------------------------

Id::Id(ValueType _value) noexcept
	: m_value(std::move(_value))
{
}

//-----------------------------------------------------------------------------

Id::Id(const Id& _rhs) noexcept
	: m_value(_rhs.m_value)
{
}

//-----------------------------------------------------------------------------

Id::Id(Id&& _rhs) noexcept
	: m_value(std::move(_rhs.m_value))
{
}

//-----------------------------------------------------------------------------

Id& Id::operator= (const Id& _rhs) noexcept
{
	m_value = _rhs.m_value;
}

//-----------------------------------------------------------------------------

Id& Id::operator= (Id&& _rhs) noexcept
{
	m_value = std::move(_rhs.m_value);
}

//-----------------------------------------------------------------------------

bool Id::operator== (const Id& _rhs) const noexcept
{
	return getValue() == _rhs.getValue();
}

//-----------------------------------------------------------------------------

bool Id::operator!= (const Id& _rhs) const noexcept
{
	return !(*this == _rhs);
}

//-----------------------------------------------------------------------------

const Id::ValueType& Id::getValue() const noexcept
{
	return m_value;
}

//-----------------------------------------------------------------------------
