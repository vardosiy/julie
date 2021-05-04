#pragma once

#include "julie/scene/FogData.hpp"
#include "julie/scene/AmbientLightData.hpp"

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

#include <string>
#include <vector>

//-----------------------------------------------------------------------------
namespace jl {
//-----------------------------------------------------------------------------

class Camera;
class Shader;

class CommonUniformsBinder
{
public:
	CommonUniformsBinder(const Camera& _camera, const glm::mat4& _worldMat) noexcept;

	void setFog(const FogData& _fog) noexcept;
	void setAmbientLight(const AmbientLightData& _ambientLight) noexcept;

	void setLights(const std::vector<glm::vec3>& _positions, const std::vector<glm::vec3>& _colors) noexcept;

	void bind(const Shader& _shader) const noexcept;

private:
	const Camera& m_camera;
	const glm::mat4& m_worldMat;

	const FogData* m_fog;
	const AmbientLightData* m_ambientLight;

	const std::vector<glm::vec3>* m_lightPositions;
	const std::vector<glm::vec3>* m_lightColors;

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
