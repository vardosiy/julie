#pragma once

#include "julie/ecs/EntityId.hpp"

#include <vector>
#include <unordered_map>

//-----------------------------------------------------------------------------

namespace jl::ecs {

//-----------------------------------------------------------------------------

template<typename T>
struct ConcreteComponentContainer
{
	std::vector<T> m_container;
	std::unordered_map<EntityId, size_t> m_lookupTable; // id -> idx
	std::unordered_map<size_t, EntityId> m_reverseLookupTable; // idx -> id
};

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

template<typename ... Args>
class ComponentsContainer : private ComponentsContainerImpl<Args...>
{
public:
	template<typename T> ConcreteComponentContainer<T>&			getContainer() noexcept;
	template<typename T> const ConcreteComponentContainer<T>&	getContainer() const noexcept;
};

//-----------------------------------------------------------------------------

template<typename ... Args>
template<typename T>
inline ConcreteComponentContainer<T>& ComponentsContainer<Args...>::getContainer() noexcept
{
	static_assert(
		std::is_base_of_v< ConcreteComponentContainer<T>, std::decay_t<decltype(*this)> >,
		"ComponentsContainer doesn't containe components of specified type"
	);
	return static_cast<ConcreteComponentContainer<T>&>(*this);
}

template<typename ... Args>
template<typename T>
inline const ConcreteComponentContainer<T>& ComponentsContainer<Args...>::getContainer() const noexcept
{
	static_assert(
		std::is_base_of_v< ConcreteComponentContainer<T>, std::decay_t<decltype(*this)> >,
		"ComponentsContainer doesn't containe components of specified type"
	);
	return static_cast<const ConcreteComponentContainer<T>&>(*this);
}

//-----------------------------------------------------------------------------

} // namespace jl::ecs

//-----------------------------------------------------------------------------
