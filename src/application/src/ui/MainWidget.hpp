#pragma once

#include <QWidget>

#include <memory>

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
	Q_OBJECT

public:
	explicit MainWidget(QWidget* parent = nullptr);
	~MainWidget();

private slots:
	void cbFillPolygonsValueChanged(int _state);

private:
	std::unique_ptr<Ui::MainWidget> m_ui;
};
