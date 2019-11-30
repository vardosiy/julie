#pragma once

#include <boost/noncopyable.hpp>

#include <string_view>
#include <memory>

class CubeTexture : boost::noncopyable
{
public:
	static std::unique_ptr<CubeTexture> create(std::string_view _filePath, uint32_t _tiling);

public:
	~CubeTexture();

	CubeTexture(CubeTexture && _rhs) noexcept;
	CubeTexture & operator =(CubeTexture && _rhs) noexcept;

	void bind(uint16_t _slot) const noexcept;

private:
	CubeTexture() noexcept = default;

private:
	uint32_t m_id;
};
