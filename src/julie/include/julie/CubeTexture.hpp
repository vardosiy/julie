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
	static std::unique_ptr<CubeTexture> loadFromFile(std::string_view _filePath);

	u32 getFaceWidth() const noexcept;

private:
	CubeTexture(const u8* _data, u32 _width, u32 _height, u32 _channels);

	static void loadDataToGpu(const u8* _data, u32 _faceWidth, u32 _channels);
	static void extractFace(
		const u8* _pSrc,	// source
		u8* _pDst,			// destination
		u32 _srcRowLength,	// pixels
		u32 _dstRowLength,	// pixels
		u32 _offsetX,		// pixels
		u32 _offsetY,		// pixels
		u32 _channels
	);
};

//-----------------------------------------------------------------------------
} // namespace jl
//-----------------------------------------------------------------------------
