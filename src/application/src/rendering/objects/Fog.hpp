#pragma once

#include <glm/vec4.hpp>

class Fog
{
public:
	Fog(float _start, float _range, const glm::vec4 & _color);

	float getStart() const noexcept				{ return m_start; }
	float getRange() const noexcept				{ return m_range; }
	const glm::vec4 & getColor() const noexcept	{ return m_color; }

private:
	float m_start;
	float m_range;
	glm::vec4 m_color;
};
