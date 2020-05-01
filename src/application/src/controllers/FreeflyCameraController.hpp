#pragma once

namespace jl {
class Camera;
}

class FreeflyCameraController
{
public:
	FreeflyCameraController() noexcept;

	void update(float _dt) noexcept;

	void setCamera(jl::Camera* _camera) noexcept;

	void setCameraMoveSpeed(int _speed) noexcept;
	void setCameraRotateSpeed(int _speed) noexcept;

private:
	float m_camMoveSpeed;
	float m_camRotationSpeed;

	jl::Camera* m_camera;
};
