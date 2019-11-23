#include "rendering/lights/Light.hpp"

#include <cmath>

//-----------------------------------------------------------------------------

Light::Light(LightType _type, glm::vec3 const & _posDir)
	: m_type(_type)
	, m_originalPosDir(_posDir)
	, m_angle(0.0f)
{
	update(0.0f);
}

//-----------------------------------------------------------------------------

void Light::update(float _deltaTime)
{
	if (m_type == LightType::Directional)
	{
		return;
	}

	m_angle += m_moveSpeed * _deltaTime;

	glm::vec3 diff(m_radius * cos(m_angle), 0.0f, m_radius * sin(m_angle));
	m_posDir = m_originalPosDir + diff;
}

//-----------------------------------------------------------------------------
