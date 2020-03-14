#include "data/Object.hpp"
#include "data/Material.hpp"

#include "renderer/Axis.hpp"
#include "renderer/Shader.hpp"
#include "renderer/Model.hpp"
#include "renderer/scene/CommonUniformsBinder.hpp"

#include <glm/gtx/transform.hpp>

//-----------------------------------------------------------------------------

namespace data {

//-----------------------------------------------------------------------------

Object::Object(std::string _name) noexcept
	: DataEntity(std::move(_name))
	, m_model(nullptr)
	, m_material(nullptr)
	, m_pos(0.0f)
	, m_scale(1.0f)
	, m_rotation(0.0f)
	, m_worldMatrix(1.0f)
	, m_bIsTransformChanged(false)
{
}

//-----------------------------------------------------------------------------

Object::~Object() = default;

//-----------------------------------------------------------------------------

void Object::update(float _dt) noexcept
{
	if (m_bIsTransformChanged)
	{
		recalculateWorldMatrix();
		m_bIsTransformChanged = false;
	}
}

//-----------------------------------------------------------------------------

const jl::Material* Object::getMaterial() const noexcept
{
	return m_material ? &m_material->getMaterial() : nullptr;
}

//-----------------------------------------------------------------------------

const jl::Model* Object::getModel() const noexcept
{
	return m_model;
}

//-----------------------------------------------------------------------------

const glm::mat4& Object::getWorldMatrix() const noexcept
{
	return m_worldMatrix;
}

//-----------------------------------------------------------------------------

void Object::setMaterial(const Material& _material) noexcept
{
	m_material = &_material;
}

//-----------------------------------------------------------------------------

void Object::setModel(const jl::Model& _model) noexcept
{
	m_model = &_model;
}

//-----------------------------------------------------------------------------

const glm::vec3& Object::getPosition() const noexcept
{
	return m_pos;
}

//-----------------------------------------------------------------------------

const glm::vec3& Object::getRotation() const noexcept
{
	return m_rotation;
}

//-----------------------------------------------------------------------------

const glm::vec3& Object::getScale() const noexcept
{
	return m_scale;
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
		glm::rotate(m_rotation.x, jl::constants::axis::x) *
		glm::rotate(m_rotation.y, jl::constants::axis::y) *
		glm::rotate(m_rotation.z, jl::constants::axis::z);

	m_worldMatrix = translate * (rotation * scale);
}

//-----------------------------------------------------------------------------

} // namespace data

//-----------------------------------------------------------------------------
