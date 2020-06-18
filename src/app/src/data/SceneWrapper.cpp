#include "SceneWrapper.hpp"

//-----------------------------------------------------------------------------

SceneWrapper::SceneWrapper()
	: m_scene(std::make_unique<jl::Scene>())
{
}

//-----------------------------------------------------------------------------

ObjectWrapper& SceneWrapper::addObject(std::unique_ptr<jl::Object>&& _object) noexcept
{
	ObjectWrapper& objWrapper = m_objWrappers.emplace_back(*_object);
	m_scene->addObject(std::move(_object));

	return objWrapper;
}

//-----------------------------------------------------------------------------

void SceneWrapper::removeObject(std::string_view _name) noexcept
{
	auto it = std::find_if(m_objWrappers.begin(), m_objWrappers.end(), [_name](const ObjectWrapper& _objWrapper)
	{
		return _name == _objWrapper.getName();
	});

	m_objWrappers.erase(it);
	m_scene->removeObject(_name);
}

//-----------------------------------------------------------------------------

ObjectWrapper* SceneWrapper::findObject(std::string_view _name) noexcept
{
	auto it = std::find_if(m_objWrappers.begin(), m_objWrappers.end(), [_name](const ObjectWrapper& _objWrapper)
	{
		return _name == _objWrapper.getName();
	});

	return it != m_objWrappers.end() ? &(*it) : nullptr;
}
//-----------------------------------------------------------------------------

const ObjectWrapper* SceneWrapper::findObject(std::string_view _name) const noexcept
{
	auto it = std::find_if(m_objWrappers.begin(), m_objWrappers.end(), [_name](const ObjectWrapper& _objWrapper)
	{
		return _name == _objWrapper.getName();
	});

	return it != m_objWrappers.end() ? &(*it) : nullptr;
}

//-----------------------------------------------------------------------------
