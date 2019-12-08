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

	static void setScreenBufferId(u32 _id);
	static Fbo s_screen;

public:
	~Fbo();

	Fbo(Fbo && _rhs) noexcept;
	Fbo & operator=(Fbo && _rhs) noexcept;

	void bind() const noexcept;

	const Texture * getColorTexture() const noexcept { return m_colorTexture.get(); }
	const Texture * getDepthTexture() const noexcept { return m_depthTexture.get(); }

private:
	Fbo() noexcept = default;

private:
	u32 m_id{ 0 };

	std::unique_ptr<Texture> m_colorTexture;
	std::unique_ptr<Texture> m_depthTexture;
};

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
