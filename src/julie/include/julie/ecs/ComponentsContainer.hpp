#pragma once

#include "julie/ecs/EntityId.hpp"

#include <vector>
#include <unordered_map>

//-----------------------------------------------------------------------------
namespace jl::ecs {
//-----------------------------------------------------------------------------

template<typename T>
class ConcreteComponentContainer
{
public:
	size_t getCount() const noexcept;

	T& getByIdx(size_t _idx) noexcept;
	const T& getByIdx(size_t _idx) const noexcept;

	T* findById(EntityId _id) noexcept;
	const T* findById(EntityId _id) const noexcept;

	std::vector<T> m_container;
	std::unordered_map<EntityId, size_t> m_lookupTable; // id -> idx
	std::unordered_map<size_t, EntityId> m_reverseLookupTable; // idx -> id
};

//-----------------------------------------------------------------------------

template<typename T, typename ... Args>
class ComponentsContainerImpl
	: public ConcreteComponentContainer<T>
	, public ComponentsContainerImpl<Args...>
{
};

template<typename T>
class ComponentsContainerImpl<T> : public ConcreteComponentContainer<T>
{
};

//-----------------------------------------------------------------------------

template<typename ... Args>
class ComponentsContainer : private ComponentsContainerImpl<Args...>
{
public:
	template<typename T> ConcreteComponentContainer<T>&			getContainer() noexcept;
	template<typename T> const ConcreteComponentContainer<T>&	getContainer() const noexcept;
};

//-----------------------------------------------------------------------------
} // namespace jl::ecs
//-----------------------------------------------------------------------------

#include "ComponentsContainer.inl"
