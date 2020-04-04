#pragma once

#include "renderer/Types.hpp"
#include "renderer/Texture.hpp"

#include <string_view>
#include <memory>

//-----------------------------------------------------------------------------

namespace jl {
class CubeTexture;
}

class TexturesFactory
{
public:
	static std::unique_ptr<jl::Texture> load2dTextureFromFile(std::string_view _filePath);
	static std::unique_ptr<jl::CubeTexture> loadCubeTextureFromFile(std::string_view _filePath);

	static std::unique_ptr<jl::Texture> createFrameColorTexture(jl::u32 _width, jl::u32 _height);
	static std::unique_ptr<jl::Texture> createFrameDepthTexture(jl::u32 _width, jl::u32 _height);

private:
	static std::unique_ptr<jl::Texture> createFrameTexture(const jl::Texture::InitData& _textureInitData);
};

//-----------------------------------------------------------------------------
