#include "julie/scene/Object.hpp"
#include "julie/Axis.hpp"

#include <glm/gtx/transform.hpp>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

Object::Object() noexcept
	: m_model(nullptr)
	, m_renderFlags(RenderFlags::DrawModel)
	, m_worldMatrix(1.0f)
	, m_isTransformChanged(false)
{
}

//-----------------------------------------------------------------------------

Model* Object::getModel() const noexcept
{
	return m_model;
}

//-----------------------------------------------------------------------------

void Object::setModel(Model* _model) noexcept
{
	m_model = _model;
}

//-----------------------------------------------------------------------------

s32 Object::getRenderFlags() const noexcept
{
	return m_renderFlags;
}

//-----------------------------------------------------------------------------

void Object::setRenderFlags(s32 _flags) noexcept
{
	m_renderFlags = _flags;
}

//-----------------------------------------------------------------------------

const glm::mat4& Object::getWorldMatrix() const noexcept
{
	if (m_isTransformChanged)
	{
		m_worldMatrix = calculateWorldMatrix(m_transformData);
		m_isTransformChanged = false;
	}

	return m_worldMatrix;
}

//-----------------------------------------------------------------------------

const glm::vec3& Object::getPosition() const noexcept
{
	return m_transformData.m_pos;
}

//-----------------------------------------------------------------------------

const glm::vec3& Object::getRotation() const noexcept
{
	return m_transformData.m_rotation;
}

//-----------------------------------------------------------------------------

const glm::vec3& Object::getScale() const noexcept
{
	return m_transformData.m_scale;
}

//-----------------------------------------------------------------------------

void Object::setPosition(const glm::vec3& _val) noexcept
{
	m_transformData.m_pos = _val;
	m_isTransformChanged = true;
}

//-----------------------------------------------------------------------------

void Object::setRotation(const glm::vec3& _val) noexcept
{
	m_transformData.m_rotation = _val;
	m_isTransformChanged = true;
}

//-----------------------------------------------------------------------------

void Object::setScale(const glm::vec3& _val) noexcept
{
	m_transformData.m_scale = _val;
	m_isTransformChanged = true;
}

//-----------------------------------------------------------------------------

glm::mat4x4 Object::calculateWorldMatrix(const TransformData& _transformData) noexcept
{
	const glm::mat4 scale = glm::scale(_transformData.m_scale);
	const glm::mat4 translate = glm::translate(_transformData.m_pos);
	const glm::mat4 rotation =
		glm::rotate(_transformData.m_rotation.x, constants::axis::x) *
		glm::rotate(_transformData.m_rotation.y, constants::axis::y) *
		glm::rotate(_transformData.m_rotation.z, constants::axis::z);

	return translate * (rotation * scale);
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
