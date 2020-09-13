#include "ui/PropertiesWidget.hpp"
#include "ui/UiUtils.hpp"
#include "ui_PropertiesWidget.h"

#include "ui/properties/MaterialPropertyValueVisitor.hpp"
#include "ui/properties/PropertyValueDelegate.hpp"
#include "ui/properties/PropertyTypes.hpp"

#include "data/ObjectWrapper.hpp"

#include "julie/managers/ResourceManager.hpp"
#include "julie/managers/MaterialsManager.hpp"
#include "julie/UniformType.hpp"
#include "julie/Model.hpp"
#include "julie/Material.hpp"

#include "utils/Utils.hpp"

#include <string>

//-----------------------------------------------------------------------------

struct GetPropertyTypeStrVisitor
{
	std::string_view operator() (float) const noexcept					{ return utils::toString(jl::UniformType::Float); }
	std::string_view operator() (jl::s32) const noexcept				{ return utils::toString(jl::UniformType::Int); }
	std::string_view operator() (const glm::vec2&) const noexcept		{ return utils::toString(jl::UniformType::Vec2); }
	std::string_view operator() (const glm::vec3&) const noexcept		{ return utils::toString(jl::UniformType::Vec3); }
	std::string_view operator() (const glm::vec4&) const noexcept		{ return utils::toString(jl::UniformType::Vec4); }
	std::string_view operator() (const jl::Texture*) const noexcept		{ return utils::toString(jl::UniformType::Texture2D); }
	std::string_view operator() (const jl::CubeTexture*) const noexcept	{ return utils::toString(jl::UniformType::CubeTexture); }
};

//-----------------------------------------------------------------------------

PropertiesWidget::PropertiesWidget(QWidget* parent)
	: QWidget(parent)
	, m_propertiesTableModel(0, 2, this)
	, m_activeEntity(nullptr)
{
	m_ui = std::make_unique<Ui::PropertiesWidget>();
	m_ui->setupUi(this);

	m_propertiesTableModel.setHeaderData(k_nameColIdx, Qt::Horizontal, "Property");
	m_propertiesTableModel.setHeaderData(k_valueColIdx, Qt::Horizontal, "Value");

	m_ui->treev_properties->setModel(&m_propertiesTableModel);
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
		m_propertiesTableModel.setRowCount(2); // model + transform

		const QModelIndex transformIdx = index(k_transformRowIdx, k_nameColIdx);
		m_propertiesTableModel.insertRows(0, k_transformsNum, transformIdx);
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
	else
	{
		reset();
		m_propertiesTableModel.setRowCount(2); // shader + uniforms
	}


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

	const QModelIndex transformIdx = index(k_transformRowIdx, k_nameColIdx);

	auto editCallback = [obj](const glm::vec3& _val) { obj->setPosition(_val); };
	const QVariant pos = QVariant::fromValue(TransformVecUiWrapper{ obj->getPosition(), editCallback });
	setCellValue(index(0, k_valueColIdx, transformIdx), pos, true);

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

	const QModelIndex transformIdx = index(k_transformRowIdx, k_nameColIdx);

	auto editCallback = [obj](const glm::vec3& _val) { obj->setScale(_val); };
	const QVariant size = QVariant::fromValue(TransformVecUiWrapper{ obj->getScale(), editCallback });
	setCellValue(index(1, k_valueColIdx, transformIdx), size, true);

	m_activeEntity = obj;
}

//-----------------------------------------------------------------------------

void PropertiesWidget::refreshObjectProperties(ObjectWrapper& _object)
{
	int propNum = 0;
	{
		jl::Model* model = _object.getModel();
		const QVariant value = QVariant::fromValue(ModelUiWrapper{ findSourceFile(model), model });
		setPropertyRow(propNum, "Model", value);

		refreshMeshes(model, index(propNum, k_nameColIdx));

		++propNum;
	}
	{
		const QModelIndex transformIdx = index(propNum, k_nameColIdx);
		setHeaderRow(propNum, "Transform");

		int transfromNum = 0;
		{
			auto editCallback = [&_object](const glm::vec3& _val) { _object.setPosition(_val); };
			const QVariant pos = QVariant::fromValue(TransformVecUiWrapper{ _object.getPosition(), editCallback });
			setPropertyRow(transfromNum++, "Position", pos, transformIdx);
		}
		{
			auto editCallback = [&_object](const glm::vec3& _val) { _object.setScale(_val); };
			const QVariant size = QVariant::fromValue(TransformVecUiWrapper{ _object.getScale(), editCallback });
			setPropertyRow(transfromNum++, "Scale", size, transformIdx);
		}
		{
			auto editCallback = [&_object](const glm::vec3& _val) { _object.setRotation(_val); };
			const QVariant rotation = QVariant::fromValue(TransformVecUiWrapper{ _object.getRotation(), editCallback });
			setPropertyRow(transfromNum++, "Rotation", rotation, transformIdx);
		}
		ASSERT(transfromNum == k_transformsNum);

		++propNum;
	}
	ASSERT(propNum == 2);
}

