#include "julie/ecs/TransformProcessSystem.hpp"
#include "julie/ecs/ComponentsMgr.hpp"

#include "julie/Axis.hpp"

#include <glm/gtx/transform.hpp>

//-----------------------------------------------------------------------------
namespace jl::ecs {
//-----------------------------------------------------------------------------

TransformProcessSystem::TransformProcessSystem(ComponentsMgr& _componentsMgr)
	: m_componentsMgr(_componentsMgr)
{
}

//-----------------------------------------------------------------------------

void TransformProcessSystem::update()
{
	auto view = m_componentsMgr.view<TransformComponent>();

	for (TransformComponent& item : view.m_containerRef)
	{
		const glm::mat4 scale		= glm::scale(item.scale);
		const glm::mat4 translate	= glm::translate(item.pos);
		const glm::mat4 rotation	= rotationVecToMat(item.rotation);

		item.worldMat = translate * (rotation * scale);
	}
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
