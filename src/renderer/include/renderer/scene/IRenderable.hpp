#pragma once

#include "glm/mat4x4.hpp"

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

class Material;
class Model;

class IRenderable
{
public:
	virtual ~IRenderable() = default;

	virtual void update(float _dt) = 0;

	virtual const jl::Model*	getModel() const noexcept = 0;
	virtual const jl::Material*	getMaterial() const noexcept = 0;
	virtual const glm::mat4&	getWorldMatrix() const noexcept = 0;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
