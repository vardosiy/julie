#pragma once

#include "CommonDefs.hpp"
#include "ui/IEntityActionHandler.hpp"

#include "controllers/FreeflyCameraController.hpp"

#include "julie/scene/Scene.hpp"
#include "julie/scene/Camera.hpp"

#include <QMainWindow>
#include <QTimer>

#include <memory>

//-----------------------------------------------------------------------------

namespace Ui {
class MainWindow;
}

namespace jl {
class Scene;
class Material;
}

class EntitiesWidget;
class PropertiesWidget;
class ViewPropertiesWidget;

class MainWindow : public QMainWindow, public IEntityActionHandler
{
	Q_OBJECT

//-----------------------------------------------------------------------------
public:
	explicit MainWindow(QMainWindow* parent = nullptr);
	~MainWindow() override;

	void entitySelected(jl::EntityRef _entity) override;
	void materialSelected(jl::Material& _material) override;
	void resetSelection() override;

	void onEntityMoved(jl::EntityRef _entity) override;
	void onEntityScaled(jl::EntityRef _entity) override;

//-----------------------------------------------------------------------------
private slots:
	void update();

//-----------------------------------------------------------------------------
private:
	void onGlLoaded();

	void initUi();
	void initScene();
	void initDefaultMaterial();

//-----------------------------------------------------------------------------
	std::unique_ptr<Ui::MainWindow> m_ui;

	EntitiesWidget* m_entitisWdg;
	PropertiesWidget* m_propertiesWdg;
	ViewPropertiesWidget* m_viewPropertiesWdg;

	QTimer m_updateTimer;
	app::ScopedConnection m_glLoadedConnection;

	jl::Scene m_scene;
	jl::Camera m_camera;

	FreeflyCameraController m_cameraController;

	static constexpr std::string_view k_saveFile{ "SaveFile.json" };
};

//-----------------------------------------------------------------------------
