#pragma once

#include <glm/vec4.hpp>

struct Parameters
{
	float specularPower;
	float tilingFactor;
	float dMax;
	float depthDispl;
	float depthAdjust;
	glm::vec4 color;
};
