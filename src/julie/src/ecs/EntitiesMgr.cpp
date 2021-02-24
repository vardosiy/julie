#include "julie/ecs/EntitiesMgr.hpp"
#include "julie/ecs/Components.hpp"

//-----------------------------------------------------------------------------
namespace jl::ecs {
//-----------------------------------------------------------------------------

EntitiesMgr::EntitiesMgr(ComponentsMgr& _componentsMgr) noexcept
	: m_nextId(1)
	, m_componentsMgr(_componentsMgr)
{
}

EntitiesMgr::~EntitiesMgr() noexcept = default;

//-----------------------------------------------------------------------------

EntityRef EntitiesMgr::create()
{
	const EntityId newEntityId = EntityId(m_nextId);
	EntityRef entity(newEntityId, m_componentsMgr);

	m_usedIds.emplace_back(newEntityId);
	m_nextId++;

	return entity;
}

//-----------------------------------------------------------------------------

void EntitiesMgr::remove(EntityId _id) noexcept
{
	auto it = std::find_if(m_usedIds.begin(), m_usedIds.end(), [_id](const EntityId& _usedId)
	{
		return _usedId == _id;
	});
	m_usedIds.erase(it);
}

//-----------------------------------------------------------------------------

size_t EntitiesMgr::getCount() const noexcept
{
	return m_usedIds.size();
}

//-----------------------------------------------------------------------------

std::optional<EntityRef> EntitiesMgr::get(size_t _idx) noexcept
{
	if (_idx < getCount())
	{
		const EntityId id = m_usedIds[_idx];
		return EntityRef(id, m_componentsMgr);
	}
	return std::nullopt;
}

//-----------------------------------------------------------------------------

std::optional<EntityRef> EntitiesMgr::find(EntityId _id) noexcept
{
	auto it = std::find_if(m_usedIds.begin(), m_usedIds.end(), [_id](const EntityId& _usedId)
	{
		return _usedId == _id;
	});

	if (it != m_usedIds.end())
	{
		return EntityRef(*it, m_componentsMgr);
	}

	return std::nullopt;
}

//-----------------------------------------------------------------------------

EntityIterator EntitiesMgr::begin() noexcept
{
	return EntityIterator(m_usedIds.begin(), m_componentsMgr);
}

//-----------------------------------------------------------------------------

EntityIterator EntitiesMgr::end() noexcept
{
	return EntityIterator(m_usedIds.end(), m_componentsMgr);
}

//-----------------------------------------------------------------------------

ConstEntityIterator EntitiesMgr::begin() const noexcept
{
	return ConstEntityIterator(m_usedIds.begin(), m_componentsMgr);
}

//-----------------------------------------------------------------------------

ConstEntityIterator EntitiesMgr::end() const noexcept
{
	return ConstEntityIterator(m_usedIds.end(), m_componentsMgr);
}

//-----------------------------------------------------------------------------
} // namespace jl::ecs
//-----------------------------------------------------------------------------
