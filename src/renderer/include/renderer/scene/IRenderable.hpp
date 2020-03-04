#pragma once

#include "glm/mat4x4.hpp"

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

class Camera;

class IRenderable
{
public:
	virtual ~IRenderable() = default;

	virtual void update(float _dt) = 0;
	virtual void render(const Camera& _camera) const noexcept = 0;

	virtual const glm::mat4& getWorldMatrix() const noexcept = 0;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
