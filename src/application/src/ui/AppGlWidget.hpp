#pragma once

#include "CommonDefs.hpp"

#include <QOpenGLWidget>

#include <functional>

//-----------------------------------------------------------------------------

namespace jl {
class Scene;
class Camera;
}

class AppGlWidget : public QOpenGLWidget
{
	Q_OBJECT

//-----------------------------------------------------------------------------
public:
	enum class DrawMode
	{
		Fill,
		Edges
	};

	using GlLoadedSignal = app::Signal<void()>;

//-----------------------------------------------------------------------------
	AppGlWidget(QWidget* _parent = nullptr);

	void setDrawMode(DrawMode _drawMode) noexcept;

	void setScene(const jl::Scene* _scene) noexcept;
	void setCamera(jl::Camera* _camera) noexcept;

	app::Connection registerOnGlLoaded(const GlLoadedSignal::slot_type& _callback);

//-----------------------------------------------------------------------------
protected:
	void initializeGL() override;
	void resizeGL(int _w, int _h) override;
	void paintGL() override;

	void keyPressEvent(QKeyEvent* _event) override;
	void keyReleaseEvent(QKeyEvent* _event) override;

//-----------------------------------------------------------------------------
private:
	GlLoadedSignal m_glLoadedSignal;

	std::function<void()> m_prerenderCommand;
	std::function<void()> m_postrenderCommand;

	const jl::Scene* m_scene;
	jl::Camera* m_camera;
};

//-----------------------------------------------------------------------------
