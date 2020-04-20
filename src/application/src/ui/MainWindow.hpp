#pragma once

#include "CommonDefs.hpp"
#include "ui/IEntityActionHandler.hpp"

#include <QMainWindow>
#include <QStringList>
#include <QStringListModel>

#include <memory>

//-----------------------------------------------------------------------------

namespace Ui {
class MainWindow;
}

namespace jl {
class Scene;
class Object;
}

class EntitiesWidget;
class PropertiesWidget;

class MainWindow : public QMainWindow, public IEntityActionHandler
{
	Q_OBJECT

//-----------------------------------------------------------------------------
public:
	explicit MainWindow(QMainWindow* parent = nullptr);
	~MainWindow() override;

	void addObject() override;
	void deleteObject(const QString& _name) override;
	void objectSelected(const QString& _name) override;

	void addMaterial() override;
	void deleteMaterial(const QString& _name) override;
	void materialSelected(const QString& _name) override;

	void resetSelection() override;

//-----------------------------------------------------------------------------
private slots:
	void onFillPolygonsValueChanged(int _state);

//-----------------------------------------------------------------------------
private:
	void setupUi();

	void onGlLoaded();

	std::string computeObjectName() const;
	std::string computeMaterialName() const;

	static std::string computeEntityName(
		std::string_view _base,
		std::function<bool(const std::string&)>&& _entityExistCheckFun
	);

//-----------------------------------------------------------------------------
	std::unique_ptr<Ui::MainWindow> m_ui;
	std::unique_ptr<jl::Scene> m_scene;

	QStringList m_objectsNamesList;
	QStringListModel m_objectsListModel;

	QStringList m_materialsNamesList;
	QStringListModel m_materialsListModel;

	EntitiesWidget* m_entitisWdg;
	PropertiesWidget* m_propertiesWdg;

	app::ScopedConnection m_glLoadedConnection;

	static constexpr std::string_view k_saveFile = "SaveFile.json";
	static constexpr std::string_view k_defaultObjectName = "object_000";
	static constexpr std::string_view k_defaultMaterialName = "material_000";
};

//-----------------------------------------------------------------------------