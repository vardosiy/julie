#include "renderer/scene/FreeflyCamera.hpp"

#include "renderer/managers/InputManager.hpp"
#include "renderer/Axis.hpp"

#include <glm/gtx/transform.hpp>

#include <algorithm>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

FreeflyCamera::FreeflyCamera(float _near, float _far, float _fov)
	: m_pos(0.0f)
	, m_target(k_camDirection)
	, m_rotation(0.0f)
	, m_upVector(0.0f)
	, m_moveSpeed(0.1f)
	, m_rotationSpeed(0.001f)
	, m_bIsModified(true)
	, m_aspect(1.0f)
	, m_near(_near)
	, m_far(_far)
	, m_fov(_fov)
	, m_viewMatrix(1.0f)
	, m_projectionMatrix(1.0f)
	, m_viewProjectionMatrix(1.0f)
{
}

//-----------------------------------------------------------------------------

void FreeflyCamera::update(float _dt)
{
	InputManager& inputMgr = InputManager::getInstance();

	glm::vec3 camTraslation(0.0f);
	const float movePoints = m_moveSpeed * _dt;
	camTraslation.x += inputMgr.isPressed('D') * movePoints;
	camTraslation.x -= inputMgr.isPressed('A') * movePoints;
	camTraslation.y += inputMgr.isPressed('R') * movePoints;
	camTraslation.y -= inputMgr.isPressed('F') * movePoints;
	camTraslation.z += inputMgr.isPressed('S') * movePoints;
	camTraslation.z -= inputMgr.isPressed('W') * movePoints;

	if (camTraslation != glm::vec3(0.0f))
	{
		move(camTraslation);
	}

	glm::vec2 camRotation(0.0f);
	const float rotatePoints = m_rotationSpeed * _dt;
	camRotation.y += inputMgr.isPressed(Arrows::Left)  * rotatePoints;
	camRotation.y -= inputMgr.isPressed(Arrows::Right) * rotatePoints;
	camRotation.x += inputMgr.isPressed(Arrows::Up)    * rotatePoints;
	camRotation.x -= inputMgr.isPressed(Arrows::Down)  * rotatePoints;

	if (camRotation != glm::vec2(0.0f))
	{
		rotate(camRotation);
	}

	if (m_bIsModified)
	{
		recalculateMatrices();
		m_bIsModified = false;
	}
}

//-----------------------------------------------------------------------------

const glm::vec3& FreeflyCamera::getPosition() const noexcept
{
	return m_pos;
}

//-----------------------------------------------------------------------------

const glm::mat4& FreeflyCamera::getViewMatrix() const noexcept
{
	return m_viewMatrix;
}

//-----------------------------------------------------------------------------

const glm::mat4& FreeflyCamera::getProjectionMatrix() const noexcept
{
	return m_projectionMatrix;
}

//-----------------------------------------------------------------------------

const glm::mat4& FreeflyCamera::getViewProjectionMatrix() const noexcept
{
	return m_viewProjectionMatrix;
}

//-----------------------------------------------------------------------------

float FreeflyCamera::getNear() const noexcept
{
	return m_near;
}

//-----------------------------------------------------------------------------

float FreeflyCamera::getFar() const noexcept
{
	return m_far;
}

//-----------------------------------------------------------------------------

float FreeflyCamera::getFov() const noexcept
{
	return m_fov;
}

//-----------------------------------------------------------------------------

void FreeflyCamera::setAspect(float _val) noexcept
{
	m_aspect = _val;
	m_bIsModified = true;
}

//-----------------------------------------------------------------------------

void FreeflyCamera::setMoveSpeed(float _val) noexcept
{
	m_moveSpeed = _val;
}

//-----------------------------------------------------------------------------

void FreeflyCamera::setRotationSpeed(float _val) noexcept
{
	m_rotationSpeed = _val;
}

//-----------------------------------------------------------------------------

void FreeflyCamera::setPosition(const glm::vec3& _vec) noexcept
{
	m_pos = _vec;
	m_target = m_pos + k_camDirection;
	m_bIsModified = true;
}

//-----------------------------------------------------------------------------

void FreeflyCamera::setRotation(const glm::vec3& _vec) noexcept
{
	m_rotation = _vec;
	rotate(glm::vec2(0.0f, 0.0f));
}

//-----------------------------------------------------------------------------

void FreeflyCamera::setUpVector(const glm::vec3& _vec) noexcept
{
	m_upVector = _vec;
	m_bIsModified = true;
}

//-----------------------------------------------------------------------------

void FreeflyCamera::move(const glm::vec3& _vec) noexcept
{
	const glm::mat4& m = m_viewMatrix;
	const glm::vec3 xAxis(m[0][0], m[1][0], m[2][0]);
	const glm::vec3 zAxis(m[0][2], m[1][2], m[2][2]);

	m_pos += xAxis * _vec.x + zAxis * _vec.z;
	m_target += xAxis * _vec.x + zAxis * _vec.z;

	m_pos.y += _vec.y;
	m_target.y += _vec.y;

	m_bIsModified = true;
}

//-----------------------------------------------------------------------------

void FreeflyCamera::rotate(const glm::vec2& _vec) noexcept
{
	m_rotation += _vec;
	m_rotation.x = std::clamp(m_rotation.x, -k_maxCamRotationX, k_maxCamRotationX);

	const glm::mat4 xRotationMat = glm::rotate(m_rotation.x, constants::axis::x);
	const glm::mat4 yRotationMat = glm::rotate(m_rotation.y, constants::axis::y);

	const glm::vec4 rotated = yRotationMat * (xRotationMat * glm::vec4(k_camDirection, 1.0));
	m_target = m_pos + glm::vec3(rotated.x, rotated.y, rotated.z);

	m_bIsModified = true;
}

//-----------------------------------------------------------------------------

void FreeflyCamera::recalculateMatrices()
{
	m_viewMatrix			= lookAt(m_pos, m_target, constants::axis::y);
	m_projectionMatrix		= glm::perspective(glm::radians(m_fov), m_aspect, m_near, m_far);
	m_viewProjectionMatrix	= m_projectionMatrix * m_viewMatrix;
}

//-----------------------------------------------------------------------------

glm::mat4 FreeflyCamera::lookAt(
	const glm::vec3& _pos,
	const glm::vec3& _target,
	const glm::vec3& _upVector
)
{
	const glm::vec3 zAxis = glm::normalize(_pos - _target);
	const glm::vec3 xAxis = glm::normalize(glm::cross(_upVector, zAxis));
	const glm::vec3 yAxis = glm::normalize(glm::cross(zAxis, xAxis));

	const float dotX = glm::dot(_pos, xAxis);
	const float dotY = glm::dot(_pos, yAxis);
	const float dotZ = glm::dot(_pos, zAxis);

	glm::mat4 m;
	m[0][0] = xAxis.x; m[0][1] = yAxis.x; m[0][2] = zAxis.x; m[0][3] = 0.0f;
	m[1][0] = xAxis.y; m[1][1] = yAxis.y; m[1][2] = zAxis.y; m[1][3] = 0.0f;
	m[2][0] = xAxis.z; m[2][1] = yAxis.z; m[2][2] = zAxis.z; m[2][3] = 0.0f;
	m[3][0] =   -dotX; m[3][1] =   -dotY; m[3][2] =   -dotZ; m[3][3] = 1.0f;

	return m;
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
