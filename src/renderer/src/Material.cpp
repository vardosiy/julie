#include "renderer/Material.hpp"
#include "renderer/Shader.hpp"
#include "renderer/Texture.hpp"
#include "renderer/CubeTexture.hpp"

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

struct PropertyBinder
{
	PropertyBinder(const jl::Shader& _shader, const std::string& _uniformName, jl::s16 _textureSlot) noexcept
		: m_shader(_shader)
		, m_uniformName(_uniformName)
		, m_textureSlot(_textureSlot)
	{
	}

	void operator() (const jl::Texture* _texture) const noexcept
	{
		_texture->bind(m_textureSlot);
		m_shader.setUniform(m_uniformName, m_textureSlot);
	}

	void operator() (const jl::CubeTexture* _texture) const noexcept
	{
		_texture->bind(m_textureSlot);
		m_shader.setUniform(m_uniformName, m_textureSlot);
	}

	template<typename T>
	void operator() (const T& _value) const noexcept
	{
		m_shader.setUniform(m_uniformName, _value);
	}

private:
	const jl::Shader& m_shader;
	const std::string& m_uniformName;
	jl::s16 m_textureSlot;
};

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
