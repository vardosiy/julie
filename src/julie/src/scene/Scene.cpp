#include "julie/scene/Scene.hpp"

#include "scene/ScenePainter.hpp"

#include "utils/Utils.hpp"

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

void Scene::render(const Camera& _cam) const
{
	ScenePainter painter(*this);
	painter.draw(_cam);
}

//-----------------------------------------------------------------------------

const FogData* Scene::getFogData() const noexcept
{
	return m_fogData.get_ptr();
}

//-----------------------------------------------------------------------------

LightsHolder& Scene::getLightsHolder() noexcept
{
	return m_lightsHolder;
}

//-----------------------------------------------------------------------------

const LightsHolder& Scene::getLightsHolder() const noexcept
{
	return m_lightsHolder;
}

//-----------------------------------------------------------------------------

void Scene::setFogData(const FogData& _data) noexcept
{
	m_fogData = _data;
}

//-----------------------------------------------------------------------------

void Scene::addObject(ObjectPtr&& _obj) noexcept
{
	ASSERT(_obj);
	if (_obj)
	{
		m_objects.emplace_back(std::move(_obj));
	}
}

//-----------------------------------------------------------------------------

u32 Scene::getObjectsCount() const noexcept
{
	return m_objects.size();
}

//-----------------------------------------------------------------------------

Object& Scene::getObject(u32 _idx)
{
	ASSERT(_idx < m_objects.size());
	return *m_objects[_idx];
}

//-----------------------------------------------------------------------------

const Object& Scene::getObject(u32 _idx) const
{
	ASSERT(_idx < m_objects.size());
	return *m_objects[_idx];
}

//-----------------------------------------------------------------------------

Scene::ObjectPtr Scene::eraseObject(u32 _idx) noexcept
{
	ObjectPtr result;

	if (_idx < m_objects.size())
	{
		auto it = m_objects.begin() + _idx;

		result.swap(*it);
		m_objects.erase(it);
	}

	return result;
}

//-----------------------------------------------------------------------------

Scene::ObjectPtr Scene::eraseObject(const Object& _obj) noexcept
{
	auto it = std::find_if(m_objects.begin(), m_objects.end(), [&_obj](const ObjectPtr& _objPtr)
	{
		return _objPtr.get() == &_obj;
	});

	ObjectPtr result;

	if (it != m_objects.end())
	{
		result.swap(*it);
		m_objects.erase(it);
	}

	return result;
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
