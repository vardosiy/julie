#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

//-----------------------------------------------------------------------------
namespace jl {
//-----------------------------------------------------------------------------

struct rayf
{
	glm::vec3 start;
	glm::vec3 end;
};

//-----------------------------------------------------------------------------

struct aabbf
{
	//   ___________
	//  /|         /|
	// /_|________2 |
	// | |        | |
	// | 1________|_|
	// | /        | /
	// |/_________|/

	float getWidth() const noexcept		{ return max.x - min.x; }
	float getHeight() const noexcept	{ return max.y - min.y; }
	float getDepth() const noexcept		{ return max.z - min.z; }

	glm::vec3 min; // 1: left-bottom-far
	glm::vec3 max; // 2: right-top-close
};

inline aabbf operator*(const glm::mat4& _mat, const aabbf& _box)
{
	return aabbf{
		_mat * glm::vec4(_box.min, 1.0f),
		_mat * glm::vec4(_box.max, 1.0f)
	};
}

//-----------------------------------------------------------------------------
} // namespace jl
//-----------------------------------------------------------------------------
