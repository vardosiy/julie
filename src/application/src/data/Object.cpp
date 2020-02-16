#include "data/Object.hpp"
#include "data/Material.hpp"

#include "renderer/Axis.hpp"
#include "renderer/Shader.hpp"
#include "renderer/Model.hpp"

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

void Object::render(const jl::ICamera& _camera) const noexcept
{
	if (m_material && m_model)
	{
		m_material->bind();

		const jl::Shader* shader = m_material->getShader();
		if (shader)
		{
			//jl::CommonUniformsBinder uniformBinder(*shader, _camera, *this);
			//uniformBinder.setupCommon();
			//
			//if (m_fogData)
			//{
			//	uniformBinder.setupFog(*m_fogData);
			//}
		}

		//jl::Shader::draw(*m_model);
	}
}

//-----------------------------------------------------------------------------

const Material* Object::getMaterial() const noexcept
{
	return m_material;
}

//-----------------------------------------------------------------------------

const Model* Object::getModel() const noexcept
{
	return m_model;
}

//-----------------------------------------------------------------------------

void Object::setMaterial(const Material& _material) noexcept
{
	m_material = &_material;
}

//-----------------------------------------------------------------------------

void Object::setModel(const Model& _model) noexcept
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

const glm::mat4& Object::getWorldMatrix() const noexcept
{
	return m_worldMatrix;
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
