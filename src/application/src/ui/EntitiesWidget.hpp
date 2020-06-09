#pragma once

#include "ui/IEntityActionHandler.hpp"

#include <QWidget>
#include <QItemSelection>
#include <QStringList>
#include <QStringListModel>

#include <memory>
#include <functional>

//-----------------------------------------------------------------------------

namespace Ui {
class EntitiesWidget;
}

namespace jl {
class Material;
}

class SceneWrapper;

class EntitiesWidget : public QWidget
{
	Q_OBJECT

//-----------------------------------------------------------------------------
public:
	explicit EntitiesWidget(QWidget* parent = nullptr);

	void setScene(SceneWrapper* _sceneWrapper);
	void setEntityActionHandler(IEntityActionHandler* _handler);

//-----------------------------------------------------------------------------
private slots:
	void onCurrentTabChanged(int _idx);

	void onAddEntityBtnReleased();
	void onDeleteEntityBtnReleased();

//-----------------------------------------------------------------------------
private:
	void onEntitySelected(const QItemSelection& _selection);
	void refreshMaterialsList();

	void addObject(const std::string& _name);
	void addMaterial(const std::string& _name);

	void deleteObject(const QString& _name);
	void deleteMaterial(const QString& _name);

	void replaceMaterialInAllMeshes(const jl::Material* _old, const jl::Material* _new);

	std::string computeObjectName() const;
	std::string computeMaterialName() const;
	static std::string computeEntityName(
		std::string_view _base,
		std::function<bool(const std::string&)>&& _entityExistCheckFun
	);

//-----------------------------------------------------------------------------
	std::unique_ptr<Ui::EntitiesWidget> m_ui;

	QStringList			m_objectsNamesList;
	QStringListModel	m_objectsListModel;
	QStringList			m_materialsNamesList;
	QStringListModel	m_materialsListModel;

	SceneWrapper* m_sceneWrapper;
	IEntityActionHandler* m_actionHandler;

	static constexpr std::string_view k_defaultObjectName = "Object_000";
	static constexpr std::string_view k_defaultMaterialName = "Material_000";
};

//-----------------------------------------------------------------------------
