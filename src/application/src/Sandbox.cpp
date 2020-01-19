#include <glad/glad.h>

#include "Sandbox.hpp"
#include "managers/ResourceManager.hpp"

#include "renderer/Globals.hpp"
#include "renderer/Shader.hpp"
#include "renderer/scene/Scene.hpp"
#include "renderer/scene/Object.hpp"
#include "renderer/managers/EffectManager.hpp"
#include "renderer/managers/InputManager.hpp"
#include "renderer/loaders/ModelsFactory.hpp"
#include "renderer/loaders/TexturesFactory.hpp"

#include "utils/LogDefs.hpp"

#include <QKeyEvent>

#include <iostream>
#include <chrono>

//-----------------------------------------------------------------------------

void Sandbox::init()
{
	jl::ResourceManager::getInstance().init();

	m_camera = std::make_unique<jl::Camera>(0.000001f, 100.0f, 45.0f);
	m_camera->setMoveSpeed(3.0f);
	m_camera->setRotationSpeed(2.0f);
	m_camera->setPosition(glm::vec3(0.0f, 0.0f, 2.0f));

	m_shaders.emplace_back(jl::Shader::create("res/shaders/SimpleColor.vs",		"res/shaders/SimpleColor.fs"));
	m_shaders.emplace_back(jl::Shader::create("res/shaders/SimpleTexture.vs",	"res/shaders/SimpleTexture.fs"));
	m_models.emplace_back(jl::ModelsFactory::loadFromFile("res/models/bus.nfg"));
	m_textures.emplace_back(jl::TexturesFactory::load2dTextureFromFile("res/textures/Rock.tga", jl::TextureTiling::ClampToEdge));

	auto& material1 = m_materials.emplace_back(new jl::Material);
	material1->setShader(*m_shaders[0]);
	material1->setProperty("u_color", glm::vec4(0.3f, 0.7f, 0.8f, 1.0f));

	auto& material2 = m_materials.emplace_back(new jl::Material);
	material2->setShader(*m_shaders[1]);
	material2->setProperty("u_texture2D", *m_textures[0]);

	std::unique_ptr<jl::Object> obj1 = std::make_unique<jl::Object>(*m_models[0]);
	obj1->setMaterial(*m_materials[1]);
	obj1->setScale(glm::vec3(0.01f));

	jl::Scene::getInstance().addObject(1, std::move(obj1));
}

//-----------------------------------------------------------------------------

void Sandbox::update(float _dt)
{
	m_camera->update(_dt);
	jl::Scene::getInstance().update(_dt);
}

//-----------------------------------------------------------------------------

void Sandbox::draw()
{
	jl::Scene::getInstance().draw(*m_camera);
}

//-----------------------------------------------------------------------------

void Sandbox::onWindowResized(jl::u32 _w, jl::u32 _h)
{
	m_camera->setAspect(static_cast<float>(_w) / static_cast<float>(_h));
}

//-----------------------------------------------------------------------------
