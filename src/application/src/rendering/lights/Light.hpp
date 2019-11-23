#pragma once

#include "rendering/lights/LightType.hpp"

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <memory>

class Light
{
public:
	Light(LightType _type, const glm::vec3 & _posDir);

	void update(float _deltaTime);

	void setColor(const glm::vec4 & _val) noexcept	{ m_color = _val; }
	void setMoveSpeed(float _val) noexcept			{ m_moveSpeed = _val; }
	void setRadius(float _val) noexcept				{ m_radius = _val; }

	LightType getType() const noexcept				{ return m_type; }
	const glm::vec4 & getColor() const noexcept		{ return m_color; }
	const glm::vec3 & getPosDir() const noexcept	{ return m_posDir; }

private:
	LightType m_type;

	glm::vec3 m_originalPosDir;
	glm::vec4 m_color;
	glm::vec3 m_posDir;

	float m_moveSpeed;
	float m_radius;
	float m_angle;
};
