#include "renderer/scene/lights/LightsHolder.hpp"

#include "utils/Utils.hpp"

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

const AmbientLightData& LightsHolder::getAmbientLightData() const noexcept
{
	return m_ambientLight;
}

//-----------------------------------------------------------------------------

void LightsHolder::setAmbientLight(const AmbientLightData& _lightData) noexcept
{
	m_ambientLight = _lightData;
}

//-----------------------------------------------------------------------------

void LightsHolder::addPointLight(const PointLightData& _lightData) noexcept
{
	ASSERT(m_pointLightsColors.size() == m_pointLightsPositions.size());

	m_pointLightsColors.push_back(_lightData.color);
	m_pointLightsPositions.push_back(_lightData.position);
}

//-----------------------------------------------------------------------------

void LightsHolder::addDirectionalLight(const DirectionalLightData& _lightData) noexcept
{
	ASSERT(m_direcitonalLightsColors.size() == m_direcitonalLightsDirection.size());

	m_direcitonalLightsColors.push_back(_lightData.color);
	m_direcitonalLightsDirection.push_back(_lightData.direction);
}

//-----------------------------------------------------------------------------

const std::vector<glm::vec3>& LightsHolder::getPointLightsColors() const noexcept
{
	return m_pointLightsColors;
}

//-----------------------------------------------------------------------------

const std::vector<glm::vec3>& LightsHolder::getPointLightsPositions() const noexcept
{
	return m_pointLightsPositions;
}

//-----------------------------------------------------------------------------

const std::vector<glm::vec3>& LightsHolder::getDirectionalLightsColors() const noexcept
{
	return m_direcitonalLightsColors;
}

//-----------------------------------------------------------------------------

const std::vector<glm::vec3>& LightsHolder::getDirectionalLightsDirections() const noexcept
{
	return m_direcitonalLightsDirection;
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
