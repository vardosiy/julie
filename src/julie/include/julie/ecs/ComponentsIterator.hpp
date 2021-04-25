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

public:
	explicit ComponentIterator(ComponentsMgr& _componentsMgr) noexcept;

	bool isValid() const noexcept;

private:
	using ComponentsPtrs = std::tuple<Args*...>;
	using ComponentsRefs = std::tuple<Args&...>; // check why iterator_facade_::reference doesn't work

	ComponentsRefs dereference() const;
	void increment() noexcept;
	bool equal(const ComponentIterator& _rhs) const noexcept;

	template<typename T, typename ... Tail>
	bool collectComponents(size_t _idx) const noexcept;

	template<typename T, typename ... Tail>
	bool collectComponentsInternal(EntityId _id) const noexcept;
	template<typename T>
	void collectComponentsInternal(EntityId _id) const noexcept;

	template<typename T, typename ...>
	size_t getFirstContainerSize() const noexcept;

	template<size_t ... I>
	static ComponentsRefs dereferenceImpl(const ComponentsPtrs& _ptrs, std::index_sequence<I...>);

	size_t m_idx;
	ComponentsPtrs m_value;
	ComponentsMgr* m_componentsMgr;
};

//-----------------------------------------------------------------------------
} // namespace jl::ecs
//-----------------------------------------------------------------------------

#include "julie/ecs/ComponentsIterator.inl"
