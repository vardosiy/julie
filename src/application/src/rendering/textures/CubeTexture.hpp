#pragma once

#include <glad/glad.h>

#include <boost/noncopyable.hpp>

#include <string_view>
#include <memory>

class CubeTexture : boost::noncopyable
{
public:
	static std::unique_ptr<CubeTexture> create(std::string_view _filePath, GLenum _tiling);

public:
	~CubeTexture();

	CubeTexture(CubeTexture && _rhs) noexcept;
	CubeTexture & operator =(CubeTexture && _rhs) noexcept;

	void bind(unsigned short _slot) const noexcept;

private:
	CubeTexture() noexcept = default;

private:
	GLuint m_handle;
};
