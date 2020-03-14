#pragma once

#include "renderer/Types.hpp"
#include "renderer/scene/FogData.hpp"

#include <glm/glm.hpp>

#include <string>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

class Camera;
class Shader;
class LightsHolder;
class IRenderable;

class CommonUniformsBinder
{
public:
	CommonUniformsBinder(const Shader& _shader) noexcept;

	void setupCommon(const jl::Camera& _camera, const glm::mat4x4& _worldMatrix) const noexcept;
	void setupFog(const FogData& _fogData) const noexcept;
	void setupLights(const LightsHolder& _lightsHolder) const noexcept;

private:
	template<typename T>
	void bindUniform(const std::string& _name, const T& _val) const noexcept;
	template<typename T>
	void bindUniform(const std::string& _name, const std::vector<T>& _val) const noexcept;

private:
	const Shader& m_shader;

	static const std::string u_W;
	static const std::string u_WVP;
	static const std::string u_time;
	static const std::string u_camPosition;
	static const std::string u_fogStart;
	static const std::string u_fogRange;
	static const std::string u_fogColor;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
