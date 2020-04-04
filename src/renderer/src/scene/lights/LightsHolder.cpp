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

} // namespace jl

//-----------------------------------------------------------------------------
