#pragma once

#include "julie/core/Types.hpp"

#include <glm/mat4x4.hpp>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

class Scene;
class Camera;
class Model;

class ScenePainter
{
public:
	ScenePainter(const Scene& _scene);
	~ScenePainter();

	void drawModels(const Camera& _cam) const;
	void drawBoundingBoxes(const Camera& _cam) const;

private:
	void drawModel(const Model& _model, const Camera& _cam, const glm::mat4& _worldMat) const noexcept;

	const Scene& m_scene;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
