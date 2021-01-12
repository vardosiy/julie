#pragma once

#include "julie/ecs/Entity.hpp"

#include <string>
#include <vector>
#include <optional>

//-----------------------------------------------------------------------------

namespace jl::ecs {

//-----------------------------------------------------------------------------

class ComponentsMgr;

class EntitiesMgr
{
//-----------------------------------------------------------------------------
public:
	using Iterator = std::vector<Entity>::iterator;
	using ConstIterator = std::vector<Entity>::const_iterator;
	
//-----------------------------------------------------------------------------
	EntitiesMgr(ComponentsMgr& _componentsMgr) noexcept;
	~EntitiesMgr() noexcept;

	Entity create(std::string name);
	void remove(EntityId _id) noexcept;

	size_t getCount() const noexcept;
	std::optional<Entity> get(size_t _idx) noexcept;
	std::optional<Entity> find(EntityId _id) noexcept;

//-----------------------------------------------------------------------------
	Iterator begin() noexcept;
	Iterator end() noexcept;

	ConstIterator begin() const noexcept;
	ConstIterator end() const noexcept;

//-----------------------------------------------------------------------------
private:
	std::vector<EntityId> m_usedIds;
	EntityId::ValueType m_nextId;

	ComponentsMgr& m_componentsMgr;
};

//-----------------------------------------------------------------------------

} // namespace jl::ecs

//-----------------------------------------------------------------------------
