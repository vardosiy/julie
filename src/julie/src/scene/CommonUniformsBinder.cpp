#include "julie/scene/CommonUniformsBinder.hpp"

#include "julie/Globals.hpp"
#include "julie/Shader.hpp"
#include "julie/scene/Scene.hpp"
#include "julie/scene/Camera.hpp"
#include "julie/scene/FogData.hpp"

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
const std::string CommonUniformsBinder::u_pointLightColor		= "u_pointLightColor";
const std::string CommonUniformsBinder::u_lightPosition			= "u_lightPosition";
const std::string CommonUniformsBinder::u_directionalLightColor	= "u_directionalLightColor";
const std::string CommonUniformsBinder::u_lightDirection		= "u_lightDirection";

//-----------------------------------------------------------------------------

CommonUniformsBinder::CommonUniformsBinder(
	const Scene& _scene,
	const Camera& _camera,
	const glm::mat4& _worldMatrix
) noexcept
	: m_scene(_scene)
	, m_camera(_camera)
	, m_worldMatrix(_worldMatrix)
{
}

//-----------------------------------------------------------------------------

void CommonUniformsBinder::bind(const Shader& _shader) const noexcept
{
	auto bindUniform = [&_shader](const std::string& _name, const auto& _val)
	{
		if (_shader.hasUniform(_name))
			_shader.setUniform(_name, _val);
	};
	auto bindUniformArr = [&_shader](const std::string& _name, const auto& _arr)
	{
		if (_shader.hasUniform(_name))
			_shader.setUniform(_name, _arr.size(), _arr.data());
	};

	_shader.bind();

	bindUniform(u_W,			m_worldMatrix);
	bindUniform(u_WVP,			m_camera.getViewProjectionMatrix() * m_worldMatrix);
	bindUniform(u_camPosition,	m_camera.getPosition());
	bindUniform(u_time,			Globals::s_timeTotal);

	if (const FogData* fogData = m_scene.getFogData())
	{
		bindUniform(u_fogStart,	fogData->start);
		bindUniform(u_fogRange,	fogData->range);
		bindUniform(u_fogColor,	fogData->color);
	}

	{
		const LightsHolder& lightsHolder = m_scene.getLightsHolder();

		bindUniform(u_ambientColor,				lightsHolder.getAmbientLightData().color);
		bindUniform(u_ambientWeight,			lightsHolder.getAmbientLightData().weight);

		bindUniformArr(u_pointLightColor,		lightsHolder.getPointLightsColors());
		bindUniformArr(u_lightPosition,			lightsHolder.getPointLightsPositions());
		bindUniformArr(u_directionalLightColor,	lightsHolder.getDirectionalLightsColors());
		bindUniformArr(u_lightDirection,		lightsHolder.getDirectionalLightsDirections());
	}
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
