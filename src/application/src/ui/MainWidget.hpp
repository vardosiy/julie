#pragma once

#include "CommonDefs.hpp"

#include <QWidget>
#include <QStringListModel>
#include <QStandardItemModel>
#include <QStringList>

#include <memory>

//-----------------------------------------------------------------------------

namespace Ui {
class MainWidget;
}

namespace jl {
class Scene;
class Object;
}

class MainWidget : public QWidget
{
	Q_OBJECT

//-----------------------------------------------------------------------------
public:
	explicit MainWidget(QWidget* parent = nullptr);
	~MainWidget();

//-----------------------------------------------------------------------------
private slots:
	void onFillPolygonsValueChanged(int _state);

	void onAddEntityBtnReleased();
	void onDeleteEntityBtnReleased();

//-----------------------------------------------------------------------------
private:
	void setupUi();
	void setupConnections();

	void onGlLoaded();

	void addObjectToGuiList(const jl::Object& _object);

//-----------------------------------------------------------------------------
	std::unique_ptr<Ui::MainWidget> m_ui;
	std::unique_ptr<jl::Scene> m_scene;

	QStringList m_objectsNamesList;
	QStringListModel m_objectsListModel;
	QStandardItemModel	m_propertiesTableModel;

	app::ScopedConnection m_glLoadedConnection;
};

//-----------------------------------------------------------------------------
