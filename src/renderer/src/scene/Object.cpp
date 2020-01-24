#include "renderer/scene/Object.hpp"

#include "renderer/Axis.hpp"
#include "renderer/Model.hpp"
#include "renderer/Material.hpp"

#include <glm/gtx/transform.hpp>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

Object::Object(const Model& _model) noexcept
	: m_model(&_model)
	, m_material(nullptr)
	, m_pos(0.0f)
	, m_scale(1.0f)
	, m_rotation(0.0f)
	, m_worldMatrix(1.0f)
	, m_bIsTransformChanged(false)
{
}

//-----------------------------------------------------------------------------

void Object::update(float _dt)
{
	if (m_bIsTransformChanged)
	{
		recalculateWorldMatrix();
		m_bIsTransformChanged = false;
	}
}

//-----------------------------------------------------------------------------

void Object::setMaterial(const Material& _material) noexcept
{
	m_material = &_material;
}

//-----------------------------------------------------------------------------

void Object::setPosition(const glm::vec3& _val) noexcept
{
	m_pos = _val;
	m_bIsTransformChanged = true;
}

//-----------------------------------------------------------------------------

void Object::setRotation(const glm::vec3& _val) noexcept
{
	m_rotation = _val;
	m_bIsTransformChanged = true;
}

//-----------------------------------------------------------------------------

void Object::setScale(const glm::vec3& _val) noexcept
{
	m_scale = _val;
	m_bIsTransformChanged = true;
}

//-----------------------------------------------------------------------------

void Object::recalculateWorldMatrix()
{
	const glm::mat4 scale = glm::scale(m_scale);
	const glm::mat4 translate = glm::translate(m_pos);
	const glm::mat4 rotation =
		glm::rotate(m_rotation.x, constants::axis::x) *
		glm::rotate(m_rotation.y, constants::axis::y) *
		glm::rotate(m_rotation.z, constants::axis::z);

	m_worldMatrix = translate * (rotation * scale);
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
