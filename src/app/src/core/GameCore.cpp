#include "core/GameCore.hpp"

#include "julie/managers/AppController.hpp"
#include "julie/managers/ResourceManager.hpp"
#include "julie/managers/MaterialsManager.hpp"

#include "julie/Globals.hpp"
#include "julie/Material.hpp"
#include "julie/Model.hpp"

#include "utils/Utils.hpp"

//-----------------------------------------------------------------------------

GameCore::GameCore()
	: m_camera(0.1f, 100.0f, 30.0f)
{
	m_camera.setPosition(glm::vec3{ 0.0f });
	m_cameraController.setCameraMoveSpeed(3.0f);
	m_cameraController.setCameraRotateSpeed(2.0f);
	m_cameraController.setCamera(&m_camera);
}

//-----------------------------------------------------------------------------

GameCore::~GameCore()
{
}

//-----------------------------------------------------------------------------

void GameCore::init()
{
	initDefaultMaterial();
	initScene();
}

//-----------------------------------------------------------------------------

void GameCore::update(DeltaTime _dt)
{
	m_transformProcessSystem.update(m_scene.getComponentsMgr());
}

//-----------------------------------------------------------------------------

void GameCore::render()
{
	m_renderSystem.update(m_scene.getComponentsMgr(), m_camera);
}

//-----------------------------------------------------------------------------

void GameCore::initScene()
{
	jl::ResourceManager& resourceMgr = jl::ResourceManager::getInstance();
	jl::MaterialsManager& materialsMgr = jl::MaterialsManager::getInstance();

	jl::Model* model = resourceMgr.loadModel("res/models/mustang/mustang_GT.obj", false);
	ASSERT(model);

	jl::Material* material = materialsMgr.findMaterial("Default");
	const size_t meshesCount = model->getMeshesCount();
	for (size_t i = 0; i < meshesCount; ++i)
	{
		model->getMesh(i).setMaterial(material);
	}

	{
		jl::EntityRef obj = m_scene.createEntity("some_name");
		obj.addComponent<ModelComponent>(model);
		TransformComponent* objTransform = obj.getComponent<TransformComponent>();
		objTransform->pos = glm::vec3{ 0.0f, 0.0f, -1.0f };
		objTransform->scale = glm::vec3{ 0.01f };
	}
	{
		jl::EntityRef light = m_scene.createEntity("light");
		light.addComponent<LightSourceComponent>(glm::vec3{ 0.0f }, glm::vec3{ 1.0f });
		TransformComponent* lightTransform = light.getComponent<TransformComponent>();
		lightTransform->pos = glm::vec3{ 0.0f, 2.0f, -1.0f };
	}
}

//-----------------------------------------------------------------------------

void GameCore::initDefaultMaterial()
{
	jl::Material& material = jl::MaterialsManager::getInstance().createMaterial("Default");

	const jl::Shader* shader = jl::ResourceManager::getInstance().loadShader("res/shaders/composed/MaterialColorShader.shdata");
	material.setShader(shader);

	material.setProperty("u_shininess",		128.0f);
	material.setProperty("u_opacity",		1.0f);
	material.setProperty("u_matAmbient",	glm::vec3{ 1.0f });
	material.setProperty("u_matDiffuse",	glm::vec3{ 1.0f });
	material.setProperty("u_matSpecular",	glm::vec3{ 1.0f });
	material.setProperty("u_texDiffuse",	static_cast<jl::Texture*>(nullptr));
	material.setProperty("u_texNormals",	static_cast<jl::Texture*>(nullptr));
}

//-----------------------------------------------------------------------------
