#pragma once

#include "renderer/Types.hpp"
#include "renderer/scene/FogData.hpp"
#include "renderer/scene/AmbientLightData.hpp"

#include <boost/optional.hpp>
#include <glm/glm.hpp>

#include <functional>
#include <memory>
#include <map>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

class IRenderable;
class ICamera;

class Scene
{
public:
	Scene();
	~Scene();

	void update(float _dt);
	void render(const ICamera& _camera);

	const FogData* getFogData() const noexcept;
	const AmbientLightData* getAmbientLightData() const noexcept;

	void setFogData(const FogData& _data) noexcept;
	void setAmbientLightData(const AmbientLightData& _data) noexcept;

	void addRenderable(s32 _id, IRenderable& _renderable);
	void removeRenderable(s32 _id);

	IRenderable* findRenderable(s32 _id) noexcept;
	const IRenderable* findRenderable(s32 _id) const noexcept;

	void forEachRenderable(const std::function<void(s32, IRenderable&)>& _callback);
	void forEachRenderable(const std::function<void(s32, const IRenderable&)>& _callback) const;

private:
	using RenderablesContainer = std::map<s32, IRenderable*>;
	RenderablesContainer m_renderables;

	boost::optional<FogData> m_fogData;
	boost::optional<AmbientLightData> m_ambientLightData;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
