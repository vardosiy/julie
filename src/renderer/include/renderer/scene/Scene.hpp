#pragma once

#include "renderer/Types.hpp"
#include "renderer/scene/FogData.hpp"
#include "renderer/scene/AmbientLightData.hpp"

#include <boost/optional.hpp>
#include <glm/glm.hpp>

#include <functional>
#include <memory>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

class ICamera;
class Shader;
class Object;

class Scene
{
public:
	Scene();
	~Scene();

	void draw(const ICamera& _camera);
	void update(float _dt);

	const FogData* getFogData() const noexcept;
	const AmbientLightData* getAmbientLightData() const noexcept;

	void setFogData(const FogData& _data) noexcept;
	void setAmbientLightData(const AmbientLightData& _data) noexcept;

	void addObject(s32 _id, std::unique_ptr<Object>&& _object);
	void removeObject(s32 _id);

	Object* findObject(s32 _id) noexcept;
	const Object* findObject(s32 _id) const noexcept;

	void forEachObject(const std::function<void(s32, Object&)>& _callback);
	void forEachObject(const std::function<void(s32, const Object&)>& _callback) const;

private:
	void drawObject(const ICamera& _camera, const Object& _object) const noexcept;

private:
	std::unordered_map<s32, std::unique_ptr<Object>> m_objects;

	boost::optional<FogData> m_fogData;
	boost::optional<AmbientLightData> m_ambientLightData;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