//-----------------------------------------------------------------------------

void PropertiesWidget::refreshMeshes(jl::Model* _model, const QModelIndex& _parent)
{
	const int meshesCount = _model ? static_cast<int>(_model->getMeshesCount()) : 0;
	setChildRowCount(meshesCount, _parent);

	if (meshesCount > 0)
	{
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
			setPropertyRow(i, meshMaterialtemplate.arg(i + 1), value, _parent);
		}
	}
}

//-----------------------------------------------------------------------------

void PropertiesWidget::refreshMaterialProperties(jl::Material& _material)
{
	int propNum = 0;
	{
		const jl::Shader* shader = _material.getShader();
		const QVariant value = QVariant::fromValue(ShaderUiWrapper{ findSourceFile(shader), shader });
		setPropertyRow(propNum++, "Shader", value);
	}
	{
		setHeaderRow(propNum, "Uniforms");
		refreshUniforms(_material, index(propNum, k_nameColIdx));
		++propNum;
	}
	ASSERT(propNum == 2);
}

//-----------------------------------------------------------------------------

void PropertiesWidget::refreshUniforms(jl::Material& _material, const QModelIndex& _parent)
{
	const auto& properties = _material.getProperties();
	const int propertiesCount = static_cast<int>(properties.size());

	setChildRowCount(propertiesCount, _parent);

	for (int i = 0; i < propertiesCount; ++i)
	{
		const jl::Material::Property& prop = properties[i];

		const std::string name = fmt::format("{} [{}]", prop.name, std::visit(GetPropertyTypeStrVisitor{}, prop.value));
		const QVariant value = std::visit(MaterialPropertyValueVisitor(_material, prop.name), prop.value);
		setPropertyRow(i, QString::fromStdString(name), value, _parent);
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
		refreshMeshes(modelWrapper.value, index(_idx.row(), k_nameColIdx));
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

		//const jl::Shader* shader =
		//	textureWrapper.value ?
		//	MaterialsManager::getInstance().getTextureShader() :
		//	MaterialsManager::getInstance().getColorShader();

		//_material.setShader(shader);
	}
}

//-----------------------------------------------------------------------------

void PropertiesWidget::setChildRowCount(int _rows, const QModelIndex& _parent)
{
	m_propertiesTableModel.removeRows(0, m_propertiesTableModel.rowCount(_parent), _parent);
	m_propertiesTableModel.removeColumns(0, m_propertiesTableModel.columnCount(_parent), _parent);

	m_propertiesTableModel.insertRows(0, _rows, _parent);
	m_propertiesTableModel.insertColumns(0, 2, _parent);
}

//-----------------------------------------------------------------------------

void PropertiesWidget::setHeaderRow(int _row, const QString& _name, const QModelIndex& _parent)
{
	setCellValue(index(_row, k_nameColIdx, _parent), _name, false);
	setCellValue(index(_row, k_valueColIdx, _parent), "", false);
}

//-----------------------------------------------------------------------------

void PropertiesWidget::setPropertyRow(int _row, const QString& _name, const QVariant& _value, const QModelIndex& _parent)
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
		item->setFlags(
			_enableEditing ?
			item->flags() | Qt::ItemIsEditable :
			item->flags() & ~Qt::ItemIsEditable
		);
	}
}

//-----------------------------------------------------------------------------

QModelIndex PropertiesWidget::index(int _row, int _col, const QModelIndex& _parent)
{
	return m_propertiesTableModel.index(_row, _col, _parent);
}

//-----------------------------------------------------------------------------
