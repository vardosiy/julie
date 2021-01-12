#pragma once

#include "julie/ecs/EntityId.hpp"
#include "julie/ecs/ComponentsMgr.hpp"

#include "utils/Identifier.hpp"

#include <glm/glm.hpp>

//-----------------------------------------------------------------------------

namespace jl::ecs {

//-----------------------------------------------------------------------------

class EntitiesMgr;

class Entity
{
	friend class EntitiesMgr;

public:
	Entity(Entity&&) noexcept = default;
	Entity& operator= (Entity&&) noexcept = default;

	EntityId getId() const noexcept;

	template<typename T, typename ... Args>
	T& addComponent(Args&& ... _args);

	template<typename T>
	T* getComponent() noexcept;

	template<typename T>
	void removeComponent() noexcept;

private:
	Entity(EntityId _id, ComponentsMgr& _componentsMgr) noexcept;

	EntityId m_id;
	ComponentsMgr* m_componentsMgr;
};

//-----------------------------------------------------------------------------

template<typename T, typename ... Args>
inline T& Entity::addComponent(Args&& ... _args)
{
	return m_componentsMgr->emplace<T>(getId(), std::forward<Args>(_args)...);
}

template<typename T>
inline T* Entity::getComponent() noexcept
{
	return m_componentsMgr->get<T>(getId());
}

template<typename T>
inline void Entity::removeComponent() noexcept
{
	m_componentsMgr->remove<T>(getId());
}

//-----------------------------------------------------------------------------

} // jl::ecs

//-----------------------------------------------------------------------------
