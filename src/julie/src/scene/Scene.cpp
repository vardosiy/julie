#include "julie/scene/Scene.hpp"

#include "scene/ScenePainter.hpp"

#include "utils/Utils.hpp"

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

void Scene::render(const Camera& _cam, bool drawBoundingBoxes) const
{
	ScenePainter painter(*this);
	painter.drawModels(_cam);

	if (drawBoundingBoxes)
	{
		painter.drawBoundingBoxes(_cam);
	}
}

//-----------------------------------------------------------------------------

const FogData* Scene::getFogData() const noexcept
{
	return m_fogData.has_value() ? &m_fogData.value() : nullptr;
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

void Scene::addObject(ObjectPtr&& _obj)
{
	ASSERT(_obj);
	if (_obj)
	{
		m_objects.emplace_back(std::move(_obj));
	}
}

//-----------------------------------------------------------------------------

int Scene::getObjectsCount() const noexcept
{
	return static_cast<int>(m_objects.size());
}

//-----------------------------------------------------------------------------

Object& Scene::getObject(int _idx)
{
	ASSERT(_idx >= 0 && _idx < m_objects.size());
	return *m_objects[_idx];
}

//-----------------------------------------------------------------------------

const Object& Scene::getObject(int _idx) const
{
	ASSERT(_idx >= 0 && _idx < m_objects.size());
	return *m_objects[_idx];
}

//-----------------------------------------------------------------------------

int Scene::findObjectIdx(const Object& _obj) const noexcept
{
	auto it = std::find_if(m_objects.begin(), m_objects.end(), [&_obj](const ObjectPtr& _objPtr)
	{
		return _objPtr.get() == &_obj;
	});

	return it != m_objects.end() ? std::distance(m_objects.begin(), it) : -1;
}

//-----------------------------------------------------------------------------

const Object* Scene::findObjectByName(std::string_view _name) const noexcept
{
	auto it = std::find_if(m_objects.begin(), m_objects.end(), [&_name](const ObjectPtr& _objPtr)
	{
		return _objPtr->getName() == _name;
	});

	return it != m_objects.end() ? it->get() : nullptr;
}

//-----------------------------------------------------------------------------

Scene::ObjectPtr Scene::eraseObject(int _idx) noexcept
{
	ObjectPtr result;

	if (_idx >= 0 && _idx < m_objects.size())
	{
		auto it = m_objects.begin() + _idx;

		result.swap(*it);
		m_objects.erase(it);
	}

	return result;
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
