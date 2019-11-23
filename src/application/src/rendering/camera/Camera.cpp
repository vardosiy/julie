#include "rendering/camera/Camera.hpp"
#include "rendering/common/Globals.hpp"

#include "rendering/managers/InputManager.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include <algorithm>

//-----------------------------------------------------------------------------

Camera::Camera(float _near, float _far, float _fov)
	: m_moveSpeed(0.1f)
	, m_rotationSpeed(0.1f)
	, m_bIsModified(true)
	, m_near(_near)
	, m_far(_far)
{
	const float aspect = static_cast<float>(Globals::s_screenWidth) / static_cast<float>(Globals::s_screenHeight);
	m_projectionMatrix = glm::perspective(_fov, aspect, _near, _far);
}

//-----------------------------------------------------------------------------

void Camera::update(float _deltaTime)
{
	InputManager & inputMgr = InputManager::getInstance();

	glm::vec3 camTraslation(0.0f, 0.0f, 0.0f);
	const float movePoints = m_moveSpeed * _deltaTime;
	camTraslation.x += inputMgr.isPressed('D') * movePoints;
	camTraslation.x -= inputMgr.isPressed('A') * movePoints;
	camTraslation.y += inputMgr.isPressed('R') * movePoints;
	camTraslation.y -= inputMgr.isPressed('F') * movePoints;
	camTraslation.z += inputMgr.isPressed('S') * movePoints;
	camTraslation.z -= inputMgr.isPressed('W') * movePoints;

	if (camTraslation.x != 0.0f || camTraslation.y != 0.0f || camTraslation.z != 0.0f)
	{
		move(camTraslation);
	}

	glm::vec3 camRotation(0.0f, 0.0f, 0.0f);
	const float rotatePoints = m_rotationSpeed * _deltaTime;
	camRotation.y += inputMgr.isPressed(Arrows::Left)  * rotatePoints;
	camRotation.y -= inputMgr.isPressed(Arrows::Rigth) * rotatePoints;
	camRotation.x += inputMgr.isPressed(Arrows::Up)    * rotatePoints;
	camRotation.x -= inputMgr.isPressed(Arrows::Down)  * rotatePoints;

	if (camRotation.x != 0.0f || camRotation.y != 0.0f)
	{
		rotate(camRotation);
	}
}

//-----------------------------------------------------------------------------

void Camera::setMoveSpeed(float _val) noexcept
{
	m_moveSpeed = _val;
}

//-----------------------------------------------------------------------------

void Camera::setRotationSpeed(float _val) noexcept
{
	m_rotationSpeed = _val;
}

//-----------------------------------------------------------------------------

void Camera::setPosition(const glm::vec3 & _vec) noexcept
{
	m_pos = _vec;
	m_target = m_pos + k_camDirection;
	m_bIsModified = true;
}

//-----------------------------------------------------------------------------

void Camera::setRotation(const glm::vec3 & _vec) noexcept
{
	m_rotation = _vec;
	rotate(glm::vec3(0.0f, 0.0f, 0.0f));
}

//-----------------------------------------------------------------------------

void Camera::setUpVector(const glm::vec3 & _vec) noexcept
{
	m_upVector = _vec;
	m_bIsModified = true;
}

//-----------------------------------------------------------------------------

const glm::mat4 & Camera::getViewMatrix()
{
	if (m_bIsModified)
	{
		calculateViewMatrix();
		m_bIsModified = false;
	}

	return m_viewMatrix;
}

//-----------------------------------------------------------------------------

const glm::mat4 & Camera::getProjectionMatrix()
{
	return m_projectionMatrix;
}

//-----------------------------------------------------------------------------

const glm::mat4 & Camera::getViewProjectionMatrix()
{
	if (m_bIsModified)
	{
		calculateViewMatrix();

		m_viewProjectionMatrix = m_viewMatrix * m_projectionMatrix;
		m_bIsModified = false;
	}

	return m_viewProjectionMatrix;
}

//-----------------------------------------------------------------------------

void Camera::calculateViewMatrix()
{
	const glm::vec3 zAxis = glm::normalize(m_pos - m_target);
	const glm::vec3 xAxis = glm::normalize(glm::cross(m_upVector, zAxis));
	const glm::vec3 yAxis = glm::normalize(glm::cross(zAxis, xAxis));

	const float dotX = glm::dot(m_pos, xAxis);
	const float dotY = glm::dot(m_pos, yAxis);
	const float dotZ = glm::dot(m_pos, zAxis);

	// for shorter name
	glm::mat4 &m = m_viewMatrix;
	m[0][0] = xAxis.x; m[0][1] = yAxis.x; m[0][2] = zAxis.x; m[0][3] = 0.0f;
	m[1][0] = xAxis.y; m[1][1] = yAxis.y; m[1][2] = zAxis.y; m[1][3] = 0.0f;
	m[2][0] = xAxis.z; m[2][1] = yAxis.z; m[2][2] = zAxis.z; m[2][3] = 0.0f;
	m[3][0] =   -dotX; m[3][1] =   -dotY; m[3][2] =   -dotZ; m[3][3] = 1.0f;
}

//-----------------------------------------------------------------------------

void Camera::move(const glm::vec3 & _vec) noexcept
{
	const glm::mat4 & m = m_viewMatrix;
	const glm::vec3 xAxis(m[0][0], m[1][0], m[2][0]);
	const glm::vec3 zAxis(m[0][2], m[1][2], m[2][2]);

	m_pos += xAxis * _vec.x + zAxis * _vec.z;
	m_target += xAxis * _vec.x + zAxis * _vec.z;

	m_pos.y += _vec.y;
	m_target.y += _vec.y;

	m_bIsModified = true;
}

//-----------------------------------------------------------------------------

void Camera::rotate(const glm::vec3 & _vec) noexcept
{
	m_rotation += _vec;
	m_rotation.x = std::clamp(m_rotation.x, -k_maxCamRotationX, k_maxCamRotationX);

	const glm::mat4 rotX = glm::rotate(glm::mat4(), m_rotation.x, glm::vec3{ 1.0f, 0.0f, 0.0f });
	const glm::mat4 rotY = glm::rotate(glm::mat4(), m_rotation.y, glm::vec3{ 0.0f, 1.0f, 0.0f });

	const glm::vec4 rotated = glm::vec4(k_camDirection, 1.0) * rotX * rotY;
	m_target = m_pos + glm::vec3(rotated.x, rotated.y, rotated.z);

	m_bIsModified = true;
}

//-----------------------------------------------------------------------------
