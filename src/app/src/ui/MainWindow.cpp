#include "ui/MainWindow.hpp"
#include "ui/EntitiesWidget.hpp"
#include "ui/PropertiesWidget.hpp"
#include "ui/ViewPropertiesWidget.hpp"
#include "ui/UiUtils.hpp"
#include "ui_MainWindow.h"

#include "data/SceneWrapper.hpp"
#include "data/ObjectWrapper.hpp"

#include "julie/managers/AppController.hpp"
#include "julie/managers/ResourceManager.hpp"
#include "julie/managers/MaterialsManager.hpp"

#include "save_restore/JsonProjectSaver.hpp"
#include "save_restore/JsonProjectRestorer.hpp"

#include "julie/Globals.hpp"
#include "julie/Model.hpp"
#include "julie/Shader.hpp"
#include "julie/Material.hpp"
#include "julie/scene/Scene.hpp"
#include "julie/scene/Object.hpp"

#include "utils/Utils.hpp"

#include <QKeyEvent>

#include <fstream>

//-----------------------------------------------------------------------------

std::unique_ptr<jl::Model> createRoomModel()
{
	constexpr size_t k_verticeCount = 30;

	std::vector<jl::Vertex> vertices(k_verticeCount);

	{
		size_t i = 0;
		vertices[i].pos = glm::vec3(0.0f, 0.0f, 0.0f); vertices[i].norm = glm::vec3(0.0f, 0.0f, 1.0f); vertices[i++].uv = glm::vec2(0.0f, 0.0f);
		vertices[i].pos = glm::vec3(1.0f, 0.0f, 0.0f); vertices[i].norm = glm::vec3(0.0f, 0.0f, 1.0f); vertices[i++].uv = glm::vec2(1.0f, 0.0f);
		vertices[i].pos = glm::vec3(1.0f, 1.0f, 0.0f); vertices[i].norm = glm::vec3(0.0f, 0.0f, 1.0f); vertices[i++].uv = glm::vec2(1.0f, 1.0f);
		vertices[i].pos = glm::vec3(1.0f, 1.0f, 0.0f); vertices[i].norm = glm::vec3(0.0f, 0.0f, 1.0f); vertices[i++].uv = glm::vec2(1.0f, 1.0f);
		vertices[i].pos = glm::vec3(0.0f, 1.0f, 0.0f); vertices[i].norm = glm::vec3(0.0f, 0.0f, 1.0f); vertices[i++].uv = glm::vec2(0.0f, 1.0f);
		vertices[i].pos = glm::vec3(0.0f, 0.0f, 0.0f); vertices[i].norm = glm::vec3(0.0f, 0.0f, 1.0f); vertices[i++].uv = glm::vec2(0.0f, 0.0f);

		vertices[i].pos = glm::vec3(0.0f, 0.0f, 1.0f); vertices[i].norm = glm::vec3(0.0f, 0.0f, -1.0f); vertices[i++].uv = glm::vec2(0.0f, 0.0f);
		vertices[i].pos = glm::vec3(1.0f, 0.0f, 1.0f); vertices[i].norm = glm::vec3(0.0f, 0.0f, -1.0f); vertices[i++].uv = glm::vec2(1.0f, 0.0f);
		vertices[i].pos = glm::vec3(1.0f, 1.0f, 1.0f); vertices[i].norm = glm::vec3(0.0f, 0.0f, -1.0f); vertices[i++].uv = glm::vec2(1.0f, 1.0f);
		vertices[i].pos = glm::vec3(1.0f, 1.0f, 1.0f); vertices[i].norm = glm::vec3(0.0f, 0.0f, -1.0f); vertices[i++].uv = glm::vec2(1.0f, 1.0f);
		vertices[i].pos = glm::vec3(0.0f, 1.0f, 1.0f); vertices[i].norm = glm::vec3(0.0f, 0.0f, -1.0f); vertices[i++].uv = glm::vec2(0.0f, 1.0f);
		vertices[i].pos = glm::vec3(0.0f, 0.0f, 1.0f); vertices[i].norm = glm::vec3(0.0f, 0.0f, -1.0f); vertices[i++].uv = glm::vec2(0.0f, 0.0f);

		vertices[i].pos = glm::vec3(0.0f, 1.0f, 1.0f); vertices[i].norm = glm::vec3(1.0f, 0.0f, 0.0f); vertices[i++].uv = glm::vec2(0.0f, 0.0f);
		vertices[i].pos = glm::vec3(0.0f, 1.0f, 0.0f); vertices[i].norm = glm::vec3(1.0f, 0.0f, 0.0f); vertices[i++].uv = glm::vec2(1.0f, 0.0f);
		vertices[i].pos = glm::vec3(0.0f, 0.0f, 0.0f); vertices[i].norm = glm::vec3(1.0f, 0.0f, 0.0f); vertices[i++].uv = glm::vec2(1.0f, 1.0f);
		vertices[i].pos = glm::vec3(0.0f, 0.0f, 0.0f); vertices[i].norm = glm::vec3(1.0f, 0.0f, 0.0f); vertices[i++].uv = glm::vec2(1.0f, 1.0f);
		vertices[i].pos = glm::vec3(0.0f, 0.0f, 1.0f); vertices[i].norm = glm::vec3(1.0f, 0.0f, 0.0f); vertices[i++].uv = glm::vec2(0.0f, 1.0f);
		vertices[i].pos = glm::vec3(0.0f, 1.0f, 1.0f); vertices[i].norm = glm::vec3(1.0f, 0.0f, 0.0f); vertices[i++].uv = glm::vec2(0.0f, 0.0f);

		vertices[i].pos = glm::vec3(1.0f, 1.0f, 1.0f); vertices[i].norm = glm::vec3(-1.0f, 0.0f, 0.0f); vertices[i++].uv = glm::vec2(0.0f, 0.0f);
		vertices[i].pos = glm::vec3(1.0f, 1.0f, 0.0f); vertices[i].norm = glm::vec3(-1.0f, 0.0f, 0.0f); vertices[i++].uv = glm::vec2(1.0f, 0.0f);
		vertices[i].pos = glm::vec3(1.0f, 0.0f, 0.0f); vertices[i].norm = glm::vec3(-1.0f, 0.0f, 0.0f); vertices[i++].uv = glm::vec2(1.0f, 1.0f);
		vertices[i].pos = glm::vec3(1.0f, 0.0f, 0.0f); vertices[i].norm = glm::vec3(-1.0f, 0.0f, 0.0f); vertices[i++].uv = glm::vec2(1.0f, 1.0f);
		vertices[i].pos = glm::vec3(1.0f, 0.0f, 1.0f); vertices[i].norm = glm::vec3(-1.0f, 0.0f, 0.0f); vertices[i++].uv = glm::vec2(0.0f, 1.0f);
		vertices[i].pos = glm::vec3(1.0f, 1.0f, 1.0f); vertices[i].norm = glm::vec3(-1.0f, 0.0f, 0.0f); vertices[i++].uv = glm::vec2(0.0f, 0.0f);

		vertices[i].pos = glm::vec3(0.0f, 0.0f, 0.0f); vertices[i].norm = glm::vec3(0.0f, 1.0f, 0.0f); vertices[i++].uv = glm::vec2(0.0f, 1.0f);
		vertices[i].pos = glm::vec3(1.0f, 0.0f, 0.0f); vertices[i].norm = glm::vec3(0.0f, 1.0f, 0.0f); vertices[i++].uv = glm::vec2(1.0f, 1.0f);
		vertices[i].pos = glm::vec3(1.0f, 0.0f, 1.0f); vertices[i].norm = glm::vec3(0.0f, 1.0f, 0.0f); vertices[i++].uv = glm::vec2(1.0f, 0.0f);
		vertices[i].pos = glm::vec3(1.0f, 0.0f, 1.0f); vertices[i].norm = glm::vec3(0.0f, 1.0f, 0.0f); vertices[i++].uv = glm::vec2(1.0f, 0.0f);
		vertices[i].pos = glm::vec3(0.0f, 0.0f, 1.0f); vertices[i].norm = glm::vec3(0.0f, 1.0f, 0.0f); vertices[i++].uv = glm::vec2(0.0f, 0.0f);
		vertices[i].pos = glm::vec3(0.0f, 0.0f, 0.0f); vertices[i].norm = glm::vec3(0.0f, 1.0f, 0.0f); vertices[i++].uv = glm::vec2(0.0f, 1.0f);

		//vertices[i].pos = glm::vec3(0.0f, 1.0f, 0.0f); vertices[i++].norm = glm::vec3(0.0f, -1.0f, 0.0f);
		//vertices[i].pos = glm::vec3(1.0f, 1.0f, 0.0f); vertices[i++].norm = glm::vec3(0.0f, -1.0f, 0.0f);
		//vertices[i].pos = glm::vec3(1.0f, 1.0f, 1.0f); vertices[i++].norm = glm::vec3(0.0f, -1.0f, 0.0f);
		//vertices[i].pos = glm::vec3(1.0f, 1.0f, 1.0f); vertices[i++].norm = glm::vec3(0.0f, -1.0f, 0.0f);
		//vertices[i].pos = glm::vec3(0.0f, 1.0f, 1.0f); vertices[i++].norm = glm::vec3(0.0f, -1.0f, 0.0f);
		//vertices[i].pos = glm::vec3(0.0f, 1.0f, 0.0f); vertices[i++].norm = glm::vec3(0.0f, -1.0f, 0.0f);

		ASSERT(i == k_verticeCount);
	}

	std::vector<jl::index_t> indices(k_verticeCount);
	for (jl::index_t j = 0; j < k_verticeCount; ++j)
	{
		indices[j] = j;
	}

	return std::make_unique<jl::Model>(vertices, indices);
}

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
	const float dt = getDeltaTime();
	jl::Globals::s_timeTotal += dt;

	m_viewPropertiesWdg->update(dt);

	m_ui->oglw_screen->repaint();
}

