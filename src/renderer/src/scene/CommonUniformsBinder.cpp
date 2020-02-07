#include "CommonUniformsBinder.hpp"

#include "renderer/Globals.hpp"
#include "renderer/Shader.hpp"
#include "renderer/scene/Scene.hpp"
#include "renderer/scene/ICamera.hpp"
#include "renderer/scene/Object.hpp"

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

const std::string CommonUniformsBinder::u_W				= "u_W";
const std::string CommonUniformsBinder::u_WVP			= "u_WVP";
const std::string CommonUniformsBinder::u_time			= "u_time";
const std::string CommonUniformsBinder::u_camPosition	= "u_camPosition";
const std::string CommonUniformsBinder::u_fogStart		= "u_fogStart";
const std::string CommonUniformsBinder::u_fogRange		= "u_fogRange";
const std::string CommonUniformsBinder::u_fogColor		= "u_fogColor";

//-----------------------------------------------------------------------------

CommonUniformsBinder::CommonUniformsBinder(
	const Shader& _shader,
	const ICamera& _camera,
	const Object& _object
) noexcept
	: m_shader(_shader)
	, m_camera(_camera)
	, m_object(_object)
{
}

//-----------------------------------------------------------------------------

void CommonUniformsBinder::setupCommon() const
{
	bindUniform(u_W, m_object.getWorldMatrix());
	bindUniform(u_WVP, m_camera.getViewProjectionMatrix() * m_object.getWorldMatrix());
	bindUniform(u_time, Globals::s_timeTotal);
	bindUniform(u_camPosition, m_camera.getPosition());
}

//-----------------------------------------------------------------------------

void CommonUniformsBinder::setupFog(const FogData& _fogData) const
{
	bindUniform(u_fogStart, _fogData.start);
	bindUniform(u_fogRange, _fogData.range);
	bindUniform(u_fogColor, _fogData.color);
}

//-----------------------------------------------------------------------------

template<typename T>
void CommonUniformsBinder::bindUniform(const std::string& _name, const T& _val) const
{
	if (m_shader.hasUniform(_name))
	{
		m_shader.setUniform(_name, _val);
	}
};

//-----------------------------------------------------------------------------

//if (m_bIsLighted)
//{
//	const AmbientLightData & ambientLightData = sceneMgr.getAmbientLightData();
//
//	m_shader->setUniform(uniforms.u_ambientColor, ambientLightData.color);
//	m_shader->setUniform(uniforms.u_ambientWeight, ambientLightData.weight);
//	
//	const std::vector<glm::vec4> & dirLightColors	= sceneMgr.getDirLightsColors();
//	const std::vector<glm::vec4> & pointLightColors	= sceneMgr.getPointLightsColors();
//	const std::vector<glm::vec3> & directions		= sceneMgr.getLightsDirections();
//	const std::vector<glm::vec3> & positions		= sceneMgr.getLightsPositions();
//
//	m_shader->setUniform(uniforms.u_dirLightColor,		dirLightColors.size(),		dirLightColors.data());
//	m_shader->setUniform(uniforms.u_pointLightColor,	pointLightColors.size(),	pointLightColors.data());
//	m_shader->setUniform(uniforms.u_lightDirection,	directions.size(),			directions.data());
//	m_shader->setUniform(uniforms.u_lightPosition,		positions.size(),			positions.data());
//}

//void Shader::initUniforms()
//{
//	memset(&m_uniforms, -1, sizeof(m_uniforms));
//
//	m_uniforms.u_WVP				= glGetUniformLocation(m_program, "u_WVP");
//
//	m_uniforms.u_W					= glGetUniformLocation(m_program, "u_W");
//	m_uniforms.u_camPosition		= glGetUniformLocation(m_program, "u_camPosition");
//
//	m_uniforms.u_fogStart			= glGetUniformLocation(m_program, "u_fogStart");
//	m_uniforms.u_fogRange			= glGetUniformLocation(m_program, "u_fogRange");
//	m_uniforms.u_fogColor			= glGetUniformLocation(m_program, "u_fogColor");
//
//	m_uniforms.u_depthAdjust		= glGetUniformLocation(m_program, "u_depthAdjust");
//	m_uniforms.u_tilingFactor		= glGetUniformLocation(m_program, "u_tilingFactor");
//	m_uniforms.u_dMax				= glGetUniformLocation(m_program, "u_dMax");
//	m_uniforms.u_depthDispl			= glGetUniformLocation(m_program, "u_depthDispl");
//	m_uniforms.u_color				= glGetUniformLocation(m_program, "u_color");
//
//	m_uniforms.u_ambientWeight		= glGetUniformLocation(m_program, "u_ambientWeight");
//	m_uniforms.u_ambientColor		= glGetUniformLocation(m_program, "u_ambientColor");
//	m_uniforms.u_specularPower		= glGetUniformLocation(m_program, "u_specularPower");
//
//	m_uniforms.u_dirLightColor		= glGetUniformLocation(m_program, "u_directionalLightColor");
//	m_uniforms.u_pointLightColor	= glGetUniformLocation(m_program, "u_pointLightColor");
//	m_uniforms.u_lightDirection		= glGetUniformLocation(m_program, "u_lightDirection");
//	m_uniforms.u_lightPosition		= glGetUniformLocation(m_program, "u_lightPosition");
//
//	m_uniforms.u_time				= glGetUniformLocation(m_program, "u_time");
//
//	m_uniforms.u_texture2D			= glGetUniformLocation(m_program, "u_texture2D");
//	m_uniforms.u_cubeTexture		= glGetUniformLocation(m_program, "u_cubeTexture");
//
//	m_uniforms.u_step				= glGetUniformLocation(m_program, "u_step");
//	m_uniforms.u_limit				= glGetUniformLocation(m_program, "u_limit");
//
//	m_uniforms.u_near				= glGetUniformLocation(m_program, "u_near");
//	m_uniforms.u_far				= glGetUniformLocation(m_program, "u_far");
//	m_uniforms.u_clarity			= glGetUniformLocation(m_program, "u_clarity");
//	m_uniforms.u_fade				= glGetUniformLocation(m_program, "u_fade");
//}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
