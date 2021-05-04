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
{
	m_cameraController.setCameraMoveSpeed(3.0f);
	m_cameraController.setCameraRotateSpeed(2.0f);
	m_cameraController.setCamera(m_core.getCamera());

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

	m_core.update(duration_cast<DeltaTime>(delta));
	m_viewPropertiesWdg->update();
	m_ui->oglw_screen->repaint();
}

//-----------------------------------------------------------------------------

void MainWindow::onGlLoaded()
{
	AppController::setContextOwner(m_ui->oglw_screen);
	m_ui->oglw_screen->setGameCore(&m_core);
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
