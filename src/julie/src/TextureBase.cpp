#include "julie/TextureBase.hpp"
#include "julie/TextureTiling.hpp"
#include "julie/TextureFiltering.hpp"

#include "utils/Utils.hpp"

#include <glad/glad.h>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

TextureBase::TextureBase(s32 _type, u32 _width, u32 _height) noexcept
	: m_type(_type)
	, m_width(_width)
	, m_height(_height)
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

u32 TextureBase::getWidth() const noexcept
{
	return m_width;
}

//-----------------------------------------------------------------------------

u32 TextureBase::getHeight() const noexcept
{
	return m_height;
}

//-----------------------------------------------------------------------------

void TextureBase::bind(u16 _slot) const noexcept
{
	glActiveTexture(GL_TEXTURE0 + _slot);
	glBindTexture(getType(), m_id);
}

//-----------------------------------------------------------------------------

void TextureBase::setTiling(TextureTiling _tiling) noexcept
{
	const float tiling = tilingToGlValue(_tiling);
	glTexParameterf(getType(), GL_TEXTURE_WRAP_S, tiling);
	glTexParameterf(getType(), GL_TEXTURE_WRAP_T, tiling);
}

//-----------------------------------------------------------------------------

void TextureBase::setMagnificationFilteringMode(TextureFiltering _mode) noexcept
{
	glTexParameteri(getType(), GL_TEXTURE_MAG_FILTER, filteringToGlValue(_mode));
}

//-----------------------------------------------------------------------------

void TextureBase::setMinificationFilteringMode(TextureFiltering _mode) noexcept
{
	glTexParameteri(getType(), GL_TEXTURE_MIN_FILTER, filteringToGlValue(_mode));
}

//-----------------------------------------------------------------------------

s32 TextureBase::getType() const noexcept
{
	return m_type;
}

//-----------------------------------------------------------------------------

s32 TextureBase::formatToGlValue(Format _format) noexcept
{
	switch (_format)
	{
		case Format::Rgb:				return GL_RGB;
		case Format::Rgba:				return GL_RGBA;
		case Format::DepthComponent:	return GL_DEPTH_COMPONENT;
	}

	ASSERT(0);
	return 0;
}

//-----------------------------------------------------------------------------

s32 TextureBase::fragmentTypeToGlValue(FragmentType _type) noexcept
{
	switch (_type)
	{
		case FragmentType::UnsignedByte:	return GL_UNSIGNED_BYTE;
		case FragmentType::UnsignedInt:		return GL_UNSIGNED_INT;
	}

	ASSERT(0);
	return 0;
}

//-----------------------------------------------------------------------------

float TextureBase::tilingToGlValue(TextureTiling _tiling) noexcept
{
	switch (_tiling)
	{
		case TextureTiling::ClampToEdge:	return GL_CLAMP_TO_EDGE;
		case TextureTiling::Repeat:			return GL_REPEAT;
		case TextureTiling::MirroredRepeat:	return GL_MIRRORED_REPEAT;
	}

	ASSERT(0);
	return 0.0f;
}

//-----------------------------------------------------------------------------

s32 TextureBase::filteringToGlValue(TextureFiltering _mode) noexcept
{
	switch (_mode)
	{
		case TextureFiltering::Nearest:				return GL_NEAREST;
		case TextureFiltering::Linear:				return GL_LINEAR;
		case TextureFiltering::LinearMipmapLinear:	return GL_LINEAR_MIPMAP_LINEAR;
	}

	ASSERT(0);
	return 0;
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
