#pragma once

#include "renderer/common/Types.hpp"

#include <boost/noncopyable.hpp>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

enum class TextureTiling;

class TextureBase : boost::noncopyable
{
public:
	u32 getHandle() const noexcept { return m_id; }

protected:
	TextureBase() = default;
	~TextureBase();

	TextureBase(TextureBase && _rhs) noexcept;
	TextureBase & operator =(TextureBase && _rhs) noexcept;

	void bindInternal(u32 _textureType, u16 _slot) const noexcept;

	void genTexture(u32 _textureType) noexcept;
	void performBasicSetup(u32 _textureType, TextureTiling _tiling) noexcept;

private:
	u32 m_id;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
