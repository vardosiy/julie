#pragma once

#include "renderer/scene/Scene.hpp"
#include "renderer/scene/Camera.hpp"

#include <QOpenGLWidget>
#include <QTimer>

#include <functional>

namespace data {
class Object;
}

class AppGlWidget : public QOpenGLWidget
{
	Q_OBJECT

public:
	enum class DrawMode
	{
		Fill,
		Edges,
	};

	AppGlWidget(QWidget* _parent = nullptr);

	void setDrawMode(DrawMode _drawMode);

	void doOnGlInitialized(std::function<void()> _callback);

	void onObjectAdded(data::Object& _object);

protected:
	void initializeGL() override;
	void resizeGL(int _w, int _h) override;
	void paintGL() override;

	void keyPressEvent(QKeyEvent* _event) override;
	void keyReleaseEvent(QKeyEvent* _event) override;

private slots:
	void update();

private:
	float getDeltaTime();

	void updateCameraPosition(float _dt) noexcept;

private:
	std::function<void()> m_callback;

	std::function<void()> m_prerenderCommand;
	std::function<void()> m_postrenderCommand;

	jl::Scene m_scene;
	jl::Camera m_camera;

	float m_camMoveSpeed;
	float m_camRotationSpeed;

	QTimer m_updateTimer;
};
