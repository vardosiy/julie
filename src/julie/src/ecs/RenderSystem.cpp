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

void RenderSystem::update(ComponentsMgr& _componentsMgr, const Camera& _cam)
{
	updateLightsCache(_componentsMgr);
	draw(_componentsMgr, _cam);
}

//-----------------------------------------------------------------------------

void RenderSystem::setFogData(std::optional<FogData> _fogData) noexcept
{
	m_fogData = _fogData;
}

//-----------------------------------------------------------------------------

void RenderSystem::setAmbientLightData(std::optional<AmbientLightData> _ambientLightData) noexcept
{
	m_ambientLightData = _ambientLightData;
}

//-----------------------------------------------------------------------------

void RenderSystem::updateLightsCache(ComponentsMgr& _componentsMgr)
{
	size_t i = 0;
	_componentsMgr.forEach<LightSourceComponent, TransformComponent>([this, &i](LightSourceComponent& _light, TransformComponent& _transform)
	{
		m_lightsColorCache[i] = _light.color;
		m_lightsPosCache[i] = _transform.pos;
		++i;
	});
}

//-----------------------------------------------------------------------------

void RenderSystem::draw(ComponentsMgr& _componentsMgr, const Camera& _cam) const noexcept
{
	_componentsMgr.forEach<ModelComponent, WorldMatComponent>([this, &_cam](ModelComponent& _model, WorldMatComponent& _worldMat)
	{
		drawModel(*_model.model, _cam, _worldMat.worldMat);
	});
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

				CommonUniformsBinder uniformBinder(_cam, _worldMat);

				if (m_fogData) uniformBinder.setFog(m_fogData.value());
				if (m_ambientLightData) uniformBinder.setAmbientLight(m_ambientLightData.value());

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
