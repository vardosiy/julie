#include "renderer/CubeTexture.hpp"
#include "renderer/TextureTiling.hpp"
#include "renderer/TextureFiltering.hpp"

#include "formats/LoadTga.hpp"

#include <glad/glad.h>

#include <utility>
#include <array>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

namespace details {

constexpr jl::u32 k_facesCount = 6;

using OffsetsArray = std::array<std::pair<jl::u32, jl::u32>, k_facesCount>;
OffsetsArray calculateOffsets(jl::u32 _faceWidth)
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

} // namespace details

//-----------------------------------------------------------------------------

std::unique_ptr<CubeTexture> CubeTexture::loadFromFile(std::string_view _filePath)
{
	int width, height, bpp;
	std::unique_ptr<char[]> tgaBuffer(loadTga(_filePath.data(), &width, &height, &bpp));

	ASSERTM(tgaBuffer, "Can not load texture from file: {}", _filePath);
	ASSERTM(width > 0 && height > 0, "Invalid texture size");
	ASSERTM(bpp == 24 || bpp == 32, "Unsupported bpp");
	ASSERTM(width / 4 == height / 3, "Cube texture has invalid aspect ratio");
	if (!tgaBuffer || width <= 0 || height <= 0 || (width / 4 == height / 3) || !(bpp == 24 || bpp == 32))
	{
		return nullptr;
	}

	std::unique_ptr<CubeTexture> texture(new CubeTexture(tgaBuffer.get(), width, height, bpp));
	texture->setMagnificationFilteringMode(TextureFiltering::Linear);
	texture->setMinificationFilteringMode(TextureFiltering::LinearMipmapLinear);
	return texture;
}

//-----------------------------------------------------------------------------

CubeTexture::CubeTexture(const char* _data, u32 _width, u32 _height, u32 _bpp)
	: TextureBase(GL_TEXTURE_CUBE_MAP, _width, _height)
{
	bind(0);
	loadDataToGpu(_data, _width / 4, _bpp);
	glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
}

//-----------------------------------------------------------------------------

u32 CubeTexture::getFaceWidth() const noexcept
{
	return getWidth() / 4;
}

//-----------------------------------------------------------------------------

void CubeTexture::loadDataToGpu(const char* _data, u32 _faceWidth, u32 _bpp)
{
	details::OffsetsArray offsets = details::calculateOffsets(_faceWidth);

	char* faceBuffer = new char[_faceWidth * _faceWidth * _bpp / 8];
	for (u32 i = 0; i < details::k_facesCount; ++i)
	{
		const u32 offsetX = offsets[i].first;
		const u32 offsetY = offsets[i].second;
		extractFace(_data, faceBuffer, _faceWidth, _faceWidth, offsetX, offsetY, _bpp);

		const u32 target = GL_TEXTURE_CUBE_MAP_POSITIVE_X + i;
		glTexImage2D(target, 0, GL_RGB, _faceWidth, _faceWidth, 0, GL_RGB, GL_UNSIGNED_BYTE, faceBuffer);
	}
	delete[] faceBuffer;
}

//-----------------------------------------------------------------------------

void CubeTexture::extractFace(
	const char* _pSrc,	// source
	char* _pDst,		// destination
	u32 _srcRowLength,	// pixels
	u32 _dstRowLength,	// pixels
	u32 _offsetX,		// pixels
	u32 _offsetY,		// pixels
	u32 _bpp
)
{
	const u32 bytesPerPixel		= _bpp / 8;

	const u32 srcOffsetXBytes	= _offsetX * bytesPerPixel;
	const u32 dstRowSize		= _dstRowLength * bytesPerPixel;
	const u32 dstColumnSize		= _dstRowLength; // because cube face is square

	for (u32 i = 0; i < dstColumnSize; ++i)
	{
		const u32 srcOffsetYBytes = _srcRowLength * bytesPerPixel * (_offsetY + i);

		const char * pSrc = _pSrc + srcOffsetXBytes + srcOffsetYBytes;
		char * pDst = _pDst + dstRowSize * i;

		memcpy_s(pDst, dstRowSize, pSrc, dstRowSize);
	}
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
