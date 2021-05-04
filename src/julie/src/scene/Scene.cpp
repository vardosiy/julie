#include "julie/scene/Scene.hpp"
#include "julie/Axis.hpp"

#include "utils/Utils.hpp"

#include <glm/gtx/transform.hpp>

//-----------------------------------------------------------------------------
namespace jl {
//-----------------------------------------------------------------------------

Scene::Scene() noexcept
	: m_entitiesMgr(m_componentsMgr)
{
}

Scene::~Scene() noexcept = default;

//-----------------------------------------------------------------------------

const FogData* Scene::getFogData() const noexcept
{
	return m_fogData.has_value() ? &m_fogData.value() : nullptr;
}

//-----------------------------------------------------------------------------

void Scene::setFogData(std::optional<FogData> _fogData) noexcept
{
	m_fogData = _fogData;
}

//-----------------------------------------------------------------------------

const AmbientLightData* Scene::getAmbientLightData() const noexcept
{
	return m_ambientLightData.has_value() ? &m_ambientLightData.value() : nullptr;
}

//-----------------------------------------------------------------------------

void Scene::setAmbientLightData(std::optional<AmbientLightData> _ambientLightData) noexcept
{
	m_ambientLightData = _ambientLightData;
}

//-----------------------------------------------------------------------------

EntityRef Scene::createEntity(std::string _name)
{
	EntityRef entity = m_entitiesMgr.create();
	entity.addComponent<TagComponent>(std::move(_name));
	entity.addComponent<TransformComponent>();
	entity.addComponent<WorldMatComponent>();

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

ecs::ComponentsMgr& Scene::getComponentsMgr() noexcept
{
	return m_componentsMgr;
}

//-----------------------------------------------------------------------------
} // namespace jl
//-----------------------------------------------------------------------------
