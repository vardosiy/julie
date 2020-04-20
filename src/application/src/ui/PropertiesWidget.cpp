#include "ui/PropertiesWidget.hpp"
#include "ui_PropertiesWidget.h"

#include "managers/ResourceManager.hpp"
#include "managers/MaterialsManager.hpp"

#include "renderer/scene/Object.hpp"
#include "renderer/Material.hpp"

#include "utils/Utils.hpp"

//-----------------------------------------------------------------------------

const QString PropertiesWidget::k_objectPropModel = "Model";
const QString PropertiesWidget::k_objectPropMaterial = "Material";

//-----------------------------------------------------------------------------

PropertiesWidget::PropertiesWidget(QWidget* parent)
	: QWidget(parent)
	, m_propertiesTableModel(0, 2, this)
{
	m_ui = std::make_unique<Ui::PropertiesWidget>();
	m_ui->setupUi(this);

	m_ui->tablev_properties->setModel(&m_propertiesTableModel);
	m_ui->tablev_properties->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

//-----------------------------------------------------------------------------

void PropertiesWidget::setActiveEntity(jl::Object& _object)
{
	constexpr int k_objectPropsCount = 2;

	m_activeEntity = &_object;
	m_propertiesTableModel.setRowCount(k_objectPropsCount);

	const ResourceManager& resourceMgr = ResourceManager::getInstance();
	const MaterialsManager& materialsMgr = MaterialsManager::getInstance();

	int propNum = 0;
	{
		QString modelSourceFile;
		if (const jl::Model* model = _object.getModel())
		{
			modelSourceFile = QString::fromStdString(resourceMgr.getSourceFile(*model).c_str());
		}
		setPropValue(propNum++, k_objectPropModel, modelSourceFile);
	}
	{
		QString materialName;
		if (const jl::Material* material = _object.getMaterial())
		{
			materialName = QString::fromStdString(materialsMgr.getMaterialName(*material));
		}
		setPropValue(propNum++, k_objectPropMaterial, materialName);
	}

	ASSERT(k_objectPropsCount == propNum);
}

//-----------------------------------------------------------------------------

void PropertiesWidget::setActiveEntity(jl::Material& _material)
{
	m_propertiesTableModel.setRowCount(0);
}

//-----------------------------------------------------------------------------

void PropertiesWidget::reset()
{
	m_activeEntity = nullptr;
	m_propertiesTableModel.setRowCount(0);
}

//-----------------------------------------------------------------------------

template<typename T>
void PropertiesWidget::setPropValue(int _idx, const QString& _name, const T& _value)
{
	constexpr int k_propNameIdx = 0;
	constexpr int k_propValueIdx = 1;

	ASSERT(m_propertiesTableModel.rowCount() > _idx);

	{
		QModelIndex propNameIdx = m_propertiesTableModel.index(_idx, k_propNameIdx);
		m_propertiesTableModel.setData(propNameIdx, _name);
	}
	{
		QModelIndex valueIdx = m_propertiesTableModel.index(_idx, k_propValueIdx);
		m_propertiesTableModel.setData(valueIdx, _value);
	}
}

//-----------------------------------------------------------------------------
