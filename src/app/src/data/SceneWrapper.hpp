#pragma once

#include "data/ObjectWrapper.hpp"

#include "julie/scene/Scene.hpp"

#include "utils/Noncopyable.hpp"

#include <functional>
#include <algorithm>

//-----------------------------------------------------------------------------

class SceneWrapper : utils::Noncopyable
{
public:
	using ObjectWrappersContainer = std::vector<ObjectWrapper>;

//-----------------------------------------------------------------------------
	SceneWrapper();

	SceneWrapper(SceneWrapper&&) = default;
	SceneWrapper& operator=(SceneWrapper&&) = default;

//-----------------------------------------------------------------------------
	void render(const jl::Camera& _cam) const;

	jl::LightsHolder& getLightsHolder() noexcept;
	const jl::LightsHolder& getLightsHolder() const noexcept;

//-----------------------------------------------------------------------------
	ObjectWrapper& createObject(std::string _name) noexcept;

	ObjectWrappersContainer::iterator begin() noexcept;
	ObjectWrappersContainer::iterator end() noexcept;

	ObjectWrappersContainer::const_iterator begin() const noexcept;
	ObjectWrappersContainer::const_iterator end() const noexcept;

	ObjectWrappersContainer::iterator findObject(std::string_view _name);

	void removeObject(std::string_view _name) noexcept;
	void removeObject(ObjectWrappersContainer::iterator _it) noexcept;

//-----------------------------------------------------------------------------
private:
	std::unique_ptr<jl::Scene> m_scene;
	ObjectWrappersContainer m_objWrappers;
};

//-----------------------------------------------------------------------------

inline void SceneWrapper::render(const jl::Camera& _cam) const
{
	m_scene->render(_cam, false);
}

inline jl::LightsHolder& SceneWrapper::getLightsHolder() noexcept
{
	return m_scene->getLightsHolder();
}

inline const jl::LightsHolder& SceneWrapper::getLightsHolder() const noexcept
{
	return m_scene->getLightsHolder();
}

//-----------------------------------------------------------------------------

inline SceneWrapper::ObjectWrappersContainer::iterator SceneWrapper::begin() noexcept
{
	return m_objWrappers.begin();
}

inline SceneWrapper::ObjectWrappersContainer::iterator SceneWrapper::end() noexcept
{
	return m_objWrappers.end();
}

inline SceneWrapper::ObjectWrappersContainer::const_iterator SceneWrapper::begin() const noexcept
{
	return m_objWrappers.begin();
}

inline SceneWrapper::ObjectWrappersContainer::const_iterator SceneWrapper::end() const noexcept
{
	return m_objWrappers.end();
}

//-----------------------------------------------------------------------------
