#include <glad/glad.h>

#include "ui/AppGlWidget.hpp"

#include "managers/InputManager.hpp"

#include "renderer/Globals.hpp"
#include "renderer/Renderer.hpp"
#include "renderer/scene/Scene.hpp"
#include "renderer/scene/Camera.hpp"

#include "utils/Utils.hpp"

#include <QKeyEvent>

//-----------------------------------------------------------------------------

AppGlWidget::AppGlWidget(QWidget* parent)
	: QOpenGLWidget(parent)
	, m_scene(nullptr)
	, m_camera(nullptr)
{
}

//-----------------------------------------------------------------------------

void AppGlWidget::setDrawMode(DrawMode _drawMode) noexcept
{
	jl::Renderer::PolygonMode frontPolygonsMode;
	jl::Renderer::PolygonMode backPolygonsMode;

	switch (_drawMode)
	{
	case DrawMode::Fill:
		{
			frontPolygonsMode = jl::Renderer::PolygonMode::Fill;
			backPolygonsMode = jl::Renderer::PolygonMode::Fill;
		}
		break;

	case DrawMode::Edges:
		{
			frontPolygonsMode = jl::Renderer::PolygonMode::Line;
			backPolygonsMode = jl::Renderer::PolygonMode::Line;
		}
		break;

	default:
		ASSERT(0);
	}

	m_prerenderCommand = [frontPolygonsMode, backPolygonsMode]()
	{
		jl::Renderer::setFrontPolygonsMode(frontPolygonsMode);
		jl::Renderer::setBackPolygonsMode(backPolygonsMode);
	};
	m_postrenderCommand = []()
	{
		jl::Renderer::setFrontPolygonsMode(jl::Renderer::PolygonMode::Fill);
		jl::Renderer::setBackPolygonsMode(jl::Renderer::PolygonMode::Fill);
	};
}

//-----------------------------------------------------------------------------

void AppGlWidget::setScene(const jl::Scene* _scene) noexcept
{
	m_scene = _scene;
}

//-----------------------------------------------------------------------------

void AppGlWidget::setCamera(jl::Camera* _camera) noexcept
{
	m_camera = _camera;
}

//-----------------------------------------------------------------------------

app::Connection AppGlWidget::registerOnGlLoaded(const GlLoadedSignal::slot_type& _callback)
{
	return m_glLoadedSignal.connect(_callback);
}

//-----------------------------------------------------------------------------

void AppGlWidget::initializeGL()
{
	ASSERT(gladLoadGL());
	m_glLoadedSignal();

	LOG_INFO(
		"OpenGL info\n-> Vendor: {}\n-> Renderer: {}\n-> Version: {}",
		glGetString(GL_VENDOR),
		glGetString(GL_RENDERER),
		glGetString(GL_VERSION)
	);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

//-----------------------------------------------------------------------------

void AppGlWidget::resizeGL(int _w, int _h)
{
	jl::Globals::s_screenWidth = static_cast<jl::u32>(_w);
	jl::Globals::s_screenHeight = static_cast<jl::u32>(_h);

	const float fWidth = static_cast<float>(_w);
	const float fHeight = static_cast<float>(_h);
	m_camera->setAspect(fWidth / fHeight);

	glViewport(0, 0, _w, _h);
}

//-----------------------------------------------------------------------------

void AppGlWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (m_scene && m_camera)
	{
		if (m_prerenderCommand)
		{
			m_prerenderCommand();
		}

		m_scene->render(*m_camera);

		if (m_postrenderCommand)
		{
			m_postrenderCommand();
		}
	}
}

//-----------------------------------------------------------------------------

void AppGlWidget::keyPressEvent(QKeyEvent* _event)
{
	if (_event->isAutoRepeat())
	{
		return;
	}

	LOG_INFO("Pressed key, keycode: {}", _event->nativeVirtualKey());
	InputManager::getInstance().processKey(_event->nativeVirtualKey(), true);
}

//-----------------------------------------------------------------------------

void AppGlWidget::keyReleaseEvent(QKeyEvent* _event)
{
	if (_event->isAutoRepeat())
	{
		return;
	}

	InputManager::getInstance().processKey(_event->nativeVirtualKey(), false);
}

//-----------------------------------------------------------------------------
