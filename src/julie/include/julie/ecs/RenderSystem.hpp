#pragma once

#include "julie/scene/FogData.hpp"
#include "julie/scene/AmbientLightData.hpp"

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

#include <vector>
#include <optional>

namespace jl {
class Camera;
class Model;
}

//-----------------------------------------------------------------------------
namespace jl::ecs {
//-----------------------------------------------------------------------------

class ComponentsMgr;

class RenderSystem
{
//-----------------------------------------------------------------------------
public:
	void update(ComponentsMgr& _componentsMgr, const Camera& _cam);

	void setFogData(std::optional<FogData> _fogData) noexcept;
	void setAmbientLightData(std::optional<AmbientLightData> _ambientLightData) noexcept;

//-----------------------------------------------------------------------------
private:
	void updateLightsCache(ComponentsMgr& _componentsMgr);

	void draw(ComponentsMgr& _componentsMgr, const Camera& _cam) const noexcept;
	void drawModel(const Model& _model, const Camera& _cam, const glm::mat4& _worldMat) const noexcept;

//-----------------------------------------------------------------------------
	std::vector<glm::vec3> m_lightsPosCache;
	std::vector<glm::vec3> m_lightsColorCache;

	std::optional<FogData> m_fogData;
	std::optional<AmbientLightData> m_ambientLightData;
};

//-----------------------------------------------------------------------------
} // namespace jl::ecs
//-----------------------------------------------------------------------------
