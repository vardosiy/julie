#include "ui/MainWindow.hpp"
#include "ui/EntitiesWidget.hpp"
#include "ui/PropertiesWidget.hpp"
#include "ui/ViewPropertiesWidget.hpp"
#include "ui_MainWindow.h"

#include "data/SceneWrapper.hpp"
#include "data/ObjectWrapper.hpp"

#include "save_restore/JsonProjectSaver.hpp"
#include "save_restore/JsonProjectRestorer.hpp"

#include "julie/managers/AppController.hpp"
#include "julie/managers/ResourceManager.hpp"
#include "julie/managers/MaterialsManager.hpp"
#include "julie/Globals.hpp"
#include "julie/Material.hpp"

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
	m_camera.setPosition(glm::vec3(1.0f, 2.0f, 5.0f));
	m_cameraController.setCameraMoveSpeed(3.0f);
	m_cameraController.setCameraRotateSpeed(2.0f);
	m_cameraController.setCamera(&m_camera);

	setupUi();

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
	std::ofstream file(k_saveFile.data());
	JsonProjectSaver::save(file, *m_sceneWrapper);
}

//-----------------------------------------------------------------------------

void MainWindow::objectSelected(ObjectWrapper& _objWrapper)
{
	m_propertiesWdg->setActiveEntity(_objWrapper);
}

//-----------------------------------------------------------------------------

void MainWindow::materialSelected(jl::Material& _material)
{
	m_propertiesWdg->setActiveEntity(_material);
	m_ui->oglw_screen->resetSelectedObj();
}

//-----------------------------------------------------------------------------

void MainWindow::resetSelection()
{
	m_propertiesWdg->reset();
	m_ui->oglw_screen->resetSelectedObj();
}

//-----------------------------------------------------------------------------

void MainWindow::onObjectMoved(ObjectWrapper& _objWrapper)
{
	m_propertiesWdg->refreshObjectPos();
}

//-----------------------------------------------------------------------------

void MainWindow::onObjectScaled(ObjectWrapper& _objWrapper)
{
	m_propertiesWdg->refreshObjectSize();
}

//-----------------------------------------------------------------------------

void MainWindow::update()
{
	static TimePoint s_lastTime = Clock::now();
	const TimePoint currentTime = Clock::now();

	auto durationFloat = std::chrono::duration_cast<std::chrono::duration<float>>(currentTime - s_lastTime);
	s_lastTime = currentTime;

	jl::Globals::s_timeTotal += durationFloat.count();
	m_cameraController.update(durationFloat.count());

	m_viewPropertiesWdg->update();
	m_ui->oglw_screen->repaint();
}

//-----------------------------------------------------------------------------

void MainWindow::onGlLoaded()
{
	std::ifstream file(k_saveFile.data());
	if (file.is_open())
	{
		JsonProjectRestorer restorer(file);
		m_sceneWrapper = restorer.extractScene();
	}
	else
	{
		m_sceneWrapper = std::make_unique<SceneWrapper>();
	}

	AppController::setContextOwner(m_ui->oglw_screen);
	m_ui->oglw_screen->setScene(m_sceneWrapper.get());
	m_ui->oglw_screen->setCamera(&m_camera);

	m_entitisWdg->setScene(m_sceneWrapper.get());
}

//-----------------------------------------------------------------------------

void MainWindow::setupUi()
{
	m_ui = std::make_unique<Ui::MainWindow>();
	m_ui->setupUi(this);

	m_ui->oglw_screen->setActionHandler(this);

	m_entitisWdg = new EntitiesWidget(m_ui->dock_entities);
	m_entitisWdg->setEntityActionHandler(this);
	m_ui->dock_entities->setWidget(m_entitisWdg);

	m_propertiesWdg = new PropertiesWidget(m_ui->dock_props);
	m_ui->dock_props->setWidget(m_propertiesWdg);

	m_viewPropertiesWdg = new ViewPropertiesWidget(m_ui->dock_viewProps);
	m_viewPropertiesWdg->setGlWidget(m_ui->oglw_screen);
	m_viewPropertiesWdg->setCameraController(&m_cameraController);
	m_ui->dock_viewProps->setWidget(m_viewPropertiesWdg);
}

//-----------------------------------------------------------------------------

void MainWindow::setupDefaultMaterial()
{
	jl::Material& material = MaterialsManager::getInstance().createMaterial("Default");

	const jl::Shader* shader = ResourceManager::getInstance().loadShader("res/shaders/MaterialColorShader.shdata");
	material.setShader(shader);

	material.setProperty("u_shininess",		128.0f);
	material.setProperty("u_opacity",		1.0f);
	material.setProperty("u_matAmbient",	glm::vec3(1.0f));
	material.setProperty("u_matDiffuse",	glm::vec3(1.0f));
	material.setProperty("u_matSpecular",	glm::vec3(1.0f));
	material.setProperty("u_texDiffuse",	static_cast<jl::Texture*>(nullptr));
	material.setProperty("u_texNormals",	static_cast<jl::Texture*>(nullptr));
}

//-----------------------------------------------------------------------------
