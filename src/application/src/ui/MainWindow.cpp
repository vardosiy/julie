#include "ui/MainWindow.hpp"
#include "ui/EntitiesWidget.hpp"
#include "ui/PropertiesWidget.hpp"
#include "ui/UiUtils.hpp"
#include "ui_MainWindow.h"

#include "data/SceneWrapper.hpp"
#include "data/ObjectWrapper.hpp"

#include "renderer/managers/AppController.hpp"
#include "renderer/managers/ResourceManager.hpp"
#include "renderer/managers/MaterialsManager.hpp"

#include "save_restore/JsonProjectSaver.hpp"
#include "save_restore/JsonProjectRestorer.hpp"

#include "renderer/Globals.hpp"
#include "renderer/Model.hpp"
#include "renderer/Shader.hpp"
#include "renderer/Material.hpp"
#include "renderer/scene/Scene.hpp"
#include "renderer/scene/Object.hpp"

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
		vertices[i].pos = glm::vec3(0.0f, 0.0f, 0.0f); vertices[i++].norm = glm::vec3(0.0f, 0.0f, 1.0f);
		vertices[i].pos = glm::vec3(1.0f, 0.0f, 0.0f); vertices[i++].norm = glm::vec3(0.0f, 0.0f, 1.0f);
		vertices[i].pos = glm::vec3(1.0f, 1.0f, 0.0f); vertices[i++].norm = glm::vec3(0.0f, 0.0f, 1.0f);
		vertices[i].pos = glm::vec3(1.0f, 1.0f, 0.0f); vertices[i++].norm = glm::vec3(0.0f, 0.0f, 1.0f);
		vertices[i].pos = glm::vec3(0.0f, 1.0f, 0.0f); vertices[i++].norm = glm::vec3(0.0f, 0.0f, 1.0f);
		vertices[i].pos = glm::vec3(0.0f, 0.0f, 0.0f); vertices[i++].norm = glm::vec3(0.0f, 0.0f, 1.0f);

		vertices[i].pos = glm::vec3(0.0f, 0.0f, 1.0f); vertices[i++].norm = glm::vec3(0.0f, 0.0f, -1.0f);
		vertices[i].pos = glm::vec3(1.0f, 0.0f, 1.0f); vertices[i++].norm = glm::vec3(0.0f, 0.0f, -1.0f);
		vertices[i].pos = glm::vec3(1.0f, 1.0f, 1.0f); vertices[i++].norm = glm::vec3(0.0f, 0.0f, -1.0f);
		vertices[i].pos = glm::vec3(1.0f, 1.0f, 1.0f); vertices[i++].norm = glm::vec3(0.0f, 0.0f, -1.0f);
		vertices[i].pos = glm::vec3(0.0f, 1.0f, 1.0f); vertices[i++].norm = glm::vec3(0.0f, 0.0f, -1.0f);
		vertices[i].pos = glm::vec3(0.0f, 0.0f, 1.0f); vertices[i++].norm = glm::vec3(0.0f, 0.0f, -1.0f);

		vertices[i].pos = glm::vec3(0.0f, 1.0f, 1.0f); vertices[i++].norm = glm::vec3(1.0f, 0.0f, 0.0f);
		vertices[i].pos = glm::vec3(0.0f, 1.0f, 0.0f); vertices[i++].norm = glm::vec3(1.0f, 0.0f, 0.0f);
		vertices[i].pos = glm::vec3(0.0f, 0.0f, 0.0f); vertices[i++].norm = glm::vec3(1.0f, 0.0f, 0.0f);
		vertices[i].pos = glm::vec3(0.0f, 0.0f, 0.0f); vertices[i++].norm = glm::vec3(1.0f, 0.0f, 0.0f);
		vertices[i].pos = glm::vec3(0.0f, 0.0f, 1.0f); vertices[i++].norm = glm::vec3(1.0f, 0.0f, 0.0f);
		vertices[i].pos = glm::vec3(0.0f, 1.0f, 1.0f); vertices[i++].norm = glm::vec3(1.0f, 0.0f, 0.0f);

		vertices[i].pos = glm::vec3(1.0f, 1.0f, 1.0f); vertices[i++].norm = glm::vec3(-1.0f, 0.0f, 0.0f);
		vertices[i].pos = glm::vec3(1.0f, 1.0f, 0.0f); vertices[i++].norm = glm::vec3(-1.0f, 0.0f, 0.0f);
		vertices[i].pos = glm::vec3(1.0f, 0.0f, 0.0f); vertices[i++].norm = glm::vec3(-1.0f, 0.0f, 0.0f);
		vertices[i].pos = glm::vec3(1.0f, 0.0f, 0.0f); vertices[i++].norm = glm::vec3(-1.0f, 0.0f, 0.0f);
		vertices[i].pos = glm::vec3(1.0f, 0.0f, 1.0f); vertices[i++].norm = glm::vec3(-1.0f, 0.0f, 0.0f);
		vertices[i].pos = glm::vec3(1.0f, 1.0f, 1.0f); vertices[i++].norm = glm::vec3(-1.0f, 0.0f, 0.0f);

		vertices[i].pos = glm::vec3(0.0f, 0.0f, 0.0f); vertices[i++].norm = glm::vec3(0.0f, 1.0f, 0.0f);
		vertices[i].pos = glm::vec3(1.0f, 0.0f, 0.0f); vertices[i++].norm = glm::vec3(0.0f, 1.0f, 0.0f);
		vertices[i].pos = glm::vec3(1.0f, 0.0f, 1.0f); vertices[i++].norm = glm::vec3(0.0f, 1.0f, 0.0f);
		vertices[i].pos = glm::vec3(1.0f, 0.0f, 1.0f); vertices[i++].norm = glm::vec3(0.0f, 1.0f, 0.0f);
		vertices[i].pos = glm::vec3(0.0f, 0.0f, 1.0f); vertices[i++].norm = glm::vec3(0.0f, 1.0f, 0.0f);
		vertices[i].pos = glm::vec3(0.0f, 0.0f, 0.0f); vertices[i++].norm = glm::vec3(0.0f, 1.0f, 0.0f);

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

