#pragma once

#include <glm/glm.hpp>
#include <string>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

class Model;
class Material;

class Object
{
//-----------------------------------------------------------------------------
public:
	Object(std::string _name) noexcept;
	~Object();

	const Model*		getModel() const noexcept;
	const Material*		getMaterial() const noexcept;
	const glm::mat4&	getWorldMatrix() const noexcept;
	const std::string&	getName() const noexcept;

	void setModel(const Model& _model) noexcept;
	void setMaterial(const Material& _material) noexcept;
	void setName(std::string _name) noexcept;

// transform data -------------------------------------------------------------
	const glm::vec3& getPosition() const noexcept;
	const glm::vec3& getRotation() const noexcept;
	const glm::vec3& getScale() const noexcept;

	void setPosition(const glm::vec3& _val) noexcept;
	void setRotation(const glm::vec3& _val) noexcept;
	void setScale(const glm::vec3& _val) noexcept;

//-----------------------------------------------------------------------------
private:
	struct TransformData
	{
		TransformData() noexcept
			: m_pos(0.0f)
			, m_scale(1.0f)
			, m_rotation(0.0f)
		{
		}

		glm::vec3 m_pos;
		glm::vec3 m_scale;
		glm::vec3 m_rotation;
	};

	static glm::mat4x4 calculateWorldMatrix(const TransformData& _transformData) noexcept;

//-----------------------------------------------------------------------------
	std::string m_name;

	const Model*	m_model;
	const Material*	m_material;

	TransformData		m_transformData;
	mutable glm::mat4	m_worldMatrix;
	mutable bool		m_bIsTransformChanged;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