//-----------------------------------------------------------------------------

float MainWindow::getDeltaTime()
{
	static TimePoint s_lastTime = Clock::now();
	const TimePoint currentTime = Clock::now();

	auto durationFloat = std::chrono::duration_cast<std::chrono::duration<float>>(currentTime - s_lastTime);
	s_lastTime = currentTime;

	return durationFloat.count();
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

	setupRoom();

	AppController::setContextOwner(m_ui->oglw_screen);
	m_ui->oglw_screen->setScene(m_sceneWrapper.get());
	m_ui->oglw_screen->setCamera(&m_camera);

	m_entitisWdg->setScene(m_sceneWrapper.get());
}

//-----------------------------------------------------------------------------

void MainWindow::setupRoom()
{
	if (!m_roomModel)
	{
		m_roomModel = createRoomModel();

		jl::Mesh& roomMesh = m_roomModel->getMesh(0);
		roomMesh.setMaterial(&MaterialsManager::getInstance().getDefaultMaterial());
	}

	const std::string k_roomObjName = "Room";

	ObjectWrapper* roomWrapper = m_sceneWrapper->findObject(k_roomObjName);
	if (!roomWrapper)
	{
		roomWrapper = &m_sceneWrapper->createObject(k_roomObjName);
	}

	const glm::vec3 originalSize = roomWrapper->getSize();
	roomWrapper->setModel(m_roomModel.get());
	roomWrapper->setSize(originalSize);
}

//-----------------------------------------------------------------------------
