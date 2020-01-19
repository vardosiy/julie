#include "renderer/Material.hpp"

#include "renderer/Shader.hpp"
#include "renderer/Texture.hpp"
#include "renderer/CubeTexture.hpp"

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

namespace visitors {

//-----------------------------------------------------------------------------

struct UniformBinder
{
	UniformBinder(const Shader& _shader, const std::string& _uniformName, s16 _textureSlot) noexcept
		: m_shader(_shader)
		, m_uniformName(_uniformName)
		, m_textureSlot(_textureSlot)
	{
	}

	void operator() (const Texture* _texture) const noexcept
	{
		_texture->bind(m_textureSlot);
		m_shader.setUniformValue(m_uniformName, m_textureSlot);
	}

	void operator() (const CubeTexture* _texture) const noexcept
	{
		_texture->bind(m_textureSlot);
		m_shader.setUniformValue(m_uniformName, m_textureSlot);
	}

	template<typename T>
	void operator() (const T& _value) const noexcept
	{
		m_shader.setUniformValue(m_uniformName, _value);
	}

private:
	const Shader& m_shader;
	const std::string& m_uniformName;
	s16 m_textureSlot;
};

//-----------------------------------------------------------------------------

} // namespace visitors

//-----------------------------------------------------------------------------

void Material::bind() const
{
	if (m_shader)
	{
		m_shader->bind();
		s16 textureSlotsCounter = 0;
		for (const auto& data : m_propertiesData)
		{
			visitors::UniformBinder binder(*m_shader, data.name, textureSlotsCounter++);
			std::visit(binder, data.value);
		}
	}
}

//-----------------------------------------------------------------------------

void Material::setShader(const Shader& _shader) noexcept
{
	m_shader = &_shader;
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
