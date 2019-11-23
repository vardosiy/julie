#include "rendering/objects/Fog.hpp"

//-----------------------------------------------------------------------------

Fog::Fog(float _start, float _range, const glm::vec4 & _color)
	: m_start(_start)
	, m_range(_range)
	, m_color(_color)
{
}

//-----------------------------------------------------------------------------
