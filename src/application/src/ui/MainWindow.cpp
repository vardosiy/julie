#include "ui/MainWindow.hpp"
#include "ui/EntitiesWidget.hpp"
#include "ui/PropertiesWidget.hpp"

#include "ui_MainWindow.h"

#include "ObjectWrapper.hpp"

#include "controllers/AppController.hpp"

#include "managers/ResourceManager.hpp"
#include "managers/MaterialsManager.hpp"

#include "save_restore/JsonSceneSaver.hpp"
#include "save_restore/JsonSceneRestorer.hpp"

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

	std::vector<jl::u16> indices(k_verticeCount);
	for (jl::u16 j = 0; j < k_verticeCount; ++j)
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

	std::vector<jl::u16> indices{ 0, 1, 2, 1, 2, 3 };

	return std::make_unique<jl::Model>(vertices, indices);
}

//-----------------------------------------------------------------------------

MainWindow::MainWindow(QMainWindow* parent)
	: QMainWindow(parent)
	, m_entitisWdg(nullptr)
	, m_propertiesWdg(nullptr)
	, m_updateTimer(this)
	, m_objectsListModel(this)
	, m_materialsListModel(this)
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

	m_camera.setPosition(glm::vec3(0.0f, 1.0f, 5.0f));

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
	//JsonSceneSaver::save(file, *m_scene);
}

//-----------------------------------------------------------------------------

void MainWindow::addObject()
{
	const std::string name = computeObjectName();
	auto object = std::make_unique<jl::Object>(name);

	m_objectsNamesList.append(name.c_str());
	m_objectsListModel.setStringList(m_objectsNamesList);

	m_objWrappers.emplace_back(*object);
	m_scene->addObject(std::move(object));
}

//-----------------------------------------------------------------------------

void MainWindow::deleteObject(const QString& _name)
{
	const std::string objName = _name.toStdString();
	auto itWrappers = std::find_if(m_objWrappers.begin(), m_objWrappers.end(), [&objName](const ObjectWrapper& _objWrapper)
	{
		return objName == _objWrapper.getInternalObject().getName();
	});
	m_objWrappers.erase(itWrappers);
	m_scene->removeObject(objName);

	auto itNames = std::find(m_objectsNamesList.begin(), m_objectsNamesList.end(), _name);
	if (itNames != m_objectsNamesList.end())
	{
		m_objectsNamesList.erase(itNames);
		m_objectsListModel.setStringList(m_objectsNamesList);
	}
}

//-----------------------------------------------------------------------------

void MainWindow::objectSelected(const QString& _name)
{
	const std::string objName = _name.toStdString();
	auto it = std::find_if(m_objWrappers.begin(), m_objWrappers.end(), [&objName](const ObjectWrapper& _objWrapper)
	{
		return objName == _objWrapper.getInternalObject().getName();
	});

	if (it != m_objWrappers.end())
	{
		m_propertiesWdg->setActiveEntity(*it);
	}
}

//-----------------------------------------------------------------------------

void MainWindow::addMaterial()
{
	const std::string name = computeMaterialName();
	jl::Material& material = MaterialsManager::getInstance().createMaterial(name);

	m_materialsNamesList.append(name.c_str());
	m_materialsListModel.setStringList(m_materialsNamesList);
}

//-----------------------------------------------------------------------------

void MainWindow::deleteMaterial(const QString& _name)
{
	//MaterialsManager::getInstance().deleteMaterial(_name.toStdString());
}

//-----------------------------------------------------------------------------

void MainWindow::materialSelected(const QString& _name)
{
	if (jl::Material* material = MaterialsManager::getInstance().findMaterial(_name.toStdString()))
	{
		m_propertiesWdg->setActiveEntity(*material);
	}
}

//-----------------------------------------------------------------------------

void MainWindow::resetSelection()
{
	m_propertiesWdg->reset();
}

//-----------------------------------------------------------------------------

void MainWindow::onObjectMoved(jl::Object& _object)
{
	m_propertiesWdg->refreshObjectPos();
}

//-----------------------------------------------------------------------------

void MainWindow::onObjectScaled(jl::Object& _object)
{
	m_propertiesWdg->refreshObjectScale();
}

