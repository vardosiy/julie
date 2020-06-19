#pragma once

#include "data/ObjectWrapper.hpp"

#include "julie/scene/Scene.hpp"

//-----------------------------------------------------------------------------

class SceneWrapper
{
public:
	SceneWrapper();

	void render(const jl::Camera& _cam) const;

	jl::LightsHolder& getLightsHolder() noexcept;
	const jl::LightsHolder& getLightsHolder() const noexcept;

	ObjectWrapper& createObject(std::string _name) noexcept;
	void removeObject(std::string_view _name) noexcept;

	ObjectWrapper* findObject(std::string_view _name) noexcept;
	const ObjectWrapper* findObject(std::string_view _name) const noexcept;

	void forEachObject(const std::function<void(ObjectWrapper&)>& _callback);
	void forEachObject(const std::function<void(const ObjectWrapper&)>& _callback) const;

private:
	std::unique_ptr<jl::Scene> m_scene;
	std::vector<ObjectWrapper> m_objWrappers;
};

//-----------------------------------------------------------------------------

inline void SceneWrapper::render(const jl::Camera& _cam) const
{
	m_scene->render(_cam);
}

inline jl::LightsHolder& SceneWrapper::getLightsHolder() noexcept
{
	return m_scene->getLightsHolder();
}

inline const jl::LightsHolder& SceneWrapper::getLightsHolder() const noexcept
{
	return m_scene->getLightsHolder();
}

inline void SceneWrapper::forEachObject(const std::function<void(ObjectWrapper&)>& _callback)
{
	std::for_each(m_objWrappers.begin(), m_objWrappers.end(), _callback);
}

inline void SceneWrapper::forEachObject(const std::function<void(const ObjectWrapper&)>& _callback) const
{
	std::for_each(m_objWrappers.begin(), m_objWrappers.end(), _callback);
}

//-----------------------------------------------------------------------------
