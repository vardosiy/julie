#include "renderer/gl_primitives/TextureBase.hpp"
#include "renderer/gl_primitives/TextureTiling.hpp"

#include "utils/Assert.hpp"

#include <glad/glad.h>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

TextureBase::TextureBase(s32 _type) noexcept
	: m_type(_type)
{
	glGenTextures(1, &m_id);
}

//-----------------------------------------------------------------------------

TextureBase::~TextureBase()
{
	glDeleteTextures(1, &m_id);
}

//-----------------------------------------------------------------------------

void TextureBase::bind(u16 _slot) const noexcept
{
	glActiveTexture(GL_TEXTURE0 + _slot);
	glBindTexture(m_type, m_id);
}

//-----------------------------------------------------------------------------

void TextureBase::setTiling(TextureTiling _tiling) noexcept
{
	glTexParameterf(m_type, GL_TEXTURE_WRAP_S, tilingToGlValue(_tiling));
	glTexParameterf(m_type, GL_TEXTURE_WRAP_T, tilingToGlValue(_tiling));
}

//-----------------------------------------------------------------------------

void TextureBase::setMagnificationFilteringMode(TextureFilteringMode _mode) noexcept
{
	glTexParameteri(m_type, GL_TEXTURE_MAG_FILTER, filteringModeToGlValue(_mode));
}

//-----------------------------------------------------------------------------

void TextureBase::setMinificationFilteringMode(TextureFilteringMode _mode) noexcept
{
	glTexParameteri(m_type, GL_TEXTURE_MIN_FILTER, filteringModeToGlValue(_mode));
}

//-----------------------------------------------------------------------------

float TextureBase::tilingToGlValue(TextureTiling _tiling)
{
	switch (_tiling)
	{
		case TextureTiling::ClampToEdge:	return GL_CLAMP_TO_EDGE;
		case TextureTiling::Repeat:			return GL_REPEAT;

		default:
			ASSERT(0);
	}

	return 0;
}

//-----------------------------------------------------------------------------

s32 TextureBase::filteringModeToGlValue(TextureFilteringMode _mode)
{
	switch (_mode)
	{
		case TextureFilteringMode::Nearest:				return GL_NEAREST;
		case TextureFilteringMode::Linear:				return GL_LINEAR;
		case TextureFilteringMode::LinearMipmapLinear:	return GL_LINEAR_MIPMAP_LINEAR;

		default:
			ASSERT(0);
	}

	return 0;
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
