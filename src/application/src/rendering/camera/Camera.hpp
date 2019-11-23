#pragma once

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

class Camera
{
public:
	Camera(float _near, float _far, float _fov);

	void update(float _deltaTime);

	void setMoveSpeed(float _val) noexcept;
	void setRotationSpeed(float _val) noexcept;

	void setPosition(const glm::vec3 & _vec) noexcept;
	void setRotation(const glm::vec3 & _vec) noexcept;
	void setUpVector(const glm::vec3 & _vec) noexcept;

	float getNear() const noexcept					{ return m_near; }
	float getFar() const noexcept					{ return m_far; }
	const glm::vec3 & getPosition() const noexcept	{ return m_pos; }

	const glm::mat4 & getViewMatrix();
	const glm::mat4 & getProjectionMatrix();
	const glm::mat4 & getViewProjectionMatrix();

private:
	void calculateViewMatrix();

	void move(const glm::vec3 & _vec) noexcept;
	void rotate(const glm::vec3 & _vec) noexcept;

private:
	glm::vec3 m_pos;
	glm::vec3 m_upVector;
	glm::vec3 m_rotation;
	glm::vec3 m_target;

	float m_moveSpeed;
	float m_rotationSpeed;

	float m_near;
	float m_far;

	glm::mat4 m_viewMatrix;
	glm::mat4 m_projectionMatrix;
	glm::mat4 m_viewProjectionMatrix;

	bool m_bIsModified;

	static constexpr glm::vec3 k_camDirection{ 0.0f, 0.0f, -1.0f };
	static constexpr float k_maxCamRotationX{ 0.99999999f };
};
