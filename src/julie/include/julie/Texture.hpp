#pragma once

#include "julie/TextureBase.hpp"

#include <string_view>
#include <memory>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

class Texture : public TextureBase
{
public:
	static std::unique_ptr<Texture> loadFromFile(std::string_view _filePath);
	static std::unique_ptr<Texture> createColorTexture(u32 _width, u32 _height);
	static std::unique_ptr<Texture> createDepthTexture(u32 _width, u32 _height);

private:
	Texture(const u8* _data, u32 _width, u32 _height, Format _format, FragmentType _fragmentType);
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
