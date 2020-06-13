#pragma once

#include "CommonDefs.hpp"
#include "ui/IEntityActionHandler.hpp"

#include "controllers/FreeflyCameraController.hpp"
#include "renderer/scene/Camera.hpp"

#include <QMainWindow>
#include <QTimer>

#include <memory>

//-----------------------------------------------------------------------------

namespace Ui {
class MainWindow;
}

namespace jl {
class Model;
class Material;
}

class SceneWrapper;
class ObjectWrapper;
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

	void objectSelected(ObjectWrapper& _objWrapper) override;
	void materialSelected(jl::Material& _material) override;
	void resetSelection() override;

	void onObjectMoved(ObjectWrapper& _objWrapper) override;
	void onObjectScaled(ObjectWrapper& _objWrapper) override;

//-----------------------------------------------------------------------------
private slots:
	void update();

//-----------------------------------------------------------------------------
private:
	void onGlLoaded();

	void setupUi();
	void setupRoom();

	float getDeltaTime();

//-----------------------------------------------------------------------------
	std::unique_ptr<Ui::MainWindow> m_ui;

	EntitiesWidget* m_entitisWdg;
	PropertiesWidget* m_propertiesWdg;
	ViewPropertiesWidget* m_viewPropertiesWdg;

	QTimer m_updateTimer;
	app::ScopedConnection m_glLoadedConnection;

	std::unique_ptr<SceneWrapper> m_sceneWrapper;
	std::unique_ptr<jl::Model> m_roomModel;

	jl::Camera m_camera;
	FreeflyCameraController m_cameraController;

	static constexpr std::string_view k_saveFile = "SaveFile.json";
};

//-----------------------------------------------------------------------------
