#include "ui/PropertiesWidget.hpp"
#include "ui_PropertiesWidget.h"

#include "ui/props/MaterialPropertyValueVisitor.hpp"
#include "ui/props/PropertyValueDelegate.hpp"
#include "ui/props/PropertyTypes.hpp"

#include "data/ObjectWrapper.hpp"

#include "julie/managers/ResourceManager.hpp"
#include "julie/managers/MaterialsManager.hpp"

#include "julie/Model.hpp"
#include "julie/Material.hpp"
#include "julie/scene/Object.hpp"

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
		reset();

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

	reset();

	const int propertiesCount = static_cast<int>(_material.getProperties().size());
	m_propertiesTableModel.setRowCount(propertiesCount);

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

	auto editCallback = [obj](const glm::vec3& _val) { obj->setPosition(_val); };
	const QVariant pos = QVariant::fromValue(TransformVecUiWrapper{ obj->getPosition(), editCallback });

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

	auto editCallback = [obj](const glm::vec3& _val) { obj->setSize(_val); };
	const QVariant size = QVariant::fromValue(TransformVecUiWrapper{ obj->getSize(), editCallback });

	const bool editable = obj->getTransformFlags() & jl::Object::TransfromFlags::Scaleable;
	setCellValue(index(1, k_valueColIdx, transformIdx), size, editable);

	m_activeEntity = obj;
}

//-----------------------------------------------------------------------------

void PropertiesWidget::refreshObjectProperties(ObjectWrapper& _object)
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
			auto editCallback = [&_object](const glm::vec3& _val) { _object.setPosition(_val); };
			const QVariant pos = QVariant::fromValue(TransformVecUiWrapper{ _object.getPosition(), editCallback });

			const bool editable = _object.getTransformFlags() & jl::Object::TransfromFlags::Moveable;
			setPropertyRow(transfromNum++, transformIdx, "Position", pos, editable);
		}
		{
			auto editCallback = [&_object](const glm::vec3& _val) { _object.setSize(_val); };
			const QVariant size = QVariant::fromValue(TransformVecUiWrapper{ _object.getSize(), editCallback });

			const bool editable = _object.getTransformFlags() & jl::Object::TransfromFlags::Scaleable;
			setPropertyRow(transfromNum++, transformIdx, "Actual Size (in meters)", size, editable);
		}
		{
			auto editCallback = [&_object](const glm::vec3& _val) { _object.setRotation(_val); };
			const QVariant rotation = QVariant::fromValue(TransformVecUiWrapper{ _object.getRotation(), editCallback });

			const bool editable = _object.getTransformFlags() & jl::Object::TransfromFlags::Rotatable;
			setPropertyRow(transfromNum++, transformIdx, "Rotation", rotation, editable);
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

			const QString meshMaterialtemplate = "Mesh %1 Material";
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

void PropertiesWidget::refreshMaterialProperties(jl::Material& _material)
{
	static const std::map<std::string, std::string> k_materialNamesMap{
		{ "u_shininess",	"Shininnes" },
		{ "u_opacity",		"Opacity" },
		{ "u_matAmbient",	"Color" },
		{ "u_matDiffuse",	"Light Reflect Color" },
		{ "u_matSpecular",	"Light Blink Color" },
		{ "u_texture2D",	"Texture" }
	};

	const auto& properties = _material.getProperties();
	const int propertiesCount = static_cast<int>(properties.size());

	const QModelIndex rootIdx;

	for (int i = 0; i < propertiesCount; ++i)
	{
		auto itName = k_materialNamesMap.find(properties[i].name);
		ASSERT(itName != k_materialNamesMap.end());

		const std::string& name = itName != k_materialNamesMap.end() ? itName->second : properties[i].name;
		const QVariant value = std::visit(MaterialPropertyValueVisitor(_material, properties[i].name), properties[i].value);
		setPropertyRow(i, rootIdx, QString::fromStdString(name), value, true);
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
		onMaterialChanged(_topLeft, *std::get<jl::Material*>(m_activeEntity));
	}
}

//-----------------------------------------------------------------------------

void PropertiesWidget::onObjectChanged(const QModelIndex& _idx, ObjectWrapper& _object)
{
	if (_idx.data().canConvert<ModelUiWrapper>())
	{
		ModelUiWrapper modelWrapper = qvariant_cast<ModelUiWrapper>(_idx.data());
		_object.setModel(modelWrapper.value);

		refreshObjectSize();
		refreshMeshes(_object.getModel());
	}
}

//-----------------------------------------------------------------------------

void PropertiesWidget::onMaterialChanged(const QModelIndex& _idx, jl::Material& _material)
{
	if (_idx.data().canConvert<TextureUiWrapper>())
	{
		const auto& props = _material.getProperties();

		TextureUiWrapper textureWrapper = qvariant_cast<TextureUiWrapper>(_idx.data());
		_material.setProperty(props[_idx.row()].name, textureWrapper.value);

		const jl::Shader& shader =
			textureWrapper.value ?
			MaterialsManager::getInstance().getTextureShader() :
			MaterialsManager::getInstance().getColorShader();
		_material.setShader(shader);
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
