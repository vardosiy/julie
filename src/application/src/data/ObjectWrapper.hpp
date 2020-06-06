#pragma once

#include "renderer/scene/Object.hpp"

//-----------------------------------------------------------------------------

class ObjectWrapper
{
public:
	ObjectWrapper(jl::Object& _obj);

	ObjectWrapper(const ObjectWrapper& _rhs) = default;
	ObjectWrapper& operator= (const ObjectWrapper& _rhs) = default;

	jl::Object& getInternalObject() noexcept;
	const jl::Object& getInternalObject() const noexcept;

//-----------------------------------------------------------------------------
	const jl::Model*	getModel() const noexcept;
	const jl::Material*	getMaterial() const noexcept;
	const glm::mat4&	getWorldMatrix() const noexcept;
	const std::string&	getName() const noexcept;

	void setModel(const jl::Model* _model) noexcept;
	void setMaterial(const jl::Material* _material) noexcept;

//-----------------------------------------------------------------------------
	jl::s32 getRenderFlags() const noexcept;
	void setRenderFlags(jl::s32 _flags) noexcept;

	jl::s32 getTransformFlags() const noexcept;
	void setTransformFlags(jl::s32 _flags) noexcept;

//-----------------------------------------------------------------------------
	const glm::vec3& getPosition() const noexcept;
	const glm::vec3& getRotation() const noexcept;
	const glm::vec3& getScale() const noexcept;

	void setPosition(const glm::vec3& _val) noexcept;
	void setRotation(const glm::vec3& _val) noexcept;
	void setScale(const glm::vec3& _val) noexcept;

//-----------------------------------------------------------------------------
private:
	void recalcTransform();

//-----------------------------------------------------------------------------
private:
	jl::Object* m_object;

	glm::vec3 m_originOffset;
	glm::vec3 m_pos;

	glm::vec3 m_initialScale;
	glm::vec3 m_scale;
};

//-----------------------------------------------------------------------------

inline jl::Object& ObjectWrapper::getInternalObject() noexcept
{
	return *m_object;
}

inline const jl::Object& ObjectWrapper::getInternalObject() const noexcept
{
	return *m_object;
}

inline const jl::Model* ObjectWrapper::getModel() const noexcept
{
	return m_object->getModel();
}

inline const jl::Material* ObjectWrapper::getMaterial() const noexcept
{
	return m_object->getMaterial();
}

inline const glm::mat4& ObjectWrapper::getWorldMatrix() const noexcept
{
	return m_object->getWorldMatrix();
}

inline const std::string& ObjectWrapper::getName() const noexcept
{
	return m_object->getName();
}

inline void ObjectWrapper::setModel(const jl::Model* _model) noexcept
{
	m_object->setModel(_model);
	recalcTransform();
}

inline void ObjectWrapper::setMaterial(const jl::Material* _material) noexcept
{
	m_object->setMaterial(_material);
}

inline jl::s32 ObjectWrapper::getRenderFlags() const noexcept
{
	return m_object->getRenderFlags();
}

inline void ObjectWrapper::setRenderFlags(jl::s32 _flags) noexcept
{
	m_object->setRenderFlags(_flags);
}

inline jl::s32 ObjectWrapper::getTransformFlags() const noexcept
{
	return m_object->getTransformFlags();
}

inline void ObjectWrapper::setTransformFlags(jl::s32 _flags) noexcept
{
	m_object->setTransformFlags(_flags);
}

inline const glm::vec3& ObjectWrapper::getPosition() const noexcept
{
	return m_pos;
}

inline const glm::vec3& ObjectWrapper::getRotation() const noexcept
{
	return m_object->getRotation();
}

inline const glm::vec3& ObjectWrapper::getScale() const noexcept
{
	return m_scale;
}

inline void ObjectWrapper::setPosition(const glm::vec3& _val) noexcept
{
	m_pos = _val;
	m_object->setPosition(m_pos + m_originOffset);
}

inline void ObjectWrapper::setRotation(const glm::vec3& _val) noexcept
{
	return m_object->setRotation(_val);
}

inline void ObjectWrapper::setScale(const glm::vec3& _val) noexcept
{
	m_scale = _val;
	recalcTransform();
}

//-----------------------------------------------------------------------------
