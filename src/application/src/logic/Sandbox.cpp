#include <glad/glad.h>

#include "logic/Sandbox.hpp"
#include "logic/ResourceManager.hpp"

#include "renderer/common/Globals.hpp"
#include "renderer/scene/Scene.hpp"
#include "renderer/managers/EffectManager.hpp"
#include "renderer/managers/InputManager.hpp"
#include "renderer/loaders/ModelsFactory.hpp"

#include "renderer/shaders/Shader.hpp"

#include "utils/LogDefs.hpp"

#include <QKeyEvent>

#include <iostream>
#include <chrono>

//-----------------------------------------------------------------------------

void Sandbox::init()
{
	jl::ResourceManager::getInstance().init();
	//jl::EffectManager::getInstance().init();
	//jl::Fbo::setScreenBufferId(defaultFramebufferObject());

	m_camera = std::make_unique<jl::Camera>(0.000001f, 100.0f, glm::radians(45.0f));
	m_camera->setMoveSpeed(1.0f);
	m_camera->setRotationSpeed(1.0f);

	m_shaders.emplace_back(jl::Shader::create("res/shaders/SimpleColor.vs", "res/shaders/SimpleColor.fs"));
	m_models.emplace_back(jl::ModelsFactory::createRect(glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec2(1.0f, 1.0f)));
}

//-----------------------------------------------------------------------------

void Sandbox::update(float _dt)
{
	jl::Scene::getInstance().update(_dt);
	//jl::EffectManager::getInstance().update(_dt);
}

//-----------------------------------------------------------------------------

void Sandbox::draw()
{
	//jl::EffectManager::getInstance().bindFbo();

	const jl::Model & model = *m_models[0];
	const jl::Shader & shader = *m_shaders[0];

	shader.bind();
	model.bind();

	const jl::ShaderUniforms & uniform = shader.getUniforms();
	shader.setUniformValue(uniform.u_color, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	shader.setUniformValue(uniform.u_color, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

	jl::Scene::getInstance().draw(*m_camera);
	//jl::EffectManager::getInstance().apply();
}

//-----------------------------------------------------------------------------
