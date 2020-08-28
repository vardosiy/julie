#include "julie/CubeTexture.hpp"
#include "julie/TextureTiling.hpp"
#include "julie/TextureFiltering.hpp"

#include "formats/stb_image.hpp"

#include <glad/glad.h>

#include <utility>
#include <array>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

namespace details {

constexpr u32 k_facesCount = 6;

using OffsetsArray = std::array<std::pair<u32, u32>, k_facesCount>;
OffsetsArray calculateOffsets(u32 _faceWidth)
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
	int width, height, channels;
	u8* buffer = stbi_load(_filePath.data(), &width, &height, &channels, STBI_default);

	ASSERTM(buffer, "Can not load texture from file: {}", _filePath);
	ASSERTM(width > 0 && height > 0, "Invalid texture size");
	ASSERTM(channels == 3 || channels == 4, "Unsupported channels count");
	ASSERTM(width / 4 == height / 3, "Cube texture has invalid aspect ratio");
	if (!buffer || width <= 0 || height <= 0 || (width / 4 == height / 3) || !(channels == 3 || channels == 4))
	{
		stbi_image_free(buffer);
		return nullptr;
	}

	std::unique_ptr<CubeTexture> texture(new CubeTexture(buffer, width, height, channels));
	texture->setMagnificationFilteringMode(TextureFiltering::Linear);
	texture->setMinificationFilteringMode(TextureFiltering::LinearMipmapLinear);

	stbi_image_free(buffer);

	return texture;
}

//-----------------------------------------------------------------------------

CubeTexture::CubeTexture(const u8* _data, u32 _width, u32 _height, u32 _channels)
	: TextureBase(GL_TEXTURE_CUBE_MAP, _width, _height)
{
	bind(0);
	loadDataToGpu(_data, _width / 4, _channels);
	glGenerateMipmap(getType());
}

//-----------------------------------------------------------------------------

u32 CubeTexture::getFaceWidth() const noexcept
{
	return getWidth() / 4;
}

//-----------------------------------------------------------------------------

void CubeTexture::loadDataToGpu(const u8* _data, u32 _faceWidth, u32 _channels)
{
	details::OffsetsArray offsets = details::calculateOffsets(_faceWidth);
	const s32 format = formatToGlValue(_channels == 4 ? Format::Rgba : Format::Rgb);

	u8* faceBuffer = new u8[_faceWidth * _faceWidth * _channels];
	for (u32 i = 0; i < details::k_facesCount; ++i)
	{
		const u32 offsetX = offsets[i].first;
		const u32 offsetY = offsets[i].second;
		extractFace(_data, faceBuffer, _faceWidth, _faceWidth, offsetX, offsetY, _channels);

		const u32 target = GL_TEXTURE_CUBE_MAP_POSITIVE_X + i;
		glTexImage2D(target, 0, format, _faceWidth, _faceWidth, 0, format, GL_UNSIGNED_BYTE, faceBuffer);
	}
	delete[] faceBuffer;
}

//-----------------------------------------------------------------------------

void CubeTexture::extractFace(
	const u8* _pSrc,	// source
	u8* _pDst,			// destination
	u32 _srcRowLength,	// pixels
	u32 _dstRowLength,	// pixels
	u32 _offsetX,		// pixels
	u32 _offsetY,		// pixels
	u32 _channels
)
{
	const u32 srcOffsetXBytes	= _offsetX * _channels;
	const u32 dstRowSize		= _dstRowLength * _channels;
	const u32 dstColumnSize		= _dstRowLength; // because cube face is square

	for (u32 i = 0; i < dstColumnSize; ++i)
	{
		const u32 srcOffsetYBytes = _srcRowLength * _channels * (_offsetY + i);

		const u8* pSrc = _pSrc + srcOffsetXBytes + srcOffsetYBytes;
		u8* pDst = _pDst + dstRowSize * i;

		memcpy_s(pDst, dstRowSize, pSrc, dstRowSize);
	}
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
