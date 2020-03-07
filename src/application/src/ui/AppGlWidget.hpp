#pragma once

#include "CommonDefs.hpp"

#include "renderer/scene/Scene.hpp"
#include "renderer/scene/Camera.hpp"

#include <QOpenGLWidget>
#include <QTimer>

#include <functional>

//-----------------------------------------------------------------------------

namespace data {
class Object;
}

//-----------------------------------------------------------------------------

class AppGlWidget : public QOpenGLWidget
{
	Q_OBJECT

//-----------------------------------------------------------------------------
public:
	enum class DrawMode
	{
		Fill,
		Edges,
	};

	using GlLoadedSignal = app::Signal<void()>;

//-----------------------------------------------------------------------------
	AppGlWidget(QWidget* _parent = nullptr);

	app::Connection registerOnGlLoaded(const GlLoadedSignal::slot_type& _callback);

	void onObjectAdded(data::Object& _object);

	void setDrawMode(DrawMode _drawMode);
	void setCameraMoveSpeed(int _speed) noexcept;
	void setCameraRotateSpeed(int _speed) noexcept;

//-----------------------------------------------------------------------------
protected:
	void initializeGL() override;
	void resizeGL(int _w, int _h) override;
	void paintGL() override;

	void keyPressEvent(QKeyEvent* _event) override;
	void keyReleaseEvent(QKeyEvent* _event) override;

//-----------------------------------------------------------------------------
private slots:
	void update();

//-----------------------------------------------------------------------------
private:
	float getDeltaTime();

	void updateCameraPosition(float _dt) noexcept;

//-----------------------------------------------------------------------------
	GlLoadedSignal m_glLoadedSignal;

	std::function<void()> m_prerenderCommand;
	std::function<void()> m_postrenderCommand;

	jl::Scene m_scene;
	jl::Camera m_camera;

	float m_camMoveSpeed;
	float m_camRotationSpeed;

	QTimer m_updateTimer;
};

//-----------------------------------------------------------------------------
