#pragma once

#include "julie/scene/Object.hpp"

//-----------------------------------------------------------------------------

class ObjectWrapper
{
public:
	ObjectWrapper(jl::Object& _obj, std::string _name);

	ObjectWrapper(const ObjectWrapper& _rhs) = default;
	ObjectWrapper& operator=(const ObjectWrapper& _rhs) = default;

	ObjectWrapper(ObjectWrapper&& _rhs) = default;
	ObjectWrapper& operator=(ObjectWrapper&& _rhs) = default;

//-----------------------------------------------------------------------------
	jl::Object& getInternalObject() noexcept;
	const jl::Object& getInternalObject() const noexcept;

	const std::string& getName() const noexcept;
	void setName(std::string _name) noexcept;

	jl::Model* getModel() const noexcept;
	void setModel(jl::Model* _model) noexcept;

//-----------------------------------------------------------------------------
	const glm::mat4& getWorldMatrix() const noexcept;

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
	std::string m_name;

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

inline const std::string& ObjectWrapper::getName() const noexcept
{
	return m_name;
}

inline void ObjectWrapper::setName(std::string _name) noexcept
{
	m_name = std::move(_name);
}

inline jl::Model* ObjectWrapper::getModel() const noexcept
{
	return m_object->getModel();
}

inline void ObjectWrapper::setModel(jl::Model* _model) noexcept
{
	m_object->setModel(_model);
	m_scale = glm::vec3(1.0f);
	recalcTransform();
	recalcSize();
}

inline const glm::mat4& ObjectWrapper::getWorldMatrix() const noexcept
{
	return m_object->getWorldMatrix();
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
