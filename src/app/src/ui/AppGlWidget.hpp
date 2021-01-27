#pragma once

#include "CommonDefs.hpp"
#include "ui/IEntityActionHandler.hpp"

#include "julie/core/Types.hpp"
#include "julie/core/Aabb.hpp"
#include "julie/managers/AppController.hpp"

#include <QOpenGLWidget>

#include <glm/glm.hpp>

#include <functional>

//-----------------------------------------------------------------------------

namespace jl {
class Scene;
class Object;
class Camera;
}

class AppGlWidget : public QOpenGLWidget, public IOpenGlContextOwner
{
	Q_OBJECT

//-----------------------------------------------------------------------------
public:
	using GlLoadedSignal = app::Signal<void()>;

//-----------------------------------------------------------------------------
	AppGlWidget(QWidget* _parent = nullptr);
	~AppGlWidget();

	void makeContextCurrent() override;

	void setWireframeModeEnabled(bool _val) noexcept;

	void setCamera(jl::Camera* _camera) noexcept;
	void setScene(jl::Scene* _scene) noexcept;
	void setActionHandler(IEntityActionHandler* _handler) noexcept;

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
	void processKeyboardModifiers(Qt::KeyboardModifiers _modifiers);

//-----------------------------------------------------------------------------
	GlLoadedSignal m_glLoadedSignal;

	std::function<void()> m_prerenderCommand;
	std::function<void()> m_postrenderCommand;

	jl::Camera* m_camera;
	jl::Scene* m_scene;
	IEntityActionHandler* m_actionHandler;
};

//-----------------------------------------------------------------------------
