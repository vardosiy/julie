#pragma once

#include <glm/vec4.hpp>

class AmbientLight
{
public:
	AmbientLight(const glm::vec4 & _color, float _weight);
	
	const glm::vec4 & getColor() const noexcept	{ return m_color; }
	float GetWeight() const noexcept			{ return m_weight; }

private:
	glm::vec4 m_color;
	float m_weight;
};
