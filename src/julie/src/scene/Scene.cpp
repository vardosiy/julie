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

EntityRef Scene::createEntity(std::string _name)
{
	EntityRef entity = m_entitiesMgr.create();
	entity.addComponent<TagComponent>(std::move(_name));
	entity.addComponent<TransformComponent>();

	return entity;
}

//-----------------------------------------------------------------------------

void Scene::removeEntity(EntityId _id) noexcept
{
	m_entitiesMgr.remove(_id);
}

//-----------------------------------------------------------------------------

size_t Scene::getEntitiesCount() const noexcept
{
	return m_entitiesMgr.getCount();
}

//-----------------------------------------------------------------------------

std::optional<EntityRef> Scene::getEntity(size_t _idx) noexcept
{
	return m_entitiesMgr.get(_idx);
}

//-----------------------------------------------------------------------------

std::optional<EntityRef> Scene::findEntity(EntityId _id) noexcept
{
	return m_entitiesMgr.find(_id);
}

//-----------------------------------------------------------------------------

EntityIterator Scene::begin() noexcept
{
	return m_entitiesMgr.begin();
}

//-----------------------------------------------------------------------------

EntityIterator Scene::end() noexcept
{
	return m_entitiesMgr.end();
}

//-----------------------------------------------------------------------------

ConstEntityIterator Scene::begin() const noexcept
{
	return m_entitiesMgr.begin();
}

//-----------------------------------------------------------------------------

ConstEntityIterator Scene::end() const noexcept
{
	return m_entitiesMgr.end();
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
