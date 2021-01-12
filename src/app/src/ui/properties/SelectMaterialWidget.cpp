#include "ui/properties/SelectMaterialWidget.hpp"

#include "julie/managers/MaterialsManager.hpp"
#include "julie/Mesh.hpp"

//-----------------------------------------------------------------------------

SelectMaterialWidget::SelectMaterialWidget(QWidget* _parent)
	: QComboBox(_parent)
{
	//MaterialsManager::getInstance().forEachMaterial([this](const std::string& _name, const jl::Material&)
	//{
	//	addItem(QString::fromStdString(_name));
	//});

	connect(this, qOverload<const QString&>(&QComboBox::currentIndexChanged), this, &SelectMaterialWidget::onMaterialChanged);
}

//-----------------------------------------------------------------------------

const MaterialUiWrapper& SelectMaterialWidget::getValue() const noexcept
{
	return m_value;
}

//-----------------------------------------------------------------------------

void SelectMaterialWidget::setValue(const MaterialUiWrapper& _value) noexcept
{
	m_value = _value;
	//setCurrentText(m_value.materialName);
}

//-----------------------------------------------------------------------------

void SelectMaterialWidget::onMaterialChanged(const QString& _materialName)
{
	//m_value.materialName = _materialName;

	jl::Material* material = MaterialsManager::getInstance().findMaterial(_materialName.toStdString());
	//m_value.mesh->setMaterial(material);
}

//-----------------------------------------------------------------------------
