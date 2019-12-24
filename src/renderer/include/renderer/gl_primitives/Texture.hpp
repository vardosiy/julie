#pragma once

#include "renderer/gl_primitives/TextureBase.hpp"

#include <string_view>
#include <memory>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

class Texture : public TextureBase
{
public:
	enum class Format
	{
		Rgb,
		Rgba,
		DepthComponent,
	};

	enum class FragmentType
	{
		UnsignedByte,
		UnsignedInt,
	};

	struct InitData
	{
		Format format;
		FragmentType fragmentType;

		std::unique_ptr<char[]> data;
		u32 width;
		u32 height;
	};

public:
	Texture(const InitData & _initData) noexcept;

	u32 getWidth() const noexcept	{ return m_width; }
	u32 getHeight() const noexcept	{ return m_height; }

private:
	static s32 formatToGlValue(Format _format);
	static s32 fragmentTypeToGlValue(FragmentType _type);

private:
	u32 m_width;
	u32 m_height;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
