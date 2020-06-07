#include "ui/PropertiesWidget.hpp"
#include "ui/PropertyValueDelegate.hpp"
#include "ui/PropertyTypes.hpp"
#include "ui/UiUtils.hpp"
#include "ui_PropertiesWidget.h"

#include "data/ObjectWrapper.hpp"

#include "managers/ResourceManager.hpp"
#include "managers/MaterialsManager.hpp"

#include "renderer/Model.hpp"
#include "renderer/Material.hpp"
#include "renderer/scene/Object.hpp"

#include "utils/Utils.hpp"

//-----------------------------------------------------------------------------

PropertiesWidget::PropertiesWidget(QWidget* parent)
	: QWidget(parent)
	, m_propertiesTableModel(0, 2, this)
	, m_activeEntity(nullptr)
{
	m_ui = std::make_unique<Ui::PropertiesWidget>();
	m_ui->setupUi(this);

	m_ui->treev_properties->setModel(&m_propertiesTableModel);
	m_ui->treev_properties->header()->setSectionResizeMode(QHeaderView::Stretch);

	m_propertiesTableModel.setHeaderData(k_nameColIdx, Qt::Horizontal, "Property");
	m_propertiesTableModel.setHeaderData(k_valueColIdx, Qt::Horizontal, "Value");

	m_ui->treev_properties->setItemDelegateForColumn(k_valueColIdx, new PropertyValueDelegate(m_ui->treev_properties));

	connect(&m_propertiesTableModel, &QStandardItemModel::dataChanged, this, &PropertiesWidget::onDataChanged);
}

//-----------------------------------------------------------------------------

void PropertiesWidget::setActiveEntity(ObjectWrapper& _object)
{
	if (std::holds_alternative<ObjectWrapper*>(m_activeEntity))
	{
		if (std::get<ObjectWrapper*>(m_activeEntity) == &_object)
		{
			return;
		}
	}
	else
	{
		m_propertiesTableModel.setRowCount(3);

		const QModelIndex transformIdx = index(k_transformRowIdx, k_nameColIdx, QModelIndex());
		m_propertiesTableModel.insertRows(0, 2, transformIdx);
		m_propertiesTableModel.insertColumns(0, 2, transformIdx);
	}

	m_activeEntity = nullptr;
	refreshObjectProperties(_object);
	m_activeEntity = &_object;
}

//-----------------------------------------------------------------------------

void PropertiesWidget::setActiveEntity(jl::Material& _material)
{
	if (std::holds_alternative<jl::Material*>(m_activeEntity))
	{
		if (std::get<jl::Material*>(m_activeEntity) == &_material)
		{
			return;
		}
	}

	const int propertiesCount = static_cast<int>(_material.getProperties().size());
	m_propertiesTableModel.setRowCount(propertiesCount);

	m_activeEntity = nullptr;
	refreshMaterialProperties(_material);
	m_activeEntity = &_material;
}

//-----------------------------------------------------------------------------

void PropertiesWidget::reset()
{
	m_activeEntity = nullptr;
	m_propertiesTableModel.setRowCount(0);
}

//-----------------------------------------------------------------------------

void PropertiesWidget::refreshObjectPos()
{
	if (!std::holds_alternative<ObjectWrapper*>(m_activeEntity))
	{
		return;
	}

	ObjectWrapper* obj = std::get<ObjectWrapper*>(m_activeEntity);
	m_activeEntity = nullptr;

	constexpr int k_posRowIdx = 0;

	const QModelIndex posIdx = index(k_posRowIdx, k_nameColIdx, index(k_transformRowIdx, k_nameColIdx, QModelIndex()));

	const glm::vec3& pos = obj->getPosition();
	const bool editable = obj->getTransformFlags() & jl::Object::TransfromFlags::Moveable;
	setCellValue(index(0, k_valueColIdx, posIdx), pos.x, editable);
	setCellValue(index(1, k_valueColIdx, posIdx), pos.y, editable);
	setCellValue(index(2, k_valueColIdx, posIdx), pos.z, editable);

	m_activeEntity = obj;
}

//-----------------------------------------------------------------------------

void PropertiesWidget::refreshObjectScale()
{
	if (!std::holds_alternative<ObjectWrapper*>(m_activeEntity))
	{
		return;
	}

	ObjectWrapper* obj = std::get<ObjectWrapper*>(m_activeEntity);
	m_activeEntity = nullptr;

	constexpr int k_scaleRowIdx = 1;

	const QModelIndex scaleIdx = index(k_scaleRowIdx, k_nameColIdx, index(k_transformRowIdx, k_nameColIdx, QModelIndex()));

	const glm::vec3& size = obj->getSize();
	const bool editable = obj->getTransformFlags() & jl::Object::TransfromFlags::Scaleable;
	setCellValue(index(0, k_valueColIdx, scaleIdx), size.x, editable);
	setCellValue(index(1, k_valueColIdx, scaleIdx), size.y, editable);
	setCellValue(index(2, k_valueColIdx, scaleIdx), size.z, editable);

	m_activeEntity = obj;
}

