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

//-----------------------------------------------------------------------------

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

//-----------------------------------------------------------------------------

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
} // namespace jl::ecs
//-----------------------------------------------------------------------------

#include "ComponentsContainerRef.inl"
