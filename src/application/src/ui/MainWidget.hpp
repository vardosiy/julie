#pragma once

#include "CommonDefs.hpp"
#include "data/Project.hpp"

#include <QWidget>
#include <QStringListModel>
#include <QStandardItemModel>
#include <QStringList>

#include <memory>

//-----------------------------------------------------------------------------

namespace Ui {
class MainWidget;
}

namespace data {
class Object;
}

//-----------------------------------------------------------------------------

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

	void addObjectToGuiList(const data::Object& _object);

//-----------------------------------------------------------------------------
	std::unique_ptr<Ui::MainWidget> m_ui;

	QStringListModel m_objectsListModel;
	QStringList m_objectsNamesList;

	QStandardItemModel m_propertiesTableModel;

	data::Project m_project;

	app::ScopedConnection m_glLoadedConnection;
};

//-----------------------------------------------------------------------------
