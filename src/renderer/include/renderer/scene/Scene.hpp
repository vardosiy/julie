#pragma once

#include "renderer/Types.hpp"
#include "renderer/scene/FogData.hpp"
#include "renderer/scene/lights/LightsHolder.hpp"

#include <boost/optional.hpp>
#include <glm/glm.hpp>

#include <functional>
#include <map>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

class Object;
class Camera;

class Scene
{
//-----------------------------------------------------------------------------
public:
	Scene();
	~Scene();

	void update(float _dt);
	void render(const Camera& _camera) const;

//-----------------------------------------------------------------------------
	const FogData* getFogData() const noexcept;
	void setFogData(const FogData& _data) noexcept;

	LightsHolder& getLightsHolder() noexcept;
	const LightsHolder& getLightsHolder() const noexcept;

//-----------------------------------------------------------------------------
	void addObject(s32 _id, Object& _object);
	void removeObject(s32 _id);

	Object* findObject(s32 _id) noexcept;
	const Object* findObject(s32 _id) const noexcept;

	void forEachObject(const std::function<void(s32, Object&)>& _callback);
	void forEachObject(const std::function<void(s32, const Object&)>& _callback) const;

//-----------------------------------------------------------------------------
private:
	using ObjectsContainer = std::map<s32, Object*>;
	ObjectsContainer m_objects;

	LightsHolder m_lightsHolder;

	boost::optional<FogData> m_fogData;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
