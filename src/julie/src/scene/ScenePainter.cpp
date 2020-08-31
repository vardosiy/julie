#include "scene/ScenePainter.hpp"
#include "scene/CommonUniformsBinder.hpp"

#include "julie/scene/Scene.hpp"
#include "julie/scene/Object.hpp"
#include "julie/scene/Camera.hpp"

#include "julie/Material.hpp"
#include "julie/Shader.hpp"
#include "julie/Model.hpp"
#include "julie/Renderer.hpp"

#include "PropertyBinder.hpp"

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

void ScenePainter::drawModels(const Camera& _cam) const
{
	const size_t objectsCount = m_scene.getObjectsCount();
	for (size_t i = 0; i < objectsCount; ++i)
	{
		const Object& object = m_scene.getObject(i);

		if (const Model* model = object.getModel())
		{
			drawModel(*model, _cam, object.getWorldMatrix());
		}
	}
}

//-----------------------------------------------------------------------------

void ScenePainter::drawBoundingBoxes(const Camera& _cam) const
{
	const size_t objectsCount = m_scene.getObjectsCount();
	for (size_t i = 0; i < objectsCount; ++i)
	{
		const Object& object = m_scene.getObject(i);

		if (const Model* model = object.getModel())
		{
			const glm::mat4 transform = _cam.getViewProjectionMatrix() * object.getWorldMatrix();
			Renderer::draw(model->getBoundingBox(), glm::vec4(1.0f), transform);
		}
	}
}

//-----------------------------------------------------------------------------

void ScenePainter::drawModel(const Model& _model, const Camera& _cam, const glm::mat4& _worldMat) const noexcept
{
	const size_t meshesCount = _model.getMeshesCount();
	for (size_t i = 0; i < meshesCount; ++i)
	{
		const Mesh& mesh = _model.getMesh(i);

		if (const Material* material = mesh.getMaterial())
		{
			if (const Shader* shader = material->getShader())
			{
				shader->bind();
				s16 textureSlotsCounter = 0;
				for (const auto& property : material->getProperties())
				{
					PropertyBinder binder(*shader, property.name, textureSlotsCounter);
					std::visit(binder, property.value);
				}

				CommonUniformsBinder uniformBinder(m_scene, _cam, _worldMat);
				uniformBinder.bind(*shader);

				Renderer::draw(mesh);
			}
		}
	}
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
