#include "ui/properties/PropertyValueDelegate.hpp"
#include "ui/properties/EditableResourcePathWidget.hpp"
#include "ui/properties/EditableVec3Widget.hpp"
#include "ui/properties/SelectMaterialWidget.hpp"

#include "ui/MetaTypes.hpp"
#include "ui/UiUtils.hpp"

#include "julie/Material.hpp"

#include <QDoubleSpinBox>

//-----------------------------------------------------------------------------

PropertyValueDelegate::PropertyValueDelegate(QWidget* _parent)
	: QStyledItemDelegate(_parent)
{
}

//-----------------------------------------------------------------------------

QWidget* PropertyValueDelegate::createEditor(QWidget* _parent, const QStyleOptionViewItem& _option, const QModelIndex& _idx) const
{
	if (_idx.data().canConvert<ModelUiWrapper>() ||
		_idx.data().canConvert<TextureUiWrapper>() ||
		_idx.data().canConvert<ShaderUiWrapper>())
	{
		return new EditableResourcePathWidget(_parent);
	}
	else if (_idx.data().canConvert<TransformVecUiWrapper>() || _idx.data().canConvert<ColorUiWrapper>())
	{
		return new EditableVec3Widget(_parent);
	}
	else if (_idx.data().canConvert<MaterialUiWrapper>())
	{
		return new SelectMaterialWidget(_parent);
	}
	else if (_idx.data().canConvert<FloatValUiWrapper>())
	{
		QDoubleSpinBox* spinBox = new QDoubleSpinBox(_parent);
		spinBox->setRange(k_floatUiMin, k_floatUiMax);
		spinBox->setSingleStep(k_floatUiStep);
		spinBox->setDecimals(k_floatDecimals);
		return spinBox;
	}

	return QStyledItemDelegate::createEditor(_parent, _option, _idx);
}

//-----------------------------------------------------------------------------

void PropertyValueDelegate::setEditorData(QWidget* _editor, const QModelIndex& _idx) const
{
	if (_idx.data().canConvert<ModelUiWrapper>())
	{
		setWidgetData<ModelUiWrapper, EditableResourcePathWidget>(_idx.data(), _editor);
	}
	else if (_idx.data().canConvert<TextureUiWrapper>())
	{
		setWidgetData<TextureUiWrapper, EditableResourcePathWidget>(_idx.data(), _editor);
	}
	else if (_idx.data().canConvert<ShaderUiWrapper>())
	{
		setWidgetData<ShaderUiWrapper, EditableResourcePathWidget>(_idx.data(), _editor);
	}
	else if (_idx.data().canConvert<TransformVecUiWrapper>())
	{
		setWidgetData<TransformVecUiWrapper, EditableVec3Widget>(_idx.data(), _editor);
	}
	else if (_idx.data().canConvert<ColorUiWrapper>())
	{
		setWidgetData<ColorUiWrapper, EditableVec3Widget>(_idx.data(), _editor);
	}
	else if (_idx.data().canConvert<MaterialUiWrapper>())
	{
		setWidgetData<MaterialUiWrapper, SelectMaterialWidget>(_idx.data(), _editor);
	}
	else if (_idx.data().canConvert<FloatValUiWrapper>())
	{
		FloatValUiWrapper floatWrapper = qvariant_cast<FloatValUiWrapper>(_idx.data());
		QDoubleSpinBox* spinBox = qobject_cast<QDoubleSpinBox*>(_editor);
		spinBox->setValue(floatWrapper.value);
		connect(spinBox, qOverload<double>(&QDoubleSpinBox::valueChanged), floatWrapper.editCallback);
	}
	else
	{
		QStyledItemDelegate::setEditorData(_editor, _idx);
	}
}

//-----------------------------------------------------------------------------

void PropertyValueDelegate::setModelData(QWidget* _editor, QAbstractItemModel* _model, const QModelIndex& _idx) const
{
	if (_idx.data().canConvert<ModelUiWrapper>() ||
		_idx.data().canConvert<TextureUiWrapper>() ||
		_idx.data().canConvert<ShaderUiWrapper>())
	{
		const EditableResourcePathWidget* pathWdg = qobject_cast<EditableResourcePathWidget*>(_editor);
		_model->setData(_idx, pathWdg->getValue());
	}
	else if (_idx.data().canConvert<TransformVecUiWrapper>() || _idx.data().canConvert<ColorUiWrapper>())
	{
		EditableVec3Widget* widget = qobject_cast<EditableVec3Widget*>(_editor);
		_model->setData(_idx, widget->getValue());
	}
	else if (_idx.data().canConvert<MaterialUiWrapper>())
	{
		const SelectMaterialWidget* materialsBox = qobject_cast<SelectMaterialWidget*>(_editor);
		_model->setData(_idx, QVariant::fromValue(materialsBox->getValue()));
	}
	else if (_idx.data().canConvert<FloatValUiWrapper>())
	{
		const QDoubleSpinBox* spinBox = qobject_cast<QDoubleSpinBox*>(_editor);
		FloatValUiWrapper floatWrapper = qvariant_cast<FloatValUiWrapper>(_idx.data());
		floatWrapper.value = static_cast<float>(spinBox->value());
		_model->setData(_idx, QVariant::fromValue(floatWrapper));
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
		result = modelWrapper.filePath;
	}
	else if (_value.canConvert<TextureUiWrapper>())
	{
		const TextureUiWrapper textureWrapper = qvariant_cast<TextureUiWrapper>(_value);
		result = textureWrapper.filePath;
	}
	else if (_value.canConvert<ShaderUiWrapper>())
	{
		const ShaderUiWrapper shaderWrapper = qvariant_cast<ShaderUiWrapper>(_value);
		result = shaderWrapper.filePath;
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
	else if (_value.canConvert<MaterialUiWrapper>())
	{
		const MaterialUiWrapper materialWrapper = qvariant_cast<MaterialUiWrapper>(_value);
		result = materialWrapper.material->getName().c_str();
	}
	else if (_value.canConvert<FloatValUiWrapper>())
	{
		const FloatValUiWrapper floatWrapper = qvariant_cast<FloatValUiWrapper>(_value);
		result = QStyledItemDelegate::displayText(floatWrapper.value, _locale);
	}
	else
	{
		result = QStyledItemDelegate::displayText(_value, _locale);
	}

	return result;
}

//-----------------------------------------------------------------------------

template<typename TData, typename TEditor>
void PropertyValueDelegate::setWidgetData(const QVariant& _data, QWidget* _editor) const
{
	TData data = qvariant_cast<TData>(_data);
	TEditor* editorWdg = qobject_cast<TEditor*>(_editor);
	editorWdg->setValue(data);
}

//-----------------------------------------------------------------------------
