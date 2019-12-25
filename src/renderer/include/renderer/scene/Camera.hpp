#pragma once

#include "renderer/common/Axis.hpp"

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

class Camera
{
public:
	Camera(float _near, float _far, float _fov);

	void update(float _deltaTime);

	void setMoveSpeed(float _val) noexcept		{ m_moveSpeed = _val; }
	void setRotationSpeed(float _val) noexcept	{ m_rotationSpeed = _val; }

	void setPosition(const glm::vec3 & _vec) noexcept;
	void setRotation(const glm::vec3 & _vec) noexcept;
	void setUpVector(const glm::vec3 & _vec) noexcept;

	float getNear() const noexcept					{ return m_near; }
	float getFar() const noexcept					{ return m_far; }
	const glm::vec3 & getPosition() const noexcept	{ return m_pos; }

	const glm::mat4 & getViewMatrix() const noexcept;
	const glm::mat4 & getProjectionMatrix() const noexcept;
	const glm::mat4 & getViewProjectionMatrix() const noexcept;

private:
	void move(const glm::vec3 & _vec) noexcept;
	void rotate(const glm::vec2 & _vec) noexcept;

	void recalculateMatrices();

	static glm::mat4 lookAt(
		const glm::vec3 & _pos,
		const glm::vec3 & _target,
		const glm::vec3 & _upVector
	);

private:
	glm::vec3 m_pos;
	glm::vec3 m_target;
	glm::vec3 m_upVector;
	glm::vec2 m_rotation;

	float m_moveSpeed;
	float m_rotationSpeed;

	float m_near;
	float m_far;

	glm::mat4 m_viewMatrix;
	glm::mat4 m_projectionMatrix;
	glm::mat4 m_viewProjectionMatrix;

	bool m_bIsModified;

	static constexpr glm::vec3 k_camDirection = -constants::axis::z;
	static constexpr float k_maxCamRotationX = 0.99999999f;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
