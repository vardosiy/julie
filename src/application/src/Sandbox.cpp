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
#include "renderer/loaders/ShadersFactory.hpp"
#include "renderer/loaders/TexturesFactory.hpp"

#include "utils/LogDefs.hpp"

#include <iostream>
#include <chrono>

//-----------------------------------------------------------------------------

void Sandbox::init()
{
	initResources();

	m_camera = std::make_unique<jl::FreeflyCamera>(0.000001f, 100.0f, 45.0f);
	m_camera->setMoveSpeed(3.0f);
	m_camera->setRotationSpeed(2.0f);
	m_camera->setPosition(glm::vec3(0.0f, 0.0f, 2.0f));

	std::unique_ptr<jl::Object> obj1 = std::make_unique<jl::Object>(*m_models[0]);
	obj1->setMaterial(*m_materials[1]);
	obj1->setScale(glm::vec3(0.01f));

	m_scene.addObject(1, std::move(obj1));

	//std::vector<jl::s32> objectIds;
	//m_scene.forEachObject(
	//	[&objectIds](jl::s32 _id, jl::Object& _obj)
	//	{
	//		objectIds.emplace_back(_id);
	//	}
	//);
}

//-----------------------------------------------------------------------------

void Sandbox::initResources()
{
	m_models.emplace_back(jl::ModelsFactory::loadFromFile("res/models/bus.nfg"));

	m_shaders.emplace_back(jl::ShadersFactory::load("res/shaders/SimpleColor.vs", "res/shaders/SimpleColor.fs"));
	m_shaders.emplace_back(jl::ShadersFactory::load("res/shaders/SimpleTexture.vs", "res/shaders/SimpleTexture.fs"));

	m_textures.emplace_back(jl::TexturesFactory::load2dTextureFromFile("res/textures/Rock.tga"));
	m_textures.back()->setTiling(jl::TextureTiling::ClampToEdge);

	m_textures.emplace_back(jl::TexturesFactory::load2dTextureFromFile("res/textures/Bus.tga"));
	m_textures.back()->setTiling(jl::TextureTiling::ClampToEdge);

	auto& material1 = m_materials.emplace_back(new jl::Material);
	material1->setShader(*m_shaders[0]);
	material1->setProperty("u_color", glm::vec4(0.3f, 0.7f, 0.8f, 1.0f));

	auto& material2 = m_materials.emplace_back(new jl::Material);
	material2->setShader(*m_shaders[1]);
	material2->setProperty("u_texture2D", *m_textures[1]);
}

//-----------------------------------------------------------------------------

void Sandbox::update(float _dt)
{
	m_camera->update(_dt);
	m_scene.update(_dt);
}

//-----------------------------------------------------------------------------

void Sandbox::draw()
{
	m_scene.draw(*m_camera);
}

//-----------------------------------------------------------------------------

void Sandbox::onWindowResized(jl::u32 _w, jl::u32 _h)
{
	m_camera->setAspect(static_cast<float>(_w) / static_cast<float>(_h));
}

//-----------------------------------------------------------------------------
