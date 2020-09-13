#pragma once

#include "julie/scene/Object.hpp"

#include "utils/Noncopyable.hpp"

//-----------------------------------------------------------------------------

class SceneWrapper;

class ObjectWrapper : utils::Noncopyable
{
	friend class SceneWrapper;

public:
	ObjectWrapper(jl::Object& _obj, std::string _name);

	ObjectWrapper(ObjectWrapper&&) = default;
	ObjectWrapper& operator=(ObjectWrapper&&) = default;

//-----------------------------------------------------------------------------
	const std::string& getName() const noexcept			{ return m_name; }
	void setName(std::string _name) noexcept			{ m_name = std::move(_name); }

//-----------------------------------------------------------------------------
	jl::Model* getModel() noexcept						{ return m_obj->getModel(); }
	const jl::Model* getModel() const noexcept			{ return m_obj->getModel(); }
	void setModel(jl::Model* _model) noexcept			{ m_obj->setModel(_model); }

//-----------------------------------------------------------------------------
	const glm::mat4& getWorldMatrix() const noexcept	{ return m_obj->getWorldMatrix(); }

	const glm::vec3& getPosition() const noexcept		{ return m_obj->getPosition(); }
	const glm::vec3& getRotation() const noexcept		{ return m_obj->getRotation(); }
	const glm::vec3& getScale() const noexcept			{ return m_obj->getScale(); }

	void setPosition(const glm::vec3& _val) noexcept	{ m_obj->setPosition(_val); }
	void setRotation(const glm::vec3& _val) noexcept	{ m_obj->setRotation(_val); }
	void setScale(const glm::vec3& _val) noexcept		{ m_obj->setScale(_val); }

//-----------------------------------------------------------------------------
private:
	jl::Object* m_obj;
	std::string m_name;
};

//-----------------------------------------------------------------------------
