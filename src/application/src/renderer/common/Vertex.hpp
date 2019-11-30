#pragma once

#include <glm/glm.hpp>

struct Vertex
{
	glm::vec3 pos;
	glm::vec2 uv;
	glm::vec3 norm;
	glm::vec3 bitangent;
	glm::vec3 tangent;
};
