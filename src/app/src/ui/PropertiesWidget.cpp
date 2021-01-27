#include "ui/PropertiesWidget.hpp"
#include "ui/UiUtils.hpp"
#include "ui_PropertiesWidget.h"

#include "ui/properties/MaterialPropertyValueVisitor.hpp"
#include "ui/properties/PropertyValueDelegate.hpp"
#include "ui/MetaTypes.hpp"

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
	, m_activeItem(nullptr)
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

void PropertiesWidget::setActiveItem(jl::EntityRef _entity)
{
	if (std::holds_alternative<jl::EntityRef>(m_activeItem))
	{
		if (std::get<jl::EntityRef>(m_activeItem) == _entity)
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

	m_activeItem = nullptr;
	refreshEntityProperties(_entity);
	m_activeItem = _entity;
}

//-----------------------------------------------------------------------------

void PropertiesWidget::setActiveItem(jl::Material& _material)
{
	if (std::holds_alternative<jl::Material*>(m_activeItem))
	{
		if (std::get<jl::Material*>(m_activeItem) == &_material)
		{
			return;
		}
	}
	else
	{
		reset();
		m_propertiesTableModel.setRowCount(2); // shader + uniforms
	}


	m_activeItem = nullptr;
	refreshMaterialProperties(_material);
	m_activeItem = &_material;
}

//-----------------------------------------------------------------------------

void PropertiesWidget::reset()
{
	m_activeItem = nullptr;
	m_propertiesTableModel.setRowCount(0);
}

//-----------------------------------------------------------------------------

void PropertiesWidget::refreshEntityPos()
{
	//if (!std::holds_alternative<jl::EntityRef>(m_activeItem))
	//{
	//	return;
	//}

	//jl::EntityRef entity = std::get<jl::EntityRef>(m_activeItem);
	//m_activeItem = nullptr;

	//const QModelIndex transformIdx = index(k_transformRowIdx, k_nameColIdx);

	//auto editCallback = [entity](const glm::vec3& _val) { obj->setPosition(_val); };
	//const QVariant pos = QVariant::fromValue(TransformVecUiWrapper{ obj->getPosition(), editCallback });
	//setCellValue(index(0, k_valueColIdx, transformIdx), pos, true);

	//m_activeItem = obj;
}

//-----------------------------------------------------------------------------

void PropertiesWidget::refreshEntitySize()
{
	//if (!std::holds_alternative<jl::Object*>(m_activeEntity))
	//{
	//	return;
	//}

	//jl::Object* obj = std::get<jl::Object*>(m_activeEntity);
	//m_activeEntity = nullptr;

	//const QModelIndex transformIdx = index(k_transformRowIdx, k_nameColIdx);

	//auto editCallback = [obj](const glm::vec3& _val) { obj->setScale(_val); };
	//const QVariant size = QVariant::fromValue(TransformVecUiWrapper{ obj->getScale(), editCallback });
	//setCellValue(index(1, k_valueColIdx, transformIdx), size, true);

	//m_activeEntity = obj;
}

//-----------------------------------------------------------------------------

void PropertiesWidget::refreshEntityProperties(jl::EntityRef _entity)
{
	int propNum = 0;

	const ModelComponent* modelCmpnt = _entity.getComponent<ModelComponent>();
	if (modelCmpnt)
	{
		setHeaderRow(propNum, "ModelComponent");
		QModelIndex modelCmpntIdx = index(propNum, k_nameColIdx);

		int prop = 0;

		std::string modelPath = jl::ResourceManager::getInstance().findSourceFile(*modelCmpnt->model);
		setPropertyRow(prop, "Model Path", QString::fromStdString(modelPath), modelCmpntIdx);
		++prop;

		setHeaderRow(prop, "Mesh Materials", modelCmpntIdx);
		refreshMeshes(modelCmpnt->model, index(prop, k_nameColIdx, modelCmpntIdx));
		++propNum;
	}

	const TransformComponent* transformCmpnt = _entity.getComponent<TransformComponent>();
	if (transformCmpnt)
	{
		setHeaderRow(propNum, "TransformComponent");
		const QModelIndex transformCmpntIdx = index(propNum, k_nameColIdx);

		int transformNum = 0;
		{
			auto editCallback = [_entity](const glm::vec3& _val) mutable
			{
				_entity.getComponent<TransformComponent>()->pos = _val;
			};

			const QVariant pos = QVariant::fromValue(TransformVecUiWrapper{ transformCmpnt->pos, editCallback });
			setPropertyRow(transformNum++, "Position", pos, transformCmpntIdx);
		}
		{
			auto editCallback = [_entity](const glm::vec3& _val) mutable
			{
				_entity.getComponent<TransformComponent>()->scale = _val;
			};

			const QVariant scale = QVariant::fromValue(TransformVecUiWrapper{ transformCmpnt->scale, editCallback });
			setPropertyRow(transformNum++, "Scale", scale, transformCmpntIdx);
		}
		{
			auto editCallback = [_entity](const glm::vec3& _val) mutable
			{
				_entity.getComponent<TransformComponent>()->rotation = _val;
			};

			const QVariant rotation = QVariant::fromValue(TransformVecUiWrapper{ transformCmpnt->rotation, editCallback });
			setPropertyRow(transformNum++, "Rotation", rotation, transformCmpntIdx);
		}
		ASSERT(transformNum == k_transformsNum);

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
		const QString meshMaterialTemplate = "Mesh %1 Material";
		for (int i = 0; i < meshesCount; ++i)
		{
			jl::Mesh& mesh = _model->getMesh(i);

			const QVariant value = QVariant::fromValue(MaterialUiWrapper{ mesh.getMaterial() });
			setPropertyRow(i, meshMaterialTemplate.arg(i + 1), value, _parent);
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
	if (std::holds_alternative<jl::EntityRef>(m_activeItem))
	{
		onEntityChanged(_topLeft, std::get<jl::EntityRef>(m_activeItem));
	}
	else if (std::holds_alternative<jl::Material*>(m_activeItem))
	{
		onMaterialChanged(_topLeft, *std::get<jl::Material*>(m_activeItem));
	}
}

//-----------------------------------------------------------------------------

void PropertiesWidget::onEntityChanged(const QModelIndex& _idx, jl::EntityRef _entity)
{
	//if (_idx.data().canConvert<ModelUiWrapper>())
	//{
	//	ModelUiWrapper modelWrapper = qvariant_cast<ModelUiWrapper>(_idx.data());
	//	_object.setModel(modelWrapper.value);

	//	refreshObjectSize();
	//	refreshMeshes(modelWrapper.value, index(_idx.row(), k_nameColIdx));
	//}
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
