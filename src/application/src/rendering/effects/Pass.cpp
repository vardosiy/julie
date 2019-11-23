//#include "stdafx.h"
//
//#include "Pass.h"
//#include "Texture.h"
//#include "Shader.h"
//#include "Fbo.h"
//
//#include "SceneManager.h"
//
//#include "Globals.h"
//
////-----------------------------------------------------------------------------
//
//Model Pass::ms_model;
//
////-----------------------------------------------------------------------------
//
//void Pass::SetTarget(FboPtr _pTarget) noexcept
//{
//	m_pTarget = _pTarget;
//}
//
////-----------------------------------------------------------------------------
//
//void Pass::SetShader(ShaderPtr _pShader) noexcept
//{
//	m_pShader = _pShader;
//
//	Uniforms const & uniforms = m_pShader->getUniforms();
//
//	m_bIsBlur = uniforms.u_step != -1;
//
//	m_bIsDof =
//		uniforms.u_near != -1 &&
//		uniforms.u_far != -1 &&
//		uniforms.u_clarity != -1 &&
//		uniforms.u_fade != -1;
//}
//
////-----------------------------------------------------------------------------
//
//void Pass::SetParameters(Array< float > _parameters) noexcept
//{
//	m_parameters = std::move(_parameters);
//
//	if (m_bIsBlur)
//		InitBlurOffsets();
//}
//
////-----------------------------------------------------------------------------
//
//void Pass::SetTextures(Array< TexturePtr > _textures) noexcept
//{
//	m_textures = std::move(_textures);
//
//	const int texturesCount = m_textures.GetSize();
//
//	if (texturesCount != m_texureUniformValue.GetSize())
//		m_texureUniformValue = Array< GLint >(texturesCount);
//
//	for (int i = 0; i < texturesCount; ++i)
//		m_texureUniformValue[i] = i;
//}
//
////-----------------------------------------------------------------------------
//
//void Pass::Run() const
//{
//	m_pTarget->bind();
//
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//	m_pShader->bind();
//	ms_model.bind();
//
//	m_pShader->bindAttributes();
//
//	const int texturesCount = m_textures.GetSize();
//	for (int i = 0; i < texturesCount; ++i)
//		m_textures[i]->bind(i);
//
//	Uniforms const & uniforms = m_pShader->getUniforms();
//	m_pShader->setUniformValue(
//		uniforms.u_texture2D,
//		texturesCount,
//		m_texureUniformValue.GetPtr()
//	);
//
//	if (m_bIsBlur)
//		m_pShader->setUniformValue(uniforms.u_step, m_blurOffsets);
//
//	if (m_bIsDof)
//	{
//		Camera const & cam = SceneManager::GetInstance()->GetCamera();
//
//		m_pShader->setUniformValue(uniforms.u_near, cam.getNear());
//		m_pShader->setUniformValue(uniforms.u_far, cam.getFar());
//		m_pShader->setUniformValue(uniforms.u_clarity, m_parameters[1]);
//		m_pShader->setUniformValue(uniforms.u_fade, m_parameters[2]);
//	}
//
//	if (uniforms.u_limit != -1)
//		m_pShader->setUniformValue(uniforms.u_limit, m_parameters[0]);
//
//	m_pShader->draw(ms_model.getIndeciesCount());
//}
//
////-----------------------------------------------------------------------------
//
//void Pass::InitModel()
//{
//	ms_model.InitRect();
//}
//
////-----------------------------------------------------------------------------
//
//void Pass::InitBlurOffsets()
//{
//	m_blurOffsets.x = 1.0f / Globals::s_screenWidth * m_parameters[0];
//	m_blurOffsets.y = 1.0f / Globals::s_screenHeight * m_parameters[0];
//}
//
////-----------------------------------------------------------------------------
