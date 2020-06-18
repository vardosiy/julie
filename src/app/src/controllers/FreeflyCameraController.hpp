#pragma once

namespace jl {
class Camera;
}

class FreeflyCameraController
{
public:
	FreeflyCameraController() noexcept;

	void update(float _dt) noexcept;

	const jl::Camera* getCamera() const noexcept;
	void setCamera(jl::Camera* _camera) noexcept;

	float getCameraMoveSpeed() const noexcept;
	float getCameraRotateSpeed() const noexcept;

	void setCameraMoveSpeed(float _value) noexcept;
	void setCameraRotateSpeed(float _value) noexcept;

private:
	float m_camMoveSpeed;
	float m_camRotationSpeed;

	jl::Camera* m_camera;
};
