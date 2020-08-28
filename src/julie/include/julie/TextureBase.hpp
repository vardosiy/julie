#pragma once

#include "julie/core/Types.hpp"

#include <boost/noncopyable.hpp>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

enum class TextureTiling;
enum class TextureFiltering;

class TextureBase : boost::noncopyable
{
public:
	u32 getHandle() const noexcept;
	u32 getWidth() const noexcept;
	u32 getHeight() const noexcept;

	void bind(u16 _slot) const noexcept;

	void setTiling(TextureTiling _tiling) noexcept;
	void setMagnificationFilteringMode(TextureFiltering _mode) noexcept;
	void setMinificationFilteringMode(TextureFiltering _mode) noexcept;

protected:
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

	TextureBase(s32 _type, u32 _width, u32 _height) noexcept;
	~TextureBase();

	s32 getType() const noexcept;

	static s32 formatToGlValue(Format _format) noexcept;
	static s32 fragmentTypeToGlValue(FragmentType _type) noexcept;

	static float tilingToGlValue(TextureTiling _tiling) noexcept;
	static s32 filteringToGlValue(TextureFiltering _mode) noexcept;

private:
	u32 m_id;
	s32 m_type;

	u32 m_width;
	u32 m_height;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
