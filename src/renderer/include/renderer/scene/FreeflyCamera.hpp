#pragma once

#include "renderer/Axis.hpp"
#include "renderer/scene/ICamera.hpp"

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

class FreeflyCamera : public ICamera
{
public:
	FreeflyCamera(float _near, float _far, float _fov);

	void update(float _dt) override;

	const glm::vec3& getPosition()				const noexcept override;
	const glm::mat4& getViewMatrix()			const noexcept override;
	const glm::mat4& getProjectionMatrix()		const noexcept override;
	const glm::mat4& getViewProjectionMatrix()	const noexcept override;

	float getNear()	const noexcept;
	float getFar()	const noexcept;
	float getFov()	const noexcept;

	void setAspect(float _val)			noexcept;
	void setMoveSpeed(float _val)		noexcept;
	void setRotationSpeed(float _val)	noexcept;

	void setPosition(const glm::vec3& _vec) noexcept;
	void setRotation(const glm::vec3& _vec) noexcept;
	void setUpVector(const glm::vec3& _vec) noexcept;

private:
	void move(const glm::vec3& _vec) noexcept;
	void rotate(const glm::vec2& _vec) noexcept;

	void recalculateMatrices();

	static glm::mat4 lookAt(
		const glm::vec3& _pos,
		const glm::vec3& _target,
		const glm::vec3& _upVector
	);

private:
	glm::vec3 m_pos;
	glm::vec3 m_target;
	glm::vec2 m_rotation;
	glm::vec3 m_upVector;

	float m_moveSpeed;
	float m_rotationSpeed;

	float m_aspect;
	float m_near;
	float m_far;
	float m_fov;

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
