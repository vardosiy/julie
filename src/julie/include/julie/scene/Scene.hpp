#pragma once

#include "julie/core/Types.hpp"
#include "julie/scene/Object.hpp"
#include "julie/scene/FogData.hpp"
#include "julie/scene/lights/LightsHolder.hpp"

#include "utils/Noncopyable.hpp"

#include <memory>
#include <vector>
#include <optional>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

class Camera;

class Scene : utils::Noncopyable
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

	int getObjectsCount() const noexcept;
	Object& getObject(int _idx);
	const Object& getObject(int _idx) const;

	int findObjectIdx(const Object& _obj) const noexcept;
	const Object* findObjectByName(std::string_view _name) const noexcept;

	ObjectPtr eraseObject(int _idx) noexcept;

//-----------------------------------------------------------------------------
private:
	std::vector<ObjectPtr> m_objects;

	LightsHolder m_lightsHolder;
	std::optional<FogData> m_fogData;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
