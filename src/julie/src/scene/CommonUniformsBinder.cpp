#include "scene/CommonUniformsBinder.hpp"

#include "julie/Globals.hpp"
#include "julie/Shader.hpp"
#include "julie/scene/Scene.hpp"
#include "julie/scene/Camera.hpp"

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

CommonUniformsBinder::CommonUniformsBinder(const Camera& _camera, const glm::mat4& _worldMat) noexcept
	: m_camera(_camera)
	, m_worldMat(_worldMat)
	, m_fog(nullptr)
	, m_ambientLight(nullptr)
	, m_lightPositions(nullptr)
	, m_lightColors(nullptr)
{
}

//-----------------------------------------------------------------------------

void CommonUniformsBinder::setFog(const FogData& _fog) noexcept
{
	m_fog = &_fog;
}

//-----------------------------------------------------------------------------

void CommonUniformsBinder::setAmbientLight(const AmbientLightData& _ambientLight) noexcept
{
	m_ambientLight = &_ambientLight;
}

//-----------------------------------------------------------------------------

void CommonUniformsBinder::setLights(const std::vector<glm::vec3>& _positions, const std::vector<glm::vec3>& _colors) noexcept
{
	m_lightPositions = &_positions;
	m_lightColors = &_colors;
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

	bindUniform(u_W,			m_worldMat);
	bindUniform(u_WVP,			m_camera.getViewProjectionMatrix() * m_worldMat);
	bindUniform(u_camPosition,	m_camera.getPosition());
	bindUniform(u_time,			Globals::s_timeTotal);

	if (m_fog)
	{
		bindUniform(u_fogStart, m_fog->start);
		bindUniform(u_fogRange, m_fog->range);
		bindUniform(u_fogColor, m_fog->color);
	}

	if (m_ambientLight)
	{
		bindUniform(u_ambientColor, m_ambientLight->color);
		bindUniform(u_ambientWeight, m_ambientLight->weight);
	}

	if (m_lightPositions && m_lightColors)
	{
		bindUniformArr(u_lightPosition, *m_lightPositions);
		bindUniformArr(u_pointLightColor, *m_lightColors);
		//bindUniformArr(u_directionalLightColor,	lightsHolder.getDirectionalLightsColors());
		//bindUniformArr(u_lightDirection,		lightsHolder.getDirectionalLightsDirections());
	}
}

//-----------------------------------------------------------------------------
} // namespace jl
//-----------------------------------------------------------------------------
