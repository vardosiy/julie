#pragma once

#include "ui/MetaTypes.hpp"
#include "utils/Assert.hpp"

#include <QStyledItemDelegate>

class EntityDelegate : public QStyledItemDelegate
{
	Q_OBJECT

public:
	explicit EntityDelegate(QWidget* _parent = nullptr);

	QWidget* createEditor(QWidget* _parent, const QStyleOptionViewItem& _option, const QModelIndex& _idx) const override;

	void setEditorData(QWidget* _editor, const QModelIndex& _idx) const override;
	void setModelData(QWidget* _editor, QAbstractItemModel* _model, const QModelIndex& _idx) const override;

	QString displayText(const QVariant& _value, const QLocale& _locale) const override;

private:
	template<typename T>
	static void runOnItem(const QVariant& _data, T&& _callback);

	static QString getEntityName(const QVariant& _value);

	static bool isModelHaveItemWithName(const QAbstractItemModel& _model, const std::string& _name);
};

template<typename T>
inline void EntityDelegate::runOnItem(const QVariant& _data, T&& _callback)
{
	ASSERT(_data.canConvert<ObjectUiWrapper>() || _data.canConvert<MaterialUiWrapper>());
	if (_data.canConvert<ObjectUiWrapper>())
	{
		const ObjectUiWrapper wrapper = qvariant_cast<ObjectUiWrapper>(_data);
		_callback(wrapper);
	}
	else if (_data.canConvert<MaterialUiWrapper>())
	{
		const MaterialUiWrapper wrapper = qvariant_cast<MaterialUiWrapper>(_data);
		_callback(wrapper);
	}
}
