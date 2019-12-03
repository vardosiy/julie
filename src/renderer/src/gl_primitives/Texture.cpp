#include "renderer/gl_primitives/Texture.hpp"

#include "loaders/loadTga.hpp"

#include <glad/glad.h>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

std::unique_ptr<Texture> Texture::create(std::string_view _filePath, u32 _tiling)
{
	s32 width, height, bpp;
	std::unique_ptr<char[]> bufferTGA = loadTga(_filePath, &width, &height, &bpp);
	if (!bufferTGA)
	{
		return nullptr;
	}

	std::unique_ptr<Texture> texture(new Texture);

	glGenTextures(1, &texture->m_id);
	glBindTexture(GL_TEXTURE_2D, texture->m_id);

	const GLint format{ bpp == 24 ? GL_RGB : GL_RGBA };
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, bufferTGA.get());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _tiling);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _tiling);

	glGenerateMipmap(GL_TEXTURE_2D);

	return texture;
}

//-----------------------------------------------------------------------------

std::unique_ptr<Texture> Texture::createFrameTexture(u32 _format, u32 _type, int _width, int _height)
{
	std::unique_ptr<Texture> texture(new Texture);

	glGenTextures(1, &texture->m_id);
	glBindTexture(GL_TEXTURE_2D, texture->m_id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, _format, _width, _height, 0, _format, _type, nullptr);

	return texture;
}

//-----------------------------------------------------------------------------

Texture::~Texture()
{
	glDeleteTextures(1, &m_id);
}

//-----------------------------------------------------------------------------

Texture::Texture(Texture && _rhs) noexcept
	: m_id(_rhs.m_id)
{
	_rhs.m_id = 0;
}

//-----------------------------------------------------------------------------

Texture & Texture::operator =(Texture && _rhs) noexcept
{
	std::swap(m_id, _rhs.m_id);

	return *this;
}

//-----------------------------------------------------------------------------

void Texture::bind(u16 _slot) const noexcept
{
	glActiveTexture(GL_TEXTURE0 + _slot);
	glBindTexture(GL_TEXTURE_2D, m_id);
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
