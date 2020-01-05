#pragma once

#include "renderer/TextureBase.hpp"

#include <string_view>
#include <memory>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

class CubeTexture : public TextureBase
{
public:
	struct InitData
	{
		std::unique_ptr<char[]> data;
		u32 width;
		u32 height;
		u32 bpp;
	};

public:
	CubeTexture(const InitData & _initData) noexcept;

	u32 getFaceWidth() const noexcept { return m_faceWidth; }

private:
	static void loadDataToGpu(const char * _data, s32 _width, s32 _height, s32 _bpp);
	static void extractFace(
		const char * _pSrc,
		char * _pDst,
		s32 _srcRowLength,	// pixels
		s32 _dstRowLength,	// pixels
		s32 _offsetX,		// pixels
		s32 _offsetY,		// pixels
		s32 _bitsPerPixel
	);

private:
	u32 m_faceWidth;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
