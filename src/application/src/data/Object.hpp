#pragma once

#include "data/DataEntity.hpp"

#include "renderer/scene/IRenderable.hpp"

#include <glm/glm.hpp>

//-----------------------------------------------------------------------------

namespace jl {
class Model;
}

//-----------------------------------------------------------------------------

namespace data {

//-----------------------------------------------------------------------------

class Material;

class Object : public DataEntity, public jl::IRenderable
{
//-----------------------------------------------------------------------------
public:
	Object(std::string _name) noexcept;
	~Object();

// jl::IRenderable ------------------------------------------------------------
	void update(float _dt) noexcept override;

	const jl::Model*	getModel() const noexcept override;
	const jl::Material*	getMaterial() const noexcept override;
	const glm::mat4&	getWorldMatrix() const noexcept override;

//-----------------------------------------------------------------------------
	void setMaterial(const Material& _material) noexcept;
	void setModel(const jl::Model& _model) noexcept;

//-----------------------------------------------------------------------------
	const glm::vec3& getPosition() const noexcept;
	const glm::vec3& getRotation() const noexcept;
	const glm::vec3& getScale() const noexcept;

	void setPosition(const glm::vec3& _val) noexcept;
	void setRotation(const glm::vec3& _val) noexcept;
	void setScale(const glm::vec3& _val) noexcept;

//-----------------------------------------------------------------------------
private:
	void recalculateWorldMatrix();

//-----------------------------------------------------------------------------
	const jl::Model* m_model;
	const Material* m_material;

	glm::vec3 m_pos;
	glm::vec3 m_scale;
	glm::vec3 m_rotation;
	glm::mat4 m_worldMatrix;

	bool m_bIsTransformChanged;
};

//-----------------------------------------------------------------------------

} // namespace data

//-----------------------------------------------------------------------------
