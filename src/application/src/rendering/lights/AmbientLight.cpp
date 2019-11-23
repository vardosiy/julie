#include "rendering/lights/AmbientLight.hpp"

//-----------------------------------------------------------------------------

AmbientLight::AmbientLight(const glm::vec4 & _color, float _weight)
	: m_color(_color)
	, m_weight(_weight)
{
}

//-----------------------------------------------------------------------------
