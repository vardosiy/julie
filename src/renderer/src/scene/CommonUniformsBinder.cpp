#include "renderer/scene/CommonUniformsBinder.hpp"

#include "renderer/Globals.hpp"
#include "renderer/Shader.hpp"
#include "renderer/scene/Scene.hpp"
#include "renderer/scene/Camera.hpp"
#include "renderer/scene/FogData.hpp"

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

const std::string CommonUniformsBinder::u_W						= "u_W";
const std::string CommonUniformsBinder::u_WVP					= "u_WVP";
const std::string CommonUniformsBinder::u_time					= "u_time";
const std::string CommonUniformsBinder::u_camPosition			= "u_camPosition";

const std::string CommonUniformsBinder::u_fogStart				= "u_fogStart";
const std::string CommonUniformsBinder::u_fogRange				= "u_fogRange";
const std::string CommonUniformsBinder::u_fogColor				= "u_fogColor";

const std::string CommonUniformsBinder::u_ambientColor			= "u_ambientColor";
const std::string CommonUniformsBinder::u_ambientWeight			= "u_ambientWeight";

const std::string CommonUniformsBinder::u_directionalLightColor	= "u_directionalLightColor";
const std::string CommonUniformsBinder::u_lightDirection		= "u_lightDirection";

const std::string CommonUniformsBinder::u_pointLightColor		= "u_pointLightColor";
const std::string CommonUniformsBinder::u_lightPosition			= "u_lightPosition";

//-----------------------------------------------------------------------------

CommonUniformsBinder::CommonUniformsBinder(
	const Shader& _shader
) noexcept
	: m_shader(_shader)
{
}

//-----------------------------------------------------------------------------

void CommonUniformsBinder::setupCommon(const jl::Camera& _camera, const glm::mat4x4& _worldMatrix) const noexcept
{
	bindUniform(u_W,			_worldMatrix);
	bindUniform(u_WVP,			_camera.getViewProjectionMatrix() * _worldMatrix);
	bindUniform(u_camPosition,	_camera.getPosition());
	bindUniform(u_time,			Globals::s_timeTotal);
}

//-----------------------------------------------------------------------------

void CommonUniformsBinder::setupFog(const FogData& _fogData) const noexcept
{
	bindUniform(u_fogStart, _fogData.start);
	bindUniform(u_fogRange, _fogData.range);
	bindUniform(u_fogColor, _fogData.color);
}

//-----------------------------------------------------------------------------

void CommonUniformsBinder::setupLights(const LightsHolder& _lightsHolder) const noexcept
{
	bindUniform(u_ambientColor,				_lightsHolder.m_ambientLight.color);
	bindUniform(u_ambientWeight,			_lightsHolder.m_ambientLight.weight);

	bindUniform(u_directionalLightColor,	_lightsHolder.m_direcitonalLightsColors);
	bindUniform(u_lightDirection,			_lightsHolder.m_direcitonalLightsDirection);

	bindUniform(u_pointLightColor,			_lightsHolder.m_pointLightsColors);
	bindUniform(u_lightPosition,			_lightsHolder.m_pointLightsPositions);
}

//-----------------------------------------------------------------------------

template<typename T>
void CommonUniformsBinder::bindUniform(const std::string& _name, const T& _val) const noexcept
{
	if (m_shader.hasUniform(_name))
	{
		m_shader.setUniform(_name, _val);
	}
};

//-----------------------------------------------------------------------------

template<typename T>
void CommonUniformsBinder::bindUniform(const std::string& _name, const std::vector<T>& _val) const noexcept
{
	if (m_shader.hasUniform(_name))
	{
		m_shader.setUniform(_name, _val.size(), _val.data());
	}
}

//-----------------------------------------------------------------------------

//	"u_depthAdjust"
//	"u_tilingFactor"
//	"u_dMax"
//	"u_depthDispl"
//	"u_specularPower"
//	"u_step"
//	"u_limit"
//	"u_near"
//	"u_far"
//	"u_clarity"
//	"u_fade"

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
