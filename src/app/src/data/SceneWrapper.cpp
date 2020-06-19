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
	ASSERT(findObject(_name) == nullptr);

	auto obj = std::make_unique<jl::Object>();
	ObjectWrapper& objWrapper = m_objWrappers.emplace_back(*obj, std::move(_name));
	m_scene->addObject(std::move(obj));

	return objWrapper;
}

//-----------------------------------------------------------------------------

void SceneWrapper::removeObject(std::string_view _name) noexcept
{
	auto it = std::find_if(m_objWrappers.begin(), m_objWrappers.end(), [_name](const ObjectWrapper& _objWrapper)
	{
		return _name == _objWrapper.getName();
	});

	if (it != m_objWrappers.end())
	{
		const jl::Object& obj = it->getInternalObject();

		m_objWrappers.erase(it);
		m_scene->removeObject(obj);
	}
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
