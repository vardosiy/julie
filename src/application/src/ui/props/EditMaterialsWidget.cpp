#include "ui/props/EditMaterialsWidget.hpp"
#include "ui_EditableVec4Widget.h"

#include "renderer/managers/MaterialsManager.hpp"

//-----------------------------------------------------------------------------

EditMaterialsWidget::EditMaterialsWidget(QWidget* _parent)
	: QComboBox(_parent)
{
	MaterialsManager::getInstance().forEachMaterial([this](const std::string& _name, const jl::Material&)
	{
		addItem(QString::fromStdString(_name));
	});
}

//-----------------------------------------------------------------------------

MaterialUiWrapper EditMaterialsWidget::getData() const noexcept
{
	MaterialUiWrapper result;
	if (currentIndex() != -1)
	{
		const std::string materialName = currentText().toStdString();
		result.value = MaterialsManager::getInstance().findMaterial(materialName);
	}
	return result;
}

//-----------------------------------------------------------------------------

void EditMaterialsWidget::setData(MaterialUiWrapper _data) noexcept
{
	QString materialName;
	if (_data.value)
	{
		materialName = MaterialsManager::getInstance().findMaterialName(*_data.value).c_str();
	}
	setCurrentText(materialName);
}

//-----------------------------------------------------------------------------
