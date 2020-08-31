#pragma once

#include "julie/core/Types.hpp"
#include "julie/scene/Object.hpp"
#include "julie/scene/FogData.hpp"
#include "julie/scene/lights/LightsHolder.hpp"

#include <boost/noncopyable.hpp>

#include <memory>
#include <vector>
#include <optional>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

class Camera;

class Scene : boost::noncopyable
{
//-----------------------------------------------------------------------------
public:
	using ObjectPtr = std::unique_ptr<Object>;

//-----------------------------------------------------------------------------
	void render(const Camera& _cam, bool drawBoundingBoxes) const;

	const FogData* getFogData() const noexcept;
	void setFogData(const FogData& _data) noexcept;

	LightsHolder& getLightsHolder() noexcept;
	const LightsHolder& getLightsHolder() const noexcept;

//-----------------------------------------------------------------------------
	void addObject(ObjectPtr&& _obj);
	size_t getObjectsCount() const noexcept;

	Object& getObject(size_t _idx);
	const Object& getObject(size_t _idx) const;

	ObjectPtr eraseObject(size_t _idx) noexcept;
	ObjectPtr eraseObject(const Object& _obj) noexcept;

//-----------------------------------------------------------------------------
private:
	std::vector<ObjectPtr> m_objects;

	LightsHolder m_lightsHolder;
	std::optional<FogData> m_fogData;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
