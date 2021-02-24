#include "julie/ecs/RenderSystem.hpp"
#include "julie/ecs/ComponentsMgr.hpp"

#include "julie/scene/Scene.hpp"
#include "julie/Model.hpp"
#include "julie/Mesh.hpp"
#include "julie/Shader.hpp"
#include "julie/Material.hpp"
#include "julie/Renderer.hpp"

#include "scene/CommonUniformsBinder.hpp"
#include "PropertyBinder.hpp"

#include "julie/Axis.hpp"

#include <glm/gtx/transform.hpp>

//-----------------------------------------------------------------------------
namespace jl::ecs {
//-----------------------------------------------------------------------------

RenderSystem::RenderSystem(const Scene& _scene, ComponentsMgr& _componentsMgr) noexcept
	: m_scene(_scene)
	, m_componentsMgr(_componentsMgr)
{
}

//-----------------------------------------------------------------------------

void RenderSystem::update(const Camera& _cam)
{
	updateLightsCache();
	drawScene(_cam);
}

//-----------------------------------------------------------------------------

void RenderSystem::updateLightsCache()
{
	auto view = m_componentsMgr.view<TransformComponent, LightSourceComponent>();

	auto& lights = view.getContainer<LightSourceComponent>();
	auto& transforms = view.getContainer<TransformComponent>();

	const size_t lightsCount = lights.m_containerRef.size();
	m_lightsPosCache.resize(lightsCount);
	m_lightsColorCache.resize(lightsCount);

	for (size_t i = 0; i < lightsCount; ++i)
	{
		const LightSourceComponent& lightComponent = lights.m_containerRef[i];
		m_lightsColorCache[i] = lightComponent.color;
	}

	for (size_t i = 0; i < lightsCount; ++i)
	{
		const EntityId currId = lights.m_reverseLookupTableRef[i];
		const size_t transformIdx = transforms.m_lookupTableRef[currId];
		m_lightsPosCache[i] = transforms.m_containerRef[transformIdx].pos;
	}
}

//-----------------------------------------------------------------------------

void RenderSystem::drawScene(const Camera& _cam) const noexcept
{
	auto view = m_componentsMgr.view<WorldMatComponent, ModelComponent>();

	auto& models = view.getContainer<ModelComponent>();
	auto& worldMats = view.getContainer<WorldMatComponent>();

	const size_t modelsCount = models.m_containerRef.size();
	for (size_t i = 0; i < modelsCount; ++i)
	{
		const ModelComponent& modelComponent = models.m_containerRef[i];

		const EntityId currId = models.m_reverseLookupTableRef[i];
		const size_t transformIdx = worldMats.m_lookupTableRef[currId];
		const glm::mat4& worldMat = worldMats.m_containerRef[transformIdx].worldMat;

		drawModel(*modelComponent.model, _cam, worldMat);
	}
}

//-----------------------------------------------------------------------------

void RenderSystem::drawModel(const Model& _model, const Camera& _cam, const glm::mat4& _worldMat) const noexcept
{
	const size_t meshesCount = _model.getMeshesCount();
	for (size_t i = 0; i < meshesCount; ++i)
	{
		const Mesh& mesh = _model.getMesh(i);
		if (const Material* material = mesh.getMaterial())
		{
			if (const Shader* shader = material->getShader())
			{
				shader->bind();
				s16 textureSlotsCounter = 0;
				for (const auto& property : material->getProperties())
				{
					PropertyBinder binder(*shader, property.name, textureSlotsCounter);
					std::visit(binder, property.value);
				}

				CommonUniformsBinder uniformBinder(m_scene, _cam, _worldMat);
				uniformBinder.setLights(m_lightsPosCache, m_lightsColorCache);
				uniformBinder.bind(*shader);

				Renderer::draw(mesh);
			}
		}
	}
}

//-----------------------------------------------------------------------------
} // namespace jl::ecs
//-----------------------------------------------------------------------------
