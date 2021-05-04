#pragma once

#include "CommonDefs.hpp"

#include "julie/managers/AppController.hpp"

#include <QOpenGLWidget>

#include <glm/glm.hpp>

#include <functional>

//-----------------------------------------------------------------------------

class GameCore;
class IEntityActionHandler;

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

	void setGameCore(GameCore* _core) noexcept;
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

	GameCore* m_core;
	IEntityActionHandler* m_actionHandler;
};

//-----------------------------------------------------------------------------
