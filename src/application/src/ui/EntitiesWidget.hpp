#pragma once

#include "ui/IEntityActionHandler.hpp"

#include <QWidget>
#include <QItemSelection>
#include <QAbstractItemModel>

#include <memory>
#include <functional>

//-----------------------------------------------------------------------------

namespace Ui {
class EntitiesWidget;
}

//-----------------------------------------------------------------------------

class EntitiesWidget : public QWidget
{
	Q_OBJECT

//-----------------------------------------------------------------------------
public:
	explicit EntitiesWidget(QWidget* parent = nullptr);

	void setObjectsListModel(QAbstractItemModel& _model);
	void setMaterialsListModel(QAbstractItemModel& _model);

	void setEntityActionHandler(IEntityActionHandler& _handler);

//-----------------------------------------------------------------------------
private slots:
	void onAddEntityBtnReleased();
	void onDeleteEntityBtnReleased();

	void onObjectSelected(const QItemSelection& _selection);
	void onMaterialSelected(const QItemSelection& _selection);

//-----------------------------------------------------------------------------
private:
	void onEntitySelected(const QItemSelection& _selection, std::function<void(const QString&)>&& _callback);

//-----------------------------------------------------------------------------
	std::unique_ptr<Ui::EntitiesWidget> m_ui;

	IEntityActionHandler* m_actionHandler;
};

//-----------------------------------------------------------------------------
