#include "data/Project.hpp"
#include "data/DataEntity.hpp"

#include "utils/Utils.hpp"

//-----------------------------------------------------------------------------

namespace data {

//-----------------------------------------------------------------------------

Project::Project() = default;
Project::~Project() = default;

//-----------------------------------------------------------------------------

void Project::addEntity(EntityPtr&& _entity) noexcept
{
	ASSERTM(
		m_entities.find(_entity->getName()) == m_entities.end(),
		"Entity with such name already exists in projects, it will be overridden"
	);
	m_entities[_entity->getName()] = std::move(_entity);
}

//-----------------------------------------------------------------------------

void Project::removeEntity(std::string_view _name) noexcept
{
	m_entities.erase(_name);
}

//-----------------------------------------------------------------------------

DataEntity* Project::findEntity(std::string_view _name) noexcept
{
	auto it = m_entities.find(_name);
	return it != m_entities.end() ? it->second.get() : nullptr;
}

//-----------------------------------------------------------------------------

const DataEntity* Project::findEntity(std::string_view _name) const noexcept
{
	auto it = m_entities.find(_name);
	return it != m_entities.end() ? it->second.get() : nullptr;
}

//-----------------------------------------------------------------------------

} // namespace data

//-----------------------------------------------------------------------------
