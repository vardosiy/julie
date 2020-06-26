#include "scene/ScenePainter.hpp"

#include "julie/scene/Scene.hpp"
#include "julie/scene/Object.hpp"
#include "julie/scene/Camera.hpp"
#include "julie/scene/CommonUniformsBinder.hpp"

#include "julie/Material.hpp"
#include "julie/Shader.hpp"
#include "julie/Model.hpp"
#include "julie/Renderer.hpp"

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

ScenePainter::ScenePainter(const Scene& _scene)
	: m_scene(_scene)
{
}

//-----------------------------------------------------------------------------

ScenePainter::~ScenePainter() = default;

//-----------------------------------------------------------------------------

void ScenePainter::draw(const Camera& _cam) const
{
	const u32 objectsCount = m_scene.getObjectsCount();
	for (u32 i = 0; i < objectsCount; ++i)
	{
		const Object& object = m_scene.getObject(i);

		const Model* model = object.getModel();
		if (!model)
		{
			continue;
		}

		const s32 renderFlags = object.getRenderFlags();
		if (renderFlags & jl::Object::RenderFlags::DrawModel)
		{
			drawModel(*model, _cam, object.getWorldMatrix());
		}
		if (renderFlags & jl::Object::RenderFlags::DrawBoundingBox)
		{
			drawBox(*model, _cam, object.getWorldMatrix());
		}
	}
}

//-----------------------------------------------------------------------------

void ScenePainter::drawModel(const Model& _model, const Camera& _cam, const glm::mat4& _worldMat) const noexcept
{
	const u32 meshesCount = _model.getMeshesCount();
	for (u32 i = 0; i < meshesCount; ++i)
	{
		const Mesh& mesh = _model.getMesh(i);

		if (const Material* material = mesh.getMaterial())
		{
			if (const Shader* shader = material->getShader())
			{
				material->bind();

				CommonUniformsBinder uniformBinder(m_scene, _cam, _worldMat);
				uniformBinder.bind(*shader);

				Renderer::draw(mesh);
			}
		}
	}
}

//-----------------------------------------------------------------------------

void ScenePainter::drawBox(const Model& _model, const Camera& _cam, const glm::mat4& _worldMat) const noexcept
{
	const glm::mat4 transform = _cam.getViewProjectionMatrix() * _worldMat;
	Renderer::draw(_model.getBoundingBox(), glm::vec4(1.0f), transform);
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
