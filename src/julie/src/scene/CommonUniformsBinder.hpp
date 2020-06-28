#pragma once

#include <glm/mat4x4.hpp>

#include <string>
#include <vector>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

class Scene;
class Camera;
class Shader;
class LightsHolder;

class CommonUniformsBinder
{
public:
	CommonUniformsBinder(
		const Scene& _scene,
		const Camera& _camera,
		const glm::mat4& _worldMatrix
	) noexcept;

	void bind(const Shader& _shader) const noexcept;

private:
	const Scene& m_scene;
	const Camera& m_camera;
	const glm::mat4& m_worldMatrix;

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
	static const std::string u_pointLightColor;
	static const std::string u_lightPosition;
	static const std::string u_directionalLightColor;
	static const std::string u_lightDirection;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
