#include "ui/props/EditMaterialsWidget.hpp"
#include "ui_EditableVec4Widget.h"

#include "julie/managers/MaterialsManager.hpp"
#include "julie/Mesh.hpp"

//-----------------------------------------------------------------------------

EditMaterialsWidget::EditMaterialsWidget(QWidget* _parent)
	: QComboBox(_parent)
{
	MaterialsManager::getInstance().forEachMaterial([this](const std::string& _name, const jl::Material&)
	{
		addItem(QString::fromStdString(_name));
	});

	connect(this, qOverload<const QString&>(&QComboBox::currentIndexChanged), this, &EditMaterialsWidget::onMaterialChanged);
}

//-----------------------------------------------------------------------------

const MaterialUiWrapper& EditMaterialsWidget::getValue() const noexcept
{
	return m_data;
}

//-----------------------------------------------------------------------------

void EditMaterialsWidget::setValue(const MaterialUiWrapper& _data) noexcept
{
	m_data = _data;
	setCurrentText(m_data.materialName);
}

//-----------------------------------------------------------------------------

void EditMaterialsWidget::onMaterialChanged(const QString& _materialName)
{
	m_data.materialName = _materialName;

	const jl::Material* material = MaterialsManager::getInstance().findMaterial(_materialName.toStdString());
	m_data.mesh->setMaterial(material);
}

//-----------------------------------------------------------------------------
