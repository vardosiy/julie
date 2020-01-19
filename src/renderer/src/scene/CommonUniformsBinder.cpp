#include "CommonUniformsBinder.hpp"

#include "renderer/Globals.hpp"
#include "renderer/Shader.hpp"
#include "renderer/scene/Scene.hpp"
#include "renderer/scene/Camera.hpp"
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
	const Shader & _shader,
	const Camera & _camera,
	const Object & _object
) noexcept
	: m_shader(_shader)
	, m_camera(_camera)
	, m_object(_object)
{
}

//-----------------------------------------------------------------------------

void CommonUniformsBinder::run()
{
	auto bindUniformFun = [this](const std::string & _name, const auto & _val)
	{
		if (m_shader.hasUniform(_name))
		{
			m_shader.setUniformValue(_name, _val);
		}
	};

	bindUniformFun(u_W, m_object.getWorldMatrix());
	bindUniformFun(u_WVP, m_camera.getViewProjectionMatrix() * m_object.getWorldMatrix());
	bindUniformFun(u_time, Globals::s_timeTotal);
	bindUniformFun(u_camPosition, m_camera.getPosition());

	const FogData * fogData = Scene::getInstance().getFogData();
	if (fogData)
	{
		bindUniformFun(u_fogStart, fogData->start);
		bindUniformFun(u_fogRange, fogData->range);
		bindUniformFun(u_fogColor, fogData->color);
	}
}

//if (m_bIsLighted)
//{
//	const AmbientLightData & ambientLightData = sceneMgr.getAmbientLightData();
//
//	m_shader->setUniformValue(uniforms.u_ambientColor, ambientLightData.color);
//	m_shader->setUniformValue(uniforms.u_ambientWeight, ambientLightData.weight);
//	
//	const std::vector<glm::vec4> & dirLightColors	= sceneMgr.getDirLightsColors();
//	const std::vector<glm::vec4> & pointLightColors	= sceneMgr.getPointLightsColors();
//	const std::vector<glm::vec3> & directions		= sceneMgr.getLightsDirections();
//	const std::vector<glm::vec3> & positions		= sceneMgr.getLightsPositions();
//
//	m_shader->setUniformValue(uniforms.u_dirLightColor,		dirLightColors.size(),		dirLightColors.data());
//	m_shader->setUniformValue(uniforms.u_pointLightColor,	pointLightColors.size(),	pointLightColors.data());
//	m_shader->setUniformValue(uniforms.u_lightDirection,	directions.size(),			directions.data());
//	m_shader->setUniformValue(uniforms.u_lightPosition,		positions.size(),			positions.data());
//}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