//-----------------------------------------------------------------------------

void MainWindow::update()
{
	const float dt = getDeltaTime();
	jl::Globals::s_timeTotal += dt;

	m_scene->update(dt);
	m_cameraController.update(dt);

	const glm::vec3& camPos = m_camera.getPosition();
	const std::string camPosStr = fmt::format("{:.2f} {:.2f} {:.2f}", camPos.x, camPos.y, camPos.z);
	m_ui->lbl_camPosValue->setText(QString::fromStdString(camPosStr));

	const glm::vec3& camViewTarget = m_camera.getViewTarget();
	const std::string camViewTargetStr = fmt::format("{:.2f} {:.2f} {:.2f}", camViewTarget.x, camViewTarget.y, camViewTarget.z);
	m_ui->lbl_camViewDirectionValue->setText(QString::fromStdString(camViewTargetStr));

	m_ui->oglw_screen->repaint();
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
	m_scene = JsonSceneRestorer::restore(file);

	setupRoom();

	AppController::setGlWidget(m_ui->oglw_screen);
	m_ui->oglw_screen->setScene(m_scene.get());
	m_ui->oglw_screen->setCamera(&m_camera);

	m_scene->forEachObject([this](jl::Object& _object)
	{
		m_objWrappers.emplace_back(_object);
		m_objectsNamesList.append(_object.getName().c_str());
	});
	m_objectsListModel.setStringList(m_objectsNamesList);

	MaterialsManager::getInstance().forEachMaterial([this](const std::string& _name, const jl::Material&)
	{
		m_materialsNamesList.append(_name.c_str());
	});
	m_materialsListModel.setStringList(m_materialsNamesList);
}

//-----------------------------------------------------------------------------

void MainWindow::setupUi()
{
	m_ui = std::make_unique<Ui::MainWindow>();
	m_ui->setupUi(this);

	m_ui->oglw_screen->setActionHandler(this);

	m_entitisWdg = new EntitiesWidget(m_ui->dock_entities);
	m_entitisWdg->setObjectsListModel(m_objectsListModel);
	m_entitisWdg->setMaterialsListModel(m_materialsListModel);
	m_entitisWdg->setEntityActionHandler(*this);
	m_ui->dock_entities->setWidget(m_entitisWdg);

	m_propertiesWdg = new PropertiesWidget(m_ui->dock_props);
	m_ui->dock_props->setWidget(m_propertiesWdg);
}

//-----------------------------------------------------------------------------

void MainWindow::setupRoom()
{
	const std::string k_roomObjName = "Room";

	jl::Object* room = m_scene->findObject(k_roomObjName);
	if (!room)
	{
		auto obj = std::make_unique<jl::Object>(k_roomObjName);
		room = obj.get();

		m_scene->addObject(std::move(obj));
	}
	if (!m_roomModel)
	{
		m_roomModel = createRoomModel();
	}

	room->setModel(*m_roomModel);
	room->setMaterial(MaterialsManager::getInstance().getDefaultMaterial());
	room->setTransformFlags(jl::Object::TransfromFlags::Scaleable);

	m_ui->oglw_screen->setUninteractibleObjects({ room });
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

std::string MainWindow::computeObjectName() const
{
	return computeEntityName(k_defaultObjectName, [this](const std::string& _name)
	{
		return m_scene->findObject(_name) != nullptr;
	});
}

//-----------------------------------------------------------------------------

std::string MainWindow::computeMaterialName() const
{
	return computeEntityName(k_defaultMaterialName, [](const std::string& _name)
	{
		return MaterialsManager::getInstance().findMaterial(_name) != nullptr;
	});
}

//-----------------------------------------------------------------------------

std::string MainWindow::computeEntityName(
	std::string_view _base,
	std::function<bool(const std::string&)>&& _entityExistCheckFun
)
{
	std::string result = _base.data();
	int counter = 0;

	while (_entityExistCheckFun(result))
	{
		fmt::memory_buffer buf;
		format_to(buf, "{:03d}", ++counter);

		const size_t offset = result.length() - 3;
		result.replace(offset, 3, buf.data(), 3); // last param need due to MSVC bug
	}

	return result;
}

//-----------------------------------------------------------------------------
