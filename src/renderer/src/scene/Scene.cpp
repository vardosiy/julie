#include "renderer/scene/Scene.hpp"

#include "renderer/scene/Camera.hpp"
#include "renderer/scene/Object.hpp"
#include "renderer/scene/Light.hpp"

#include "renderer/Globals.hpp"
#include "renderer/Model.hpp"
#include "renderer/Shader.hpp"
#include "renderer/Material.hpp"

#include "scene/CommonUniformsBinder.hpp"

#include "utils/LogDefs.hpp"
#include "utils/Assert.hpp"

#include <string>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

Scene::Scene() = default;
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
		drawObject(_camera, *it.second);
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

const FogData * Scene::getFogData() const noexcept
{
	return m_fogData.get_ptr();
}

//-----------------------------------------------------------------------------

const AmbientLightData * Scene::getAmbientLightData() const noexcept
{
	return m_ambientLightData.get_ptr();
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

void Scene::drawObject(const Camera & _camera, const Object & _object) const noexcept
{
	const Material * material = _object.getMaterial();
	if (material)
	{
		material->bind();

		const Shader * shader = material->getShader();
		if (shader)
		{
			CommonUniformsBinder uniformBinder(*shader, _camera, _object);
			uniformBinder.run();
		}

		Shader::draw(_object.getModel());
	}
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
