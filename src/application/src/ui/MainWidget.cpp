#include "ui/MainWidget.hpp"
#include "ui_MainWidget.h"

#include "data/Object.hpp"
#include "data/Material.hpp"

#include "factories/ModelsFactory.hpp"
#include "factories/ShadersFactory.hpp"

#include "renderer/scene/Scene.hpp"
#include "renderer/Model.hpp"
#include "renderer/Shader.hpp"
#include "utils/Utils.hpp"

#include <QStringListModel>
#include <QKeyEvent>
#include <fmt/format.h>

std::unique_ptr<jl::Model> g_model;
std::unique_ptr<jl::Shader> g_shader;
std::unique_ptr<data::Material> g_material;

//-----------------------------------------------------------------------------

MainWidget::MainWidget(QWidget* parent)
	: QWidget(parent)
	, m_ui(std::make_unique<Ui::MainWidget>())
	, m_objectsListModel(this)
{
	m_ui->setupUi(this);
	m_ui->listv_objects->setModel(&m_objectsListModel);

	connect(m_ui->chb_fillPolygons, &QCheckBox::stateChanged, this, &MainWidget::onFillPolygonsValueChanged);

	connect(m_ui->btn_add, &QPushButton::released, this, &MainWidget::onAddEntityReleased);
	connect(m_ui->btn_delete, &QPushButton::released, this, &MainWidget::onDeleteEntityReleased);

	m_ui->oglw_screen->doOnGlInitialized([this]() { onGlLoaded(); });
}

//-----------------------------------------------------------------------------

MainWidget::~MainWidget() = default;

//-----------------------------------------------------------------------------

void MainWidget::onGlLoaded()
{
	g_model = ModelsFactory::loadFromFile("res/models/Bila.nfg");
	g_shader = ShadersFactory::load("res/shaders/composed/SimpleColor.shdata");
	g_material.reset(new data::Material("material"));
	g_material->setProperty("u_color", glm::vec4(1.0f));
	g_material->setShader(*g_shader);
}

//-----------------------------------------------------------------------------

void MainWidget::onFillPolygonsValueChanged(int _state)
{
	AppGlWidget::DrawMode drawMode = AppGlWidget::DrawMode::Fill;

	switch (_state)
	{
		case Qt::CheckState::Checked:
		{
			drawMode = AppGlWidget::DrawMode::Fill;
		}
		break;

		case Qt::CheckState::PartiallyChecked:
		{
		}
		break;

		case Qt::CheckState::Unchecked:
		{
			drawMode = AppGlWidget::DrawMode::Edges;
		}
		break;

		default:
			ASSERT(0);
	}

	m_ui->oglw_screen->setDrawMode(drawMode);
}

//-----------------------------------------------------------------------------

void MainWidget::onAddEntityReleased()
{
	const bool test1 = m_ui->tab_objects->isVisible();
	const bool test2 = m_ui->tab_materials->isVisible();
	const bool test3 = m_ui->tab_objects->isActiveWindow();
	const bool test4 = m_ui->tab_materials->isActiveWindow();

	if (m_ui->tab_objects->isVisible())
	{
		auto object = std::make_unique<data::Object>("name");
		object->setModel(*g_model);
		object->setMaterial(*g_material);

		m_ui->oglw_screen->onObjectAdded(*object);

		addObjectToList(*object);
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

void MainWidget::onDeleteEntityReleased()
{

}

//-----------------------------------------------------------------------------

void MainWidget::addObjectToList(const data::Object& _object)
{
	m_objectsNamesList << _object.getName().c_str();
	m_objectsListModel.setStringList(m_objectsNamesList);
}

//-----------------------------------------------------------------------------
