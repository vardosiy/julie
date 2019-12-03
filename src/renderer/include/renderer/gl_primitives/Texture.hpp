#pragma once

#include "renderer/common/Types.hpp"

#include <boost/noncopyable.hpp>

#include <string_view>
#include <memory>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

class Texture : boost::noncopyable
{
public:
	static std::unique_ptr<Texture> create(std::string_view _filePath, u32 _tiling);
	static std::unique_ptr<Texture> createFrameTexture(u32 _format, u32 _type, int _width, int _height);

public:
	~Texture();

	Texture(Texture && _rhs) noexcept;
	Texture & operator =(Texture && _rhs) noexcept;

	void bind(u16 _slot) const noexcept;

	u32 getHandle() const noexcept { return m_id; }

private:
	Texture() noexcept = default;

private:
	u32 m_id;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
