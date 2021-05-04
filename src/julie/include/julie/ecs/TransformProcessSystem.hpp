#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

//-----------------------------------------------------------------------------
namespace jl::ecs {
//-----------------------------------------------------------------------------

class ComponentsMgr;

class TransformProcessSystem
{
public:
	void update(ComponentsMgr& _componentsMgr);

private:
	static glm::mat4 rotationVecToMat(const glm::vec3& _rotation);
};

//-----------------------------------------------------------------------------
} // namespace jl::ecs
//-----------------------------------------------------------------------------
