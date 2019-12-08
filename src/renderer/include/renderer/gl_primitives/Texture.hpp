#pragma once

#include "renderer/gl_primitives/TextureBase.hpp"

#include <string_view>
#include <memory>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

enum class TextureTiling;

class Texture : public TextureBase
{
public:
	static std::unique_ptr<Texture> create(std::string_view _filePath, TextureTiling _tiling);
	static std::unique_ptr<Texture> createFrameTexture(u32 _format, u32 _type, int _width, int _height);

public:
	~Texture() = default;

	Texture(Texture && _rhs) noexcept;
	Texture & operator=(Texture && _rhs) noexcept;

	void bind(u16 _slot) const noexcept;

private:
	Texture() noexcept = default;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
