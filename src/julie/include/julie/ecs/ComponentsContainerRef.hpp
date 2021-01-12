#pragma once

#include "julie/ecs/EntityId.hpp"
#include "julie/ecs/ComponentsContainer.hpp"

#include <vector>
#include <unordered_map>

//-----------------------------------------------------------------------------

namespace jl::ecs {

//-----------------------------------------------------------------------------

template<typename T>
class ConcreteComponentContainerRef
{
public:
	ConcreteComponentContainerRef(ConcreteComponentContainer<T>& _base) noexcept;

	std::vector<T>& m_containerRef;
	std::unordered_map<EntityId, size_t>& m_lookupTableRef;
	std::unordered_map<size_t, EntityId>& m_reverseLookupTableRef;
};

template<typename T, typename ... Args>
class ComponentsContainerRefImpl
	: public ConcreteComponentContainerRef<T>
	, public ComponentsContainerRefImpl<Args...>
{
public:
	template<typename ... ArgsBase>
	ComponentsContainerRefImpl(ComponentsContainer<ArgsBase...>& _base) noexcept;
};

template<typename T>
class ComponentsContainerRefImpl<T> : public ConcreteComponentContainerRef<T>
{
public:
	template<typename ... ArgsBase>
	ComponentsContainerRefImpl(ComponentsContainer<ArgsBase...>& _base) noexcept;
};

template<typename ... Args>
class ComponentsContainerRef : private ComponentsContainerRefImpl<Args...>
{
public:
	template<typename ... ArgsBase>
	ComponentsContainerRef(ComponentsContainer<ArgsBase...>& _base) noexcept;

	template<typename T> ConcreteComponentContainerRef<T>&			getContainer() noexcept;
	template<typename T> const ConcreteComponentContainerRef<T>&	getContainer() const noexcept;
};

//-----------------------------------------------------------------------------

template<typename T>
ConcreteComponentContainerRef<T>::ConcreteComponentContainerRef(ConcreteComponentContainer<T>& _base) noexcept
	: m_containerRef(_base.m_container)
	, m_lookupTableRef(_base.m_lookupTable)
	, m_reverseLookupTableRef(_base.m_reverseLookupTable)
{
}

template<typename T, typename ... Args>
template<typename ... ArgsBase>
ComponentsContainerRefImpl<T, Args...>::ComponentsContainerRefImpl(ComponentsContainer<ArgsBase...>& _base) noexcept
	: ConcreteComponentContainerRef<T>(_base.getContainer<T>())
	, ComponentsContainerRefImpl<Args...>(_base)
{
}

template<typename T>
template<typename ... ArgsBase>
ComponentsContainerRefImpl<T>::ComponentsContainerRefImpl(ComponentsContainer<ArgsBase...>& _base) noexcept
	: ConcreteComponentContainerRef<T>(_base.getContainer<T>())
{
}

//-----------------------------------------------------------------------------

template<typename ... Args>
template<typename ... ArgsBase>
inline ComponentsContainerRef<Args...>::ComponentsContainerRef(ComponentsContainer<ArgsBase...>& _base) noexcept
	: ComponentsContainerRefImpl<Args...>(_base)
{
}

template<typename ... Args>
template<typename T>
inline ConcreteComponentContainerRef<T>& ComponentsContainerRef<Args...>::getContainer() noexcept
{
	using test = decltype(*this);
	static_assert(
		std::is_base_of_v< ConcreteComponentContainerRef<T>, std::decay_t<decltype(*this)> >,
		"ComponentsContainer doesn't containe components of specified type"
	);
	return static_cast<ConcreteComponentContainerRef<T>&>(*this);
}

template<typename ... Args>
template<typename T>
inline const ConcreteComponentContainerRef<T>& ComponentsContainerRef<Args...>::getContainer() const noexcept
{
	static_assert(
		std::is_base_of_v< ConcreteComponentContainerRef<T>, std::decay_t<decltype(*this)> >,
		"ComponentsContainer doesn't containe components of specified type"
	);
	return static_cast<const ConcreteComponentContainerRef<T>&>(*this);
}

//-----------------------------------------------------------------------------

} // namespace jl::ecs

//-----------------------------------------------------------------------------
