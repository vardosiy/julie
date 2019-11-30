#pragma once

#include <boost/noncopyable.hpp>

#include <string_view>
#include <memory>

class Texture : boost::noncopyable
{
public:
	static std::unique_ptr<Texture> create(std::string_view _filePath, uint32_t _tiling);
	static std::unique_ptr<Texture> createFrameTexture(uint32_t _format, uint32_t _type, int _width, int _height);

public:
	~Texture();

	Texture(Texture && _rhs) noexcept;
	Texture & operator =(Texture && _rhs) noexcept;

	void bind(uint16_t _slot) const noexcept;

	uint32_t getHandle() const noexcept { return m_id; }

private:
	Texture() noexcept = default;

private:
	uint32_t m_id;
};
