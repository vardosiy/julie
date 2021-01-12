#include "julie/ecs/EntitiesMgr.hpp"
#include "julie/ecs/Components.hpp"

//-----------------------------------------------------------------------------

namespace jl::ecs {

//-----------------------------------------------------------------------------

EntitiesMgr::EntitiesMgr(ComponentsMgr& _componentsMgr) noexcept
	: m_nextId(0)
	, m_componentsMgr(_componentsMgr)
{
}

EntitiesMgr::~EntitiesMgr() noexcept = default;

//-----------------------------------------------------------------------------

Entity EntitiesMgr::create(std::string _name)
{
	const EntityId newEntityId = EntityId(m_nextId);

	Entity entity(newEntityId, m_componentsMgr);
	entity.addComponent<TagComponent>(std::move(_name));
	entity.addComponent<TransformComponent>();

	m_usedIds.emplace_back(newEntityId);
	m_nextId++;

	return entity;
}

//-----------------------------------------------------------------------------

std::optional<Entity> EntitiesMgr::find(EntityId _id) noexcept
{
	auto it = std::find_if(m_usedIds.begin(), m_usedIds.end(), [_id](const EntityId& _usedId)
	{
		return _usedId == _id;
	});

	if (it != m_usedIds.end())
	{
		return Entity(*it, m_componentsMgr);
	}

	return std::nullopt;
}

//-----------------------------------------------------------------------------

void EntitiesMgr::remove(EntityId _id) noexcept
{
	auto removeIt = std::remove_if(m_usedIds.begin(), m_usedIds.end(), [_id](const EntityId& _usedId)
	{
		return _usedId == _id;
	});
	m_usedIds.erase(removeIt);
}

//-----------------------------------------------------------------------------

size_t EntitiesMgr::getCount() const noexcept
{
	return m_usedIds.size();
}

std::optional<Entity> EntitiesMgr::get(size_t _idx) noexcept
{
	if (_idx < getCount())
	{
		const EntityId id = m_usedIds[_idx];
		return Entity(id, m_componentsMgr);
	}
	return std::nullopt;
}

//-----------------------------------------------------------------------------

//EntitiesMgr::Iterator EntitiesMgr::begin() noexcept
//{
//	return m_entities.begin();
//}
//
////-----------------------------------------------------------------------------
//
//EntitiesMgr::Iterator EntitiesMgr::end() noexcept
//{
//	return m_entities.end();
//}
//
////-----------------------------------------------------------------------------
//
//EntitiesMgr::ConstIterator EntitiesMgr::begin() const noexcept
//{
//	return m_entities.begin();
//}
//
////-----------------------------------------------------------------------------
//
//EntitiesMgr::ConstIterator EntitiesMgr::end() const noexcept
//{
//	return m_entities.end();
//}

//-----------------------------------------------------------------------------

} // namespace jl::ecs

//-----------------------------------------------------------------------------
