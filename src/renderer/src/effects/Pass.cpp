#include "renderer/effects/Pass.hpp"

#include "renderer/common/Globals.hpp"
#include "renderer/managers/SceneManager.hpp"

#include "renderer/loaders/ModelsFactory.hpp"
#include "renderer/scene/Model.hpp"
#include "renderer/scene/Camera.hpp"
#include "renderer/gl_primitives/Fbo.hpp"
#include "renderer/gl_primitives/Texture.hpp"
#include "renderer/shaders/Shader.hpp"

#include "utils/Assert.hpp"
#include "utils/LogDefs.hpp"

#include <glad/glad.h>

//-----------------------------------------------------------------------------

namespace jl {

//-----------------------------------------------------------------------------

std::unique_ptr<Model> Pass::ms_model;

//-----------------------------------------------------------------------------

void Pass::setTarget(const Fbo & _target) noexcept
{
	m_target = &_target;
}

//-----------------------------------------------------------------------------

void Pass::setShader(const Shader & _shader) noexcept
{
	m_shader = &_shader;

	const ShaderUniforms & uniforms = m_shader->getUniforms();

	m_bIsBlur = uniforms.u_step != -1;

	m_bIsDof =
		uniforms.u_near != -1 &&
		uniforms.u_far != -1 &&
		uniforms.u_clarity != -1 &&
		uniforms.u_fade != -1;
}

//-----------------------------------------------------------------------------

void Pass::setParameters(const std::vector<float> & _parameters) noexcept
{
	m_parameters = _parameters;

	if (m_bIsBlur)
	{
		initBlurOffsets();
	}
}

//-----------------------------------------------------------------------------

void Pass::setTextures(const std::vector<const Texture *> & _textures) noexcept
{
	m_textures = _textures;
	m_texureUniformValue.reserve(m_textures.size());

	const s32 texturesCount = static_cast<s32>(m_textures.size());
	for (s32 i = 0; i < texturesCount; ++i)
	{
		m_texureUniformValue.push_back(i);
	}
}

//-----------------------------------------------------------------------------

void Pass::run() const
{
	ASSERTM(m_target && m_shader, "PostFX pass is not complitely initialized before it being used");
	if (!m_target || !m_shader)
	{
		return;
	}

	m_target->bind();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_shader->bind();

	const std::size_t texturesCount = m_textures.size();
	for (std::size_t i = 0; i < texturesCount; ++i)
	{
		m_textures[i]->bind(static_cast<u16>(i));
	}

	const ShaderUniforms & uniforms = m_shader->getUniforms();
	m_shader->setUniformValue(
		uniforms.u_texture2D,
		texturesCount,
		m_texureUniformValue.data()
	);

	if (m_bIsBlur)
	{
		m_shader->setUniformValue(uniforms.u_step, m_blurOffsets);
	}

	if (m_bIsDof)
	{
		const Camera & camera = Scene::getInstance().getCamera();

		m_shader->setUniformValue(uniforms.u_near, camera.getNear());
		m_shader->setUniformValue(uniforms.u_far, camera.getFar());
		m_shader->setUniformValue(uniforms.u_clarity, m_parameters[1]);
		m_shader->setUniformValue(uniforms.u_fade, m_parameters[2]);
	}

	if (uniforms.u_limit != -1)
	{
		m_shader->setUniformValue(uniforms.u_limit, m_parameters[0]);
	}

	m_shader->draw(*ms_model);
}

//-----------------------------------------------------------------------------

void Pass::initModel()
{
	ms_model = ModelsFactory::createRect(glm::vec3{ -1.0f, -1.0f, 0.0f }, glm::vec2{ 2.0f, 2.0f });
}

//-----------------------------------------------------------------------------

void Pass::destroyModel()
{
	ms_model.reset();
}

//-----------------------------------------------------------------------------

void Pass::initBlurOffsets()
{
	m_blurOffsets.x = 1.0f / Globals::s_screenWidth * m_parameters[0];
	m_blurOffsets.y = 1.0f / Globals::s_screenHeight * m_parameters[0];
}

//-----------------------------------------------------------------------------

} // namespace jl

//-----------------------------------------------------------------------------
