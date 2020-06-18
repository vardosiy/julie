#pragma once

#include <glm/glm.hpp>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

class ILightMoveController
{
public:
	~ILightMoveController() = default;

	virtual glm::vec3 calculatePos(float _dt, const glm::vec3& _originalPos) = 0;
};

//-----------------------------------------------------------------------------

class NoMoveController : public ILightMoveController
{
public:
	glm::vec3 calculatePos(float _dt, const glm::vec3& _originalPos) override {}
};

//-----------------------------------------------------------------------------

class CircularMoveController : public ILightMoveController
{
public:
	CircularMoveController(float _radius, float _moveSpeed) noexcept;

	glm::vec3 calculatePos(float _dt, const glm::vec3& _originalPos) override;

private:
	float m_radius;
	float m_moveSpeed;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
