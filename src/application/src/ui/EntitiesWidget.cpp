#include "ui/EntitiesWidget.hpp"
#include "ui_EntitiesWidget.h"

#include "utils/Utils.hpp"

//-----------------------------------------------------------------------------

EntitiesWidget::EntitiesWidget(QWidget* parent)
	: QWidget(parent)
{
	m_ui = std::make_unique<Ui::EntitiesWidget>();
	m_ui->setupUi(this);

	connect(m_ui->btn_add, &QPushButton::released, this, &EntitiesWidget::onAddEntityBtnReleased);
	connect(m_ui->btn_delete, &QPushButton::released, this, &EntitiesWidget::onDeleteEntityBtnReleased);
}

//-----------------------------------------------------------------------------

void EntitiesWidget::setObjectsListModel(QAbstractItemModel& _model)
{
	m_ui->listv_objects->setModel(&_model);

	const QItemSelectionModel* objectsSelectionModel = m_ui->listv_objects->selectionModel();
	connect(objectsSelectionModel, &QItemSelectionModel::selectionChanged, this, &EntitiesWidget::onObjectSelected);
}

//-----------------------------------------------------------------------------

void EntitiesWidget::setMaterialsListModel(QAbstractItemModel& _model)
{
	m_ui->listv_materials->setModel(&_model);

	const QItemSelectionModel* objectsSelectionModel = m_ui->listv_materials->selectionModel();
	connect(objectsSelectionModel, &QItemSelectionModel::selectionChanged, this, &EntitiesWidget::onMaterialSelected);
}

//-----------------------------------------------------------------------------

void EntitiesWidget::setEntityActionHandler(IEntityActionHandler& _handler)
{
	m_actionHandler = &_handler;
}

//-----------------------------------------------------------------------------

void EntitiesWidget::onAddEntityBtnReleased()
{
	ASSERT(m_actionHandler);
	if (!m_actionHandler)
	{
		return;
	}

	if (m_ui->tab_objects->isVisible())
	{
		m_actionHandler->addObject();
	}
	else if (m_ui->tab_materials->isVisible())
	{
		m_actionHandler->addMaterial();
	}
	else
	{
		ASSERTM(0, "Unhandled case while adding entity");
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
	else
	{
		ASSERTM(0, "Unhandled case while removing entity");
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

void EntitiesWidget::onObjectSelected(const QItemSelection& _selection)
{
	onEntitySelected(_selection, std::bind(&IEntityActionHandler::objectSelected, m_actionHandler, std::placeholders::_1));
}

//-----------------------------------------------------------------------------

void EntitiesWidget::onMaterialSelected(const QItemSelection& _selection)
{
	onEntitySelected(_selection, std::bind(&IEntityActionHandler::materialSelected, m_actionHandler, std::placeholders::_1));
}

//-----------------------------------------------------------------------------

void EntitiesWidget::onEntitySelected(const QItemSelection& _selection, std::function<void(const QString&)>&& _callback)
{
	const QModelIndexList indexList = _selection.indexes();
	if (indexList.size() == 1)
	{
		const QString entityName = indexList.back().data().toString();
		_callback(entityName);
	}
	else
	{
		m_actionHandler->resetSelection();
	}
}

//-----------------------------------------------------------------------------
