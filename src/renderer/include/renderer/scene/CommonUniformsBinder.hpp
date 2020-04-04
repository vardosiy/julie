#pragma once

#include "renderer/Types.hpp"

#include <glm/glm.hpp>

#include <string>
#include <vector>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

class Camera;
class Shader;
class LightsHolder;
struct FogData;

class CommonUniformsBinder
{
//-----------------------------------------------------------------------------
public:
	CommonUniformsBinder(const Shader& _shader) noexcept;

	void setupCommon(const jl::Camera& _camera, const glm::mat4x4& _worldMatrix) const noexcept;
	void setupFog(const FogData& _fogData) const noexcept;
	void setupLights(const LightsHolder& _lightsHolder) const noexcept;

//-----------------------------------------------------------------------------
private:
	template<typename T>
	void bindUniform(const std::string& _name, const T& _val) const noexcept;
	template<typename T>
	void bindUniform(const std::string& _name, const std::vector<T>& _val) const noexcept;

//-----------------------------------------------------------------------------
	const Shader& m_shader;

//-----------------------------------------------------------------------------
	static const std::string u_W;
	static const std::string u_WVP;
	static const std::string u_time;
	static const std::string u_camPosition;

	static const std::string u_fogStart;
	static const std::string u_fogRange;
	static const std::string u_fogColor;

	static const std::string u_ambientColor;
	static const std::string u_ambientWeight;

	static const std::string u_directionalLightColor;
	static const std::string u_lightDirection;

	static const std::string u_pointLightColor;
	static const std::string u_lightPosition;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
