#pragma once

#include "renderer/TextureBase.hpp"

#include <string_view>
#include <memory>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

class CubeTexture : public TextureBase
{
//-----------------------------------------------------------------------------
public:
	struct InitData
	{
		std::unique_ptr<char[]> data;
		u32 width;
		u32 height;
		u32 bpp;
	};
	
//-----------------------------------------------------------------------------
	CubeTexture(const InitData& _initData) noexcept;

	u32 getFaceWidth() const noexcept { return m_faceWidth; }

//-----------------------------------------------------------------------------
private:
	static void loadDataToGpu(const char* _data, u32 _width, u32 _height, u32 _bpp);
	static void extractFace(
		const char* _pSrc,	// source
		char* _pDst,		// destination
		u32 _srcRowLength,	// pixels
		u32 _dstRowLength,	// pixels
		u32 _offsetX,		// pixels
		u32 _offsetY,		// pixels
		u32 _bpp
	);
	
//-----------------------------------------------------------------------------
	u32 m_faceWidth;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
