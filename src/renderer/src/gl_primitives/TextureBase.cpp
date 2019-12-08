#include "renderer/gl_primitives/TextureBase.hpp"
#include "renderer/gl_primitives/TextureTiling.hpp"

#include "utils/Assert.hpp"

#include <glad/glad.h>

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

jl::s32 tilingToOpenGlVal(jl::TextureTiling _tiling)
{
	switch (_tiling)
	{
		case jl::TextureTiling::ClampToEdge:	return GL_CLAMP_TO_EDGE;
		case jl::TextureTiling::Repeat:			return GL_REPEAT;

		default:
			ASSERT(false, "Invalid or unhandled case in obtained while converting texture tiling");
	}

	return 0;
}

//-----------------------------------------------------------------------------

} // namespace details

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

TextureBase::~TextureBase()
{
	glDeleteTextures(1, &m_id);
}

//-----------------------------------------------------------------------------

TextureBase::TextureBase(TextureBase && _rhs) noexcept
	: m_id(_rhs.m_id)
{
	_rhs.m_id = 0;
}

//-----------------------------------------------------------------------------

TextureBase & TextureBase::operator=(TextureBase && _rhs) noexcept
{
	std::swap(m_id, _rhs.m_id);

	return *this;
}

//-----------------------------------------------------------------------------

void TextureBase::bindInternal(u32 _textureType, u16 _slot) const noexcept
{
	glActiveTexture(GL_TEXTURE0 + _slot);
	glBindTexture(_textureType, m_id);
}

//-----------------------------------------------------------------------------

void TextureBase::genTexture(u32 _textureType) noexcept
{
	glGenTextures(1, &m_id);
	glBindTexture(_textureType, m_id);
}

//-----------------------------------------------------------------------------

void TextureBase::performBasicSetup(u32 _textureType, TextureTiling _tiling) noexcept
{
	glTexParameteri(_textureType, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(_textureType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	const s32 glTiling = details::tilingToOpenGlVal(_tiling);
	glTexParameteri(_textureType, GL_TEXTURE_WRAP_S, glTiling);
	glTexParameteri(_textureType, GL_TEXTURE_WRAP_T, glTiling);

	glGenerateMipmap(_textureType);
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
