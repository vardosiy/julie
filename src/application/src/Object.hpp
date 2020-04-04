#pragma once

#include "renderer/scene/IRenderable.hpp"

#include <glm/glm.hpp>
#include <string>

//-----------------------------------------------------------------------------

namespace jl {
class Model;
class Material;
}

//-----------------------------------------------------------------------------

class Object : public jl::IRenderable
{
//-----------------------------------------------------------------------------
public:
	Object(std::string _name) noexcept;
	~Object();

	void update(float _dt) noexcept override {}

	const jl::Model*	getModel() const noexcept override;
	const jl::Material*	getMaterial() const noexcept override;
	const glm::mat4&	getWorldMatrix() const noexcept override;

	void setModel(const jl::Model& _model) noexcept;
	void setMaterial(const jl::Material& _material) noexcept;

	const std::string& getName() const noexcept;
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

	const jl::Model*	m_model;
	const jl::Material*	m_material;

	TransformData		m_transformData;
	mutable glm::mat4	m_worldMatrix;
	mutable bool		m_bIsTransformChanged;
};

//-----------------------------------------------------------------------------
