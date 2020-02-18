#pragma once

#include "renderer/Types.hpp"

#include <boost/noncopyable.hpp>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

enum class TextureTiling;
enum class TextureFilteringMode;

class TextureBase : boost::noncopyable
{
public:
	u32 getHandle() const noexcept;

	void bind(u16 _slot) const noexcept;

	void setTiling(TextureTiling _tiling) noexcept;
	void setMagnificationFilteringMode(TextureFilteringMode _mode) noexcept;
	void setMinificationFilteringMode(TextureFilteringMode _mode) noexcept;

protected:
	TextureBase(s32 _type) noexcept;
	~TextureBase();

private:
	u32 m_id;
	s32 m_type;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
