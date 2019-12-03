#pragma once

#include "renderer/common/Types.hpp"

#include <boost/noncopyable.hpp>

#include <string_view>
#include <memory>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

class CubeTexture : boost::noncopyable
{
public:
	static std::unique_ptr<CubeTexture> create(std::string_view _filePath, u32 _tiling);

public:
	~CubeTexture();

	CubeTexture(CubeTexture && _rhs) noexcept;
	CubeTexture & operator =(CubeTexture && _rhs) noexcept;

	void bind(u16 _slot) const noexcept;

private:
	CubeTexture() noexcept = default;

private:
	u32 m_id;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
