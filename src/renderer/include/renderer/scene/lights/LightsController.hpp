#pragma once

#include "renderer/scene/lights/LightsData.hpp"

#include <boost/noncopyable.hpp>

#include <vector>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

class LightsController : boost::noncopyable
{
public:
	void update(float _dt);

	void setAmbientLight(const AmbientLightData& _lightData) noexcept;

	void addPointLight(const PointLightData& _lightData) noexcept;
	void addDirectionalLight(const DirectionalLightData& _lightData) noexcept;

	const AmbientLightData& getAmbientLightData() const noexcept { return m_ambientLight; }

private:
	AmbientLightData m_ambientLight;

	std::vector<PointLightData> m_pointLights;
	std::vector<DirectionalLightData> m_directionalLights;

	std::vector<glm::vec4> m_pointLightsColors;
	std::vector<glm::vec3> m_pointLightsPositions;
	std::vector<glm::vec4> m_direcitonalLightsColors;
	std::vector<glm::vec3> m_direcitonalLightsDirection;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
