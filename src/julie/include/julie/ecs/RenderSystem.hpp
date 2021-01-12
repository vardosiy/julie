#pragma once

#include <glm/mat4x4.hpp>

#include <chrono>
#include <vector>

namespace jl {
class Camera;
class Scene;
class Model;
}

//-----------------------------------------------------------------------------

namespace jl::ecs {

//-----------------------------------------------------------------------------

class ComponentsMgr;

class RenderSystem
{
public:
	RenderSystem(const Scene& _scene, ComponentsMgr& _componentsMgr) noexcept;

	void update(const Camera& _cam);

private:
	void updateLightsCache();

	void drawScene(const Camera& _cam) const noexcept;
	void drawModel(const Model& _model, const Camera& _cam, const glm::mat4& _worldMat) const noexcept;

private:
	const Scene& m_scene;
	ComponentsMgr& m_componentsMgr;

	std::vector<glm::vec3> m_lightsPosCache;
	std::vector<glm::vec3> m_lightsColorCache;
};

//-----------------------------------------------------------------------------

} // namespace jl::ecs

//-----------------------------------------------------------------------------
