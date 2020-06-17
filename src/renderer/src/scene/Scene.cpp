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
		if (!model)
		{
			continue;
		}

		const s32 renderFlags = object->getRenderFlags();
		if (renderFlags & jl::Object::RenderFlags::DrawModel)
		{
			drawModel(*model, _camera, object->getWorldMatrix());
		}

		boost::optional<glm::vec4> bbColor;
		if (renderFlags & jl::Object::RenderFlags::IsSelected)
		{
			bbColor = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
			if (renderFlags & jl::Object::RenderFlags::IsIntersected)
			{
				bbColor->r = 1.0f;
			}
		}
		else if (renderFlags & jl::Object::RenderFlags::DrawBoundingBox)
		{
			if (renderFlags & jl::Object::RenderFlags::IsIntersected)
			{
				bbColor = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
			}
			else
			{
				bbColor = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
			}
		}

		if (bbColor)
		{
			const glm::mat4 transform = _camera.getViewProjectionMatrix() * object->getWorldMatrix();
			Renderer::draw(model->getBoundingBox(), *bbColor, transform);
		}
	}
}

//-----------------------------------------------------------------------------

void Scene::drawModel(const Model& _model, const Camera& _camera, const glm::mat4& _worldMat) const
{
	const u32 meshesCount = _model.getMeshesCount();
	for (u32 i = 0; i < meshesCount; ++i)
	{
		const Mesh& mesh = _model.getMesh(i);

		if (const Material* material = mesh.getMaterial())
		{
			if (const Shader* shader = material->getShader())
			{
				material->bind();

				CommonUniformsBinder uniformBinder(*shader);
				uniformBinder.setupCommon(_camera, _worldMat);
				uniformBinder.setupLights(m_lightsHolder);

				Renderer::draw(mesh);
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
