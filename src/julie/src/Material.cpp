#include "julie/Material.hpp"
#include "julie/Shader.hpp"

#include "PropertyBinder.hpp"

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

void Material::bind() const
{
	if (m_shader)
	{
		m_shader->bind();
		s16 textureSlotsCounter = 0;
		for (const auto& data : m_properties)
		{
			PropertyBinder binder(*m_shader, data.name, textureSlotsCounter);
			std::visit(binder, data.value);
		}
	}
}

//-----------------------------------------------------------------------------

const Shader* Material::getShader() const noexcept
{
	return m_shader;
}

//-----------------------------------------------------------------------------

void Material::setShader(const Shader* _shader) noexcept
{
	m_shader = _shader;
}

//-----------------------------------------------------------------------------

const std::vector<Material::Property>& Material::getProperties() const noexcept
{
	return m_properties;
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
