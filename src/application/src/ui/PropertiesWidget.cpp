#include "ui/PropertiesWidget.hpp"
#include "ui_PropertiesWidget.h"

#include "ui/props/MaterialPropertyValueVisitor.hpp"
#include "ui/props/PropertyValueDelegate.hpp"
#include "ui/props/PropertyTypes.hpp"

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

		const QModelIndex transformIdx = index(k_transformRowIdx, k_nameColIdx, QModelIndex());
		m_propertiesTableModel.insertRows(0, k_transformsNum, transformIdx);
		m_propertiesTableModel.insertColumns(0, 2, transformIdx);
	}

	m_activeEntity = nullptr;
	refreshMeshes(_object.getModel());
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

	const QModelIndex transformIdx = index(k_transformRowIdx, k_nameColIdx, QModelIndex());

	const QVariant pos = QVariant::fromValue(TransformVecUiWrapper{ obj->getPosition() });
	const bool editable = obj->getTransformFlags() & jl::Object::TransfromFlags::Moveable;
	setCellValue(index(0, k_valueColIdx, transformIdx), pos, editable);

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

	const QModelIndex transformIdx = index(k_transformRowIdx, k_nameColIdx, QModelIndex());

	const QVariant size = QVariant::fromValue(TransformVecUiWrapper{ obj->getSize() });
	const bool editable = obj->getTransformFlags() & jl::Object::TransfromFlags::Scaleable;
	setCellValue(index(1, k_valueColIdx, transformIdx), size, editable);

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
			const QVariant pos = QVariant::fromValue(TransformVecUiWrapper{ _object.getPosition() });
			const bool editable = _object.getTransformFlags() & jl::Object::TransfromFlags::Moveable;

			setPropertyRow(transfromNum++, transformIdx, "Position", pos, editable);
		}
		{
			const QVariant size = QVariant::fromValue(TransformVecUiWrapper{ _object.getSize() });
			const bool editable = _object.getTransformFlags() & jl::Object::TransfromFlags::Scaleable;

			setPropertyRow(transfromNum++, transformIdx, "Actual Size (in meters)", size, editable);
		}
		{
			const QVariant rotation = QVariant::fromValue(TransformVecUiWrapper{ _object.getRotation() });
			const bool editable = _object.getTransformFlags() & jl::Object::TransfromFlags::Rotatable;

			setPropertyRow(transfromNum++, transformIdx, "Rotatation", rotation, editable);
		}
		ASSERT(transfromNum == k_transformsNum);

		++propNum;
	}
	ASSERT(propNum == 2);
}

//-----------------------------------------------------------------------------

void PropertiesWidget::refreshMeshes(jl::Model* _model)
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

			const QString meshMaterialtemplate = "Mesh %1";
			for (int i = 0; i < meshesCount; ++i)
			{
				jl::Mesh& mesh = _model->getMesh(i);

				QString materialName;
				if (const jl::Material* material = mesh.getMaterial())
				{
					materialName = MaterialsManager::getInstance().findMaterialName(*material).c_str();
				}

				const QVariant value = QVariant::fromValue(MaterialUiWrapper{ materialName, &mesh });
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
		const QVariant value = std::visit(MaterialPropertyValueVisitor{}, properties[i].value);
		setPropertyRow(i, rootIdx, QString::fromStdString(properties[i].name), value, true);
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
		_object.setModel(modelWrapper.value);

		refreshObjectSize();
		refreshMeshes(_object.getModel());
	}
	else
	{
		const QModelIndex transformIdx = index(k_transformRowIdx, k_nameColIdx, rootIdx);

		int transformNum = 0;
		if (_idx == index(transformNum++, k_valueColIdx, transformIdx))
		{
			const TransformVecUiWrapper pos = qvariant_cast<TransformVecUiWrapper>(_idx.data());
			_object.setPosition(pos.value);
		}
		else if (_idx == index(transformNum++, k_nameColIdx, transformIdx))
		{
			const TransformVecUiWrapper size = qvariant_cast<TransformVecUiWrapper>(_idx.data());
			if (size.value != _object.getSize())
			{
				_object.setSize(size.value);
			}
		}
		else if (_idx == index(transformNum++, k_valueColIdx, transformIdx))
		{
			const TransformVecUiWrapper roatation = qvariant_cast<TransformVecUiWrapper>(_idx.data());
			_object.setRotation(roatation.value);
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
