#include "ui/PropertiesWidget.hpp"
#include "ui_PropertiesWidget.h"

#include "managers/ResourceManager.hpp"
#include "managers/MaterialsManager.hpp"

#include "renderer/Material.hpp"
#include "renderer/scene/Object.hpp"

#include "utils/Utils.hpp"

//-----------------------------------------------------------------------------

PropertiesWidget::PropertiesWidget(QWidget* parent)
	: QWidget(parent)
	, m_propertiesTableModel(0, 2, this)
{
	m_ui = std::make_unique<Ui::PropertiesWidget>();
	m_ui->setupUi(this);

	m_ui->treev_properties->setModel(&m_propertiesTableModel);
	m_ui->treev_properties->header()->setSectionResizeMode(QHeaderView::Stretch);

	m_propertiesTableModel.setHeaderData(k_nameColIdx, Qt::Horizontal, "Property");
	m_propertiesTableModel.setHeaderData(k_valueColIdx, Qt::Horizontal, "Value");

	connect(&m_propertiesTableModel, &QStandardItemModel::dataChanged, this, &PropertiesWidget::onDataChanged);
}

//-----------------------------------------------------------------------------

void PropertiesWidget::setActiveEntity(jl::Object& _object)
{
	constexpr int k_objectPropsCount = 3;

	m_activeEntity = nullptr;
	m_propertiesTableModel.setRowCount(k_objectPropsCount);

	const QModelIndex rootIdx;

	int propNum = 0;
	{
		QString modelSourceFile;
		if (const jl::Model* model = _object.getModel())
		{
			modelSourceFile = ResourceManager::getInstance().getSourceFile(*model).c_str();
		}
		setPropertyRow(propNum++, rootIdx, "Model", modelSourceFile);
	}
	{
		QString materialName;
		if (const jl::Material* material = _object.getMaterial())
		{
			materialName = MaterialsManager::getInstance().findMaterialName(*material).c_str();
		}
		setPropertyRow(propNum++, rootIdx, "Material", materialName);
	}
	{
		setHeaderRow(propNum, rootIdx, "Transform");
		setupObjectTransform(index(propNum, k_nameColIdx, rootIdx), _object);

		++propNum;
	}
	ASSERT(k_objectPropsCount == propNum);

	m_activeEntity = &_object;
}

//-----------------------------------------------------------------------------

void PropertiesWidget::setupObjectTransform(const QModelIndex& _parent, const jl::Object& _object)
{
	m_propertiesTableModel.insertRows(0, 2, _parent);
	m_propertiesTableModel.insertColumns(0, 2, _parent);

	int transfromNum = 0;
	{
		const QModelIndex posIdx = index(transfromNum, k_nameColIdx, _parent);
		m_propertiesTableModel.insertRows(0, 3, posIdx);
		m_propertiesTableModel.insertColumns(0, 2, posIdx);

		setHeaderRow(transfromNum, _parent, "Position");

		const glm::vec3& pos = _object.getPosition();
		setPropertyRow(0, posIdx, "X", pos.x);
		setPropertyRow(1, posIdx, "Y", pos.y);
		setPropertyRow(2, posIdx, "Z", pos.z);

		++transfromNum;
	}
	{
		const QModelIndex scaleIdx = index(transfromNum, k_nameColIdx, _parent);
		m_propertiesTableModel.insertRows(0, 3, scaleIdx);
		m_propertiesTableModel.insertColumns(0, 2, scaleIdx);

		setHeaderRow(transfromNum, _parent, "Actual Size (in meters)");

		const glm::vec3& scale = _object.getScale();
		setPropertyRow(0, scaleIdx, "Width",  scale.x);
		setPropertyRow(1, scaleIdx, "Height", scale.y);
		setPropertyRow(2, scaleIdx, "Depth",  scale.z);

		++transfromNum;
	}
}

//-----------------------------------------------------------------------------

void PropertiesWidget::setActiveEntity(jl::Material& _material)
{
	m_activeEntity = nullptr;

	const auto& properties = _material.getProperties();
	const int propertiesCount = properties.size();

	const QModelIndex rootIdx;

	m_propertiesTableModel.setRowCount(propertiesCount);
	for (int i = 0; i < propertiesCount; ++i)
	{
		setPropertyRow(i, rootIdx, QString::fromStdString(properties[i].name), "");
	}

	m_activeEntity = &_material;
}

