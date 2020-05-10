#pragma once

#include "renderer/Axis.hpp"

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

class Camera
{
//-----------------------------------------------------------------------------
public:
	Camera(float _near, float _far, float _fov);

	void update();

	const glm::vec3& getPosition()				const noexcept;
	const glm::vec3& getViewTarget()			const noexcept;
	const glm::mat4& getViewMatrix()			const noexcept;
	const glm::mat4& getProjectionMatrix()		const noexcept;
	const glm::mat4& getViewProjectionMatrix()	const noexcept;

	float getNear()	const noexcept;
	float getFar()	const noexcept;
	float getFov()	const noexcept;

	void setAspect(float _val) noexcept;

	void setPosition(const glm::vec3& _vec) noexcept;
	void setRotation(const glm::vec3& _vec) noexcept;
	void setUpVector(const glm::vec3& _vec) noexcept;

	void move(const glm::vec3& _vec) noexcept;
	void rotate(const glm::vec2& _vec) noexcept;
	
//-----------------------------------------------------------------------------
private:
	void recalculateMatrices();

	static glm::mat4 lookAt(
		const glm::vec3& _pos,
		const glm::vec3& _target,
		const glm::vec3& _upVector
	);
	
//-----------------------------------------------------------------------------
	glm::vec3 m_pos;
	glm::vec3 m_target;
	glm::vec3 m_upVector;
	glm::vec2 m_rotation;

	float m_aspect;
	float m_near;
	float m_far;
	float m_fov;

	glm::mat4 m_viewMatrix;
	glm::mat4 m_projectionMatrix;
	glm::mat4 m_viewProjectionMatrix;

	bool m_bIsModified;

//-----------------------------------------------------------------------------
	static constexpr glm::vec3 k_camDirection = -constants::axis::z;
	static constexpr float k_maxCamRotationX = 0.99999999f;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
