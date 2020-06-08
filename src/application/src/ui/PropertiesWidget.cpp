#include "ui/PropertiesWidget.hpp"
#include "ui/PropertyValueDelegate.hpp"
#include "ui/PropertyTypes.hpp"
#include "ui_PropertiesWidget.h"

#include "data/ObjectWrapper.hpp"

#include "renderer/managers/ResourceManager.hpp"
#include "renderer/managers/MaterialsManager.hpp"

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
		m_propertiesTableModel.setRowCount(2);

		refreshMeshes(_object.getModel());

		const QModelIndex transformIdx = index(k_transformRowIdx, k_nameColIdx, QModelIndex());
		m_propertiesTableModel.insertRows(0, 2, transformIdx);
		m_propertiesTableModel.insertColumns(0, 2, transformIdx);

		int transfromNum = 0;
		const QModelIndex posIdx = index(transfromNum++, k_nameColIdx, transformIdx);
		m_propertiesTableModel.insertRows(0, 3, posIdx);
		m_propertiesTableModel.insertColumns(0, 2, posIdx);

		const QModelIndex scaleIdx = index(transfromNum++, k_nameColIdx, transformIdx);
		m_propertiesTableModel.insertRows(0, 3, scaleIdx);
		m_propertiesTableModel.insertColumns(0, 2, scaleIdx);
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

void PropertiesWidget::refreshObjectSize()
{
	if (!std::holds_alternative<ObjectWrapper*>(m_activeEntity))
	{
		return;
	}

	ObjectWrapper* obj = std::get<ObjectWrapper*>(m_activeEntity);
	m_activeEntity = nullptr;

	constexpr int k_sizeRowIdx = 1;

	const QModelIndex scaleIdx = index(k_sizeRowIdx, k_nameColIdx, index(k_transformRowIdx, k_nameColIdx, QModelIndex()));

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
		const QModelIndex transformIdx = index(propNum, k_nameColIdx, rootIdx);

		setHeaderRow(propNum, rootIdx, "Transform");

		int transfromNum = 0;
		{
			const QModelIndex posIdx = index(transfromNum, k_nameColIdx, transformIdx);

			setHeaderRow(transfromNum, transformIdx, "Position");

			const glm::vec3& pos = _object.getPosition();
			const bool editable = _object.getTransformFlags() & jl::Object::TransfromFlags::Moveable;
			setPropertyRow(0, posIdx, "X", pos.x, editable);
			setPropertyRow(1, posIdx, "Y", pos.y, editable);
			setPropertyRow(2, posIdx, "Z", pos.z, editable);

			++transfromNum;
		}
		{
			const QModelIndex scaleIdx = index(transfromNum, k_nameColIdx, transformIdx);

			setHeaderRow(transfromNum, transformIdx, "Actual Size (in meters)");

			const glm::vec3& size = _object.getSize();
			const bool editable = _object.getTransformFlags() & jl::Object::TransfromFlags::Scaleable;
			setPropertyRow(0, scaleIdx, "Width",  size.x, editable);
			setPropertyRow(1, scaleIdx, "Height", size.y, editable);
			setPropertyRow(2, scaleIdx, "Depth",  size.z, editable);

			++transfromNum;
		}
		ASSERT(transfromNum == 2);

		++propNum;
	}
	ASSERT(propNum == 2);
}

//-----------------------------------------------------------------------------

void PropertiesWidget::refreshMeshes(const jl::Model* _model)
{
	const QModelIndex modelIdx = index(k_modelRowIdx, k_nameColIdx, QModelIndex());

	m_propertiesTableModel.removeRows(0, m_propertiesTableModel.rowCount(modelIdx), modelIdx);
	m_propertiesTableModel.removeColumns(0, m_propertiesTableModel.columnCount(modelIdx), modelIdx);

	if (_model)
	{
		const int meshesCount = static_cast<int>(_model->getMeshesCount());

		if (meshesCount > 0)
		{
			m_propertiesTableModel.insertRows(0, meshesCount, modelIdx);
			m_propertiesTableModel.insertColumns(0, 2, modelIdx);

			const QString meshMaterialtemplate = "Mesh #%1 material";
			for (int i = 0; i < meshesCount; ++i)
			{
				const QVariant value = QVariant::fromValue(MaterialUiWrapper{ _model->getMesh(i).getMaterial() });
				setPropertyRow(i, modelIdx, meshMaterialtemplate.arg(i + 1), value, true);
			}
		}
	}
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

		refreshObjectSize();
		refreshMeshes(_object.getModel());
	}
	else if (_idx.data().canConvert<MaterialUiWrapper>())
	{
		//MaterialUiWrapper materialWrapper = qvariant_cast<MaterialUiWrapper>(_idx.data());
		//_object.setMaterial(materialWrapper.material);
	}
	else
	{
		const QModelIndex transformIdx = index(k_transformRowIdx, k_nameColIdx, rootIdx);
		bool handled = false;
		int transformNum = 0;

		{
			const QModelIndex posIdx = index(transformNum++, k_nameColIdx, transformIdx);

			const QModelIndex x = index(0, k_valueColIdx, posIdx);
			const QModelIndex y = index(1, k_valueColIdx, posIdx);
			const QModelIndex z = index(2, k_valueColIdx, posIdx);

			if (_idx == x || _idx == y || _idx == z)
			{
				_object.setPosition(glm::vec3{ x.data().toFloat(), y.data().toFloat(), z.data().toFloat() });
				handled = true;
			}
		}

		if (!handled)
		{
			const QModelIndex sizeIdx = index(transformNum++, k_nameColIdx, transformIdx);

			const QModelIndex x = index(0, k_valueColIdx, sizeIdx);
			const QModelIndex y = index(1, k_valueColIdx, sizeIdx);
			const QModelIndex z = index(2, k_valueColIdx, sizeIdx);

			if (_idx == x || _idx == y || _idx == z)
			{
				_object.setSize(glm::vec3{ x.data().toFloat(), y.data().toFloat(), z.data().toFloat() });
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
