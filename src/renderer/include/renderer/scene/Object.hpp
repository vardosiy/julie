#pragma once

#include "renderer/Types.hpp"

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
	enum RenderFlags
	{
		DrawModel		= 1 << 0,
		DrawBoundingBox	= 1 << 1,
		DrawAll			= DrawModel | DrawBoundingBox
	};

	enum TransfromFlags
	{
		Moveable		= 1 << 0,
		Scaleable		= 1 << 1,
		Rotatable		= 1 << 2,
		TransformAll	= Moveable | Scaleable | Rotatable
	};

//-----------------------------------------------------------------------------
	Object(std::string _name) noexcept;

	const Model*		getModel() const noexcept;
	const Material*		getMaterial() const noexcept;
	const glm::mat4&	getWorldMatrix() const noexcept;
	const std::string&	getName() const noexcept;

	s32 getRenderFlags() const noexcept;
	void setRenderFlags(s32 _flags) noexcept;

	s32 getTransformFlags() const noexcept;
	void setTransformFlags(s32 _flags) noexcept;

	void setModel(const Model* _model) noexcept;
	void setMaterial(const Material* _material) noexcept;
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
		glm::vec3 m_pos{ 0.0f };
		glm::vec3 m_scale{ 1.0f };
		glm::vec3 m_rotation{ 0.0f };
	};

	static glm::mat4x4 calculateWorldMatrix(const TransformData& _transformData) noexcept;

//-----------------------------------------------------------------------------
	std::string m_name;

	const Model* m_model;
	const Material* m_material;

	s32 m_renderFlags;
	s32 m_transformFlags;

	TransformData		m_transformData;
	mutable bool		m_isTransformChanged;
	mutable glm::mat4	m_worldMatrix;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
