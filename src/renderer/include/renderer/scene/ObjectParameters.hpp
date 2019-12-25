#pragma once

#include <glm/vec4.hpp>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

struct ObjectParameters
{
	float		specularPower;
	float		tilingFactor;
	float		dMax;
	float		depthDispl;
	float		depthAdjust;
	glm::vec4	color;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
