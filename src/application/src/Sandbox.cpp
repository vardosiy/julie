#include <glad/glad.h>

#include "Sandbox.hpp"

#include "renderer/common/Globals.hpp"
#include "renderer/managers/SceneManager.hpp"
#include "renderer/managers/ResourceManager.hpp"
#include "renderer/managers/EffectManager.hpp"
#include "renderer/managers/InputManager.hpp"

#include "renderer/shaders/Shader.hpp"

#include "utils/LogDefs.hpp"

#include <QKeyEvent>

#include <iostream>
#include <chrono>

//-----------------------------------------------------------------------------

void Sandbox::init()
{
	m_shaders.emplace_back(jl::Shader::create("res/shaders/SimpleColor.vs", "res/shaders/SimpleColor.fs"));
	m_models.emplace_back(jl::Model::createRect(glm::vec3{ -0.5f, -0.5f, 0.0f }, glm::vec2{ 1.0f, 1.0f }));

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

//-----------------------------------------------------------------------------

void Sandbox::update(float _dt)
{
}

//-----------------------------------------------------------------------------

void Sandbox::draw()
{
	const jl::Model & model = *m_models[0];
	const jl::Shader & shader = *m_shaders[0];

	shader.bind();
	model.bind();

	const jl::ShaderUniforms & uniform = shader.getUniforms();
	shader.setUniformValue(uniform.u_color, glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f });
	shader.setUniformValue(uniform.u_color, glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f });

	shader.draw(model.getIndeciesCount());
}

//-----------------------------------------------------------------------------
