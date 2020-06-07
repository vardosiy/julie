#pragma once

#include <QWidget>
#include <QVector3D>

namespace Ui {
class EditableVec3Widget;
}

class EditableVec3Widget : public QWidget
{
	Q_OBJECT

public:
	explicit EditableVec3Widget(QWidget* _parent = nullptr);

	QVector3D getValue() const noexcept;
	void setValue(const QVector3D& _value) noexcept;

private slots:
	void onValueChanged();

private:
	std::unique_ptr<Ui::EditableVec3Widget> m_ui;

	QVector3D m_value;
};
