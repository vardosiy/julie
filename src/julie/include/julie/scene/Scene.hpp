#pragma once

#include "julie/core/Types.hpp"

#include "julie/scene/AmbientLightData.hpp"
#include "julie/scene/FogData.hpp"

#include "julie/ecs/Entity.hpp"
#include "julie/ecs/EntitiesMgr.hpp"
#include "julie/ecs/ComponentsMgr.hpp"

#include "julie/ecs/TransformProcessSystem.hpp"
#include "julie/ecs/RenderSystem.hpp"

#include "utils/Noncopyable.hpp"

#include <optional>

//-----------------------------------------------------------------------------
namespace jl {
//-----------------------------------------------------------------------------

class Camera;

class Scene : utils::Noncopyable
{
//-----------------------------------------------------------------------------
public:
	Scene() noexcept;
	~Scene() noexcept;

//-----------------------------------------------------------------------------
	const FogData* getFogData() const noexcept;
	void setFogData(std::optional<FogData> _fogData) noexcept;

	const AmbientLightData* getAmbientLightData() const noexcept;
	void setAmbientLightData(std::optional<AmbientLightData> _ambientLightData) noexcept;

//-----------------------------------------------------------------------------
	EntityRef createEntity(std::string _name);
	void removeEntity(EntityId _id) noexcept;

	size_t getEntitiesCount() const noexcept;
	std::optional<EntityRef> getEntity(size_t _idx) noexcept;
	std::optional<EntityRef> findEntity(EntityId _id) noexcept;

	EntityIterator begin() noexcept;
	EntityIterator end() noexcept;

	ConstEntityIterator begin() const noexcept;
	ConstEntityIterator end() const noexcept;

//-----------------------------------------------------------------------------
	ecs::ComponentsMgr& getComponentsMgr() noexcept; // FIX THIS PEACE OF SHIT

//-----------------------------------------------------------------------------
private:
	ecs::ComponentsMgr m_componentsMgr;
	ecs::EntitiesMgr m_entitiesMgr;

	std::optional<FogData> m_fogData;
	std::optional<AmbientLightData> m_ambientLightData;
};

//-----------------------------------------------------------------------------
} // namespace jl
//-----------------------------------------------------------------------------