std::unique_ptr<jl::Model> createPlatformModel()
{
	std::vector<jl::Vertex> vertices(4);

	vertices[0].pos  = glm::vec3(0.0f, 0.0f, 0.0f);
	vertices[1].pos  = glm::vec3(0.0f, 0.0f, 1.0f);
	vertices[2].pos  = glm::vec3(1.0f, 0.0f, 0.0f);
	vertices[3].pos  = glm::vec3(1.0f, 0.0f, 1.0f);

	vertices[0].norm = glm::vec3(0.0f, 1.0f, 0.0f);
	vertices[1].norm = glm::vec3(0.0f, 1.0f, 0.0f);
	vertices[2].norm = glm::vec3(0.0f, 1.0f, 0.0f);
	vertices[3].norm = glm::vec3(0.0f, 1.0f, 0.0f);

	std::vector<jl::index_t> indices{ 0, 1, 2, 1, 2, 3 };

	return std::make_unique<jl::Model>(vertices, indices);
}

//-----------------------------------------------------------------------------

MainWindow::MainWindow(QMainWindow* parent)
	: QMainWindow(parent)
	, m_entitisWdg(nullptr)
	, m_propertiesWdg(nullptr)
	, m_updateTimer(this)
	, m_camera(0.001f, 100.0f, 45.0f)
{
	setupUi();

	connect(&m_updateTimer,				&QTimer::timeout,			this, &MainWindow::update);
	connect(m_ui->chb_fillPolygons,		&QCheckBox::stateChanged,	this, &MainWindow::onFillPolygonsValueChanged);
	connect(m_ui->sld_camMoveSpeed,		&QSlider::valueChanged,		[this](int _value) { m_cameraController.setCameraMoveSpeed(_value); });
	connect(m_ui->sld_camRotateSpeed,	&QSlider::valueChanged,		[this](int _value) { m_cameraController.setCameraRotateSpeed(_value); });
	connect(m_ui->chb_showBb,			&QCheckBox::stateChanged,	[this](int _value) { m_ui->oglw_screen->drawBoundingBoxes(_value == Qt::CheckState::Checked); });

	m_updateTimer.start(1);
	m_cameraController.setCamera(&m_camera);

	m_camera.setPosition(glm::vec3(1.0f, 2.0f, 5.0f));

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

	m_sceneWrapper->update(dt);
	m_cameraController.update(dt);

	m_ui->lbl_camPosValue->setText(vecToString(m_camera.getPosition()));
	m_ui->lbl_camViewDirectionValue->setText(vecToString(m_camera.getViewTarget()));

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

void MainWindow::onFillPolygonsValueChanged(int _state)
{
	AppGlWidget::DrawMode drawMode = AppGlWidget::DrawMode::Fill;

	switch (_state)
	{
	case Qt::CheckState::Checked:
		drawMode = AppGlWidget::DrawMode::Fill;
		break;

	case Qt::CheckState::Unchecked:
		drawMode = AppGlWidget::DrawMode::Edges;
		break;

	default:
		ASSERT(0);
	}

	m_ui->oglw_screen->setDrawMode(drawMode);
}

//-----------------------------------------------------------------------------

void MainWindow::onGlLoaded()
{
	std::ifstream file(k_saveFile.data());
	JsonProjectRestorer restorer(file);
	m_sceneWrapper = restorer.extractScene();

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
		auto obj = std::make_unique<jl::Object>(k_roomObjName);
		roomWrapper = &m_sceneWrapper->addObject(std::move(obj));
	}

	const glm::vec3 originalSize = roomWrapper->getSize();
	roomWrapper->setModel(m_roomModel.get());
	roomWrapper->setSize(originalSize);
	roomWrapper->setTransformFlags(jl::Object::TransfromFlags::Scaleable);

	m_ui->oglw_screen->setUninteractibleObjects({ k_roomObjName });
}

//-----------------------------------------------------------------------------
