#include "renderer/gl_primitives/Fbo.hpp"

#include "renderer/common/Types.hpp"
#include "renderer/common/Globals.hpp"

#include "utils/LogDefs.hpp"

#include <glad/glad.h>

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

void checkStatus()
{
	jl::u32 status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	switch (status)
	{
		case GL_FRAMEBUFFER_COMPLETE:
		break;

		case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
		LOG_ERROR("FrameBuffer error: incomplete attachment");
		break;

		case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
		LOG_ERROR("FrameBuffer error: missing attachment");
		break;

		case GL_FRAMEBUFFER_UNSUPPORTED:
		LOG_ERROR("FrameBuffer error: unsupported");
		break;

		default:
		LOG_ERROR("FrameBuffer error");
	}
}

//-----------------------------------------------------------------------------

} // namespace details

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

Fbo Fbo::screen;

//-----------------------------------------------------------------------------

std::unique_ptr<Fbo> Fbo::create()
{
	auto colorTexture = Texture::createFrameTexture(GL_RGBA, GL_UNSIGNED_BYTE, Globals::s_screenWidth, Globals::s_screenHeight);
	if (!colorTexture)
	{
		LOG_ERROR("Can not create frame texture for storage of color");
		return nullptr;
	}

	auto depthTexture = Texture::createFrameTexture(GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, Globals::s_screenWidth, Globals::s_screenHeight);
	if (!depthTexture)
	{
		LOG_ERROR("Can not create frame texture for storage of depth");
		return nullptr;
	}

	std::unique_ptr<Fbo> fbo(new Fbo);

	fbo->m_colorTexture = std::move(colorTexture);
	fbo->m_depthTexture = std::move(depthTexture);

	glGenFramebuffers(1, &fbo->m_id);
	fbo->bind();

	const u32 colorTexHandle{ fbo->m_colorTexture->getHandle() };
	const u32 depthTexHandle{ fbo->m_depthTexture->getHandle() };
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTexHandle, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexHandle, 0);

	details::checkStatus();

	return fbo;
}

//-----------------------------------------------------------------------------

Fbo::~Fbo()
{
	glDeleteFramebuffers(1, &m_id);
}

//-----------------------------------------------------------------------------

Fbo::Fbo(Fbo && _rhs) noexcept
	: m_id(_rhs.m_id)
	, m_colorTexture(std::move(_rhs.m_colorTexture))
	, m_depthTexture(std::move(_rhs.m_depthTexture))
{
	_rhs.m_id = 0;
	_rhs.m_colorTexture = nullptr;
	_rhs.m_depthTexture = nullptr;
}

//-----------------------------------------------------------------------------

Fbo & Fbo::operator =(Fbo && _rhs) noexcept
{
	std::swap(m_id, _rhs.m_id);
	std::swap(m_colorTexture, _rhs.m_colorTexture);
	std::swap(m_depthTexture, _rhs.m_depthTexture);

	return *this;
}

//-----------------------------------------------------------------------------

void Fbo::bind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_id);
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
