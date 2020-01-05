#pragma once

#include "renderer/Types.hpp"
#include "renderer/TextureTiling.hpp"
#include "renderer/TextureFilteringMode.hpp"

#include <boost/noncopyable.hpp>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

class TextureBase : boost::noncopyable
{
public:
	u32 getHandle() const noexcept { return m_id; }

	void bind(u16 _slot) const noexcept;

	void setTiling(TextureTiling _tiling) noexcept;
	void setMagnificationFilteringMode(TextureFilteringMode _mode) noexcept;
	void setMinificationFilteringMode(TextureFilteringMode _mode) noexcept;

protected:
	TextureBase(s32 _type) noexcept;
	~TextureBase();

	static float tilingToGlValue(TextureTiling _tiling);
	static s32 filteringModeToGlValue(TextureFilteringMode _mode);

private:
	u32 m_id;
	s32 m_type;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
