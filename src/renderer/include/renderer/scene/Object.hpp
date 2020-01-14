#pragma once

#include "renderer/Types.hpp"

#include <glm/glm.hpp>

#include <vector>
#include <memory>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

class Camera;
class Model;
class Material;

class Object
{
public:
	Object(const Model & _model) noexcept;

	void update(float _dt);

	const Model &		getModel()			const noexcept { return *m_model; }
	const Material *	getMaterial()		const noexcept { return m_material; }
	const glm::vec3 &	getPosition()		const noexcept { return m_pos; }
	const glm::vec3 &	getRotation()		const noexcept { return m_rotation; }
	const glm::vec3 &	getScale()			const noexcept { return m_scale; }
	const glm::mat4 &	getWorldMatrix()	const noexcept { return m_worldMatrix; }

	void setMaterial(const Material & _material) noexcept;
	void setPosition(const glm::vec3 & _val) noexcept;
	void setRotation(const glm::vec3 & _val) noexcept;
	void setScale(const glm::vec3 & _val) noexcept;

private:
	void recalculateWorldMatrix();

private:
	const Model * m_model;
	const Material * m_material;

	glm::vec3 m_pos;
	glm::vec3 m_scale;
	glm::vec3 m_rotation;
	glm::mat4 m_worldMatrix;

	bool m_bIsTransformChanged;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
