#include "ComponentsIterator.hpp"

//-----------------------------------------------------------------------------
namespace jl::ecs {
//-----------------------------------------------------------------------------

template<typename ... Args>
inline ComponentIterator<Args...>::ComponentIterator(ComponentsMgr& _componentsMgr) noexcept
	: m_idx(0)
	, m_componentsMgr(&_componentsMgr)
{
	if (isValid() && !collectComponents<Args...>())
	{
		increment();
	}
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
inline void ComponentIterator<Args...>::increment() noexcept
{
	++m_idx;

	const size_t size = getFirstContainerSize<Args...>();
	while (m_idx < size)
	{
		if (collectComponents<Args...>())
			break;

		++m_idx;
	}
}

//-----------------------------------------------------------------------------

template<typename ... Args>
inline std::tuple<Args&...> ComponentIterator<Args...>::dereference() const noexcept
{
	return std::tuple<Args&...>{ (*std::get<Args*>(m_value))... };
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
inline bool ComponentIterator<Args...>::collectComponents() noexcept
{
	ConcreteComponentContainer<T>& container = m_componentsMgr->getContainer<T>();
	std::get<T*>(m_value) = &container.getByIdx(m_idx);

	EntityId id = container.m_reverseLookupTable[m_idx];
	return ( ... && findComponent(id, std::get<Tail*>(m_value)) );
}

//-----------------------------------------------------------------------------

template<typename ... Args>
template<typename T>
inline bool ComponentIterator<Args...>::findComponent(EntityId _id, T*& _cmpnt) noexcept
{
	T* cmpnt = m_componentsMgr->getContainer<T>().findById(_id);
	_cmpnt = cmpnt;
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
} // namespace jl::ecs
//-----------------------------------------------------------------------------
