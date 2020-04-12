#include "ui/MainWindow.hpp"
#include "ui_MainWindow.h"

#include "managers/ResourceManager.hpp"
#include "managers/MaterialsManager.hpp"

#include "save_restore/JsonSceneSaver.hpp"
#include "save_restore/JsonSceneRestorer.hpp"

#include "renderer/scene/Scene.hpp"
#include "renderer/scene/Object.hpp"

#include "renderer/Model.hpp"
#include "renderer/Shader.hpp"
#include "renderer/Material.hpp"

#include "utils/Utils.hpp"

#include <QKeyEvent>
#include <fstream>

//-----------------------------------------------------------------------------

static std::unique_ptr<jl::Model> createRoom()
{
	std::vector<jl::Vertex> vertices(8);
	vertices[0].pos = glm::vec3(-1.0f, 1.0f, -1.0f); // back rect
	vertices[1].pos = glm::vec3(-1.0f, 0.0f, -1.0f);
	vertices[2].pos = glm::vec3(1.0f, 1.0f, -1.0f);
	vertices[3].pos = glm::vec3(1.0f, 0.0f, -1.0f);

	vertices[4].pos = glm::vec3(-1.0f, 1.0f, 1.0f); // front rect
	vertices[5].pos = glm::vec3(-1.0f, 0.0f, 1.0f);
	vertices[6].pos = glm::vec3(1.0f, 1.0f, 1.0f);
	vertices[7].pos = glm::vec3(1.0f, 0.0f, 1.0f);

	std::vector<jl::u16> indices = {
		0, 1, 2, // back
		1, 2, 3,
		4, 5, 6, // front
		5, 6, 7,
		0, 1, 4, // left
		1, 4, 5,
		2, 3, 6, // right
		3, 6, 7,
		1, 3, 5, // bottom
		3, 5, 7,
	};

	return std::make_unique<jl::Model>(vertices, indices);
}

//-----------------------------------------------------------------------------

MainWindow::MainWindow(QMainWindow* parent)
	: QMainWindow(parent)
	, m_ui(std::make_unique<Ui::MainWindow>())
	, m_objectsListModel(this)
	, m_propertiesTableModel(5, 2, this)
{
	setupUi();
	setupConnections();

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

void MainWindow::onGlLoaded()
{
	std::ifstream file(k_saveFile.data());
	m_scene = JsonSceneRestorer::restore(file);

	m_ui->oglw_screen->setScene(m_scene.get());

	m_scene->forEachObject([this](const jl::Object& _object)
	{
		addObjectToGuiList(_object);
	});
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

void MainWindow::onAddEntityBtnReleased()
{
	if (m_ui->tab_objects->isVisible())
	{
		//auto object = std::make_unique<data::Object>("name");
		//object->setModel(*ResourceManager::getInstance().loadModel("res/models/Bila.nfg"));
		//object->setMaterial(*g_material);

		//addObjectToGuiList(*object);
		//m_ui->oglw_screen->onObjectAdded(*object);

		//m_project.addEntity(std::move(object));
	}
	else if (m_ui->tab_materials->isVisible())
	{

	}
	else
	{
		ASSERTM(0, "Unhandled case while adding entity");
	}
}

//-----------------------------------------------------------------------------

void MainWindow::onDeleteEntityBtnReleased()
{
	if (m_ui->tab_objects->isVisible())
	{
		QItemSelectionModel* selectionModel = m_ui->listv_objects->selectionModel();
		QModelIndexList indexList = selectionModel->selectedIndexes();
		for (auto& index : indexList)
		{
			//QString data = index.data().toString();
			//m_objectsNamesList.removeOne(data);
			//m_objectsListModel.removeRow(index.row());
		}
	}
	else if (m_ui->tab_materials->isVisible())
	{

	}
	else
	{
		ASSERTM(0, "Unhandled case while adding entity");
	}
}

//-----------------------------------------------------------------------------

void MainWindow::setupUi()
{
	m_ui->setupUi(this);
	m_ui->listv_objects->setModel(&m_objectsListModel);

	for (int i = 0; i < 5; ++i)
	{
		QModelIndex propIdx = m_propertiesTableModel.index(i, 0);
		m_propertiesTableModel.setData(propIdx, QString("property"));

		QModelIndex valIdx = m_propertiesTableModel.index(i, 1);
		m_propertiesTableModel.setData(valIdx, QString("value"));
	}

	m_ui->tablev_properties->setModel(&m_propertiesTableModel);
	m_ui->tablev_properties->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	m_ui->tablev_properties->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

//-----------------------------------------------------------------------------

void MainWindow::setupConnections()
{
	connect(m_ui->chb_fillPolygons,		&QCheckBox::stateChanged,	this,				&MainWindow::onFillPolygonsValueChanged);

	connect(m_ui->btn_add,				&QPushButton::released,		this,				&MainWindow::onAddEntityBtnReleased);
	connect(m_ui->btn_delete,			&QPushButton::released,		this,				&MainWindow::onDeleteEntityBtnReleased);

	connect(m_ui->sld_camMoveSpeed,		&QSlider::valueChanged,		m_ui->oglw_screen,	&AppGlWidget::setCameraMoveSpeed);
	connect(m_ui->sld_camRotateSpeed,	&QSlider::valueChanged,		m_ui->oglw_screen,	&AppGlWidget::setCameraRotateSpeed);
}

//-----------------------------------------------------------------------------

void MainWindow::addObjectToGuiList(const jl::Object& _object)
{
	m_objectsNamesList << _object.getName().c_str();
	m_objectsListModel.setStringList(m_objectsNamesList);
}

//-----------------------------------------------------------------------------
