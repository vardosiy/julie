#include "renderer/scene/Scene.hpp"
#include "renderer/scene/Object.hpp"
#include "renderer/scene/CommonUniformsBinder.hpp"

#include "renderer/Material.hpp"
#include "renderer/Shader.hpp"
#include "renderer/Model.hpp"
#include "renderer/Renderer.hpp"
#include "renderer/scene/Camera.hpp"

#include "utils/Utils.hpp"

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

Scene::Scene() = default;
Scene::~Scene() = default;

//-----------------------------------------------------------------------------

void Scene::update(float _dt)
{
}

//-----------------------------------------------------------------------------

void Scene::render(const Camera& _camera) const
{
	for (auto& object : m_objects)
	{
		const Model* model = object->getModel();
		const Material* material = object->getMaterial();

		if (object->getRenderFlags() & jl::Object::RenderFlags::DrawModel && material && model)
		{
			material->bind();

			const Shader* shader = material->getShader();
			if (shader)
			{
				CommonUniformsBinder uniformBinder(*shader);
				uniformBinder.setupCommon(_camera, object->getWorldMatrix());
				uniformBinder.setupLights(m_lightsHolder);

				Renderer::draw(*model);
			}
		}

		if (object->getRenderFlags() & jl::Object::RenderFlags::DrawBoundingBox && model)
		{
			Renderer::draw(
				model->getBoundingBox(),
				glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
				_camera.getViewProjectionMatrix() * object->getWorldMatrix()
			);
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

void Scene::addObject(ObjectPtr&& _object) noexcept
{
	ASSERT(_object);
	if (_object)
	{
		m_objects.emplace_back(std::move(_object));
	}
}

//-----------------------------------------------------------------------------

void Scene::removeObject(std::string_view _name) noexcept
{
	auto it = std::find_if(m_objects.begin(), m_objects.end(), [_name](const ObjectPtr& object)
	{
		return object->getName() == _name;
	});

	if (it != m_objects.end())
	{
		m_objects.erase(it);
	}
}

//-----------------------------------------------------------------------------

Object* Scene::findObject(std::string_view _name) noexcept
{
	auto it = std::find_if(m_objects.begin(), m_objects.end(), [_name](const ObjectPtr& object)
	{
		return object->getName() == _name;
	});
	return it != m_objects.end() ? it->get() : nullptr;
}

//-----------------------------------------------------------------------------

const Object* Scene::findObject(std::string_view _name) const noexcept
{
	auto it = std::find_if(m_objects.begin(), m_objects.end(), [_name](const ObjectPtr& object)
	{
		return object->getName() == _name;
	});
	return it != m_objects.end() ? it->get() : nullptr;
}

//-----------------------------------------------------------------------------

void Scene::forEachObject(const std::function<void(Object&)>& _callback)
{
	for (ObjectPtr& object : m_objects)
	{
		_callback(*object);
	}
}

//-----------------------------------------------------------------------------

void Scene::forEachObject(const std::function<void(const Object&)>& _callback) const
{
	for (const ObjectPtr& object : m_objects)
	{
		_callback(*object);
	}
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
