#include "data/DataEntity.hpp"

//-----------------------------------------------------------------------------

namespace data {

//-----------------------------------------------------------------------------

DataEntity::DataEntity(std::string _name)
	: m_name(std::move(_name))
{
}

//-----------------------------------------------------------------------------

DataEntity::~DataEntity() = default;

//-----------------------------------------------------------------------------

const std::string& DataEntity::getName() const noexcept
{
	return m_name;
}

//-----------------------------------------------------------------------------

void DataEntity::setName(std::string _name) noexcept
{
	m_name = std::move(_name);
}

//-----------------------------------------------------------------------------

} // namespace data

//-----------------------------------------------------------------------------
