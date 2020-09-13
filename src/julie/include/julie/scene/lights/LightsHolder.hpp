#pragma once

#include "julie/scene/lights/LightsData.hpp"

#include "utils/Noncopyable.hpp"

#include <vector>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

class Shader;

class LightsHolder : utils::Noncopyable
{
public:
	const AmbientLightData& getAmbientLightData() const noexcept;
	void setAmbientLight(const AmbientLightData& _lightData) noexcept;

	void addPointLight(const PointLightData& _lightData) noexcept;
	void addDirectionalLight(const DirectionalLightData& _lightData) noexcept;

	const std::vector<glm::vec3>& getPointLightsColors() const noexcept;
	const std::vector<glm::vec3>& getPointLightsPositions() const noexcept;

	const std::vector<glm::vec3>& getDirectionalLightsColors() const noexcept;
	const std::vector<glm::vec3>& getDirectionalLightsDirections() const noexcept;

private:
	AmbientLightData m_ambientLight;

	std::vector<glm::vec3> m_pointLightsColors;
	std::vector<glm::vec3> m_pointLightsPositions;

	std::vector<glm::vec3> m_direcitonalLightsColors;
	std::vector<glm::vec3> m_direcitonalLightsDirection;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
