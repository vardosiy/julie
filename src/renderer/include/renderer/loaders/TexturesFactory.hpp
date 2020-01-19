#pragma once

#include "renderer/Types.hpp"
#include "renderer/Texture.hpp"

#include <string_view>
#include <memory>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

class CubeTexture;
enum class TextureTiling;

class TexturesFactory
{
public:
	static std::unique_ptr<Texture> load2dTextureFromFile(std::string_view _filePath, TextureTiling _tiling);
	static std::unique_ptr<CubeTexture> loadCubeTextureFromFile(std::string_view _filePath, TextureTiling _tiling);

	static std::unique_ptr<Texture> createFrameColorTexture(u32 _width, u32 _height);
	static std::unique_ptr<Texture> createFrameDepthTexture(u32 _width, u32 _height);

private:
	static std::unique_ptr<Texture> createFrameTexture(const Texture::InitData& _textureInitData);
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
