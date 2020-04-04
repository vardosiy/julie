#include "renderer/Material.hpp"
#include "renderer/Shader.hpp"
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
		for (const auto& data : m_propertiesData)
		{
			PropertyBinder binder(*m_shader, data.name, textureSlotsCounter++);
			std::visit(binder, data.value);
		}
	}
}

//-----------------------------------------------------------------------------

const jl::Shader* Material::getShader() const noexcept
{
	return m_shader;
}

//-----------------------------------------------------------------------------

void Material::setShader(const jl::Shader& _shader) noexcept
{
	m_shader = &_shader;
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
