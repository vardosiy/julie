#include "julie/scene/Scene.hpp"
#include "julie/Axis.hpp"

#include "utils/Utils.hpp"

#include <glm/gtx/transform.hpp>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

Scene::Scene() noexcept
	: m_entitiesMgr(m_componentsMgr)
	, m_transformProcessSystem(m_componentsMgr)
	, m_renderSystem(*this, m_componentsMgr)
{
}

Scene::~Scene() noexcept = default;

//-----------------------------------------------------------------------------

void Scene::update(std::chrono::milliseconds _dt)
{
	m_transformProcessSystem.update();
}

//-----------------------------------------------------------------------------

void Scene::render(const Camera& _cam)
{
	m_renderSystem.update(_cam);
}

//-----------------------------------------------------------------------------

const AmbientLightData& Scene::getAmbientLightData() const noexcept
{
	return m_ambientLightData;
}

//-----------------------------------------------------------------------------

void Scene::setAmbientLightData(const AmbientLightData& _data) noexcept
{
	m_ambientLightData = _data;
}

//-----------------------------------------------------------------------------

const FogData* Scene::getFogData() const noexcept
{
	return m_fogData.has_value() ? &m_fogData.value() : nullptr;
}

//-----------------------------------------------------------------------------

void Scene::setFogData(const FogData& _data) noexcept
{
	m_fogData = _data;
}

//-----------------------------------------------------------------------------

ecs::Entity& Scene::createEntity(std::string _name)				{ return m_entitiesMgr.create(std::move(_name)); }
ecs::Entity* Scene::findEntity(ecs::EntityId _id) noexcept		{ return m_entitiesMgr.find(_id); }
void Scene::removeEntity(ecs::EntityId _id) noexcept			{ m_entitiesMgr.remove(_id); }

size_t Scene::getEntitiesCount() const noexcept					{ return m_entitiesMgr.getCount(); }

//-----------------------------------------------------------------------------

ecs::EntitiesMgr::Iterator Scene::begin() noexcept				{ return m_entitiesMgr.begin(); }
ecs::EntitiesMgr::Iterator Scene::end() noexcept				{ return m_entitiesMgr.end(); }

ecs::EntitiesMgr::ConstIterator Scene::begin() const noexcept	{ return m_entitiesMgr.begin(); }
ecs::EntitiesMgr::ConstIterator Scene::end() const noexcept		{ return m_entitiesMgr.end(); }

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
