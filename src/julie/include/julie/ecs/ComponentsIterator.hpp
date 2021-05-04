#pragma once

#include "julie/ecs/ComponentsMgr.hpp"

#include <boost/iterator/iterator_facade.hpp>

#include <tuple>

//-----------------------------------------------------------------------------
namespace jl::ecs {
//-----------------------------------------------------------------------------

class ComponentsMgr;

template<typename ... Args>
class ComponentIterator
	: public boost::iterator_facade<ComponentIterator<Args...>,		// derived
									std::tuple<Args&...>,			// value
									boost::forward_traversal_tag,	// category
									std::tuple<Args&...>>			// reference
{
	friend class boost::iterator_core_access;

//-----------------------------------------------------------------------------
public:
	explicit ComponentIterator(ComponentsMgr& _componentsMgr) noexcept;

	bool isValid() const noexcept;

//-----------------------------------------------------------------------------
private:
	void increment() noexcept;
	std::tuple<Args&...> dereference() const noexcept;
	bool equal(const ComponentIterator& _rhs) const noexcept;

//-----------------------------------------------------------------------------
	template<typename T, typename ... Tail>
	bool collectComponents() noexcept;

	template<typename T>
	bool findComponent(EntityId _id, T*& _cmpnt) noexcept;

	template<typename T, typename ...>
	size_t getFirstContainerSize() const noexcept;

//-----------------------------------------------------------------------------
	size_t m_idx;
	std::tuple<Args*...> m_value;
	ComponentsMgr* m_componentsMgr;
};

//-----------------------------------------------------------------------------
} // namespace jl::ecs
//-----------------------------------------------------------------------------

#include "julie/ecs/ComponentsIterator.inl"
