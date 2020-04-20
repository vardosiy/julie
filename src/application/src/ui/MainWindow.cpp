#include "ui/MainWindow.hpp"
#include "ui/EntitiesWidget.hpp"
#include "ui/PropertiesWidget.hpp"

#include "ui_MainWindow.h"

#include "managers/ResourceManager.hpp"
#include "managers/MaterialsManager.hpp"

#include "save_restore/JsonSceneSaver.hpp"
#include "save_restore/JsonSceneRestorer.hpp"

#include "renderer/Material.hpp"
#include "renderer/scene/Scene.hpp"
#include "renderer/scene/Object.hpp"

#include "utils/Utils.hpp"

#include <QKeyEvent>

#include <fstream>

//-----------------------------------------------------------------------------

MainWindow::MainWindow(QMainWindow* parent)
	: QMainWindow(parent)
	, m_objectsListModel(this)
	, m_entitisWdg(nullptr)
{
	setupUi();

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
	JsonSceneSaver::save(file, *m_scene);
}

//-----------------------------------------------------------------------------

void MainWindow::addObject()
{
	auto object = std::make_unique<jl::Object>(computeObjectName());

	m_objectsNamesList.append(object->getName().c_str());
	m_objectsListModel.setStringList(m_objectsNamesList);

	m_scene->addObject(std::move(object));
}

//-----------------------------------------------------------------------------

void MainWindow::deleteObject(const QString& _name)
{
	m_scene->removeObject(_name.toStdString());

	auto it = std::find(m_objectsNamesList.begin(), m_objectsNamesList.end(), _name);
	if (it != m_objectsNamesList.end())
	{
		m_objectsNamesList.erase(it);
		m_objectsListModel.setStringList(m_objectsNamesList);
	}
}

//-----------------------------------------------------------------------------

void MainWindow::objectSelected(const QString& _name)
{
	if (jl::Object* object = m_scene->findObject(_name.toStdString()))
	{
		m_propertiesWdg->setActiveEntity(*object);
	}
}

//-----------------------------------------------------------------------------

void MainWindow::addMaterial()
{
	const std::string materialName = computeMaterialName();
	jl::Material& material = MaterialsManager::getInstance().getMaterial(materialName);

	m_materialsNamesList.append(materialName.c_str());
	m_materialsListModel.setStringList(m_materialsNamesList);
}

//-----------------------------------------------------------------------------

void MainWindow::deleteMaterial(const QString& _name)
{
}

//-----------------------------------------------------------------------------

void MainWindow::materialSelected(const QString& _name)
{
}

//-----------------------------------------------------------------------------

void MainWindow::resetSelection()
{
	m_propertiesWdg->reset();
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

void MainWindow::setupUi()
{
	m_ui = std::make_unique<Ui::MainWindow>();
	m_ui->setupUi(this);

	m_entitisWdg = new EntitiesWidget(m_ui->dock_entities);
	m_entitisWdg->setObjectsListModel(m_objectsListModel);
	m_entitisWdg->setMaterialsListModel(m_materialsListModel);
	m_entitisWdg->setEntityActionHandler(*this);
	m_ui->dock_entities->setWidget(m_entitisWdg);

	m_propertiesWdg = new PropertiesWidget(m_ui->dock_props);
	m_ui->dock_props->setWidget(m_propertiesWdg);

	connect(m_ui->chb_fillPolygons,		&QCheckBox::stateChanged,	this,				&MainWindow::onFillPolygonsValueChanged);
	connect(m_ui->sld_camMoveSpeed,		&QSlider::valueChanged,		m_ui->oglw_screen,	&AppGlWidget::setCameraMoveSpeed);
	connect(m_ui->sld_camRotateSpeed,	&QSlider::valueChanged,		m_ui->oglw_screen,	&AppGlWidget::setCameraRotateSpeed);
}

//-----------------------------------------------------------------------------

void MainWindow::onGlLoaded()
{
	std::ifstream file(k_saveFile.data());
	m_scene = JsonSceneRestorer::restore(file);

	m_ui->oglw_screen->setScene(m_scene.get());

	m_scene->forEachObject([this](const jl::Object& _object)
	{
		m_objectsNamesList.append(_object.getName().c_str());
	});
	m_objectsListModel.setStringList(m_objectsNamesList);
}

//-----------------------------------------------------------------------------

std::string MainWindow::computeObjectName() const
{
	return computeEntityName(k_defaultObjectName, [this](const std::string& _name)
	{
		return m_scene->findObject(_name);
	});
}

//-----------------------------------------------------------------------------

std::string MainWindow::computeMaterialName() const
{
	return computeEntityName(k_defaultMaterialName, [](const std::string& _name)
	{
		return MaterialsManager::getInstance().hasMaterial(_name);
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
		format_to(buf, "{:03d}\n", ++counter);

		const size_t offset = result.length() - 3;
		result.replace(offset, 3, buf.data(), 3); // last param need due to MSVC bug
	}

	return result;
}

//-----------------------------------------------------------------------------
