#pragma once

#include "CommonDefs.hpp"
#include "ui/IEntityActionHandler.hpp"

#include "renderer/Types.hpp"
#include "renderer/managers/AppController.hpp"

#include <boost/optional.hpp>
#include <glm/glm.hpp>

#include <QOpenGLWidget>

#include <functional>

//-----------------------------------------------------------------------------

namespace jl {
class Camera;
}

class SceneWrapper;
class ObjectWrapper;

class AppGlWidget : public QOpenGLWidget, public IOpenGlContextOwner
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
	~AppGlWidget();

	void makeContextCurrent() override;

	void setDrawMode(DrawMode _drawMode) noexcept;
	void drawBoundingBoxes(bool _val) noexcept;

	void setScene(SceneWrapper* _sceneWrapper) noexcept;
	void setUninteractibleObjects(std::vector<const ObjectWrapper*> _objWrappers) noexcept;

	void setCamera(jl::Camera* _camera) noexcept;
	void setActionHandler(IEntityActionHandler* _handler) noexcept;

	app::Connection registerOnGlLoaded(const GlLoadedSignal::slot_type& _callback);

//-----------------------------------------------------------------------------
protected:
	void initializeGL() override;
	void resizeGL(int _w, int _h) override;
	void paintGL() override;

	void keyPressEvent(QKeyEvent* _event) override;
	void keyReleaseEvent(QKeyEvent* _event) override;

	void mousePressEvent(QMouseEvent* _event) override;
	void mouseReleaseEvent(QMouseEvent* _event) override;
	void mouseMoveEvent(QMouseEvent* _event) override;

	void wheelEvent(QWheelEvent* _event) override;

//-----------------------------------------------------------------------------
private:
	void processKeyboardModifiers(Qt::KeyboardModifiers _modifiers);
	void processObjectSelection(const jl::rayf& _ray);

	static jl::rayf calcRayFromMouseClick(QPoint _pos, const jl::Camera& _camera);
	static glm::vec3 calcWorldPosFromMouseClick(QPoint _pos, const jl::Camera& _camera);

	static glm::vec3 calcNormalizedClickPos(QPoint _pos, const jl::Camera& _camera);

//-----------------------------------------------------------------------------
	GlLoadedSignal m_glLoadedSignal;

	std::function<void()> m_prerenderCommand;
	std::function<void()> m_postrenderCommand;

	SceneWrapper* m_sceneWrapper;
	std::vector<const ObjectWrapper*> m_uninteractibleObjWrappers;

	jl::Camera* m_camera;
	IEntityActionHandler* m_actionHandler;

	ObjectWrapper* m_selectedObject;
	float m_selectedObjDistance;

	boost::optional<glm::vec3> m_prevMousePos;
};

//-----------------------------------------------------------------------------
