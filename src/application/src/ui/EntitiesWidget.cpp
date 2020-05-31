#include "ui/EntitiesWidget.hpp"
#include "ui_EntitiesWidget.h"

#include "utils/Utils.hpp"

//-----------------------------------------------------------------------------

EntitiesWidget::EntitiesWidget(QWidget* parent)
	: QWidget(parent)
{
	m_ui = std::make_unique<Ui::EntitiesWidget>();
	m_ui->setupUi(this);

	m_ui->tabv_data->setCurrentIndex(0);

	connect(m_ui->btn_add,		&QPushButton::released,			this, &EntitiesWidget::onAddEntityBtnReleased);
	connect(m_ui->btn_delete,	&QPushButton::released,			this, &EntitiesWidget::onDeleteEntityBtnReleased);
	connect(m_ui->tabv_data,	&QTabWidget::currentChanged,	this, &EntitiesWidget::onCurrentTabChanged);
}

//-----------------------------------------------------------------------------

void EntitiesWidget::setObjectsListModel(QAbstractItemModel& _model)
{
	m_ui->listv_objects->setModel(&_model);

	const QItemSelectionModel* selectionModel = m_ui->listv_objects->selectionModel();
	connect(selectionModel, &QItemSelectionModel::selectionChanged, this, &EntitiesWidget::onEntitySelected);
}

//-----------------------------------------------------------------------------

void EntitiesWidget::setMaterialsListModel(QAbstractItemModel& _model)
{
	m_ui->listv_materials->setModel(&_model);

	const QItemSelectionModel* selectionModel = m_ui->listv_materials->selectionModel();
	connect(selectionModel, &QItemSelectionModel::selectionChanged, this, &EntitiesWidget::onEntitySelected);
}

//-----------------------------------------------------------------------------

void EntitiesWidget::setEntityActionHandler(IEntityActionHandler& _handler)
{
	m_actionHandler = &_handler;
}

//-----------------------------------------------------------------------------

void EntitiesWidget::onCurrentTabChanged(int _idx)
{
	const QWidget* currentTab = m_ui->tabv_data->widget(_idx);
	if (currentTab == m_ui->tab_objects)
	{
		const QItemSelectionModel* selectionModel = m_ui->listv_objects->selectionModel();
		onEntitySelected(selectionModel->selection());
	}
	else if (currentTab == m_ui->tab_materials)
	{
		const QItemSelectionModel* selectionModel = m_ui->listv_materials->selectionModel();
		onEntitySelected(selectionModel->selection());
	}
}

//-----------------------------------------------------------------------------

void EntitiesWidget::onAddEntityBtnReleased()
{
	ASSERT(m_actionHandler);
	if (!m_actionHandler)
	{
		return;
	}

	ASSERTM(m_ui->tab_objects->isVisible() || m_ui->tab_materials->isVisible(), "Unhandled case while adding entity");
	if (m_ui->tab_objects->isVisible())
	{
		m_actionHandler->addObject();
	}
	else if (m_ui->tab_materials->isVisible())
	{
		m_actionHandler->addMaterial();
	}
}

//-----------------------------------------------------------------------------

void EntitiesWidget::onDeleteEntityBtnReleased()
{
	ASSERT(m_actionHandler);
	if (!m_actionHandler)
	{
		return;
	}

	const QAbstractItemView* view = nullptr;
	std::function<void(const QString&)> deleteFun;

	ASSERTM(m_ui->tab_objects->isVisible() || m_ui->tab_materials->isVisible(), "Unhandled case while removing entity");
	if (m_ui->tab_objects->isVisible())
	{
		view = m_ui->listv_objects;
		deleteFun = std::bind(&IEntityActionHandler::deleteObject, m_actionHandler, std::placeholders::_1);
	}
	else if (m_ui->tab_materials->isVisible())
	{
		view = m_ui->listv_materials;
		deleteFun = std::bind(&IEntityActionHandler::deleteMaterial, m_actionHandler, std::placeholders::_1);
	}

	if (view && deleteFun)
	{
		const QItemSelectionModel* selectionModel = view->selectionModel();
		const QModelIndexList indexList = selectionModel->selectedIndexes();
		for (const auto& index : indexList)
		{
			const QString entityName = index.data().toString();
			deleteFun(entityName);
		}
	}
}

//-----------------------------------------------------------------------------

void EntitiesWidget::onEntitySelected(const QItemSelection& _selection)
{
	ASSERT(m_actionHandler);
	if (!m_actionHandler)
	{
		return;
	}

	const QModelIndexList indexList = _selection.indexes();
	if (indexList.size() == 1)
	{
		const QString entityName = indexList.back().data().toString();

		ASSERT(m_ui->tab_objects->isVisible() || m_ui->tab_materials->isVisible());
		if (m_ui->tab_objects->isVisible())
		{
			m_actionHandler->objectSelected(entityName);
		}
		else if (m_ui->tab_materials->isVisible())
		{
			m_actionHandler->materialSelected(entityName);
		}
	}
	else
	{
		m_actionHandler->resetSelection();
	}
}

//-----------------------------------------------------------------------------
