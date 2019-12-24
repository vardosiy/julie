#include "renderer/gl_primitives/Texture.hpp"
#include "renderer/gl_primitives/TextureTiling.hpp"

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
		case jl::Texture::Format::Rgb:				return GL_RGB;
		case jl::Texture::Format::Rgba:				return GL_RGBA;
		case jl::Texture::Format::DepthComponent:	return GL_DEPTH_COMPONENT;

		default:
			ASSERT(false, "Unhandled case");
	}

	return GL_RGB;
}

//-----------------------------------------------------------------------------

s32 Texture::fragmentTypeToGlValue(FragmentType _type)
{
	switch (_type)
	{
		case jl::Texture::FragmentType::UnsignedByte:	return GL_UNSIGNED_BYTE;
		case jl::Texture::FragmentType::UnsignedInt:	return GL_UNSIGNED_INT;

		default:
			ASSERT(false, "Unhandled case");
	}

	return GL_UNSIGNED_BYTE;
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
