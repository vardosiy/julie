#pragma once

#include "CommonDefs.hpp"
#include "data/Project.hpp"

#include <QWidget>
#include <QStringListModel>
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

	void onGlLoaded();

//-----------------------------------------------------------------------------
private slots:
	void onFillPolygonsValueChanged(int _state);

	void onAddEntityBtnReleased();
	void onDeleteEntityBtnReleased();

//-----------------------------------------------------------------------------
private:
	void setupConnections();

	void addObjectToGuiList(const data::Object& _object);

//-----------------------------------------------------------------------------
	std::unique_ptr<Ui::MainWidget> m_ui;

	QStringListModel m_objectsListModel;
	QStringList m_objectsNamesList;

	data::Project m_project;

	app::ScopedConnection m_glLoadedConnection;
};

//-----------------------------------------------------------------------------
