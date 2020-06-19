#include "julie/scene/Scene.hpp"
#include "julie/scene/Object.hpp"
#include "julie/scene/Camera.hpp"
#include "julie/scene/CommonUniformsBinder.hpp"

#include "julie/Material.hpp"
#include "julie/Shader.hpp"
#include "julie/Model.hpp"
#include "julie/Renderer.hpp"

#include "utils/Utils.hpp"

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

Scene::Scene() = default;
Scene::~Scene() = default;

//-----------------------------------------------------------------------------

void Scene::render(const Camera& _cam) const
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
			drawModel(*model, _cam, object->getWorldMatrix());
		}
		if (renderFlags & jl::Object::RenderFlags::DrawBoundingBox)
		{
			const glm::mat4 transform = _cam.getViewProjectionMatrix() * object->getWorldMatrix();
			Renderer::draw(model->getBoundingBox(), glm::vec4(1.0f), transform);
		}
	}
}

//-----------------------------------------------------------------------------

void Scene::drawModel(const Model& _model, const Camera& _cam, const glm::mat4& _worldMat) const noexcept
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
				uniformBinder.setupCommon(_cam, _worldMat);
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

void Scene::addObject(ObjectPtr&& _obj) noexcept
{
	ASSERT(_obj);
	if (_obj)
	{
		m_objects.emplace_back(std::move(_obj));
	}
}

//-----------------------------------------------------------------------------

u32 Scene::getObjectsCount() const noexcept
{
	return m_objects.size();
}

//-----------------------------------------------------------------------------

Object* Scene::getObject(u32 _idx) noexcept
{
	return _idx < m_objects.size() ? m_objects[_idx].get() : nullptr;
}

//-----------------------------------------------------------------------------

const Object* Scene::getObject(u32 _idx) const noexcept
{
	return _idx < m_objects.size() ? m_objects[_idx].get() : nullptr;
}

//-----------------------------------------------------------------------------

void Scene::removeObject(u32 _idx) noexcept
{
	if (_idx < m_objects.size())
	{
		m_objects.erase(m_objects.begin() + _idx);
	}
}

//-----------------------------------------------------------------------------

void Scene::removeObject(const Object& _obj) noexcept
{
	auto it = std::find_if(m_objects.begin(), m_objects.end(), [&_obj](const ObjectPtr& _objPtr)
	{
		return _objPtr.get() == &_obj;
	});

	if (it != m_objects.end())
	{
		m_objects.erase(it);
	}
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
