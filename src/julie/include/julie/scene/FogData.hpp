#pragma once

#include <glm/vec4.hpp>

//-----------------------------------------------------------------------------
namespace jl {
//-----------------------------------------------------------------------------

struct FogData
{
	float		start{ 0.0f };
	float		range{ 0.0f };
	glm::vec4	color{ 1.0f };
};

//-----------------------------------------------------------------------------
} // namespace jl
//-----------------------------------------------------------------------------
