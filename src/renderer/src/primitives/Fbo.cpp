//#include "renderer/primitives/Fbo.hpp"
//
//#include "renderer/loaders/TexturesFactory.hpp"
//#include "renderer/Types.hpp"
//#include "renderer/Globals.hpp"
//
//#include "utils/LogDefs.hpp"
//
//#include <glad/glad.h>
//
////-----------------------------------------------------------------------------
//
//namespace details {
//
////-----------------------------------------------------------------------------
//
//void checkFramebufferStatus()
//{
//	jl::u32 status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
//
//	switch (status)
//	{
//		case GL_FRAMEBUFFER_COMPLETE:
//			break;
//
//		case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
//			LOG_ERROR("FrameBuffer error: incomplete attachment");
//			break;
//
//		case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
//			LOG_ERROR("FrameBuffer error: missing attachment");
//			break;
//
//		case GL_FRAMEBUFFER_UNSUPPORTED:
//			LOG_ERROR("FrameBuffer error: unsupported");
//			break;
//
//		default:
//			LOG_ERROR("FrameBuffer error");
//	}
//}
//
////-----------------------------------------------------------------------------
//
//} // namespace details
//
////-----------------------------------------------------------------------------
//
//namespace jl {
//
////-----------------------------------------------------------------------------
//
//Fbo Fbo::s_screen;
//
////-----------------------------------------------------------------------------
//
//std::unique_ptr<Fbo> Fbo::create()
//{
//	auto colorTexture = TexturesFactory::createFrameColorTexture(Globals::s_screenWidth, Globals::s_screenHeight);
//	if (!colorTexture)
//	{
//		LOG_ERROR("Can not create frame texture for storage of color");
//		return nullptr;
//	}
//
//	auto depthTexture = TexturesFactory::createFrameDepthTexture(Globals::s_screenWidth, Globals::s_screenHeight);
//	if (!depthTexture)
//	{
//		LOG_ERROR("Can not create frame texture for storage of depth");
//		return nullptr;
//	}
//
//	std::unique_ptr<Fbo> fbo(new Fbo);
//
//	fbo->m_colorTexture = std::move(colorTexture);
//	fbo->m_depthTexture = std::move(depthTexture);
//
//	glGenFramebuffers(1, &fbo->m_id);
//	fbo->bind();
//
//	const u32 colorTexHandle = fbo->m_colorTexture->getHandle();
//	const u32 depthTexHandle = fbo->m_depthTexture->getHandle();
//	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTexHandle, 0);
//	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexHandle, 0);
//
//	details::checkFramebufferStatus();
//
//	return fbo;
//}
//
////-----------------------------------------------------------------------------
//
//void Fbo::setScreenBufferId(u32 _id)
//{
//	s_screen.m_id = _id;
//}
//
////-----------------------------------------------------------------------------
//
//Fbo::~Fbo()
//{
//	glDeleteFramebuffers(1, &m_id);
//}
//
////-----------------------------------------------------------------------------
//
//void Fbo::bind() const noexcept
//{
//	glBindFramebuffer(GL_FRAMEBUFFER, m_id);
//}
//
////-----------------------------------------------------------------------------
//
//Fbo::Fbo() noexcept
//	: m_id(0)
//{
//}
//
////-----------------------------------------------------------------------------
//
//} // namespace jl
//
////-----------------------------------------------------------------------------
