#pragma once

#include "CommonDefs.hpp"

#include <QMainWindow>
#include <QStringListModel>
#include <QStandardItemModel>
#include <QStringList>

#include <memory>

//-----------------------------------------------------------------------------

namespace Ui {
class MainWindow;
}

namespace jl {
class Scene;
class Object;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

//-----------------------------------------------------------------------------
public:
	explicit MainWindow(QMainWindow* parent = nullptr);
	~MainWindow();

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
	std::unique_ptr<Ui::MainWindow> m_ui;
	std::unique_ptr<jl::Scene> m_scene;

	QStringList m_objectsNamesList;
	QStringListModel m_objectsListModel;
	QStandardItemModel m_propertiesTableModel;

	app::ScopedConnection m_glLoadedConnection;

	static constexpr std::string_view k_saveFile = "SaveFile.json";
};

//-----------------------------------------------------------------------------
