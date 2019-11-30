#pragma once

#include <glm/vec4.hpp>

struct FogData
{
	FogData() noexcept = default;

	float		start;
	float		range;
	glm::vec4	color;
};
