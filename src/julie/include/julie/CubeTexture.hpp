#pragma once

#include "julie/TextureBase.hpp"

#include <string_view>
#include <memory>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

class CubeTexture : public TextureBase
{
public:
	static std::unique_ptr<jl::CubeTexture> loadFromFile(std::string_view _filePath);

	u32 getFaceWidth() const noexcept;

private:
	CubeTexture(const char* _data, u32 _width, u32 _height, u32 _bpp);

	static void loadDataToGpu(const char* _data, u32 _faceWidth, u32 _bpp);
	static void extractFace(
		const char* _pSrc,	// source
		char* _pDst,		// destination
		u32 _srcRowLength,	// pixels
		u32 _dstRowLength,	// pixels
		u32 _offsetX,		// pixels
		u32 _offsetY,		// pixels
		u32 _bpp
	);
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
