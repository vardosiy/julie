#pragma once

#include <glm/glm.hpp>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

struct AmbientLightData
{
	glm::vec4 color;
	float weight;
};

struct DirectionalLightData
{
	glm::vec4 color;
	glm::vec3 direction;
};

struct PointLightData
{
	glm::vec4 color;
	glm::vec3 position;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
