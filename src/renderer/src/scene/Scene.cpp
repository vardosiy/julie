#include "renderer/scene/Scene.hpp"
#include "renderer/scene/Object.hpp"
#include "renderer/scene/CommonUniformsBinder.hpp"

#include "renderer/Model.hpp"
#include "renderer/Material.hpp"
#include "renderer/Shader.hpp"

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

Scene::Scene() = default;
Scene::~Scene() = default;

//-----------------------------------------------------------------------------

void Scene::update(float _dt)
{
	//for (auto& [id, renderable] : m_objects)
	//{
	//	renderable->update(_dt);
	//}
}

//-----------------------------------------------------------------------------

void Scene::render(const Camera& _camera) const
{
	for (auto& [id, object] : m_objects)
	{
		const Model* model = object->getModel();
		const Material* material = object->getMaterial();

		if (material && model)
		{
			material->bind();

			const Shader* shader = material->getShader();
			if (shader)
			{
				CommonUniformsBinder uniformBinder(*shader);
				uniformBinder.setupCommon(_camera, object->getWorldMatrix());
				uniformBinder.setupLights(m_lightsHolder);

				shader->draw(*model);
			}
		}
	}
}

//-----------------------------------------------------------------------------

const FogData* Scene::getFogData() const noexcept
{
	return m_fogData.get_ptr();
}

//-----------------------------------------------------------------------------

LightsHolder& Scene::getLightsHolder() noexcept
{
	return m_lightsHolder;
}

//-----------------------------------------------------------------------------

const LightsHolder& Scene::getLightsHolder() const noexcept
{
	return m_lightsHolder;
}

//-----------------------------------------------------------------------------

void Scene::setFogData(const FogData& _data) noexcept
{
	m_fogData = _data;
}

//-----------------------------------------------------------------------------

void Scene::addObject(s32 _id, Object& _object)
{
	m_objects.emplace(_id, &_object);
}

//-----------------------------------------------------------------------------

void Scene::removeObject(s32 _id)
{
	m_objects.erase(_id);
}

//-----------------------------------------------------------------------------

Object* Scene::findObject(s32 _id) noexcept
{
	auto it = m_objects.find(_id);
	return it != m_objects.end() ? it->second : nullptr;
}

//-----------------------------------------------------------------------------

const Object* Scene::findObject(s32 _id) const noexcept
{
	auto it = m_objects.find(_id);
	return it != m_objects.end() ? it->second : nullptr;
}

//-----------------------------------------------------------------------------

void Scene::forEachObject(const std::function<void(s32, Object&)>& _callback)
{
	for (auto& [id, object] : m_objects)
	{
		_callback(id, *object);
	}
}

//-----------------------------------------------------------------------------

void Scene::forEachObject(const std::function<void(s32, const Object&)>& _callback) const
{
	for (const auto& [id, object] : m_objects)
	{
		_callback(id, *object);
	}
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
