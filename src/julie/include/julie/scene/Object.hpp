#pragma once

#include "julie/core/Types.hpp"
#include "julie/Entity.hpp"

#include <glm/glm.hpp>
#include <string>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

class Camera;
class Model;

class Object : public Entity
{
//-----------------------------------------------------------------------------
public:
	Object() noexcept;
	~Object();

	Model* getModel() noexcept;
	const Model* getModel() const noexcept;
	void setModel(Model* _model) noexcept;

// transform data -------------------------------------------------------------
	const glm::mat4& getWorldMatrix() const noexcept;

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
		glm::vec3 m_pos{ 0.0f };
		glm::vec3 m_scale{ 1.0f };
		glm::vec3 m_rotation{ 0.0f };
	};

	static glm::mat4x4 calculateWorldMatrix(const TransformData& _transformData) noexcept;

//-----------------------------------------------------------------------------
	Model* m_model;

	TransformData		m_transformData;
	mutable bool		m_isTransformChanged;
	mutable glm::mat4	m_worldMatrix;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
