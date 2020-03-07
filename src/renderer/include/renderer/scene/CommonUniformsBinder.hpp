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
class Object;
class IRenderable;

class CommonUniformsBinder
{
public:
	CommonUniformsBinder(const Shader& _shader, const Camera& _camera, const IRenderable& _renderable) noexcept;

	void setupCommon() const;
	void setupFog(const FogData& _fogData) const;

private:
	template<typename T>
	void bindUniform(const std::string& _name, const T& _val) const;

private:
	const Shader& m_shader;
	const Camera& m_camera;
	const IRenderable& m_renderable;

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
