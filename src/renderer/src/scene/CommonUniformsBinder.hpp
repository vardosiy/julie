#pragma once

#include "renderer/Types.hpp"
#include "renderer/scene/FogData.hpp"
#include "renderer/scene/AmbientLightData.hpp"

#include <glm/glm.hpp>

#include <string>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

class Camera;
class Shader;
class Object;

class CommonUniformsBinder
{
public:
	static void run(const Shader & _shader, const Camera & _camera, const Object & _object);

private:
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
