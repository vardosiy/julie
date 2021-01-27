//#include "ui/entities/EntityDelegate.hpp"
//#include "ui/MetaTypes.hpp"
//
//#include "julie/Material.hpp"
//
//#include <QLineEdit>
//
////-----------------------------------------------------------------------------
//
//EntityDelegate::EntityDelegate(QWidget* _parent)
//	: QStyledItemDelegate(_parent)
//{
//}
//
////-----------------------------------------------------------------------------
//
//QWidget* EntityDelegate::createEditor(QWidget* _parent, const QStyleOptionViewItem& _option, const QModelIndex& _idx) const
//{
//	return new QLineEdit(_parent);
//}
//
////-----------------------------------------------------------------------------
//
//void EntityDelegate::setEditorData(QWidget* _editor, const QModelIndex& _idx) const
//{
//	const QString name = getEntityName(_idx.data());
//	QLineEdit* textEdit = qobject_cast<QLineEdit*>(_editor);
//
//	textEdit->setText(name);
//	textEdit->selectAll();
//}
//
////-----------------------------------------------------------------------------
//
//void EntityDelegate::setModelData(QWidget* _editor, QAbstractItemModel* _model, const QModelIndex& _idx) const
//{
//	const QLineEdit* textEdit = qobject_cast<QLineEdit*>(_editor);
//	std::string newName = textEdit->text().toStdString();
//
//	if (isModelHaveItemWithName(*_model, newName))
//	{
//		return;
//	}
//
//	runOnItem(_idx.data(), [newName = std::move(newName)](auto&& _wrapper)
//	{
//		_wrapper.value->setName(std::move(newName));
//	});
//}
//
////-----------------------------------------------------------------------------
//
//QString EntityDelegate::displayText(const QVariant& _value, const QLocale& _locale) const
//{
//	return getEntityName(_value);
//}
//
////-----------------------------------------------------------------------------
//
//QString EntityDelegate::getEntityName(const QVariant& _value)
//{
//	QString result;
//
//	runOnItem(_value, [&](auto&& _wrapper)
//	{
//		const std::string& name = _wrapper.value->getName();
//		result = name.empty() ? "<unnamed entity>" : name.c_str();
//	});
//
//	return result;
//}
//
////-----------------------------------------------------------------------------
//
//bool EntityDelegate::isModelHaveItemWithName(const QAbstractItemModel& _model, const std::string& _name)
//{
//	const int rowCount = _model.rowCount();
//	for (int i = 0; i < rowCount; ++i)
//	{
//		const QVariant data = _model.data(_model.index(i, 0));
//
//		bool found = false;
//		runOnItem(data, [&](auto&& _wrapper)
//		{
//			found = _wrapper.value->getName() == _name;
//		});
//
//		if (found)
//		{
//			return true;
//		}
//	}
//
//	return false;
//}
//
////-----------------------------------------------------------------------------