//-----------------------------------------------------------------------------

void PropertiesWidget::reset()
{
	m_activeEntity = nullptr;
	m_propertiesTableModel.setRowCount(0);
}

//-----------------------------------------------------------------------------

void PropertiesWidget::setHeaderRow(int _row, const QModelIndex& _parent, const QString& _name)
{
	setCellValue(index(_row, k_nameColIdx, _parent), _name, false);
	setCellValue(index(_row, k_valueColIdx, _parent), "", false);
}

//-----------------------------------------------------------------------------

void PropertiesWidget::setPropertyRow(int _row, const QModelIndex& _parent, const QString& _name, const QVariant& _value)
{
	setCellValue(index(_row, k_nameColIdx, _parent), _name, false);
	setCellValue(index(_row, k_valueColIdx, _parent), _value, true);
}

//-----------------------------------------------------------------------------

void PropertiesWidget::setCellValue(const QModelIndex& _idx, const QVariant& _value, bool _enableEditing)
{
	m_propertiesTableModel.setData(_idx, _value);

	QStandardItem* item = m_propertiesTableModel.itemFromIndex(_idx);
	ASSERT(item);
	if (item)
	{
		item->setFlags(_enableEditing ? item->flags() | Qt::ItemIsEditable : item->flags() & ~Qt::ItemIsEditable);
	}
}

//-----------------------------------------------------------------------------

QModelIndex PropertiesWidget::index(int _row, int _col, const QModelIndex& _parent)
{
	return m_propertiesTableModel.index(_row, _col, _parent);
}

//-----------------------------------------------------------------------------

void PropertiesWidget::onDataChanged(const QModelIndex& _topLeft, const QModelIndex& _bottomRight, const QVector<int>& _roles)
{
	if (std::holds_alternative<jl::Object*>(m_activeEntity))
	{
		onObjectChanged(_topLeft, *std::get<jl::Object*>(m_activeEntity));
	}
	else if (std::holds_alternative<jl::Material*>(m_activeEntity))
	{

	}
}

//-----------------------------------------------------------------------------

void PropertiesWidget::onObjectChanged(const QModelIndex& _idx, jl::Object& _object)
{
	const QModelIndex rootIdx;
	const QString newValue = _idx.data().toString();

	int propNum = 0;
	if (_idx == index(propNum++, k_valueColIdx, rootIdx))
	{
		if (const jl::Model* model = ResourceManager::getInstance().loadModel(newValue.toStdString()))
		{
			_object.setModel(*model);
		}
	}
	else if (_idx == index(propNum++, k_valueColIdx, rootIdx))
	{
		if (const jl::Material* material = MaterialsManager::getInstance().findMaterial(newValue.toStdString()))
		{
			_object.setMaterial(*material);
		}
	}
	else
	{
		const QModelIndex transformIdx = index(propNum++, k_nameColIdx, rootIdx);
		bool handled = false;
		int transformNum = 0;

		{
			const QModelIndex posIdx = index(transformNum++, k_nameColIdx, transformIdx);

			const QModelIndex x = index(0, k_valueColIdx, posIdx);
			const QModelIndex y = index(1, k_valueColIdx, posIdx);
			const QModelIndex z = index(2, k_valueColIdx, posIdx);

			if (_idx == x || _idx == y || _idx == z)
			{
				glm::vec3 newPos(x.data().toFloat(), y.data().toFloat(), z.data().toFloat());

				_object.setPosition(newPos);
				handled = true;
			}
		}

		if (!handled)
		{
			const QModelIndex scaleIdx = index(transformNum++, k_nameColIdx, transformIdx);

			const QModelIndex x = index(0, k_valueColIdx, scaleIdx);
			const QModelIndex y = index(1, k_valueColIdx, scaleIdx);
			const QModelIndex z = index(2, k_valueColIdx, scaleIdx);

			if (_idx == x || _idx == y || _idx == z)
			{
				glm::vec3 newPos(x.data().toFloat(), y.data().toFloat(), z.data().toFloat());

				_object.setScale(newPos);
			}
		}
	}
}

//-----------------------------------------------------------------------------
