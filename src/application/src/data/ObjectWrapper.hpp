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
	const glm::mat4&	getWorldMatrix() const noexcept;
	const std::string&	getName() const noexcept;

	void setModel(const jl::Model* _model) noexcept;

//-----------------------------------------------------------------------------
	jl::s32 getRenderFlags() const noexcept;
	void setRenderFlags(jl::s32 _flags) noexcept;

	jl::s32 getTransformFlags() const noexcept;
	void setTransformFlags(jl::s32 _flags) noexcept;

//-----------------------------------------------------------------------------
	const glm::vec3& getPosition() const noexcept;
	const glm::vec3& getRotation() const noexcept;
	const glm::vec3& getSize() const noexcept;

	void setPosition(const glm::vec3& _val) noexcept;
	void setRotation(const glm::vec3& _val) noexcept;
	void setSize(const glm::vec3& _val) noexcept;

//-----------------------------------------------------------------------------
private:
	void recalcTransform();
	void recalcSize();

//-----------------------------------------------------------------------------
private:
	jl::Object* m_object;

	glm::vec3 m_originOffset;
	glm::vec3 m_pos;

	glm::vec3 m_initialScale;
	glm::vec3 m_scale;

	glm::vec3 m_size;
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
	recalcSize();
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

inline const glm::vec3& ObjectWrapper::getSize() const noexcept
{
	return m_size;
}

inline void ObjectWrapper::setPosition(const glm::vec3& _val) noexcept
{
	m_pos = _val;
	m_object->setPosition(m_pos + m_originOffset);
}

inline void ObjectWrapper::setRotation(const glm::vec3& _val) noexcept
{
	m_object->setRotation(_val);
}

inline void ObjectWrapper::setSize(const glm::vec3& _val) noexcept
{
	m_scale *= _val / m_size;
	m_size = _val;
	recalcTransform();
}

//-----------------------------------------------------------------------------
