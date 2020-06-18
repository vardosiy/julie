#pragma once

#include "julie/Types.hpp"
#include "julie/scene/FogData.hpp"
#include "julie/scene/lights/LightsHolder.hpp"

#include <boost/optional.hpp>
#include <glm/glm.hpp>

#include <functional>
#include <vector>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

class Object;
class Camera;
class Model;

class Scene
{
//-----------------------------------------------------------------------------
public:
	using ObjectPtr = std::unique_ptr<Object>;

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
	void addObject(ObjectPtr&& _object) noexcept;
	void removeObject(std::string_view _name) noexcept;

	Object* findObject(std::string_view _name) noexcept;
	const Object* findObject(std::string_view _name) const noexcept;

	void forEachObject(const std::function<void(Object&)>& _callback);
	void forEachObject(const std::function<void(const Object&)>& _callback) const;

//-----------------------------------------------------------------------------
private:
	void drawModel(const Model& _model, const Camera& _camera, const glm::mat4& _worldMat) const;

//-----------------------------------------------------------------------------
	std::vector<ObjectPtr> m_objects;

	LightsHolder m_lightsHolder;

	boost::optional<FogData> m_fogData;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