//-----------------------------------------------------------------------------

void PropertiesWidget::refreshObjectProperties(const ObjectWrapper& _object)
{
	const QModelIndex rootIdx;

	int propNum = 0;
	{
		const QVariant value = QVariant::fromValue(ModelUiWrapper{ _object.getModel() });
		setPropertyRow(propNum++, rootIdx, "Model", value, true);
	}
	{
		const QVariant value = QVariant::fromValue(MaterialUiWrapper{ _object.getMaterial() });
		setPropertyRow(propNum++, rootIdx, "Material", value, true);
	}
	{
		const QModelIndex transformIdx = index(propNum, k_nameColIdx, rootIdx);

		setHeaderRow(propNum, rootIdx, "Transform");

		int transfromNum = 0;
		{
			const QVector3D pos = toQtVec(_object.getPosition());
			const bool editable = _object.getTransformFlags() & jl::Object::TransfromFlags::Moveable;
			setPropertyRow(transfromNum++, transformIdx, "Position", pos, editable);
		}
		{
			const QVector3D size = toQtVec(_object.getSize());
			const bool editable  = _object.getTransformFlags() & jl::Object::TransfromFlags::Scaleable;
			setPropertyRow(transfromNum++, transformIdx, "Actual Size (in meters)", size, editable);
		}
		ASSERT(transfromNum == 2);

		++propNum;
	}
	ASSERT(propNum == 3);
}

//-----------------------------------------------------------------------------

void PropertiesWidget::refreshMaterialProperties(const jl::Material& _material)
{
	const auto& properties = _material.getProperties();
	const int propertiesCount = static_cast<int>(properties.size());

	const QModelIndex rootIdx;

	for (int i = 0; i < propertiesCount; ++i)
	{
		setPropertyRow(i, rootIdx, QString::fromStdString(properties[i].name), "", false);
	}
}

//-----------------------------------------------------------------------------

void PropertiesWidget::onDataChanged(const QModelIndex& _topLeft, const QModelIndex& _bottomRight, const QVector<int>& _roles)
{
	if (std::holds_alternative<ObjectWrapper*>(m_activeEntity))
	{
		onObjectChanged(_topLeft, *std::get<ObjectWrapper*>(m_activeEntity));
	}
	else if (std::holds_alternative<jl::Material*>(m_activeEntity))
	{

	}
}

//-----------------------------------------------------------------------------

void PropertiesWidget::onObjectChanged(const QModelIndex& _idx, ObjectWrapper& _object)
{
	const QModelIndex rootIdx;

	if (_idx.data().canConvert<ModelUiWrapper>())
	{
		ModelUiWrapper modelWrapper = qvariant_cast<ModelUiWrapper>(_idx.data());
		_object.setModel(modelWrapper.model);
	}
	else if (_idx.data().canConvert<MaterialUiWrapper>())
	{
		MaterialUiWrapper materialWrapper = qvariant_cast<MaterialUiWrapper>(_idx.data());
		_object.setMaterial(materialWrapper.material);
	}
	else
	{
		const QModelIndex transformIdx = index(k_transformRowIdx, k_nameColIdx, rootIdx);

		int transformNum = 0;
		if (_idx == index(transformNum++, k_valueColIdx, transformIdx))
		{
			const glm::vec3 pos = toGlmVec(qvariant_cast<QVector3D>(_idx.data()));
			_object.setPosition(pos);
		}
		else if (_idx == index(transformNum++, k_nameColIdx, transformIdx))
		{
			const glm::vec3 size = toGlmVec(qvariant_cast<QVector3D>(_idx.data()));
			if (size != _object.getSize())
			{
				_object.setSize(size);
			}
		}
	}
}

//-----------------------------------------------------------------------------

void PropertiesWidget::setHeaderRow(int _row, const QModelIndex& _parent, const QString& _name)
{
	setCellValue(index(_row, k_nameColIdx, _parent), _name, false);
	setCellValue(index(_row, k_valueColIdx, _parent), "", false);
}

//-----------------------------------------------------------------------------

void PropertiesWidget::setPropertyRow(int _row, const QModelIndex& _parent, const QString& _name, const QVariant& _value, bool _editable)
{
	setCellValue(index(_row, k_nameColIdx, _parent), _name, false);
	setCellValue(index(_row, k_valueColIdx, _parent), _value, _editable);
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
