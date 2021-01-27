#include "ui/MainWindow.hpp"
#include "ui/EntitiesWidget.hpp"
#include "ui/PropertiesWidget.hpp"
#include "ui/ViewPropertiesWidget.hpp"
#include "ui_MainWindow.h"

#include "save_restore/JsonProjectSaver.hpp"
#include "save_restore/JsonProjectRestorer.hpp"

#include "julie/managers/AppController.hpp"
#include "julie/managers/ResourceManager.hpp"
#include "julie/managers/MaterialsManager.hpp"

#include "julie/Globals.hpp"
#include "julie/Material.hpp"
#include "julie/Model.hpp"

#include "utils/Utils.hpp"

#include <QKeyEvent>

#include <fstream>

//-----------------------------------------------------------------------------

MainWindow::MainWindow(QMainWindow* parent)
	: QMainWindow(parent)
	, m_entitisWdg(nullptr)
	, m_propertiesWdg(nullptr)
	, m_updateTimer(this)
	, m_camera(0.1f, 100.0f, 30.0f)
{
	m_camera.setPosition(glm::vec3{ 0.0f });
	m_cameraController.setCameraMoveSpeed(3.0f);
	m_cameraController.setCameraRotateSpeed(2.0f);
	m_cameraController.setCamera(&m_camera);

	initUi();

	connect(&m_updateTimer, &QTimer::timeout, this, &MainWindow::update);
	m_updateTimer.start(1);

	m_glLoadedConnection = m_ui->oglw_screen->registerOnGlLoaded([this]()
	{
		m_glLoadedConnection.disconnect();
		onGlLoaded();
	});
}

//-----------------------------------------------------------------------------

MainWindow::~MainWindow()
{
	//std::ofstream file(k_saveFile.data());
	//JsonProjectSaver::save(file, m_scene);
}

//-----------------------------------------------------------------------------

void MainWindow::entitySelected(jl::EntityRef _entity)
{
	//m_propertiesWdg->setActiveItem(_entity);
}

//-----------------------------------------------------------------------------

void MainWindow::materialSelected(jl::Material& _material)
{
	//m_propertiesWdg->setActiveItem(_material);
}

//-----------------------------------------------------------------------------

void MainWindow::resetSelection()
{
	//m_propertiesWdg->reset();
}

//-----------------------------------------------------------------------------

void MainWindow::onEntityMoved(jl::EntityRef _entity)
{
	//m_propertiesWdg->refreshEntityPos();
}

//-----------------------------------------------------------------------------

void MainWindow::onEntityScaled(jl::EntityRef _entity)
{
	//m_propertiesWdg->refreshEntitySize();
}

//-----------------------------------------------------------------------------

void MainWindow::update()
{
	using namespace std::chrono;

	static TimePoint s_lastTime = Clock::now();
	const TimePoint currentTime = Clock::now();

	auto delta = currentTime - s_lastTime;
	s_lastTime = currentTime;

	float deltaf = duration_cast<duration<float>>(delta).count();
	jl::Globals::s_timeTotal += deltaf;
	m_cameraController.update(deltaf);

	m_scene.update(duration_cast<milliseconds>(delta));
	m_viewPropertiesWdg->update();
	m_ui->oglw_screen->repaint();
}

//-----------------------------------------------------------------------------

void MainWindow::onGlLoaded()
{
	AppController::setContextOwner(m_ui->oglw_screen);
	m_ui->oglw_screen->setScene(&m_scene);
	m_ui->oglw_screen->setCamera(&m_camera);

	//m_entitisWdg->setScene(&m_scene);

	initDefaultMaterial();
	initScene();
}

//-----------------------------------------------------------------------------

void MainWindow::initUi()
{
	m_ui = std::make_unique<Ui::MainWindow>();
	m_ui->setupUi(this);

	m_ui->oglw_screen->setActionHandler(this);

	//m_entitisWdg = new EntitiesWidget(m_ui->dock_entities);
	//m_entitisWdg->setEntityActionHandler(this);
	//m_ui->dock_entities->setWidget(m_entitisWdg);

	//m_propertiesWdg = new PropertiesWidget(m_ui->dock_props);
	//m_ui->dock_props->setWidget(m_propertiesWdg);

	m_viewPropertiesWdg = new ViewPropertiesWidget(m_ui->dock_viewProps);
	m_viewPropertiesWdg->setGlWidget(m_ui->oglw_screen);
	m_viewPropertiesWdg->setCameraController(&m_cameraController);
	m_ui->dock_viewProps->setWidget(m_viewPropertiesWdg);
}

//-----------------------------------------------------------------------------

void MainWindow::initScene()
{
	//std::ifstream file(k_saveFile.data());
	//if (file.is_open())
	//{
	//	JsonProjectRestorer restorer(file);
	//	std::optional<jl::Scene> restoredScene = restorer.extractScene();

	//	if (restoredScene)
	//	{
	//		m_scene = std::move(restoredScene.value());
	//	}
	//}

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

void MainWindow::initDefaultMaterial()
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

	//m_entitisWdg->setDefaultMaterial(&material);
}

//-----------------------------------------------------------------------------
