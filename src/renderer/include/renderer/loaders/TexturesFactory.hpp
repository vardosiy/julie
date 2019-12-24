#pragma once

#include "renderer/common/Types.hpp"

#include <string_view>
#include <memory>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

class Texture;
class CubeTexture;
enum class TextureTiling;

class TexturesFactory
{
public:
	static std::unique_ptr<Texture> load2dTextureFromFile(std::string_view _filePath, TextureTiling _tiling);
	static std::unique_ptr<CubeTexture> loadCubeTextureFromFile(std::string_view _filePath, TextureTiling _tiling);

	static std::unique_ptr<Texture> createFrameColorTexture(u32 _width, u32 _height);
	static std::unique_ptr<Texture> createFrameDepthTexture(u32 _width, u32 _height);
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
