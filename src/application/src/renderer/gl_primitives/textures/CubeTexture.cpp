#include "renderer/gl_primitives/textures/CubeTexture.hpp"
#include "renderer/loaders/loadTga.hpp"

#include <glad/glad.h>

#include <utility>
#include <array>

namespace details {

//-----------------------------------------------------------------------------

constexpr int k_facesCount{ 6 };
using OffsetsArray = std::array<std::pair<int, int>, k_facesCount>;

//-----------------------------------------------------------------------------

OffsetsArray calculateOffsets(int _faceWidth)
{
	return {
		std::pair{ _faceWidth * 2, _faceWidth },
		std::pair{ 0, _faceWidth },
		std::pair{ _faceWidth, 0 },
		std::pair{ _faceWidth, _faceWidth * 2 },
		std::pair{ _faceWidth, _faceWidth },
		std::pair{ _faceWidth * 3, _faceWidth }
	};
}

//-----------------------------------------------------------------------------

void extractFace(
	const char * _pSrc,
	char * _pDst,
	int _srcRowLength, // pixels
	int _dstRowLength, // pixels
	int _offsetX, // pixels
	int _offsetY, // pixels
	int _bitsPerPixel
)
{
	const int bytesPerPixel = _bitsPerPixel / 8;

	const int dstRowSize = _dstRowLength * bytesPerPixel;
	const int srcOffsetXBytes = _offsetX * bytesPerPixel;

	const int dstColumnSize = _dstRowLength; // because cube face is square

	for (int i{ 0 }; i < dstColumnSize; ++i)
	{
		const int srcOffsetYBytes = _srcRowLength * bytesPerPixel * (_offsetY + i);

		const char * pSrc = _pSrc + srcOffsetXBytes + srcOffsetYBytes;
		char * pDst = _pDst + dstRowSize * i;

		memcpy_s(pDst, dstRowSize, pSrc, dstRowSize);
	}
}

//-----------------------------------------------------------------------------

} // namespace details

//-----------------------------------------------------------------------------

std::unique_ptr<CubeTexture> CubeTexture::create(std::string_view _filePath, uint32_t _tiling)
{
	int width, height, bpp;
	std::unique_ptr<char[]> bufferTGA = loadTga(_filePath, &width, &height, &bpp);
	if (!bufferTGA)
	{
		return nullptr;
	}

	std::unique_ptr<CubeTexture> cubeTexture(new CubeTexture);

	glGenTextures(1, &cubeTexture->m_id);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubeTexture->m_id);

	const int faceWidth{ width / 4 };
	details::OffsetsArray offsets = details::calculateOffsets(faceWidth);

	std::unique_ptr<char[]> bufferFace(new char[faceWidth * faceWidth * bpp / 8]);
	for (int i = 0; i < details::k_facesCount; ++i)
	{
		details::extractFace(bufferTGA.get(), bufferFace.get(), width, faceWidth, offsets[i].first, offsets[i].second, bpp);
		GLenum target = GL_TEXTURE_CUBE_MAP_POSITIVE_X + i;
		glTexImage2D(target, 0, GL_RGB, faceWidth, faceWidth, 0, GL_RGB, GL_UNSIGNED_BYTE, bufferFace.get());
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, _tiling);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, _tiling);

	glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

	return cubeTexture;
}

//-----------------------------------------------------------------------------

CubeTexture::~CubeTexture()
{
	glDeleteTextures(1, &m_id);
}

//-----------------------------------------------------------------------------

CubeTexture::CubeTexture(CubeTexture && _rhs) noexcept
	: m_id(_rhs.m_id)
{
	_rhs.m_id = 0;
}

//-----------------------------------------------------------------------------

CubeTexture & CubeTexture::operator =(CubeTexture && _rhs) noexcept
{
	std::swap(m_id, _rhs.m_id);

	return *this;
}

//-----------------------------------------------------------------------------

void CubeTexture::bind(uint16_t _slot) const noexcept
{
	glActiveTexture(GL_TEXTURE0 + _slot);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_id);
}

//-----------------------------------------------------------------------------
