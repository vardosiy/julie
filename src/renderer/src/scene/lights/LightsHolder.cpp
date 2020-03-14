#include "renderer/scene/lights/LightsHolder.hpp"

#include "renderer/Shader.hpp"

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

void LightsHolder::update(float _dt)
{
}

//-----------------------------------------------------------------------------

void LightsHolder::bind(const Shader& _shader) const
{
	auto setVectorUniform =
		[&_shader](const std::string& _uniformName, const auto& _vector)
		{
			_shader.setUniform(_uniformName, _vector.size(), _vector.data());
		};

	setVectorUniform("u_directionalLightColor", m_direcitonalLightsColors);
	setVectorUniform("u_lightDirection", m_direcitonalLightsDirection);

	setVectorUniform("u_pointLightColor", m_pointLightsColors);
	setVectorUniform("u_lightPosition", m_pointLightsPositions);
}

//-----------------------------------------------------------------------------

const AmbientLightData& LightsHolder::getAmbientLightData() const noexcept
{
	return m_ambientLight;
}

//-----------------------------------------------------------------------------

void LightsHolder::setAmbientLight(const AmbientLightData & _lightData) noexcept
{
	m_ambientLight = _lightData;
}

//-----------------------------------------------------------------------------

void LightsHolder::addPointLight(const PointLightData& _lightData) noexcept
{
	m_pointLightsColors.push_back(_lightData.color);
	m_pointLightsPositions.push_back(_lightData.position);

	//m_pointLights.emplace_back(_lightData);
}

//-----------------------------------------------------------------------------

void LightsHolder::addDirectionalLight(const DirectionalLightData & _lightData) noexcept
{
	m_direcitonalLightsColors.push_back(_lightData.color);
	m_direcitonalLightsDirection.push_back(_lightData.direction);

	//m_directionalLights.emplace_back(_lightData);
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
