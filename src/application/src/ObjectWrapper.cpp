#include "ObjectWrapper.hpp"

#include "renderer/Model.hpp"

#include <algorithm>

//-----------------------------------------------------------------------------

ObjectWrapper::ObjectWrapper(jl::Object& _obj)
	: m_object(&_obj)
	, m_originOffset(0.0f)
	, m_pos(0.0f)
	, m_initialScale(1.0f)
	, m_scale(1.0f)
{
	recalcTransform();
}

//-----------------------------------------------------------------------------

void ObjectWrapper::recalcTransform()
{
	if (const jl::Model* model = getModel())
	{
		const jl::boxf& modelBox = model->getBoundingBox();

		const float width = modelBox.getWidth();
		const float height = modelBox.getHeight();
		const float depth = modelBox.getDepth();

		const float max = std::max(width, std::max(height, depth));
		m_initialScale = glm::vec3(1.0f / max);
		m_object->setScale(m_scale * m_initialScale);
		m_object->setPosition(glm::vec3(0.0f));

		const jl::boxf worldBox = m_object->getWorldMatrix() * modelBox;
		m_originOffset = -worldBox.min;
		m_object->setPosition(m_pos + m_originOffset);
	}
}

//-----------------------------------------------------------------------------
