#pragma once

#include <glm/glm.hpp>

#include <memory>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

class ILightMoveController;

struct AmbientLightData
{
	glm::vec4	color;
	float		weight;
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
	std::unique_ptr<ILightMoveController> moveController;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
