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

void CommonUniformsBinder::run(const Shader & _shader, const Camera & _camera, const Object & _object)
{
	auto bindUniformFun = [&_shader](const std::string & _name, const auto & _val)
	{
		if (_shader.hasUniform(_name))
		{
			_shader.setUniformValue(_name, _val);
		}
	};

	bindUniformFun(u_W, _object.getWorldMatrix());
	bindUniformFun(u_WVP, _camera.getViewProjectionMatrix() * _object.getWorldMatrix());
	bindUniformFun(u_time, Globals::s_timeTotal);
	bindUniformFun(u_camPosition, _camera.getPosition());

	const FogData & fogData = Scene::getInstance().getFogData();
	bindUniformFun(u_fogStart, fogData.start);
	bindUniformFun(u_fogRange, fogData.range);
	bindUniformFun(u_fogColor, fogData.color);
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
