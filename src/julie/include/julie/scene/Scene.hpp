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

	void update(std::chrono::milliseconds _dt);
	void render(const Camera& _cam);

//-----------------------------------------------------------------------------
	const AmbientLightData& getAmbientLightData() const noexcept;
	void setAmbientLightData(const AmbientLightData& _data) noexcept;

	const FogData* getFogData() const noexcept;
	void setFogData(const FogData& _data) noexcept;

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
private:
	ecs::ComponentsMgr m_componentsMgr;
	ecs::EntitiesMgr m_entitiesMgr;

	ecs::TransformProcessSystem m_transformProcessSystem;
	ecs::RenderSystem m_renderSystem;

	AmbientLightData m_ambientLightData;
	std::optional<FogData> m_fogData;
};

//-----------------------------------------------------------------------------
} // namespace jl
//-----------------------------------------------------------------------------
