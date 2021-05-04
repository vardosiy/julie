#include "julie/ecs/TransformProcessSystem.hpp"
#include "julie/ecs/ComponentsMgr.hpp"

#include "julie/Axis.hpp"

#include <glm/gtx/transform.hpp>

//-----------------------------------------------------------------------------
namespace jl::ecs {
//-----------------------------------------------------------------------------

void TransformProcessSystem::update(ComponentsMgr& _componentsMgr)
{
	_componentsMgr.forEach<TransformComponent, WorldMatComponent>([](TransformComponent& transform, WorldMatComponent& worldMat)
	{
		const glm::mat4 scale		= glm::scale(transform.scale);
		const glm::mat4 translate	= glm::translate(transform.pos);
		const glm::mat4 rotation	= TransformProcessSystem::rotationVecToMat(transform.rotation);

		worldMat.worldMat = translate * (rotation * scale);
	});
}

//-----------------------------------------------------------------------------

glm::mat4 TransformProcessSystem::rotationVecToMat(const glm::vec3& _rotation)
{
	return
		glm::rotate(_rotation.x, constants::axis::x) *
		glm::rotate(_rotation.y, constants::axis::y) *
		glm::rotate(_rotation.z, constants::axis::z);
}

//-----------------------------------------------------------------------------
} // namespace jl::ecs
//-----------------------------------------------------------------------------
