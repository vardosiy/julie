#include "ui/MainWidget.hpp"
#include "ui_MainWidget.h"

#include "data/Object.hpp"
#include "data/Material.hpp"

#include "managers/ResourceManager.hpp"

#include "renderer/scene/Scene.hpp"
#include "renderer/Model.hpp"
#include "renderer/Shader.hpp"
#include "utils/Utils.hpp"

#include <QKeyEvent>

#include <QAbstractListModel>

#include <renderer/Model.hpp>
#include "factories/ModelsFactory.hpp"

//-----------------------------------------------------------------------------

std::unique_ptr<data::Material> g_material;
std::unique_ptr<jl::Model> g_model;

static std::unique_ptr<jl::Model> createRoom()
{
	std::vector<jl::Vertex> vertices(8);
	vertices[0].pos = glm::vec3(-1.0f, 1.0f, -1.0f);  // back rect
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

MainWidget::MainWidget(QWidget* parent)
	: QWidget(parent)
	, m_ui(std::make_unique<Ui::MainWidget>())
	, m_objectsListModel(this)
{
	m_ui->setupUi(this);
	m_ui->listv_objects->setModel(&m_objectsListModel);

	setupConnections();

	m_glLoadedConnection = m_ui->oglw_screen->registerOnGlLoaded(
		[this]()
		{
			m_glLoadedConnection.disconnect();
			onGlLoaded();
		}
	);
}

//-----------------------------------------------------------------------------

MainWidget::~MainWidget() = default;

//-----------------------------------------------------------------------------

void MainWidget::onGlLoaded()
{
	g_material.reset(new data::Material("material"));
	g_material->setProperty("u_color", glm::vec4(1.0f));
	g_material->setShader(*ResourceManager::getInstance().loadShader("res/shaders/composed/SimpleColor.shdata"));

	g_model = createRoom();
}

//-----------------------------------------------------------------------------

void MainWidget::onFillPolygonsValueChanged(int _state)
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

void MainWidget::onAddEntityBtnReleased()
{
	if (m_ui->tab_objects->isVisible())
	{
		auto object = std::make_unique<data::Object>("name");
		object->setModel(*g_model);
		object->setMaterial(*g_material);

		m_ui->oglw_screen->onObjectAdded(*object);

		addObjectToGuiList(*object);
		m_project.addEntity(std::move(object));
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

void MainWidget::onDeleteEntityBtnReleased()
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

void MainWidget::setupConnections()
{
	connect(m_ui->chb_fillPolygons,		&QCheckBox::stateChanged,	this,				&MainWidget::onFillPolygonsValueChanged);

	connect(m_ui->btn_add,				&QPushButton::released,		this,				&MainWidget::onAddEntityBtnReleased);
	connect(m_ui->btn_delete,			&QPushButton::released,		this,				&MainWidget::onDeleteEntityBtnReleased);

	connect(m_ui->sld_camMoveSpeed,		&QSlider::valueChanged,		m_ui->oglw_screen,	&AppGlWidget::setCameraMoveSpeed);
	connect(m_ui->sld_camRotateSpeed,	&QSlider::valueChanged,		m_ui->oglw_screen,	&AppGlWidget::setCameraRotateSpeed);
}

//-----------------------------------------------------------------------------

void MainWidget::addObjectToGuiList(const data::Object& _object)
{
	m_objectsNamesList << _object.getName().c_str();
	m_objectsListModel.setStringList(m_objectsNamesList);
}

//-----------------------------------------------------------------------------
