#pragma once

#include "julie/ecs/EntityId.hpp"
#include "julie/ecs/ComponentsMgr.hpp"

namespace jl::ecs {
class EntitiesMgr;
}

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

class EntityIterator;
class ConstEntityIterator;

class EntityRef
{
	friend class ecs::EntitiesMgr;

	friend class EntityIterator;
	friend class ConstEntityIterator;

//-----------------------------------------------------------------------------
public:
	EntityRef(const EntityRef&) noexcept = default;
	EntityRef& operator= (const EntityRef&) noexcept = default;

	EntityRef(EntityRef&&) noexcept = default;
	EntityRef& operator= (EntityRef&&) noexcept = default;

	bool operator== (EntityRef _rhs) const noexcept { return getId() == _rhs.getId(); }
	bool operator!= (EntityRef _rhs) const noexcept { return !(*this == _rhs); }

//-----------------------------------------------------------------------------
	EntityId getId() const noexcept;

	template<typename T, typename ... Args>
	T& addComponent(Args&& ... _args);

	template<typename T>
	T* getComponent() noexcept;

	template<typename T>
	const T* getComponent() const noexcept;

	template<typename T>
	void removeComponent() noexcept;

//-----------------------------------------------------------------------------
private:
	EntityRef(EntityId _id, ecs::ComponentsMgr& _componentsMgr) noexcept;

//-----------------------------------------------------------------------------
	EntityId m_id;
	ecs::ComponentsMgr* m_componentsMgr;
};

//-----------------------------------------------------------------------------

template<typename T, typename ... Args>
inline T& EntityRef::addComponent(Args&& ... _args)
{
	return m_componentsMgr->emplace<T>(getId(), std::forward<Args>(_args)...);
}

template<typename T>
inline T* EntityRef::getComponent() noexcept
{
	return m_componentsMgr->get<T>(getId());
}

template<typename T>
inline const T* EntityRef::getComponent() const noexcept
{
	return m_componentsMgr->get<T>(getId());
}

template<typename T>
inline void EntityRef::removeComponent() noexcept
{
	m_componentsMgr->remove<T>(getId());
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
