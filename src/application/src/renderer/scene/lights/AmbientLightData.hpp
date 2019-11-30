#pragma once

#include <glm/vec4.hpp>

struct AmbientLightData
{
	AmbientLightData() noexcept = default;

	float		weight;
	glm::vec4	color;
};
