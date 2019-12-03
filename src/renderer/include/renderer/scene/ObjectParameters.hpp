#pragma once

#include <glm/vec4.hpp>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

struct ObjectParameters
{
	ObjectParameters() noexcept = default;

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
