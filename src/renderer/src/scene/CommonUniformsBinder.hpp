#pragma once

#include "renderer/Types.hpp"
#include "renderer/scene/FogData.hpp"
#include "renderer/scene/AmbientLightData.hpp"

#include <glm/glm.hpp>

#include <string>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

class ICamera;
class Shader;
class Object;

class CommonUniformsBinder
{
public:
	CommonUniformsBinder(const Shader& _shader, const ICamera& _camera, const Object& _object) noexcept;

	void setupCommon() const;
	void setupFog(const FogData& _fogData) const;

private:
	template<typename T>
	void bindUniform(const std::string& _name, const T& _val) const;

private:
	const Shader& m_shader;
	const ICamera& m_camera;
	const Object& m_object;

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
