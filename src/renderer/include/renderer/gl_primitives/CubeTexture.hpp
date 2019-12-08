#pragma once

#include "renderer/gl_primitives/TextureBase.hpp"

#include <string_view>
#include <memory>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

enum class TextureTiling;

class CubeTexture : public TextureBase
{
public:
	static std::unique_ptr<CubeTexture> create(std::string_view _filePath, TextureTiling _tiling);

public:
	~CubeTexture() = default;

	CubeTexture(CubeTexture && _rhs) noexcept;
	CubeTexture & operator=(CubeTexture && _rhs) noexcept;

	void bind(u16 _slot) const noexcept;

private:
	CubeTexture() noexcept = default;

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
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
