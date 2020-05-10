#pragma once

#include <cstdint>

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

using s8 = int8_t;
using u8 = uint8_t;

using s16 = int16_t;
using u16 = uint16_t;

using s32 = int32_t;
using u32 = uint32_t;

using s64 = int64_t;
using u64 = uint64_t;

//-----------------------------------------------------------------------------

struct rayf
{
	glm::vec3 start;
	glm::vec3 end;
};

//-----------------------------------------------------------------------------

struct boxf
{
	//   ___________
	//  /|         /|
	// /_|________2 |
	// | |        | |
	// | 1________|_|
	// | /        | /
	// |/_________|/

	glm::vec3 min; // 1: left-bottom-far
	glm::vec3 max; // 2: right-top-close
};

inline boxf operator*(const glm::mat4& _mat, const boxf& _box)
{
	return jl::boxf{
		_mat * glm::vec4(_box.min, 1.0f),
		_mat * glm::vec4(_box.max, 1.0f)
	};
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
