#include "renderer/scene/Light.hpp"

#include <cmath>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

Light::Light(Type _type, const glm::vec3 & _posDir)
	: m_type(_type)
	, m_originalPosDir(_posDir)
	, m_posDir(_posDir)
	, m_color(0.0f, 0.0f, 0.0f, 0.0f)
	, m_angle(0.0f)
	, m_moveSpeed(0.0f)
	, m_radius(0.0f)
{
	//update(0.0f);
}

//-----------------------------------------------------------------------------

void Light::update(float _deltaTime)
{
	if (m_type == Type::Point)
	{
		m_angle += m_moveSpeed * _deltaTime;

		glm::vec3 diff(m_radius * cos(m_angle), 0.0f, m_radius * sin(m_angle));
		m_posDir = m_originalPosDir + diff;
	}
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
