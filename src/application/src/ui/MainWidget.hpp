#pragma once

#include <QWidget>

#include <memory>

namespace Ui {
class MainWidget;
}

namespace jl {
class Object;
}

class QStringListModel;

class MainWidget : public QWidget
{
	Q_OBJECT

public:
	explicit MainWidget(QWidget* parent = nullptr);
	~MainWidget();

	void refreshObjectsList(const std::vector<std::unique_ptr<jl::Object>>& _objects);

private slots:
	void cbFillPolygonsValueChanged(int _state);

private:
	std::unique_ptr<Ui::MainWidget> m_ui;
	std::unique_ptr<QStringListModel> m_listModel;
};
