#pragma once

#include <glad/glad.h>

#include <boost/noncopyable.hpp>

#include <string_view>
#include <memory>

class Texture : boost::noncopyable
{
public:
	static std::unique_ptr<Texture> create(std::string_view _filePath, GLenum _tiling);
	static std::unique_ptr<Texture> createFrameTexture(GLenum _format, GLenum _type, int _width, int _height);

public:
	~Texture();

	Texture(Texture && _rhs) noexcept;
	Texture & operator =(Texture && _rhs) noexcept;

	void bind(unsigned short _slot = 0) const noexcept;

	GLuint getHandle() const noexcept { return m_handle; }

private:
	Texture() noexcept = default;

private:
	GLuint m_handle;
};
