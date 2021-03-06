#pragma once

#include <glm/glm.hpp>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

struct AmbientLightData
{
	glm::vec3 color;
	float weight;
};

struct DirectionalLightData
{
	glm::vec3 color;
	glm::vec3 direction;
};

struct PointLightData
{
	glm::vec3 color;
	glm::vec3 position;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
