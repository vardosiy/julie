#pragma once

#include <QWidget>
#include <QVector4D>

namespace Ui {
class EditableVec4Widget;
}

class EditableVec4Widget : public QWidget
{
	Q_OBJECT

public:
	explicit EditableVec4Widget(QWidget* _parent = nullptr);

	const QVector4D& getValue() const noexcept;
	void setValue(const QVector4D& _value) noexcept;

private slots:
	void onValueChanged();

private:
	std::unique_ptr<Ui::EditableVec4Widget> m_ui;

	QVector4D m_value;
};
