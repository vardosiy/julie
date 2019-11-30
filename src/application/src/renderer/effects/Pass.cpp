#include "renderer/effects/Pass.hpp"

#include "renderer/gl_primitives/Fbo.hpp"
#include "renderer/shaders/Shader.hpp"
#include "renderer/scene/objects/Model.hpp"

#include "renderer/scene/SceneManager.hpp"
#include "renderer/scene/camera/Camera.hpp"

#include "renderer/common/Globals.hpp"

#include "utils/Assert.hpp"
#include "utils/LogDefs.hpp"

#include <glad/glad.h>

//-----------------------------------------------------------------------------

std::unique_ptr<Model> Pass::ms_model;

//-----------------------------------------------------------------------------

void Pass::setTarget(Fbo * _target) noexcept
{
	m_target = _target;
}

//-----------------------------------------------------------------------------

void Pass::setShader(Shader * _shader) noexcept
{
	m_shader = _shader;

	const ShaderUniforms & uniforms = m_shader->getUniforms();

	m_isBlur = uniforms.u_step != -1;

	m_isDof =
		uniforms.u_near != -1 &&
		uniforms.u_far != -1 &&
		uniforms.u_clarity != -1 &&
		uniforms.u_fade != -1;
}

//-----------------------------------------------------------------------------

void Pass::setParameters(const std::vector<float> & _parameters) noexcept
{
	m_parameters = std::move(_parameters);

	if (m_isBlur)
	{
		initBlurOffsets();
	}
}

//-----------------------------------------------------------------------------

void Pass::setTextures(const std::vector<Texture *> & _textures) noexcept
{
	m_textures = _textures;
	m_texureUniformValue.reserve(m_textures.size());

	const std::size_t texturesCount{ m_textures.size() };
	for (std::size_t i{ 0 }; i < texturesCount; ++i)
	{
		m_texureUniformValue[i] = static_cast<int>(i);
	}
}

//-----------------------------------------------------------------------------

void Pass::run() const
{
	ASSERT(m_target && m_shader, "");

	m_target->bind();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_shader->bind();
	ms_model->bind();

	m_shader->bindAttributes();

	const std::size_t texturesCount{ m_textures.size() };
	for (std::size_t i{ 0 }; i < texturesCount; ++i)
	{
		m_textures[i]->bind(static_cast<uint16_t>(i));
	}

	const ShaderUniforms & uniforms = m_shader->getUniforms();
	m_shader->setUniformValue(
		uniforms.u_texture2D,
		texturesCount,
		m_texureUniformValue.data()
	);

	if (m_isBlur)
	{
		m_shader->setUniformValue(uniforms.u_step, m_blurOffsets);
	}

	if (m_isDof)
	{
		const Camera & camera = SceneManager::getInstance().getCamera();

		m_shader->setUniformValue(uniforms.u_near, camera.getNear());
		m_shader->setUniformValue(uniforms.u_far, camera.getFar());
		m_shader->setUniformValue(uniforms.u_clarity, m_parameters[1]);
		m_shader->setUniformValue(uniforms.u_fade, m_parameters[2]);
	}

	if (uniforms.u_limit != -1)
	{
		m_shader->setUniformValue(uniforms.u_limit, m_parameters[0]);
	}

	m_shader->draw(ms_model->getIndeciesCount());
}

//-----------------------------------------------------------------------------

void Pass::initModel()
{
	ms_model = Model::createRect(glm::vec3{ 0.0f, 0.0f, 0.0f }, glm::vec2{ 1.0f, 1.0f });
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
