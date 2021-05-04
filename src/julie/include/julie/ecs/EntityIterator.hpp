#pragma once

#include "julie/ecs/EntityId.hpp"

#include <boost/iterator/iterator_adaptor.hpp>

namespace jl::ecs {
class ComponentsMgr;
}

//-----------------------------------------------------------------------------
namespace jl {
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
namespace details {
//-----------------------------------------------------------------------------

template<typename It, typename Value>
class EntityIteratorBase
	: public boost::iterator_adaptor<EntityIteratorBase<It, Value>,	// derived
									 It,							// base
									 Value,							// value
									 boost::use_default,			// traversal
									 Value>							// reference
{
public:
	EntityIteratorBase(It _it, ecs::ComponentsMgr& _componentsMgr)
		: iterator_adaptor_(_it)
		, m_componentsMgr(_componentsMgr)
	{
	}

protected:
	using EntityIteratorBase_t = EntityIteratorBase<It, Value>;

private:
	typename Value dereference() const
	{
		return Value(*this->base(), m_componentsMgr);
	}

	ecs::ComponentsMgr& m_componentsMgr;
};

//-----------------------------------------------------------------------------
} // namespace details
//-----------------------------------------------------------------------------

class EntityIterator
	: public details::EntityIteratorBase<std::vector<EntityId>::iterator, EntityRef>
{
public:
	EntityIterator(EntityIteratorBase_t::base_type _it, ecs::ComponentsMgr& _componentsMgr)
		: EntityIteratorBase_t(_it, _componentsMgr)
	{
	}
};

//-----------------------------------------------------------------------------

class ConstEntityIterator
	: public details::EntityIteratorBase<std::vector<EntityId>::const_iterator, const EntityRef>
{
public:
	ConstEntityIterator(EntityIteratorBase_t::base_type _it, ecs::ComponentsMgr& _componentsMgr)
		: EntityIteratorBase_t(_it, _componentsMgr)
	{
	}
};

//-----------------------------------------------------------------------------
} // namespace jl
//-----------------------------------------------------------------------------
