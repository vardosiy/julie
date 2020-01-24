#pragma once

#include "renderer/Axis.hpp"

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

class ICamera
{
public:
	virtual void update(float _dt) = 0;

	virtual const glm::vec3& getPosition()				const noexcept = 0;
	virtual const glm::mat4& getViewMatrix()			const noexcept = 0;
	virtual const glm::mat4& getProjectionMatrix()		const noexcept = 0;
	virtual const glm::mat4& getViewProjectionMatrix()	const noexcept = 0;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
