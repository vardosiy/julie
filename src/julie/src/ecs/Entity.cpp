#include "julie/ecs/Entity.hpp"

//-----------------------------------------------------------------------------
namespace jl {
//-----------------------------------------------------------------------------

EntityRef::EntityRef(EntityId _id, ecs::ComponentsMgr& _componentsMgr) noexcept
	: m_id(_id)
	, m_componentsMgr(&_componentsMgr)
{
}

//-----------------------------------------------------------------------------

EntityId EntityRef::getId() const  noexcept
{
	return m_id;
}

//-----------------------------------------------------------------------------
} // namespace jl
//-----------------------------------------------------------------------------
