#include "julie/Types.hpp"
#include "julie/Shader.hpp"
#include "julie/Texture.hpp"
#include "julie/CubeTexture.hpp"

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

class PropertyBinder
{
public:
	PropertyBinder(const Shader& _shader, const std::string& _uniformName, s16 _textureSlot) noexcept
		: m_shader(_shader)
		, m_uniformName(_uniformName)
		, m_textureSlot(_textureSlot)
	{
	}

	void operator() (const Texture* _texture) const noexcept
	{
		if (_texture)
		{
			_texture->bind(m_textureSlot);
			m_shader.setUniform(m_uniformName, m_textureSlot);
		}
	}

	void operator() (const CubeTexture* _texture) const noexcept
	{
		if (_texture)
		{
			_texture->bind(m_textureSlot);
			m_shader.setUniform(m_uniformName, m_textureSlot);
		}
	}

	template<typename T>
	void operator() (const T& _value) const noexcept
	{
		m_shader.setUniform(m_uniformName, _value);
	}

private:
	const Shader& m_shader;
	const std::string& m_uniformName;
	s16 m_textureSlot;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
