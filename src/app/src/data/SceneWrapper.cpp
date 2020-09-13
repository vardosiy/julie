#include "SceneWrapper.hpp"

#include "utils/Utils.hpp"

//-----------------------------------------------------------------------------

SceneWrapper::SceneWrapper()
	: m_scene(std::make_unique<jl::Scene>())
{
}

//-----------------------------------------------------------------------------

ObjectWrapper& SceneWrapper::createObject(std::string _name) noexcept
{
	auto it = findObject(_name);
	if (it != end())
	{
		return *it;
	}

	auto obj = std::make_unique<jl::Object>();
	ObjectWrapper& objWrapper = m_objWrappers.emplace_back(*obj, std::move(_name));
	m_scene->addObject(std::move(obj));

	return objWrapper;
}

//-----------------------------------------------------------------------------

SceneWrapper::ObjectWrappersContainer::iterator SceneWrapper::findObject(std::string_view _name)
{
	return std::find_if(begin(), end(), [_name](const ObjectWrapper& _objWrapper)
	{
		return _name == _objWrapper.getName();
	});
}

//-----------------------------------------------------------------------------

void SceneWrapper::removeObject(std::string_view _name) noexcept
{
	auto it = findObject(_name);
	removeObject(it);
}

//-----------------------------------------------------------------------------

void SceneWrapper::removeObject(ObjectWrappersContainer::iterator _it) noexcept
{
	if (_it != m_objWrappers.end())
	{
		const jl::Object& obj = *_it->m_obj;

		m_objWrappers.erase(_it);
		m_scene->eraseObject(obj);
	}
}

//-----------------------------------------------------------------------------
