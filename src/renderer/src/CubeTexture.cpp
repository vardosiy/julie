#include "renderer/CubeTexture.hpp"
#include "renderer/TextureTiling.hpp"

#include <glad/glad.h>

#include <utility>
#include <array>

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

constexpr jl::u32 k_facesCount = 6;
using OffsetsArray = std::array<std::pair<jl::u32, jl::u32>, k_facesCount>;

//-----------------------------------------------------------------------------

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

//-----------------------------------------------------------------------------

} // namespace details

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

CubeTexture::CubeTexture(const InitData & _initData) noexcept
	: TextureBase(GL_TEXTURE_CUBE_MAP)
	, m_faceWidth(_initData.width / 4)
{
	bind(0);
	loadDataToGpu(_initData.data.get(), _initData.width, _initData.height, _initData.bpp);
	glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
}

//-----------------------------------------------------------------------------

void CubeTexture::loadDataToGpu(const char * _data, s32 _width, s32 _height, s32 _bpp)
{
	const u32 faceWidth = static_cast<u32>(_width) / 4;
	details::OffsetsArray offsets = details::calculateOffsets(faceWidth);

	char * faceBuffer = new char[faceWidth * faceWidth * _bpp / 8];
	for (s32 i = 0; i < details::k_facesCount; ++i)
	{
		extractFace(_data, faceBuffer, _width, faceWidth, offsets[i].first, offsets[i].second, _bpp);
		s32 target = GL_TEXTURE_CUBE_MAP_POSITIVE_X + i;
		glTexImage2D(target, 0, GL_RGB, faceWidth, faceWidth, 0, GL_RGB, GL_UNSIGNED_BYTE, faceBuffer);
	}
	delete[] faceBuffer;
}

//-----------------------------------------------------------------------------

void CubeTexture::extractFace(
	const char * _pSrc,
	char * _pDst,
	s32 _srcRowLength,	// pixels
	s32 _dstRowLength,	// pixels
	s32 _offsetX,		// pixels
	s32 _offsetY,		// pixels
	s32 _bitsPerPixel
)
{
	const s32 bytesPerPixel		= _bitsPerPixel / 8;

	const s32 srcOffsetXBytes	= _offsetX * bytesPerPixel;
	const s32 dstRowSize		= _dstRowLength * bytesPerPixel;
	const s32 dstColumnSize		= _dstRowLength; // because cube face is square

	for (s32 i = 0; i < dstColumnSize; ++i)
	{
		const s32 srcOffsetYBytes = _srcRowLength * bytesPerPixel * (_offsetY + i);

		const char * pSrc = _pSrc + srcOffsetXBytes + srcOffsetYBytes;
		char * pDst = _pDst + dstRowSize * i;

		memcpy_s(pDst, dstRowSize, pSrc, dstRowSize);
	}
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
