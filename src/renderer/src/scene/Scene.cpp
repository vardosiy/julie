#include "renderer/scene/Scene.hpp"

#include "renderer/scene/Camera.hpp"
#include "renderer/scene/Model.hpp"
#include "renderer/scene/Object.hpp"
#include "renderer/scene/AmbientLightData.hpp"
#include "renderer/scene/Light.hpp"

#include "renderer/common/Axis.hpp"

#include "utils/LogDefs.hpp"
#include "utils/Assert.hpp"

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

Scene::Scene() = default;

//-----------------------------------------------------------------------------

Scene::~Scene() = default;

//-----------------------------------------------------------------------------

void Scene::draw(const Camera & _camera)
{
	if (m_prerenderCallback)
	{
		m_prerenderCallback();
	}

	for (auto & it : m_objects)
	{
		it.second->draw(_camera);
	}

	if (m_postrenderCallback)
	{
		m_postrenderCallback();
	}
}

//-----------------------------------------------------------------------------

void Scene::update(float _deltaTime)
{
	for (auto & it : m_objects)
	{
		it.second->update(_deltaTime);
	}
}

//-----------------------------------------------------------------------------

void Scene::addObject(s32 _id, std::unique_ptr<Object> && _object)
{
	m_objects.emplace(_id, std::move(_object));
}

//-----------------------------------------------------------------------------

Object * Scene::findObject(s32 _id) noexcept
{
	auto it = m_objects.find(_id);
	return it != m_objects.end() ? it->second.get() : nullptr;
}

//-----------------------------------------------------------------------------

const Object * Scene::findObject(s32 _id) const noexcept
{
	auto it = m_objects.find(_id);
	return it != m_objects.end() ? it->second.get() : nullptr;
}

//-----------------------------------------------------------------------------

void Scene::forEachObject(const std::function<void(s32, Object &)> & _callback)
{
	for (auto & it : m_objects)
	{
		_callback(it.first, *it.second);
	}
}

//-----------------------------------------------------------------------------

void Scene::forEachObject(const std::function<void(s32, const Object &)> & _callback) const
{
	for (const auto & it : m_objects)
	{
		_callback(it.first, *it.second);
	}
}

//-----------------------------------------------------------------------------

void Scene::setFogData(const FogData & _data) noexcept
{
	m_fogData = _data;
}

//-----------------------------------------------------------------------------

void Scene::setAmbientLightData(const AmbientLightData & _data) noexcept
{
	m_ambientLightData = _data;
}

//-----------------------------------------------------------------------------

void Scene::setPrerenderCommand(const std::function<void()> & _callback) noexcept
{
	m_prerenderCallback = _callback;
}

//-----------------------------------------------------------------------------

void Scene::setPostrenderCommand(const std::function<void()> & _callback) noexcept
{
	m_postrenderCallback = _callback;
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
