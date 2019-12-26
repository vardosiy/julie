#pragma once

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <memory>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

class Light
{
public:
	enum class Type { Directional, Point };

public:
	Light(Type _type, const glm::vec3 & _posDir);

	void update(float _deltaTime);

	void setColor(const glm::vec4 & _val) noexcept	{ m_color = _val; }
	void setMoveSpeed(float _val) noexcept			{ m_moveSpeed = _val; }
	void setRadius(float _val) noexcept				{ m_radius = _val; }

	Type getType() const noexcept					{ return m_type; }
	const glm::vec3 & getPosDir() const noexcept	{ return m_posDir; }
	const glm::vec4 & getColor() const noexcept		{ return m_color; }

private:
	Type m_type;

	glm::vec3 m_originalPosDir;
	glm::vec3 m_posDir;
	glm::vec4 m_color;

	float m_moveSpeed;
	float m_radius;
	float m_angle;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
