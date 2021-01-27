#pragma once

#include "julie/ecs/EntityId.hpp"
#include "julie/ecs/Components.hpp"
#include "julie/ecs/ComponentsContainer.hpp"
#include "julie/ecs/ComponentsContainerRef.hpp"

#include "utils/TypeTraits.hpp"

//-----------------------------------------------------------------------------

namespace jl::ecs {

//-----------------------------------------------------------------------------

class ComponentsMgr
{
public:
	template<typename T, typename ... Args>
	T& emplace(EntityId _id, Args&& ... _args);

	template<typename T>
	T* get(EntityId _id) noexcept;

	template<typename T>
	const T* get(EntityId _id) const noexcept;

	template<typename T>
	void remove(EntityId _id) noexcept;

	template<typename T>
	ConcreteComponentContainerRef<T> view() noexcept;

	template<typename ... Args, typename = std::enable_if_t<utils::IsGreater_v<sizeof...(Args), 1>> >
	ComponentsContainerRef<Args...> view() noexcept;

private:
	using AllComponentsContainer = ComponentsContainer<TagComponent,
													   TransformComponent,
													   ModelComponent,
													   RenderComponent,
													   LightSourceComponent>;

	AllComponentsContainer m_componentsContainer;
};

//-----------------------------------------------------------------------------

template<typename T, typename ... Args>
inline T& ComponentsMgr::emplace(EntityId _id, Args&& ... _args)
{
	ConcreteComponentContainer<T>& concreteContainer = m_componentsContainer.getContainer<T>();

	concreteContainer.m_container.emplace_back(std::forward<Args>(_args)...);
	const size_t addedIdx = concreteContainer.m_container.size() - 1;

	concreteContainer.m_lookupTable[_id] = addedIdx;
	concreteContainer.m_reverseLookupTable[addedIdx] = _id;

	return concreteContainer.m_container.back();
}

//-----------------------------------------------------------------------------

template<typename T>
inline T* ComponentsMgr::get(EntityId _id) noexcept
{
	ConcreteComponentContainer<T>& concreteContainer = m_componentsContainer.getContainer<T>();

	T* result = nullptr;

	auto it = concreteContainer.m_lookupTable.find(_id);
	if (it != concreteContainer.m_lookupTable.end())
	{
		const size_t idx = it->second;
		result = &concreteContainer.m_container[idx];
	}

	return result;
}

//-----------------------------------------------------------------------------

template<typename T>
inline const T* ComponentsMgr::get(EntityId _id) const noexcept
{
	ConcreteComponentContainer<T>& concreteContainer = m_componentsContainer.getContainer<T>();

	T* result = nullptr;

	auto it = concreteContainer.m_lookupTable.find(_id);
	if (it != concreteContainer.m_lookupTable.end())
	{
		const size_t idx = it->second;
		result = &concreteContainer.m_container[idx];
	}

	return result;
}

//-----------------------------------------------------------------------------

template<typename T>
inline void ComponentsMgr::remove(EntityId _id) noexcept
{
	ConcreteComponentContainer<T>& concreteContainer = m_componentsContainer.getContainer<T>();

	auto it = concreteContainer.m_lookupTable.find(_id);
	if (it != concreteContainer.m_lookupTable.end())
	{
		const size_t idx = it->second;
		concreteContainer.m_container.erase(concreteContainer.m_container.begin() + idx);

		concreteContainer.m_lookupTable.erase(_id);
		concreteContainer.m_reverselookupTable.erase(idx);
	}
}

//-----------------------------------------------------------------------------

template<typename ... Args, typename>
inline ComponentsContainerRef<Args...> ComponentsMgr::view() noexcept
{
	return ComponentsContainerRef<Args...>(m_componentsContainer);
}

//-----------------------------------------------------------------------------

template<typename T>
inline ConcreteComponentContainerRef<T> ComponentsMgr::view() noexcept
{
	return ConcreteComponentContainerRef<T>(m_componentsContainer.getContainer<T>());
}

//-----------------------------------------------------------------------------

} // namespace jl::ecs

//-----------------------------------------------------------------------------
