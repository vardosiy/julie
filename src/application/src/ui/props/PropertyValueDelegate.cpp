#include "ui/props/PropertyValueDelegate.hpp"
#include "ui/props/PropertyTypes.hpp"
#include "ui/props/EditableResourcePathWidget.hpp"
#include "ui/props/EditableVec3Widget.hpp"
#include "ui/props/EditableVec4Widget.hpp"
#include "ui/props/EditMaterialsWidget.hpp"

#include "ui/UiUtils.hpp"

#include "renderer/managers/ResourceManager.hpp"
#include "renderer/managers/MaterialsManager.hpp"

#include <QDoubleSpinBox>

//-----------------------------------------------------------------------------

PropertyValueDelegate::PropertyValueDelegate(QWidget* _parent)
	: QStyledItemDelegate(_parent)
{
}

//-----------------------------------------------------------------------------

QWidget* PropertyValueDelegate::createEditor(QWidget* _parent, const QStyleOptionViewItem& _option, const QModelIndex& _idx) const
{
	if (_idx.data().canConvert<ModelUiWrapper>() || _idx.data().canConvert<TextureUiWrapper>())
	{
		return new EditableResourcePathWidget(_parent);
	}
	else if (_idx.data().canConvert<MaterialUiWrapper>())
	{
		return new EditMaterialsWidget(_parent);
	}
	else if (_idx.data().canConvert<float>())
	{
		QDoubleSpinBox* spinBox = new QDoubleSpinBox(_parent);
		spinBox->setRange(k_floatUiMin, k_floatUiMax);
		spinBox->setSingleStep(k_floatUiStep);
		spinBox->setDecimals(k_floatDecimals);
		return spinBox;
	}
	else if (_idx.data().canConvert<TransformVecUiWrapper>() || _idx.data().canConvert<ColorUiWrapper>())
	{
		return new EditableVec3Widget(_parent);
	}

	return QStyledItemDelegate::createEditor(_parent, _option, _idx);
}

//-----------------------------------------------------------------------------

void PropertyValueDelegate::setEditorData(QWidget* _editor, const QModelIndex& _idx) const
{
	if (_idx.data().canConvert<ModelUiWrapper>())
	{
		ModelUiWrapper modelWrapper = qvariant_cast<ModelUiWrapper>(_idx.data());
		EditableResourcePathWidget* pathWdg = qobject_cast<EditableResourcePathWidget*>(_editor);
		pathWdg->setValue(modelWrapper);
	}
	else if (_idx.data().canConvert<TextureUiWrapper>())
	{
		TextureUiWrapper textureWrapper = qvariant_cast<TextureUiWrapper>(_idx.data());
		EditableResourcePathWidget* pathWdg = qobject_cast<EditableResourcePathWidget*>(_editor);
		pathWdg->setValue(textureWrapper);
	}
	else if (_idx.data().canConvert<MaterialUiWrapper>())
	{
		MaterialUiWrapper materialWrapper = qvariant_cast<MaterialUiWrapper>(_idx.data());
		EditMaterialsWidget* materialsBox = qobject_cast<EditMaterialsWidget*>(_editor);
		materialsBox->setData(materialWrapper);
	}
	else if (_idx.data().canConvert<float>())
	{
		QDoubleSpinBox* spinBox = qobject_cast<QDoubleSpinBox*>(_editor);
		spinBox->setValue(_idx.data().toDouble());
	}
	else if (_idx.data().canConvert<TransformVecUiWrapper>())
	{
		TransformVecUiWrapper wrapper = qvariant_cast<TransformVecUiWrapper>(_idx.data());
		EditableVec3Widget* widget = qobject_cast<EditableVec3Widget*>(_editor);
		widget->setValue(wrapper);
	}
	else if (_idx.data().canConvert<ColorUiWrapper>())
	{
		ColorUiWrapper wrapper = qvariant_cast<ColorUiWrapper>(_idx.data());
		EditableVec3Widget* widget = qobject_cast<EditableVec3Widget*>(_editor);
		widget->setValue(wrapper);
	}
	else
	{
		QStyledItemDelegate::setEditorData(_editor, _idx);
	}
}

//-----------------------------------------------------------------------------

void PropertyValueDelegate::setModelData(QWidget* _editor, QAbstractItemModel* _model, const QModelIndex& _idx) const
{
	if (_idx.data().canConvert<ModelUiWrapper>() || _idx.data().canConvert<TextureUiWrapper>())
	{
		const EditableResourcePathWidget* pathWdg = qobject_cast<EditableResourcePathWidget*>(_editor);
		_model->setData(_idx, pathWdg->getValue());
	}
	else if (_idx.data().canConvert<MaterialUiWrapper>())
	{
		const EditMaterialsWidget* materialsBox = qobject_cast<EditMaterialsWidget*>(_editor);
		_model->setData(_idx, QVariant::fromValue(materialsBox->getData()));
	}
	else if (_idx.data().canConvert<float>())
	{
		const QDoubleSpinBox* spinBox = qobject_cast<QDoubleSpinBox*>(_editor);
		_model->setData(_idx, spinBox->value());
	}
	else if (_idx.data().canConvert<TransformVecUiWrapper>() || _idx.data().canConvert<ColorUiWrapper>())
	{
		EditableVec3Widget* widget = qobject_cast<EditableVec3Widget*>(_editor);
		_model->setData(_idx, widget->getValue());
	}
	else
	{
		QStyledItemDelegate::setModelData(_editor, _model, _idx);
	}
}

//-----------------------------------------------------------------------------

QString PropertyValueDelegate::displayText(const QVariant& _value, const QLocale& _locale) const
{
	QString result;

	if (_value.canConvert<ModelUiWrapper>())
	{
		const ModelUiWrapper modelWrapper = qvariant_cast<ModelUiWrapper>(_value);
		if (modelWrapper.value)
		{
			result = ResourceManager::getInstance().findSourceFile(*modelWrapper.value).c_str();
		}
	}
	else if (_value.canConvert<TextureUiWrapper>())
	{
		const TextureUiWrapper textureWrapper = qvariant_cast<TextureUiWrapper>(_value);
		if (textureWrapper.value)
		{
			result = ResourceManager::getInstance().findSourceFile(*textureWrapper.value).c_str();
		}
	}
	else if (_value.canConvert<MaterialUiWrapper>())
	{
		const MaterialUiWrapper materialWrapper = qvariant_cast<MaterialUiWrapper>(_value);
		result = materialWrapper.materialName;
	}
	else if (_value.canConvert<TransformVecUiWrapper>())
	{
		TransformVecUiWrapper wrapper = qvariant_cast<TransformVecUiWrapper>(_value);
		result = vecToString(wrapper.value);
	}
	else if (_value.canConvert<ColorUiWrapper>())
	{
		ColorUiWrapper wrapper = qvariant_cast<ColorUiWrapper>(_value);
		result = vecToString(wrapper.value);
	}
	else
	{
		result = QStyledItemDelegate::displayText(_value, _locale);
	}

	return result;
}

//-----------------------------------------------------------------------------
