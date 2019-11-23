#include "rendering/textures/Texture.hpp"

#include "rendering/loaders/loadTga.hpp"

//-----------------------------------------------------------------------------

std::unique_ptr<Texture> Texture::create(std::string_view _filePath, GLenum _tiling)
{
	int width, height, bpp;
	std::unique_ptr<char[]> bufferTGA = loadTga(_filePath, &width, &height, &bpp);
	if (!bufferTGA)
	{
		return nullptr;
	}

	std::unique_ptr<Texture> texture(new Texture);

	glGenTextures(1, &texture->m_handle);
	glBindTexture(GL_TEXTURE_2D, texture->m_handle);

	GLint format{ bpp == 24 ? GL_RGB : GL_RGBA };
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, bufferTGA.get());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _tiling);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _tiling);

	glGenerateMipmap(GL_TEXTURE_2D);

	return texture;
}

//-----------------------------------------------------------------------------

std::unique_ptr<Texture> Texture::createFrameTexture(GLenum _format, GLenum _type, int _width, int _height)
{
	std::unique_ptr<Texture> texture(new Texture);

	glGenTextures(1, &texture->m_handle);
	glBindTexture(GL_TEXTURE_2D, texture->m_handle);

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
	glDeleteTextures(1, &m_handle);
}

//-----------------------------------------------------------------------------

Texture::Texture(Texture && _rhs) noexcept
	: m_handle(_rhs.m_handle)
{
	_rhs.m_handle = 0;
}

//-----------------------------------------------------------------------------

Texture & Texture::operator =(Texture && _rhs) noexcept
{
	std::swap(m_handle, _rhs.m_handle);

	return *this;
}

//-----------------------------------------------------------------------------

void Texture::bind(unsigned short _slot) const noexcept
{
	glActiveTexture(GL_TEXTURE0 + _slot);
	glBindTexture(GL_TEXTURE_2D, m_handle);
}

//-----------------------------------------------------------------------------
