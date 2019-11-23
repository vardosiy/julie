#include "rendering/wrappers/Fbo.hpp"
#include "rendering/common/Globals.hpp"

#include "utils/LogDefs.hpp"

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

void checkStatus()
{
	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

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

	glGenFramebuffers(1, &fbo->m_handle);
	fbo->bind();

	GLuint colorTexHandle = fbo->m_colorTexture->getHandle();
	GLuint depthTexHandle = fbo->m_depthTexture->getHandle();
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTexHandle, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexHandle, 0);

	details::checkStatus();

	return fbo;
}

//-----------------------------------------------------------------------------

Fbo::~Fbo()
{
	glDeleteFramebuffers(1, &m_handle);
}

//-----------------------------------------------------------------------------

Fbo::Fbo(Fbo && _rhs) noexcept
	: m_handle(_rhs.m_handle)
	, m_colorTexture(std::move(_rhs.m_colorTexture))
	, m_depthTexture(std::move(_rhs.m_depthTexture))
{
	_rhs.m_handle = 0;
	_rhs.m_colorTexture = nullptr;
	_rhs.m_depthTexture = nullptr;
}

//-----------------------------------------------------------------------------

Fbo & Fbo::operator =(Fbo && _rhs) noexcept
{
	std::swap(m_handle, _rhs.m_handle);
	std::swap(m_colorTexture, _rhs.m_colorTexture);
	std::swap(m_depthTexture, _rhs.m_depthTexture);

	return *this;
}

//-----------------------------------------------------------------------------

void Fbo::bind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_handle);
}

//-----------------------------------------------------------------------------
