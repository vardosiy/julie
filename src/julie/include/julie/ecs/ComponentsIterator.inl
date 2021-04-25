#include "ComponentsIterator.hpp"

//-----------------------------------------------------------------------------
namespace jl::ecs {
//-----------------------------------------------------------------------------

template<typename ... Args>
inline ComponentIterator<Args...>::ComponentIterator(ComponentsMgr& _componentsMgr) noexcept
	: m_idx(0)
	, m_componentsMgr(&_componentsMgr)
{
}

//-----------------------------------------------------------------------------

template<typename ... Args>
inline bool ComponentIterator<Args...>::isValid() const noexcept
{
	const size_t size = getFirstContainerSize<Args...>();
	return m_idx < size;
}

//-----------------------------------------------------------------------------

template<typename ... Args>
inline typename ComponentIterator<Args...>::ComponentsRefs ComponentIterator<Args...>::dereference() const
{
	return dereferenceImpl(m_value, std::make_index_sequence<sizeof...(Args)>{});
}

//-----------------------------------------------------------------------------

template<typename ... Args>
inline void ComponentIterator<Args...>::increment() noexcept
{
	++m_idx;

	const size_t size = getFirstContainerSize<Args...>();
	while (m_idx < size)
	{
		if (collectComponents<Args...>(m_idx))
			break;

		++m_idx;
	}
}

//-----------------------------------------------------------------------------

template<typename ... Args>
inline bool ComponentIterator<Args...>::equal(const ComponentIterator& _rhs) const noexcept
{
	return m_idx == _rhs.m_idx && m_componentsMgr == _rhs.m_componentsMgr;
}

//-----------------------------------------------------------------------------

template<typename ... Args>
template<typename T, typename ... Tail>
inline bool ComponentIterator<Args...>::collectComponents(size_t _idx) const noexcept
{
	ConcreteComponentContainer<T>& container = m_componentsMgr->getContainer<T>();
	std::get<T*>(m_value) = &container.getByIdx(_idx);

	EntityId id = container.m_reverseLookupTable[_idx];
	return collectComponentsInternal<Tail...>(id);
}

//-----------------------------------------------------------------------------

template<typename ... Args>
template<typename T, typename ... Tail>
inline bool ComponentIterator<Args...>::collectComponentsInternal(EntityId _id) const noexcept
{
	T* cmpnt = m_componentsMgr->getContainer<T>().findById(_id);
	std::get<T*>(m_value) = cmpnt;

	const bool shouldContinue = cmpnt != nullptr;
	return shouldContinue ? collectComponentsInternal<Tail...>(_id) : false;
}

//-----------------------------------------------------------------------------

template<typename ... Args>
template<typename T>
inline void ComponentIterator<Args...>::collectComponentsInternal(EntityId _id) const noexcept
{
	T* cmpnt = m_componentsMgr->getContainer<T>().findById(_id);
	std::get<T*>(m_value) = cmpnt;
	return cmpnt != nullptr;
}

//-----------------------------------------------------------------------------

template<typename ... Args>
template<typename T, typename ...>
inline size_t ComponentIterator<Args...>::getFirstContainerSize() const noexcept
{
	return m_componentsMgr->getContainer<T>().getCount();
}

//-----------------------------------------------------------------------------

template<typename ... Args>
template<size_t ... I>
inline typename ComponentIterator<Args...>::ComponentsRefs ComponentIterator<Args...>::dereferenceImpl(
	const ComponentsPtrs& _ptrs,
	std::index_sequence<I...>
)
{
	return { (*std::get<I>(_tuple))... };
}

//-----------------------------------------------------------------------------
} // namespace jl::ecs
//-----------------------------------------------------------------------------
