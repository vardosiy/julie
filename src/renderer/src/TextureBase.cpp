#include "renderer/TextureBase.hpp"
#include "renderer/TextureTiling.hpp"

#include "ConvertingHelper.hpp"

#include "utils/Utils.hpp"

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

u32 TextureBase::getHandle() const noexcept
{
	return m_id;
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
	const float tiling = tilingToGlValue(_tiling);
	glTexParameterf(m_type, GL_TEXTURE_WRAP_S, tiling);
	glTexParameterf(m_type, GL_TEXTURE_WRAP_T, tiling);
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

} // namespace jl

//-----------------------------------------------------------------------------
