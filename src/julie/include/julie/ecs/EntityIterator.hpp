#pragma once

#include "julie/ecs/EntityId.hpp"

#include <boost/iterator/iterator_adaptor.hpp>

namespace jl::ecs {
class ComponentsMgr;
}

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

namespace details {

template<typename It, typename Value>
class EntityIteratorBase
	: public boost::iterator_adaptor<EntityIteratorBase<It, Value>,	// derived
									 It,							// base
									 Value,							// value
									 boost::use_default,			// traversal
									 Value>							// reference
{
	using Adaptor = 
		typename boost::iterator_adaptor<EntityIteratorBase<It, Value>,
										 It,
										 Value,
										 boost::use_default,
										 Value>;
public:
	EntityIteratorBase(It _it, ecs::ComponentsMgr& _componentsMgr)
		: Adaptor(_it)
		, m_componentsMgr(_componentsMgr)
	{
	}

private:
	typename Adaptor::reference dereference() const
	{
		return Entity(*this->base(), m_componentsMgr);
	}

	ecs::ComponentsMgr& m_componentsMgr;
};

} // namespace details

//-----------------------------------------------------------------------------

class EntityIterator
	: public details::EntityIteratorBase<std::vector<EntityId>::iterator, EntityRef>
{
	using Base = details::EntityIteratorBase<std::vector<EntityId>::iterator, EntityRef>;

public:
	EntityIterator(Base::base_type _it, ecs::ComponentsMgr& _componentsMgr)
		: Base(_it, _componentsMgr)
	{
	}
};

//-----------------------------------------------------------------------------

class ConstEntityIterator
	: public details::EntityIteratorBase<std::vector<EntityId>::const_iterator, const EntityRef>
{
	using Base = details::EntityIteratorBase<std::vector<EntityId>::const_iterator, const EntityRef>;

public:
	ConstEntityIterator(Base::base_type _it, ecs::ComponentsMgr& _componentsMgr)
		: Base(_it, _componentsMgr)
	{
	}
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
