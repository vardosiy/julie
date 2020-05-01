#include "controllers/FreeflyCameraController.hpp"

#include "managers/InputManager.hpp"

#include "renderer/scene/Camera.hpp"

//-----------------------------------------------------------------------------

FreeflyCameraController::FreeflyCameraController() noexcept
	: m_camMoveSpeed(1.0f)
	, m_camRotationSpeed(1.0f)
	, m_camera(nullptr)
{
}

//-----------------------------------------------------------------------------

void FreeflyCameraController::update(float _dt) noexcept
{
	if (!m_camera)
	{
		return;
	}

	InputManager& inputMgr = InputManager::getInstance();

	glm::vec3 camTraslation(0.0f);
	const float movePoints = m_camMoveSpeed * _dt;
	camTraslation.x += inputMgr.isPressed('D') * movePoints;
	camTraslation.x -= inputMgr.isPressed('A') * movePoints;
	camTraslation.y += inputMgr.isPressed('R') * movePoints;
	camTraslation.y -= inputMgr.isPressed('F') * movePoints;
	camTraslation.z += inputMgr.isPressed('S') * movePoints;
	camTraslation.z -= inputMgr.isPressed('W') * movePoints;

	if (camTraslation != glm::vec3(0.0f))
	{
		m_camera->move(camTraslation);
	}

	glm::vec2 camRotation(0.0f);
	const float rotatePoints = m_camRotationSpeed * _dt;
	camRotation.y += inputMgr.isPressed(InputManager::Arrows::Left)  * rotatePoints;
	camRotation.y -= inputMgr.isPressed(InputManager::Arrows::Right) * rotatePoints;
	camRotation.x += inputMgr.isPressed(InputManager::Arrows::Up)    * rotatePoints;
	camRotation.x -= inputMgr.isPressed(InputManager::Arrows::Down)  * rotatePoints;

	if (camRotation != glm::vec2(0.0f))
	{
		m_camera->rotate(camRotation);
	}

	m_camera->update();
}

//-----------------------------------------------------------------------------

void FreeflyCameraController::setCamera(jl::Camera* _camera) noexcept
{
	m_camera = _camera;
}

//-----------------------------------------------------------------------------

void FreeflyCameraController::setCameraMoveSpeed(int _speed) noexcept
{
	m_camMoveSpeed = static_cast<float>(_speed) * 0.01f;
}

//-----------------------------------------------------------------------------

void FreeflyCameraController::setCameraRotateSpeed(int _speed) noexcept
{
	m_camRotationSpeed = static_cast<float>(_speed) * 0.01f;
}

//-----------------------------------------------------------------------------
