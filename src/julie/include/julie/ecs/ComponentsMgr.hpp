#pragma once

#include "julie/ecs/EntityId.hpp"
#include "julie/ecs/Components.hpp"
#include "julie/ecs/ComponentsContainer.hpp"
#include "julie/ecs/ComponentsIterator.hpp"

#include "utils/TypeTraits.hpp"

#include <functional>

//-----------------------------------------------------------------------------
namespace jl::ecs {
//-----------------------------------------------------------------------------

class ComponentsMgr
{
	template<typename...> friend class ComponentIterator;

public:
	template<typename T, typename ... Args>
	T& emplace(EntityId _id, Args&& ... _args);

	template<typename T>
	void remove(EntityId _id) noexcept;

	template<typename T>
	T* get(EntityId _id) noexcept;

	template<typename T>
	const T* get(EntityId _id) const noexcept;

	template<typename ... Components>
	void forEach(std::function<void(Components&...)>&& _fun);

private:
	using AllComponentsContainer = ComponentsContainer<TagComponent,
													   TransformComponent,
													   ModelComponent,
													   RenderComponent,
													   WorldMatComponent,
													   LightSourceComponent>;

	template<typename T>
	ConcreteComponentContainer<T>& getContainer() noexcept;
	template<typename T>
	const ConcreteComponentContainer<T>& getContainer() const noexcept;

	AllComponentsContainer m_componentsContainer;
};

//-----------------------------------------------------------------------------

template<typename T, typename ... Args>
inline T& ComponentsMgr::emplace(EntityId _id, Args&& ... _args)
{
	ConcreteComponentContainer<T>& concreteContainer = getContainer<T>();

	T& result = concreteContainer.m_container.emplace_back(std::forward<Args>(_args)...);
	const size_t addedIdx = concreteContainer.m_container.size() - 1;

	concreteContainer.m_lookupTable[_id] = addedIdx;
	concreteContainer.m_reverseLookupTable[addedIdx] = _id;

	return result;
}

//-----------------------------------------------------------------------------

template<typename T>
inline void ComponentsMgr::remove(EntityId _id) noexcept
{
	ConcreteComponentContainer<T>& concreteContainer = getContainer<T>();

	auto it = concreteContainer.m_lookupTable.find(_id);
	if (it != concreteContainer.m_lookupTable.end())
	{
		const size_t idx = it->second;
		concreteContainer.m_container.erase(concreteContainer.m_container.begin() + idx);

		concreteContainer.m_lookupTable.erase(_id);
		concreteContainer.m_reverseLookupTable.erase(idx);
	}
}

//-----------------------------------------------------------------------------

template<typename T>
inline T* ComponentsMgr::get(EntityId _id) noexcept
{
	ConcreteComponentContainer<T>& concreteContainer = getContainer<T>();
	return concreteContainer.findById(_id);
}

//-----------------------------------------------------------------------------

template<typename T>
inline const T* ComponentsMgr::get(EntityId _id) const noexcept
{
	ConcreteComponentContainer<T>& concreteContainer = getContainer<T>();
	return concreteContainer.findById(_id);
}

//-----------------------------------------------------------------------------

template<typename ... Components>
inline void ComponentsMgr::forEach(std::function<void(Components&...)>&& _fun)
{
	ComponentIterator<Components...> it(*this);
	while (it.isValid())
	{
		std::apply(_fun, *it);
		++it;
	}
}

//-----------------------------------------------------------------------------

template<typename T>
inline ConcreteComponentContainer<T>& ComponentsMgr::getContainer() noexcept
{
	return m_componentsContainer.getContainer<T>();
}

//-----------------------------------------------------------------------------

template<typename T>
inline const ConcreteComponentContainer<T>& ComponentsMgr::getContainer() const noexcept
{
	return m_componentsContainer.getContainer<T>();
}

//-----------------------------------------------------------------------------
} // namespace jl::ecs
//-----------------------------------------------------------------------------
