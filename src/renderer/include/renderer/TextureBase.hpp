#pragma once

#include "renderer/Types.hpp"

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

	void bind(u16 _slot) const noexcept;

	void setTiling(TextureTiling _tiling) noexcept;
	void setMagnificationFilteringMode(TextureFiltering _mode) noexcept;
	void setMinificationFilteringMode(TextureFiltering _mode) noexcept;

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
