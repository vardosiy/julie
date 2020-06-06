#include "ui/PropertyValueDelegate.hpp"
#include "ui/PropertyTypes.hpp"
#include "ui/EditableResourcePathWidget.hpp"

#include "managers/ResourceManager.hpp"

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
	return QStyledItemDelegate::createEditor(_parent, _option, _idx);
}

//-----------------------------------------------------------------------------

void PropertyValueDelegate::setEditorData(QWidget* _editor, const QModelIndex& _idx) const
{
	if (_idx.data().canConvert<ModelUiWrapper>())
	{
		ModelUiWrapper modelWrapper = qvariant_cast<ModelUiWrapper>(_idx.data());
		EditableResourcePathWidget* wdg = qobject_cast<EditableResourcePathWidget*>(_editor);

		QString modelPath;
		if (modelWrapper.model)
		{
			modelPath = ResourceManager::getInstance().findSourceFile(*modelWrapper.model).c_str();
		}

		wdg->setPath(modelPath);
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
		EditableResourcePathWidget* wdg = qobject_cast<EditableResourcePathWidget*>(_editor);
		const QString& modelPath = wdg->getPath();

		ModelUiWrapper modelWrapper;
		if (!modelPath.isEmpty())
		{
			modelWrapper.model = ResourceManager::getInstance().loadModel(modelPath.toStdString());
		}
		_model->setData(_idx, QVariant::fromValue(modelWrapper));
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
	else
	{
		result = QStyledItemDelegate::displayText(_value, _locale);
	}

	return result;
}

//-----------------------------------------------------------------------------
