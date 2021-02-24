#pragma once

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

//-----------------------------------------------------------------------------
namespace jl {
//-----------------------------------------------------------------------------

struct Vertex
{
	glm::vec3 pos;
	glm::vec2 uv;
	glm::vec3 norm;
	glm::vec3 bitangent;
	glm::vec3 tangent;
};

//-----------------------------------------------------------------------------
} // namespace jl
//-----------------------------------------------------------------------------
