#include "renderer/scene/Scene.hpp"
#include "renderer/scene/IRenderable.hpp"

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

Scene::Scene() = default;
Scene::~Scene() = default;

//-----------------------------------------------------------------------------

void Scene::update(float _dt)
{
	for (auto& it : m_renderables)
	{
		it.second->update(_dt);
	}
}

//-----------------------------------------------------------------------------

void Scene::render(const Camera& _camera)
{
	for (auto& it : m_renderables)
	{
		it.second->render(_camera);
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
	for (auto& it : m_renderables)
	{
		_callback(it.first, *it.second);
	}
}

//-----------------------------------------------------------------------------

void Scene::forEachRenderable(const std::function<void(s32, const IRenderable&)>& _callback) const
{
	for (const auto& it : m_renderables)
	{
		_callback(it.first, *it.second);
	}
}

//-----------------------------------------------------------------------------

//void Scene::drawObject(const ICamera& _camera, const Object& _object) const noexcept
//{
//	const Material* material = _object.getMaterial();
//	if (material)
//	{
//		material->bind();
//
//		const Shader* shader = material->getShader();
//		if (shader)
//		{
//			CommonUniformsBinder uniformBinder(*shader, _camera, _object);
//			uniformBinder.setupCommon();
//
//			if (m_fogData)
//			{
//				uniformBinder.setupFog(*m_fogData);
//			}
//		}
//
//		Shader::draw(_object.getModel());
//	}
//}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
