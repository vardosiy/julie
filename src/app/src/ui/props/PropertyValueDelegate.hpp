#pragma once

#include <QStyledItemDelegate>

class PropertyValueDelegate : public QStyledItemDelegate
{
	Q_OBJECT

public:
	explicit PropertyValueDelegate(QWidget* parent = nullptr);

	QWidget* createEditor(QWidget* _parent, const QStyleOptionViewItem& _option, const QModelIndex& _idx) const override;

	void setEditorData(QWidget* _editor, const QModelIndex& _idx) const override;
	void setModelData(QWidget* _editor, QAbstractItemModel* _model, const QModelIndex& _idx) const override;

	QString displayText(const QVariant& _value, const QLocale& _locale) const override;

private:
	template<typename TData, typename TEditor>
	void setWidgetData(const QVariant& _data, QWidget* _editor) const;
};
