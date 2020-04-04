#include "Object.hpp"

#include "renderer/Axis.hpp"

#include <glm/gtx/transform.hpp>

//-----------------------------------------------------------------------------

Object::Object(std::string _name) noexcept
	: m_name(std::move(_name))
	, m_model(nullptr)
	, m_material(nullptr)
	, m_worldMatrix(1.0f)
	, m_bIsTransformChanged(false)
{
}

//-----------------------------------------------------------------------------

Object::~Object() = default;

//-----------------------------------------------------------------------------

const jl::Model* Object::getModel() const noexcept
{
	return m_model;
}

//-----------------------------------------------------------------------------

const jl::Material* Object::getMaterial() const noexcept
{
	return m_material;
}

//-----------------------------------------------------------------------------

const glm::mat4& Object::getWorldMatrix() const noexcept
{
	if (m_bIsTransformChanged)
	{
		m_worldMatrix = calculateWorldMatrix(m_transformData);
		m_bIsTransformChanged = false;
	}

	return m_worldMatrix;
}

//-----------------------------------------------------------------------------

void Object::setModel(const jl::Model& _model) noexcept
{
	m_model = &_model;
}

//-----------------------------------------------------------------------------

void Object::setMaterial(const jl::Material& _material) noexcept
{
	m_material = &_material;
}

//-----------------------------------------------------------------------------

const std::string& Object::getName() const noexcept
{
	return m_name;
}

//-----------------------------------------------------------------------------

void Object::setName(std::string _name) noexcept
{
	m_name = _name;
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
	m_bIsTransformChanged = true;
}

//-----------------------------------------------------------------------------

void Object::setRotation(const glm::vec3& _val) noexcept
{
	m_transformData.m_rotation = _val;
	m_bIsTransformChanged = true;
}

//-----------------------------------------------------------------------------

void Object::setScale(const glm::vec3& _val) noexcept
{
	m_transformData.m_scale = _val;
	m_bIsTransformChanged = true;
}

//-----------------------------------------------------------------------------

glm::mat4x4 Object::calculateWorldMatrix(const TransformData& _transformData) noexcept
{
	const glm::mat4 scale = glm::scale(_transformData.m_scale);
	const glm::mat4 translate = glm::translate(_transformData.m_pos);
	const glm::mat4 rotation =
		glm::rotate(_transformData.m_rotation.x, jl::constants::axis::x) *
		glm::rotate(_transformData.m_rotation.y, jl::constants::axis::y) *
		glm::rotate(_transformData.m_rotation.z, jl::constants::axis::z);

	return translate * (rotation * scale);
}

//-----------------------------------------------------------------------------
