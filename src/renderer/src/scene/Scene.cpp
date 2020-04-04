#include "renderer/scene/Scene.hpp"

#include "renderer/Model.hpp"
#include "renderer/Material.hpp"
#include "renderer/Shader.hpp"
#include "renderer/scene/IRenderable.hpp"
#include "renderer/scene/CommonUniformsBinder.hpp"

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

Scene::Scene() = default;
Scene::~Scene() = default;

//-----------------------------------------------------------------------------

void Scene::update(float _dt)
{
	for (auto& [id, renderable] : m_renderables)
	{
		renderable->update(_dt);
	}
}

//-----------------------------------------------------------------------------

void Scene::render(const Camera& _camera) const
{
	for (auto& [id, renderable] : m_renderables)
	{
		const Model* model = renderable->getModel();
		const Material* material = renderable->getMaterial();

		if (material && model)
		{
			material->bind();

			const Shader* shader = material->getShader();
			if (shader)
			{
				CommonUniformsBinder uniformBinder(*shader);
				uniformBinder.setupCommon(_camera, renderable->getWorldMatrix());
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

void Scene::addRenderable(s32 _id, IRenderable& _renderable)
{
	m_renderables.emplace(_id, &_renderable);
}

//-----------------------------------------------------------------------------

void Scene::removeRenderable(s32 _id)
{
	m_renderables.erase(_id);
}

//-----------------------------------------------------------------------------

IRenderable* Scene::findRenderable(s32 _id) noexcept
{
	auto it = m_renderables.find(_id);
	return it != m_renderables.end() ? it->second : nullptr;
}

//-----------------------------------------------------------------------------

const IRenderable* Scene::findRenderable(s32 _id) const noexcept
{
	auto it = m_renderables.find(_id);
	return it != m_renderables.end() ? it->second : nullptr;
}

//-----------------------------------------------------------------------------

void Scene::forEachRenderable(const std::function<void(s32, IRenderable&)>& _callback)
{
	for (auto& [id, renderable] : m_renderables)
	{
		_callback(id, *renderable);
	}
}

//-----------------------------------------------------------------------------

void Scene::forEachRenderable(const std::function<void(s32, const IRenderable&)>& _callback) const
{
	for (const auto& [id, renderable] : m_renderables)
	{
		_callback(id, *renderable);
	}
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
