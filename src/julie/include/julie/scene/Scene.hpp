#pragma once

#include "julie/core/Types.hpp"
#include "julie/scene/Object.hpp"
#include "julie/scene/FogData.hpp"
#include "julie/scene/lights/LightsHolder.hpp"

#include <boost/optional.hpp>
#include <boost/noncopyable.hpp>

#include <memory>
#include <vector>

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
	void render(const Camera& _cam) const;

	const FogData* getFogData() const noexcept;
	void setFogData(const FogData& _data) noexcept;

	LightsHolder& getLightsHolder() noexcept;
	const LightsHolder& getLightsHolder() const noexcept;

//-----------------------------------------------------------------------------
	void addObject(ObjectPtr&& _obj) noexcept;
	u32 getObjectsCount() const noexcept;

	Object& getObject(u32 _idx);
	const Object& getObject(u32 _idx) const;

	ObjectPtr eraseObject(u32 _idx) noexcept;
	ObjectPtr eraseObject(const Object& _obj) noexcept;

//-----------------------------------------------------------------------------
private:
	std::vector<ObjectPtr> m_objects;

	LightsHolder m_lightsHolder;
	boost::optional<FogData> m_fogData;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
