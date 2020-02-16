#include "renderer/Texture.hpp"
#include "renderer/TextureTiling.hpp"

#include "utils/Assert.hpp"

#include <glad/glad.h>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

Texture::Texture(const InitData& _initData) noexcept
	: TextureBase(GL_TEXTURE_2D)
	, m_width(_initData.width)
	, m_height(_initData.height)
{
	bind(0);

	const s32 format	= formatToGlValue(_initData.format);
	const s32 type		= fragmentTypeToGlValue(_initData.fragmentType);
	glTexImage2D(GL_TEXTURE_2D, 0, format, m_width, m_height, 0, format, type, _initData.data.get());
	glGenerateMipmap(GL_TEXTURE_2D);
}

//-----------------------------------------------------------------------------

s32 Texture::formatToGlValue(Format _format)
{
	switch (_format)
	{
		case Texture::Format::Rgb:				return GL_RGB;
		case Texture::Format::Rgba:				return GL_RGBA;
		case Texture::Format::DepthComponent:	return GL_DEPTH_COMPONENT;

		default:
			ASSERT(0);
	}

	return 0;
}

//-----------------------------------------------------------------------------

s32 Texture::fragmentTypeToGlValue(FragmentType _type)
{
	switch (_type)
	{
		case Texture::FragmentType::UnsignedByte:	return GL_UNSIGNED_BYTE;
		case Texture::FragmentType::UnsignedInt:	return GL_UNSIGNED_INT;

		default:
			ASSERT(0);
	}

	return 0;
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
