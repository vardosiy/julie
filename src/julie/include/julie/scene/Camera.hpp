#pragma once

#include "julie/Axis.hpp"

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

//-----------------------------------------------------------------------------
	float getAspect() const noexcept	{ return m_aspect; }
	float getNear() const noexcept		{ return m_near; }
	float getFar() const noexcept		{ return m_far; }
	float getFov() const noexcept		{ return m_fov; }

	void setAspect(float _val) noexcept;
	void setNear(float _val) noexcept;
	void setFar(float _val) noexcept;
	void setFov(float _val) noexcept;

//-----------------------------------------------------------------------------
	const glm::vec3& getPosition() const noexcept	{ return m_pos; }
	const glm::vec3& getViewTarget() const noexcept	{ return m_target; }

	void setPosition(const glm::vec3& _vec) noexcept;
	void setRotation(const glm::vec3& _vec) noexcept;

//-----------------------------------------------------------------------------
	const glm::mat4& getViewMatrix() const noexcept;
	const glm::mat4& getProjectionMatrix() const noexcept;
	const glm::mat4& getViewProjectionMatrix() const noexcept;

	void move(const glm::vec3& _vec) noexcept;
	void rotate(const glm::vec2& _vec) noexcept;
	
//-----------------------------------------------------------------------------
private:
	static glm::mat4 lookAt(
		const glm::vec3& _pos,
		const glm::vec3& _target,
		const glm::vec3& _upVector
	);
	
//-----------------------------------------------------------------------------
	glm::vec3 m_pos{ 0.0f };
	glm::vec2 m_rotation{ 1.0f };
	glm::vec3 m_target{ k_camDirection };

	float m_aspect{ 1.0f };
	float m_near{ 0.0f };
	float m_far{ 1.0f };
	float m_fov{ 1.0f };

	mutable glm::mat4 m_viewMatrix{ 1.0f };
	mutable glm::mat4 m_projectionMatrix{ 1.0f };
	mutable glm::mat4 m_viewProjectionMatrix{ 1.0f };

	mutable bool m_isTransformModified{ true };
	mutable bool m_isProjectionModified{ true };

	static constexpr glm::vec3 k_camDirection = -constants::axis::z;
	static constexpr float k_maxCamRotationX = 0.99999999f;
};

//-----------------------------------------------------------------------------
} // namespace jl
//-----------------------------------------------------------------------------
