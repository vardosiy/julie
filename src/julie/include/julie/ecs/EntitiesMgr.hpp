#pragma once

#include "julie/ecs/Entity.hpp"
#include "julie/ecs/EntityIterator.hpp"

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
	explicit EntitiesMgr(ComponentsMgr& _componentsMgr) noexcept;
	~EntitiesMgr() noexcept;

	EntityRef create();
	void remove(EntityId _id) noexcept;

	size_t getCount() const noexcept;
	std::optional<EntityRef> get(size_t _idx) noexcept;
	std::optional<EntityRef> find(EntityId _id) noexcept;

//-----------------------------------------------------------------------------
	EntityIterator begin() noexcept;
	EntityIterator end() noexcept;

	ConstEntityIterator begin() const noexcept;
	ConstEntityIterator end() const noexcept;

//-----------------------------------------------------------------------------
private:
	std::vector<EntityId> m_usedIds;
	EntityId::ValueType m_nextId;

	ComponentsMgr& m_componentsMgr;
};

//-----------------------------------------------------------------------------

} // namespace jl::ecs

//-----------------------------------------------------------------------------
