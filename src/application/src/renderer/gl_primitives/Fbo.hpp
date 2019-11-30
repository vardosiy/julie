#pragma once

#include "renderer/gl_primitives/textures/Texture.hpp"

#include <boost/noncopyable.hpp>

#include <cstdint>
#include <memory>

class Fbo : boost::noncopyable
{
public:
	static std::unique_ptr<Fbo> create();

public:
	~Fbo();

	Fbo(Fbo && _rhs) noexcept;
	Fbo & operator =(Fbo && _rhs) noexcept;

	void bind() const;

	Texture & getColorTexture() const noexcept { return *m_colorTexture; }
	Texture & getDepthTexture() const noexcept { return *m_depthTexture; }

private:
	Fbo() noexcept = default;

private:
	uint32_t m_id;
	std::unique_ptr<Texture> m_colorTexture;
	std::unique_ptr<Texture> m_depthTexture;
};
