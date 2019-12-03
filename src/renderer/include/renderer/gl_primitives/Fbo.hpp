#pragma once

#include "renderer/common/Types.hpp"
#include "renderer/gl_primitives/Texture.hpp"

#include <boost/noncopyable.hpp>

#include <memory>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

class Fbo : boost::noncopyable
{
public:
	static std::unique_ptr<Fbo> create();
	static Fbo screen;

public:
	~Fbo();

	Fbo(Fbo && _rhs) noexcept;
	Fbo & operator =(Fbo && _rhs) noexcept;

	void bind() const;

	const Texture & getColorTexture() const noexcept { return *m_colorTexture; }
	const Texture & getDepthTexture() const noexcept { return *m_depthTexture; }

	u32 m_id = 0;

private:
	Fbo() noexcept = default;

private:
	std::unique_ptr<Texture> m_colorTexture;
	std::unique_ptr<Texture> m_depthTexture;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
