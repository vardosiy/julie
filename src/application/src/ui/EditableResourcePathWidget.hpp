#pragma once

#include <QWidget>

namespace Ui {
class EditableResourcePathWidget;
}

class EditableResourcePathWidget : public QWidget
{
	Q_OBJECT

public:
	explicit EditableResourcePathWidget(QWidget* _parent = nullptr);

	QString getPath() const noexcept;
	void setPath(const QString& _path) noexcept;

private slots:
	void onOpenFilePressed();

private:
	std::unique_ptr<Ui::EditableResourcePathWidget> m_ui;
};
