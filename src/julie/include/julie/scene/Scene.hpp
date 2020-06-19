#pragma once

#include "julie/core/Types.hpp"
#include "julie/scene/FogData.hpp"
#include "julie/scene/lights/LightsHolder.hpp"

#include <boost/optional.hpp>
#include <glm/glm.hpp>

#include <functional>
#include <memory>
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

	void render(const Camera& _cam) const;

//-----------------------------------------------------------------------------
	const FogData* getFogData() const noexcept;
	void setFogData(const FogData& _data) noexcept;

	LightsHolder& getLightsHolder() noexcept;
	const LightsHolder& getLightsHolder() const noexcept;

//-----------------------------------------------------------------------------
	void addObject(ObjectPtr&& _obj) noexcept;
	u32 getObjectsCount() const noexcept;

	Object* getObject(u32 _idx) noexcept;
	const Object* getObject(u32 _idx) const noexcept;

	void removeObject(u32 _idx) noexcept;
	void removeObject(const Object& _obj) noexcept;

//-----------------------------------------------------------------------------
private:
	void drawModel(const Model& _model, const Camera& _cam, const glm::mat4& _worldMat) const noexcept;

//-----------------------------------------------------------------------------
	std::vector<ObjectPtr> m_objects;

	LightsHolder m_lightsHolder;

	boost::optional<FogData> m_fogData;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
