#include <glad/glad.h>

#include "logic/Sandbox.hpp"
#include "logic/ResourceManager.hpp"

#include "renderer/common/Globals.hpp"
#include "renderer/scene/Scene.hpp"
#include "renderer/scene/Object.hpp"
#include "renderer/managers/EffectManager.hpp"
#include "renderer/managers/InputManager.hpp"
#include "renderer/loaders/ModelsFactory.hpp"
#include "renderer/loaders/TexturesFactory.hpp"

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

	m_camera = std::make_unique<jl::Camera>(0.000001f, 100.0f, 45.0f);
	m_camera->setMoveSpeed(3.0f);
	m_camera->setRotationSpeed(2.0f);
	m_camera->setPosition(glm::vec3(0.0f, 0.0f, 1.0f));

	m_shaders.emplace_back(jl::Shader::create("res/shaders/SimpleTexture.vs", "res/shaders/SimpleTexture.fs"));
	m_models.emplace_back(jl::ModelsFactory::createRect(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(1.0f, 1.0f)));
	m_textures.emplace_back(jl::TexturesFactory::load2dTextureFromFile("res/textures/Rock.tga", jl::TextureTiling::ClampToEdge));

	std::unique_ptr<jl::Object> obj = std::make_unique<jl::Object>(*m_models[0]);
	obj->setShader(*m_shaders[0]);
	obj->setTextures2D({ m_textures[0].get() });
	obj->setPosition(glm::vec3(0.0f));
	obj->setRotation(glm::vec3(0.0f));
	obj->setScale(glm::vec3(1.0f));

	jl::Scene::getInstance().addObject(0, std::move(obj));
}

//-----------------------------------------------------------------------------

void Sandbox::update(float _dt)
{
	m_camera->update(_dt);
	jl::Scene::getInstance().update(_dt);
	//jl::EffectManager::getInstance().update(_dt);
}

//-----------------------------------------------------------------------------

void Sandbox::draw()
{
	//jl::EffectManager::getInstance().bindFbo();
	jl::Scene::getInstance().draw(*m_camera);
	//jl::EffectManager::getInstance().apply();
}

//-----------------------------------------------------------------------------
