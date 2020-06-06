#include "ui/PropertyValueDelegate.hpp"
#include "ui/PropertyTypes.hpp"
#include "ui/EditableResourcePathWidget.hpp"

#include "managers/ResourceManager.hpp"
#include "managers/MaterialsManager.hpp"

#include <QComboBox>

//-----------------------------------------------------------------------------

PropertyValueDelegate::PropertyValueDelegate(QWidget* _parent)
	: QStyledItemDelegate(_parent)
{
}

//-----------------------------------------------------------------------------

QWidget* PropertyValueDelegate::createEditor(QWidget* _parent, const QStyleOptionViewItem& _option, const QModelIndex& _idx) const
{
	if (_idx.data().canConvert<ModelUiWrapper>())
	{
		return new EditableResourcePathWidget(_parent);
	}
	else if (_idx.data().canConvert<MaterialUiWrapper>())
	{
		QComboBox* materialsBox = new QComboBox(_parent);
		MaterialsManager::getInstance().forEachMaterial([materialsBox](const std::string& _name, const jl::Material& _material)
		{
			materialsBox->addItem(QString::fromStdString(_name));
		});
		return materialsBox;
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

		QString modelPath;
		if (modelWrapper.model)
		{
			modelPath = ResourceManager::getInstance().findSourceFile(*modelWrapper.model).c_str();
		}
		pathWdg->setPath(modelPath);
	}
	else if (_idx.data().canConvert<MaterialUiWrapper>())
	{
		MaterialUiWrapper materialWrapper = qvariant_cast<MaterialUiWrapper>(_idx.data());
		QComboBox* materialsBox = qobject_cast<QComboBox*>(_editor);

		QString materialName;
		if (materialWrapper.material)
		{
			materialName = MaterialsManager::getInstance().findMaterialName(*materialWrapper.material).c_str();
		}
		materialsBox->setCurrentText(materialName);
	}
	else
	{
		QStyledItemDelegate::setEditorData(_editor, _idx);
	}
}

//-----------------------------------------------------------------------------

void PropertyValueDelegate::setModelData(QWidget* _editor, QAbstractItemModel* _model, const QModelIndex& _idx) const
{
	if (_idx.data().canConvert<ModelUiWrapper>())
	{
		const EditableResourcePathWidget* pathWdg = qobject_cast<EditableResourcePathWidget*>(_editor);
		const QString& modelPath = pathWdg->getPath();

		ModelUiWrapper modelWrapper;
		if (!modelPath.isEmpty())
		{
			modelWrapper.model = ResourceManager::getInstance().loadModel(modelPath.toStdString());
		}
		_model->setData(_idx, QVariant::fromValue(modelWrapper));
	}
	else if (_idx.data().canConvert<MaterialUiWrapper>())
	{
		const QComboBox* materialsBox = qobject_cast<QComboBox*>(_editor);

		MaterialUiWrapper materialWrapper;
		if (materialsBox->currentIndex() != -1)
		{
			const std::string materialName = materialsBox->currentText().toStdString();
			materialWrapper.material = MaterialsManager::getInstance().findMaterial(materialName);
		}
		_model->setData(_idx, QVariant::fromValue(materialWrapper));
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
		if (modelWrapper.model)
		{
			result = ResourceManager::getInstance().findSourceFile(*modelWrapper.model).c_str();
		}
	}
	else if (_value.canConvert<MaterialUiWrapper>())
	{
		const MaterialUiWrapper materialWrapper = qvariant_cast<MaterialUiWrapper>(_value);
		if (materialWrapper.material)
		{
			result = MaterialsManager::getInstance().findMaterialName(*materialWrapper.material).c_str();
		}
	}
	else
	{
		result = QStyledItemDelegate::displayText(_value, _locale);
	}

	return result;
}

//-----------------------------------------------------------------------------
