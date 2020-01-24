#pragma once

#include "renderer/Types.hpp"

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

	void refreshObjectsList(const std::vector<jl::s32>& _objects);

private slots:
	void chbFillPolygonsValueChanged(int _state);

private:
	std::unique_ptr<Ui::MainWidget> m_ui;
	std::unique_ptr<QStringListModel> m_listModel;
};
