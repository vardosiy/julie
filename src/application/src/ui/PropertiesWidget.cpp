#include "ui/PropertiesWidget.hpp"
#include "ui_PropertiesWidget.h"

#include "managers/ResourceManager.hpp"
#include "managers/MaterialsManager.hpp"

#include "renderer/Material.hpp"
#include "renderer/scene/Object.hpp"

#include "utils/Utils.hpp"

//-----------------------------------------------------------------------------

const QString PropertiesWidget::k_objectPropModel		= "Model";
const QString PropertiesWidget::k_objectPropMaterial	= "Material";

const QString PropertiesWidget::k_columnHeaderPropValue	= "Value";
const QString PropertiesWidget::k_columnHeaderPropName	= "Property";

//-----------------------------------------------------------------------------

PropertiesWidget::PropertiesWidget(QWidget* parent)
	: QWidget(parent)
	, m_propertiesTableModel(0, 2, this)
{
	m_ui = std::make_unique<Ui::PropertiesWidget>();
	m_ui->setupUi(this);

	m_ui->tablev_properties->setModel(&m_propertiesTableModel);
	m_ui->tablev_properties->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

	m_propertiesTableModel.setHeaderData(k_propNameIdx, Qt::Horizontal, k_columnHeaderPropName);
	m_propertiesTableModel.setHeaderData(k_propValueIdx, Qt::Horizontal, k_columnHeaderPropValue);

	connect(&m_propertiesTableModel, &QStandardItemModel::dataChanged, this, &PropertiesWidget::onDataChanged);
}

//-----------------------------------------------------------------------------

void PropertiesWidget::setActiveEntity(jl::Object& _object)
{
	constexpr int k_objectPropsCount = 2;

	m_activeEntity = nullptr;
	m_propertiesTableModel.setRowCount(k_objectPropsCount);

	int propNum = 0;
	{
		QString modelSourceFile;
		if (const jl::Model* model = _object.getModel())
		{
			modelSourceFile = ResourceManager::getInstance().getSourceFile(*model).c_str();
		}

		setTableCellValue(propNum, k_propNameIdx, k_objectPropModel);
		setTableCellValue(propNum++, k_propValueIdx, modelSourceFile);
	}
	{
		QString materialName;
		if (const jl::Material* material = _object.getMaterial())
		{
			materialName = MaterialsManager::getInstance().getMaterialName(*material).c_str();
		}

		setTableCellValue(propNum, k_propNameIdx, k_objectPropMaterial);
		setTableCellValue(propNum++, k_propValueIdx, materialName);
	}
	ASSERT(k_objectPropsCount == propNum);

	m_activeEntity = &_object;
}

//-----------------------------------------------------------------------------

void PropertiesWidget::setActiveEntity(jl::Material& _material)
{
	m_activeEntity = nullptr;
	m_propertiesTableModel.setRowCount(0);
}

//-----------------------------------------------------------------------------

void PropertiesWidget::reset()
{
	m_activeEntity = nullptr;
	m_propertiesTableModel.setRowCount(0);
}

//-----------------------------------------------------------------------------

void PropertiesWidget::setTableCellValue(int _row, int _col, const QString& _value)
{
	ASSERT(m_propertiesTableModel.rowCount() > _row);
	ASSERT(m_propertiesTableModel.columnCount() > _col);

	const QModelIndex idx = m_propertiesTableModel.index(_row, _col);
	m_propertiesTableModel.setData(idx, _value);
}

//-----------------------------------------------------------------------------

void PropertiesWidget::onDataChanged(const QModelIndex& _topLeft, const QModelIndex& _bottomRight, const QVector<int>& _roles)
{
	ASSERT(_topLeft.row() < 2);

	const std::string newValue = _topLeft.data().toString().toStdString();
	std::visit(DataChangedHandleVisitor{ _topLeft.row(), newValue }, m_activeEntity);
}

//-----------------------------------------------------------------------------

void PropertiesWidget::DataChangedHandleVisitor::operator()(jl::Object* _object)
{
	switch (m_propIdx)
	{
	case 0:
		if (const jl::Model* model = ResourceManager::getInstance().loadModel(m_newValue))
		{
			_object->setModel(*model);
		}
		break;

	case 1:
		if (const jl::Material* material = MaterialsManager::getInstance().getMaterial(m_newValue))
		{
			_object->setMaterial(*material);
		}
		break;

	default:
		ASSERT(0);
	}
}

//-----------------------------------------------------------------------------

void PropertiesWidget::DataChangedHandleVisitor::operator()(jl::Material* _material)
{
}

//-----------------------------------------------------------------------------

void PropertiesWidget::DataChangedHandleVisitor::operator()(std::nullptr_t _null)
{
}

//-----------------------------------------------------------------------------
