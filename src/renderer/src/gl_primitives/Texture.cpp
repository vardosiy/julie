#include "renderer/gl_primitives/Texture.hpp"
#include "renderer/gl_primitives/TextureTiling.hpp"

#include "loaders/loadTga.hpp"

#include <glad/glad.h>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

std::unique_ptr<Texture> Texture::create(std::string_view _filePath, TextureTiling _tiling)
{
	s32 width, height, bpp;
	char *tgaBuffer = loadTga(_filePath.data(), &width, &height, &bpp);
	if (!tgaBuffer)
	{
		return nullptr;
	}

	std::unique_ptr<Texture> texture(new Texture);
	texture->genTexture(GL_TEXTURE_2D);
	texture->bind(0);

	const s32 format = bpp == 24 ? GL_RGB : GL_RGBA;
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, tgaBuffer);
	delete[] tgaBuffer;

	texture->performBasicSetup(GL_TEXTURE_2D, _tiling);

	return texture;
}

//-----------------------------------------------------------------------------

std::unique_ptr<Texture> Texture::createFrameTexture(u32 _format, u32 _type, int _width, int _height)
{
	std::unique_ptr<Texture> texture(new Texture);
	texture->genTexture(GL_TEXTURE_2D);
	texture->bind(0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, _format, _width, _height, 0, _format, _type, nullptr);

	return texture;
}

//-----------------------------------------------------------------------------

Texture::Texture(Texture && _rhs) noexcept
	: TextureBase(std::forward<Texture>(_rhs))
{
}

//-----------------------------------------------------------------------------

Texture & Texture::operator =(Texture && _rhs) noexcept
{
	TextureBase::operator=(std::forward<Texture>(_rhs));
	return *this;
}

//-----------------------------------------------------------------------------

void Texture::bind(u16 _slot) const noexcept
{
	bindInternal(GL_TEXTURE_2D, _slot);
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
